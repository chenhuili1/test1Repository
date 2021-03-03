#pragma once


// CPg_Vel 对话框

class CPg_Vel : public CDialog
{
	DECLARE_DYNAMIC(CPg_Vel)

public:
	CPg_Vel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPg_Vel();
	
	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	BOOL GetProData(PROGRAM_DATA *pdata);
	void UpdateDlg(PROGRAM_DATA*pdata);
// 对话框数据
	enum { IDD = IDD_DLG_PG_VEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
