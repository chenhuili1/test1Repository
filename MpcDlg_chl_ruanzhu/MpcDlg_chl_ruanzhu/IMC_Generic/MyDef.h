#pragma once

#define WM_MY_FACT_LOGIN  (WM_USER+1)
#define WM_MY_STATUS_INFO	WM_USER+2	//
#define WM_MY_PROGRAM_SHOW	WM_USER+3
#define WM_MY_WARNEDIT_SHOW	WM_USER+4


#define PROCESS_TIME
#define MAX_NAXIS	16	//最大轴数
//定时器id
enum {
	TIMER_DEV_OPEN = 1,
	TIMER_GET_ENCP,
	TIMER_FHOME_ENCP,
	TIMER_MAIN_ENCP,
	TIMER_KEY_INPUT,
	TIMER_MACHIN_TIMING,
	TIMER_MANUAL_TIMING,
	TIMER_SYSTIME,
	TIMER_FILE_MG,
	TIMER_PG_HANDWHEEL,
	TIMER_DEBUG,
};
#define SHOW_ENCP_TIME		40
#define GET_KEY_INPUT_TIME		40
//IO映射
typedef struct _IO_MAP_{
	WORD loc;	//寄存器地址
	BYTE bit;	//第几位
	BYTE axis;	//轴号
}IO_MAP;

enum{
	MAP_X = 0,
	MAP_Y,
	MAP_Z,
	MAP_A,
	MAP_B,
	MAP_C,
	MAP_D,
	MAP_E,
	MAP_F,
	MAP_G,
	MAP_H,
	MAP_I,
	MAP_J,
	MAP_K,
	MAP_L,
	MAP_M
};
#define INPUT_NUM	32
#define OUTPUT_NUM	32
#define LED_NUM		3
#define KEY_NUM		4
//#define HANFWHEEL_NUM		10



#define PASSWORD_LEN	8		//密码数组大小
#define PASSWORD_USE_LEN	6	//密码长度
enum{
	MY_PW_NULL,
	MY_PW_FACT,
	MY_PW_LOGIN,
	MY_PW_EDIT,
	MY_PW_SYS,
	MY_PW_RUN,
};


#define IMC_DEST_FAC(a)	g_factcfg.distFac[a]	//位移因子(1个位移单位等于多少脉冲
#define IMC_TIME_FAC(a)	g_factcfg.timeFac[a]	//时间因子
#define IMC_SPEED_FAC(a)	(65536 * IMC_DEST_FAC(a)/IMC_TIME_FAC(a))		//速度因子
#define IMC_ACCEL_FAC(a)	(65536 * IMC_DEST_FAC(a)/IMC_TIME_FAC(a)/IMC_TIME_FAC(a))		//速度因子
#define IMC_ENCP_SHOW(encp, a) (double)(1.0*encp[g_factcfg.g_mapAxis[a]]/g_factcfg.distFac[a])

#if defined(WINCE)
#define WINCE_SD_DIR		_T("\\USB HardDisk")
#define WINCE_SD_PATH		_T("\\USB HardDisk\\")
#define SAV_FILE_PATH	_T("\\HardDisk\\IMCG\\save\\")
#define SYS_FILE_DIR	_T("\\HardDisk\\IMCG")
#define CFG_FILE_DIR	_T("\\HardDisk\\IMCG\\data")
#define SAV_FILE_DIR	_T("\\HardDisk\\IMCG\\save")
#define CFG_FILE_NAME	_T("\\HardDisk\\IMCG\\data\\d1.dat")
#define FACT_CFG_FILE_NAME	_T("\\HardDisk\\IMCG\\data\\d2.dat")
#define USE_FILE_NAME	_T("\\HardDisk\\IMCG\\data\\d3.dat")
#define FACT_POLAR_FILE_NAME	_T("\\HardDisk\\IMCG\\data\\d4.dat")
#define IOMAP_FILE_NAME	_T("\\HardDisk\\IMCG\\data\\d5.dat")	//IO映射文件
#define WARN_FILE_NAME	_T("\\HardDisk\\IMCG\\data\\d6.dat")	//警告文件
#define INI_FILE_NAME	_T("\\HardDisk\\IMCG\\data\\cfg.ini")
#define SAV_FILE_RESET	_T("\\HardDisk\\IMCG\\save\\reset")
#define SAV_FILE_EMSTOP	_T("\\HardDisk\\IMCG\\save\\emstop")
#else
#define WINCE_SD_DIR		_T("\\USB HardDisk")
#define WINCE_SD_PATH		_T("\\USB HardDisk\\")
//#define SAV_FILE_PATH	_T("\\HardDisk\\IMCG\\save\\")
//#define SYS_FILE_DIR	_T("\\HardDisk\\IMCG")
#define CFG_FILE_DIR	_T("\\data")
#define SAV_FILE_DIR	_T("\\save")
#define CFG_FILE_NAME	_T("\\data\\d1.dat")
#define FACT_CFG_FILE_NAME	_T("\\data\\d2.dat")
#define USE_FILE_NAME	_T("\\data\\d3.dat")
#define FACT_POLAR_FILE_NAME	_T("\\data\\d4.dat")
#define IOMAP_FILE_NAME	_T("\\data\\d5.dat")	//IO映射文件
#define WARN_FILE_NAME	_T("\\data\\d6.dat")	//警告文件
#define INI_FILE_NAME	_T("\\data\\cfg.ini")
#define SAV_FILE_RESET	_T("\\save\\reset")
#define SAV_FILE_EMSTOP	_T("\\save\\emstop")
#endif

#define SEACH_FILE_EXP	_T("*.sgc")
#define FILE_EXP	_T(".sgc")
//字符串格式化
#define STR_FMT_6	_T("%06.02f")
#define STR_FMT_7	_T("%07.02f")
#define STR_FMT_d	_T("%d")

#define FACT_INFO_LEN	64
//厂家设置信息
typedef struct FACT_CFG_{
	WORD Naxis;			//控制卡控制轴数（g_mapAxis有效数据个数）
/*	IO_MAP mapI[INPUT_NUM];		//IO输入映射
	IO_MAP mapO[OUTPUT_NUM];	//IO输出映射
	IO_MAP mapLed[LED_NUM];			//灯映射
	IO_MAP mapKey[KEY_NUM];			//按键映射
	IO_MAP mapHW[MAX_NAXIS+4];			//手轮映射*/
	short g_mapAxis[MAX_NAXIS];	//轴映射,在运动控制时使用
	double distFac[MAX_NAXIS];
	long timeFac[MAX_NAXIS];
	WCHAR Unit[MAX_NAXIS][8];		//各轴的位移单位
	WCHAR PWfact[PASSWORD_LEN];		//厂家设置密码
	WORD steptime[MAX_NAXIS];	//脉冲宽度
	BYTE encpctr[MAX_NAXIS];	//使用内部还是外部反馈
	BYTE Alm[MAX_NAXIS];
//	BYTE stopin;	//急停按钮极限
	double encpfac[MAX_NAXIS];
	WCHAR sysName[FACT_INFO_LEN];
	WCHAR factName[FACT_INFO_LEN];
	WCHAR web[FACT_INFO_LEN];
	WCHAR phone[FACT_INFO_LEN];
	WCHAR address[FACT_INFO_LEN];
}FACT_CFG;


//IO映射
typedef struct _FACT_IOMAP_INFO_tag{
	IO_MAP mapI[INPUT_NUM];		//IO输入映射
	IO_MAP mapO[OUTPUT_NUM];	//IO输出映射
	IO_MAP mapLed[LED_NUM];			//灯映射
	IO_MAP mapKey[KEY_NUM];			//按键映射
	IO_MAP mapHW[MAX_NAXIS+4];		//手轮映射
	IO_MAP mapJogBnZ[MAX_NAXIS];		//点动按钮
	IO_MAP mapJogBnF[MAX_NAXIS];		//点动按钮
}FACT_IOMAP_INFO;

//输入端口极性
typedef struct _FACT_POLAR_tag{
	BYTE gin[INPUT_NUM];
	BYTE aioP[MAX_NAXIS];	//正限位
	BYTE aioN[MAX_NAXIS];	//负限位
	BYTE stopin;			//急停
}FACT_POLAR;

typedef struct _FACT_WARN_tag{
	WCHAR name[8];
	WCHAR warn[256];
}FACT_WARN;

//系统设置信息
typedef struct SYS_CFG_{
	double workVel[MAX_NAXIS];
	double fastVel[MAX_NAXIS];
	double jogVel[MAX_NAXIS];
	double locusVel;
	double locusFastVel;
	double locusAcc;
	double accel[MAX_NAXIS];
	double decel[MAX_NAXIS];
	WCHAR PWlogin[PASSWORD_LEN];	//登陆密码
	WCHAR PWEdit[PASSWORD_LEN];		//编辑密码
	WCHAR PWSys[PASSWORD_LEN];		//系统设置密码
	WCHAR PWRun[PASSWORD_LEN];		//启动密码
	WORD NetSel;
	WORD devID;
	CLSID	SipID;	//输入法
	WORD isAutoAddCMD;				//新指令编辑完成后是否自动增加指令
	WORD coordmode;					//坐标系选择
	double WorkCoord[MAX_NAXIS];	//工件坐标系零点偏移值
	short homeAxis[MAX_NAXIS];		//回零轴
	char  homeDir[MAX_NAXIS];		//回零方向
	char  homeSort[MAX_NAXIS];		//回零顺序
	double homeVel[MAX_NAXIS];		//回零速度
	WORD smooth[MAX_NAXIS];
	DWORD machinSel;	//默认加工选择
}SYS_CFG;

#define MOVE_HOMED_VEL	65536
//密码
typedef struct _SYS_PW_{
	WCHAR pw[8];
}SYS_PW;

//指令类型
enum CMD_TYPE{
	CMD_NULL	= 0,
	CMD_LINKAGE,//多轴联动
	CMD_ARC,	//圆弧
	CMD_OUTPUT,	//输出
	CMD_INPUT,	//输入
	CMD_GOHOME,	//回零
	CMD_GHWHIRL,	//回零
	CMD_VEL,	//连续匀速运动
	CMD_POS,	//点到点运动
	CMD_WAIT,	//等待（等待插补运动完成或者点到点运动结束）
	CMD_LOOP,	//循环开始
	CMD_WEND,	//循环结束
	CMD_DELAY,	//延时
	CMD_JUMP,	//跳转
	CMD_END,	//程序结束
	CMD_TOTAL
};

enum{
	KEY_RUN,
	KEY_PAUSE,
	KEY_EMSTOP,
	KEY_RESET
};
enum{
	LED_RED,
	LED_GREED,
	LED_YELLOW
};

#define LED_ON	0	//开灯
#define LED_OFF	1	//关灯

#define ARC_DIR_S	0	//顺时针
#define ARC_DIR_N	1	//逆时针

#define IOVAL_OPEN	0	//输出IO列表框选择开
#define IOVAL_CLOSE	1	//输出IO列表框选择关

#define SW_OUTPUT_ON	1	//输出IO开
#define SW_OUTPUT_OFF	0	//输出IO关

#define SW_INPUT_OPEN		1	//输入IO断开
#define SW_INPUT_CLOSE		0	//输入IO联通

#define CHANGE_DATA_0	
typedef struct _PROGRAM_DATA_{
	int size;	//此结构体的大小，
	int id;
	CMD_TYPE type;	//主指令类型
	int subType;	//子类型
	//
	DWORD delay;		//延时时间，单位毫秒

	PVOID LinePtr;	//记录行号所在数据指针，以防增加删除后行号变化,重新加载的时候需要根据jumpLine重新赋值
	DWORD jumpLine;	//跳转的行号，删除或插入的时候根据LinePtr的值重新计算
	DWORD loopNum;	//循环次数

	DWORD posBit;	//联动直线插补的有效轴号，置1表示轴参与联动
	double pos[MAX_NAXIS];//联动的位置信息,或者pos[0]为点到点的位置信息
	long vel;		//轨迹速度, 0:自动速度  1,快移速度, 如果是连续速度模式，则为速度
	DWORD arcBit;	//圆弧插补的选择的轴号，置1表示轴参与圆弧，(arcBit & posBit)不能等于非零
	double arc[6];	//圆弧上的点和终点坐标
	double center[2];	//圆心
	long dir;
	long axis;		//连续运动的轴号
	short isWT;		//点到点运动是否等待运动停止,（用来记录旋转轴回零等待了）

#ifdef CHANGE_DATA_0
	BYTE OutputVal;	//IO输出,高位为IO，低位为输出值
	BYTE OutputBit;	//IO输出,高位为IO，低位为输出值
#else
	WORD Output;	//IO输出,高位为IO，低位为输出值
#endif

#ifdef CHANGE_DATA_0
	BYTE InputVal;		//IO输入,高位为IO，低位为输入值
	BYTE InputBit;		//IO输入,高位为IO，低位为输入值
#else
	WORD Input;		//IO输入,高位为IO，低位为输入值
#endif
	WORD timeout;	//输入判断的超时时间
	WORD InSel;		//超时处理选择，高位为是否开灯报警，低位为动作选择
//	BYTE InSel;		//超时处理选择，高位为是否开灯报警，低位为动作选择
//	BYTE IsWarn;		//超时处理选择，高位为是否开灯报警，低位为动作选择


	WORD homeMode;	//回零模式， 0，同时回零， 1，按顺序回零
	DWORD homeBit;	//置1表示需要回零的轴，
	BYTE homeSort[MAX_NAXIS];//回零顺序，

	WORD WTbit;	//0，等待插补停止 ；1，等待点到点运动停止
	WORD velRatio;	//进给倍率
}PROGRAM_DATA;

typedef struct _JUMP_REC_{
	int line;			//有跳转的行，记录的是索引，
	int jumpLine;		//跳转到的行,记录的是行号，与索引相差1
	PROGRAM_DATA *pdata;//有跳转的行数据
	PROGRAM_DATA *pjdata;//跳转到的行数据
	struct _JUMP_REC_ *next;
}JUMP_REC;


typedef struct _File_HEAD_{
	char str[4];
	long version;
	int size;	//每个PROGRAM_DATA结构体的大小
	int cnt;
}File_HEAD;

#define FILE_VERSION	1
#define INIT_FILE_HEAD(head, ver) \
{\
	head.str[0] = 'S';	\
	head.str[1] = 'G';	\
	head.str[2] = 'C';	\
	head.str[3] = 0;	\
	head.version = ver;	\
}	

#define IsSysFile(head)	\
	((head.str[0] == 'S') && (head.str[1] == 'G') && (head.str[2] == 'C') && (head.str[3] == 0))


//#define TRY_VERSION		//测试版本控制开关
//测试版本信息
typedef struct _TEST_VER_INFO_{
	char isTest;	//是否是测试版本； 0：正式版， 1：测试版1， 2：测试版2； 大于零表示使用序列号的算法不同
	char licenseLen;	//license长度
	__int64 starttime;//开始时间，系统每次启动时修改这个时间
	__int64 endtime;	//结束时间
	char lcSN[32];		//license序列号
	char lc[32];		//license
}TEST_VER_INFO;


typedef struct 
{	
		long 	ActPos_OuterEncoder[8];//编码器的实际位置

	
}SYSTEM_STATUS_OBJECT;





