// dlg/MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "MainDlg.h"
#include "IMC_GenericDlg.h"

#include "ProgramDlg.h"
#include "Manual.h"
#include "MpcDlg.h"
#include "dlg/MyPassWord.h"

//#define WM_MY_PROGRAM_SHOW	WM_USER+1

// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialog)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
	, m_machinSel(2)
{
	m_isEditEN = FALSE;
	m_listFont = NULL;
	m_jpRec = NULL;
	m_naxis = 6;
	m_bmp[0]= (HBITMAP)::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BMP_GOFF));
	m_bmp[1]= (HBITMAP)::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BMP_GON));
	m_bmp[2]= (HBITMAP)::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BMP_YOFF));
	m_bmp[3]= (HBITMAP)::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BMP_YON));
	m_bmp[4]= (HBITMAP)::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BMP_ROFF));
	m_bmp[5]= (HBITMAP)::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BMP_RON));
}

CMainDlg::~CMainDlg()
{
	if(m_listFont)
		delete m_listFont;
	DeleteAllRec();
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Radio(pDX, IDC_RADIO1, m_machinSel);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	ON_BN_CLICKED(IDC_BN_EDIT_EN, &CMainDlg::OnBnClickedBnEditEn)
	ON_BN_CLICKED(IDC_BN_EDIT_CHANGE, &CMainDlg::OnBnClickedBnEditChange)
	ON_BN_CLICKED(IDC_BN_EDIT_ADD_LINE, &CMainDlg::OnBnClickedBnEditAddLine)
	ON_BN_CLICKED(IDC_BN_EDIT_INSERT, &CMainDlg::OnBnClickedBnEditInsert)
	ON_BN_CLICKED(IDC_BN_EDIT_DELETE_ALL, &CMainDlg::OnBnClickedBnEditDeleteAll)
	ON_BN_CLICKED(IDC_BN_EDIT_DELETE, &CMainDlg::OnBnClickedBnEditDelete)
	ON_BN_CLICKED(IDC_BN_LOAD_FILE, &CMainDlg::OnBnClickedBnLoadFile)
	ON_BN_CLICKED(IDC_BN_SAVE_FILE, &CMainDlg::OnBnClickedBnSaveFile)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CMainDlg::OnNMClickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CMainDlg::OnDblclkList1)
	//
	ON_MESSAGE(WM_MY_PROGRAM_SHOW,OnProgramDlg)
	ON_BN_CLICKED(IDC_BN_SYS_CFG, &CMainDlg::OnBnClickedBnSysCfg)
	ON_BN_CLICKED(IDC_BN_NEW_FILE, &CMainDlg::OnBnClickedBnNewFile)
	ON_BN_CLICKED(IDC_BN_RUN, &CMainDlg::OnBnClickedBnRun)
	ON_BN_CLICKED(IDC_BN_PAUSE, &CMainDlg::OnBnClickedBnPause)
	ON_BN_CLICKED(IDC_BN_GOHOME, &CMainDlg::OnBnClickedBnGohome)
	ON_BN_CLICKED(IDC_BN_MANUAL, &CMainDlg::OnBnClickedBnManual)
	ON_BN_CLICKED(IDC_BN_EMSTOP, &CMainDlg::OnBnClickedBnEmstop)
	ON_BN_CLICKED(IDC_BN_FILE_MG, &CMainDlg::OnBnClickedBnFileMg)
	ON_BN_CLICKED(IDC_BN_RESET, &CMainDlg::OnBnClickedBnReset)
	ON_BN_CLICKED(IDC_BTN_RUN_TO_POS_1, &CMainDlg::OnBnClickedBtnRunToPos1)
	ON_BN_CLICKED(IDC_BTN_RUN_TO_POS_2, &CMainDlg::OnBnClickedBtnRunToPos2)
	ON_BN_CLICKED(IDC_BTN_RUN_TO_POS_3, &CMainDlg::OnBnClickedBtnRunToPos3)
	ON_BN_CLICKED(IDC_BTN_RUN_TO_POS_XYZ, &CMainDlg::OnBnClickedBtnRunToPosXyz)
	ON_BN_CLICKED(IDC_BN_ESTOP, &CMainDlg::OnBnClickedBnEstop)
	ON_BN_CLICKED(IDC_BUTTON1, &CMainDlg::OnBnClickedButton1)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CMainDlg 消息处理程序

BOOL CMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
//	SetIcon(m_hIcon, TRUE);			// 设置大图标
//	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitListCtrl();
	GetDlgItem(IDC_BN_EDIT_CHANGE)->EnableWindow(m_isEditEN);
	GetDlgItem(IDC_BN_EDIT_ADD_LINE)->EnableWindow(m_isEditEN);
	GetDlgItem(IDC_BN_EDIT_INSERT)->EnableWindow(m_isEditEN);
	GetDlgItem(IDC_BN_EDIT_DELETE)->EnableWindow(m_isEditEN);
	GetDlgItem(IDC_BN_EDIT_DELETE_ALL)->EnableWindow(m_isEditEN);
	GetDlgItem(IDC_BN_LOAD_FILE)->EnableWindow(m_isEditEN);
	GetDlgItem(IDC_BN_SAVE_FILE)->EnableWindow(m_isEditEN);
	GetDlgItem(IDC_BN_NEW_FILE)->EnableWindow(m_isEditEN);

	SetDlgItemInt(IDC_EDIT1, 1);
	
#if defined(WINCE)
	GetDlgItem(IDC_BN_FILE_MG)->ShowWindow(SW_SHOW);
#else
	GetDlgItem(IDC_BN_FILE_MG)->ShowWindow(SW_HIDE);
#endif
	CIMC_GenericDlg* mdlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
#ifdef PROCESS_TIME
/*	m_TStatusdlg.SetMainDlgPtr(m_mdlg);
	m_TStatusdlg.Create(IDD_DLG_STATUS, this);
	m_TStatusdlg.ShowWindow(SW_SHOW);
	if(mdlg->m_imc.IsOpen()) 
		m_TStatusdlg.SetEncpTimer();*/
	CreateEncpDlg();
	ShowEncpDlg();
#endif
	MoveDlg();
	
	m_machinSel = g_cfg.machinSel + 1;
	UpdateData(FALSE);

	CMyPassWord dlg;
	CIMC_GenericDlg* pdlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	dlg.SetMainDlgPtr(m_mdlg);
	INT_PTR nResponse = dlg.DoModal();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_KEYDOWN || pMsg->message==WM_KEYUP )
	{ 	
		if(pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}
void CMainDlg::CreateEncpDlg()
{
	m_4dlg.SetMainDlgPtr(m_mdlg);
	m_6dlg.SetMainDlgPtr(m_mdlg);
	m_8dlg.SetMainDlgPtr(m_mdlg);
	m_10dlg.SetMainDlgPtr(m_mdlg);
	m_12dlg.SetMainDlgPtr(m_mdlg);
	m_14dlg.SetMainDlgPtr(m_mdlg);
	m_16dlg.SetMainDlgPtr(m_mdlg);
	m_4dlg.Create(IDD_DLG_ENCP_STATUS, this);
	m_6dlg.Create(IDD_DLG_ENCP_STATUS_6, this);
	m_8dlg.Create(IDD_DLG_ENCP_STATUS_8, this);
	m_10dlg.Create(IDD_DLG_ENCP_STATUS_10, this);
	m_12dlg.Create(IDD_DLG_ENCP_STATUS_12, this);
	m_14dlg.Create(IDD_DLG_ENCP_STATUS_14, this);
	m_16dlg.Create(IDD_DLG_ENCP_STATUS_16, this);

}
void CMainDlg::MoveDlg()
{
	CRect rc,rc1, rc2, rc3;
	GetClientRect(&rc);
	GetDlgItem(IDC_STATIC_BOX)->GetWindowRect(&rc1);
	ScreenToClient(&rc1);
	GetDlgItem(IDC_STATIC_EDIT_BOX)->GetWindowRect(&rc2);
	ScreenToClient(&rc2);
#ifdef PROCESS_TIME
	m_4dlg.GetClientRect(&rc3);
	rc3.left -= 5;
	rc3.top = rc2.bottom;
	rc3.bottom = rc.bottom;
	rc3.right = rc1.left - 2;
	m_4dlg.MoveWindow(rc3);
	m_4dlg.MoveWindow(rc3);
	m_6dlg.MoveWindow(rc3);
	m_8dlg.MoveWindow(rc3);
	m_10dlg.MoveWindow(rc3);
	m_12dlg.MoveWindow(rc3);
	m_14dlg.MoveWindow(rc3);
	m_16dlg.MoveWindow(rc3);
#endif
}
void CMainDlg::ShowEncpDlg()
{
	switch(m_naxis)
	{
	case 4:		m_4dlg.ShowWindow(SW_HIDE);		m_4dlg.SetEncpTimer(FALSE);break;
	case 6:		m_6dlg.ShowWindow(SW_HIDE);		m_6dlg.SetEncpTimer(FALSE);break;
	case 8:		m_8dlg.ShowWindow(SW_HIDE);		m_8dlg.SetEncpTimer(FALSE);break;
	case 10:	m_10dlg.ShowWindow(SW_HIDE);	m_10dlg.SetEncpTimer(FALSE);break;
	case 12:	m_12dlg.ShowWindow(SW_HIDE);	m_12dlg.SetEncpTimer(FALSE);break;
	case 14:	m_14dlg.ShowWindow(SW_HIDE);	m_14dlg.SetEncpTimer(FALSE);break;
	case 16:	m_16dlg.ShowWindow(SW_HIDE);	m_16dlg.SetEncpTimer(FALSE);break;
	}
	m_naxis = g_factcfg.Naxis;
	switch(m_naxis)
	{
	case 4:		m_4dlg.ShowWindow(SW_SHOW);		m_4dlg.SetEncpTimer(TRUE);break;
	case 6:		m_6dlg.ShowWindow(SW_SHOW);		m_6dlg.SetEncpTimer(TRUE);break;
	case 8:		m_8dlg.ShowWindow(SW_SHOW);		m_8dlg.SetEncpTimer(TRUE);break;
	case 10:	m_10dlg.ShowWindow(SW_SHOW);	m_10dlg.SetEncpTimer(TRUE);break;
	case 12:	m_12dlg.ShowWindow(SW_SHOW);	m_12dlg.SetEncpTimer(TRUE);break;
	case 14:	m_14dlg.ShowWindow(SW_SHOW);	m_14dlg.SetEncpTimer(TRUE);break;
	case 16:	m_16dlg.ShowWindow(SW_SHOW);	m_16dlg.SetEncpTimer(TRUE);break;
	}
}
void CMainDlg::EnableRunKey()
{
	CIMC_GenericDlg* mdlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	BOOL ena = mdlg->GetThreadSt();
	BOOL pause = mdlg->IsPause();
//	GetDlgItem(IDC_BN_RUN)->EnableWindow(m_isEditEN);
	GetDlgItem(IDC_BN_PAUSE)->EnableWindow(ena && !pause);
	GetDlgItem(IDC_BN_EMSTOP)->EnableWindow(ena);
	GetDlgItem(IDC_BN_MANUAL)->EnableWindow(!ena);
	GetDlgItem(IDC_BN_GOHOME)->EnableWindow(!ena);
	GetDlgItem(IDC_BN_SYS_CFG)->EnableWindow(!ena);
	if(ena){
		if(pause)
			SetDlgItemText(IDC_BN_RUN, _T("启动"));
		else
			SetDlgItemText(IDC_BN_RUN, _T("停止"));
		m_isEditEN = TRUE;
		OnBnClickedBnEditEn();
	}else
		SetDlgItemText(IDC_BN_RUN, _T("启动"));
}
void CMainDlg::InitListCtrl()
{
	DWORD dwStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;   //清除显示方式位 
	dwStyle|= LVS_REPORT; //设置报表风格
	//在原有样式的基本上，添加LVS_REPORT扩展样式
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, dwStyle);
	//获取已有的扩展样式
	DWORD dwStyles = m_list.GetExStyle();
	//取消复选框样式
	dwStyles &= ~LVS_EX_CHECKBOXES;
	dwStyles   |=LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES  ;
	//添加整行选择和表格线扩展样式
	m_list.SetExtendedStyle(dwStyles);
//	m_list.SetRowHeigt(18);//设置行高度
//	m_list.SetFontHW(15,0);               //设置字体高度，和宽度,0表示缺省宽度
	if(m_listFont == NULL){//
		m_listFont = new CFont;
		m_listFont->CreateFont(20,0,0,0,0,FALSE,FALSE,0,0,0,0,0,0,_T("宋体"));//创建字体
	}
	m_listlen = 800;
	m_list.SetFont(m_listFont, TRUE);//设置字体改变行高
	m_list.InsertColumn(0, _T("行号"),LVCFMT_RIGHT,60);
	m_list.InsertColumn(1, _T("指令"),LVCFMT_CENTER,135);
	m_list.InsertColumn(2, _T("描述"),LVCFMT_LEFT,m_listlen);
}
//进入编辑模式
void CMainDlg::OnBnClickedBnEditEn()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* mdlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(!m_isEditEN){
		if(mdlg->GetThreadSt()) return;
		if(!mdlg->IsPasswordOK(MY_PW_EDIT)) return;
		SetDlgItemText(IDC_BN_EDIT_EN, _T("退出编辑模式"));
	}else
		SetDlgItemText(IDC_BN_EDIT_EN, _T("进入编辑模式"));
	m_isEditEN = !m_isEditEN;
	GetDlgItem(IDC_BN_EDIT_ADD_LINE)->EnableWindow(m_isEditEN);
	int cnt = m_list.GetItemCount();
	if(cnt > 0){
		GetDlgItem(IDC_BN_EDIT_CHANGE)->EnableWindow(m_isEditEN);
		if(m_isEditEN)
		{
			int row = m_list.GetSelectionMark();
			if(row >= 0){
			//	if(m_machinSel == 0){
					m_list.EnsureVisible(row, TRUE);
			/*	}else{
					m_list.SetItemState(row, 0, -1);//取消选择
					m_list.SetSelectionMark(cnt-1);
					m_list.EnsureVisible(cnt-1, TRUE);
					m_list.SetItemState(cnt-1,LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED|LVIS_DROPHILITED);//选择
				}*/
			}
		}
	}
	GetDlgItem(IDC_BN_EDIT_DELETE_ALL)->EnableWindow(m_isEditEN);
	GetDlgItem(IDC_BN_EDIT_INSERT)->EnableWindow(m_isEditEN);
	GetDlgItem(IDC_BN_EDIT_DELETE)->EnableWindow(FALSE);

	GetDlgItem(IDC_BN_LOAD_FILE)->EnableWindow(m_isEditEN);
	GetDlgItem(IDC_BN_SAVE_FILE)->EnableWindow(m_isEditEN);
	GetDlgItem(IDC_BN_NEW_FILE)->EnableWindow(m_isEditEN);
//	GetDlgItem(IDC_BN_LOAD_CAD)->EnableWindow(m_isEditEN);
}

//双击
void CMainDlg::OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* mdlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(mdlg->GetThreadSt()) {
		*pResult = 1;
		return;
	}
	int nItem=phdr->iItem;
	if(m_isEditEN){
		if(nItem!=-1){
		//	ProgramDlg(nItem);//启动编程对话框
			PostMessage(WM_MY_PROGRAM_SHOW, (WPARAM)nItem, (LPARAM)CMD_NULL);//通知主框架更新
		}
	}
	*pResult = 0;
}
//单击
void CMainDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* mdlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(mdlg->GetThreadSt()) {
		*pResult = 1;
		return;
	}
	int nItem=phdr->iItem;
	if(m_isEditEN){
		if(nItem!=-1){
			GetDlgItem(IDC_BN_EDIT_DELETE)->EnableWindow(true);
			GetDlgItem(IDC_BN_EDIT_INSERT)->EnableWindow(true);
			GetDlgItem(IDC_BN_EDIT_CHANGE)->EnableWindow(true);
		}else{
			GetDlgItem(IDC_BN_EDIT_DELETE)->EnableWindow(false);
			GetDlgItem(IDC_BN_EDIT_INSERT)->EnableWindow(false);
			GetDlgItem(IDC_BN_EDIT_CHANGE)->EnableWindow(false);
		}
	}
	*pResult = 0;
}
void CMainDlg::SetShow(int line)
{
	int row;
	row = m_list.GetSelectionMark();//获得当前选择的行
	m_list.SetItemState(row, 0, -1);//取消选择
	if(m_machinSel == 0)//单步时
		row = m_startLine + line;
	else
		row = line;
	m_list.SetSelectionMark(row);
	m_list.SetItemState(row,LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED|LVIS_DROPHILITED);//选择
	m_list.EnsureVisible(row, FALSE);
}
void CMainDlg::ShowStepStart(int line)
{	
	int num = m_list.GetItemCount();
	if(line + m_startLine >= num)
		SetDlgItemInt(IDC_EDIT1, 1);
	else
		SetDlgItemInt(IDC_EDIT1, line + m_startLine + 1);
}

void CMainDlg::ShowMachinTimeTotal(DWORD time)
{//加工计时:
	CString str;
	str.Format(_T("%02d:%02d:%02d"), time/3600, time/60, time%60);
	SetDlgItemText(IDC_STATIC_WORK_TIME, str);
}

void CMainDlg::ShowMachinTime(DWORD time)
{//单件计时
	CString str;
	str.Format(_T("%02d:%02d:%02d"), time/3600, time/60, time%60);
	SetDlgItemText(IDC_STATIC_WORK_TIME_ONE, str);
}
void CMainDlg::ShowMachinNum(DWORD cnt)
{//加工计数
	CString str;
	str.Format(_T("%06d "), cnt);
	SetDlgItemText(IDC_STATIC_WORKED_CNT, str);
}
void CMainDlg::ShowMachinStatus()
{//加工计数
	CIMC_GenericDlg * dlg = (CIMC_GenericDlg*)m_mdlg;
	if(dlg->GetThreadSt())
		SetDlgItemText(IDC_STATIC_RUN_STATUS, _T("运行状态:  运行中..."));
	else
		SetDlgItemText(IDC_STATIC_RUN_STATUS, _T("运行状态:  未运行"));
}
void CMainDlg::MahinEndTip(int tip)
{
	CString str;
	switch(tip)
	{
	case 0: str = _T(""); break;
	case 1: str = _T("正在加工最后一件..."); break;
	case 2: str = _T("22急停按钮按下， 放开急停按钮恢复"); break;
	case 3: str = _T("33急停按钮按下， 放开急停按钮恢复"); break;
	}
	SetDlgItemText(IDC_STATIC_MACHIN_END, str);
}
void CMainDlg::MahinEndTip(CString str)
{
	SetDlgItemText(IDC_STATIC_MACHIN_END, str);
}
//修改
void CMainDlg::OnBnClickedBnEditChange()
{
	// TODO: 在此添加控件通知处理程序代码
	int row = m_list.GetSelectionMark();//获得当前选择的行
	if(row != -1){
		PostMessage(WM_MY_PROGRAM_SHOW, (WPARAM)row, (LPARAM)CMD_NULL);//通知主框架更新
	}
}

//增加新行
void CMainDlg::OnBnClickedBnEditAddLine()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	int row;
	row = m_list.GetSelectionMark();//获得当前选择的行
	m_list.SetItemState(row, 0, -1);//取消选择
	row=m_list.GetItemCount();
	str.Format(_T("%d"),row+1);
	m_list.InsertItem(row, str);
	m_list.SetSelectionMark(row);
	m_list.EnsureVisible(row, TRUE);
	m_list.SetItemState(row,LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED|LVIS_DROPHILITED);//选择
	PROGRAM_DATA *pd;
	pd = new PROGRAM_DATA;
	memset(pd, 0, sizeof(PROGRAM_DATA));
	pd->posBit = -1;
	pd->velRatio = 9;
	m_list.SetItemData(row, (DWORD)pd);
	GetDlgItem(IDC_BN_EDIT_DELETE)->EnableWindow(true);
	GetDlgItem(IDC_BN_EDIT_CHANGE)->EnableWindow(true);
	GetDlgItem(IDC_BN_EDIT_DELETE_ALL)->EnableWindow(true);
	GetDlgItem(IDC_BN_EDIT_INSERT)->EnableWindow(true);
}

//插入新行
void CMainDlg::OnBnClickedBnEditInsert()
{
	// TODO: 在此添加控件通知处理程序代码
	int i,rows = 0, row ;
	CString str;
	row = m_list.GetSelectionMark();//获得当前选择的行
	m_list.SetItemState(row, 0, -1);//取消选择
	if(row!=-1){
		UpdateRec(row, TRUE);
		str.Format(_T("%d"),row+1);
		m_list.InsertItem(row, str);
		m_list.SetSelectionMark(row);
		m_list.EnsureVisible(row, TRUE);
		m_list.SetItemState(row,LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED|LVIS_DROPHILITED);
		PROGRAM_DATA *pd;
		pd = new PROGRAM_DATA;
		memset(pd, 0, sizeof(PROGRAM_DATA));
		pd->velRatio = 9;
		m_list.SetItemData(row, (DWORD)pd);
		rows = m_list.GetItemCount();
		for(i=row+1;i<rows;i++)
		{
			str.Format(_T("%d"),i+1);
			m_list.SetItemText(i,0,str);
		}
	}else{
		rows = m_list.GetItemCount();
		if(rows == 0){
			str.Format(_T("%d"),1);
			m_list.InsertItem(0, str);
			m_list.SetSelectionMark(0);
			m_list.SetItemState(0,LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED|LVIS_DROPHILITED);
			PROGRAM_DATA *pd;
			pd = new PROGRAM_DATA;
			memset(pd, 0, sizeof(PROGRAM_DATA));
			pd->velRatio = 9;
			m_list.SetItemData(0, (DWORD)pd);
		}
	}
	m_list.SetFocus();
	GetDlgItem(IDC_BN_EDIT_DELETE)->EnableWindow(true);
	GetDlgItem(IDC_BN_EDIT_DELETE_ALL)->EnableWindow(true);
	GetDlgItem(IDC_BN_EDIT_CHANGE)->EnableWindow(true);
}
void CMainDlg::DeleteAllProgramData()
{
	PROGRAM_DATA *pd;
	int rows=m_list.GetItemCount();
	for(int i=0; i<rows; i++){
		pd = (PROGRAM_DATA*)m_list.GetItemData(i);
		if(pd != NULL) delete pd;
	}
}
//删除全部
void CMainDlg::OnBnClickedBnEditDeleteAll()
{
	// TODO: 在此添加控件通知处理程序代码
	if(MessageBox(_T("是否删除列表中的所有指令？"), _T("提示"), MB_YESNO) == IDNO)
		return ;
	DeleteAllProgramData();
	m_list.DeleteAllItems();
	DeleteAllRec();
	GetDlgItem(IDC_BN_EDIT_DELETE)->EnableWindow(false);
	GetDlgItem(IDC_BN_EDIT_DELETE_ALL)->EnableWindow(false);
	GetDlgItem(IDC_BN_EDIT_CHANGE)->EnableWindow(false);
	CIMC_GenericDlg* mh = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	mh->m_bChange = TRUE;
}

//删除
void CMainDlg::OnBnClickedBnEditDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	int i,rows = 0, index=m_list.GetSelectionMark();
	if(index!=-1){
		PROGRAM_DATA *pd;
		pd = (PROGRAM_DATA*)m_list.GetItemData(index);
		if(!UpdateRec(index, FALSE)) return;
		if(pd != NULL) delete pd;
		m_list.DeleteItem(index);
		if(index > 1)
			m_list.EnsureVisible(index - 1, TRUE);
		rows=m_list.GetItemCount();
		if(index == rows)
			m_list.SetItemState(index - 1,LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED|LVIS_DROPHILITED);
		else
			m_list.SetItemState(index, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED|LVIS_DROPHILITED);
		CString str;
		for(i=index;i<rows;i++)
		{
			str.Format(_T("%d"),i+1);
			m_list.SetItemText(i,0,str);
		}
	}
	if(rows < 1){
		GetDlgItem(IDC_BN_EDIT_DELETE)->EnableWindow(false);
		GetDlgItem(IDC_BN_EDIT_DELETE_ALL)->EnableWindow(false);
		GetDlgItem(IDC_BN_EDIT_CHANGE)->EnableWindow(false);
	}
	m_list.SetFocus();
	CIMC_GenericDlg* mh = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	mh->m_bChange = TRUE;
}

//导入文件
void CMainDlg::OnBnClickedBnLoadFile()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* mh = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(mh->m_bChange){
		if(MessageBox(_T("是否需要保存当前编辑的程序？"), _T("提示"), MB_YESNO) == IDYES){
			OnBnClickedBnSaveFile();
		}
	}
	m_list.DeleteAllItems();
	DeleteAllRec();
	CFileDialog   pFileDlg(TRUE,
							FILE_EXP,
							NULL,
							OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
							_T("*.sgc(*.SGC)|*.sgc||")); 
	pFileDlg.m_ofn.lpstrInitialDir = SAV_FILE_DIR;
	if(pFileDlg.DoModal() != IDOK)
		return;
	LoadSGCfile(pFileDlg.GetPathName());
}
BOOL CMainDlg::LoadSGCfile(CString path)
{
	FILE *pf;
	pf = _wfopen(path, _T("rb"));
	if(pf == NULL){
		path = GetMyMFCDir();
		path += USE_FILE_NAME;
		::DeleteFile(path);
		MessageBox(_T("无法打开编程文件，导入失败！"));
		return FALSE;
	}
	PROGRAM_DATA *pdata;
	JUMP_REC * prec, *pre;
	char *pt;
	File_HEAD head;
	int i, len, size;
	CString str;
	len =fread(&head, sizeof(File_HEAD), 1, pf);
	if(!IsSysFile(head) || len != 1){
		MessageBox(_T("文件格式错误！"));
		return FALSE;
	}
	if(head.size > sizeof(PROGRAM_DATA)) size = sizeof(PROGRAM_DATA);
	else size = head.size;
	pt =new char[head.size];
	for(i=0; i<head.cnt; i++)
	{
		pdata = new PROGRAM_DATA;
		memset(pdata, 0, sizeof(PROGRAM_DATA));
		len = fread(pt, head.size, 1, pf);//读到缓存pt中
		if(len != 1) {
			delete [] pt;
			delete pdata;
			return FALSE;
		}
		str.Format(_T("%d"),i+1);
		m_list.InsertItem(i, str);
		m_list.SetItemData(i, (DWORD)pdata);
		memcpy(pdata, pt, size);//只复制size大小的数据
		ShowListData(i, pdata);
	}
	//**********************************************
	pre = NULL;
	while(1){
		prec = new JUMP_REC;
		len = fread(prec, sizeof(JUMP_REC), 1, pf);//读到缓存pt中
		if(len > 0){
			if(m_jpRec == NULL)
				m_jpRec = prec;
			if(pre != NULL) pre->next = prec;
			pre = prec;
		}else {
			delete prec;
			break;
		}
	}
	pre = m_jpRec;
	while(pre != NULL){
		pre->pdata = (PROGRAM_DATA*)m_list.GetItemData(pre->line);
		pre->pjdata = (PROGRAM_DATA*)m_list.GetItemData(pre->jumpLine-1);
		pre = pre->next;
	}
	//**********************************************
	delete [] pt;
	fclose(pf);
//	CString iniPath = theApp.GetMyMFCDir()+INI_FILE_NAME;
//	WritePrivateProfileString(_T("cfg"),_T("srcpath"),path,iniPath);
	SaveCurFile(path);

	i=path.ReverseFind('\\');
	CString name;
	name = path.Mid(i+1);
	i = name.ReverseFind('.');
	name = name.Left(i);
	SetDlgItemText(IDC_BN_LOAD_CAD, name);

	return TRUE;
}

//保存文件
void CMainDlg::OnBnClickedBnSaveFile()
{
	// TODO: 在此添加控件通知处理程序代码
#if defined(WINCE)
	if(!g_isSipShow) {
		g_isSipShow = TRUE;
		SipShowIM(SIPF_ON);
	}
#endif
	CFileDialog   pFileDlg(FALSE,
							FILE_EXP,
							NULL,
							OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
							_T("*.sgc(*.SGC)|*.sgc||")); 
	pFileDlg.m_ofn.lpstrInitialDir = SAV_FILE_DIR;

	if(pFileDlg.DoModal() != IDOK){
#if defined(WINCE)
		if(g_isSipShow) {
			g_isSipShow = FALSE;
			SipShowIM(SIPF_OFF);
		}
#endif
		return;
	}
#if defined(WINCE)
	if(g_isSipShow) {
		g_isSipShow = FALSE;
		SipShowIM(SIPF_OFF);
	}
#endif
	CString path;
	CIMC_GenericDlg* mh = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	mh->m_bChange = FALSE;
	FILE *pf;
	path = pFileDlg.GetPathName();
	pf = _wfopen(path, _T("wb"));
	if(pf == NULL){
		MessageBox(_T("无法打开文件，保存失败！"));
		return;
	}
	PROGRAM_DATA *pdata;
	JUMP_REC * prec;
	int cnt = m_list.GetItemCount();
	File_HEAD head;
	INIT_FILE_HEAD(head, FILE_VERSION);
	head.cnt = cnt;
	head.size = sizeof(PROGRAM_DATA);
	fwrite(&head, sizeof(File_HEAD), 1, pf);
	for(int i=0; i<cnt; i++)
	{
		pdata = (PROGRAM_DATA*)m_list.GetItemData(i);
		fwrite(pdata, sizeof(PROGRAM_DATA), 1, pf);
	}
	prec = m_jpRec;
	while(prec != NULL){
		fwrite(prec, sizeof(JUMP_REC), 1, pf);
		prec = prec->next;
	}
	fclose(pf);
//	CString iniPath = theApp.GetMyMFCDir()+INI_FILE_NAME;
//	WritePrivateProfileString(_T("cfg"),_T("srcpath"),path,iniPath);
	SaveCurFile(path);
	SetDlgItemText(IDC_BN_LOAD_CAD, pFileDlg.GetFileTitle());
}
//新建
void CMainDlg::OnBnClickedBnNewFile()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* mh = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(mh->m_bChange){
		if(MessageBox(_T("是否需要保存当前编辑的程序？"), _T("提示"), MB_YESNO) == IDYES){
			OnBnClickedBnSaveFile();
		}
		mh->m_bChange = FALSE;
	}
	m_list.DeleteAllItems();
	DeleteAllRec();
	GetDlgItem(IDC_BN_EDIT_DELETE)->EnableWindow(false);
	GetDlgItem(IDC_BN_EDIT_DELETE_ALL)->EnableWindow(false);
	GetDlgItem(IDC_BN_EDIT_CHANGE)->EnableWindow(false);
	SetDlgItemText(IDC_BN_LOAD_CAD, _T(""));
}

//系统配置
void CMainDlg::OnBnClickedBnSysCfg()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(!dlg->IsPasswordOK(MY_PW_SYS)) return;
	dlg->ShowDlg(JM_SYS);
}
//启动
void CMainDlg::OnBnClickedBnRun()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* mdlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(!mdlg->m_imc.IsOpen()){
		MessageBox(_T("设备没有连接！"),_T("警告"));
		return;
	}
	if(mdlg->m_imc.m_Naxis < g_factcfg.Naxis){
		MessageBox(_T("控制卡有效轴数与程序设置不符！"),_T("警告"));
		return;
	}
	if(m_list.GetItemCount() < 1){
		MessageBox(_T("没有指令可执行！"));
		return;
	}
	if(!mdlg->IsPasswordOK(MY_PW_RUN)) return;
	UpdateData(TRUE);
	EnableRunKey();
	mdlg->StartMatchin(m_machinSel);
}
//暂停
void CMainDlg::OnBnClickedBnPause()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* mdlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	mdlg->PauseMatchin();
}

//急停
void CMainDlg::OnBnClickedBnEmstop()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	dlg->EmstopMatchin();
}
//复位
void CMainDlg::OnBnClickedBnReset()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(!dlg->m_imc.IsOpen()){
		MessageBox(_T("设备没有连接！"),_T("警告"));
		return;
	}
	CString str;
	str = GetMyMFCDir();
	str += SAV_FILE_RESET;
	str += FILE_EXP;
	if(!IsFileDirExist(str)){
		MessageBox(_T("系统中还没有复位程序(reset)。\r\n\r\n请先编辑一个复位动作程序,并保存为“reset”"), _T("提示"));
		return;
	}
	dlg->ResetMatchin();
}

void CMainDlg::EnaResetBn(BOOL ena)
{
//	GetDlgItem(IDC_BN_PAUSE)->EnableWindow(ena);
//	GetDlgItem(IDC_BN_EMSTOP)->EnableWindow(ena);
	GetDlgItem(IDC_BN_MANUAL)->EnableWindow(ena);
	GetDlgItem(IDC_BN_GOHOME)->EnableWindow(ena);
	GetDlgItem(IDC_BN_SYS_CFG)->EnableWindow(ena);
	GetDlgItem(IDC_BN_RUN)->EnableWindow(ena);
	if(ena){
		SetDlgItemText(IDC_BN_RESET, _T("复位"));
	}else
		SetDlgItemText(IDC_BN_RESET, _T("停止"));
}
//手动操作
void CMainDlg::OnBnClickedBnManual()
{
	// TODO: 在此添加控件通知处理程序代码
	CManual dlg;
	CIMC_GenericDlg* mdlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(!mdlg->m_imc.IsOpen()){
		MessageBox(_T("设备没有连接！"),_T("警告"));
		return;
	}
	if(mdlg->m_imc.m_Naxis < g_factcfg.Naxis){
		MessageBox(_T("控制卡有效轴数与程序设置不符！"),_T("警告"));
		return;
	}
	dlg.SetMainDlgPtr(m_mdlg);
	INT_PTR nResponse = dlg.DoModal();
}
//回零
void CMainDlg::OnBnClickedBnGohome()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(!dlg->m_imc.IsOpen()){
		MessageBox(_T("设备没有连接！"),_T("警告"));
		return;
	}
	if(dlg->m_imc.m_Naxis < g_factcfg.Naxis){
		MessageBox(_T("控制卡有效轴数与程序设置不符！"),_T("警告"));
		return;
	}
	dlg->ShowDlg(JM_HOME);
}
//******************************************************************************************
void CMainDlg::DeleteAllRec()
{
	JUMP_REC *prec;
	while(m_jpRec != NULL)
	{
		prec = m_jpRec->next;
		delete m_jpRec;
		m_jpRec = prec;
	}
}
JUMP_REC* CMainDlg::FindJumpRec(int row, PROGRAM_DATA*pdata, JUMP_REC **recPtr)
{
	*recPtr = NULL;
	JUMP_REC *prec = m_jpRec;
	while(prec != NULL)
	{
		if(prec->line == row &&  prec->pdata == pdata)
			break;
		*recPtr = prec;
		prec = prec->next;
	}
	return prec;
}
BOOL CMainDlg::UpdateRec(int row, BOOL isNew)
{//当删除一行或者插入一行前，需更新跳转语句
	JUMP_REC *prec = m_jpRec;
	while(prec != NULL)
	{
		if(prec->pjdata->type != CMD_NULL){//指定的行有数据才更新
			if(isNew){//插入一行
				if((prec->jumpLine-1) >= row){//只有在后面才需更新
					if(prec->jumpLine-1 != prec->line){//当删除了跳转的行后，再删除其他行时，会出现相等的情况
						prec->pdata->jumpLine ++;
						prec->jumpLine ++;
						ShowListData(prec->line, prec->pdata);
					}
				}
			}else{
				if((prec->jumpLine-1) == row){//如果删除的是跳转到的行，
					CString str;
					str.Format(_T("第 %d 行会跳转到此行，如要删除，请注意修改第 %d 行的跳转。\r\n\r\n是否要删除此行？"), prec->line+1, prec->line+1);
					if(MessageBox(str, _T("提示"), MB_YESNO) == IDNO)
						return FALSE;
				}if((prec->jumpLine-1) > row){
					if(prec->jumpLine-1 != prec->line){//当删除了跳转的行后，再删除其他行时，会出现相等的情况
						prec->pdata->jumpLine --;
						prec->jumpLine --;
						ShowListData(prec->line, prec->pdata);
					}
				}
			}
		}
		if(prec->line >= row){
			if(isNew)
				prec->line ++;
			else
				prec->line --;
		}
		prec = prec->next;
	}
	return TRUE;
}
//显示程序编辑对话框
LRESULT CMainDlg::OnProgramDlg(WPARAM wparam,LPARAM lparam)
{
	int row = (int)wparam;
	CMD_TYPE type = (CMD_TYPE)lparam;
	ProgramDlg(row, type);
	return 0;
}
void CMainDlg::ProgramDlg(int row, CMD_TYPE type)
{
	CProgramDlg dlg;
	PROGRAM_DATA* pdata, *pdata1;
	JUMP_REC* prec, *pRecP;
	CIMC_GenericDlg* mh = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	pdata = (PROGRAM_DATA*)m_list.GetItemData(row);
	prec = FindJumpRec(row, pdata, &pRecP);
	if(type == CMD_NULL)
		dlg.SetType(pdata->type, (PVOID)pdata);
	else
		dlg.SetType(type, (PVOID)pdata);
	dlg.SetMainDlgPtr(m_mdlg);
	if(dlg.DoModal() == IDOK){
		mh->m_bChange = TRUE;
		ShowListData(row, pdata);
		if((pdata->type == CMD_INPUT && pdata->InSel == 1) || pdata->type == CMD_JUMP || pdata->type == CMD_LOOP )
		{
			if(prec == NULL){
				prec = new JUMP_REC;
				memset(prec, 0, sizeof(JUMP_REC));
				if(pRecP == NULL)
					m_jpRec = prec;
			}
			prec->line = row;
			prec->pdata = pdata;
			prec->jumpLine = pdata->jumpLine;
			if(pdata->jumpLine < m_list.GetItemCount())
				prec->pjdata = (PROGRAM_DATA*)m_list.GetItemData(pdata->jumpLine);
			if(pRecP != NULL)
				pRecP->next = prec;
		}else{//没有跳转的，需删除有跳转的
			if(prec != NULL){
				if(pRecP != NULL)//当前记录不是第一个
					pRecP->next = prec->next;
				else //当前记录不是第一个
					m_jpRec = prec->next;
				delete prec;
			}	
		}
		if(g_isUseHWok){
			if(m_list.GetItemCount() == row + 1){//当在最后一行的时候才增加
				OnBnClickedBnEditAddLine();
				int line = m_list.GetSelectionMark();//获得当前选择的行
				pdata1 = (PROGRAM_DATA*)m_list.GetItemData(line);
				pdata1->posBit = pdata->posBit;
				pdata1->arcBit = pdata->arcBit;
				pdata1->arc[0] = pdata->arc[4];
				pdata1->arc[1] = pdata->arc[5];
				PostMessage(WM_MY_PROGRAM_SHOW, (WPARAM)line, (LPARAM)pdata->type);//通知主框架更新
			}
		}
	}
//	dlg.StopHW();
}
//显示列表框中的数据
void CMainDlg::ShowListData(int row, PROGRAM_DATA*pdata)
{
	CString str;
//	str.Format(_T("%d"),i+1);
	if(pdata == NULL) return;
	m_list.SetItemText(row,1,g_cmdStr[pdata->type]);
	ShowDescription(row, pdata);
}
//显示列表框中的描述
void CMainDlg::ShowDescription(int row, PROGRAM_DATA*pdata)
{
	CString str,tmp, tmp1;
	int i , j;
	switch(pdata->type)
	{
	case CMD_LINKAGE://多轴联动	
		if(pdata->InSel){//相对移动
			for(i=0; i<g_Naxis; i++){
				if(pdata->posBit & (1 << i)){
					tmp.Format(_T("%s 移动距离 %.02f%s; "), g_AxisName[i], 1.0*pdata->pos[i]/*/g_factcfg.distFac[i]*/, g_factcfg.Unit[i]);
					str += tmp;
				}
			}
		}else{
			for(i=0; i<g_Naxis; i++){
				if(pdata->posBit & (1 << i)){
					tmp.Format(_T("%s 目标位置 %.02f%s; "), g_AxisName[i], 1.0*pdata->pos[i]/*/g_factcfg.distFac[i]*/, g_factcfg.Unit[i]);
					str += tmp;
				}
			}
		}
		tmp.Format(_T("轨迹以 %s速度 运动，其速度比率为%d%%"), pdata->vel == 0 ? _T("工作") : _T("快移"), (pdata->velRatio+1) *10);
		str += tmp;
		break;
	case CMD_ARC:	//圆弧	
		int x[2];
		j=0;
		str = _T("走圆弧的轴为：");
		for(i=0; i<g_Naxis; i++){
			if(pdata->arcBit & (1 << i)){
				x[j++] = i;
				tmp.Format(_T("%s、"), g_AxisName[i]);
				str += tmp;
			}
		}
		if(j<2) break;
		tmp.Format(_T("圆弧上的点坐标为P1（%.02f,%.02f)，P2（%.02f,%.02f)，P3（%.02f,%.02f)；"), 
			1.0*pdata->arc[0]/*/g_factcfg.distFac[x[0]]*/, 1.0*pdata->arc[1]/*/g_factcfg.distFac[x[1]]*/, 
			1.0*pdata->arc[2]/*/g_factcfg.distFac[x[0]]*/, 1.0*pdata->arc[3]/*/g_factcfg.distFac[x[1]]*/, 
			1.0*pdata->arc[4]/*/g_factcfg.distFac[x[0]]*/, 1.0*pdata->arc[5]/*/g_factcfg.distFac[x[1]]*/);
		str += tmp;
		if(pdata->posBit){
			str += _T("同步轴：");		
			for(i=0; i<g_Naxis; i++){
				if(pdata->posBit & (1 << i)){
					tmp.Format(_T("%s 目标位置 %.02f%s;"), g_AxisName[i], 1.0*pdata->pos[i]/*/g_factcfg.distFac[i]*/, g_factcfg.Unit[i]);
					str += tmp;
				}
			}
		}
		tmp.Format(_T(" 速度比率为%d%%"),  (pdata->velRatio+1) *10);
		str += tmp;
		break;
	case CMD_OUTPUT://输出		
		str.Format(_T("在输出端口 %d 输出动作 %s"), 
#ifdef CHANGE_DATA_0
			pdata->OutputBit +1, pdata->OutputVal ? _T("断开") : _T("连通"));
#else
			((pdata->Output >> 8)&0xFF) +1, (pdata->Output&0xFF) ? _T("断开") : _T("连通"));
#endif
		if(pdata->InSel & 0xFF){
			tmp.Format(_T("，并在%.02f秒后输出动作 %s"), 1.0*pdata->delay/1000, ((pdata->InSel>>8) & 0xFF) ? _T("断开") : _T("连通"));
			str += tmp;
		}
		break;
	case CMD_INPUT:	//输入	
		tmp1.Format(_T("跳转到第 %d 行指令"), pdata->jumpLine);
		str.Format(_T("在 %.02f 秒内检测输入端口 %d 的输入动作 %s ，如果超时，%s%s%s"), 1.0*pdata->delay/1000,
#ifdef CHANGE_DATA_0
			pdata->InputBit + 1, 
			pdata->InputVal == 0  ? _T("断开") : _T("连通"),
#else
			((pdata->Input >> 8)&0xFF) + 1, 
			(pdata->Input&0xFF) == 0  ? _T("断开") : _T("连通"),
#endif
			((pdata->InSel&0xFF) == 0 ? _T("暂停指令") : (pdata->InSel&0xFF) == 1 ? tmp1 : _T("无动作，直接执行下一条指令")),
			((pdata->InSel>> 8)&0xFF) ? _T("，并开启红灯报警") : _T(""),
			pdata->homeMode ? _T("，弹出提示") : _T(""));
		break;
	case CMD_DELAY:	//延时		
		str.Format(_T("等待 %.2f 秒后执行下一个指令"), 1.0*pdata->delay/1000);
		break;
	case CMD_JUMP:	//跳转	
		str.Format(_T("跳转到第 %d 行执行"), pdata->jumpLine);
		break;
	case CMD_LOOP:	//循环开始	
		str.Format(_T("跳转到第 %d 行开始循环，并循环 %d 次"), pdata->jumpLine, pdata->loopNum);
		break;
	case CMD_END:	//程序结束，	
		str = _T("程序结束，将继续从程序开始位置执行指令");
		break;
	case CMD_WEND:	//循环结束，	
		str = _T("循环结束标志，判断循环次数，并决定从循环跳转行开始还是从循环开始指令的下一条指令开始执行指令");
		break;
	case CMD_GOHOME://回零	
		if(pdata->homeMode == 0){//同时回零
			str = _T("移动到零点：");
			for(i=0; i<g_Naxis; i++){
				if(pdata->homeBit & (1 << i)){
					tmp.Format(_T("%s 顺序：%d、"), g_AxisName[i], pdata->homeSort[i]+1);
					str += tmp;
				}
			}
			tmp.Format(_T("以 %s速度 移动到设置的零点;"), pdata->vel == 0 ? _T("工作") : _T("快移"));
			str += tmp;
			tmp.Format(_T(" 速度比率为%d%%"),  (pdata->velRatio+1) *10);
			str += tmp;
		}else if(pdata->homeMode == 1){
			str = _T("搜索零点开关：");
			for(i=0; i<g_Naxis; i++){
				if(pdata->homeBit & (1 << i)){
					tmp.Format(_T("%s 顺序：%d、"), g_AxisName[i], pdata->homeSort[i]+1);
					str += tmp;
				}
			}
			tmp.Format(_T("以 %s速度 搜索零点开关;"), pdata->vel == 0 ? _T("工作") : _T("快移"));
			str += tmp;
			tmp.Format(_T(" 速度比率为%d%%"),  (pdata->velRatio+1) *10);
			str += tmp;
		}else if(pdata->homeMode == 2){
			str.Format(_T("将指定的轴："));
			for(i=0; i<g_Naxis; i++){
				if(pdata->homeBit & (1 << i)){
					tmp.Format(_T("%d:%s、"), pdata->homeSort[i] +1, g_AxisName[i]);
					str += tmp;
				}
			}
			str += _T(" 当前位置设置为零点；");
		}
		break;
	case CMD_GHWHIRL://回零	
		str.Format(_T("旋转轴 %s 回零"), g_AxisName[pdata->homeMode]);

		break;
	case CMD_VEL:	//连续匀速运动，	
		if(pdata->vel == 2){
			str.Format(_T("停止 %s 的转动"), g_AxisName[pdata->axis]);
		}else{
			str.Format(_T("设定 %s 以 %s速度 匀速%s，直到改变此轴运动为止; 速度比率为%d%%"), 
				g_AxisName[pdata->axis], pdata->vel == 0 ? _T("工作") : _T("快移"),
				pdata->dir? _T("反转") : _T("正转"),  (pdata->velRatio+1) *10);
		}
		break;
	case CMD_POS:	//点到点运动，	
		if(pdata->InSel){
			str.Format(_T("设定 %s 以 %s速度 移动距离 %.02f%s; 速度比率为%d%%"), 
				g_AxisName[pdata->axis], pdata->vel == 0 ? _T("工作") : _T("快移"), 1.0*pdata->pos[0]/*/g_factcfg.distFac[pdata->axis]*/, g_factcfg.Unit[pdata->axis]/*, pdata->isWT ? _T("并等待其移动结束") : _T("")*/,  (pdata->velRatio+1) *10);
		}else{
			str.Format(_T("设定 %s 以 %s速度 从当前位置移动到目标位置 %.02f%s; 速度比率为%d%%"), 
				g_AxisName[pdata->axis], pdata->vel == 0 ? _T("工作") : _T("快移"), 1.0*pdata->pos[0]/*/g_factcfg.distFac[pdata->axis]*/, g_factcfg.Unit[pdata->axis]/*, pdata->isWT ? _T("并等待其移动结束") : _T("")*/,  (pdata->velRatio+1) *10);
		}
		break;
	case CMD_WAIT:	//等待，	
		if(pdata->WTbit == 0)
			str = _T("等待插补运动停止");
		else if(pdata->WTbit == 1)
			str = _T("等待点位运动停止");
		break;
	}
	int len = m_list.GetStringWidth(str) + 16;
	if(m_listlen < len){
		m_listlen = len;
		m_list.SetColumnWidth(2, m_listlen);
	}
	m_list.SetItemText(row,2,str);
}


PROGRAM_DATA *CMainDlg::GetProData(int index)
{
	if(index >= m_list.GetItemCount())
		return NULL;
	return (PROGRAM_DATA*)m_list.GetItemData(index);
}

PROGRAM_DATA *CMainDlg::GetRunData(int *pnum)
{
	PROGRAM_DATA * pdata, *tmp;
	int num = m_list.GetItemCount();
	if(m_machinSel == 0){//单步时
		m_startLine = GetDlgItemInt(IDC_EDIT1) - 1;
		if(m_startLine >= num){
			*pnum = 0;
			return NULL;
		}
	}else
		m_startLine = 0;

	if(num < 1) {
		*pnum = 0;
		return NULL;
	}
	if(m_startLine < 0) 
		m_startLine = 0;
	pdata = new PROGRAM_DATA[num];
	memset(pdata, 0, sizeof(PROGRAM_DATA) * (num));
	for(int i=m_startLine; i<num; i++)
	{
		tmp = (PROGRAM_DATA*)m_list.GetItemData(i);
		memcpy(pdata+ i-m_startLine, tmp, sizeof(PROGRAM_DATA));
	}
	*pnum = num - m_startLine;
	return pdata;
}
//读取复位程序
PROGRAM_DATA *CMainDlg::GetResetData(int *pnum)
{
	CString dir;
	dir = GetMyMFCDir();
	dir += SAV_FILE_RESET;
	dir += FILE_EXP;

	FILE *pf;
	pf = _wfopen(dir, _T("rb"));
	if(pf == NULL){
		*pnum = 0;
		return NULL;
	}
	PROGRAM_DATA * pdata;
	File_HEAD head;
	int i, len, size;
	CString str;
	len =fread(&head, sizeof(File_HEAD), 1, pf);
	if(!IsSysFile(head) || len != 1){
		MessageBox(_T("文件格式错误！"));
		*pnum = 0;
		return NULL;
	}
	if(head.cnt < 1){
		*pnum = 0;
		return NULL;
	}
	if(head.size > sizeof(PROGRAM_DATA)) size = sizeof(PROGRAM_DATA);
	else size = head.size;
	char *tmp = new char[head.size];
	pdata = new PROGRAM_DATA[head.cnt];
	for(i=0; i<head.cnt; i++)
	{
		len = fread(tmp, head.size, 1, pf);//读到缓存中
		if(len != 1) {
			break;
		}
		memcpy(pdata + i, tmp, size);//只复制size大小的数据
	}
	delete tmp;
	*pnum = i;
	return pdata;
}

//读取急停程序
PROGRAM_DATA *CMainDlg::GetEmstopData(int *pnum)
{
	CString dir;
	dir = GetMyMFCDir();
	dir += SAV_FILE_EMSTOP;
	dir += FILE_EXP;

	FILE *pf;
	pf = _wfopen(dir, _T("rb"));
	if(pf == NULL){
		*pnum = 0;
		return NULL;
	}
	PROGRAM_DATA * pdata;
	File_HEAD head;
	int i, len, size;
	CString str;
	len =fread(&head, sizeof(File_HEAD), 1, pf);
	if(!IsSysFile(head) || len != 1){
		MessageBox(_T("文件格式错误！"));
		*pnum = 0;
		return NULL;
	}
	if(head.cnt < 1){
		*pnum = 0;
		return NULL;
	}
	if(head.size > sizeof(PROGRAM_DATA)) size = sizeof(PROGRAM_DATA);
	else size = head.size;
	char *tmp = new char[head.size];
	pdata = new PROGRAM_DATA[head.cnt];
	for(i=0; i<head.cnt; i++)
	{
		len = fread(tmp, head.size, 1, pf);//读到缓存中
		if(len != 1) {
			break;
		}
		memcpy(pdata + i, tmp, size);//只复制size大小的数据
	}
	delete tmp;
	*pnum = i;
	return pdata;
}


void CMainDlg::SetBmpVal(UINT id, int val)
{
	CStatic *ic=(CStatic*)GetDlgItem(IDC_STATIC_BMP_GREED + id);
	
	if(val==0){//关
		ic->SetBitmap(m_bmp[id*2]);
	}else{//开
		ic->SetBitmap(m_bmp[id*2 + 1]);
	}
}
void CMainDlg::OnBnClickedBnFileMg()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	dlg->ShowDlg(JM_FILE);
}

void CMainDlg::OnBnClickedBtnRunToPos1()
{
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;

	WCHAR curPosSetStr[64];
	memset(curPosSetStr, 0, sizeof(WCHAR) * 64);
	GetDlgItemText(IDC_EDIT_POS_X,curPosSetStr, 60);
      double curPosSet =_tstof(curPosSetStr);
 	//   CString strTmp;
	//  strTmp.Format(_T("X curPosSet=%.3f"),curPosSet);

	 // AfxMessageBox(strTmp);
	//g_cfg.accel[0]=50;
	//dlg->m_imc.SetAccel();

	dlg->gotoPos_singleAxis(AXIS_IDX_0_X,G00,10,curPosSet); 
}

void CMainDlg::OnBnClickedBtnRunToPos2()
{
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;

	WCHAR curPosSetStr[64];
	memset(curPosSetStr, 0, sizeof(WCHAR) * 64);
	GetDlgItemText(IDC_EDIT_POS_Y,curPosSetStr, 60);
      double curPosSet =_tstof(curPosSetStr);


	  CString strTmp;
	  strTmp.Format(_T("Y curPosSet=%.3f"),curPosSet);

	 // MessageBox(strTmp,_T("警告"));



	  
	dlg->gotoPos_singleAxis(AXIS_IDX_1_Y,G00,10,curPosSet); 
}

void CMainDlg::OnBnClickedBtnRunToPos3()
{
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;

	WCHAR curPosSetStr[64];
	memset(curPosSetStr, 0, sizeof(WCHAR) * 64);
	GetDlgItemText(IDC_EDIT_POS_Z,curPosSetStr, 60);
      double curPosSet =_tstof(curPosSetStr);
	    CString strTmp;
	  strTmp.Format(_T("Z curPosSet=%.3f"),curPosSet);

	 // MessageBox(strTmp,_T("警告"));
	dlg->gotoPos_singleAxis(AXIS_IDX_2_Z,G00,10,curPosSet); 
}
void CMainDlg::OnBnClickedBtnRunToPosXyz()
{
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;
	
	WCHAR curPosSetStr[64];

	memset(curPosSetStr, 0, sizeof(WCHAR) * 64);	
	GetDlgItemText(IDC_EDIT_POS_X,curPosSetStr, 60);
	double x =_tstof(curPosSetStr);

	memset(curPosSetStr, 0, sizeof(WCHAR) * 64);	
	GetDlgItemText(IDC_EDIT_POS_Y,curPosSetStr, 60);
	double y =_tstof(curPosSetStr);


	memset(curPosSetStr, 0, sizeof(WCHAR) * 64);	
	GetDlgItemText(IDC_EDIT_POS_Z,curPosSetStr, 60);
	double z =_tstof(curPosSetStr);

	dlg->gotoPos_MultiAxis(G00,10,x,y,z); 

}

void CMainDlg::OnBnClickedBnEstop()
{
	OnBnClickedBnEmstop();//急停
}

void CMainDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CMpcDlg dlg;
	CIMC_GenericDlg* mdlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();

	if(!mdlg->m_imc.IsOpen()){
		MessageBox(_T("设备没有连接！"),_T("警告"));
		return;
	}
	if(mdlg->m_imc.m_Naxis < g_factcfg.Naxis){
		MessageBox(_T("控制卡有效轴数与程序设置不符！"),_T("警告"));
		return;
	}

	dlg.SetMainDlgPtr(m_mdlg);
	INT_PTR nResponse = dlg.DoModal();
}

void CMainDlg::OnPaint()
{
 CPaintDC dc(this); // device context for painting
        // TODO: 在此处添加消息处理程序代码
 CRect  rect;
 GetClientRect(&rect);
 CDC  dcMem;
 dcMem.CreateCompatibleDC(&dc);
 CBitmap  bmpBackground;
 bmpBackground.LoadBitmap(IDB_BITMAP6);
 BITMAP  bitmap;
 bmpBackground.GetBitmap(&bitmap);
 CBitmap* pbmpOld = dcMem.SelectObject(&bmpBackground); 
 dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
        // 不为绘图消息调用 CDialog::OnPaint()
}