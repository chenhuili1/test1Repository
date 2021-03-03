#pragma once

#define WM_MY_FACT_LOGIN  (WM_USER+1)
#define WM_MY_STATUS_INFO	WM_USER+2	//
#define WM_MY_PROGRAM_SHOW	WM_USER+3
#define WM_MY_WARNEDIT_SHOW	WM_USER+4


#define PROCESS_TIME
#define MAX_NAXIS	16	//�������
//��ʱ��id
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
//IOӳ��
typedef struct _IO_MAP_{
	WORD loc;	//�Ĵ�����ַ
	BYTE bit;	//�ڼ�λ
	BYTE axis;	//���
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



#define PASSWORD_LEN	8		//���������С
#define PASSWORD_USE_LEN	6	//���볤��
enum{
	MY_PW_NULL,
	MY_PW_FACT,
	MY_PW_LOGIN,
	MY_PW_EDIT,
	MY_PW_SYS,
	MY_PW_RUN,
};


#define IMC_DEST_FAC(a)	g_factcfg.distFac[a]	//λ������(1��λ�Ƶ�λ���ڶ�������
#define IMC_TIME_FAC(a)	g_factcfg.timeFac[a]	//ʱ������
#define IMC_SPEED_FAC(a)	(65536 * IMC_DEST_FAC(a)/IMC_TIME_FAC(a))		//�ٶ�����
#define IMC_ACCEL_FAC(a)	(65536 * IMC_DEST_FAC(a)/IMC_TIME_FAC(a)/IMC_TIME_FAC(a))		//�ٶ�����
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
#define IOMAP_FILE_NAME	_T("\\HardDisk\\IMCG\\data\\d5.dat")	//IOӳ���ļ�
#define WARN_FILE_NAME	_T("\\HardDisk\\IMCG\\data\\d6.dat")	//�����ļ�
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
#define IOMAP_FILE_NAME	_T("\\data\\d5.dat")	//IOӳ���ļ�
#define WARN_FILE_NAME	_T("\\data\\d6.dat")	//�����ļ�
#define INI_FILE_NAME	_T("\\data\\cfg.ini")
#define SAV_FILE_RESET	_T("\\save\\reset")
#define SAV_FILE_EMSTOP	_T("\\save\\emstop")
#endif

#define SEACH_FILE_EXP	_T("*.sgc")
#define FILE_EXP	_T(".sgc")
//�ַ�����ʽ��
#define STR_FMT_6	_T("%06.02f")
#define STR_FMT_7	_T("%07.02f")
#define STR_FMT_d	_T("%d")

#define FACT_INFO_LEN	64
//����������Ϣ
typedef struct FACT_CFG_{
	WORD Naxis;			//���ƿ�����������g_mapAxis��Ч���ݸ�����
/*	IO_MAP mapI[INPUT_NUM];		//IO����ӳ��
	IO_MAP mapO[OUTPUT_NUM];	//IO���ӳ��
	IO_MAP mapLed[LED_NUM];			//��ӳ��
	IO_MAP mapKey[KEY_NUM];			//����ӳ��
	IO_MAP mapHW[MAX_NAXIS+4];			//����ӳ��*/
	short g_mapAxis[MAX_NAXIS];	//��ӳ��,���˶�����ʱʹ��
	double distFac[MAX_NAXIS];
	long timeFac[MAX_NAXIS];
	WCHAR Unit[MAX_NAXIS][8];		//�����λ�Ƶ�λ
	WCHAR PWfact[PASSWORD_LEN];		//������������
	WORD steptime[MAX_NAXIS];	//������
	BYTE encpctr[MAX_NAXIS];	//ʹ���ڲ������ⲿ����
	BYTE Alm[MAX_NAXIS];
//	BYTE stopin;	//��ͣ��ť����
	double encpfac[MAX_NAXIS];
	WCHAR sysName[FACT_INFO_LEN];
	WCHAR factName[FACT_INFO_LEN];
	WCHAR web[FACT_INFO_LEN];
	WCHAR phone[FACT_INFO_LEN];
	WCHAR address[FACT_INFO_LEN];
}FACT_CFG;


//IOӳ��
typedef struct _FACT_IOMAP_INFO_tag{
	IO_MAP mapI[INPUT_NUM];		//IO����ӳ��
	IO_MAP mapO[OUTPUT_NUM];	//IO���ӳ��
	IO_MAP mapLed[LED_NUM];			//��ӳ��
	IO_MAP mapKey[KEY_NUM];			//����ӳ��
	IO_MAP mapHW[MAX_NAXIS+4];		//����ӳ��
	IO_MAP mapJogBnZ[MAX_NAXIS];		//�㶯��ť
	IO_MAP mapJogBnF[MAX_NAXIS];		//�㶯��ť
}FACT_IOMAP_INFO;

//����˿ڼ���
typedef struct _FACT_POLAR_tag{
	BYTE gin[INPUT_NUM];
	BYTE aioP[MAX_NAXIS];	//����λ
	BYTE aioN[MAX_NAXIS];	//����λ
	BYTE stopin;			//��ͣ
}FACT_POLAR;

typedef struct _FACT_WARN_tag{
	WCHAR name[8];
	WCHAR warn[256];
}FACT_WARN;

//ϵͳ������Ϣ
typedef struct SYS_CFG_{
	double workVel[MAX_NAXIS];
	double fastVel[MAX_NAXIS];
	double jogVel[MAX_NAXIS];
	double locusVel;
	double locusFastVel;
	double locusAcc;
	double accel[MAX_NAXIS];
	double decel[MAX_NAXIS];
	WCHAR PWlogin[PASSWORD_LEN];	//��½����
	WCHAR PWEdit[PASSWORD_LEN];		//�༭����
	WCHAR PWSys[PASSWORD_LEN];		//ϵͳ��������
	WCHAR PWRun[PASSWORD_LEN];		//��������
	WORD NetSel;
	WORD devID;
	CLSID	SipID;	//���뷨
	WORD isAutoAddCMD;				//��ָ��༭��ɺ��Ƿ��Զ�����ָ��
	WORD coordmode;					//����ϵѡ��
	double WorkCoord[MAX_NAXIS];	//��������ϵ���ƫ��ֵ
	short homeAxis[MAX_NAXIS];		//������
	char  homeDir[MAX_NAXIS];		//���㷽��
	char  homeSort[MAX_NAXIS];		//����˳��
	double homeVel[MAX_NAXIS];		//�����ٶ�
	WORD smooth[MAX_NAXIS];
	DWORD machinSel;	//Ĭ�ϼӹ�ѡ��
}SYS_CFG;

#define MOVE_HOMED_VEL	65536
//����
typedef struct _SYS_PW_{
	WCHAR pw[8];
}SYS_PW;

//ָ������
enum CMD_TYPE{
	CMD_NULL	= 0,
	CMD_LINKAGE,//��������
	CMD_ARC,	//Բ��
	CMD_OUTPUT,	//���
	CMD_INPUT,	//����
	CMD_GOHOME,	//����
	CMD_GHWHIRL,	//����
	CMD_VEL,	//���������˶�
	CMD_POS,	//�㵽���˶�
	CMD_WAIT,	//�ȴ����ȴ��岹�˶���ɻ��ߵ㵽���˶�������
	CMD_LOOP,	//ѭ����ʼ
	CMD_WEND,	//ѭ������
	CMD_DELAY,	//��ʱ
	CMD_JUMP,	//��ת
	CMD_END,	//�������
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

#define LED_ON	0	//����
#define LED_OFF	1	//�ص�

#define ARC_DIR_S	0	//˳ʱ��
#define ARC_DIR_N	1	//��ʱ��

#define IOVAL_OPEN	0	//���IO�б��ѡ��
#define IOVAL_CLOSE	1	//���IO�б��ѡ���

#define SW_OUTPUT_ON	1	//���IO��
#define SW_OUTPUT_OFF	0	//���IO��

#define SW_INPUT_OPEN		1	//����IO�Ͽ�
#define SW_INPUT_CLOSE		0	//����IO��ͨ

#define CHANGE_DATA_0	
typedef struct _PROGRAM_DATA_{
	int size;	//�˽ṹ��Ĵ�С��
	int id;
	CMD_TYPE type;	//��ָ������
	int subType;	//������
	//
	DWORD delay;		//��ʱʱ�䣬��λ����

	PVOID LinePtr;	//��¼�к���������ָ�룬�Է�����ɾ�����кű仯,���¼��ص�ʱ����Ҫ����jumpLine���¸�ֵ
	DWORD jumpLine;	//��ת���кţ�ɾ��������ʱ�����LinePtr��ֵ���¼���
	DWORD loopNum;	//ѭ������

	DWORD posBit;	//����ֱ�߲岹����Ч��ţ���1��ʾ���������
	double pos[MAX_NAXIS];//������λ����Ϣ,����pos[0]Ϊ�㵽���λ����Ϣ
	long vel;		//�켣�ٶ�, 0:�Զ��ٶ�  1,�����ٶ�, ����������ٶ�ģʽ����Ϊ�ٶ�
	DWORD arcBit;	//Բ���岹��ѡ�����ţ���1��ʾ�����Բ����(arcBit & posBit)���ܵ��ڷ���
	double arc[6];	//Բ���ϵĵ���յ�����
	double center[2];	//Բ��
	long dir;
	long axis;		//�����˶������
	short isWT;		//�㵽���˶��Ƿ�ȴ��˶�ֹͣ,��������¼��ת�����ȴ��ˣ�

#ifdef CHANGE_DATA_0
	BYTE OutputVal;	//IO���,��λΪIO����λΪ���ֵ
	BYTE OutputBit;	//IO���,��λΪIO����λΪ���ֵ
#else
	WORD Output;	//IO���,��λΪIO����λΪ���ֵ
#endif

#ifdef CHANGE_DATA_0
	BYTE InputVal;		//IO����,��λΪIO����λΪ����ֵ
	BYTE InputBit;		//IO����,��λΪIO����λΪ����ֵ
#else
	WORD Input;		//IO����,��λΪIO����λΪ����ֵ
#endif
	WORD timeout;	//�����жϵĳ�ʱʱ��
	WORD InSel;		//��ʱ����ѡ�񣬸�λΪ�Ƿ񿪵Ʊ�������λΪ����ѡ��
//	BYTE InSel;		//��ʱ����ѡ�񣬸�λΪ�Ƿ񿪵Ʊ�������λΪ����ѡ��
//	BYTE IsWarn;		//��ʱ����ѡ�񣬸�λΪ�Ƿ񿪵Ʊ�������λΪ����ѡ��


	WORD homeMode;	//����ģʽ�� 0��ͬʱ���㣬 1����˳�����
	DWORD homeBit;	//��1��ʾ��Ҫ������ᣬ
	BYTE homeSort[MAX_NAXIS];//����˳��

	WORD WTbit;	//0���ȴ��岹ֹͣ ��1���ȴ��㵽���˶�ֹͣ
	WORD velRatio;	//��������
}PROGRAM_DATA;

typedef struct _JUMP_REC_{
	int line;			//����ת���У���¼����������
	int jumpLine;		//��ת������,��¼�����кţ����������1
	PROGRAM_DATA *pdata;//����ת��������
	PROGRAM_DATA *pjdata;//��ת����������
	struct _JUMP_REC_ *next;
}JUMP_REC;


typedef struct _File_HEAD_{
	char str[4];
	long version;
	int size;	//ÿ��PROGRAM_DATA�ṹ��Ĵ�С
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


//#define TRY_VERSION		//���԰汾���ƿ���
//���԰汾��Ϣ
typedef struct _TEST_VER_INFO_{
	char isTest;	//�Ƿ��ǲ��԰汾�� 0����ʽ�棬 1�����԰�1�� 2�����԰�2�� �������ʾʹ�����кŵ��㷨��ͬ
	char licenseLen;	//license����
	__int64 starttime;//��ʼʱ�䣬ϵͳÿ������ʱ�޸����ʱ��
	__int64 endtime;	//����ʱ��
	char lcSN[32];		//license���к�
	char lc[32];		//license
}TEST_VER_INFO;


typedef struct 
{	
		long 	ActPos_OuterEncoder[8];//��������ʵ��λ��

	
}SYSTEM_STATUS_OBJECT;





