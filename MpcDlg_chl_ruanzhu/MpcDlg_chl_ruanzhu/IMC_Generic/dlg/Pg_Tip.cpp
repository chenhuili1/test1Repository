// dlg/Pg_Tip.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "Pg_Tip.h"


// CPg_Tip �Ի���

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


// CPg_Tip ��Ϣ�������
void CPg_Tip::SetPrompt(int cmd)
{
	if(cmd == CMD_END)
		SetDlgItemText(IDC_STATIC_TIP, _T("ִ�е���ָ��󣬳���������������ӳ���ʼλ��ִ��ָ��"));
	else if(cmd == CMD_WEND)
		SetDlgItemText(IDC_STATIC_TIP, _T("ִ�е���ָ������δ��ѭ�����������ѭ����ת�п�ʼִ�У�����ִ��ѭ����ʼָ�����һ��ָ�"));
	else 
		SetDlgItemText(IDC_STATIC_TIP, _T(""));
}