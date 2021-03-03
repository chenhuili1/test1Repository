#pragma once


// CFactWarn 对话框

class CFactWarn : public CDialog
{
	DECLARE_DYNAMIC(CFactWarn)

public:
	CFactWarn(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFactWarn();

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void UpdateCtr();
	BOOL GetCfg();
// 对话框数据
	enum { IDD = IDD_DLG_FACT_WARN };

protected:
	CFont *m_listFont;
	int m_row;

	void InitListCtrl();
	void UpdataListItem(int item, FACT_WARN* pdata);
	void EditWarnDlg();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_listctr1;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT EditWarnDlg(WPARAM wparam,LPARAM lparam);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
