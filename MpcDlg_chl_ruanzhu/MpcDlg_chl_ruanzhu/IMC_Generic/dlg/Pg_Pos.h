#pragma once


// CPg_Pos �Ի���

class CPg_Pos : public CDialog
{
	DECLARE_DYNAMIC(CPg_Pos)

public:
	CPg_Pos(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPg_Pos();
	
	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	BOOL GetProData(PROGRAM_DATA *pdata);
	void UpdateDlg(PROGRAM_DATA*pdata);
// �Ի�������
	enum { IDD = IDD_DLG_PG_POS };

protected:
	long GetEditFloat(UINT id, double fac);
	double GetEditFloat(UINT id);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelendokComboAxis();
	afx_msg void OnBnClickedButtonGetEncp();
	CMyEdit m_edit;
	afx_msg void OnBnClickedCheck2();
};
