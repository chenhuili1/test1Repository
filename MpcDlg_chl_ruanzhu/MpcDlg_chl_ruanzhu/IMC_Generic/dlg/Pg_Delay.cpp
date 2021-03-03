// dlg/Pg_Delay.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "Pg_Delay.h"


// CPg_Delay 对话框

IMPLEMENT_DYNAMIC(CPg_Delay, CDialog)

CPg_Delay::CPg_Delay(CWnd* pParent /*=NULL*/)
	: CDialog(CPg_Delay::IDD, pParent)
{

}

CPg_Delay::~CPg_Delay()
{
}

void CPg_Delay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TIME, m_edit);
}


BEGIN_MESSAGE_MAP(CPg_Delay, CDialog)
END_MESSAGE_MAP()


// CPg_Delay 消息处理程序


long CPg_Delay::GetEditFloat(UINT id, double fac)
{
	WCHAR data[16];
	double dval;
	int len = GetDlgItemText(id, data, 15);
	if(len == 0) return 0;
	data[len] = 0;
	swscanf(data, _T("%lf"),&dval);
	return (long)(dval * fac);
}
void CPg_Delay::UpdateDlg(PROGRAM_DATA*pdata)
{
	CString str;
	str.Format(_T("%.2f"), 1.0*pdata->delay/1000);
	SetDlgItemText(IDC_EDIT_TIME, str );
}
BOOL CPg_Delay::GetProData(PROGRAM_DATA *pdata)
{
	pdata->delay = GetEditFloat(IDC_EDIT_TIME, 1000);
	return TRUE;
}