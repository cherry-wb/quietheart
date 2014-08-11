#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>//for exit
#include <cstdio>
#include <cstring>
#include "neuHwrIface.h"

using std::cout;
using std::endl;
using std::cerr;
using std::vector;
using std::string;

NeuHwrIface::NeuHwrIface(const point_type *points)
{
	PerStrokeData = NULL;
	RawCharData = NULL;
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
#if MY_DEBUG == 1
		cout<<"the point serial is:"<<endl;
		for(int i = 0; i < inputPoints.size(); ++i)
		{
			cout<<"("<<inputPoints[i].x<<","<<inputPoints[i].y<<") ";
		}
		cout<<endl;
#endif
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
#if MY_DEBUG == 1
		cout<<"the point serial is:"<<endl;
		for(int i = 0; i < inputPoints.size(); ++i)
		{
			cout<<"("<<inputPoints[i].x<<","<<inputPoints[i].y<<") ";
		}
		cout<<endl;
#endif
	}
}
void NeuHwrIface::process()
{
	time_t old_time = time(NULL);
    time_t tmp_time = 1259315249;
    stime(&tmp_time);
#if MY_DEBUG == 1
	cout<<"begin to process!"<<endl;
#endif


	unsigned char WorkBuf[2048*1024];
	int size;

	/*
	   unsigned char AI_Buffer[65536]={0};
	   FILE *fp;
	   fp=_wfopen(L"ai.txt",L"rb");//lvkaiwatch,这个文件对应什么??
	   if(fp){
	   fread(AI_Buffer,1,65536,fp);//lvkaiwatch载入获取AI_Buffer
	   fclose(fp);
	   }
	 */

	//获取合适的内存大小
	size=GetRAMSize();
	if(size>sizeof(WorkBuf))
	{
#if MY_DEBUG == 1
		cerr<<"Error: GetRAMSize buffer size too large!"<<endl;
#endif
		exit(1);
	}

	//////初始化
	//HWRInitialize(WorkBuf,AI_Buffer,NULL,NULL);
	if(HWRInitialize(WorkBuf,NULL,NULL,NULL) != 0)
	{
		cerr<<"Error: HWRInitialize failed!"<<endl;
		exit(1);
	}
	
#ifdef AI_ON
	SetAIMode(WorkBuf,AI_OPEN);
#endif

	//设置
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
	cout<<"the counter is:"<<mySRS.counter<<endl;
	for(int i = 0; i < mySRS.counter; ++i)
	{
		cout<<mySRS.string[i];
	}
	cout<<endl;
#endif
#ifdef ENABLE_BOX_WRITING
	if(inputPoints.size() < 2048)
	{
		//short   RecogType=0xFFFF;

		//for chinese
		short   ShapeMode=0x0;
		short   RecogType=CHINESE_TYPE;

		//for eng
		//short   RecogType=ALPHA_TYPE;
		//short   ShapeMode=FULL_MODE;
		if(RawCharData != NULL)
		{
			delete []RawCharData;
			RawCharData = NULL;
		}
		RawCharData = new point_type[3000];
#if MY_DEBUG == 1
		cout<<"inputPoints.size():"<<inputPoints.size()<<endl;
#endif
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
#if MY_DEBUG == 1
		cout<<"the RawData is:"<<endl;
		for(int i = 0; i < inputPoints.size(); ++i)
		{
			cout<<i<<":("<<RawCharData[i].x<<','<<RawCharData[i].y<<")"<<endl;
		}
#endif
		ptr_RRS=sub(WorkBuf, RecogType, ShapeMode, RawCharData);
		if(ptr_RRS->counter>10)
		{
			cerr<<"Error: cand count out of range!"<<endl;
		}
		else
		{
#if MY_DEBUG == 1
			cout<<"the ptr_RRS->counter is "<<ptr_RRS->counter<<endl;
			cout<<"ptr_RRS->string is:"<<endl;
			for(int i = 0; i < ptr_RRS->counter; ++i)
			{
				cout<<ptr_RRS->string[i]<<',';
			}
			cout<<endl;
#endif
			/*
			   TCHAR txt[256]={0};
			   TCHAR msg[256]={0};
			   int i;
			   for(i=0;i<ptr_RRS->counter;i++)
			   {
			   wsprintf(msg,TEXT("<%04X>"),ptr_RRS->string[i]);
			   _tcscat(txt,msg);
			   }
			   MessageBox(hMainWnd,
			   txt,
			   TEXT("Result"),
			   MB_OK);
			   */
			//PostMessage(hMainWnd,UDM_GETSUBRESULT,0,ptr_RRS);
			//开始处理生成结果
			//看看这个处理生成什么
			char txt[256] = {0};
			char msg[256] = {0};
			for(int i = 0; i < ptr_RRS->counter; ++i)
			{
				sprintf(msg, "%04X", ptr_RRS->string[i]);
				strcat(txt,msg);
			}
			cout<<"first try to see what:"<<txt<<endl;
			//再看看这个处理生成什么
			char text[8192]={0},message[100]={0};
			sprintf(message,"(%3d)\n",ptr_RRS->counter);
			strcat(text,msg);
			if(ptr_RRS->counter > 0 && ptr_RRS->counter < 10)
			{
				int min = 10 < ptr_RRS->counter?10:ptr_RRS->counter;
				for(int j=0;j<min;j++)
				{
#ifdef UNICODE
                    sprintf(message,"1 %c(%04x)",
							ptr_RRS->string[j], ptr_RRS->string[j]);
#else
                    sprintf(message," 2 %C(%04x)",
                            ptr_RRS->string[j], ptr_RRS->string[j]);
#endif
                    strcat(text,message);
					sprintf(message,"%c",ptr_RRS->string[j]);
					message[1]=message[2]=0;
					cout<<"second try to see what:"<<message<<endl;
				}
			}
		}
	}//if(inputPoints.size()<2048)
#endif
	time_t new_time = old_time+(time(NULL) - tmp_time);
	stime(&new_time);
}
void NeuHwrIface::getOutputStrList(vector<string> &output)
{
#if MY_DEBUG == 1
	cout<<"begin to get out put!"<<endl;
#endif
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
