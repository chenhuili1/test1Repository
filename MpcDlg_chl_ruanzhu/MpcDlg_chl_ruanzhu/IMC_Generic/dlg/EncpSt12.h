#pragma once


// CEncpSt12 �Ի���

class CEncpSt12 : public CDialog
{
	DECLARE_DYNAMIC(CEncpSt12)

public:
	CEncpSt12(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEncpSt12();

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void SetEncpTimer(BOOL isRun);
// �Ի�������
	enum { IDD = IDD_DLG_ENCP_STATUS_12 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	long m_encp[MAX_NAXIS];
	void ShowEncp(long *encp);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
