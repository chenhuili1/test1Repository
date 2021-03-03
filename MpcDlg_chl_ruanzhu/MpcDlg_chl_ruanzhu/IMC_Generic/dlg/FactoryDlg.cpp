// dlg/FactoryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "FactoryDlg.h"

#include "IMC_GenericDlg.h"

// CFactoryDlg 对话框

IMPLEMENT_DYNAMIC(CFactoryDlg, CDialog)

CFactoryDlg::CFactoryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFactoryDlg::IDD, pParent)
{

}

CFactoryDlg::~CFactoryDlg()
{
}

void CFactoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PWFACT_OLD, m_edit[0]);
	DDX_Control(pDX, IDC_EDIT_PWFACT_NEW, m_edit[1]);
}


BEGIN_MESSAGE_MAP(CFactoryDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CFactoryDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CFactoryDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BN_IOMAP, &CFactoryDlg::OnBnClickedBnIomap)
	ON_BN_CLICKED(IDC_BN_CHPW_FACT, &CFactoryDlg::OnBnClickedBnChpwFact)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BN_FACT_INFO, &CFactoryDlg::OnBnClickedBnFactInfo)
	ON_BN_CLICKED(IDC_BN_AXIS_SET, &CFactoryDlg::OnBnClickedBnAxisSet)
	ON_BN_CLICKED(IDC_BN_IN_POLAR, &CFactoryDlg::OnBnClickedBnInPolar)
	ON_BN_CLICKED(IDC_BN_FACT_WARN, &CFactoryDlg::OnBnClickedBnFactWarn)
END_MESSAGE_MAP()


// CFactoryDlg 消息处理程序

BOOL CFactoryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_axisdlg.SetMainDlgPtr(m_mdlg);
	m_IOmapdlg.SetMainDlgPtr(m_mdlg);
	m_infodlg.SetMainDlgPtr(m_mdlg);
	m_polardlg.SetMainDlgPtr(m_mdlg);

	m_axisdlg.Create(IDD_DLG_FACT_AXIS, this);
	m_axisdlg.ShowWindow(SW_SHOW);
	m_IOmapdlg.Create(IDD_DLG_FACT_IOMAP, this);
	m_IOmapdlg.ShowWindow(SW_HIDE);
	m_infodlg.Create(IDD_DLG_FACT_INFO, this);
	m_infodlg.ShowWindow(SW_HIDE);
	m_polardlg.Create(IDD_DLG_FACT_POLAR, this);
	m_polardlg.ShowWindow(SW_HIDE);
	m_warndlg.Create(IDD_DLG_FACT_WARN, this);
	m_warndlg.ShowWindow(SW_HIDE);
	m_dlg = FACT_AXIS;
	MoveDlg();
//	SetDlgItemText(IDC_EDIT_SYS_NAME,g_factcfg.sysName);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CFactoryDlg::MoveDlg()
{
	CRect rc,rc1, rc2;
	GetClientRect(&rc);
//	GetDlgItem(IDOK)->GetWindowRect(&rc1);
//	ScreenToClient(&rc1);
	GetDlgItem(IDC_BN_IOMAP)->GetWindowRect(&rc2);
	ScreenToClient(&rc2);

//	m_axisdlg.GetClientRect(&rc1);
//	rc.bottom = rc1.top -2;
	rc.right = rc2.left-5;
	m_axisdlg.MoveWindow(rc);
	m_IOmapdlg.MoveWindow(rc);
	m_infodlg.MoveWindow(rc);
	m_polardlg.MoveWindow(rc);
	m_warndlg.MoveWindow(rc);

}


void CFactoryDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	switch(m_dlg)
	{
	case FACT_AXIS: if(!m_axisdlg.GetCfg()) return; break;
	case FACT_IOMAP:if(!m_IOmapdlg.GetCfg()) return; break;
	case FACT_INFO:if(!m_infodlg.GetCfg()) return; break;
	case FAC_POLAR:if(!m_polardlg.GetCfg()) return; break;
	case FAC_WARN:if(!m_warndlg.GetCfg()) return; break;
	}	
	SaveFactCfg();
	SaveFactPolar();
	SaveIOMap();
	SaveWarn();
	dlg->ShowDlg(JM_SYS);
	dlg->m_imc.SetSteptime();
	dlg->m_imc.SetPolar();
//	CDialog::OnOK();
}


void CFactoryDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	dlg->ShowDlg(JM_SYS);
//	CDialog::OnCancel();
}

void CFactoryDlg::ShowDlg(int dlg)
{
	SetDlgItemText(IDC_EDIT_PWFACT_OLD, _T(""));
	SetDlgItemText(IDC_EDIT_PWFACT_NEW, _T(""));
	if(m_dlg != dlg){
		switch(m_dlg)
		{
		case FACT_AXIS: if(!m_axisdlg.GetCfg()) return; m_axisdlg.ShowWindow(SW_HIDE); break;
		case FACT_IOMAP:if(!m_IOmapdlg.GetCfg()) return; m_IOmapdlg.ShowWindow(SW_HIDE); break;
		case FACT_INFO:if(!m_infodlg.GetCfg()) return; m_infodlg.ShowWindow(SW_HIDE); break;
		case FAC_POLAR:if(!m_polardlg.GetCfg()) return; m_polardlg.ShowWindow(SW_HIDE); break;
		case FAC_WARN:if(!m_warndlg.GetCfg()) return; m_warndlg.ShowWindow(SW_HIDE); break;
		}
	}
	m_dlg = dlg;
	switch(m_dlg)
	{
	case FACT_AXIS: m_axisdlg.UpdateCtr();	m_axisdlg.ShowWindow(SW_SHOW); break;
	case FACT_IOMAP:m_IOmapdlg.UpdateCtr();	m_IOmapdlg.ShowWindow(SW_SHOW); break;
	case FACT_INFO:	m_infodlg.UpdateCtr();	m_infodlg.ShowWindow(SW_SHOW); break;
	case FAC_POLAR:	m_polardlg.UpdateCtr();	m_polardlg.ShowWindow(SW_SHOW); break;
	case FAC_WARN:	/*m_warndlg.UpdateCtr();	*/m_warndlg.ShowWindow(SW_SHOW); break;
	}
}

void CFactoryDlg::OnBnClickedBnAxisSet()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_dlg != FACT_AXIS)
		ShowDlg(FACT_AXIS);
}

void CFactoryDlg::OnBnClickedBnIomap()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_dlg != FACT_IOMAP)
		ShowDlg(FACT_IOMAP);
}

void CFactoryDlg::OnBnClickedBnFactInfo()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_dlg != FACT_INFO)
		ShowDlg(FACT_INFO);
}

void CFactoryDlg::OnBnClickedBnInPolar()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_dlg != FAC_POLAR)
		ShowDlg(FAC_POLAR);
}

void CFactoryDlg::OnBnClickedBnFactWarn()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_dlg != FAC_WARN)
		ShowDlg(FAC_WARN);
}



void CFactoryDlg::OnBnClickedBnChpwFact()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	CString str;
	GetDlgItemText(IDC_EDIT_PWFACT_OLD, str);
	int len = str.GetLength();
	WCHAR *pw;
	pw = g_factcfg.PWfact; 
	if(pw[0]){
		if(len != PASSWORD_USE_LEN){
			SetDlgItemText(IDC_EDIT_PWFACT_OLD, _T(""));
			MessageBox(_T("密码错误"));
			return ;
		}
		for(int i=0; i<PASSWORD_USE_LEN; i++)
		{
			if(str.GetAt(i) != pw[i]){
				SetDlgItemText(IDC_EDIT_PWFACT_OLD, _T(""));
				MessageBox(_T("密码错误"));
				return ;
			}
		}
	}
	WCHAR pw1[16];
	len = GetDlgItemText(IDC_EDIT_PWFACT_NEW, pw1, 16);
	
	if(len == 0){
		memset(pw, 0, PASSWORD_USE_LEN * sizeof(WCHAR));
	}else {
		if(len != PASSWORD_USE_LEN){
			MessageBox(_T("密码长度为6个字符"));
			return;
		}
		memcpy(pw, pw1, PASSWORD_USE_LEN * sizeof(WCHAR));
	}
}


void CFactoryDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	if(bShow)
		ShowDlg(FACT_AXIS);
}
