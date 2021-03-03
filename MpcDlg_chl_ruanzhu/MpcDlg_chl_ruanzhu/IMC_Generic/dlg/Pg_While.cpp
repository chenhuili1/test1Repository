// dlg/Pg_While.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "Pg_While.h" 


// CPg_While 对话框

IMPLEMENT_DYNAMIC(CPg_While, CDialog)

CPg_While::CPg_While(CWnd* pParent /*=NULL*/)
	: CDialog(CPg_While::IDD, pParent)
{

}

CPg_While::~CPg_While()
{
}

void CPg_While::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LINE, m_edit[0]);
	DDX_Control(pDX, IDC_EDIT_NUM, m_edit[1]);
}


BEGIN_MESSAGE_MAP(CPg_While, CDialog)
END_MESSAGE_MAP()


// CPg_While 消息处理程序

void CPg_While::UpdateDlg(PROGRAM_DATA*pdata)
{
	SetDlgItemInt(IDC_EDIT_LINE, pdata->jumpLine);
	SetDlgItemInt(IDC_EDIT_NUM, pdata->loopNum);
}
BOOL CPg_While::GetProData(PROGRAM_DATA *pdata)
{
	pdata->jumpLine = (DWORD)GetDlgItemInt(IDC_EDIT_LINE);
	pdata->loopNum = (DWORD)GetDlgItemInt(IDC_EDIT_NUM);
	return TRUE;
}