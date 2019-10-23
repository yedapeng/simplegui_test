#ifndef __INCLUDE_DEMO_RESOURCE_UTF8_H__
#define __INCLUDE_DEMO_RESOURCE_UTF8_H__

#if defined ( __CC_ARM )
	//#pragma	diag_suppress	177							// Disabled "declared but never referenced." warning.
#endif


/* Screen 1: Multiple lines text. */
/* Start screen scroll text. */
#define     DEMO_START_NOTICE           (\
"  ��ӭ����SimpleGUI��ʾ���̣�������������ʾGUI��ͼ��HMIģ�ͽ�����ʹ�÷���\
�Լ�����������ʾ����ʹ�ô���ģ����̲�������������ʽΪ115200/N/8/1��ÿ��\
�������ֽ�ģ��һ�μ��̶�����������ο�DemoActions.h�ļ���\n\
  ���Ϳո����(0x0020)��ʼ��ʾ��"\
)

/* Screen 2: List*/
/* Demo list title. */
#define     DEMO_LIST_TITLE             ("�����б�")
/* Enumed list item choice type. */
#define     DEMO_LIST_ITEM_NOTICE_TEXT  ("������Ϣ")
#define     DEMO_LIST_ITEM_NOTICE_TIME  ("ϵͳʱ��")
#define     DEMO_LIST_ITEM_ENUM_VALUE1  ("ö����1")
#define     DEMO_LIST_ITEM_ENUM_VALUE2  ("ö����2")
#define     DEMO_LIST_ITEM_ENUM_VALUE3  ("ö����3")


/* List items data.                      Sign   ListText                            List item type           List value                 Decimal point           Enumed text list    */
/*                                                                                                           init.  min.   max.         init.  min.   max.                          */
#define     DEMO_LIST_ITEM_0            {0,     "���б���",                       LIST_ITEM_NORMAL,		{0,     0,     0     },    {0,     0,     0     },  NULL}
#define     DEMO_LIST_ITEM_1			{1,     "ö�������б���",		            LIST_ITEM_ENUM,			{0,     0,     1     },    {0,     0,     0     },  s_arrszNoticeType}
#define     DEMO_LIST_ITEM_2            {2,     "�����б���",			            LIST_ITEM_DIGIT,		{0,     -50,   50    },    {0,     0,     3     },  NULL}
#define     DEMO_LIST_ITEM_3			{3,     "��С���������б���",               LIST_ITEM_DIGIT,		{1,     -50,   50    },    {2,     0,     5     },  NULL}
#define     DEMO_LIST_ITEM_4            {4,     "�������ֵļ��б���",             LIST_ITEM_NORMAL,		{0,     0,     0     },    {0,     0,     0     },  NULL}
#define     DEMO_LIST_ITEM_5            {5,     "�༭��",				            LIST_ITEM_NORMAL,		{0,     0,     0     },    {0,     0,     0     },  NULL}
#define     DEMO_LIST_ITEM_6			{6,     "ʵʱ����",				            LIST_ITEM_NORMAL,		{0,     0,     0     },    {0,     0,     0     },  NULL}
#define     DEMO_LIST_ITEM_7            {7,     "������Ŀ1",				        LIST_ITEM_NORMAL,		{0,     0,     0     },    {0,     0,     0     },  NULL}
#define     DEMO_LIST_ITEM_8            {8,     "������Ŀ2",				        LIST_ITEM_ENUM,			{0,     0,     2     },    {0,     0,     0     },  s_arrszEnumedValue}
#define     DEMO_LIST_ITEM_9			{9,     "������Ŀ3",				        LIST_ITEM_DIGIT,		{0,     -50,   50    },    {0,     0,     3     },  NULL}

/* Screen 3: Text notice box. */
/* List notice text format. */
#define     DEMO_LIST_NOTICE_TEXT_FMT   ("ѡ���б���%u.")

/* Screen 4: RTC notice box. */
#define     DEMO_RTC_NOTICE_TEXT_FMT    ("ϵͳʱ��\n%04u-%02u-%02u\n%02u:%02u:%02u")

/* Screen 5: Variable box. */
#define     DEMO_VARIABLE_BOX_TITLE     ("��ֵ/�ı��༭��ʾ")
#define     DEMO_VARIABLE_BOX_HELPER    ("TAB���л�����༭��\n���¼�ͷ������ֵ��\n���Ҽ�ͷ���������ַ���\n���ո��������")

/* Others */
#define     DEMO_TEST_TEXT              ("��������")

#endif // __INCLUDE_DEMO_RESOURCE_UTF8_H__
