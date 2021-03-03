// dlg/Pg_Output.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "Pg_Output.h"


// CPg_Output 对话框

IMPLEMENT_DYNAMIC(CPg_Output, CDialog)

CPg_Output::CPg_Output(CWnd* pParent /*=NULL*/)
	: CDialog(CPg_Output::IDD, pParent)
{

}

CPg_Output::~CPg_Output()
{
}

void CPg_Output::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TIME, m_edit);
}


BEGIN_MESSAGE_MAP(CPg_Output, CDialog)
END_MESSAGE_MAP()


// CPg_Output 消息处理程序
BOOL CPg_Output::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString str;
	for(int i=0; i<OUTPUT_NUM; i++){
		str.Format(_T("%d"), i+1);
		((CComboBox*)GetDlgItem(IDC_COMBO_OUTPUT))->AddString(str);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_OUTPUT))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_ACTION))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_ACTION2))->SetCurSel(1);
	SetDlgItemInt(IDC_EDIT_TIME,0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

long CPg_Output::GetEditFloat(UINT id, double fac)
{
	WCHAR data[16];
	double dval;
	int len = GetDlgItemText(id, data, 15);
	if(len == 0) return 0;
	data[len] = 0;
	swscanf(data, _T("%lf"),&dval);
	return (long)(dval * fac);
}
void CPg_Output::UpdateDlg(PROGRAM_DATA*pdata)
{
#ifdef CHANGE_DATA_0
	((CComboBox*)GetDlgItem(IDC_COMBO_OUTPUT))->SetCurSel(pdata->OutputBit);
	((CComboBox*)GetDlgItem(IDC_COMBO_ACTION))->SetCurSel(pdata->OutputVal);
#else
	((CComboBox*)GetDlgItem(IDC_COMBO_OUTPUT))->SetCurSel((pdata->Output>>8) & 0xFF);
	((CComboBox*)GetDlgItem(IDC_COMBO_ACTION))->SetCurSel(pdata->Output & 0xFF);
#endif
	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(pdata->InSel & 0xFF);
	((CComboBox*)GetDlgItem(IDC_COMBO_ACTION2))->SetCurSel((pdata->InSel>>8) & 0xFF);
	CString str;
	str.Format(_T("%.2f"), 1.0*pdata->delay/1000);
	SetDlgItemText(IDC_EDIT_TIME, str );
}
BOOL CPg_Output::GetProData(PROGRAM_DATA *pdata)
{
#ifdef CHANGE_DATA_0
	int sel = ((CComboBox*)GetDlgItem(IDC_COMBO_OUTPUT))->GetCurSel();
	pdata->OutputBit = sel;//高位为IO，
	sel = ((CComboBox*)GetDlgItem(IDC_COMBO_ACTION))->GetCurSel();
	pdata->OutputVal = sel;
#else
	int sel = ((CComboBox*)GetDlgItem(IDC_COMBO_OUTPUT))->GetCurSel();
	pdata->Output = (sel <<8) & 0xFF00;//高位为IO，
	sel = ((CComboBox*)GetDlgItem(IDC_COMBO_ACTION))->GetCurSel();
	pdata->Output |= sel;
#endif
	pdata->InSel = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
	sel = ((CComboBox*)GetDlgItem(IDC_COMBO_ACTION2))->GetCurSel();
	pdata->InSel |= (sel <<8) & 0xFF00;
	pdata->delay = GetEditFloat(IDC_EDIT_TIME, 1000);
	return TRUE;
}

