#pragma once


// CFindHome �Ի���

class CFindHome : public CDialog
{
	DECLARE_DYNAMIC(CFindHome)

public:
	CFindHome(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFindHome();

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void UpdateCtr();
// �Ի�������
	enum { IDD = IDD_DLG_FIND_HOME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	long m_encp[MAX_NAXIS];
	void ShowEncp(long *encp);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBnAxisZ(UINT nID);
	afx_msg void OnBnClickedBnAxisF(UINT nID);
	afx_msg void OnBnClickedBnStopFind(UINT nID);
	afx_msg void OnBnClickedBnSetHome(UINT nID);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
