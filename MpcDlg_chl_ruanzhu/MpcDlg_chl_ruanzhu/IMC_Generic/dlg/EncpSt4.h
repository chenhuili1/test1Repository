#pragma once


// CEncpSt4 对话框

class CEncpSt4 : public CDialog
{
	DECLARE_DYNAMIC(CEncpSt4)

public:
	CEncpSt4(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEncpSt4();

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void SetEncpTimer(BOOL isRun);
// 对话框数据
	enum { IDD = IDD_DLG_ENCP_STATUS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	long m_encp[MAX_NAXIS];
	void ShowEncp(long *encp);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
