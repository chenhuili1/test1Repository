// dlg/Pg_Pos.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "Pg_Pos.h"
#include "IMC_GenericDlg.h"


// CPg_Pos 对话框

IMPLEMENT_DYNAMIC(CPg_Pos, CDialog)

CPg_Pos::CPg_Pos(CWnd* pParent /*=NULL*/)
	: CDialog(CPg_Pos::IDD, pParent)
{

}

CPg_Pos::~CPg_Pos()
{
}

void CPg_Pos::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_AXIS_0, m_edit);
}


BEGIN_MESSAGE_MAP(CPg_Pos, CDialog)
	ON_CBN_SELENDOK(IDC_COMBO_AXIS, &CPg_Pos::OnCbnSelendokComboAxis)
	ON_BN_CLICKED(IDC_BUTTON_GET_ENCP, &CPg_Pos::OnBnClickedButtonGetEncp)
	ON_BN_CLICKED(IDC_CHECK2, &CPg_Pos::OnBnClickedCheck2)
END_MESSAGE_MAP()


// CPg_Pos 消息处理程序
BOOL CPg_Pos::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	int i;

	for(i=0; i< g_Naxis; i++)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_AXIS))->AddString(g_AxisName[i]);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_AXIS))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_SPEED))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_SPEED_RATIO))->SetCurSel(9);
	SetDlgItemText(IDC_STATIC_UINT_AIXS_0, g_factcfg.Unit[0]);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CPg_Pos::UpdateDlg(PROGRAM_DATA*pdata)
{
	CString str;
	((CComboBox*)GetDlgItem(IDC_COMBO_AXIS))->SetCurSel(pdata->axis);
	((CComboBox*)GetDlgItem(IDC_COMBO_SPEED))->SetCurSel(pdata->vel);
	((CComboBox*)GetDlgItem(IDC_COMBO_SPEED_RATIO))->SetCurSel(pdata->velRatio);
	str.Format(_T("%.02f"), 1.0*pdata->pos[0]/*/g_factcfg.distFac[pdata->axis]*/);
	SetDlgItemText(IDC_EDIT_AXIS_0, str);
	SetDlgItemText(IDC_STATIC_UINT_AIXS_0, g_factcfg.Unit[pdata->axis]);
//	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(pdata->isWT);
	((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(pdata->InSel);
}
BOOL CPg_Pos::GetProData(PROGRAM_DATA *pdata)
{
	pdata->vel = ((CComboBox*)GetDlgItem(IDC_COMBO_SPEED))->GetCurSel();
	pdata->velRatio = ((CComboBox*)GetDlgItem(IDC_COMBO_SPEED_RATIO))->GetCurSel();
	pdata->axis = ((CComboBox*)GetDlgItem(IDC_COMBO_AXIS))->GetCurSel();
	pdata->pos[0] = GetEditFloat(IDC_EDIT_AXIS_0/*, g_factcfg.distFac[pdata->axis]*/);
//	pdata->isWT = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
	pdata->InSel = ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck();
	return TRUE;
}

long CPg_Pos::GetEditFloat(UINT id, double fac)
{
	WCHAR data[16];
	double dval;
	int len = GetDlgItemText(id, data, 15);
	if(len == 0) return 0;
	data[len] = 0;
	swscanf(data, _T("%lf"),&dval);
	return (long)(dval * fac);
}
double CPg_Pos::GetEditFloat(UINT id)
{
	WCHAR data[16];
	double dval;
	int len = GetDlgItemText(id, data, 15);
	if(len == 0) return 0;
	data[len] = 0;
	swscanf(data, _T("%lf"),&dval);
	return dval;
}

void CPg_Pos::OnCbnSelendokComboAxis()
{
	// TODO: 在此添加控件通知处理程序代码
	int axis = ((CComboBox*)GetDlgItem(IDC_COMBO_AXIS))->GetCurSel();
	SetDlgItemText(IDC_STATIC_UINT_AIXS_0, g_factcfg.Unit[axis]);
}


void CPg_Pos::OnBnClickedButtonGetEncp()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	long encp[MAX_NAXIS];
	CString str;
	int axis = ((CComboBox*)GetDlgItem(IDC_COMBO_AXIS))->GetCurSel();
	dlg->GetCurEncp(encp);
	str.Format(_T("%.02f"), IMC_ENCP_SHOW(encp, axis));
	SetDlgItemText(IDC_EDIT_AXIS_0, str);
}

void CPg_Pos::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	int sel = ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck();
	if(sel){
		GetDlgItem(IDC_BUTTON_GET_ENCP)->ShowWindow(SW_HIDE);
	}else
		GetDlgItem(IDC_BUTTON_GET_ENCP)->ShowWindow(SW_SHOW);
}
