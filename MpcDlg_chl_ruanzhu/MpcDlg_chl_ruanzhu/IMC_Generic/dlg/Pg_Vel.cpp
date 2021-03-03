// dlg/Pg_Vel.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "Pg_Vel.h" 


// CPg_Vel 对话框

IMPLEMENT_DYNAMIC(CPg_Vel, CDialog)

CPg_Vel::CPg_Vel(CWnd* pParent /*=NULL*/)
	: CDialog(CPg_Vel::IDD, pParent)
{

}

CPg_Vel::~CPg_Vel()
{
}

void CPg_Vel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPg_Vel, CDialog)
END_MESSAGE_MAP()


// CPg_Vel 消息处理程序
BOOL CPg_Vel::OnInitDialog()
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
	((CComboBox*)GetDlgItem(IDC_COMBO_DIR))->SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CPg_Vel::UpdateDlg(PROGRAM_DATA*pdata)
{
	((CComboBox*)GetDlgItem(IDC_COMBO_AXIS))->SetCurSel(pdata->axis);
	((CComboBox*)GetDlgItem(IDC_COMBO_SPEED))->SetCurSel(pdata->vel);
	((CComboBox*)GetDlgItem(IDC_COMBO_SPEED_RATIO))->SetCurSel(pdata->velRatio);
	((CComboBox*)GetDlgItem(IDC_COMBO_DIR))->SetCurSel(pdata->dir);
}
BOOL CPg_Vel::GetProData(PROGRAM_DATA *pdata)
{
	pdata->vel = ((CComboBox*)GetDlgItem(IDC_COMBO_SPEED))->GetCurSel();
	pdata->velRatio = ((CComboBox*)GetDlgItem(IDC_COMBO_SPEED_RATIO))->GetCurSel();
	pdata->axis = ((CComboBox*)GetDlgItem(IDC_COMBO_AXIS))->GetCurSel();
	pdata->dir = ((CComboBox*)GetDlgItem(IDC_COMBO_DIR))->GetCurSel();
	return TRUE;
}