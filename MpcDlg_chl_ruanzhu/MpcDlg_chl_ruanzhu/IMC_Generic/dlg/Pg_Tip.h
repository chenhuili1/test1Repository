#pragma once


// CPg_Tip 对话框

class CPg_Tip : public CDialog
{
	DECLARE_DYNAMIC(CPg_Tip)

public:
	CPg_Tip(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPg_Tip();
	
	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void SetPrompt(int cmd);
// 对话框数据
	enum { IDD = IDD_DLG_PG_TIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
