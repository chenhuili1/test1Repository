#pragma once
#include "afxcmn.h"


// CSysDlg 对话框

class CSysDlg : public CDialog
{
	DECLARE_DYNAMIC(CSysDlg)

public:
	CSysDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSysDlg();

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void UpdateCtr();
	BOOL GetCfg();
	void SetDefSip();
// 对话框数据
	enum { IDD = IDD_DLG_SYS };

protected:
	UINT m_factID;
	CFont *m_listFont;
	int m_row;
	int m_lie;
	char m_dir[MAX_NAXIS];

	BOOL IsPasswordOK(UINT id, int type);
	long GetEditFloat(UINT id, double fac);
	double GetEditFloat(UINT id);
	double GetListFloat(int row, int lie);
	int GetHomeDir(int row);
	void MoveEdit(int row, int lie);
	BOOL HideEdit();

	void InitListCtrl();
#if defined(WINCE)
	void GetKeySipEnum();
	void OnSipSelect() ;
#endif
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBnFactCfg();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBnChpwLogin();
	afx_msg void OnBnClickedBnChpwEdit();
	afx_msg void OnBnClickedBnChpwSys();
	afx_msg void OnBnClickedBnChpwRun();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBnOk();
	CEdit m_edit[10];
#if defined(WINCE)
	afx_msg void OnCbnSelendokComboKeyboard();
#endif
	afx_msg LRESULT OnFactLgin(WPARAM wparam,LPARAM lparam);
	afx_msg void OnBnClickedBnDebug();
	CListCtrl m_listctr;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
