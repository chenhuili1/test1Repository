// IMC_GenericDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "IMC_GenericDlg.h"

#include "MyPassWord.h"
#include "math.h"

#if defined(WINCE)
#include "sip.h"
#include "SIPAPI.H"
#endif

#include "LogoInfo.h"

CLogoInfo *g_pinfodlg = NULL;

enum{
	MACHIN_STEP,
	MACHIN_SINGLE,
	MACHIN_LOOP,
};


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CIMC_GenericDlg 对话框

CIMC_GenericDlg::CIMC_GenericDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIMC_GenericDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_isInit = FALSE;
	m_bChange = FALSE;
	m_curdlg = 0;
	m_timeTotal = 0;
	m_matchinNum = 0;
	m_threadPause = FALSE;
	m_threadRun = FALSE;	//线程是否正在运行
	m_EmstopRun = FALSE;	//线程是否正在运行
	m_threadStop = FALSE;	//控制线程停止
	m_threadReset = FALSE;	//控制线程复位，即立即退出线程
	m_threadStep = FALSE;
	m_machinMode = 2;	//循环
	m_errRunT = FALSE;

	g_isTestV = FALSE;
	g_cmdStr[CMD_NULL] =_T("");
	g_cmdStr[CMD_LINKAGE] =_T("启动多轴联动");
	g_cmdStr[CMD_ARC] =_T("启动圆弧动作");
	g_cmdStr[CMD_OUTPUT] =_T("开关量输出");
	g_cmdStr[CMD_INPUT] =_T("开关量输入");
	g_cmdStr[CMD_JUMP] =_T("跳转");
//	g_cmdStr[CMD_IF] =_T("条件");
	g_cmdStr[CMD_LOOP] =_T("循环开始");
	g_cmdStr[CMD_WEND] =_T("循环结束");
	g_cmdStr[CMD_DELAY] =_T("延时");
	g_cmdStr[CMD_END] =_T("程序结束");
	g_cmdStr[CMD_GOHOME] =_T("回零操作");
	g_cmdStr[CMD_GHWHIRL] =_T("旋转轴回零");
	g_cmdStr[CMD_VEL] =_T("启动连续运动");
	g_cmdStr[CMD_POS] =_T("启动单轴点位");
	g_cmdStr[CMD_WAIT] =_T("等待");
	g_AxisName[MAP_X] = _T("X轴");
	g_AxisName[MAP_Y] = _T("Y轴");
	g_AxisName[MAP_Z] = _T("Z轴");
	g_AxisName[MAP_A] = _T("A轴");
	g_AxisName[MAP_B] = _T("B轴");
	g_AxisName[MAP_C] = _T("C轴");
	g_AxisName[MAP_D] = _T("D轴");
	g_AxisName[MAP_E] = _T("E轴");
	g_AxisName[MAP_F] = _T("F轴");
	g_AxisName[MAP_G] = _T("G轴");
	g_AxisName[MAP_H] = _T("H轴");
	g_AxisName[MAP_I] = _T("I轴");
	g_AxisName[MAP_J] = _T("J轴");
	g_AxisName[MAP_K] = _T("K轴");
	g_AxisName[MAP_L] = _T("L轴");
	g_AxisName[MAP_M] = _T("M轴");
	g_Naxis = 4;
	memset(&g_factcfg, 0, sizeof(FACT_CFG));
	memset(&g_cfg, 0, sizeof(SYS_CFG));
	int i;
	g_cfg.machinSel = 1;
	g_cfg.locusVel = 10;
	g_cfg.locusFastVel = 20;
	g_cfg.locusAcc = 10;
	for(i=0; i<MAX_NAXIS; i++){
		g_cfg.workVel[i] = 10;
		g_cfg.fastVel[i] = 20;
		g_cfg.jogVel[i] = 10;
		g_cfg.homeVel[i] = 10;
		g_cfg.homeDir[i] = 1;
		g_cfg.accel[i] = 20;
		g_cfg.decel[i] = 20;
		g_factcfg.distFac[i] = 10000;
		g_factcfg.timeFac[i] = 1000;
		g_factcfg.steptime[i] = 200;
		g_factcfg.g_mapAxis[i] = i;
		g_factcfg.encpfac[i] = 1.0;
		memcpy(g_factcfg.Unit[i], _T("cm"), sizeof(_T("cm")));
		m_axis[i] = i;
		m_encp[i] = 0;
		m_error[i] = 0;
	}
	g_factcfg.Naxis = 4;
#ifdef errrrrr
#else
	memcpy(g_factcfg.sysName, _T("可编程通用运动控制系统"), sizeof(_T("可编程通用运动控制系统")));
	memcpy(g_factcfg.factName, _T("广州研为电子科技有限公司"), sizeof(_T("广州研为电子科技有限公司")));
	memcpy(g_factcfg.web, _T("www.gzyanwei.com"), sizeof(_T("www.gzyanwei.com")));
	memcpy(g_factcfg.phone, _T("020-39337878"), sizeof(_T("020-39337878")));
	memcpy(g_factcfg.address, _T("广州市大学城外环东路232号研发东区A432"), sizeof(_T("广州市大学城外环东路232号研发东区A432")));
#endif
	for(i=0; i<INPUT_NUM; i++){
		g_iomap.mapI[i].bit = i;
		g_iomap.mapI[i].loc = i > 15 ? gin2Loc : gin1Loc;
		g_iomap.mapI[i].axis = 0;
	}
	for(i=0; i<OUTPUT_NUM; i++){
		g_iomap.mapO[i].bit = i;
		g_iomap.mapO[i].loc = i > 15 ? gout2Loc : gout1Loc;
		g_iomap.mapO[i].axis = 0;
	}
/*	for(i=0; i<LED_NUM; i++){
		g_factcfg.mapLed[i].bit = i;
		g_factcfg.mapLed[i].loc = gout2Loc;
		g_factcfg.mapLed[i].axis = 0;
	}
	for(i=0; i<KEY_NUM; i++){
		g_factcfg.mapKey[i].bit = i;
		g_factcfg.mapKey[i].loc = gin2Loc;
		g_factcfg.mapKey[i].axis = 0;
		m_key[i] = SW_INPUT_OPEN;
	}*/
	g_fn14 = new CFont;
	g_fn14->CreateFont(30,            // nHeight 字体的高度
		 0,           // nWidth 字体的宽度。
		 0,           // nEscapement 字体的倾斜角
		 0,           // nOrientation 字体的倾斜角
		 FW_BOLD,     // nWeight 字体的粗细。
		 FALSE,        // bItalic 字体是否斜体。
		 FALSE,       // bUnderline 字体是否有下划线。
		 0,           // cStrikeOut 字体是否有删除线
		 GB2312_CHARSET,              // nCharSet 字体使用的字符集。
		 OUT_DEFAULT_PRECIS,        // nOutPrecision 如何选择合适的字体。
		 CLIP_DEFAULT_PRECIS,       // nClipPrecision 用来确定裁剪的精度。
		 DEFAULT_QUALITY,           // nQuality 怎么样跟选择的字体相符合。
		 DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 间距标志和属性标志
		 _T("隶书")); //_T("Arial"));             // lpszFac字体的名称。
}

CIMC_GenericDlg::~CIMC_GenericDlg()
{
	delete g_fn14;
}
void CIMC_GenericDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIMC_GenericDlg, CDialog)
//	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#define MY_BKCOLOR RGB(0,0,230)

// CIMC_GenericDlg 消息处理程序

BOOL CIMC_GenericDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	m_brush.CreateSolidBrush(MY_BKCOLOR);

	//让程序全屏
#if defined(WINCE)
	int iFullWidth = GetSystemMetrics(SM_CXSCREEN) + 6;
	int iFullHeight = GetSystemMetrics(SM_CYSCREEN) + 6;
	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, -3, -3, iFullWidth, iFullHeight, SWP_NOOWNERZORDER|SWP_SHOWWINDOW|WS_EX_TOPMOST);
#else
	LONG lStyle = ::GetWindowLong(this->m_hWnd, GWL_STYLE);
	::SetWindowLong(this->m_hWnd, GWL_STYLE, lStyle | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU);
//	::SetWindowPos(this->m_hWnd, NULL, 0, 0, 0, 0,
//	SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);

#endif
	//************************************************************************************************************
	// TODO: 在此添加额外的初始化代码
#if defined(WINCE)
	SipShowIM(SIPF_OFF);
#endif

	CreateSysDir();
	ReadFactCfg();
	ReadFactPolar();
	ReadIOMap();
	ReadWarn();
	ReadCfg();
	g_Naxis = g_factcfg.Naxis;

	StartLogo();
	
#if defined(WINCE)
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(g_fn14);
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(g_factcfg.sysName);
	CString str;
	m_sysTime = CTime::GetCurrentTime();
	UINT ret = SetTimer(TIMER_SYSTIME,60000, NULL);
	str = m_sysTime.Format(_T("%H:%M"));
	SetDlgItemText(IDC_STATIC_SYS_TIME, str);
#else
	GetDlgItem(IDC_STATIC_TITLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_SYS_TIME)->ShowWindow(SW_HIDE);
	SetWindowText(g_factcfg.sysName);
#endif
	

	m_maindlg.SetMainDlgPtr(this);
	m_FactoryDlg.SetMainDlgPtr(this);
	m_SysDlg.SetMainDlgPtr(this);
	m_homeDlg.SetMainDlgPtr(this);
	m_sinfoDlg.SetMainDlgPtr(this);
	m_fileDlg.SetMainDlgPtr(this);
	m_debugDlg.SetMainDlgPtr(this);

	m_maindlg.Create(IDD_DLG_MAIN, this);
	m_FactoryDlg.Create(IDD_DLG_FACT, this);
	m_SysDlg.Create(IDD_DLG_SYS, this);
	m_homeDlg.Create(IDD_DLG_FIND_HOME, this);
	m_sinfoDlg.Create(IDD_DLG_SYS_INFO, this);
	m_fileDlg.Create(IDD_DLG_FILE, this);
	m_debugDlg.Create(IDD_DLG_DEBUG, this);

	m_maindlg.ShowWindow(SW_HIDE);
	m_FactoryDlg.ShowWindow(SW_HIDE);
	m_SysDlg.ShowWindow(SW_HIDE);
	m_homeDlg.ShowWindow(SW_HIDE);
	m_sinfoDlg.ShowWindow(SW_HIDE);
	m_fileDlg.ShowWindow(SW_HIDE);
	m_debugDlg.ShowWindow(SW_HIDE);

	//
	MoveDlg();
	
	if(!m_imc.OpenDev()){
		StartOpenTimer();
	//	title += _T(" - 设备没有连接");
	}else{
		if(!DebugVersion()){
			CString title;
			m_imc.CloseDev();
			title += _T(" - 试用版已到期");
#if defined(WINCE)
			GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(title);
#else
			SetWindowText(title);
#endif
		}
	}

//	CString title = g_factcfg.sysName;
	if(m_imc.IsOpen()){
		//SetTimer(TIMER_GET_ENCP, 40, NULL);
		SetTimer(TIMER_KEY_INPUT, 1000, NULL);
	}

	if(!IsPasswordOK(MY_PW_LOGIN)) 
		exit(0);

	WCHAR srcpath[256];
	if(ReadCurFile(srcpath))
		m_maindlg.LoadSGCfile(srcpath);
	
	if(g_pinfodlg) g_pinfodlg->OnCancel();
	m_maindlg.ShowWindow(SW_SHOW);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CIMC_GenericDlg::StartOpenTimer()
{
	SetTimer(TIMER_DEV_OPEN, 1000, NULL);
}
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CIMC_GenericDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_IMC_GENERIC_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_IMC_GENERIC_DIALOG));
	}
}
#endif

void CIMC_GenericDlg::StartLogo()
{
	g_pinfodlg = new CLogoInfo;
	g_pinfodlg->Create(IDD_DLG_LOGO,this);
	g_pinfodlg->ShowWindow(SW_SHOW);
}
//防止使用Input Panel时任务栏出现*******************************************************************

void CIMC_GenericDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CWnd::OnActivate(nState, pWndOther, bMinimized);  //注意这里从CWnd继承        
//	SHFullScreen( this->m_hWnd, SHFS_HIDETASKBAR);////隐藏任务栏
}

void CIMC_GenericDlg::MoveDlg()
{
	CRect rc,rc1, rcb,rct;
	GetClientRect(&rc);
//	GetWindowRect(&rc);
#if defined(WINCE)
	GetDlgItem(IDC_STATIC_TITLE)->GetWindowRect(&rcb);
	GetDlgItem(IDC_STATIC_SYS_TIME)->GetWindowRect(&rct);
	int width = rct.Width();
	rct.right = rc.right;
	rct.left = rc.right - width;
	rcb.right = rct.left - 2;
	GetDlgItem(IDC_STATIC_TITLE)->MoveWindow(&rcb);
	GetDlgItem(IDC_STATIC_SYS_TIME)->MoveWindow(&rct);
	rc.top = rcb.bottom + 4;
#endif
	m_maindlg.MoveWindow(rc);
	m_SysDlg.MoveWindow(rc);
	m_FactoryDlg.MoveWindow(rc);
	m_homeDlg.MoveWindow(rc);
	m_fileDlg.MoveWindow(rc);
	m_sinfoDlg.MoveWindow(rc);
	m_debugDlg.MoveWindow(rc);

	m_isInit = TRUE;
}

HBRUSH CIMC_GenericDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  在此更改 DC 的任何特性
	if(nCtlColor ==  CTLCOLOR_STATIC ) { 
		pDC->SetTextColor(RGB(250,250,250));
	//	return m_brush; //返加刷子
	}
		pDC->SetBkColor(MY_BKCOLOR);
		return m_brush; //返加刷子
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CIMC_GenericDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
//	if(m_isInit) 
//		MoveDlg();
}

void CIMC_GenericDlg::ShowDlg(int dlg)
{
	if(GetThreadSt()) return;
	if(m_curdlg == dlg) return;
	switch(m_curdlg)
	{
	case JM_MAIN:	m_maindlg.ShowWindow(SW_HIDE); break;
	case JM_SYS:	m_SysDlg.ShowWindow(SW_HIDE); break;
	case JM_FACT:	m_FactoryDlg.ShowWindow(SW_HIDE); break;
	case JM_HOME:	m_homeDlg.ShowWindow(SW_HIDE); break;
	case JM_SINFO:	m_sinfoDlg.ShowWindow(SW_HIDE); break;
	case JM_FILE:	m_fileDlg.MyHideWindow(); break;
	case JM_DEBUG:	m_debugDlg.MyHideWindow(); break;
	default: return;
	}
	m_curdlg = dlg;
	switch(m_curdlg)
	{
	case JM_MAIN:	m_maindlg.ShowEncpDlg();	m_maindlg.ShowWindow(SW_SHOW); m_maindlg.SetFocus(); break;
	case JM_SYS:	m_SysDlg.UpdateCtr(); m_SysDlg.ShowWindow(SW_SHOW); m_SysDlg.SetFocus(); break;
	case JM_FACT:	m_FactoryDlg.ShowWindow(SW_SHOW); m_FactoryDlg.ShowDlg(FACT_AXIS); break;
	case JM_HOME:	m_homeDlg.UpdateCtr(); m_homeDlg.ShowWindow(SW_SHOW); m_homeDlg.SetFocus(); break;
	case JM_SINFO:	m_sinfoDlg.UpdateInfo(); m_sinfoDlg.ShowWindow(SW_SHOW); break;
	case JM_FILE:	m_fileDlg.MyShowWindow();  break;
	case JM_DEBUG:	m_debugDlg.UpdateCtr(); m_debugDlg.ShowWindow(SW_SHOW); break;
	}
}

void CIMC_GenericDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_bChange){
		int res = MessageBox(_T("是否保存程序？"), _T("提示"), MB_YESNOCANCEL);
		if(res == IDYES){
			m_maindlg.OnBnClickedBnSaveFile();
		}else if(res == IDCANCEL)
			return;
	}
	m_maindlg.DeleteAllProgramData();
	CDialog::OnClose();
}
BOOL CIMC_GenericDlg::IsPasswordOK(int type)
{
	switch(type)
	{
	case MY_PW_FACT:	if(g_factcfg.PWfact[0] == 0) return TRUE; break;
	case MY_PW_LOGIN:	if(g_cfg.PWlogin[0] == 0) return TRUE; break;
	case MY_PW_EDIT:	if(g_cfg.PWEdit[0] == 0) return TRUE; break;
	case MY_PW_SYS:		if(g_cfg.PWSys[0] == 0) return TRUE; break;
	case MY_PW_RUN:		if(g_cfg.PWRun[0] == 0) return TRUE; break;
	default: return FALSE;
	}
	CMyPassWord dlg;
	dlg.SetType(type);
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
		return TRUE;
	return FALSE;
}
//************************************************************************************************
//文件相关
//************************************************************************************************

BOOL CIMC_GenericDlg::IsFileDirExist(CString dir)
{//判断文件或目录是否存在
	WIN32_FIND_DATA fd; 
	HANDLE hd = INVALID_HANDLE_VALUE; 	
	hd=::FindFirstFile(dir,&fd); 
	if(INVALID_HANDLE_VALUE != hd) 
		return TRUE;
	return FALSE;
}
BOOL CIMC_GenericDlg::CreateSysDir()
{//创建目录
	CString dir, file;
	SECURITY_ATTRIBUTES attrib;
    attrib.bInheritHandle = FALSE;
    attrib.lpSecurityDescriptor = NULL;
    attrib.nLength = sizeof(SECURITY_ATTRIBUTES);
#if defined(WINCE)
	dir = SYS_FILE_DIR;
#else
	dir = GetMyMFCDir();
#endif
	if(!IsFileDirExist(dir))
	{
		::CreateDirectory(dir, &attrib);
	}
#if defined(WINCE)
	file = CFG_FILE_DIR;
#else
	file = dir + CFG_FILE_DIR;
#endif
	if(!IsFileDirExist(file))
	{
		::CreateDirectory(file, &attrib);
	}
#if defined(WINCE)
	file = SAV_FILE_DIR;
#else
	file = dir + SAV_FILE_DIR;
#endif
	if(!IsFileDirExist(file))
	{
		::CreateDirectory(file, &attrib);
	}
	return TRUE;
}
void CIMC_GenericDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString title;
	switch(nIDEvent)
	{
	case TIMER_SYSTIME:
#if defined(WINCE)
		{
		CString str;
		m_sysTime = CTime::GetCurrentTime();
		str = m_sysTime.Format(_T("%H:%M"));
		SetDlgItemText(IDC_STATIC_SYS_TIME, str);
		}
#endif
		break;
	case TIMER_DEV_OPEN: 
		title = g_factcfg.sysName;
		if(m_imc.OpenDev()){
			KillTimer(TIMER_DEV_OPEN);
			if(!DebugVersion()){
				m_imc.CloseDev();
				title += _T(" - 试用版已到期");
				GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(title);
				break;
			}
			//SetTimer(TIMER_GET_ENCP, 40, NULL);
			SetTimer(TIMER_KEY_INPUT, 1000, NULL);
#if defined(WINCE)
			GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(title);
#else
			SetWindowText(title);
#endif
		//	m_maindlg.m_TStatusdlg.SetEncpTimer();
//			g_Naxis = m_imc.m_Naxis;
		}else{
			title += _T(" - 设备没有连接");
#if defined(WINCE)
			GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(title);
#else
			SetWindowText(title);
#endif
		}
		break;
	case TIMER_GET_ENCP: 
		m_imc.GetEncp(m_encp, m_axis, g_Naxis);
		break;
	case TIMER_KEY_INPUT: 
		short key[KEY_NUM];
		KillTimer(TIMER_KEY_INPUT);
		if(m_imc.KeyInPut(key)== IMC_OK){
			if(m_key[KEY_RUN] != key[KEY_RUN]){
				if(key[KEY_RUN] == SW_INPUT_CLOSE){
					if(m_curdlg == JM_MAIN)
						m_maindlg.OnBnClickedBnRun();
				}
				m_key[KEY_RUN] = key[KEY_RUN];
			}
			if(m_key[KEY_PAUSE] != key[KEY_PAUSE]){
				if(key[KEY_PAUSE] == SW_INPUT_CLOSE){
					if(m_curdlg == JM_MAIN)
						m_maindlg.OnBnClickedBnPause();
				}
				m_key[KEY_PAUSE] = key[KEY_PAUSE];
			}
			if(m_key[KEY_EMSTOP] != key[KEY_EMSTOP])
			{
				if(key[KEY_EMSTOP] == SW_INPUT_CLOSE){

					//RedLedOn();
					//m_maindlg.MahinEndTip(3);
					
					if(m_curdlg == JM_MAIN)
						m_maindlg.OnBnClickedBnEmstop();//急停
				}
				else
				{
					//RedLedOff();
					//m_maindlg.MahinEndTip(0);

				}
				m_key[KEY_EMSTOP] = key[KEY_EMSTOP];
			}
			if(m_key[KEY_RESET] != key[KEY_RESET]){
				if(key[KEY_RESET] == SW_INPUT_CLOSE){
					if(m_curdlg == JM_MAIN)
						m_maindlg.OnBnClickedBnReset();//复位
				}
				m_key[KEY_RESET] = key[KEY_RESET];
			}
		}
		EmstopInput();
		ErrorShow();
		SetTimer(TIMER_KEY_INPUT, GET_KEY_INPUT_TIME, NULL);
		break;
	case TIMER_MACHIN_TIMING:
		m_time ++;
		m_timeTotal ++;
		m_maindlg.ShowMachinTime(m_time);
		m_maindlg.ShowMachinTimeTotal(m_timeTotal);
	}
	CDialog::OnTimer(nIDEvent);
}
void CIMC_GenericDlg::GetCurEncp(long *encp)
{
	memcpy(encp, m_encp, sizeof(long) *g_Naxis);
}

UINT ErrorThread(PVOID param)
{
	CIMC_GenericDlg *pdlg = (CIMC_GenericDlg*)param;
	CString str, tmp;
	BOOL isOk = TRUE, isclr[16];
	WORD *err;
	pdlg->m_errRunT = TRUE;
	for(int i=0; i<16; i++)
		isclr[i] = TRUE;
//	while(1)
	{
		str = _T("");
		err = pdlg->GetErrorVal();
		for(int i=0; i<g_Naxis; i++)
		{
			if(err[i]){
				if(err[i] & 0x80){
					isOk = FALSE;
					tmp.Format(_T("%s 位置误差超限\r\n"), g_AxisName[i]);
					str += tmp;	
				}else
				if(err[i] & 0x2000){
					isOk = FALSE;
					tmp.Format(_T("%s 速度超限\r\n"), g_AxisName[i]);
					str += tmp;
				}else
				if(err[i] & 0x4000){
					isOk = FALSE;
					tmp.Format(_T("%s 加速度超限\r\n"), g_AxisName[i]);
					str += tmp;
				}else
				if(err[i] & 0x40){//伺服报警
					isOk = FALSE;
					tmp.Format(_T("%s 伺服报警\r\n"), g_AxisName[i]);
					str += tmp;
				}
				if(err[i] & 0x01){//正限位
					tmp.Format(_T("%s 正方向限位\r\n"), g_AxisName[i]);
					pdlg->m_maindlg.MahinEndTip(tmp);
					isclr[i] = FALSE;
				}else
				if(err[i] & 0x02){//负限位
					tmp.Format(_T("%s 负方向限位\r\n"), g_AxisName[i]);
					pdlg->m_maindlg.MahinEndTip(tmp);
					isclr[i] = FALSE;
				}
			}else{
				if(!isclr[i]){
					pdlg->m_maindlg.MahinEndTip(_T(""));
					isclr[i] = TRUE;
				}
			}
		}
		if(isOk == FALSE){
			AfxMessageBox(str);
			isOk = TRUE;
		}
		Sleep(100);
	}
	pdlg->m_errRunT = FALSE;
	return 0;
}
WORD *CIMC_GenericDlg::GetErrorVal()
{
	return m_error;
}
void CIMC_GenericDlg::ErrorShow()
{
	if( m_imc.GetError(m_error, m_axis, g_Naxis) == IMC_OK){
	/*	if(m_errRunT == FALSE){
			m_errRunT = TRUE;
			AfxBeginThread(ErrorThread, this);
		}*/
		ErrorThread(this);
	}
}


void CIMC_GenericDlg::EmstopInput()
{//按下急停开关
	short key;
	if(IMC_OK == m_imc.GetEmstop(&key)){
		if(key != m_emstopkey){
			m_emstopkey = key;
			if(m_emstopkey/* == SW_INPUT_OPEN*/){//急停键按下,停止所有程序
				m_maindlg.OnBnClickedBnEmstop();
		//		m_warndlg.SetWarnText(_T("急停开关已按下！\r\n\r\n放开急停开关恢复！"));	
				m_maindlg.MahinEndTip(2);
				RedLedOn();
			}else/* if(m_emstopkey == SW_INPUT_CLOSE)*/{//急停键放开,恢复所有程序
				m_imc.ReEnaAxis();
				m_maindlg.MahinEndTip(0);
				RedLedOff();
			}
		}
	}
}
//*************************************************************************************************************
//
//*************************************************************************************************************
//UINT ThreadRun(PVOID param);
UINT ThreadRun_new(PVOID param);
BOOL CIMC_GenericDlg::GetThreadSt()
{//返回线程运行状态
	return m_threadRun;
}
BOOL CIMC_GenericDlg::IsPause()
{
	return m_threadPause;
}
void CIMC_GenericDlg::StartMatchin(BOOL mode)
{//启动线程
	m_machinMode = mode;

	if(m_threadPause){
		m_threadPause = FALSE;
		m_imc.SetPauseStatus(FALSE);
		m_maindlg.EnableRunKey();
		YellowLedOff();
	}else if(m_threadStep){
	//	m_threadStep = FALSE;
		m_threadPause = FALSE;
	}else if(!GetThreadSt()){
		m_threadPause = FALSE;
		m_threadReset = FALSE;
		m_threadStop = FALSE;
		m_imc.StopFun(FALSE);
		if(m_machinMode == MACHIN_STEP)
			m_threadStep = TRUE;
		else
			m_threadStep = FALSE;
		YellowLedOff();
		RedLedOff();
		SetTimer(TIMER_MACHIN_TIMING, 1000, NULL);
		AfxBeginThread(ThreadRun_new, this);
	}else
		StopMatchin();
}
void CIMC_GenericDlg::PauseMatchin()
{//加工完当前行后暂停线程
	if(!GetThreadSt()) return;
	m_threadPause = TRUE;
	m_imc.SetPauseStatus(TRUE);
	YellowLedOn();
	m_maindlg.EnableRunKey();
}
void CIMC_GenericDlg::StopMatchin()
{//加工完最后一条后退出线程
	m_threadPause = FALSE;
	m_threadStop = TRUE;
	m_maindlg.MahinEndTip(1);
}
UINT EmstopThreadRun(PVOID param);
void CIMC_GenericDlg::EmstopMatchin()
{//立即退出线程
	if(!GetThreadSt()) return;
	BOOL step = m_threadPause;
	m_threadPause = FALSE;
	m_threadReset = TRUE;
	m_imc.StopFun(TRUE);//停止循环，如果有的话
	m_imc.StopDev();//急停
	if(!m_EmstopRun && !step && m_machinMode != MACHIN_STEP)
		AfxBeginThread(EmstopThreadRun, this);
	DoEvents();
	Sleep(200);
	m_imc.StopReset();
}

UINT ResetThreadRun(PVOID param);
void CIMC_GenericDlg::ResetMatchin()
{
	if(!GetThreadSt()){
		m_threadReset = FALSE;
		m_imc.StopFun(FALSE);
		AfxBeginThread(ResetThreadRun, this);
	}else{
		EmstopMatchin();
	}
}
void CIMC_GenericDlg::RedLedOn()
{
	m_maindlg.SetBmpVal(2, 1);
	m_imc.LedCtr(LED_RED, LED_ON, SEL_PFIFO1);
}
void CIMC_GenericDlg::RedLedOff()
{
	m_maindlg.SetBmpVal(2, 0);
	m_imc.LedCtr(LED_RED, LED_OFF, SEL_PFIFO1);
}
void CIMC_GenericDlg::YellowLedOn()
{
	m_maindlg.SetBmpVal(1, 1);
	m_imc.LedCtr(LED_YELLOW, LED_ON, SEL_PFIFO1);
}
void CIMC_GenericDlg::YellowLedOff()
{
	m_maindlg.SetBmpVal(1, 0);
	m_imc.LedCtr(LED_YELLOW, LED_OFF, SEL_PFIFO1);
}
void CIMC_GenericDlg::GreedLedOn()
{
	m_maindlg.SetBmpVal(0, 1);
	m_imc.LedCtr(LED_GREED, LED_ON, SEL_PFIFO1);
}
void CIMC_GenericDlg::GreedLedOff()
{
	m_maindlg.SetBmpVal(0, 0);
	m_imc.LedCtr(LED_GREED, LED_OFF, SEL_PFIFO1);
}
void CIMC_GenericDlg::SetCurLine(int line)
{
	m_curLine = line;
}
int CIMC_GenericDlg::GetCurLine()
{
	return m_curLine;
}

PROGRAM_DATA  *g_phead = NULL;
int g_cmdNum = 0;
UINT ThreadRun_new(PVOID param)
{
	CIMC_GenericDlg* pdlg = (CIMC_GenericDlg*)param;
	PROGRAM_DATA *pdata;	//编程数据
	short count;
	int line;
	int matchinNum = 0;
	BOOL ispause = FALSE;
	pdlg->m_threadRun = TRUE;
	pdlg->m_maindlg.EnableRunKey();
	pdlg->m_maindlg.ShowMachinStatus();
	pdlg->m_imc.SetPauseStatus(FALSE);
	pdlg->GreedLedOn();
	pdlg->YellowLedOff();
	g_phead = pdlg->m_maindlg.GetRunData(&g_cmdNum);
	while(!pdlg->m_threadStop && !pdlg->m_threadReset && g_cmdNum > 0)
	{//加工完最后一个动作后退出
		pdlg->SetCurLine(0);
		pdata = g_phead + pdlg->GetCurLine();
		count = 0;
		pdlg->m_time = 0;
		matchinNum ++;
		pdlg->m_imc.SetData16(startpath1Loc, -1, SEL_IFIFO);
		while(pdata != NULL && !pdlg->m_threadReset)
		{
			line = pdlg->GetCurLine();
			if(line >= g_cmdNum) break;
			if(pdata->type == CMD_END) break;

			pdlg->m_maindlg.SetShow(line);
			pdlg->SetCurLine(line + 1);
			
		//	pdlg->m_imc.SetData16(user16b0Loc, count, SEL_PFIFO1);
			pdata->isWT = 0;
			while(!pdlg->RunAll(pdata)){
				if(pdlg->m_threadReset) break;
				Sleep(10);
			};
		/*	while(!pdlg->m_threadReset){
				pdlg->m_imc.GetData16(user16b0Loc, &count1);
				if(count1 == count) break;
				else Sleep(50);
			}*/
			if(pdlg->m_machinMode == MACHIN_STEP){//单步的时候暂停
				pdlg->PauseMatchin();
			}
			if(pdlg->m_threadPause){
				pdlg->m_maindlg.EnableRunKey();
				ispause = TRUE;
			}
			while(pdlg->m_threadPause && !pdlg->m_threadStop && !pdlg->m_threadReset){
				Sleep(50);//暂停
			}
			if(ispause){
				pdlg->m_maindlg.EnableRunKey();
				pdlg->m_imc.SetPauseStatus(FALSE);
				ispause = FALSE;
			}
			count ++;
			pdata = g_phead + pdlg->GetCurLine();
		}
		
		pdlg->WaitAllOver();//等待运动完成

		if(pdlg->m_machinMode == MACHIN_STEP)//单步
			break;//不计数
		pdlg->m_matchinNum ++;
		pdlg->m_maindlg.ShowMachinNum(pdlg->m_matchinNum);
		Sleep(500);//等待200毫秒后再重新开始
		if(pdlg->m_machinMode == MACHIN_SINGLE)//单步
			break;//计数后跳出
	}
	if(pdlg->m_machinMode == MACHIN_STEP)
	{
		pdlg->m_maindlg.ShowStepStart(pdlg->GetCurLine());
	}
	pdlg->m_threadStep = FALSE;
	pdlg->m_threadRun = FALSE;
	pdlg->KillTimer(TIMER_MACHIN_TIMING);
	pdlg->m_maindlg.EnableRunKey();
	pdlg->m_maindlg.ShowMachinStatus();
	pdlg->GreedLedOff();
	pdlg->YellowLedOn();
	if(!pdlg->m_emstopkey)
		pdlg->m_maindlg.MahinEndTip(0);
	if(g_phead) delete [] g_phead;
	g_phead = NULL;
	return 0;
}
//复位线程
UINT ResetThreadRun(PVOID param)
{
	CIMC_GenericDlg* pdlg = (CIMC_GenericDlg*)param;
	PROGRAM_DATA *pdata;	//编程数据
	int line;
	int matchinNum = 0;
	BOOL ispause = FALSE;
	pdlg->m_threadRun = TRUE;
	g_phead = pdlg->m_maindlg.GetResetData(&g_cmdNum);
	pdlg->m_maindlg.EnaResetBn(FALSE);

	pdlg->m_imc.SetPauseStatus(FALSE);
	pdlg->GreedLedOn();
	pdlg->YellowLedOff();

	pdlg->SetCurLine(0);
	pdata = g_phead + pdlg->GetCurLine();
	pdlg->m_imc.SetData16(startpath1Loc, -1, SEL_IFIFO);
	while(pdata != NULL && !pdlg->m_threadReset)
	{
		line = pdlg->GetCurLine();
		if(line >= g_cmdNum) break;
		pdata = g_phead + line;
		if(pdata->type == CMD_END) break;

		pdlg->SetCurLine(line + 1);
		
		pdata->isWT = 0;
		while(!pdlg->RunAll(pdata)){
			if(pdlg->m_threadReset) break;
			Sleep(10);
		};
	}
	pdlg->WaitAllOver();//等待运动完成
		
	pdlg->m_threadRun = FALSE;
	if(g_phead) delete [] g_phead;
	g_phead = NULL;
	pdlg->m_maindlg.EnaResetBn(TRUE);
	pdlg->GreedLedOff();
	pdlg->YellowLedOn();
	return 0;
}
//急停按钮需要执行的线程，不运行运动控制指令
PROGRAM_DATA *g_phead_em;
int g_cmdNum_em;
int g_emLine;
UINT EmstopThreadRun(PVOID param)
{
	CIMC_GenericDlg* pdlg = (CIMC_GenericDlg*)param;
	PROGRAM_DATA *pdata;	//编程数据
	int line;
	int matchinNum = 0;
	BOOL ispause = FALSE;
	pdlg->m_EmstopRun = TRUE;
	g_phead_em = pdlg->m_maindlg.GetEmstopData(&g_cmdNum_em);

	pdlg->m_imc.SetPauseStatus(FALSE);
	g_emLine = 0;
	pdata = g_phead_em + g_emLine;
	pdlg->m_imc.SetData16(startpath1Loc, -1, SEL_IFIFO);
	while(pdata != NULL/* && !pdlg->m_threadReset*/)
	{
		line = g_emLine;
		if(line >= g_cmdNum_em) break;
		pdata = g_phead_em + line;
		if(pdata->type == CMD_END) break;

		g_emLine ++;
		
		pdata->isWT = 0;
		while(!pdlg->RunEmstop(pdata)){
		//	if(pdlg->m_threadReset) break;
			Sleep(10);
		};
	}
	pdlg->WaitAllOver();//等待运动完成
		
	pdlg->m_EmstopRun = FALSE;
	if(g_phead_em) delete [] g_phead_em;
	g_phead_em = NULL;
//	pdlg->m_maindlg.EnaResetBn(TRUE);
//	pdlg->GreedLedOff();
//	pdlg->YellowLedOn();
	return 0;
}

BOOL CIMC_GenericDlg::RunAll(PROGRAM_DATA *pdata)
{
	switch(pdata->type)
	{
	case CMD_LINKAGE:	return LineMulFun(pdata); //多轴联动
	case CMD_ARC:		return ArcFun(pdata); //圆弧
	case CMD_OUTPUT:	return OutputFun(pdata); //输出
	case CMD_INPUT:		return InputFun(pdata); //输入
	case CMD_JUMP:		SetCurLine(pdata->jumpLine-1); return TRUE;//跳转
	case CMD_LOOP:		return LoopFun(pdata); //循环开始
	case CMD_DELAY:		return DelayFun(pdata); //延时
	case CMD_GOHOME:	return GohomeFun(pdata); //回零
	case CMD_GHWHIRL:	return WhirlFun(pdata); //回零
	case CMD_VEL:		return VelFun(pdata); //匀速
	case CMD_POS:		return PosFun(pdata); //点位
	case CMD_WAIT:		return WaitFun(pdata); //等待
	case CMD_END:		break;//程序结束
	case CMD_WEND:		break;//循环结束
	}
	return TRUE;
}
BOOL CIMC_GenericDlg::RunEmstop(PROGRAM_DATA *pdata)
{
	switch(pdata->type)
	{
//	case CMD_LINKAGE:	return LineMulFun(pdata); //多轴联动
//	case CMD_ARC:		return ArcFun(pdata); //圆弧
	case CMD_OUTPUT:	return OutputFun(pdata); //输出
	case CMD_INPUT:		return InputFun(pdata); //输入
	case CMD_JUMP:		g_emLine = pdata->jumpLine-1; return TRUE;//跳转
	case CMD_LOOP:		return LoopFun_em(pdata); //循环开始
//	case CMD_DELAY:		return DelayFun(pdata); //延时
//	case CMD_GOHOME:	return GohomeFun(pdata); //回零
//	case CMD_GHWHIRL:	return WhirlFun(pdata); //回零
//	case CMD_VEL:		return VelFun(pdata); //匀速
//	case CMD_POS:		return PosFun(pdata); //点位
//	case CMD_WAIT:		return WaitFun(pdata); //等待
	case CMD_END:		break;//程序结束
	case CMD_WEND:		break;//循环结束
	}
	return TRUE;
}

int CIMC_GenericDlg::GetUseFIFO(PROGRAM_DATA *pdata)
{
	return SEL_PFIFO1;
}
BOOL CIMC_GenericDlg::WaitAllOver()
{//等待所有运动结束
	short count[MAX_NAXIS], count1, axis, i;
	int isOk;
	Sleep(100);
	while(!m_threadReset){//等待运动完成
		if(m_imc.GetData16(PFIFOcnt1Loc, &count1) == IMC_OK){
			if(count1 == 0) break;
		}
		while(m_threadPause && !m_threadStop && !m_threadReset){
			Sleep(50);//暂停
		}
		Sleep(50);
	}
	while(!m_threadReset){//等待运动完成
		isOk = TRUE;
		if(m_imc.GetMoving(count) == IMC_OK)
		{
			for(i=0; i<g_Naxis; i++){
				axis = g_factcfg.g_mapAxis[i];
				if(count[axis]) isOk = FALSE;
			}
			if(isOk) 
				break;
		}
		while(m_threadPause && !m_threadStop && !m_threadReset){
			Sleep(50);//暂停
		}
		Sleep(50);
	}
	return TRUE;
}
BOOL CIMC_GenericDlg::DelayFun(PROGRAM_DATA *pdata)
{
	long time;

	WaitAllOver();
	time = pdata->delay;
	while(time > 0){
		if(time > 500){
			Sleep(500);
			time -= 500;
		}else{
			Sleep(time);
			time = 0;
		}
	}
	return TRUE;

	int fifo = GetUseFIFO(pdata);
	if(m_imc.WaitTime(pdata->delay, fifo) == IMC_OK)
		return TRUE;
	return FALSE;
}
BOOL CIMC_GenericDlg::LoopFun(PROGRAM_DATA *pdata)
{
	DWORD i, index;
	PROGRAM_DATA * pd;
	for(i=0; i<pdata->loopNum; i++)
	{
		index = pdata->jumpLine-1;
		pd = g_phead + index;
		while(pd  && !m_threadReset && index < g_cmdNum)
		{
			if(pd->type == CMD_WEND) break;
			while(!RunAll(pd)){
				if(m_threadReset) break;
				Sleep(10);
			}
			index ++;
			pd = g_phead + index;
		}
	}
	return TRUE;
}
BOOL CIMC_GenericDlg::LoopFun_em(PROGRAM_DATA *pdata)
{
	DWORD i, index;
	PROGRAM_DATA * pd;
	for(i=0; i<pdata->loopNum; i++)
	{
		index = pdata->jumpLine-1;
		pd = g_phead_em + index;
		while(pd/*  && !m_threadReset */&& index < g_cmdNum_em)
		{
			if(pd->type == CMD_WEND) break;
			while(!RunEmstop(pd)){
				if(m_threadReset) break;
				Sleep(10);
			}
			index ++;
			pd = g_phead_em + index;
		}
	}
	return TRUE;
}
BOOL CIMC_GenericDlg::isInterP()
{
	if((GetCurLine() + 1) >= g_cmdNum) 
		return FALSE;
	else{
		PROGRAM_DATA *ptmp = g_phead + (GetCurLine() + 1);
	//	if(ptmp->type == CMD_LINKAGE || ptmp->type == CMD_ARC)
		if(ptmp->type == CMD_WAIT || ptmp->type == CMD_DELAY)
			return FALSE;
		else return TRUE;
	}
}
BOOL CIMC_GenericDlg::LineMulFun(PROGRAM_DATA *pdata)
{
	int fifo = GetUseFIFO(pdata);
	BOOL isP = isInterP();
	if(m_imc.LineMulCtrl(pdata, fifo, isP) == IMC_OK)
		return TRUE;
	return FALSE;
}
BOOL CIMC_GenericDlg::ArcFun(PROGRAM_DATA *pdata)
{
	int fifo = GetUseFIFO(pdata);
	BOOL isP = isInterP();
	if(m_imc.ArcCtrl(pdata, fifo, isP) == IMC_OK)
		return TRUE;
	return FALSE;
}
BOOL CIMC_GenericDlg::OutputFun(PROGRAM_DATA *pdata)
{
	int fifo = GetUseFIFO(pdata);
	LONGLONG time;
	if(m_imc.OutPutCtrl(pdata, fifo) == IMC_OK){
		if(pdata->InSel & 0xFF){
			StartTimes();
			while(1)
			{
				time = GetTimems();
				if(time > pdata->delay){//超时
#ifdef CHANGE_DATA_0
					if(m_imc.OutPutCtrl(pdata->OutputBit, ((pdata->InSel>>8) & 0xFF), fifo) == IMC_OK)
#else
					if(m_imc.OutPutCtrl((pdata->Output>> 8) & 0xFF, ((pdata->InSel>>8) & 0xFF), fifo) == IMC_OK)
#endif
						return TRUE;
					else return FALSE;
				}else Sleep(10);
			}
		}
		return TRUE;
	}
	return FALSE;
}
BOOL CIMC_GenericDlg::InputFun(PROGRAM_DATA *pdata)
{
	IMC_STATUS status;
	LONGLONG time;
	StartTimes();
	short val, sel;
	while(1){
		status = m_imc.InPutCtrl(pdata, &val);
		if(status == IMC_OK){
#ifdef CHANGE_DATA_0
			if(pdata->InputVal){//联通
#else
			if(pdata->Input & 0xFF){//联通
#endif
				if(val == 0) break;
			}else {//断开
				if(val) break;
			}
		}
		time = GetTimems();
		if(time > pdata->delay){//超时
			if((pdata->InSel>> 8) & 0xFF){//开报警灯
				m_imc.LedCtr(LED_RED, LED_ON, SEL_PFIFO1);
			}
			sel = (pdata->InSel & 0xFF);
			if(sel == 0){//暂停
				PauseMatchin();
			}else if(sel == 1){//跳转
				SetCurLine(pdata->jumpLine-1);
			}else if(sel == 2){//无动作
			}
			if(pdata->homeMode){
				if(pdata->homeBit <= g_warnNum && pdata->homeBit > 0)
					MessageBox(g_warn[pdata->homeBit - 1].warn, _T("提示"));
			}
			break;
		}else
			Sleep(20);
	}
	return TRUE;
}
BOOL CIMC_GenericDlg::GohomeFun(PROGRAM_DATA *pdata)
{
	long i, k=0, axis[MAX_NAXIS];
	int fifo = GetUseFIFO(pdata);
	if(pdata->homeMode == 0)//直接回零
	{
	//	m_imc.GohomeSynCtrl(pdata, fifo);
		m_imc.GohomeSortCtrl(pdata, fifo);
	}else if(pdata->homeMode == 1)//搜零
	{
		if(pdata->homeBit == 0) return TRUE;
		short data,n, sort[MAX_NAXIS];
		for(i=0; i<g_Naxis; i++){
			if(pdata->homeBit & (1<<i)){
				axis[k] = i;
				sort[k++] = pdata->homeSort[i];
			}
		}
		for(n=0; n<g_Naxis; n++){
			for(i=0; i<k; i++){
				if(sort[i] == n){//查找回零顺序相同的轴号
			//		m_imc.SetData16(homedLoc, 0, g_factcfg.g_mapAxis[axis[i]]);
					if(m_imc.IsOfHomed(axis[i])){
						if(g_cfg.homeDir[axis[i]])//往负方向搜零，需要往正方向移动一点点
							m_imc.Jog(MOVE_HOMED_VEL, axis[i]);
						else
							m_imc.Jog(-(MOVE_HOMED_VEL), axis[i]);
						while(m_imc.IsOfHomed(axis[i]) && !m_threadReset);
						m_imc.Jog(0, axis[i]);
					}
					m_imc.FindHome(g_cfg.homeDir[axis[i]], axis[i]);
				}
			}
			Sleep(10);
			for(i=0; i<k; i++){
				if(sort[i] == n){//查找回零顺序相同的轴号
					data = 1;
					while(!m_threadReset){
					//	if(m_imc.GetData16(homedLoc, &data, g_factcfg.g_mapAxis[axis[i]]) == IMC_OK){
						if(m_imc.GetData16(movingLoc, &data, g_factcfg.g_mapAxis[axis[i]]) == IMC_OK){
							if(data == 0)
								break;
							else
								Sleep(10);
						}else Sleep(10);
					}
				}
			}
		}
		m_imc.SetData16(startpath1Loc, -1, SEL_IFIFO);
		m_imc.SetData16(startpath2Loc, -1, SEL_IFIFO);
	}else if(pdata->homeMode == 2)//
	{
		for(i=0; i<g_Naxis; i++)
		{
			if(pdata->homeBit & (1<<i)){
				axis[k++] = g_factcfg.g_mapAxis[i];
			}
		}
		for(i=0; i<k; i++)
			m_imc.SetCurHome(axis[i]);
	}
	return TRUE;
}
BOOL CIMC_GenericDlg::WhirlFun(PROGRAM_DATA *pdata)
{
	short data = 0;
	if(pdata->isWT == 0){
		int fifo = GetUseFIFO(pdata);
		m_imc.GetData16(aioLoc, &data, pdata->homeMode);
		if(data & 0x4){//常开
			m_imc.FindHomeWhirl((pdata->homeBit >> 16) & 0xFF, (pdata->homeBit >> 24) & 0xFF, pdata->homeMode, fifo);
		}else{//常闭
			m_imc.FindHomeWhirl(pdata->homeBit & 0xFF, (pdata->homeBit >> 8) & 0xFF, pdata->homeMode, fifo);
		}
		pdata->isWT = 1;
	}
	if(pdata->isWT == 1){
		m_imc.GetData16(homedLoc, &data, pdata->homeMode);
		if(data == 0)
			return FALSE;
		pdata->isWT = 0;
	}
	return TRUE;
}
	
BOOL CIMC_GenericDlg::VelFun(PROGRAM_DATA *pdata)
{
	int fifo = GetUseFIFO(pdata);
	m_imc.VelCtrl(pdata, fifo);
	return TRUE;
}
BOOL CIMC_GenericDlg::PosFun(PROGRAM_DATA *pdata)
{
	int fifo = GetUseFIFO(pdata);
	m_imc.PosCtrl(pdata, fifo);
	return TRUE;
}

BOOL CIMC_GenericDlg::WaitFun(PROGRAM_DATA *pdata)
{
//	short count;
	short count[MAX_NAXIS], axis, ok = TRUE;
//	m_count ++;
//	int fifo = GetUseFIFO(pdata);
//	m_imc.SetData16(user16b1Loc, m_count, fifo);
/*	if(pdata->WTbit == 0){//等待插补停止
		while(!m_threadReset){
			if(IMC_OK == m_imc.GetData16(pathmoving1Loc, &count[0], 0)){
				if(0 == count[0]) break;
			}
			Sleep(50);
		}
	}else if(pdata->WTbit == 1){//等待点到点运动停止*/
/*		while(!m_threadReset){
			for(int i=0; i<g_Naxis; i++){
				long axis = g_factcfg.g_mapAxis[i];
				m_imc.GetData16(mcsgoLoc, &count[i], axis);
			}
			for(int i=0; i<g_Naxis; i++){
				if(count[i]) break;//只要有1个开始运行就退出
			}
		}*/
		while(!m_threadReset){
			ok = TRUE;
			Sleep(50);
			if(m_imc.GetMoving(count) == IMC_OK)
			{
				for(int i=0; i<g_Naxis; i++){
					axis = g_factcfg.g_mapAxis[i];
					if(count[axis]) ok = FALSE;
				}
				if(ok) 
					break;
			}
			while(m_threadPause && !m_threadStop && !m_threadReset){
				Sleep(50);//暂停
			}
		}
//	}
//	Sleep(50);
	return TRUE;
}


BOOL CIMC_GenericDlg::DebugVersion()
{
#ifdef TRY_VERSION
#endif
	return TRUE;
}
void CIMC_GenericDlg::gotoPos_singleAxis(long axis,long velType,WORD velRatio,double pos)
{
	PROGRAM_DATA pdata;

	pdata.vel = velType;
	pdata.velRatio = velRatio;
	pdata.axis = axis;
	pdata.pos[0] = pos;
//	pdata->isWT = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
	pdata.InSel = 0;
	

	
	PosFun(&pdata);
}

void CIMC_GenericDlg::gotoPos_MultiAxis(char cmdType,double velRatio,double X,double Y,double Z)
{

	PROGRAM_DATA pdata;

	memset(&pdata, 0, sizeof(PROGRAM_DATA));
	
	pdata.type = CMD_LINKAGE;
	pdata.vel = cmdType;//G00,G01
	pdata.velRatio = velRatio;
	pdata.InSel = 0;//绝对位置0，相对位置1	
	pdata.posBit = 0;
	for(int j=0; j<3; j++)
	{	
		//if(j==4)
		//	continue;
		pdata.posBit |= (1 << j);
	}
	pdata.pos[0] = X;
	pdata.pos[1] = Y;//-343.5+36.22
	pdata.pos[2] = Z;
	pdata.pos[3] = 0;
	pdata.pos[4] = 0;
	pdata.pos[5] = 0;		
	
	LineMulFun(&pdata);

	
}

