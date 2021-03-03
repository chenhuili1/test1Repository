// dlg/Pg_Input.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "Pg_Input.h"


// CPg_Input 对话框

IMPLEMENT_DYNAMIC(CPg_Input, CDialog)

CPg_Input::CPg_Input(CWnd* pParent /*=NULL*/)
	: CDialog(CPg_Input::IDD, pParent)
	, m_inSel(FALSE)
{

}

CPg_Input::~CPg_Input()
{
}

void CPg_Input::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_inSel);
	DDX_Control(pDX, IDC_EDIT_TIME, m_edit[0]);
	DDX_Control(pDX, IDC_EDIT_LINE, m_edit[1]);
}


BEGIN_MESSAGE_MAP(CPg_Input, CDialog)
END_MESSAGE_MAP()


// CPg_Input 消息处理程序


BOOL CPg_Input::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	((CComboBox*)GetDlgItem(IDC_COMBO_ACTION))->SetCurSel(0);
	SetDlgItemInt(IDC_EDIT_TIME,5);
	CString str;
	for(int i=0; i<INPUT_NUM; i++){
		str.Format(_T("%d"), i+1);
		((CComboBox*)GetDlgItem(IDC_COMBO_INPUT))->AddString(str);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_INPUT))->SetCurSel(0);

	((CComboBox*)GetDlgItem(IDC_COMBO_ACTION3))->AddString(_T("无"));
	for(int i=0; i<g_warnNum; i++){
		((CComboBox*)GetDlgItem(IDC_COMBO_ACTION3))->AddString(g_warn[i].name);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CPg_Input::UpdateDlg(PROGRAM_DATA*pdata)
{
#ifdef CHANGE_DATA_0
	((CComboBox*)GetDlgItem(IDC_COMBO_INPUT))->SetCurSel(pdata->InputBit);
	((CComboBox*)GetDlgItem(IDC_COMBO_ACTION))->SetCurSel(pdata->InputVal); 
#else
	((CComboBox*)GetDlgItem(IDC_COMBO_INPUT))->SetCurSel((pdata->Input>>8) & 0xFF);
	((CComboBox*)GetDlgItem(IDC_COMBO_ACTION))->SetCurSel((pdata->Input & 0xFF)); 
#endif
	((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(pdata->homeMode);//是否提示报警
	if(pdata->homeMode)
		((CComboBox*)GetDlgItem(IDC_COMBO_ACTION3))->SetCurSel(pdata->homeBit); 
	else
		((CComboBox*)GetDlgItem(IDC_COMBO_ACTION3))->SetCurSel(0); 
	CString str;
	str.Format(_T("%.2f"), 1.0*pdata->delay/1000);
	SetDlgItemText(IDC_EDIT_TIME, str );
	m_inSel = pdata->InSel & 0xFF;
	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck((pdata->InSel>>8) & 0xFF);
	SetDlgItemInt(IDC_EDIT_LINE, pdata->jumpLine);
	UpdateData(FALSE);
}
long CPg_Input::GetEditFloat(UINT id, double fac)
{
	WCHAR data[16];
	double dval;
	int len = GetDlgItemText(id, data, 15);
	if(len == 0) return 0;
	data[len] = 0;
	swscanf(data, _T("%lf"),&dval);
	return (long)(dval * fac);
}
BOOL CPg_Input::GetProData(PROGRAM_DATA *pdata)
{
	UpdateData();
#ifdef CHANGE_DATA_0
	int sel = ((CComboBox*)GetDlgItem(IDC_COMBO_INPUT))->GetCurSel();
	pdata->InputBit = sel;//高位为IO，
	sel = ((CComboBox*)GetDlgItem(IDC_COMBO_ACTION))->GetCurSel();
	pdata->InputVal = sel;
#else
	int sel = ((CComboBox*)GetDlgItem(IDC_COMBO_INPUT))->GetCurSel();
	pdata->Input = (sel <<8) & 0xFF00;//高位为IO，
	sel = ((CComboBox*)GetDlgItem(IDC_COMBO_ACTION))->GetCurSel();
	pdata->Input |= sel;
#endif
	pdata->delay = GetEditFloat(IDC_EDIT_TIME, 1000);
	pdata->jumpLine = GetDlgItemInt(IDC_EDIT_LINE);
	pdata->InSel = m_inSel;
	BOOL check = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
	if(check) pdata->InSel |= 0xFF00; //高位为是否开灯报警，
	pdata->homeMode = ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck();//是否提示报警
	if(pdata->homeMode)
		pdata->homeBit = ((CComboBox*)GetDlgItem(IDC_COMBO_ACTION3))->GetCurSel(); 
	else
		pdata->homeBit = 0; 
	return TRUE;
}