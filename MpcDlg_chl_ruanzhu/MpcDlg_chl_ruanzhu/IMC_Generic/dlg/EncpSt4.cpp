// dlg/EncpSt4.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "EncpSt4.h"
#include "IMC_GenericDlg.h"


// CEncpSt4 对话框

IMPLEMENT_DYNAMIC(CEncpSt4, CDialog)

CEncpSt4::CEncpSt4(CWnd* pParent /*=NULL*/)
	: CDialog(CEncpSt4::IDD, pParent)
{

}

CEncpSt4::~CEncpSt4()
{
}

void CEncpSt4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEncpSt4, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CEncpSt4 消息处理程序

BOOL CEncpSt4::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CEncpSt4::SetEncpTimer(BOOL isRun)
{
	if(isRun)
		SetTimer(TIMER_MAIN_ENCP, SHOW_ENCP_TIME, NULL);
	else
		KillTimer(TIMER_MAIN_ENCP);
}

void CEncpSt4::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	if(nIDEvent == TIMER_MAIN_ENCP)
	{
		long encp[MAX_NAXIS];
		dlg->GetCurEncp(encp);
		ShowEncp(encp);
	}
	CDialog::OnTimer(nIDEvent);
}

void CEncpSt4::ShowEncp(long *encp)
{
	CString str;
	int axis, num;
	static char Ach[MAX_NAXIS] = {'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M'};
	if(g_Naxis > 12) num = 12;
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
