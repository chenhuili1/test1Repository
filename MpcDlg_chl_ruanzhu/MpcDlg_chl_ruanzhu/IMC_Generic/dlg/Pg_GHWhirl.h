#pragma once


// CPg_GHWhirl �Ի���

class CPg_GHWhirl : public CDialog
{
	DECLARE_DYNAMIC(CPg_GHWhirl)

public:
	CPg_GHWhirl(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPg_GHWhirl();
	
	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	BOOL GetProData(PROGRAM_DATA *pdata);
	void UpdateDlg(PROGRAM_DATA*pdata);
// �Ի�������
	enum { IDD = IDD_DLG_PG_GOHOME_WHIRL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
