// dlg/Pg_Tip.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "Pg_Tip.h"


// CPg_Tip 对话框

IMPLEMENT_DYNAMIC(CPg_Tip, CDialog)

CPg_Tip::CPg_Tip(CWnd* pParent /*=NULL*/)
	: CDialog(CPg_Tip::IDD, pParent)
{

}

CPg_Tip::~CPg_Tip()
{
}

void CPg_Tip::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPg_Tip, CDialog)
END_MESSAGE_MAP()


// CPg_Tip 消息处理程序
void CPg_Tip::SetPrompt(int cmd)
{
	if(cmd == CMD_END)
		SetDlgItemText(IDC_STATIC_TIP, _T("执行到此指令后，程序结束，将继续从程序开始位置执行指令"));
	else if(cmd == CMD_WEND)
		SetDlgItemText(IDC_STATIC_TIP, _T("执行到此指令后，如果未到循环次数，则从循环跳转行开始执行，否则执行循环开始指令的下一条指令。"));
	else 
		SetDlgItemText(IDC_STATIC_TIP, _T(""));
}