#pragma once


// CFactAxis 对话框

class CFactAxis : public CDialog
{
	DECLARE_DYNAMIC(CFactAxis)

public:
	CFactAxis(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFactAxis();
	
	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	BOOL GetCfg();
	void UpdateCtr(BOOL isUpAxis = TRUE);
	BOOL m_isInit;
// 对话框数据
	enum { IDD = IDD_DLG_FACT_AXIS };

protected:
	CFont *m_listFont;

	int m_row;
	int m_lie;
	
	void InitListCtrl();
	double GetListFloat(int row, int lie);
	void MoveEdit(int row, int lie);
	BOOL HideEdit();
//	void MoveBox(int row, int lie);
//	BOOL HideBox();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditNaxis();
	CListCtrl m_listctr;
	CMyEdit m_listEdit;
	CMyEdit m_edit;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEditUnit0();
//	CComboBox m_listbox;
//	afx_msg void OnCbnSelendokCombo1();
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
};
