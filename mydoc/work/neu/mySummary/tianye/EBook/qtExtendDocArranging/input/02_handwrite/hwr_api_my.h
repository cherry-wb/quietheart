/*说明：这个文件是对头文件hwr_api.h的我的总结。
 *说明了使用那个头文件的方法。

 *关于平台的问题
 *如果将这个头文件接口如果用在linux环境下，那么：
  如果是在 Linux 上面, 必須把WINAPI 幾個字使用 -DWINAPI= 的參數屏蔽掉;
  另外, 因為提供的是靜態庫, 請定義 STATIC_LINK 這個關鍵字(syntax : -DSTATIC_LINK)
  以及 -DENABLE_SEGMENTATION -DAI_ON

 *关于文档和头文件的差异问题：
 文档是：highlevelplatformapi4_continuouswriting_without_phrase.pdf
 头文件是：hwr_api.h
  文档中第3页中的MAX_NO_POINT_IN_SCREEN定义没有在头文件中找到。
  文档中第3页中的MAX_STROKE_SIZE定义没有在头文件中找到。
  文档中第3页中的MAX_POINT_FOR_PER_SHAPE定义没有在头文件中找到。
  文档中第6页中的MAX_BUFFER_RETURN_SIZE定义没有在头文件中找到。
  文档中第6页中的NormalPointType结构定义没有在头文件中找到。
  文档中第7页中的LearnRecordStruct结构定义没有在头文件中找到,但是在头文件中的一个函数(GetLearnRecord)声明中发现了该结构的引用。
  文档中第7页中的RecogStruct结构定义没有在头文件中找到。
  在文档19页中的函数HWRRelease返回值是整数，在头文件中动态库方式返回的是指针？
  文档第14页中的AI_Adjust函数，说明该函数返回的是True和False但是头文件中是char，那么这个函数在使用的时候怎样处理它的返回值呢？

 *关于库函数的问题
SetArea什么作用？函数在文档中没有指明作用，是否这个函数不需要？
process_one_stroke什么作用？函数在文档中没有指明作用，是否这个函数不需要？
set_writing_size什么作用？函数在文档中没有指明作用，是否这个函数不需要？
SetCandCount什么作用？函数在文档中没有指明作用，是否这个函数不需要？

sub函数的参数：Type,ShapeMode的可能取值是什么？能否举例？最好针对英文和中文字符。
				SubPoint参数是否就是以(-2,-2)结尾的点数组？

SetAIMode函数的参数pp的可能取值是什么？

split_recognition函数当用户想要分割Result_Word_List中的字符的时候被调用,这里Result_Word_List是什么结构的？分割的是什么？能否举例说明一下用户在什么时候会分割。

*关于数据结构的问题：
struct RecogResultStruct这个数据结构，在文档中没有说，能否具体说明一下其每个成员的作用？以及它和结构SegmentResultStruct的关系？

SegmentResultStruct结构中的string成员，文档上面说是候选字符码序列，这里的候选字符指的是什么？假设我用手写输入某个中文字符，那么这个候选字符是最后识别出来的所有可能的中文字符的码序列么？RecogResultStruct中的string呢？

文档中的shape是什么意思？（我理解的是用鼠标绘制的完一个字符就形成一个shape,形成一个shape的期间有多个stroke对应绘制该字符的每一笔画，对么？）

每个stroke和每个shape是什么区别?（我的猜测是stroke是(-1,-1)结尾的，shape是(-2,-2)结尾的，对吗)

在函数中，类型point_type*的参数分别有：RawData,PointBuf,SubPoint,RawPointBuf,是不是只是用户绘制形成的点数组这一个含义？如果不是能否说明一下它们的具体含义？
是否函数参数中的所有point_type *数组都是这样的格式：
 (x,y),(x,y),...,(-1,-1),(x,y),(x,y),...,(-1,-1),...,(-2,-2)
 如果是，那么一个数组中可否有多个(-2,-2)？

 另外，
 文档中的HWRE,AP,AI(在第?页出现过）,它们分别是什么？(其中我猜测的是HWRE代表unsigned char * ptr_global_data;AP就是应用程序,是否正确)
  文档中第7页中的LearnRecordStruct结构定义没有在头文件中找到,但是在头文件中的一个函数(GetLearnRecord)声明中发现了该结构的引用, 是否我在使用您提供的头文件接口的时候，不用考虑这个数据结构？如果不是希望能够提供该结构的信息。
*/
#ifndef PPHWR_GLOBAL_SETTING
#define PPHWR_GLOBAL_SETTING 1
#ifndef SHARP_18030
//-----------------------------
/*中文common*/
#define IN_5401_TYPE      1
#define IN_JIS1_TYPE      1

#define EUROPEAN_TYPE	  1

/*大小写字母*/
#define UPPER_ALPHA_TYPE  2
#define LOWER_ALPHA_TYPE  4

#define KATA_TYPE         8
#define HIRA_TYPE        16
#define NUMA_TYPE        32
#define SYMBOL_TYPE      64
#define GESTURE_TYPE    128

/*中文Rare*/
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
#define HIRA_TYPE           16384  // ¥­°²¦W
#define KATA_TYPE           32768 // ¤ù°²¦W
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
#define SHAPE_TYPE         0x0001  /* FULL_TYPE ==0 HALF_TYPE == 1 */
#define TURN_ON_HK         0x0002  /* open HK characters */
/*Traditional Only*/
#define TURN_ON_BIG_ONLY   0x0004  /* ¥u¥X²{ÁcÅé¦r */
/*Simplified Only*/
#define TURN_ON_GB_ONLY    0x0008  /* ¥u¥X²{Â²Åé¦r */
#define TURN_ON_BIG_AND_GB 0x000C  /* ¼gÁc±oÁc ¼gÂ²±oÂ² */
/*Full Set including Rare*/
#define TURN_ON_FULL_UNICODE 0x0010 /* ¼gÁc±oÁc ¼gÂ²±oÂ²  ¥þ¦r¶° §t¨u¥Î¦r */
/*used only for Simplified Version*/
#define TURN_ON_GBB_ONLY   0x0020  /* ¼gÁc±oÂ² only for ¤j³°ª©*/
#define TURN_ON_OCR        0x0040  /* turn on off-line recognition */

#define JPN_SHIFT_JIS	932
#define SIMPLIFIED_CHINESE	936
#define HANGEUL_TongHabHyung	949 //«nÁúWindows¨Ï¥Î
#define TRADITIONAL_CHINESE	950
#define HANGEUL_JOHAB	1361


#define BIG_ONLY_MODE 0
#define GB_ONLY_MODE 1
#define BIG_AND_GB_MODE 2
#define FULL_UNICODE_MODE 3
#define GBB_ONLY_MODE 4

/*每个Char的最大cand数目（候选字符数目？）*/
#define MAX_RADCOUNT 29
//-----------------------------

#define MAX_NO_POINT 2048
#define MAX_POINT_NO_IN_ONE_STROKE 256
#define CHAR_WIDTH_X 127
#define CHAR_WIDTH_Y 127
/*在Segmentation模式下面的shapes的最大允许数目*/
#define REAL_MAX_NO_CHAR	20

/*切换和请求当前AI记录更新模式*/
/*AI记录更新操作激活*/
#define AI_CLOSE 0
/*AI记录更新操作挂起*/
#define AI_OPEN  1

/*注意：
 * 1）ShapeMode用于控制返回的UNICODE的范围。如果AP没有关于它的任何方法，就把它设置为0（对于空类型）或者1（半类型?）
 * 2）为了改善吞吐量，AP可能在调用segment_one_stroke之前需要收集不止一个stroke；当然，结束标记(-2,-2)是必须的并且追加到最后的stroke的末尾
 * */

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
	/*segmentation调用的字符数,由REAL_MAX_NO_CHAR(即20)来进行限制。*/
   short counter; /* no of segmentation char in string MAX character is 10 */

   /*Segmentation结果
	*内容含义如下：
	{第一个字符的候选字符数目,第一个候选字符，第一个候选字符索引，第二个候选字符，第二个候选字符索引，...
	第二个字符的候选字符数目，第一个候选字符, 第一个候选字符索引, 第二个候选字符, 第二个候选字符索引,...
	...
	}
	*这里，如果候选字符数目<0，则为学习字符串。
	* */
   unsigned short string[1024]; /* no_final,code0,AI0,code1,AI1...,etc,
				   no_final,code0,AI0,code1,AI1...,etc,
                                   if no_final < 0 means learn string */


   /*这里GESTURE_TYPE为128*/
   unsigned short type;/* if count==1 and is gesture code then type=GESTURE_TYPE */

   /*每个字符的结尾(cutting)笔画,笔画索引从0开始,这里数组数20+1*/
   unsigned short split_stroke_index[REAL_MAX_NO_CHAR+1]; /* stroke index begin from 0 */
};
/*关于Stroke data的格式
 * (-1,-1)表示per_stroke的结尾，(-2,-2)是一个shape数据的结束标记。
 * 例如(x,y),(x,y),...,(-1,-1),(x,y),(x,y),...,(-1,-1),...,(-2,-2),
 * 没有stroke也不要忘记了(-1,-1).(-2,-2)必须作为RawData.
 * */




#ifdef STATIC_LINK
extern short WINAPI SetArea(unsigned char *ptr_global_data,
		unsigned long Area);

/*输出请求的内核对象大小
 * 注意：调用"HWRInitialize"之前调用这个函数获得合适的对象大小，分配内存空间*/
extern int WINAPI GetRAMSize(void);

/*输入：1）内核对象指针
 *		2）指向AI（??）记录引用的指针
 *		3）指向学习记录(??)引用的指针
 *		4）默认的HWRE数据库指针
 *输出：如果是0表示初始化成功，如果是-1表示出错需要检查指针。
 注意：
 1）使用GetRAMSize获得合适的内核对象大小，以分配对象的内存。
 2）如果AP(??)不使用AI进行学习，就把引用指针置空。
 3）如果HWRE没有使用"pre-loaded ROM数据库"，把DBAddress置空。
 4）这个函数在出了GetRAMSize之外的所有函数之前被调用。
 5）一旦这个函数返回了，内核对象的指针会被其他函数需要。
 * */
extern int WINAPI HWRInitialize(unsigned char * ptr_global_data,
  		     unsigned char *lpAIMMF,
		     unsigned char *lpLearnMMF,
                         unsigned char *DBAddress);

/*输入：内核对象指针
 * 输出：0代表释放成功，其他代表释放失败
 * 注意：在HWRE释放清理内存之前调用这个函数
 * */
extern int WINAPI HWRRelease(unsigned char * ptr_global_data);

//extern int WINAPI SetCandCount(unsigned char *ptr_hwre_obj,
//                        int CandCount);


/*作用?*/
extern struct point_type * WINAPI
       process_one_stroke(unsigned char * ptr_global_data,
                          struct point_type *PointBuf);

/*单个Shapes的，为每一个stroke调用。AP(??)必须为recognition进程保存PointBuf和返回的数据。
 * 输入：
 * 1）内核对象指针
 * 2）想要的recognition类型。
 * 3）想要的Shape Mode(返回DBCs或者ASCII字符用于英文字母，符号和数字)
 * 4）用户绘制的shape的所有stroke数据。
 * 输出：
 * 候选的数目，候选Recognition数组，Cost和Type和每个RecogResultStruct结构的候选组下标。
 * 注意：
 * 1）每个候选精确地映射到结构中的实体（string,cost,type,AI array）
 * 2）对于DBCs码，候选码应该将它的高比特和低比特位反置。对于ASCII码，它占据一个无符号短整型的大小，码将会放置在高比特，低比特被刷零。
 * 3）在shape数据的最后，结束标记(-2,-2)应该被AP(??)加上，以确保HWRE正常。例如:
	(,)....(-1,-1)(-2,-2).
 * 4）分组数据中总共的点的数目应该小于等于MAX_POINT_FOR_PER_SHAPE.
 * */
extern struct RecogResultStruct * WINAPI
       sub(unsigned char * ptr_global_data,
           short Type,
		   short ShapeMode,
		   struct point_type *SubPoint);

#ifdef ENABLE_SEGMENTATION
/*多Shapes的，为每个stroke调用，AP(??)不需要仅仅保存数据到PointBuf中。
 * 输入：
 * 1）内核对象指针
 * 2）想要的recognition类型
 * 3）用户的输入stroke数据。
 * 输出：没有输出。
 * 注意：
 * 1）这个函数不会返回任何减少的数据。这些数据保存在HWRE中。如果AP调用这个函数，它需要调用start_recognition来代替sub以获得正确的结果。
 * 2）分组数据中总共的点的数目应该小于等于MAX_POINT_IN_SCREEN.
 * */
extern void WINAPI segment_one_stroke(unsigned char * ptr_global_data,
                               short Type,
                               short ShapeMode,
                               struct point_type *PointBuf);

/*如果用户决定分割Result_Word_List中的字符，AP应该首先从PointBuf中收集所有的需要的strokes到RawData数组，然后调用这个函数。
 * 输入：
 * 1）内核对象指针
 * 2）想要的recognition类型
 * 3）期望的ShapeMode
 * 4）原始输入stroke的分组数据。
 * 输出：Segmentation Recognition Result结构
 * 注意：
 * 1）这个函数不应该在start_recognition之前被调用。它只能在用户想要分割输入数据的时候被调用。当用户这样做的时候，AP应该收集像RawData这样相应的stroke数据。
 * 2）如果RawData不能再被分割的时候，AP将会获得和以前一样的候选者.
 * */
extern struct SegmentResultStruct * WINAPI
   split_recognition(unsigned char * ptr_global_data,
                     short Type,short ShapeMode,
                     struct point_type *RawData);

/*当用户绘制完多个shapes的时候，AP将会调用这个函数来获得recognition的结果。不需要再准备Point Data了。
 * 输入：
 * 1）内核对象指针
 * 2）想要的recognition类型。
 * 3）期望的ShapeMode.
 * 输出：Segmentation Recognition Result结构
 * 注意：
 * 1）定义的SegmentResultStruct成员在上面已经列出了，需要引用它。
 * 2）HWRE使用内部的存储来保存stroke的数据，因此，AP不需要保存用户输入的数据。如果AP想要具有分割和合并函数，原来的输入数据应该被保存。
 * 3)如果AP想要使用合并函数，需要收集相应的strokes数据，并且用sub来执行合并函数。
 *
 * */
extern struct SegmentResultStruct * WINAPI
   start_recognition(unsigned char * ptr_global_data,
                     short Type,short ShapeMode);
#endif

/*使用不同的喜好的segmentation方向（horizontal=1,vertical=2)，以及不同的segmentation标准(dx>=20,逻辑距离)（这里的标准好像就是尺度??）
 * 输入:
 * 1）内核对象指针
 * 2）喜欢的分割方向
 * 3）分割的标准
 * 输出：没有输出
 * 注意：
 * 1）如果喜欢水平的分割，那么segmentation_switch=1;否则segmentation_switch=2。如果两个都喜欢，那么值为3。
 * 2）最小的标准是20。
 * 3）AP不应该调用这个函数，它将会影响HWRE的hit-ratio.
 * */
extern void WINAPI set_segmentation_mode(unsigned char * ptr_global_data,
                                  short segmentation_switch,
                                  short dx);
#ifdef AI_ON
/*当用户选择另外一个候选，这个候选有RRS.AI[index]==-1做为需要的候选，AP应该准备所有的这个shape的stroke数据，并且调用这个函数来建立一个新的AI记录。
 * 输入：
 * 1）内核对象指针
 * 2）DBC码（双字节字符），不需要反置它。
 * 3）码的类型
 * 4）用户输入数据
 * 输出：成功返回TRUE,失败返回FALSE。
 * 注意：始终使用原始的用户输入。
 * */
extern unsigned char WINAPI
   AI_Adjust(unsigned char * ptr_global_data,
             short nLearnCode, short Type,
             struct point_type *RawPointBuf);

/*如果原来需要的具有AI[index]!=-1的候选被忽略了，AP应该调用这个函数并把参数设为AIIndex(AI[index])，来调整这个AI记录。
 * 输入：
 * 1）内核对象指针
 * 2）和被替代的候选相关的AI index.
 * 输出：没有输出。
 * 注意：
 * 如果HWRE返回的最好的候选的AI index entry != -1,那么用户选择替代这个候选，AP应该调用这个函数来更正使用的AI记录引用。
 * */
extern void WINAPI VerifyAIHit(unsigned char * ptr_global_data,
                        int AIIndex);

/*如果一个具有AI[index]!=-1的候选被选为想要的候选，那么AP应该调用这个函数，参数设置为AIIndex(AI[index])来发起这个AI 记录。
 * 输入：
 * 1）内核对象指针
 * 2）用户选择候选的AI index entry（如果!=-1）
 * 输出：没有输出。
 * 注意：
 * 当用户选择第二个最好的候选（或者其他不是最好的）来作为最好的，AP将会调用这个函数来更新使用记录的AI记录引用。
 * */
extern void WINAPI SetAIHit(unsigned char * ptr_global_data,
                     int AIIndex);

/*决定AI更新切换
 * 输入：
 * 1）内核对象指针
 * 2）切换参数
 * 输出：没有输出。
 * 注意：
 * 如果AP选择关闭AI更新，那么AI字符仍然可以做为用户写的匹配。然而新的AI记录不会被建立，AI引用也不能被更新了。
 *
 * */
extern void WINAPI SetAIMode(unsigned char * ptr_global_data,
                      char pp);

/*请求获得当前AI更新的切换（值)
 * 输入：内核对象指针
 * 输出：当前的切换值
 * 注意：没有什么注意的。
 * */
extern char WINAPI GetAIMode(unsigned char * ptr_global_data);
#endif

#ifdef ENABLE_LEARNING
/*一个新的学习记录被建立。它将会被追加到已有学习记录的末端。因此DatabaseIndex经常表示当前学习记录的总数目
 * 输入：
 * 1）内核对象指针
 * 2）学习的字符串的长度
 * 3）学习的字符串
 * 4）stroke数据。
 * 输出：如果成功返回TRUE，如果失败返回FALSE.
 * 注意：point数据必须是Raw Data.
 * */
extern unsigned char WINAPI
              SetDBFromData(unsigned char * ptr_global_data,
                            int nLearnCode,
                            unsigned short * pLearnString,
                            struct point_type *point);

/*从Database中取得学习的记录
 *输入：
 *1）内核对象指针
 *2）存在的学习记录索引
 *输出：一个指向学习记录结构的指针。
 *注意：
 1）函数返回的常偶AP应该把结构拷贝。
 2）AP不应该修改数据库结构的内容。
 * */
extern struct LearnRecordStruct * WINAPI
       GetLearnRecord(unsigned char * ptr_global_data,
                      short nIndex);

/*取得学习记录的总数
 *输入：内核对象指针
 *输出：已有的学习记录的总数
 *注意：没有什么注意的
 * */
extern int WINAPI GetLearnCount(unsigned char * ptr_global_data);

/*从学习记录列表中移走一条单个的记录
 * 输入：
 * 1）内核对象指针
 * 2）一个已经存在的学习记录索引
 * 输出：成功返回TRUE,失败返回FALSE
 * 注意：
 * 如果之前AP没有备份这个记录，那么该记录会永久消失。
 * */
extern char WINAPI DeleteDatabase(unsigned char * ptr_global_data,
                           int DataIndex);

/*给定一个学习记录索引，把这个记录用一个新的记录替代
 * 输入：
 * 1）内核对象指针
 * 2）已有的学习记录索引
 * 3）新的代码的长度。
 * 4）新的代码字符串（无符号整数）
 * 输出：成功返回TRUE,失败返回FALSE。
 * 注意：使用这个函数，AP可以使用相同的shape直接改变学习记录中的学习代码.
 * */
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

/*单个Shapes的，为每一个stroke调用。AP(??)必须为recognition进程保存PointBuf和返回的数据。
 * 输入：
 * 1）内核对象指针
 * 2）想要的recognition类型。
 * 3）想要的Shape Mode(返回DBCs或者ASCII字符用于英文字母，符号和数字)
 * 4）用户绘制的shape的所有stroke数据。
 * 输出：
 * 候选的数目，候选Recognition数组，Cost和Type和每个RecogResultStruct结构的候选组下标。
 * 注意：
 * 1）每个候选精确地映射到结构中的实体（string,cost,type,AI array）
 * 2）对于DBCs码，候选码应该将它的高比特和低比特位反置。对于ASCII码，它占据一个无符号短整型的大小，码将会放置在高比特，低比特被刷零。
 * 3）在shape数据的最后，结束标记(-2,-2)应该被AP(??)加上，以确保HWRE正常。例如:
	(,)....(-1,-1)(-2,-2).
 * 4）分组数据中总共的点的数目应该小于等于MAX_POINT_FOR_PER_SHAPE.
 * */
struct RecogResultStruct * (WINAPI
       *sub)(unsigned char * ptr_global_data,
           short Type,
		   short ShapeMode,
		   struct point_type *SubPoint);

/*多Shapes的，为每个stroke调用，AP(??)不需要仅仅保存数据到PointBuf中。
 * 输入：
 * 1）内核对象指针
 * 2）想要的recognition类型
 * 3）用户的输入stroke数据。
 * 输出：没有输出。
 * 注意：
 * 1）这个函数不会返回任何减少的数据。这些数据保存在HWRE中。如果AP调用这个函数，它需要调用start_recognition来代替sub以获得正确的结果。
 * 2）分组数据中总共的点的数目应该小于等于MAX_POINT_IN_SCREEN.
 * */
void (WINAPI *segment_one_stroke)(unsigned char * ptr_global_data,
                               short Type,
                               short ShapeMode,
                               struct point_type *PointBuf);

/*如果用户决定分割Result_Word_List中的字符，AP应该首先从PointBuf中收集所有的需要的strokes到RawData数组，然后调用这个函数。
 * 输入：
 * 1）内核对象指针
 * 2）想要的recognition类型
 * 3）期望的ShapeMode
 * 4）原始输入stroke的分组数据。
 * 输出：Segmentation Recognition Result结构
 * 注意：
 * 1）这个函数不应该在start_recognition之前被调用。它只能在用户想要分割输入数据的时候被调用。当用户这样作的时候，AP应该收集想RawData这样相应的stroke数据。
 * 2）如果RawData不能再被分割的时候，AP将会获得和以前一样的候选者.
 * */
struct SegmentResultStruct * (WINAPI
   *split_recognition)(unsigned char * ptr_global_data,
                     short Type,short ShapeMode,
                     struct point_type *RawData);

/*当用户绘制完多个shapes的时候，AP将会调用这个函数来获得recognition的结果。不需要再准备Point Data了。
 * 输入：
 * 1）内核对象指针
 * 2）想要的recognition类型。
 * 3）期望的ShapeMode.
 * 输出：Segmentation Recognition Result结构
 * 注意：
 * 1）定义的SegmentResultStruct成员在上面已经列出了，需要引用它。
 * 2）HWRE使用内部的存储来保存stroke的数据，因此，AP不需要保存用户输入的数据。如果AP想要具有分割和合并函数，原来的输入数据应该被保存。
 * 3)如果AP想要使用合并函数，需要收集相应的strokes数据，并且用sub来执行合并函数。
 *
 * */
struct SegmentResultStruct * (WINAPI
   *start_recognition)(unsigned char * ptr_global_data,
                     short Type,short ShapeMode);

/*使用不同的喜好的segmentation方向（horizontal=1,vertical=2)，以及不同的segmentation标准(dx>=20,逻辑距离)（这里的标准好像就是尺度??）
 * 输入:
 * 1）内核对象指针
 * 2）喜欢的分割方向
 * 3）分割的标准
 * 输出：没有输出
 * 注意：
 * 1）如果喜欢水平的分割，那么segmentation_switch=1;否则segmentation_switch=2。如果两个都喜欢，那么值为3。
 * 2）最小的标准是20。
 * 3）AP不应该调用这个函数，它将会影响HWRE的hit-ratio.
 * */
void (WINAPI *set_segmentation_mode)(unsigned char * ptr_global_data,
                                  short segmentation_switch,
                                  short dx);

void  (WINAPI *set_writing_size)(unsigned char * ptr_global_data,short,short);

int (WINAPI *SetCandCount)(unsigned char * ptr_global_data,
                           int CandCount);


#ifdef AI_ON
/*当用户选择另外一个候选，这个候选有RRS.AI[index]==-1做为需要的候选，AP应该准备所有的这个shape的stroke数据，并且调用这个函数来建立一个新的AI记录。
 * 输入：
 * 1）内核对象指针
 * 2）DBC码（双字节字符），不需要反置它。
 * 3）码的类型
 * 4）用户输入数据
 * 输出：成功返回TRUE,失败返回FALSE。
 * 注意：始终使用原始的用户输入。
 * */
unsigned char (WINAPI
   *AI_Adjust)(unsigned char * ptr_global_data,
             short nLearnCode, short Type,
             struct point_type *RawPointBuf);

/*如果原来需要的具有AI[index]!=-1的候选被忽略了，AP应该调用这个函数并把参数设为AIIndex(AI[index])，来调整这个AI记录。
 * 输入：
 * 1）内核对象指针
 * 2）和被替代的候选相关的AI index.
 * 输出：没有输出。
 * 注意：
 * 如果HWRE返回的最好的候选的AI index entry != -1,那么用户选择替代这个候选，AP应该调用这个函数来更正使用的AI记录引用。
 * */
void (WINAPI *VerifyAIHit)(unsigned char * ptr_global_data,
                        int AIIndex);

/*如果一个具有AI[index]!=-1的候选被选为想要的候选，那么AP应该调用这个函数，参数设置为AIIndex(AI[index])来发起这个AI 记录。
 * 输入：
 * 1）内核对象指针
 * 2）用户选择候选的AI index entry（如果!=-1）
 * 输出：没有输出。
 * 注意：
 * 当用户选择第二个最好的候选（或者其他不是最好的）来作为最好的，AP将会调用这个函数来更新使用记录的AI记录引用。
 * */
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

