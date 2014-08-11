//#include <string>
#include <QStringList>
#include <vector>
#include <iostream>
#include <cstdlib>//for exit
#include <cstdio>
#include <cstring>
#include <QTextCodec>
#include <QDebug>
#include "neuHwrIface.h"

using std::vector;

NeuHwrIface::NeuHwrIface(const point_type *points)
{
	PerStrokeData = NULL;
	RawCharData = NULL;
	candcnt = 0;
	if(points != NULL)
	{
		for(int i = 0; ; ++i)
		{
			inputPoints.push_back(points[i]);
			if(points[i].x == -2 && points[i].y == -2)
			{
				break;
			}
		}
	}
}
void NeuHwrIface::setInputPoints(const point_type *points)
{
	if(points != NULL)
	{
		if(!inputPoints.empty())
		{
			inputPoints.clear();
		}
		for(int i = 0; ; ++i)
		{
			inputPoints.push_back(points[i]);
			if(points[i].x == -2 && points[i].y == -2)
			{
				break;
			}
		}
	}
}
void NeuHwrIface::process()
{
#if MY_DEBUG_TIMEMODIFYCRACK == 1
	time_t old_time = time(NULL);
    time_t tmp_time = 1259315249;
    stime(&tmp_time);
#endif
	unsigned char WorkBuf[2048*1024];
	int size;

	size=GetRAMSize();
	if(size>sizeof(WorkBuf))
	{
		exit(1);
	}

	//HWRInitialize(WorkBuf,AI_Buffer,NULL,NULL);
	if(HWRInitialize(WorkBuf,NULL,NULL,NULL) != 0)
	{
		qDebug()<<"Error: HWRInitialize failed!";
		exit(1);
	}
	
#ifdef AI_ON
	SetAIMode(WorkBuf,AI_OPEN);
#endif
	SetCandCount(WorkBuf,10);

#ifdef ENABLE_CONTINUOUS_WRITING
	//////对绘制的点序列的处理
	//如果连笔的话点矩阵中在鼠标抬起的时候会在结尾加上(-2,-2),然后如下处理：
	//segment_one_stroke(WorkBuf,RecogType,ShapeMode,PerStrokeData);
	//其中：
	short   RecogType=0xFFFF; //VALID_TYPE;
	short   ShapeMode=0x0;
	//如果不是连笔的话就不加(-2,-2)
	//short   RecogType=ALPHA_TYPE;
	//short   ShapeMode=FULL_MODE;
	if(PerStrokeData != NULL)
	{
		delete []PerStrokeData;
		PerStrokeData = NULL;
	}
	PerStrokeData = new point_type[1024];
	for(int i = 0; i < 1024; ++i)
	{
		if(i < inputPoints.size())
		{
			PerStrokeData[i] = inputPoints[i];
		}
		else
		{
			//PerStrokeData[i].x = -2;
			//PerStrokeData[i].y = -2;
			PerStrokeData[i].x = 0;
			PerStrokeData[i].y = 0;
		}
	}

	struct RecogResultStruct *ptr_RRS;
	struct SegmentResultStruct *ptr_SRS;
	static struct SegmentResultStruct mySRS;
	segment_one_stroke(WorkBuf,RecogType,ShapeMode,PerStrokeData);
	ptr_SRS=start_recognition(WorkBuf,RecogType,ShapeMode);
	mySRS=*ptr_SRS;
#endif
#ifdef ENABLE_BOX_WRITING
	if(inputPoints.size() < 2048)
	{
		//short   RecogType=0xFFFF;
		short   RecogType=ALL_TYPE;
		//short   ShapeMode=0x0;
		short   ShapeMode=JPN_SHIFT_JIS;
		//short   RecogType=ALPHA_TYPE;
		//short   ShapeMode=FULL_MODE;
		if(RawCharData != NULL)
		{
			delete []RawCharData;
			RawCharData = NULL;
		}
		RawCharData = new point_type[3000];
		for(int i = 0; i < 3000; ++i)
		{
			if(i < inputPoints.size())
			{
				RawCharData[i] = inputPoints[i];
			}
			else
			{
				RawCharData[i].x = -2;
				RawCharData[i].y = -2;
			}
		}
		struct RecogResultStruct *ptr_RRS;
		ptr_RRS=sub(WorkBuf, RecogType, ShapeMode, RawCharData);
		int counter = ptr_RRS->counter > 10?10:ptr_RRS->counter;
#ifdef UNICODE
		for(int j=0;j<counter;j++)
		{
			QString tmp(QChar(ptr_RRS->string[j]));
			outputStrList<<tmp;
		}
#endif
		qDebug()<<"!!!!!!!list:"<<outputStrList;
	}//if(inputPoints.size()<2048)
#endif
	HWRRelease(WorkBuf);//释放资源
#if MY_DEBUG_TIMEMODIFYCRACK == 1
	time_t new_time = old_time+(time(NULL) - tmp_time);
	stime(&new_time);
#endif
}
void NeuHwrIface::getOutputStrList(QStringList &output)
{
	output = outputStrList;
}
NeuHwrIface::~NeuHwrIface()
{
	if(PerStrokeData != NULL)
	{
		delete []PerStrokeData;
		PerStrokeData = NULL;
	}
	if(RawCharData != NULL)
	{
		delete []RawCharData;
		RawCharData = NULL;
	}
}
