// dlg/SysInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "SysInfo.h"

#include "IMC_GenericDlg.h"

// CSysInfo �Ի���

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


// CSysInfo ��Ϣ�������

BOOL CSysInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	UpdateInfo();

	int iFullWidth = GetSystemMetrics(SM_CXSCREEN) + 6;
	int iFullHeight = GetSystemMetrics(SM_CYSCREEN) + 6;
	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, -3, -3, iFullWidth, iFullHeight, SWP_NOOWNERZORDER|SWP_SHOWWINDOW);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	dlg->ShowDlg(JM_SYS);
//	OnOK();
}
