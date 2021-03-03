// dlg/Pg_Wait.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "Pg_Wait.h" 
#include "IMC_GenericDlg.h"


// CPg_Wait �Ի���

IMPLEMENT_DYNAMIC(CPg_Wait, CDialog)

CPg_Wait::CPg_Wait(CWnd* pParent /*=NULL*/)
	: CDialog(CPg_Wait::IDD, pParent)
	, m_wait(FALSE)
{

}

CPg_Wait::~CPg_Wait()
{
}

void CPg_Wait::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_wait);
}


BEGIN_MESSAGE_MAP(CPg_Wait, CDialog)
END_MESSAGE_MAP()


// CPg_Wait ��Ϣ�������
BOOL CPg_Wait::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CPg_Wait::UpdateDlg(PROGRAM_DATA*pdata)
{
	m_wait = pdata->WTbit;
	UpdateData(FALSE);
}
BOOL CPg_Wait::GetProData(PROGRAM_DATA *pdata)
{
	UpdateData(TRUE);
	pdata->WTbit = m_wait;
	return TRUE;
}
