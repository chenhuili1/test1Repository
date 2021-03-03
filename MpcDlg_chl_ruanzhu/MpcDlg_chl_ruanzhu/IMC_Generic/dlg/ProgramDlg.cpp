// dlg/ProgramDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "ProgramDlg.h" 
#include "IMC_GenericDlg.h"


// CProgramDlg 对话框

IMPLEMENT_DYNAMIC(CProgramDlg, CDialog)

CProgramDlg::CProgramDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgramDlg::IDD, pParent)
{
	m_oldtype = CMD_NULL;
	m_hwOK = FALSE;
	memset(sJogdata, 0, sizeof(short)*2*MAX_NAXIS);
}

CProgramDlg::~CProgramDlg()
{
}

void CProgramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProgramDlg, CDialog)
	ON_CBN_SELENDOK(IDC_COMBO_CMD, &CProgramDlg::OnCbnSelendokComboCmd)
	ON_BN_CLICKED(IDOK, &CProgramDlg::OnBnClickedOk)
	ON_CBN_SELENDOK(IDC_COMBO_AXIS, &CProgramDlg::OnCbnSelendokComboAxis)
	ON_CBN_SELCHANGE(IDC_COMBO_RATIO, &CProgramDlg::OnCbnSelchangeComboRatio)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &CProgramDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK1, &CProgramDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CProgramDlg 消息处理程序


BOOL CProgramDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
#if defined(WINCE)
	int wf = GetSystemMetrics(SM_CXSCREEN);
	CRect rc;
	GetWindowRect(&rc);
	int w = rc.Width();
	int h = rc.Height();
	rc.right = wf-1;
	rc.left = rc.right - w;
	MoveWindow(rc);
#endif

	m_jplpdlg.SetMainDlgPtr(m_mdlg);
	m_Linkagedlg.SetMainDlgPtr(m_mdlg);
	m_Arcdlg.SetMainDlgPtr(m_mdlg);
	m_Outputdlg.SetMainDlgPtr(m_mdlg);
	m_Inputdlg.SetMainDlgPtr(m_mdlg);
	m_Gohomedlg.SetMainDlgPtr(m_mdlg);
	m_Whiledlg.SetMainDlgPtr(m_mdlg);
	m_Tipdlg.SetMainDlgPtr(m_mdlg);
	m_Veldlg.SetMainDlgPtr(m_mdlg);
	m_Posdlg.SetMainDlgPtr(m_mdlg);
	m_waitdlg.SetMainDlgPtr(m_mdlg);
	m_delaydlg.SetMainDlgPtr(m_mdlg);
	m_whirldlg.SetMainDlgPtr(m_mdlg);
	m_jplpdlg.Create(IDD_DLG_PG_JUMP, this);
	m_jplpdlg.ShowWindow(SW_HIDE);
	m_Linkagedlg.Create(IDD_DLG_PG_LINKAGE, this);
	m_Linkagedlg.ShowWindow(SW_HIDE);
	m_Arcdlg.Create(IDD_DLG_PG_ARC, this);
	m_Arcdlg.ShowWindow(SW_HIDE);
	m_Outputdlg.Create(IDD_DLG_PG_OUTPUT, this);
	m_Outputdlg.ShowWindow(SW_HIDE);
	m_Inputdlg.Create(IDD_DLG_PG_INPUT, this);
	m_Inputdlg.ShowWindow(SW_HIDE);
	m_Gohomedlg.Create(IDD_DLG_PG_GOHOME, this);
	m_Gohomedlg.ShowWindow(SW_HIDE);
	m_Whiledlg.Create(IDD_DLG_PG_LOOP, this);
	m_Whiledlg.ShowWindow(SW_HIDE);
	m_Tipdlg.Create(IDD_DLG_PG_TIP, this);
	m_Tipdlg.ShowWindow(SW_HIDE);
	m_Veldlg.Create(IDD_DLG_PG_VEL, this);
	m_Veldlg.ShowWindow(SW_HIDE);
	m_Posdlg.Create(IDD_DLG_PG_POS, this);
	m_Posdlg.ShowWindow(SW_HIDE);
	m_waitdlg.Create(IDD_DLG_PG_WAIT, this);
	m_waitdlg.ShowWindow(SW_HIDE);
	m_delaydlg.Create(IDD_DLG_PG_DELAY, this);
	m_delaydlg.ShowWindow(SW_HIDE);
	m_whirldlg.Create(IDD_DLG_PG_GOHOME_WHIRL, this);
	m_whirldlg.ShowWindow(SW_HIDE);
	MoveDlg();
	InitCmdBox();
	if(m_oldtype == CMD_NULL) 
		m_oldtype = CMD_LINKAGE;
	ShowCMDDlg(m_oldtype);
	SetComBoSel(m_oldtype);
	MyUpdateData(m_oldtype);
	((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(1);
	for(int i=0; i<g_Naxis; i++)
		((CComboBox*)GetDlgItem(IDC_COMBO_AXIS))->AddString(g_AxisName[i]);
	for(int i=0; i<g_factcfg.Naxis; i++){
		GetDlgItem(IDC_CHECK_JOG_X1 + i)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_JOG_X2 + i)->ShowWindow(SW_SHOW);
	}
	for(int i=g_factcfg.Naxis; i<MAX_NAXIS; i++){
		GetDlgItem(IDC_CHECK_JOG_X1 + i)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_JOG_X2 + i)->ShowWindow(SW_HIDE);
	}

	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	WORD axis;
	long ratio = 1;
	m_hwaxis = 0;
	m_hwratio = 10;
	if(dlg->m_imc.GetHWAxis(&axis) == IMC_OK){
		if(axis != MAX_NAXIS && axis < g_Naxis)
			m_hwaxis = axis;
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_AXIS))->SetCurSel(m_hwaxis);
	if(dlg->m_imc.GetHWRatio(&ratio) == IMC_OK)
		m_hwratio = ratio;
	((CComboBox*)GetDlgItem(IDC_COMBO_RATIO))->SetCurSel(m_hwratio == 1 ? 0 : m_hwratio == 10 ? 1 : 2);
	dlg->m_imc.SetHandWheel(m_hwratio, m_hwaxis);

	dlg->m_imc.HWJogKeyInPut(sJogdata);

	SetTimer(TIMER_PG_HANDWHEEL, 40, NULL);

	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(g_isUseHWok);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CProgramDlg::InitCmdBox()
{
	CComboBox* pb = (CComboBox*)GetDlgItem(IDC_COMBO_CMD);
	for(int i=CMD_LINKAGE; i<CMD_TOTAL; i++)
		pb->AddString(g_cmdStr[i]);
}
void CProgramDlg::MoveDlg()
{
	CRect rc,rc1, rc2, rc3;
	GetDlgItem(IDC_STATIC_SPACE)->GetWindowRect(&rc1);
	ScreenToClient(&rc1);
	GetDlgItem(IDC_STATIC_JOG_BOX)->GetWindowRect(&rc3);
	ScreenToClient(&rc3);
	//跳转
	m_jplpdlg.GetClientRect(&rc2);
	rc.left = rc3.right;
	rc.top = rc1.bottom+1;
	rc.bottom = rc.top + rc2.Height();
	rc.right = rc.left + rc2.Width();
	m_jplpdlg.MoveWindow(rc);
	//联动
	m_Linkagedlg.GetClientRect(&rc2);
	rc.bottom = rc.top + rc2.Height();
	rc.right = rc.left + rc2.Width();
	m_Linkagedlg.MoveWindow(rc);
	//圆弧
	m_Arcdlg.GetClientRect(&rc2);
	rc.bottom = rc.top + rc2.Height();
	rc.right = rc.left + rc2.Width();
	m_Arcdlg.MoveWindow(rc);
	//输出
	m_Outputdlg.GetClientRect(&rc2);
	rc.bottom = rc.top + rc2.Height();
	rc.right = rc.left + rc2.Width();
	m_Outputdlg.MoveWindow(rc);
	//输出
	m_Inputdlg.GetClientRect(&rc2);
	rc.bottom = rc.top + rc2.Height();
	rc.right = rc.left + rc2.Width();
	m_Inputdlg.MoveWindow(rc);
	//回零
	m_Gohomedlg.GetClientRect(&rc2);
	rc.bottom = rc.top + rc2.Height();
	rc.right = rc.left + rc2.Width();
	m_Gohomedlg.MoveWindow(rc);
	//循环
	m_Whiledlg.GetClientRect(&rc2);
	rc.bottom = rc.top + rc2.Height();
	rc.right = rc.left + rc2.Width();
	m_Whiledlg.MoveWindow(rc);
	//提示
	m_Tipdlg.GetClientRect(&rc2);
	rc.bottom = rc.top + rc2.Height();
	rc.right = rc.left + rc2.Width();
	m_Tipdlg.MoveWindow(rc);
	//匀速运动
	m_Veldlg.GetClientRect(&rc2);
	rc.bottom = rc.top + rc2.Height();
	rc.right = rc.left + rc2.Width();
	m_Veldlg.MoveWindow(rc);
	//点到点运动
	m_Posdlg.GetClientRect(&rc2);
	rc.bottom = rc.top + rc2.Height();
	rc.right = rc.left + rc2.Width();
	m_Posdlg.MoveWindow(rc);
	//等待
	m_waitdlg.GetClientRect(&rc2);
	rc.bottom = rc.top + rc2.Height();
	rc.right = rc.left + rc2.Width();
	m_waitdlg.MoveWindow(rc);
	//等待
	m_delaydlg.GetClientRect(&rc2);
	rc.bottom = rc.top + rc2.Height();
	rc.right = rc.left + rc2.Width();
	m_delaydlg.MoveWindow(rc);
	//等待
	m_whirldlg.GetClientRect(&rc2);
	rc.bottom = rc.top + rc2.Height();
	rc.right = rc.left + rc2.Width();
	m_whirldlg.MoveWindow(rc);
}
void CProgramDlg::SetType(CMD_TYPE type, PVOID pdata)
{
	m_oldtype = type;
	m_pdata = (PROGRAM_DATA*) pdata;
}
void CProgramDlg::SetComBoSel(CMD_TYPE type)
{//选择当前指令
	CComboBox* pb = (CComboBox*)GetDlgItem(IDC_COMBO_CMD);
	switch(m_oldtype)
	{
	case CMD_LINKAGE:pb->SelectString(-1, g_cmdStr[CMD_LINKAGE]);break;//多轴联动
	case CMD_ARC:	pb->SelectString(-1, g_cmdStr[CMD_ARC]);break;//圆弧
	case CMD_OUTPUT:pb->SelectString(-1, g_cmdStr[CMD_OUTPUT]);break;	//输出
	case CMD_INPUT:pb->SelectString(-1, g_cmdStr[CMD_INPUT]);break;	//输出
//	case CMD_IF:	pb->SelectString(-1, g_cmdStr[CMD_IF]);break;	//条件
	case CMD_DELAY:	pb->SelectString(-1, g_cmdStr[CMD_DELAY]);break;//延时
	case CMD_END:	pb->SelectString(-1, g_cmdStr[CMD_END]);break;//程序结束
	case CMD_LOOP:	pb->SelectString(-1, g_cmdStr[CMD_LOOP]);break;//循环开始
	case CMD_JUMP:	pb->SelectString(-1, g_cmdStr[CMD_JUMP]);break;//跳转
	case CMD_WEND:	pb->SelectString(-1, g_cmdStr[CMD_WEND]);break;//循环结束，没有对话框显示
	case CMD_GOHOME:pb->SelectString(-1, g_cmdStr[CMD_GOHOME]);break;//回零
	case CMD_GHWHIRL:pb->SelectString(-1, g_cmdStr[CMD_GHWHIRL]);break;//回零
	case CMD_VEL:	pb->SelectString(-1, g_cmdStr[CMD_VEL]);break;//连续匀速运动
	case CMD_POS:	pb->SelectString(-1, g_cmdStr[CMD_POS]);break;//点到点运动
	case CMD_WAIT:	pb->SelectString(-1, g_cmdStr[CMD_WAIT]);break;//等待
	}
}
void CProgramDlg::ShowCMDDlg(CMD_TYPE type)
{
	switch(m_oldtype)
	{
	case CMD_LINKAGE:	m_Linkagedlg.ShowWindow(SW_HIDE); break;//多轴联动
	case CMD_ARC:		m_Arcdlg.ShowWindow(SW_HIDE); break;//圆弧
	case CMD_OUTPUT:	m_Outputdlg.ShowWindow(SW_HIDE); break;//输出
	case CMD_INPUT:		m_Inputdlg.ShowWindow(SW_HIDE); break;//输入
//	case CMD_IF:		break;//条件
	case CMD_DELAY:		m_delaydlg.ShowWindow(SW_HIDE); break;//延时
	case CMD_JUMP:		m_jplpdlg.ShowWindow(SW_HIDE); break;//跳转
	case CMD_LOOP:		m_Whiledlg.ShowWindow(SW_HIDE); break;//循环开始
	case CMD_END:		m_Tipdlg.ShowWindow(SW_HIDE); break;//程序结束，
	case CMD_WEND:		m_Tipdlg.ShowWindow(SW_HIDE); break;//循环结束，
	case CMD_GOHOME:	m_Gohomedlg.ShowWindow(SW_HIDE); break;//回零
	case CMD_GHWHIRL:	m_whirldlg.ShowWindow(SW_HIDE); break;//回零
	case CMD_VEL:		m_Veldlg.ShowWindow(SW_HIDE); break;//连续匀速运动
	case CMD_POS:		m_Posdlg.ShowWindow(SW_HIDE); break;//点到点运动
	case CMD_WAIT:		m_waitdlg.ShowWindow(SW_HIDE); break;//等待
	}
	m_oldtype = type;
	switch(m_oldtype)
	{
	case CMD_LINKAGE:	m_Linkagedlg.ShowWindow(SW_SHOW); break;//多轴联动
	case CMD_ARC:		m_Arcdlg.ShowWindow(SW_SHOW); break;//圆弧
	case CMD_OUTPUT:	m_Outputdlg.ShowWindow(SW_SHOW); break;//输出
	case CMD_INPUT:		m_Inputdlg.ShowWindow(SW_SHOW); break;//输入
//	case CMD_IF:		break;	//条件
	case CMD_DELAY:		m_delaydlg.ShowWindow(SW_SHOW); break;//延时
	case CMD_JUMP:		m_jplpdlg.ShowWindow(SW_SHOW); break;//跳转
	case CMD_LOOP:		m_Whiledlg.ShowWindow(SW_SHOW); break;//循环开始
	case CMD_END:		m_Tipdlg.SetPrompt(m_oldtype);m_Tipdlg.ShowWindow(SW_SHOW);break;//程序结束，
	case CMD_WEND:		m_Tipdlg.SetPrompt(m_oldtype);m_Tipdlg.ShowWindow(SW_SHOW);break;//循环结束，
	case CMD_GOHOME:	m_Gohomedlg.ShowWindow(SW_SHOW); break;//回零
	case CMD_GHWHIRL:	m_whirldlg.ShowWindow(SW_SHOW); break;//回零
	case CMD_VEL:		m_Veldlg.ShowWindow(SW_SHOW); break;//连续匀速运动
	case CMD_POS:		m_Posdlg.ShowWindow(SW_SHOW); break;//点到点运动
	case CMD_WAIT:		m_waitdlg.ShowWindow(SW_SHOW); break;//等待
	default: return;
	}
}
void CProgramDlg::MyUpdateData(CMD_TYPE type)
{
	if(m_pdata == NULL) return;
	switch(type)
	{
	case CMD_LINKAGE:	m_Linkagedlg.UpdateDlg(m_pdata); break;//多轴联动
	case CMD_ARC:		m_Arcdlg.UpdateDlg(m_pdata); break;//圆弧
	case CMD_OUTPUT:	m_Outputdlg.UpdateDlg(m_pdata); break;//输出
	case CMD_INPUT:		m_Inputdlg.UpdateDlg(m_pdata); break;//输入
//	case CMD_IF:		break;//条件
	case CMD_DELAY:		m_delaydlg.UpdateDlg(m_pdata); break;//延时
	case CMD_JUMP:		m_jplpdlg.UpdateDlg(m_pdata); break;//跳转
	case CMD_LOOP:		m_Whiledlg.UpdateDlg(m_pdata); break;//循环开始
	case CMD_END:		 break;//程序结束，
	case CMD_WEND:		break;//循环结束，
	case CMD_GOHOME:	m_Gohomedlg.UpdateDlg(m_pdata); break;//回零
	case CMD_GHWHIRL:	m_whirldlg.UpdateDlg(m_pdata); break;//回零
	case CMD_VEL:		m_Veldlg.UpdateDlg(m_pdata); break;//连续匀速运动
	case CMD_POS:		m_Posdlg.UpdateDlg(m_pdata); break;//点到点运动
	case CMD_WAIT:		m_waitdlg.UpdateDlg(m_pdata); break;//点到点运动
	}
}
void CProgramDlg::OnCbnSelendokComboCmd()
{
	// TODO: 在此添加控件通知处理程序代码
	CMD_TYPE type;
	int sel = ((CComboBox*)GetDlgItem(IDC_COMBO_CMD))->GetCurSel();
	type = (CMD_TYPE)(sel +1);
	if(type == CMD_ARC){
		CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
		long encp[MAX_NAXIS];
		dlg->GetCurEncp(encp);
		m_pdata->arc[0] = IMC_ENCP_SHOW(encp, 0);
		m_pdata->arc[1] = IMC_ENCP_SHOW(encp, 1);
		MyUpdateData(type);
	}
	ShowCMDDlg(type);
}


void CProgramDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(TIMER_PG_HANDWHEEL);
	if(m_pdata != NULL) {
		int sel = ((CComboBox*)GetDlgItem(IDC_COMBO_CMD))->GetCurSel();
		m_pdata->type = (CMD_TYPE)(sel +1);
		switch(m_pdata->type)
		{
		case CMD_LINKAGE:	m_Linkagedlg.GetProData(m_pdata); break;//多轴联动
		case CMD_ARC:		m_Arcdlg.GetProData(m_pdata); break;//圆弧
		case CMD_OUTPUT:	m_Outputdlg.GetProData(m_pdata); break;//输出
		case CMD_INPUT:		m_Inputdlg.GetProData(m_pdata); break;//输入
	//	case CMD_IF:		break;//条件
		case CMD_DELAY:		m_delaydlg.GetProData(m_pdata); break;//延时
		case CMD_JUMP:		m_jplpdlg.GetProData(m_pdata); break;//跳转
		case CMD_LOOP:		m_Whiledlg.GetProData(m_pdata); break;//循环开始
		case CMD_END:		break;//程序结束，
		case CMD_WEND:		break;//循环结束，
		case CMD_GOHOME:	m_Gohomedlg.GetProData(m_pdata); break;//回零
		case CMD_GHWHIRL:	m_whirldlg.GetProData(m_pdata); break;//回零
		case CMD_VEL:		m_Veldlg.GetProData(m_pdata); break;//匀速
		case CMD_POS:		m_Posdlg.GetProData(m_pdata); break;//点位
		case CMD_WAIT:		m_waitdlg.GetProData(m_pdata); break;//等待
		}
	}
	StopHW();
	CDialog::OnOK();
}
void CProgramDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(TIMER_PG_HANDWHEEL);
	StopHW();
	OnCancel();
}

void CProgramDlg::StopHW()
{
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	dlg->m_imc.StopHandWheel(m_hwaxis);
}

void CProgramDlg::OnCbnSelendokComboAxis()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	
		int axis = ((CComboBox*)GetDlgItem(IDC_COMBO_AXIS))->GetCurSel();
		dlg->m_imc.StopHandWheel(m_hwaxis);
		m_hwaxis = axis;
		dlg->m_imc.SetHandWheel(m_hwratio, m_hwaxis);
}
void CProgramDlg::OnCbnSelchangeComboRatio()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
		int ratio = ((CComboBox*)GetDlgItem(IDC_COMBO_RATIO))->GetCurSel();
		m_hwratio = ratio == 0? 1 : ratio == 1 ? 10 : 100;
		dlg->m_imc.SetHandWheel(m_hwratio, m_hwaxis);
}


BOOL CProgramDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	int axis;
	if(pMsg->message==WM_LBUTTONDOWN)
	{ 	
		UINT buttonID=GetWindowLong(pMsg->hwnd,   GWL_ID);//获得按钮ID
		if(buttonID >= IDC_CHECK_JOG_X1 && buttonID <= IDC_CHECK_JOG_N1)
		{
			SetCapture();//用于捕获鼠标：无论鼠标光标位置在何处，都会将鼠标消息送给调用它的那一个窗口
			((CButton*)GetDlgItem(buttonID))->SetCheck(1);
			axis = buttonID - IDC_CHECK_JOG_X1;
			Jog(TRUE, FALSE, axis);
		}else
		if(buttonID >= IDC_CHECK_JOG_X2 && buttonID <= IDC_CHECK_JOG_N2)
		{
			SetCapture();//用于捕获鼠标：无论鼠标光标位置在何处，都会将鼠标消息送给调用它的那一个窗口
			((CButton*)GetDlgItem(buttonID))->SetCheck(1);
			axis = buttonID - IDC_CHECK_JOG_X2;
			Jog(TRUE, TRUE, axis);
		}
	}else if(pMsg->message==WM_LBUTTONUP){
		UINT buttonID=GetWindowLong(pMsg->hwnd,   GWL_ID);//获得按钮ID
		if(buttonID >= IDC_CHECK_JOG_X1 && buttonID <= IDC_CHECK_JOG_N1)
		{
			axis = buttonID - IDC_CHECK_JOG_X1;
			Jog(FALSE, FALSE, axis);
			((CButton*)GetDlgItem(buttonID))->SetCheck(0);
			ReleaseCapture();//用ReleaseCapture()释放窗口对鼠标的控制，否则其他窗口将无法接收到鼠标消息
		}else
		if(buttonID >= IDC_CHECK_JOG_X2 && buttonID <= IDC_CHECK_JOG_N2)
		{
			axis = buttonID - IDC_CHECK_JOG_X2;
			Jog(FALSE, TRUE, axis);
			((CButton*)GetDlgItem(buttonID))->SetCheck(0);
			ReleaseCapture();//用ReleaseCapture()释放窗口对鼠标的控制，否则其他窗口将无法接收到鼠标消息
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CProgramDlg::Jog(BOOL isdown, BOOL isZ, int axis)
{
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	if(((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck()){
		if(isdown){
			long vel = g_cfg.jogVel[axis]*IMC_SPEED_FAC(axis);
			if(!isZ) vel = -vel;
			dlg->m_imc.Jog(vel, axis);
		}else 
			dlg->m_imc.Jog(0, axis);
	}
}


void CProgramDlg::KeyJogMg()
{
	int k = 0;
	for(int i=0; i<g_Naxis; i++)
	{
		if(sJogdata[k] != Jogdata[k]){//正方向
			sJogdata[k] = Jogdata[k];
			if(Jogdata[k] == SW_INPUT_CLOSE){//正方向按下
				if(sJogdata[k+1] == SW_INPUT_CLOSE){//如果负方向已经按下，则停止
					Jog(FALSE, TRUE, i);
				}else{
					Jog(TRUE, TRUE, i);
				}
			}else {
				if(sJogdata[k+1] == SW_INPUT_CLOSE){//如果负方向已经按下，则启动
					Jog(TRUE, FALSE, i);//启动负方向
				}else{
					Jog(FALSE, TRUE, i);//停止
				}
			}
			k+=2;
		}else{
			k++;
			if(sJogdata[k] != Jogdata[k]){//负方向
				sJogdata[k] = Jogdata[k];
				if(Jogdata[k] == SW_INPUT_CLOSE){//负方向按下
					if(sJogdata[k-1] == SW_INPUT_CLOSE){//如果正方向已经按下，则停止
						Jog(FALSE, FALSE, i);
					}else{
						Jog(TRUE, FALSE, i);
					}
				}else {//负方向放开
					if(sJogdata[k-1] == SW_INPUT_CLOSE){//如果正方向已经按下，则启动正方向
						Jog(TRUE, TRUE, i);
					}else{
						Jog(FALSE, FALSE, i);
					}
				}
			}
			k++;
		}
	}
}


void CProgramDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	switch(nIDEvent)
	{
	case TIMER_PG_HANDWHEEL:
		WORD axis;
		long ratio = 1;
		BOOL isok, isc = FALSE;
		if(dlg->m_imc.HWJogKeyInPut(Jogdata) == IMC_OK){
			KeyJogMg();
		}
		if(dlg->m_imc.GetHWAxis(&axis) == IMC_OK){
			if(axis != MAX_NAXIS){
				if(m_hwaxis != axis && axis < g_Naxis){
					dlg->m_imc.StopHandWheel(m_hwaxis);
					m_hwaxis = axis;
					((CComboBox*)GetDlgItem(IDC_COMBO_AXIS))->SetCurSel(m_hwaxis);
					isc = TRUE;
				}
			}else{
			/*	if(m_HWoff){
					dlg->m_imc.StopHandWheel(m_hwaxis);
				}else
					m_HWoff = TRUE;*/
			}
		}
		if(m_hwaxis != MAX_NAXIS){
			if(dlg->m_imc.GetHWRatio(&ratio) == IMC_OK){
				if(m_hwratio != ratio){
					m_hwratio = ratio;
					((CComboBox*)GetDlgItem(IDC_COMBO_RATIO))->SetCurSel(m_hwratio == 1 ? 0 : m_hwratio == 10 ? 1 : 2);
					isc = TRUE;
				}
			}
		}
		if(isc)
			dlg->m_imc.SetHandWheel(m_hwratio, m_hwaxis);

		if(dlg->m_imc.GetHWOK(&isok) == IMC_OK){
			if(m_hwOK != isok){
				m_hwOK = isok;
				if(m_hwOK)
					GetEncpMG();
			}
		}
	}

	CDialog::OnTimer(nIDEvent);
}
void CProgramDlg::GetEncpMG()
{
	int sel = ((CComboBox*)GetDlgItem(IDC_COMBO_CMD))->GetCurSel();
	CMD_TYPE type = (CMD_TYPE)(sel +1);
	switch(type)
	{
		case CMD_LINKAGE:	
			m_Linkagedlg.OnBnClickedButtonGetEncp(); 
			if(g_isUseHWok) 
				OnBnClickedOk();
			break;//多轴联动
		case CMD_ARC:		
			if(m_Arcdlg.GetEncp() && g_isUseHWok) 
				OnBnClickedOk();
			break;//圆弧
		case CMD_POS:		
			m_Posdlg.OnBnClickedButtonGetEncp();  
			if(g_isUseHWok) 
				OnBnClickedOk();
			break;//点位
		case CMD_OUTPUT:	OnBnClickedOk(); break;//输出
		case CMD_INPUT:		OnBnClickedOk(); break;//输入
	//	case CMD_IF:		break;//条件
		case CMD_DELAY:		OnBnClickedOk(); break;//延时
		case CMD_JUMP:		OnBnClickedOk(); break;//跳转
		case CMD_LOOP:		OnBnClickedOk(); break;//循环开始
		case CMD_END:		OnBnClickedOk(); break;//程序结束，
		case CMD_WEND:		OnBnClickedOk(); break;//循环结束，
		case CMD_GOHOME:	OnBnClickedOk(); break;//回零
		case CMD_GHWHIRL:	OnBnClickedOk(); break;//回零
		case CMD_VEL:		OnBnClickedOk(); break;//匀速
		case CMD_WAIT:		OnBnClickedOk(); break;//等待
	}
}
void CProgramDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	g_isUseHWok = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
}
