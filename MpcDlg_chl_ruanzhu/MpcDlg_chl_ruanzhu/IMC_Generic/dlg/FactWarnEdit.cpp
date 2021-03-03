// dlg/FactWarnEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "FactWarnEdit.h"


// CFactWarnEdit �Ի���

IMPLEMENT_DYNAMIC(CFactWarnEdit, CDialog)

CFactWarnEdit::CFactWarnEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CFactWarnEdit::IDD, pParent)
{
	memset(&m_warnInfo, 0, sizeof(FACT_WARN));

}

CFactWarnEdit::~CFactWarnEdit()
{
}

void CFactWarnEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit[0]);
	DDX_Control(pDX, IDC_EDIT2, m_edit[1]);
}


BEGIN_MESSAGE_MAP(CFactWarnEdit, CDialog)
	ON_BN_CLICKED(IDOK, &CFactWarnEdit::OnBnClickedOk)
END_MESSAGE_MAP()


// CFactWarnEdit ��Ϣ�������


BOOL CFactWarnEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_edit[0].SetFloatFlag(EDIT_STRING);
	m_edit[1].SetFloatFlag(EDIT_STRING);

	CString str;
	str.Format(_T("%s"),  m_warnInfo.name);
	SetDlgItemText(IDC_EDIT1, str);
	str.Format(_T("%s"),  m_warnInfo.warn);
	SetDlgItemText(IDC_EDIT2, str);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CFactWarnEdit::SetWarnInfo(FACT_WARN * info)
{
	if(info)
		memcpy(&m_warnInfo, info, sizeof(FACT_WARN));
}
void CFactWarnEdit::GetWarnInfo(FACT_WARN * info)
{
	if(info)
		memcpy(info, &m_warnInfo, sizeof(FACT_WARN));
}


void CFactWarnEdit::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int len;
	len = GetDlgItemText(IDC_EDIT1, m_warnInfo.name, 7);
	m_warnInfo.name[len] = 0;
	len = GetDlgItemText(IDC_EDIT2, m_warnInfo.warn, 255);
	m_warnInfo.warn[len] = 0;
	
	OnOK();
}
