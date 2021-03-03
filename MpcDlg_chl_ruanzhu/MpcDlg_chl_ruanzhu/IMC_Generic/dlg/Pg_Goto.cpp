// dlg/Pg_Goto.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "Pg_Goto.h"


// CPg_Goto �Ի���

IMPLEMENT_DYNAMIC(CPg_Goto, CDialog)

CPg_Goto::CPg_Goto(CWnd* pParent /*=NULL*/)
	: CDialog(CPg_Goto::IDD, pParent)
{

}

CPg_Goto::~CPg_Goto()
{
}

void CPg_Goto::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_GOTO_LINE, m_edit);
}


BEGIN_MESSAGE_MAP(CPg_Goto, CDialog)
END_MESSAGE_MAP()


// CPg_Goto ��Ϣ�������
/*
void CPg_Goto::SetPrompt(int cmd)
{
	m_cmd = cmd;
	if(cmd == CMD_JUMP)
		SetDlgItemText(IDC_STATIC_PROMPT, _T("��ת���ڼ���ָ��:"));
	else if(cmd == CMD_DELAY)
		SetDlgItemText(IDC_STATIC_PROMPT, _T("��ʱʱ��(��):"));
}
*/
void CPg_Goto::UpdateDlg(PROGRAM_DATA*pdata)
{
	SetDlgItemInt(IDC_EDIT_GOTO_LINE, pdata->jumpLine);
}
BOOL CPg_Goto::GetProData(PROGRAM_DATA *pdata)
{
	pdata->jumpLine = (DWORD)GetDlgItemInt(IDC_EDIT_GOTO_LINE);
	return TRUE;
}