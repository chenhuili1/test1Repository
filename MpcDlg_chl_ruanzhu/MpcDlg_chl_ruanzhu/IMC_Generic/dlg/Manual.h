#pragma once


// CManual 对话框

class CManual : public CDialog
{
	DECLARE_DYNAMIC(CManual)

public:
	CManual(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CManual();

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void Jog(BOOL isdown, BOOL isZ, int axis);
	void UpdateInputIcon(short *data);
	void UpdateOutputIcon(short *data);
	void UpdateLimtIcon(short *data);
	void KeyJogMg();
// 对话框数据
	enum { IDD = IDD_DLG_MANUAL };

protected:
	HBITMAP m_bmp0;
	HBITMAP m_bmp1;
	WORD m_hwaxis;
	long m_hwratio;
	DWORD m_status;
	short m_inS[INPUT_NUM];
	short m_outS[OUTPUT_NUM];
	short m_limtS[MAX_NAXIS];
		short idata[INPUT_NUM];
		short odata[OUTPUT_NUM];
		short aiodata[MAX_NAXIS];
		short Jogdata[MAX_NAXIS*2];
		short sJogdata[MAX_NAXIS*2];
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnCbnSelendokComboAxis();
	afx_msg void OnCbnSelchangeComboRatio();
	afx_msg void OnBnClickedButtonOut(UINT nId);
public:
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton4();
	long m_encpDelta1[MAX_NAXIS];
	long m_encp1[MAX_NAXIS];
	double F[320];
	double phi[1600];
	double m_MatlabTest;
	afx_msg void OnBnClickedButton5();
	double Yreal[4];
	double rc[2];
	double f;
	int k;
	double m_X;
	double m_V;
	double m_angle;
	double m_anglev;
	long m_vmpc;
	int num_v;
	void Txtsave(double parm[5]);
	CString Filename;
    CStdioFile FileWrite;
	afx_msg void OnBnClickedButton6();

};
