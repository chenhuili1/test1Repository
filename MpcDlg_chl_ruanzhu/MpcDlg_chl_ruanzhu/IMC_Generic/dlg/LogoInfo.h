#pragma once


// CLogoInfo 对话框

class CLogoInfo : public CDialog
{
	DECLARE_DYNAMIC(CLogoInfo)

public:
	CLogoInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogoInfo();

	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void PostNcDestroy();
// 对话框数据
	enum { IDD = IDD_DLG_LOGO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
