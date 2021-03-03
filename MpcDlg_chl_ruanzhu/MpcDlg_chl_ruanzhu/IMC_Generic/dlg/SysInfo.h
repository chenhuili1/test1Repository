#pragma once


// CSysInfo 对话框

class CSysInfo : public CDialog
{
	DECLARE_DYNAMIC(CSysInfo)

public:
	CSysInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSysInfo();

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void UpdateInfo();
// 对话框数据
	enum { IDD = IDD_DLG_SYS_INFO };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
