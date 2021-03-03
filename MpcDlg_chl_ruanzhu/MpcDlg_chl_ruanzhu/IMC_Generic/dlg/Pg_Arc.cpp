// dlg/Pg_Arc.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "Pg_Arc.h"

#include "IMC_GenericDlg.h"

// CPg_Arc 对话框

IMPLEMENT_DYNAMIC(CPg_Arc, CDialog)

CPg_Arc::CPg_Arc(CWnd* pParent /*=NULL*/)
	: CDialog(CPg_Arc::IDD, pParent)
{

}

CPg_Arc::~CPg_Arc()
{
}

void CPg_Arc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ARC_AXIS_0, m_edit[0]);
	DDX_Control(pDX, IDC_EDIT_ARC_AXIS_1, m_edit[1]);
	DDX_Control(pDX, IDC_EDIT_ARC_AXIS_2, m_edit[2]);
	DDX_Control(pDX, IDC_EDIT_ARC_AXIS_3, m_edit[3]);
	DDX_Control(pDX, IDC_EDIT_ARC_AXIS_4, m_edit[4]);
	DDX_Control(pDX, IDC_EDIT_ARC_AXIS_5, m_edit[5]);
	DDX_Control(pDX, IDC_EDIT_AXIS_0, m_edit[6]);
	DDX_Control(pDX, IDC_EDIT_AXIS_1, m_edit[7]);
	DDX_Control(pDX, IDC_EDIT_AXIS_2, m_edit[8]);
	DDX_Control(pDX, IDC_EDIT_AXIS_3, m_edit[9]);
	DDX_Control(pDX, IDC_EDIT_AXIS_4, m_edit[10]);
	DDX_Control(pDX, IDC_EDIT_AXIS_5, m_edit[11]);
	DDX_Control(pDX, IDC_EDIT_AXIS_6, m_edit[12]);
	DDX_Control(pDX, IDC_EDIT_AXIS_7, m_edit[13]);
	DDX_Control(pDX, IDC_EDIT_AXIS_8, m_edit[14]);
	DDX_Control(pDX, IDC_EDIT_AXIS_9, m_edit[15]);
	DDX_Control(pDX, IDC_EDIT_AXIS_10, m_edit[16]);
	DDX_Control(pDX, IDC_EDIT_AXIS_11, m_edit[17]);
	DDX_Control(pDX, IDC_EDIT_AXIS_12, m_edit[18]);
	DDX_Control(pDX, IDC_EDIT_AXIS_13, m_edit[19]);
	DDX_Control(pDX, IDC_EDIT_AXIS_14, m_edit[20]);
	DDX_Control(pDX, IDC_EDIT_AXIS_15, m_edit[21]);
}


BEGIN_MESSAGE_MAP(CPg_Arc, CDialog)
	ON_COMMAND_RANGE(IDC_CHECK_AXIS_0, IDC_CHECK_AXIS_15, &CPg_Arc::OnBnClickedCheckAxis)
	ON_CBN_SELENDOK(IDC_COMBO_ARC_AXIS_0, &CPg_Arc::OnCbnSelendokComboArcAxis0)
	ON_CBN_SELENDOK(IDC_COMBO_ARC_AXIS_1, &CPg_Arc::OnCbnSelendokComboArcAxis1)
	ON_BN_CLICKED(IDC_BUTTON_GET_ENCP, &CPg_Arc::OnBnClickedButtonGetEncp)
	ON_BN_CLICKED(IDC_BUTTON_GET_ENCP1, &CPg_Arc::OnBnClickedButtonGetEncp1)
	ON_BN_CLICKED(IDC_BUTTON_GET_ENCP2, &CPg_Arc::OnBnClickedButtonGetEncp2)
	ON_BN_CLICKED(IDC_BUTTON_GET_ENCP3, &CPg_Arc::OnBnClickedButtonGetEncp3)
END_MESSAGE_MAP()


// CPg_Arc 消息处理程序

BOOL CPg_Arc::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	int i;
	for(i=0; i< 6; i++)
		SetDlgItemText(IDC_STATIC_UINT_AIXS_ARC_0 + i, g_factcfg.Unit[i%2]);
	for(i=0; i< g_Naxis; i++)
		SetDlgItemText(IDC_STATIC_UINT_AIXS_0 + i, g_factcfg.Unit[i]);
	for(; i< MAX_NAXIS; i++){
		GetDlgItem(IDC_CHECK_AXIS_0 + i)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_AXIS_0 + i)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_UINT_AIXS_0 + i)->ShowWindow(SW_HIDE);
	}
	for(i=0; i< g_Naxis; i++)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_ARC_AXIS_0))->AddString(g_AxisName[i]);
		((CComboBox*)GetDlgItem(IDC_COMBO_ARC_AXIS_1))->AddString(g_AxisName[i]);
	}
	m_ArcSel[0] = 0;
	m_ArcSel[1] = 1;
	((CComboBox*)GetDlgItem(IDC_COMBO_ARC_AXIS_0))->SetCurSel(m_ArcSel[0]);
	((CComboBox*)GetDlgItem(IDC_COMBO_ARC_AXIS_1))->SetCurSel(m_ArcSel[1]);
	for(i=0; i<2; i++){
		GetDlgItem(IDC_CHECK_AXIS_0 + m_ArcSel[i])->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_AXIS_0 + m_ArcSel[i])->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_UINT_AIXS_0 + m_ArcSel[i])->EnableWindow(FALSE);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_SPEED))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_SPEED_RATIO))->SetCurSel(9);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CPg_Arc::UpdateDlg(PROGRAM_DATA*pdata)
{
	int i, k=0;
	CString str;
	for(i=0; i<g_Naxis; i++){
		if(pdata->arcBit & (1 <<i)){
			if(m_ArcSel[0] != m_ArcSel[1]){
				GetDlgItem(IDC_CHECK_AXIS_0 + m_ArcSel[k])->EnableWindow(TRUE);
				if(((CButton*)GetDlgItem(IDC_CHECK_AXIS_0 + m_ArcSel[k]))->GetCheck())
					GetDlgItem(IDC_EDIT_AXIS_0 + m_ArcSel[k])->EnableWindow(TRUE);
				GetDlgItem(IDC_STATIC_UINT_AIXS_0 + m_ArcSel[k])->EnableWindow(TRUE);
			}
			m_ArcSel[k] = i;
			GetDlgItem(IDC_CHECK_AXIS_0 + m_ArcSel[k])->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_AXIS_0 + m_ArcSel[k])->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC_UINT_AIXS_0 + m_ArcSel[k])->EnableWindow(FALSE);
			k++;
		}
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_ARC_AXIS_0))->SetCurSel(m_ArcSel[0]);
	((CComboBox*)GetDlgItem(IDC_COMBO_ARC_AXIS_1))->SetCurSel(m_ArcSel[1]);
	for(i=0; i< 6; i++){//
		str.Format(_T("%.02f"), 1.0*pdata->arc[i]/*/g_factcfg.distFac[m_ArcSel[i%2]]*/);
		SetDlgItemText(IDC_EDIT_ARC_AXIS_0 + i, str);
	}
	for(i=0; i<g_Naxis; i++){
		if(pdata->posBit & (1 <<i)){
			if(i == m_ArcSel[0] || i == m_ArcSel[1])
				continue;
			((CButton*)GetDlgItem(IDC_CHECK_AXIS_0 + i))->SetCheck(1);
			GetDlgItem(IDC_EDIT_AXIS_0 + i)->EnableWindow(TRUE);
			str.Format(_T("%.02f"), 1.0*pdata->pos[i]/*/g_factcfg.distFac[i]*/);
			SetDlgItemText(IDC_EDIT_AXIS_0 + i, str);
		}
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_SPEED))->SetCurSel(pdata->vel);
	((CComboBox*)GetDlgItem(IDC_COMBO_SPEED_RATIO))->SetCurSel(pdata->velRatio);
	m_index = 1;
}

void CPg_Arc::OnBnClickedCheckAxis(UINT nId)
{
	// TODO: 在此添加控件通知处理程序代码
	int index = nId - IDC_CHECK_AXIS_0;
	BOOL check = ((CButton*)GetDlgItem(nId))->GetCheck();
	GetDlgItem(IDC_EDIT_AXIS_0 + index)->EnableWindow(check);
}



void CPg_Arc::OnCbnSelendokComboArcAxis0()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_ArcSel[0] != m_ArcSel[1]){
		GetDlgItem(IDC_CHECK_AXIS_0 + m_ArcSel[0])->EnableWindow(TRUE);
		if(((CButton*)GetDlgItem(IDC_CHECK_AXIS_0 + m_ArcSel[0]))->GetCheck())
			GetDlgItem(IDC_EDIT_AXIS_0 + m_ArcSel[0])->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_UINT_AIXS_0 + m_ArcSel[0])->EnableWindow(TRUE);
	}
	m_ArcSel[0] = ((CComboBox*)GetDlgItem(IDC_COMBO_ARC_AXIS_0))->GetCurSel();
	GetDlgItem(IDC_CHECK_AXIS_0 + m_ArcSel[0])->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_AXIS_0 + m_ArcSel[0])->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_UINT_AIXS_0 + m_ArcSel[0])->EnableWindow(FALSE);
	SetDlgItemText(IDC_STATIC_UINT_AIXS_ARC_0, g_factcfg.Unit[m_ArcSel[0]%2]);
	SetDlgItemText(IDC_STATIC_UINT_AIXS_ARC_2, g_factcfg.Unit[m_ArcSel[0]%2]);
	OnBnClickedButtonGetEncp();
}


void CPg_Arc::OnCbnSelendokComboArcAxis1()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_ArcSel[0] != m_ArcSel[1]){
		GetDlgItem(IDC_CHECK_AXIS_0 + m_ArcSel[1])->EnableWindow(TRUE);
		if(((CButton*)GetDlgItem(IDC_CHECK_AXIS_0 + m_ArcSel[1]))->GetCheck())
			GetDlgItem(IDC_EDIT_AXIS_0 + m_ArcSel[1])->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_UINT_AIXS_0 + m_ArcSel[1])->EnableWindow(TRUE);
	}
	m_ArcSel[1] = ((CComboBox*)GetDlgItem(IDC_COMBO_ARC_AXIS_1))->GetCurSel();
	GetDlgItem(IDC_CHECK_AXIS_0 + m_ArcSel[1])->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_AXIS_0 + m_ArcSel[1])->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_UINT_AIXS_0 + m_ArcSel[1])->EnableWindow(FALSE);
	SetDlgItemText(IDC_STATIC_UINT_AIXS_ARC_1, g_factcfg.Unit[m_ArcSel[1]%2]);
	SetDlgItemText(IDC_STATIC_UINT_AIXS_ARC_2, g_factcfg.Unit[m_ArcSel[1]%2]);
	OnBnClickedButtonGetEncp();
}

long CPg_Arc::GetEditFloat(UINT id, double fac)
{
	WCHAR data[16];
	double dval;
	int len = GetDlgItemText(id, data, 15);
	if(len == 0) return 0;
	data[len] = 0;
	swscanf(data, _T("%lf"),&dval);
	return (long)(dval * fac);
}
double CPg_Arc::GetEditFloat(UINT id)
{
	WCHAR data[16];
	double dval;
	int len = GetDlgItemText(id, data, 15);
	if(len == 0) return 0;
	data[len] = 0;
	swscanf(data, _T("%lf"),&dval);
	return dval;
}

struct ARC_COORD{
	double x;
	double y;
};
bool cocircle(ARC_COORD p1,ARC_COORD p2,ARC_COORD p3,ARC_COORD &q) 
{ 
	double x12=p2.x-p1.x; 
	double y12=p2.y-p1.y; 
	double x13=p3.x-p1.x; 
	double y13=p3.y-p1.y; 
	double k, b;
	if(x12 == 0) {
		if(y12 == 0)//p1和p2是同一个点
			return false;
		else if(x13 == 0)//p1和p2、p3都在直线x = b上
			return false;
	}else {
		k = y12/x12;
		b = p1.y - k * p1.x;
		if((p3.x * k + b) == p3.y) 
			return false;//在同一条直线上
	}
	double z2=x12*(p1.x+p2.x)+y12*(p1.y+p2.y); 
	double z3=x13*(p1.x+p3.x)+y13*(p1.y+p3.y); 
	double d=2.0*(x12*(p3.y-p2.y)-y12*(p3.x-p2.x)); 
//	if(abs(d) <1) //共线，圆不存在 
//		return false; 
	q.x=(y13*z2-y12*z3)/d; 
	q.y=(x12*z3-x13*z2)/d; 
	//r=dist(p1,q); 
	return true; 
}
BOOL CPg_Arc::GetProData(PROGRAM_DATA *pdata)
{
	if(m_ArcSel[0] == m_ArcSel[1]) return FALSE;
	CIMC_GenericDlg* md = (CIMC_GenericDlg*)m_mdlg;
	ARC_COORD arc[3], cq;
	pdata->arcBit = (1 << m_ArcSel[0]) | (1 << m_ArcSel[1]);
	pdata->arc[0] = GetEditFloat(IDC_EDIT_ARC_AXIS_0);//, g_factcfg.distFac[m_ArcSel[0]]);
	pdata->arc[1] = GetEditFloat(IDC_EDIT_ARC_AXIS_1);//, g_factcfg.distFac[m_ArcSel[1]]);
	pdata->arc[2] = GetEditFloat(IDC_EDIT_ARC_AXIS_2);//, g_factcfg.distFac[m_ArcSel[0]]);
	pdata->arc[3] = GetEditFloat(IDC_EDIT_ARC_AXIS_3);//, g_factcfg.distFac[m_ArcSel[1]]);
	pdata->arc[4] = GetEditFloat(IDC_EDIT_ARC_AXIS_4);//, g_factcfg.distFac[m_ArcSel[0]]);
	pdata->arc[5] = GetEditFloat(IDC_EDIT_ARC_AXIS_5);//, g_factcfg.distFac[m_ArcSel[1]]);
	arc[0].x = pdata->arc[0]*g_factcfg.distFac[m_ArcSel[0]];
	arc[0].y = pdata->arc[1]*g_factcfg.distFac[m_ArcSel[1]];
	arc[1].x = pdata->arc[2]*g_factcfg.distFac[m_ArcSel[0]];
	arc[1].y = pdata->arc[3]*g_factcfg.distFac[m_ArcSel[1]];
	arc[2].x = pdata->arc[4]*g_factcfg.distFac[m_ArcSel[0]];
	arc[2].y = pdata->arc[5]*g_factcfg.distFac[m_ArcSel[1]];
	pdata->posBit = 0;
	for(int i=0; i< g_Naxis; i++)
	{
		if(i == m_ArcSel[0] || i == m_ArcSel[1]) continue;
		if(((CButton*)GetDlgItem(IDC_CHECK_AXIS_0 + i))->GetCheck()){
			pdata->posBit |= (1 << i);
			pdata->pos[i] = GetEditFloat(IDC_EDIT_AXIS_0+i);//, g_factcfg.distFac[i]);
		}
	}
	pdata->vel = ((CComboBox*)GetDlgItem(IDC_COMBO_SPEED))->GetCurSel();
	pdata->velRatio = ((CComboBox*)GetDlgItem(IDC_COMBO_SPEED_RATIO))->GetCurSel();
//	md->m_imc.GetCenter(&pdata->center[0],&pdata->center[1],arc[0],arc[1],arc[2],arc[3],arc[4],arc[5]);
	cocircle(arc[0], arc[1], arc[2], cq);
	pdata->center[0] = cq.x/g_factcfg.distFac[m_ArcSel[0]];
	pdata->center[1] = cq.y/g_factcfg.distFac[m_ArcSel[1]];
//	pdata->dir = md->m_imc.GetArcDir(pdata->center[0],pdata->center[1],pdata->arc[0],pdata->arc[1],pdata->arc[2],pdata->arc[3],pdata->arc[4],pdata->arc[5]);
	pdata->dir = md->m_imc.GetArcDir(cq.x, cq.y, arc[0].x, arc[0].y, arc[1].x, arc[1].y, arc[2].x, arc[2].y);
	return TRUE;
}

//启点
void CPg_Arc::OnBnClickedButtonGetEncp()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	long encp[MAX_NAXIS];
	CString str;
	dlg->GetCurEncp(encp);
	str.Format(_T("%.02f"), IMC_ENCP_SHOW(encp, m_ArcSel[0]));
	SetDlgItemText(IDC_EDIT_ARC_AXIS_0, str);
	str.Format(_T("%.02f"), IMC_ENCP_SHOW(encp, m_ArcSel[1]));
	SetDlgItemText(IDC_EDIT_ARC_AXIS_1, str);
	m_index = 1;
}

//圆弧点
void CPg_Arc::OnBnClickedButtonGetEncp1()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	long encp[MAX_NAXIS];
	CString str;
	dlg->GetCurEncp(encp);
	str.Format(_T("%.02f"), IMC_ENCP_SHOW(encp, m_ArcSel[0]));
	SetDlgItemText(IDC_EDIT_ARC_AXIS_2, str);
	str.Format(_T("%.02f"), IMC_ENCP_SHOW(encp, m_ArcSel[1]));
	SetDlgItemText(IDC_EDIT_ARC_AXIS_3, str);
	m_index = 2;
}

//终点
void CPg_Arc::OnBnClickedButtonGetEncp2()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	long encp[MAX_NAXIS];
	CString str;
	dlg->GetCurEncp(encp);
	str.Format(_T("%.02f"), IMC_ENCP_SHOW(encp, m_ArcSel[0]));
	SetDlgItemText(IDC_EDIT_ARC_AXIS_4, str);
	str.Format(_T("%.02f"), IMC_ENCP_SHOW(encp, m_ArcSel[1]));
	SetDlgItemText(IDC_EDIT_ARC_AXIS_5, str);
	m_index  = 3;
}

//其他轴位置
void CPg_Arc::OnBnClickedButtonGetEncp3()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	long encp[MAX_NAXIS];
	CString str;
	dlg->GetCurEncp(encp);
	for(int i=0; i< g_Naxis; i++)
	{
		if(i == m_ArcSel[0] || i == m_ArcSel[1]) continue;
		if(((CButton*)GetDlgItem(IDC_CHECK_AXIS_0 + i))->GetCheck()){
			str.Format(_T("%.02f"), IMC_ENCP_SHOW(encp, i));
			SetDlgItemText(IDC_EDIT_AXIS_0 + i, str);
		}
	}
	m_index  = 4;
}
BOOL CPg_Arc::GetEncp()
{
	switch(m_index)
	{
	case 1: OnBnClickedButtonGetEncp1();  return FALSE;
	case 2: OnBnClickedButtonGetEncp2();  return FALSE;
	case 3: OnBnClickedButtonGetEncp3();  return TRUE;
	}
	return TRUE;
}