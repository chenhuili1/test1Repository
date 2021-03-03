#pragma once


// CMpcDlg 对话框
#define TIMER_MPC	12
#define DATALENGTH	16000
#define XKFNUM	1000


class CMpcDlg : public CDialog
{
	DECLARE_DYNAMIC(CMpcDlg)

public:
	CMpcDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMpcDlg();


	IMCU32 CurTickCnt;
	IMCU32 OldTickCnt;
	IMCU32 DeltaTickCnt;
	IMC32 Xmove;
	IMC32 XCmove;
	IMC32 Xangle;
	

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
// 对话框数据
	enum { IDD = IDD_DLG_MPC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
	double m_Xpos;
	CString Filename;
    CStdioFile FileWrite;
	bool IsFileOpen;
	void Txtsave(double *parm);
	afx_msg void OnBnClickedButton3();
	void ParmCalculate(double *Parm);
	long m_encpDelta1[MAX_NAXIS];
	long m_encp1[MAX_NAXIS];
	double MpcParm[4];
	long m_encp[MAX_NAXIS];
	
	WORD axis[6];
	double rc[2];
	double f,f_last,v_last;
	double y0[4];
	unsigned long k,cont,ckf,k1;
	double F[320],countflag,MpcParm0last;
	double phi[1600];
	double ParmSave[DATALENGTH];
	double ParmXkf[XKFNUM];
	long t1,t2;
	double lastAngleRad[2],AngleSpeed[2];
	double lastV[2],SpeedV[2];
	double a_X,a_Y,X_last,Y_last,X_Speed_last;


	UINT CreateTimer();
	UINT timerID,timerID1;
	static void PASCAL TimeProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
	static void PASCAL TimeProc1(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
	void MyTimer(UINT nIDEvent);
	void DestroyTimer();
	unsigned long m_number;
	double Move(double *Parm);
	double Stop(double *Parm);
	void FinishRun();
	int flag,flag_v,flag_y0,Greedledflag,Yellowledflag,Redledflag;
	//double a;
	afx_msg void OnBnClickedButton4();
	double xkf[2];
	afx_msg void OnBnClickedButton5();
	double stopX;
	afx_msg void OnPaint();
};
