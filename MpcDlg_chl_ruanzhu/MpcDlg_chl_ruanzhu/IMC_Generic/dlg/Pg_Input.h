#pragma once


// CPg_Input �Ի���

class CPg_Input : public CDialog
{
	DECLARE_DYNAMIC(CPg_Input)

public:
	CPg_Input(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPg_Input();
	
	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	long GetEditFloat(UINT id, double fac = 1.0);
	BOOL GetProData(PROGRAM_DATA *pdata);
	void UpdateDlg(PROGRAM_DATA*pdata);
// �Ի�������
	enum { IDD = IDD_DLG_PG_INPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	BOOL m_inSel;
	CMyEdit m_edit[2];
};
