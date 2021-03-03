#pragma once


// CPg_Linkage 对话框

class CPg_Linkage : public CDialog
{
	DECLARE_DYNAMIC(CPg_Linkage)

public:
	CPg_Linkage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPg_Linkage();
	
	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	BOOL GetProData(PROGRAM_DATA *pdata);
	void UpdateDlg(PROGRAM_DATA*pdata);
// 对话框数据
	enum { IDD = IDD_DLG_PG_LINKAGE };

protected:
	long GetEditFloat(UINT id, double fac);
	double GetEditFloat(UINT id);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMyEdit m_edit[16];
	afx_msg void OnBnClickedCheckAxis(UINT nId);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonGetEncp();
};
