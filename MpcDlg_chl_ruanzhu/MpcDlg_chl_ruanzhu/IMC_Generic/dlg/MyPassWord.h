#pragma once


// CMyPassWord 对话框

class CMyPassWord : public CDialog
{
	DECLARE_DYNAMIC(CMyPassWord)

public:
	CMyPassWord(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyPassWord();

	void* m_mdlg;
	void SetMainDlgPtr(void* pdlg) {m_mdlg = pdlg;}
	void SetType(int type);
// 对话框数据
	enum { IDD = IDD_DLG_PASSWORD };

protected:
	int m_type;
	BOOL IsPasswordOK();
	void GetPassword();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
};
