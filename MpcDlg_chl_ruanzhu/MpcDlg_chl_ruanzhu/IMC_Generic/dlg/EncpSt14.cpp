// dlg/EncpSt14.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "EncpSt14.h"
#include "IMC_GenericDlg.h"


// CEncpSt14 �Ի���

IMPLEMENT_DYNAMIC(CEncpSt14, CDialog)

CEncpSt14::CEncpSt14(CWnd* pParent /*=NULL*/)
	: CDialog(CEncpSt14::IDD, pParent)
{

}

CEncpSt14::~CEncpSt14()
{
}

void CEncpSt14::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEncpSt14, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CEncpSt14 ��Ϣ�������

BOOL CEncpSt14::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CEncpSt14::SetEncpTimer(BOOL isRun)
{
	if(isRun)
		SetTimer(TIMER_MAIN_ENCP, SHOW_ENCP_TIME, NULL);
	else
		KillTimer(TIMER_MAIN_ENCP);
}

void CEncpSt14::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	if(nIDEvent == TIMER_MAIN_ENCP)
	{
		long encp[MAX_NAXIS];
		dlg->GetCurEncp(encp);
		ShowEncp(encp);
	}
	CDialog::OnTimer(nIDEvent);
}

void CEncpSt14::ShowEncp(long *encp)
{
	CString str;
	int axis, num;
	static char Ach[MAX_NAXIS] = {'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M'};
	if(g_Naxis > 14) num = 14;
	else num = g_Naxis;
	for(int i=0; i<num; i++)
	{
		axis = g_factcfg.g_mapAxis[i];
		if(encp[axis] != m_encp[axis]){
		//	str.Format(_T("%c:%07.2lf"), Ach[i], 1.0*encp[axis]/g_factcfg.distFac[i]);
			str.Format(_T("%c: %07.2lf"), Ach[i], IMC_ENCP_SHOW(encp, i));
			SetDlgItemText(IDC_STATIC_ENCP_A0 + i, str);
			m_encp[axis] = encp[axis];
		}
	}
}
