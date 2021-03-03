#pragma once


// CFactPolar �Ի���

class CFactPolar : public CDialog
{
	DECLARE_DYNAMIC(CFactPolar)

public:
	CFactPolar(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFactPolar();

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void UpdateCtr();
	BOOL GetCfg();
// �Ի�������
	enum { IDD = IDD_DLG_FACT_POLAR };

protected:
	CFont *m_listFont;
	FACT_POLAR m_polar;
	void InitListCtrl();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_listctr1;
	CListCtrl m_listctr2;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
};
