#pragma once


// CFactInfo �Ի���

class CFactInfo : public CDialog
{
	DECLARE_DYNAMIC(CFactInfo)

public:
	CFactInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFactInfo();

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void UpdateCtr();
	BOOL GetCfg();
// �Ի�������
	enum { IDD = IDD_DLG_FACT_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CMyEdit m_edit[5];
};
