#pragma once


// CPg_Gohome 对话框

class CPg_Gohome : public CDialog
{
	DECLARE_DYNAMIC(CPg_Gohome)

public:
	CPg_Gohome(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPg_Gohome();
	
	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	BOOL GetProData(PROGRAM_DATA *pdata);
	void UpdateDlg(PROGRAM_DATA*pdata);
// 对话框数据
	enum { IDD = IDD_DLG_PG_GOHOME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheck(UINT nId);
	virtual BOOL OnInitDialog();
	BOOL m_mode;
};
