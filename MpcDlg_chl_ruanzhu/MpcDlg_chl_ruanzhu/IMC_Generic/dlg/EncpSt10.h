#pragma once


// CEncpSt10 �Ի���

class CEncpSt10 : public CDialog
{
	DECLARE_DYNAMIC(CEncpSt10)

public:
	CEncpSt10(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEncpSt10();

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void SetEncpTimer(BOOL isRun);
// �Ի�������
	enum { IDD = IDD_DLG_ENCP_STATUS_10 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	long m_encp[MAX_NAXIS];
	void ShowEncp(long *encp);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
