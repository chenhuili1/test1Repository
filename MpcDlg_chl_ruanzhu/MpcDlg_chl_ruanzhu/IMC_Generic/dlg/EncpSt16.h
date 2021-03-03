#pragma once


// CEncpSt16 对话框

class CEncpSt16 : public CDialog
{
	DECLARE_DYNAMIC(CEncpSt16)

public:
	CEncpSt16(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEncpSt16();

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void SetEncpTimer(BOOL isRun);
// 对话框数据
	enum { IDD = IDD_DLG_ENCP_STATUS_16 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	long m_encp[MAX_NAXIS];
	void ShowEncp(long *encp);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
