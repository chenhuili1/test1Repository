// dlg/SysInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "SysInfo.h"

#include "IMC_GenericDlg.h"

// CSysInfo 对话框

IMPLEMENT_DYNAMIC(CSysInfo, CDialog)

CSysInfo::CSysInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CSysInfo::IDD, pParent)
{

}

CSysInfo::~CSysInfo()
{
}

void CSysInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSysInfo, CDialog)
	ON_BN_CLICKED(IDOK, &CSysInfo::OnBnClickedOk)
END_MESSAGE_MAP()


// CSysInfo 消息处理程序

BOOL CSysInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	UpdateInfo();

	int iFullWidth = GetSystemMetrics(SM_CXSCREEN) + 6;
	int iFullHeight = GetSystemMetrics(SM_CYSCREEN) + 6;
	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, -3, -3, iFullWidth, iFullHeight, SWP_NOOWNERZORDER|SWP_SHOWWINDOW);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CSysInfo::UpdateInfo()
{
	SetDlgItemText(IDC_EDIT_FACT_NAME, g_factcfg.factName);
	SetDlgItemText(IDC_EDIT_FACT_PHONE, g_factcfg.phone);
	SetDlgItemText(IDC_EDIT_FACT_ADDRESS, g_factcfg.address);
	SetDlgItemText(IDC_EDIT_FACT_WEB, g_factcfg.web);
}
void CSysInfo::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	dlg->ShowDlg(JM_SYS);
//	OnOK();
}
