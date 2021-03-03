#pragma once


// CFactIOmap 对话框

class CFactIOmap : public CDialog
{
	DECLARE_DYNAMIC(CFactIOmap)

public:
	CFactIOmap(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFactIOmap();

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void UpdateCtr();
	BOOL GetCfg();
// 对话框数据
	enum { IDD = IDD_DLG_FACT_IOMAP };

protected:
	CFont *m_listFont;
	
	int m_row;
	int m_lie;
	void InitListCtrl();
	void MoveBox(int row);
	BOOL HideBox();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_listctr1;
	CListCtrl m_listctr2;
	CComboBox m_listbox1;
	CComboBox m_listbox2;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelendokCombo1();
	afx_msg void OnCbnSelendokCombo2();
};
