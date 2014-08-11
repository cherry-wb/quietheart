//#ifndef __HWR_API2_H
//#define __HWR_API2_H

//
#ifndef PPHWR_GLOBAL_SETTING
#define PPHWR_GLOBAL_SETTING 1
/*lvkaiadd{*/
//#define WINAPI  
//#define STATIC_LINK
//#define ENABLE_SEGMENTATION
//#define AI_ON
/*lvkaiadd}*/
#ifndef SHARP_18030
//-----------------------------
#define IN_5401_TYPE      1
#define IN_JIS1_TYPE      1
#define EUROPEAN_TYPE	  1
#define UPPER_ALPHA_TYPE  2
#define LOWER_ALPHA_TYPE  4
#define KATA_TYPE         8
#define HIRA_TYPE        16
#define NUMA_TYPE        32
#define SYMBOL_TYPE      64
#define GESTURE_TYPE    128
#define IN_13052_TYPE   256
#define IN_JIS2_TYPE    256
#define CONTROL_TYPE    512
#define LEARN_TYPE     1024
#define KSC_TYPE       2048
#define PHON_TYPE    0x8000
#define ALPHA_TYPE (UPPER_ALPHA_TYPE|LOWER_ALPHA_TYPE)
#define KANA_TYPE  (KATA_TYPE|HIRA_TYPE)
#define CHINESE_TYPE (IN_JIS1_TYPE|IN_JIS2_TYPE)
#define ASCII_TYPE (SYMBOL_TYPE|NUMA_TYPE|ALPHA_TYPE)
#define CURSIVE_TYPE (IN_JIS1_TYPE|ASCII_TYPE|KANA_TYPE|GESTURE_TYPE)
#define ALL_TYPE   (CURSIVE_TYPE|IN_JIS2_TYPE)
#else
#define LOWER_ALPHA_TYPE		1
#define UPPER_ALPHA_TYPE		2
#define NUMA_TYPE			4
#define NUMERIC_TYPE		4
#define GENERAL_PUNCT_TYPE		8
#define EXTEND_PUNCT_TYPE		16
#define GENERAL_SYMBOL_TYPE		32
#define EXTEND_SYMBOL_TYPE		64
#define GESTURE_TYPE		128
#define RADICAL_TYPE		256
#define CHINESE_1_TYPE		512
#define CHINESE_2_TYPE		1024

#define PINYIN_LOWER_TYPE   2048
#define PINYIN_UPPER_TYPE   4096
#define IN_KSC_TYPE			8192
#define HIRA_TYPE           16384  
#define KATA_TYPE           32768 
#define KSC_TYPE			IN_KSC_TYPE

#define IN_JIS1_TYPE		CHINESE_1_TYPE
#define IN_JIS2_TYPE		CHINESE_2_TYPE
#define IN_5401_TYPE		CHINESE_1_TYPE
#define IN_13052_TYPE		CHINESE_2_TYPE
#define SYMBOL_TYPE			GENERAL_SYMBOL_TYPE
#define ALPHA_TYPE			(UPPER_ALPHA_TYPE|LOWER_ALPHA_TYPE)
#define KANJI_TYPE      (HIRA_TYPE+KATA_TYPE)
#define ASCII_TYPE      (ALPHA_TYPE+NUMA_TYPE+SYMBOL_TYPE)
#define CHINESE_TYPE    (IN_5401_TYPE|IN_13052_TYPE)
#define CURSIVE_TYPE (IN_5401_TYPE|KANJI_TYPE|ASCII_TYPE|GESTURE_TYPE)

#define ALL_TYPE			(CHINESE_TYPE|NUMA_TYPE|SYMBOL_TYPE|ALPHA_TYPE|KANJI_TYPE|GESTURE_TYPE)

#endif
//-----------------------------
#define FULL_MODE 0
#define HALF_MODE 1
#define SHAPE_TYPE         0x0001  
#define TURN_ON_HK         0x0002  
#define TURN_ON_BIG_ONLY   0x0004  
#define TURN_ON_GB_ONLY    0x0008  
#define TURN_ON_BIG_AND_GB 0x000C  
#define TURN_ON_FULL_UNICODE 0x0010 
#define TURN_ON_GBB_ONLY   0x0020  
#define TURN_ON_OCR        0x0040  

#define JPN_SHIFT_JIS	932
#define SIMPLIFIED_CHINESE	936
#define HANGEUL_TongHabHyung	949 
#define TRADITIONAL_CHINESE	950
#define HANGEUL_JOHAB	1361


#define BIG_ONLY_MODE 0
#define GB_ONLY_MODE 1
#define BIG_AND_GB_MODE 2
#define FULL_UNICODE_MODE 3
#define GBB_ONLY_MODE 4

#define MAX_RADCOUNT 29
//-----------------------------

#define MAX_NO_POINT 2048
#define MAX_POINT_NO_IN_ONE_STROKE 256
#define CHAR_WIDTH_X 127
#define CHAR_WIDTH_Y 127
#define REAL_MAX_NO_CHAR	20
#define AI_CLOSE 0
#define AI_OPEN  1

struct point_type
{
  short 	x;
  short 	y;
};

struct RecogResultStruct
{
  short counter;
  unsigned short string[1024];
  unsigned short type[MAX_RADCOUNT];
  short AI[MAX_RADCOUNT];
  unsigned short cost[MAX_RADCOUNT];
};

struct SegmentResultStruct{
   short counter; 
   unsigned short string[1024]; 
   unsigned short type;
   unsigned short split_stroke_index[REAL_MAX_NO_CHAR+1]; 
};


#ifdef STATIC_LINK
extern short WINAPI SetArea(unsigned char *ptr_global_data,
		unsigned long Area);
extern int WINAPI GetRAMSize(void);

extern int WINAPI HWRInitialize(unsigned char * ptr_global_data,
  		     unsigned char *lpAIMMF,
		     unsigned char *lpLearnMMF,
                         unsigned char *DBAddress);

extern int WINAPI HWRRelease(unsigned char * ptr_global_data);

//extern int WINAPI SetCandCount(unsigned char *ptr_hwre_obj,
//                        int CandCount);
extern int WINAPI SetCandCount(unsigned char *ptr_hwre_obj,
                        int CandCount);//lvkaiadd


extern struct point_type * WINAPI
       process_one_stroke(unsigned char * ptr_global_data,
                          struct point_type *PointBuf);

extern struct RecogResultStruct * WINAPI
       sub(unsigned char * ptr_global_data,
           short Type,
		   short ShapeMode,
		   struct point_type *SubPoint);

#ifdef ENABLE_SEGMENTATION
extern void WINAPI segment_one_stroke(unsigned char * ptr_global_data,
                               short Type,
                               short ShapeMode,
                               struct point_type *PointBuf);

extern struct SegmentResultStruct * WINAPI
   split_recognition(unsigned char * ptr_global_data,
                     short Type,short ShapeMode,
                     struct point_type *RawData);

extern struct SegmentResultStruct * WINAPI
   start_recognition(unsigned char * ptr_global_data,
                     short Type,short ShapeMode);
#endif

extern void WINAPI set_segmentation_mode(unsigned char * ptr_global_data,
                                  short segmentation_switch,
                                  short dx);
#ifdef AI_ON
extern unsigned char WINAPI
   AI_Adjust(unsigned char * ptr_global_data,
             short nLearnCode, short Type,
             struct point_type *RawPointBuf);

extern void WINAPI VerifyAIHit(unsigned char * ptr_global_data,
                        int AIIndex);

extern void WINAPI SetAIHit(unsigned char * ptr_global_data,
                     int AIIndex);

extern void WINAPI SetAIMode(unsigned char * ptr_global_data,
                      char pp);

extern char WINAPI GetAIMode(unsigned char * ptr_global_data);
#endif

#ifdef ENABLE_LEARNING
extern unsigned char WINAPI
              SetDBFromData(unsigned char * ptr_global_data,
                            int nLearnCode,
                            unsigned short * pLearnString,
                            struct point_type *point);

extern struct LearnRecordStruct * WINAPI
       GetLearnRecord(unsigned char * ptr_global_data,
                      short nIndex);

extern int WINAPI GetLearnCount(unsigned char * ptr_global_data);

extern char WINAPI DeleteDatabase(unsigned char * ptr_global_data,
                           int DataIndex);

extern char WINAPI SetLearnCode(unsigned char * ptr_global_data,
                         short LrnIndex,
                         short CodeLength,
                         unsigned short *LearnString);
#endif

#endif



#ifdef DYNAMIC_LINK
int (WINAPI *GetRAMSize)(void);

int (WINAPI *HWRInitialize)(unsigned char * ptr_global_data,
  		     unsigned char *lpAIMMF,
		     unsigned char *lpLearnMMF,
                         unsigned char *DBAddress);

int (WINAPI *HWRRelease)(unsigned char * ptr_global_data);


struct point_type * (WINAPI
       *process_one_stroke)(unsigned char * ptr_global_data,
                          struct point_type *PointBuf);

struct RecogResultStruct * (WINAPI
       *sub)(unsigned char * ptr_global_data,
           short Type,
		   short ShapeMode,
		   struct point_type *SubPoint);

void (WINAPI *segment_one_stroke)(unsigned char * ptr_global_data,
                               short Type,
                               short ShapeMode,
                               struct point_type *PointBuf);

struct SegmentResultStruct * (WINAPI
   *split_recognition)(unsigned char * ptr_global_data,
                     short Type,short ShapeMode,
                     struct point_type *RawData);

struct SegmentResultStruct * (WINAPI
   *start_recognition)(unsigned char * ptr_global_data,
                     short Type,short ShapeMode);

void (WINAPI *set_segmentation_mode)(unsigned char * ptr_global_data,
                                  short segmentation_switch,
                                  short dx);

void  (WINAPI *set_writing_size)(unsigned char * ptr_global_data,short,short);

int (WINAPI *SetCandCount)(unsigned char * ptr_global_data,
                           int CandCount);


#ifdef AI_ON
unsigned char (WINAPI
   *AI_Adjust)(unsigned char * ptr_global_data,
             short nLearnCode, short Type,
             struct point_type *RawPointBuf);

void (WINAPI *VerifyAIHit)(unsigned char * ptr_global_data,
                        int AIIndex);

void (WINAPI *SetAIHit)(unsigned char * ptr_global_data,
                     int AIIndex);

void (WINAPI *SetAIMode)(unsigned char * ptr_global_data,
                      char pp);

char (WINAPI *GetAIMode)(unsigned char * ptr_global_data);
#endif

int (WINAPI *Find_Phrase)(unsigned short code,
                unsigned short size_of_return_buffer,
                unsigned short *return_buffer);


short (WINAPI *SetArea)(unsigned char *ptr_global_data,
			unsigned long Area);

#endif


#endif
//#endif
