#pragma once


// CFactWarn �Ի���

class CFactWarn : public CDialog
{
	DECLARE_DYNAMIC(CFactWarn)

public:
	CFactWarn(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFactWarn();

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void UpdateCtr();
	BOOL GetCfg();
// �Ի�������
	enum { IDD = IDD_DLG_FACT_WARN };

protected:
	CFont *m_listFont;
	int m_row;

	void InitListCtrl();
	void UpdataListItem(int item, FACT_WARN* pdata);
	void EditWarnDlg();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
