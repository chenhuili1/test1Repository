// IMC_GenericDlg.h : 头文件
//

#pragma once

#include "MainDlg.h"
#include "FactoryDlg.h"
#include "SysDlg.h"
#include "SysInfo.h"
#include "FindHome.h"
#include "MyFileMg.h"
#include "MyDebug.h"

enum{
	JM_MAIN,
	JM_SYS,
	JM_FACT,
	JM_HOME,
	JM_SINFO,
	JM_FILE,
	JM_DEBUG,
};


// CIMC_GenericDlg 对话框
class CIMC_GenericDlg : public CDialog
{
// 构造
public:
	CIMC_GenericDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CIMC_GenericDlg();

	void gotoPos_singleAxis(long axis,long velType,WORD velRatio,double pos);
	void gotoPos_MultiAxis(char cmdType,double velRatio,double X,double Y,double Z);



	

	BOOL m_bChange;	//记录程序是否被修改
	CMainDlg m_maindlg;
	CSysDlg m_SysDlg;
	CFactoryDlg m_FactoryDlg;
	CFindHome m_homeDlg;
	CSysInfo m_sinfoDlg;
	CMyFileMg m_fileDlg;
	CMyDebug m_debugDlg;

	CIMCFun m_imc;
	long m_encp[MAX_NAXIS];
	WORD m_axis[MAX_NAXIS];	
	WORD m_error[MAX_NAXIS];	
	short m_key[KEY_NUM];
	short m_emstopkey;	//急停开关状态值

	BOOL m_errRunT;	//错误线程运行


	void StartLogo();
	void ShowDlg(int dlg);
	BOOL IsPasswordOK(int type);
	BOOL DebugVersion();
	void StartOpenTimer();
	

	void GetCurEncp(long *encp);
	void EmstopInput();
	void ErrorShow();
	WORD *GetErrorVal();

	BOOL m_threadRun;	//线程是否正在运行
	BOOL m_threadPause;	//线程是否暂停
	BOOL m_threadStop;	//控制线程停止
	BOOL m_threadStep;	//
	BOOL m_threadReset;	//控制线程复位，即立即退出线程
	BOOL m_EmstopRun;	//急停线程是否运行
	BOOL m_machinMode;	//单步，单次，循环
	DWORD m_time;	//单件加工计时
	DWORD m_timeTotal;	//加工计时
	DWORD m_matchinNum;

	BOOL IsPause();
	BOOL GetThreadSt();
	void StartMatchin(BOOL mode);
	void PauseMatchin();
	void StopMatchin();
	void ResetMatchin();
	void EmstopMatchin();
	void RedLedOn();
	void RedLedOff();
	void YellowLedOn();
	void YellowLedOff();
	void GreedLedOn();
	void GreedLedOff();
	void SetCurLine(int line);
	int GetCurLine();
	void SetNextLine(int line);
	int GetNextLine();
	BOOL RunAll(PROGRAM_DATA *pdata);
	BOOL RunEmstop(PROGRAM_DATA *pdata);
	BOOL WaitAllOver();
		
// 对话框数据
	enum { IDD = IDD_IMC_GENERIC_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;
	CBrush m_brush;
	BOOL m_isInit;
	CFont * g_fn14;	//字体
	CTime m_sysTime;//系统时间
//	CRect m_mainRC;
	int m_curdlg;
	int m_curLine;	//当前程序执行的行
	int m_nextLine;	//执行的下一行
	short m_count;


	void MoveDlg();
	BOOL IsFileDirExist(CString dir);
	BOOL CreateSysDir();

	int GetUseFIFO(PROGRAM_DATA *pdata);
	BOOL DelayFun(PROGRAM_DATA *pdata);
	BOOL LoopFun(PROGRAM_DATA *pdata);
	BOOL LoopFun_em(PROGRAM_DATA *pdata);
	BOOL LineMulFun(PROGRAM_DATA *pdata);
	BOOL isInterP();
	BOOL ArcFun(PROGRAM_DATA *pdata);
	BOOL OutputFun(PROGRAM_DATA *pdata);
	BOOL InputFun(PROGRAM_DATA *pdata);
	BOOL GohomeFun(PROGRAM_DATA *pdata);
	BOOL WhirlFun(PROGRAM_DATA *pdata);
	BOOL VelFun(PROGRAM_DATA *pdata);
	BOOL PosFun(PROGRAM_DATA *pdata);
	BOOL WaitFun(PROGRAM_DATA *pdata);

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
