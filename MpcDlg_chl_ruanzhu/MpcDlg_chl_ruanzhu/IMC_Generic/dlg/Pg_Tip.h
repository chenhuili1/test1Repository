#pragma once


// CPg_Tip �Ի���

class CPg_Tip : public CDialog
{
	DECLARE_DYNAMIC(CPg_Tip)

public:
	CPg_Tip(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPg_Tip();
	
	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void SetPrompt(int cmd);
// �Ի�������
	enum { IDD = IDD_DLG_PG_TIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
