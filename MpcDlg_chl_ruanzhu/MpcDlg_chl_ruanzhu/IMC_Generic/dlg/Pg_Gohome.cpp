// dlg/Pg_Gohome.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "Pg_Gohome.h"


// CPg_Gohome 对话框

IMPLEMENT_DYNAMIC(CPg_Gohome, CDialog)

CPg_Gohome::CPg_Gohome(CWnd* pParent /*=NULL*/)
	: CDialog(CPg_Gohome::IDD, pParent)
	, m_mode(FALSE)
{

}

CPg_Gohome::~CPg_Gohome()
{
}

void CPg_Gohome::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_mode);
}


BEGIN_MESSAGE_MAP(CPg_Gohome, CDialog)
	ON_COMMAND_RANGE(IDC_CHECK1, IDC_CHECK16, &CPg_Gohome::OnBnClickedCheck)
END_MESSAGE_MAP()


// CPg_Gohome 消息处理程序
BOOL CPg_Gohome::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CComboBox *pc;
	int i;
	CString str;
	for(i=0; i<g_Naxis; i++)
	{
		pc = (CComboBox*) GetDlgItem(IDC_COMBO_SORT_0 + i);
		for(int k=0; k<g_Naxis; k++){
			str.Format(_T("%d"), k+1);
			pc->AddString(str);
		}
	}
	for(; i< MAX_NAXIS; i++){
		GetDlgItem(IDC_CHECK1 + i)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_SORT_0 + i)->ShowWindow(SW_HIDE);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_SPEED))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_SPEED_RATIO))->SetCurSel(9);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CPg_Gohome::UpdateDlg(PROGRAM_DATA*pdata)
{
	m_mode = pdata->homeMode;
	for(int i=0; i< g_Naxis; i++)
	{
		if(pdata->homeBit & (1 << i)){
			((CButton*)GetDlgItem(IDC_CHECK1 + i))->SetCheck(1);
			((CComboBox*) GetDlgItem(IDC_COMBO_SORT_0 + i))->SetCurSel(pdata->homeSort[i]);
			GetDlgItem(IDC_COMBO_SORT_0 + i)->EnableWindow(TRUE);
		}
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_SPEED))->SetCurSel(pdata->vel);
	((CComboBox*)GetDlgItem(IDC_COMBO_SPEED_RATIO))->SetCurSel(pdata->velRatio);
	UpdateData(FALSE);
}

void CPg_Gohome::OnBnClickedCheck(UINT nId)
{
	// TODO: 在此添加控件通知处理程序代码
	int index = nId - IDC_CHECK1;
	BOOL check = ((CButton*)GetDlgItem(nId))->GetCheck();
	if(check)
		((CComboBox*) GetDlgItem(IDC_COMBO_SORT_0 + index))->SetCurSel(0);
	else
		((CComboBox*) GetDlgItem(IDC_COMBO_SORT_0 + index))->SetCurSel(-1);
	GetDlgItem(IDC_COMBO_SORT_0 + index)->EnableWindow(check);
}

BOOL CPg_Gohome::GetProData(PROGRAM_DATA *pdata)
{
	UpdateData();
	pdata->homeMode = m_mode;
	pdata->homeBit = 0;
	for(int i=0; i< g_Naxis; i++)
	{
		if(((CButton*)GetDlgItem(IDC_CHECK1 + i))->GetCheck()){
			pdata->homeBit |= (1 << i);
			pdata->homeSort[i] = (BYTE)((CComboBox*) GetDlgItem(IDC_COMBO_SORT_0 + i))->GetCurSel();
			if(pdata->homeSort[i] < 0) return FALSE;
		}
	}
	pdata->vel = ((CComboBox*)GetDlgItem(IDC_COMBO_SPEED))->GetCurSel();
	pdata->velRatio = ((CComboBox*)GetDlgItem(IDC_COMBO_SPEED_RATIO))->GetCurSel();
	return TRUE;
}

