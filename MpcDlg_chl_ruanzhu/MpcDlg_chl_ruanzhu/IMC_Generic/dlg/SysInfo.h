#pragma once


// CSysInfo �Ի���

class CSysInfo : public CDialog
{
	DECLARE_DYNAMIC(CSysInfo)

public:
	CSysInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSysInfo();

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void UpdateInfo();
// �Ի�������
	enum { IDD = IDD_DLG_SYS_INFO };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
