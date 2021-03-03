#pragma once


// CFactPolar 对话框

class CFactPolar : public CDialog
{
	DECLARE_DYNAMIC(CFactPolar)

public:
	CFactPolar(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFactPolar();

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void UpdateCtr();
	BOOL GetCfg();
// 对话框数据
	enum { IDD = IDD_DLG_FACT_POLAR };

protected:
	CFont *m_listFont;
	FACT_POLAR m_polar;
	void InitListCtrl();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_listctr1;
	CListCtrl m_listctr2;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
};
