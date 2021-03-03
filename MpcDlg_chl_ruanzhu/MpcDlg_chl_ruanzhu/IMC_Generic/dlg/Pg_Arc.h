#pragma once


// CPg_Arc 对话框

class CPg_Arc : public CDialog
{
	DECLARE_DYNAMIC(CPg_Arc)

public:
	CPg_Arc(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPg_Arc();

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	BOOL GetProData(PROGRAM_DATA *pdata);
	void UpdateDlg(PROGRAM_DATA*pdata);
	BOOL GetEncp();
// 对话框数据
	enum { IDD = IDD_DLG_PG_ARC };

protected:
	int m_ArcSel[2];
	int m_index;
	long GetEditFloat(UINT id, double fac);
	double GetEditFloat(UINT id);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CMyEdit m_edit[22];
	afx_msg void OnBnClickedCheckAxis(UINT nId);
	afx_msg void OnCbnSelendokComboArcAxis0();
	afx_msg void OnCbnSelendokComboArcAxis1();
	afx_msg void OnBnClickedButtonGetEncp();
	afx_msg void OnBnClickedButtonGetEncp1();
	afx_msg void OnBnClickedButtonGetEncp2();
	afx_msg void OnBnClickedButtonGetEncp3();
};
