// dlg/FactInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "FactInfo.h"

#include "IMC_GenericDlg.h"

// CFactInfo �Ի���

IMPLEMENT_DYNAMIC(CFactInfo, CDialog)

CFactInfo::CFactInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CFactInfo::IDD, pParent)
{

}

CFactInfo::~CFactInfo()
{
}

void CFactInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FACT_NAME, m_edit[0]);
	DDX_Control(pDX, IDC_EDIT_FACT_WEB, m_edit[1]);
	DDX_Control(pDX, IDC_EDIT_FACT_PHONE, m_edit[2]);
	DDX_Control(pDX, IDC_EDIT_FACT_ADDRESS, m_edit[3]);
	DDX_Control(pDX, IDC_EDIT_SYS_NAME, m_edit[4]);
}


BEGIN_MESSAGE_MAP(CFactInfo, CDialog)
END_MESSAGE_MAP()


// CFactInfo ��Ϣ�������

BOOL CFactInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	UpdateCtr();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CFactInfo::UpdateCtr()
{
	SetDlgItemText(IDC_EDIT_SYS_NAME,g_factcfg.sysName);
	SetDlgItemText(IDC_EDIT_FACT_NAME,g_factcfg.factName);
	SetDlgItemText(IDC_EDIT_FACT_WEB,g_factcfg.web);
	SetDlgItemText(IDC_EDIT_FACT_PHONE,g_factcfg.phone);
	SetDlgItemText(IDC_EDIT_FACT_ADDRESS,g_factcfg.address);
}

BOOL CFactInfo::GetCfg()
{
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	memset(g_factcfg.sysName, 0, sizeof(WCHAR) * FACT_INFO_LEN);
	GetDlgItemText(IDC_EDIT_SYS_NAME,g_factcfg.sysName, 60);
	memset(g_factcfg.factName, 0, sizeof(WCHAR) * FACT_INFO_LEN);
	GetDlgItemText(IDC_EDIT_FACT_NAME,g_factcfg.factName, 60);
	memset(g_factcfg.web, 0, sizeof(WCHAR) * FACT_INFO_LEN);
	GetDlgItemText(IDC_EDIT_FACT_WEB,g_factcfg.web, 60);
	memset(g_factcfg.phone, 0, sizeof(WCHAR) * FACT_INFO_LEN);
	GetDlgItemText(IDC_EDIT_FACT_PHONE,g_factcfg.phone, 60);
	memset(g_factcfg.address, 0, sizeof(WCHAR) * FACT_INFO_LEN);
	GetDlgItemText(IDC_EDIT_FACT_ADDRESS,g_factcfg.address, 60);
	dlg->SetWindowText(g_factcfg.sysName);
	return TRUE;
}