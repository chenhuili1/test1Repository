#pragma once


// CMyFileMg 对话框

class CMyFileMg : public CDialog
{
	DECLARE_DYNAMIC(CMyFileMg)

public:
	CMyFileMg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyFileMg();

	void * m_mdlg;
	void SetMainDlgPtr(void* ptr) { m_mdlg = ptr;}
	void MyHideWindow();
	void MyShowWindow();
// 对话框数据
	enum { IDD = IDD_DLG_FILE };

protected:
//	int m_id;
	CBrush m_brush;
	CFont *m_listFont;
	CImageList m_imgList;
	HTREEITEM m_hRoot;
	HTREEITEM m_hcur;
	BOOL m_isSDEx;


	void InitTree();
	void InitListCtrl();
	CString GetFullPath(HTREEITEM hNode);
	void FindSDDir(HTREEITEM hNode);
	void FindFIle(int type, CListCtrl & list, CString str=_T(""));
	BOOL DeleteAllChildNodes(HTREEITEM hNode);
	
#if defined(WINCE)
	void OnShowSip(BOOL show);
#endif
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listctrl1;
	CListCtrl m_listctrl2;
	CTreeCtrl m_TreeCtrl;
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	CMyButton m_ctrBn[6];
	afx_msg void OnTvnItemexpandingTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnEndlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBnNew();
	afx_msg void OnEnKillfocusEditEd();
	afx_msg void OnTvnBeginlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedBnCopyToSys();
	afx_msg void OnBnClickedBnCopyToSd();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBnDelete();
};
