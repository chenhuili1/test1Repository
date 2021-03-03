// dlg/EncpSt6.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "EncpSt6.h"
#include "IMC_GenericDlg.h"


// CEncpSt6 对话框

IMPLEMENT_DYNAMIC(CEncpSt6, CDialog)

CEncpSt6::CEncpSt6(CWnd* pParent /*=NULL*/)
	: CDialog(CEncpSt6::IDD, pParent)
{

}

CEncpSt6::~CEncpSt6()
{
}

void CEncpSt6::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEncpSt6, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CEncpSt6 消息处理程序

BOOL CEncpSt6::OnInitDialog()
{
	CDialog::OnInitDialog();

CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	IMC_GetParam32(dlg->m_imc.m_handle, ticksLoc, (PVOID)&CurTickCnt, SEL_IFIFO);
	OldTickCnt = CurTickCnt;


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CEncpSt6::SetEncpTimer(BOOL isRun)
{
	if(isRun)
		;//SetTimer(TIMER_MAIN_ENCP, SHOW_ENCP_TIME, NULL);
	else
		KillTimer(TIMER_MAIN_ENCP);
}

void CEncpSt6::OnTimer(UINT_PTR nIDEvent)
{
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	if(nIDEvent == TIMER_MAIN_ENCP)
	{
		long encp[MAX_NAXIS];
		dlg->GetCurEncp(encp);
        //dlg->m_imc.GetEncp(m_encp, dlg->m_axis, g_Naxis);


		IMC_GetParam32(dlg->m_imc.m_handle, ticksLoc, (PVOID)&CurTickCnt, SEL_IFIFO);
			
		ShowEncp(encp);


		
	}
	CDialog::OnTimer(nIDEvent);
}

void CEncpSt6::ShowEncp(long *encp)
{
	CString str;
	int axis, num;
	static char Ach[MAX_NAXIS] = {'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M'};
	if(g_Naxis > 6) num = 6;
	else num = g_Naxis;


	DeltaTickCnt = CurTickCnt -OldTickCnt;
	OldTickCnt = CurTickCnt;


	
	for(int i=0; i<num; i++)
	{
		axis = g_factcfg.g_mapAxis[i];
		//if(encp[axis] != m_encp[axis])
			{
		//	str.Format(_T("%c:%07.2lf"), Ach[i], 1.0*encp[axis]/g_factcfg.distFac[i]);

			m_encpDelta[axis] =encp[axis] -m_encp[axis] ;


			//m_encpDelta[axis] = m_encpDelta[axis]*(1000.0/DeltaTickCnt);
			 m_encpDelta[axis] = m_encpDelta[axis]*(1000.0/40.0);
		

			if(axis==4||axis==5)
				str.Format(_T("%c Angle: %.3f"), Ach[i], encp[axis]*360.0/(4*5000.0));
			else
				str.Format(_T("%c: %.3f,V=%.3f"), Ach[i], IMC_ENCP_SHOW(encp, i), IMC_ENCP_SHOW(m_encpDelta, i));


		
			SetDlgItemText(IDC_STATIC_ENCP_A0 + i, str);


			SysStatusObj.ActPos_OuterEncoder[axis] = encp[axis];
			m_encp[axis] = encp[axis];
		}
	}

	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	double curRealKB_F_Rate = dlg->m_imc.GetRealtimeFeedRate()/65536.0;

	str.Format(_T("%07.2lf"),curRealKB_F_Rate);		
	SetDlgItemText(IDC_STATIC_RealFeedrate, str);


	

}
