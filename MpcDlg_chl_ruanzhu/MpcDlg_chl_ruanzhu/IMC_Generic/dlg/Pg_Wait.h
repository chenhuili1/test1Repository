#pragma once


// CPg_Wait �Ի���

class CPg_Wait : public CDialog
{
	DECLARE_DYNAMIC(CPg_Wait)

public:
	CPg_Wait(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPg_Wait();
	
	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	BOOL GetProData(PROGRAM_DATA *pdata);
	void UpdateDlg(PROGRAM_DATA*pdata);
// �Ի�������
	enum { IDD = IDD_DLG_PG_WAIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_wait;
};
