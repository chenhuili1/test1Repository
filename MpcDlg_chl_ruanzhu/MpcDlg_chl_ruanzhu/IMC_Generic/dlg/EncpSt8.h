#pragma once


// CEncpSt8 �Ի���

class CEncpSt8 : public CDialog
{
	DECLARE_DYNAMIC(CEncpSt8)

public:
	CEncpSt8(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEncpSt8();

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void SetEncpTimer(BOOL isRun);
// �Ի�������
	enum { IDD = IDD_DLG_ENCP_STATUS_8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	long m_encp[MAX_NAXIS];
	void ShowEncp(long *encp);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStnClickedStaticEncpA6();
};
