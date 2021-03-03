// dlg/LogoInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "LogoInfo.h"


// CLogoInfo 对话框

IMPLEMENT_DYNAMIC(CLogoInfo, CDialog)

CLogoInfo::CLogoInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CLogoInfo::IDD, pParent)
{

}

CLogoInfo::~CLogoInfo()
{
}

void CLogoInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLogoInfo, CDialog)
END_MESSAGE_MAP()


// CLogoInfo 消息处理程序

BOOL CLogoInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_EDIT_SYS_NAME, g_factcfg.sysName);
	SetDlgItemText(IDC_EDIT_FACT_NAME, g_factcfg.factName);
	SetDlgItemText(IDC_EDIT_FACT_PHONE, g_factcfg.phone);
	SetDlgItemText(IDC_EDIT_FACT_ADDRESS, g_factcfg.address);
	SetDlgItemText(IDC_EDIT_FACT_WEB, g_factcfg.web);
#if defined(WINCE)
	int iFullWidth = GetSystemMetrics(SM_CXSCREEN) + 6;
	int iFullHeight = GetSystemMetrics(SM_CYSCREEN) + 6;
	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, -3, -3, iFullWidth, iFullHeight, SWP_NOOWNERZORDER|SWP_SHOWWINDOW);
#endif
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLogoInfo::OnCancel()
{
    DestroyWindow();
}
void CLogoInfo::PostNcDestroy()
{
    CDialog::PostNcDestroy();
    delete this;
}