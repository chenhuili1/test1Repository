// dlg/Manual.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "Manual.h"
#include "IMC_GenericDlg.h"
#include "Uout.h"
#include "math.h"
#include "locale.h"

// CManual 对话框

IMPLEMENT_DYNAMIC(CManual, CDialog)

CManual::CManual(CWnd* pParent /*=NULL*/)
	: CDialog(CManual::IDD, pParent)
	, m_MatlabTest(0),F(),phi(),Yreal(),rc(),f(0),k(0),num_v(0)
	, m_X(0)
	, m_V(0)
	, m_angle(0)
	, m_anglev(0)
	, m_vmpc(0)
{
	m_status = 0;
	m_bmp0= (HBITMAP)::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BMP_IOFF));
	m_bmp1= (HBITMAP)::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BMP_ION));
	for(int i=0; i<INPUT_NUM; i++)
		m_inS[i] = -1;
	for(int i=0; i<MAX_NAXIS; i++)
		m_limtS[i] = -1;
	for(int i=0; i<OUTPUT_NUM; i++)
		m_outS[i] = -1;
	memset(sJogdata, 0, sizeof(short)*2*MAX_NAXIS);
}

CManual::~CManual()
{
}

void CManual::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_MatlabTest);
	DDX_Text(pDX, IDC_EDIT4, m_X);
	DDX_Text(pDX, IDC_EDIT5, m_V);
	DDX_Text(pDX, IDC_EDIT6, m_angle);
	DDX_Text(pDX, IDC_EDIT7, m_anglev);
	DDX_Text(pDX, IDC_EDIT8, m_vmpc);
}


BEGIN_MESSAGE_MAP(CManual, CDialog)
	ON_BN_CLICKED(IDC_BUTTON4, &CManual::OnBnClickedButton4)
	ON_CBN_SELENDOK(IDC_COMBO_AXIS, &CManual::OnCbnSelendokComboAxis)
	ON_CBN_SELCHANGE(IDC_COMBO_RATIO, &CManual::OnCbnSelchangeComboRatio)
	ON_COMMAND_RANGE(IDC_CHECK_OUT_0, IDC_CHECK_OUT_31, &CManual::OnBnClickedButtonOut)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON5, &CManual::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CManual::OnBnClickedButton6)
END_MESSAGE_MAP()


// CManual 消息处理程序

BOOL CManual::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	main_GetFphi(F,phi);
	SetTimer(TIMER_MAIN_ENCP, 40, NULL);
	Filename="D:\\jtl\\SDEdu\\parm.txt";
	FileWrite.Open(Filename,CFile::modeCreate|CFile::modeWrite|CFile::typeText);
#if defined(WINCE)
	CRect rc;
	GetWindowRect(&rc);
	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, 1, 1, rc.Width(), rc.Height(), SWP_NOOWNERZORDER|SWP_SHOWWINDOW);
#endif
	for(int i=0; i<g_Naxis; i++)
		((CComboBox*)GetDlgItem(IDC_COMBO_AXIS))->AddString(g_AxisName[i]);
	((CComboBox*)GetDlgItem(IDC_COMBO_MODE))->SetCurSel(0);
	for(int i=0; i<g_factcfg.Naxis; i++){
		GetDlgItem(IDC_CHECK_JOG_X1 + i)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_JOG_X2 + i)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_LIMT_Z_0 + i)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_LIMT_Z_16 + i)->ShowWindow(SW_SHOW);
	}
	for(int i=g_factcfg.Naxis; i<MAX_NAXIS; i++){
		GetDlgItem(IDC_CHECK_JOG_X1 + i)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_JOG_X2 + i)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LIMT_Z_0 + i)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LIMT_Z_16 + i)->ShowWindow(SW_HIDE);
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
	SetTimer(TIMER_MANUAL_TIMING, 40, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CManual::OnCbnSelendokComboAxis()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	int axis = ((CComboBox*)GetDlgItem(IDC_COMBO_AXIS))->GetCurSel();
	dlg->m_imc.StopHandWheel(m_hwaxis);
	m_hwaxis = axis;
	dlg->m_imc.SetHandWheel(m_hwratio, m_hwaxis);
}
void CManual::OnCbnSelchangeComboRatio()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	int ratio = ((CComboBox*)GetDlgItem(IDC_COMBO_RATIO))->GetCurSel();
	m_hwratio = ratio == 0? 1 : ratio == 1 ? 10 : 100;
	dlg->m_imc.SetHandWheel(m_hwratio, m_hwaxis);
}

void CManual::OnBnClickedButtonOut(UINT nId)
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	int mode = ((CComboBox*)GetDlgItem(IDC_COMBO_MODE))->GetCurSel();
	UINT id = nId - IDC_CHECK_OUT_0;
	if(mode == 0){//锁定
		if(m_status & (1 << id)){
			dlg->m_imc.OutPutCtrl(id, IOVAL_CLOSE, SEL_IFIFO);
		}else
			dlg->m_imc.OutPutCtrl(id, IOVAL_OPEN, SEL_IFIFO);
	}	
}

BOOL CManual::PreTranslateMessage(MSG* pMsg)
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
		}else
			if(buttonID >= IDC_CHECK_OUT_0 && buttonID <= IDC_CHECK_OUT_31)
			{
				int mode = ((CComboBox*)GetDlgItem(IDC_COMBO_MODE))->GetCurSel();
				if(mode){//点动
					CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
					dlg->m_imc.OutPutCtrl(buttonID - IDC_CHECK_OUT_0, IOVAL_OPEN, SEL_IFIFO);
				}
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
		}else
			if(buttonID >= IDC_CHECK_OUT_0 && buttonID <= IDC_CHECK_OUT_31)
			{
				int mode = ((CComboBox*)GetDlgItem(IDC_COMBO_MODE))->GetCurSel();
				if(mode){//点动
					CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
					dlg->m_imc.OutPutCtrl(buttonID - IDC_CHECK_OUT_0, IOVAL_CLOSE, SEL_IFIFO);
				}
			}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CManual::Jog(BOOL isdown, BOOL isZ, int axis)
{
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	if(isdown){
		long vel = (long)(g_cfg.jogVel[axis]*IMC_SPEED_FAC(axis));
		if(!isZ) vel = -vel;
		g_cfg.accel[0]=20;
		dlg->m_imc.Jog(vel, axis);
		Sleep(1000);
		g_cfg.accel[0]=200;
		dlg->m_imc.Jog(vel, axis);
	}else 
	{
	    g_cfg.accel[0]=500;
		dlg->m_imc.Jog(0, axis);
	}
}


void CManual::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	dlg->m_imc.StopHandWheel(m_hwaxis);
	KillTimer(TIMER_MANUAL_TIMING);
	KillTimer(TIMER_MAIN_ENCP);
	CDialog::OnClose();
}

void CManual::KeyJogMg()
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
void CManual::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	long vmpc=0;
	double parm[5]={0};
	switch(nIDEvent)
	{
	case TIMER_MAIN_ENCP:
		long encp[MAX_NAXIS];
		dlg->GetCurEncp(encp);
		memcpy(encp, dlg->m_encp, sizeof(long) *g_Naxis);
		int axis0, num;
		if (g_Naxis > 6) num = 6;
		else num = g_Naxis;
		double vel0[4],angle0[4];
		for (int i = 0; i < num; i++)
		{
			    axis0 = g_factcfg.g_mapAxis[i];
				m_encpDelta1[axis0] = encp[axis0] - m_encp1[axis0];
				if(axis0==4||axis0==5)
				{
					angle0[axis0-4]=encp[axis0]*360.0/(4*5000.0);
					angle0[axis0-2]=m_encpDelta1[axis0]*360.0/(4*500.0);
				}
				else
				{
					m_encpDelta1[axis0] = m_encpDelta1[axis0] * (1000.0 / 10.0);
					vel0[axis0]=(double)(1.0*m_encpDelta1[g_factcfg.g_mapAxis[axis0]]/g_factcfg.distFac[axis0]);
				}
				//long vel = (long)(g_cfg.jogVel[axis0] * IMC_SPEED_FAC(axis0));
				//if (vel0[0]>500.0)
			//	{
			//		g_cfg.accel[0] = 500;
			//		dlg->m_imc.Jog(0, 0);
			//	}
				SysStatusObj.ActPos_OuterEncoder[axis0] = encp[axis0];
				m_encp1[axis0] = encp[axis0];
		}
		Yreal[0]=IMC_ENCP_SHOW(encp, 0)/1000;
		Yreal[1]=(double)vel0[0]/1000;
		Yreal[2]=atan(1.4142*tan(angle0[0]*3.1416/180));
		Yreal[3]=atan(1.4142*tan(angle0[2]*3.1416/180));
		rc[0]=30-f;
		rc[1]=30+f;
		//k=k+1;
		//f=main_Getintput_u(F,phi,Yreal,rc,k);
		//g_cfg.accel[0] = f*1000/24;
	/*	num_v++;
		if(num_v>=1)
		{
			vmpc=(long)((g_cfg.accel[0] *0.04)* IMC_SPEED_FAC(0));
			//dlg->m_imc.Jog(vmpc, 0);
			num_v=0;
		}*/
		UpdateData(TRUE);
		//m_X=dlg->MpcParm[0];
		m_V=Yreal[0];
		m_angle=Yreal[2]*180/3.1416;
		m_anglev=Yreal[3]*180/3.1416;
		//m_vmpc=g_cfg.accel[0]*0.2;
		//m_MatlabTest=f*1000/24;
		UpdateData(FALSE);
	/*	parm[0]=Yreal[0];
		parm[1]=Yreal[1];
		parm[2]=Yreal[2]*180/3.1416;
		parm[3]=Yreal[3]*180/3.1416;
		parm[4]=f;
		Txtsave(parm);*/
		break;
	case TIMER_MANUAL_TIMING:
		if(dlg->m_imc.HWJogKeyInPut(Jogdata) == IMC_OK){
			KeyJogMg();
		}
		if(dlg->m_imc.GetInPut(idata) == IMC_OK){
			UpdateInputIcon(idata);
		}
		if(dlg->m_imc.GetOutPut(odata) == IMC_OK){
			UpdateOutputIcon(odata);
		}
		if(dlg->m_imc.GetAio(aiodata) == IMC_OK){
			UpdateLimtIcon(aiodata);
		}
		WORD axis;
		long ratio = 1;
		BOOL isc = FALSE;
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
	}
	CDialog::OnTimer(nIDEvent);
}

void CManual::Txtsave(double parm[5])
{
 // setlocale(LC_CTYPE,'chs');
  for(int i=0;i<5;i++)
  {
	CString temp;
	temp.Format(_T("%lf  "),parm[i]);
	FileWrite.WriteString(temp);
  }
  FileWrite.WriteString(_T("\r\n"));
}
void CManual::UpdateInputIcon(short *data)
{
	CStatic *ic;
	for(int i=0; i<INPUT_NUM; i++){
		if(m_inS[i] != data[i]){
			ic = (CStatic*)GetDlgItem(IDC_STATIC_IN_0 + i);
			if(data[i])
				ic->SetBitmap(m_bmp0);
			else
				ic->SetBitmap(m_bmp1);
			m_inS[i] = data[i];
		}
	}
}
void CManual::UpdateOutputIcon(short *data)
{
	CStatic *ic;
	for(int i=0; i<INPUT_NUM; i++){
		if(m_outS[i] != data[i]){
			ic = (CStatic*)GetDlgItem(IDC_STATIC_OUT_0 + i);
			if(data[i]){
				ic->SetBitmap(m_bmp1);	
				m_status |= (1 << i);	
			}else{
				ic->SetBitmap(m_bmp0);				
				m_status &= ~(1 << i);	
			}
			m_outS[i] = data[i];
		}
	}
}
void CManual::UpdateLimtIcon(short *data)
{
	CStatic *ic;
	for(int i=0; i<g_Naxis; i++){
		if(m_limtS[i] != data[i]){
			ic = (CStatic*)GetDlgItem(IDC_STATIC_LIMT_Z_0 + i);
			if(data[i] & 0x1){//正限位,无输入，即高电平
				if(g_polar.aioP[i])//高电平有效
					ic->SetBitmap(m_bmp1);
				else
					ic->SetBitmap(m_bmp0);
			}else{//低电平
				if(g_polar.aioP[i])//高电平有效
					ic->SetBitmap(m_bmp0);
				else
					ic->SetBitmap(m_bmp1);
			}
			ic = (CStatic*)GetDlgItem(IDC_STATIC_LIMT_Z_16 + i);
			if(data[i] & 0x2){//负限位
				if(g_polar.aioN[i])//高电平有效
					ic->SetBitmap(m_bmp1);
				else
					ic->SetBitmap(m_bmp0);
			}else{//低电平
				if(g_polar.aioN[i])//高电平有效
					ic->SetBitmap(m_bmp0);
				else
					ic->SetBitmap(m_bmp1);
			}
			m_limtS[i] = data[i];
		}
	}
}
void CManual::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	long vel = (long)(g_cfg.jogVel[0] * IMC_SPEED_FAC(0));
	SetTimer(TIMER_MAIN_ENCP, 100, NULL);
	//if (!isZ) vel = -vel;
	g_cfg.accel[0] = 100;
	dlg->m_imc.Jog(vel, 0);
}

void CManual::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(TRUE);
	//m_MatlabTest=main_Getintput_u(F,phi,Yreal,rc,k);
	//UpdateData(FALSE);
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	long vel = (long)(g_cfg.jogVel[0] * IMC_SPEED_FAC(0));
	KillTimer(TIMER_MAIN_ENCP);
	//if (!isZ) vel = -vel;
	g_cfg.accel[0] = 500;
	dlg->m_imc.Jog(0, 0);
    FileWrite.Close();
}

void CManual::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	PROGRAM_DATA pdata;

	pdata.vel = 1;
	pdata.velRatio = 10;
	pdata.axis = 0;
	pdata.pos[0] = 500;
//	pdata->isWT = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
	pdata.InSel = 0;
	dlg->m_imc.PosCtrl(&pdata, 2);
}
