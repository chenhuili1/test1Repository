#pragma once


// CPg_Wait 对话框

class CPg_Wait : public CDialog
{
	DECLARE_DYNAMIC(CPg_Wait)

public:
	CPg_Wait(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPg_Wait();
	
	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	BOOL GetProData(PROGRAM_DATA *pdata);
	void UpdateDlg(PROGRAM_DATA*pdata);
// 对话框数据
	enum { IDD = IDD_DLG_PG_WAIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_wait;
};
