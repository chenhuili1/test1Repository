// dlg/FindHome.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "FindHome.h"
#include "IMC_GenericDlg.h"


// CFindHome 对话框

IMPLEMENT_DYNAMIC(CFindHome, CDialog)

CFindHome::CFindHome(CWnd* pParent /*=NULL*/)
	: CDialog(CFindHome::IDD, pParent)
{

}

CFindHome::~CFindHome()
{
}

void CFindHome::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFindHome, CDialog)
	ON_BN_CLICKED(IDOK, &CFindHome::OnBnClickedOk)
	ON_COMMAND_RANGE(IDC_BN_AXIS_Z_0, IDC_BN_AXIS_Z_15, &CFindHome::OnBnClickedBnAxisZ)
	ON_COMMAND_RANGE(IDC_BN_AXIS_F_0, IDC_BN_AXIS_F_15, &CFindHome::OnBnClickedBnAxisF)
	ON_COMMAND_RANGE(IDC_BN_STOP_FIND_0, IDC_BN_STOP_FIND_15, &CFindHome::OnBnClickedBnStopFind)
	ON_COMMAND_RANGE(IDC_BN_SET_HOME_0, IDC_BN_SET_HOME_15, &CFindHome::OnBnClickedBnSetHome)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CFindHome 消息处理程序


BOOL CFindHome::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE; 
}


void CFindHome::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	KillTimer(TIMER_FHOME_ENCP);
	dlg->ShowDlg(JM_MAIN);
//	CDialog::OnOK();
}
typedef struct FHomeData_tag{
	PVOID dlg;
	int axis;
	int dir;
}FHomeData;
UINT FindHomeThread(PVOID param)
{
	FHomeData *pdata = (FHomeData*)param;
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)pdata->dlg;//GetParent();
	int axis = pdata->axis;
	int dir = pdata->dir;
	if(dlg->m_imc.IsOfHomed(axis)){
		if(dir)//往负方向搜零，需要往正方向移动一点点
			dlg->m_imc.Jog(MOVE_HOMED_VEL, axis);
		else
			dlg->m_imc.Jog(-(MOVE_HOMED_VEL), axis);
		while(dlg->m_imc.IsOfHomed(axis));
		dlg->m_imc.Jog(0, axis);
	}
	dlg->m_imc.FindHome(dir, axis);
	delete pdata;
	return 0;
}

void CFindHome::OnBnClickedBnAxisZ(UINT nID)
{
/*	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	long axis = nID - IDC_BN_AXIS_Z_0;
	if(dlg->m_imc.IsOfHomed(axis)){
		dlg->m_imc.Jog(-10000, axis);
		while(dlg->m_imc.IsOfHomed(axis));
		dlg->m_imc.Jog(0, 0);
	}
	dlg->m_imc.FindHome(0, axis);
	*/
	FHomeData *data;
	int axis = nID - IDC_BN_AXIS_Z_0;
	data = new FHomeData;
	data->axis = axis;
	data->dlg = m_mdlg;
	data->dir = 0;
	AfxBeginThread(FindHomeThread, data);
}
void CFindHome::OnBnClickedBnAxisF(UINT nID)
{
/*	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	long axis = nID - IDC_BN_AXIS_F_0;
	if(dlg->m_imc.IsOfHomed(axis)){
		dlg->m_imc.Jog(10000, axis);
		while(dlg->m_imc.IsOfHomed(axis));
		dlg->m_imc.Jog(0, 0);
	}
	dlg->m_imc.FindHome(1, axis);*/
	FHomeData *data;
	int axis = nID - IDC_BN_AXIS_F_0;
	data = new FHomeData;
	data->axis = axis;
	data->dlg = m_mdlg;
	data->dir = 1;
	AfxBeginThread(FindHomeThread, data);
}
void CFindHome::OnBnClickedBnStopFind(UINT nID)
{
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	long axis = nID - IDC_BN_STOP_FIND_0;
	dlg->m_imc.StopFindHome(axis);
}
void CFindHome::OnBnClickedBnSetHome(UINT nID)
{
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	long axis = nID - IDC_BN_SET_HOME_0;
	dlg->m_imc.StopFindHome(axis);
	dlg->m_imc.SetCurHome(axis);
}

void CFindHome::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
/*	if(bShow){
		SetTimer(TIMER_FHOME_ENCP, SHOW_ENCP_TIME, NULL);
	}
	else KillTimer(TIMER_FHOME_ENCP);
	*/
}

void CFindHome::UpdateCtr()
{	
	int i;
	for( i=0; i<g_Naxis; i++){
		GetDlgItem(IDC_BN_AXIS_Z_0 + i)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BN_AXIS_F_0 + i)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BN_STOP_FIND_0 + i)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_ENCP_0 + i)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BN_SET_HOME_0 + i)->ShowWindow(SW_SHOW);
	}
	for(i=g_Naxis; i<MAX_NAXIS; i++){
		GetDlgItem(IDC_BN_AXIS_Z_0 + i)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BN_AXIS_F_0 + i)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BN_STOP_FIND_0 + i)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_ENCP_0 + i)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BN_SET_HOME_0 + i)->ShowWindow(SW_HIDE);
	}
	SetTimer(TIMER_FHOME_ENCP, SHOW_ENCP_TIME, NULL);
}

void CFindHome::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(nIDEvent == TIMER_FHOME_ENCP){
		long encp[MAX_NAXIS];
		dlg->GetCurEncp(encp);
		ShowEncp(encp);
	}
	CDialog::OnTimer(nIDEvent);
}
void CFindHome::ShowEncp(long *encp)
{
	CString str;
	int axis;
	for(int i=0; i<g_Naxis; i++)
	{
		axis = g_factcfg.g_mapAxis[i];
		if(encp[axis] != m_encp[axis]){
			str.Format(_T("%07.2lf"), 1.0*encp[axis]/g_factcfg.distFac[axis]);
			SetDlgItemText(IDC_STATIC_ENCP_0 + i, str);
			m_encp[axis] = encp[axis];
		}
	}
}