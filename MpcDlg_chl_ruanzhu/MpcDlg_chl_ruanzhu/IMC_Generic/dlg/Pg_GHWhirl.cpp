// dlg/Pg_Gohome.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "Pg_GHWhirl.h"


// CPg_GHWhirl 对话框

IMPLEMENT_DYNAMIC(CPg_GHWhirl, CDialog)

CPg_GHWhirl::CPg_GHWhirl(CWnd* pParent /*=NULL*/)
	: CDialog(CPg_GHWhirl::IDD, pParent)
{

}

CPg_GHWhirl::~CPg_GHWhirl()
{
}

void CPg_GHWhirl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPg_GHWhirl, CDialog)
END_MESSAGE_MAP()


// CPg_GHWhirl 消息处理程序
BOOL CPg_GHWhirl::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	int i;
	for(i=0; i<g_Naxis; i++)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_AXIS))->AddString(g_AxisName[i]);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_AXIS))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_DIR))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_RISEEDGE))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_DIR2))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_RISEEDGE2))->SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CPg_GHWhirl::UpdateDlg(PROGRAM_DATA*pdata)
{
	((CComboBox*)GetDlgItem(IDC_COMBO_AXIS))->SetCurSel(pdata->homeMode);
	((CComboBox*)GetDlgItem(IDC_COMBO_DIR))->SetCurSel(pdata->homeBit & 0xFF);
	((CComboBox*)GetDlgItem(IDC_COMBO_RISEEDGE))->SetCurSel((pdata->homeBit >> 8)  & 0xFF);
	((CComboBox*)GetDlgItem(IDC_COMBO_DIR2))->SetCurSel((pdata->homeBit >> 16)  & 0xFF);
	((CComboBox*)GetDlgItem(IDC_COMBO_RISEEDGE2))->SetCurSel((pdata->homeBit >> 24)  & 0xFF);
}

BOOL CPg_GHWhirl::GetProData(PROGRAM_DATA *pdata)
{
	int sel;
	pdata->homeMode = ((CComboBox*)GetDlgItem(IDC_COMBO_AXIS))->GetCurSel();
	pdata->homeBit = ((CComboBox*)GetDlgItem(IDC_COMBO_DIR))->GetCurSel();
	sel = ((CComboBox*)GetDlgItem(IDC_COMBO_RISEEDGE))->GetCurSel();
	pdata->homeBit |= (sel << 8) & 0x0000FF00;
	sel = ((CComboBox*)GetDlgItem(IDC_COMBO_DIR2))->GetCurSel();
	pdata->homeBit |= (sel << 16) & 0x00FF0000;
	sel = ((CComboBox*)GetDlgItem(IDC_COMBO_RISEEDGE2))->GetCurSel();
	pdata->homeBit |= (sel << 24) & 0xFF000000;
	return TRUE;
}

