#pragma once

#if defined(WINCE)
#if (_WIN32_WCE < 0x700)
#ifdef MCGS_617
#pragma comment(lib, "IMCDriver_617/imcCENet.lib")
#include "IMCDriver_617/imcnet.h"
#include "IMCDriver_617/ParamDef.h"
#else
#pragma comment(lib, "IMCDriver/imcCENet.lib")
#include "IMCDriver/imcnet.h"
#include "IMCDriver/ParamDef.h"
#endif
#else
#include "IMCDriver_CE7/IMCnet.h"
#include "IMCDriver_CE7/ParamDef.h"
#pragma comment(lib, "IMCDriver_CE7/imcCENet.lib")
#endif
#else
#pragma comment(lib, "drivers/imcnet.lib")
#include "drivers/imcnet.h"
#include "drivers/ParamDef.h"
#endif

#include "MyDef.h"
#include "IMCFun.h"
#include "MyEdit.h"


extern CString g_cmdStr[CMD_TOTAL];
extern CString g_AxisName[MAX_NAXIS];
extern int g_Naxis;
extern SYS_CFG g_cfg;
extern FACT_CFG g_factcfg;
extern TEST_VER_INFO g_verinfo;
extern FACT_POLAR g_polar;	
extern FACT_IOMAP_INFO g_iomap;
extern FACT_WARN *g_warn;
extern int g_warnNum;


#if defined(WINCE)
extern	BOOL g_isSipShow;//�Ƿ��Ѿ���ʾ���뷨
#endif
extern	BOOL g_isTestV;//�Ƿ������ð�
extern	BOOL g_isUseHWok;	//������Ƿ�ʹ������ȷ����ť����

extern CFont* MyGetFonts(int height, WCHAR *name, int width);
extern void StartTimes();
extern DWORD GetTimes();
extern LONGLONG GetTimems();

#if !defined(WINCE)
extern	CString GetMyMFCDir();
#endif
extern BOOL IsFileDirExist(CString dir);
extern void DoEvents();

extern	BOOL SaveCfg();
extern	BOOL SaveFactCfg();
extern	BOOL SaveFactPolar();
extern	BOOL SaveIOMap();
extern	BOOL SaveWarn();
extern	BOOL ReadCfg();
extern	BOOL ReadFactCfg();
extern	BOOL ReadFactPolar();
extern	BOOL ReadIOMap();
extern	BOOL ReadWarn();
extern	BOOL SaveCurFile(const WCHAR* path);
extern	BOOL ReadCurFile(WCHAR* path);


extern SYSTEM_STATUS_OBJECT SysStatusObj;




