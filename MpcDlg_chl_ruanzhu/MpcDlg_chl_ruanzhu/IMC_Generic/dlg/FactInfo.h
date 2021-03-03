#pragma once


// CFactInfo 对话框

class CFactInfo : public CDialog
{
	DECLARE_DYNAMIC(CFactInfo)

public:
	CFactInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFactInfo();

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void UpdateCtr();
	BOOL GetCfg();
// 对话框数据
	enum { IDD = IDD_DLG_FACT_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CMyEdit m_edit[5];
};
