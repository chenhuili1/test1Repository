#pragma once


// CPg_Delay 对话框

class CPg_Delay : public CDialog
{
	DECLARE_DYNAMIC(CPg_Delay)

public:
	CPg_Delay(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPg_Delay();
	
	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
//	void SetPrompt(int cmd);
	long GetEditFloat(UINT id, double fac);
	BOOL GetProData(PROGRAM_DATA *pdata);
	void UpdateDlg(PROGRAM_DATA*pdata);
// 对话框数据
	enum { IDD = IDD_DLG_PG_DELAY };

protected:
	CMyEdit m_edit;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
