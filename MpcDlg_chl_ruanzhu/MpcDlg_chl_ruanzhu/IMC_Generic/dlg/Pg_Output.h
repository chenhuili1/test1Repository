#pragma once


// CPg_Output �Ի���

class CPg_Output : public CDialog
{
	DECLARE_DYNAMIC(CPg_Output)

public:
	CPg_Output(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPg_Output();
	
	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	long GetEditFloat(UINT id, double fac);
	BOOL GetProData(PROGRAM_DATA *pdata);
	void UpdateDlg(PROGRAM_DATA*pdata);
// �Ի�������
	enum { IDD = IDD_DLG_PG_OUTPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CMyEdit m_edit;
};
