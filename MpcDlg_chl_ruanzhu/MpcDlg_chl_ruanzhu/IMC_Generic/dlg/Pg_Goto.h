#pragma once


// CPg_Goto �Ի���

class CPg_Goto : public CDialog
{
	DECLARE_DYNAMIC(CPg_Goto)

public:
	CPg_Goto(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPg_Goto();
	
	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
//	void SetPrompt(int cmd);
	BOOL GetProData(PROGRAM_DATA *pdata);
	void UpdateDlg(PROGRAM_DATA*pdata);
// �Ի�������
	enum { IDD = IDD_DLG_PG_JUMP };

protected:
	int m_cmd;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	CMyEdit m_edit;
};
