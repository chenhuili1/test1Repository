#pragma once


// CPg_While 对话框

class CPg_While : public CDialog
{
	DECLARE_DYNAMIC(CPg_While)

public:
	CPg_While(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPg_While();
	
	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	BOOL GetProData(PROGRAM_DATA *pdata);
	void UpdateDlg(PROGRAM_DATA*pdata);
// 对话框数据
	enum { IDD = IDD_DLG_PG_LOOP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	CMyEdit m_edit[2];
};
