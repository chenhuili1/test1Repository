#pragma once


// CEncpSt6 对话框

class CEncpSt6 : public CDialog
{
	DECLARE_DYNAMIC(CEncpSt6)

public:
	CEncpSt6(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEncpSt6();

	IMC32 CurTickCnt;
	IMC32 OldTickCnt;
	IMC32 DeltaTickCnt;
	

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void SetEncpTimer(BOOL isRun);
// 对话框数据
	enum { IDD = IDD_DLG_ENCP_STATUS_6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	long m_encp[MAX_NAXIS];

	long m_encpDelta[MAX_NAXIS];
	void ShowEncp(long *encp);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
