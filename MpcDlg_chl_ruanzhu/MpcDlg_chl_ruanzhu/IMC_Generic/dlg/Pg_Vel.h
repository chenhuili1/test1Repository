#pragma once


// CPg_Vel �Ի���

class CPg_Vel : public CDialog
{
	DECLARE_DYNAMIC(CPg_Vel)

public:
	CPg_Vel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPg_Vel();
	
	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	BOOL GetProData(PROGRAM_DATA *pdata);
	void UpdateDlg(PROGRAM_DATA*pdata);
// �Ի�������
	enum { IDD = IDD_DLG_PG_VEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
