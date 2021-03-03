#pragma once


// CFactWarnEdit 对话框

class CFactWarnEdit : public CDialog
{
	DECLARE_DYNAMIC(CFactWarnEdit)

public:
	CFactWarnEdit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFactWarnEdit();

	void SetWarnInfo(FACT_WARN * info);
	void GetWarnInfo(FACT_WARN * info);
// 对话框数据
	enum { IDD = IDD_DLG_EDIT_WARN };

protected:
	FACT_WARN m_warnInfo;

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMyEdit m_edit[2];
	afx_msg void OnBnClickedOk();
};
