// dlg/Pg_Linkage.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "Pg_Linkage.h"
#include "IMC_GenericDlg.h"


// CPg_Linkage 对话框

IMPLEMENT_DYNAMIC(CPg_Linkage, CDialog)

CPg_Linkage::CPg_Linkage(CWnd* pParent /*=NULL*/)
	: CDialog(CPg_Linkage::IDD, pParent)
{

}

CPg_Linkage::~CPg_Linkage()
{
}

void CPg_Linkage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_AXIS_0, m_edit[0]);
	DDX_Control(pDX, IDC_EDIT_AXIS_1, m_edit[1]);
	DDX_Control(pDX, IDC_EDIT_AXIS_2, m_edit[2]);
	DDX_Control(pDX, IDC_EDIT_AXIS_3, m_edit[3]);
	DDX_Control(pDX, IDC_EDIT_AXIS_4, m_edit[4]);
	DDX_Control(pDX, IDC_EDIT_AXIS_5, m_edit[5]);
	DDX_Control(pDX, IDC_EDIT_AXIS_6, m_edit[6]);
	DDX_Control(pDX, IDC_EDIT_AXIS_7, m_edit[7]);
	DDX_Control(pDX, IDC_EDIT_AXIS_8, m_edit[8]);
	DDX_Control(pDX, IDC_EDIT_AXIS_9, m_edit[9]);
	DDX_Control(pDX, IDC_EDIT_AXIS_10, m_edit[10]);
	DDX_Control(pDX, IDC_EDIT_AXIS_11, m_edit[11]);
	DDX_Control(pDX, IDC_EDIT_AXIS_12, m_edit[12]);
	DDX_Control(pDX, IDC_EDIT_AXIS_13, m_edit[13]);
	DDX_Control(pDX, IDC_EDIT_AXIS_14, m_edit[14]);
	DDX_Control(pDX, IDC_EDIT_AXIS_15, m_edit[15]);
}


BEGIN_MESSAGE_MAP(CPg_Linkage, CDialog)
	ON_COMMAND_RANGE(IDC_CHECK_AXIS_0, IDC_CHECK_AXIS_15, &CPg_Linkage::OnBnClickedCheckAxis)
	ON_BN_CLICKED(IDC_BUTTON_GET_ENCP, &CPg_Linkage::OnBnClickedButtonGetEncp)
END_MESSAGE_MAP()


// CPg_Linkage 消息处理程序

BOOL CPg_Linkage::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	int i;
	for(i=0; i< g_Naxis; i++)
		SetDlgItemText(IDC_STATIC_UINT_AIXS_0 + i, g_factcfg.Unit[i]);
	for(; i< MAX_NAXIS; i++){
		GetDlgItem(IDC_CHECK_AXIS_0 + i)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_AXIS_0 + i)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_UINT_AIXS_0 + i)->ShowWindow(SW_HIDE);
	}
	
	((CComboBox*)GetDlgItem(IDC_COMBO_SPEED))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_SPEED_RATIO))->SetCurSel(9);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CPg_Linkage::UpdateDlg(PROGRAM_DATA*pdata)
{
	CString str;
	for(int i=0; i<g_Naxis; i++){
		if((pdata->posBit & (1 << i))){
			((CButton*)GetDlgItem(IDC_CHECK_AXIS_0 + i))->SetCheck(1);
			GetDlgItem(IDC_EDIT_AXIS_0 + i)->EnableWindow(TRUE);
			str.Format(_T("%.02f"), 1.0*pdata->pos[i]/*/g_factcfg.distFac[i]*/);
			SetDlgItemText(IDC_EDIT_AXIS_0 + i, str);
		}
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_SPEED))->SetCurSel(pdata->vel);
	((CComboBox*)GetDlgItem(IDC_COMBO_SPEED_RATIO))->SetCurSel(pdata->velRatio);
	((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(pdata->InSel);
}

void CPg_Linkage::OnBnClickedCheckAxis(UINT nId)
{
	// TODO: 在此添加控件通知处理程序代码
	int index = nId - IDC_CHECK_AXIS_0;
	BOOL check = ((CButton*)GetDlgItem(nId))->GetCheck();
	GetDlgItem(IDC_EDIT_AXIS_0 + index)->EnableWindow(check);
}
long CPg_Linkage::GetEditFloat(UINT id, double fac)
{
	WCHAR data[16];
	double dval;
	int len = GetDlgItemText(id, data, 15);
	if(len == 0) return 0;
	data[len] = 0;
	swscanf(data, _T("%lf"),&dval);
	return (long)(dval * fac);
}
double CPg_Linkage::GetEditFloat(UINT id)
{
	WCHAR data[16];
	double dval;
	int len = GetDlgItemText(id, data, 15);
	if(len == 0) return 0;
	data[len] = 0;
	swscanf(data, _T("%lf"),&dval);
	return dval;
}
BOOL CPg_Linkage::GetProData(PROGRAM_DATA *pdata)
{
	pdata->posBit = 0;
	for(int i=0; i< g_Naxis; i++)
	{
		if(((CButton*)GetDlgItem(IDC_CHECK_AXIS_0 + i))->GetCheck()){
			pdata->posBit |= (1 << i);
			pdata->pos[i] = GetEditFloat(IDC_EDIT_AXIS_0 + i/*, g_factcfg.distFac[i]*/);
		}
	}
	pdata->vel = ((CComboBox*)GetDlgItem(IDC_COMBO_SPEED))->GetCurSel();
	pdata->velRatio = ((CComboBox*)GetDlgItem(IDC_COMBO_SPEED_RATIO))->GetCurSel();
	pdata->InSel = ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck();
	return TRUE;
}



void CPg_Linkage::OnBnClickedButtonGetEncp()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	long encp[MAX_NAXIS];
	CString str;
	dlg->GetCurEncp(encp);
	for(int i=0; i< g_Naxis; i++)
	{
		if(((CButton*)GetDlgItem(IDC_CHECK_AXIS_0 + i))->GetCheck()){
			str.Format(_T("%.02f"), IMC_ENCP_SHOW(encp, i));
			SetDlgItemText(IDC_EDIT_AXIS_0 + i, str);
		}
	}
}
