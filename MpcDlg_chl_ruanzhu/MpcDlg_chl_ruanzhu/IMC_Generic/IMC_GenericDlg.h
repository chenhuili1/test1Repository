// IMC_GenericDlg.h : ͷ�ļ�
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


// CIMC_GenericDlg �Ի���
class CIMC_GenericDlg : public CDialog
{
// ����
public:
	CIMC_GenericDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CIMC_GenericDlg();

	void gotoPos_singleAxis(long axis,long velType,WORD velRatio,double pos);
	void gotoPos_MultiAxis(char cmdType,double velRatio,double X,double Y,double Z);



	

	BOOL m_bChange;	//��¼�����Ƿ��޸�
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
	short m_emstopkey;	//��ͣ����״ֵ̬

	BOOL m_errRunT;	//�����߳�����


	void StartLogo();
	void ShowDlg(int dlg);
	BOOL IsPasswordOK(int type);
	BOOL DebugVersion();
	void StartOpenTimer();
	

	void GetCurEncp(long *encp);
	void EmstopInput();
	void ErrorShow();
	WORD *GetErrorVal();

	BOOL m_threadRun;	//�߳��Ƿ���������
	BOOL m_threadPause;	//�߳��Ƿ���ͣ
	BOOL m_threadStop;	//�����߳�ֹͣ
	BOOL m_threadStep;	//
	BOOL m_threadReset;	//�����̸߳�λ���������˳��߳�
	BOOL m_EmstopRun;	//��ͣ�߳��Ƿ�����
	BOOL m_machinMode;	//���������Σ�ѭ��
	DWORD m_time;	//�����ӹ���ʱ
	DWORD m_timeTotal;	//�ӹ���ʱ
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
		
// �Ի�������
	enum { IDD = IDD_IMC_GENERIC_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;
	CBrush m_brush;
	BOOL m_isInit;
	CFont * g_fn14;	//����
	CTime m_sysTime;//ϵͳʱ��
//	CRect m_mainRC;
	int m_curdlg;
	int m_curLine;	//��ǰ����ִ�е���
	int m_nextLine;	//ִ�е���һ��
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

	// ���ɵ���Ϣӳ�亯��
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
