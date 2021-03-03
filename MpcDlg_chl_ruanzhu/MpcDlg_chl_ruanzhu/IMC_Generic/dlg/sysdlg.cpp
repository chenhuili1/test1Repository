// dlg/SysDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "SysDlg.h"

#include "IMC_GenericDlg.h"

#if defined(WINCE)
#include "sip.h"
#include "SIPAPI.H"
#endif

// CSysDlg 对话框

IMPLEMENT_DYNAMIC(CSysDlg, CDialog)

CSysDlg::CSysDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSysDlg::IDD, pParent)
{
	m_listFont = NULL;
}

CSysDlg::~CSysDlg()
{
	delete m_listFont;
}

void CSysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PWLOGIN_OLD, m_edit[0]);
	DDX_Control(pDX, IDC_EDIT_PWLOGIN_NEW, m_edit[1]);
	DDX_Control(pDX, IDC_EDIT_PWEDIT_OLD, m_edit[2]);
	DDX_Control(pDX, IDC_EDIT_PWEDIT_NEW, m_edit[3]);
	DDX_Control(pDX, IDC_EDIT_PWSYS_OLD, m_edit[4]);
	DDX_Control(pDX, IDC_EDIT_PWSYS_NEW, m_edit[5]);
	DDX_Control(pDX, IDC_EDIT_PWRUN_OLD, m_edit[6]);
	DDX_Control(pDX, IDC_EDIT_PWRUN_NEW, m_edit[7]);
	DDX_Control(pDX, IDC_EDIT_DEV_ID, m_edit[8]);
	DDX_Control(pDX, IDC_EDIT_UNIT_0, m_edit[9]);
	DDX_Control(pDX, IDC_LIST1, m_listctr);
}


BEGIN_MESSAGE_MAP(CSysDlg, CDialog)
	ON_BN_CLICKED(IDC_BN_FACT_CFG, &CSysDlg::OnBnClickedBnFactCfg)
	ON_BN_CLICKED(IDOK, &CSysDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSysDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BN_CHPW_LOGIN, &CSysDlg::OnBnClickedBnChpwLogin)
	ON_BN_CLICKED(IDC_BN_CHPW_EDIT, &CSysDlg::OnBnClickedBnChpwEdit)
	ON_BN_CLICKED(IDC_BN_CHPW_SYS, &CSysDlg::OnBnClickedBnChpwSys)
	ON_BN_CLICKED(IDC_BN_CHPW_RUN, &CSysDlg::OnBnClickedBnChpwRun)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BN_OK, &CSysDlg::OnBnClickedBnOk)
#if defined(WINCE)
	ON_CBN_SELENDOK(IDC_COMBO_KEYBOARD, &CSysDlg::OnCbnSelendokComboKeyboard)
#endif
	ON_MESSAGE(WM_MY_FACT_LOGIN, &CSysDlg::OnFactLgin)
	ON_BN_CLICKED(IDC_BN_DEBUG, &CSysDlg::OnBnClickedBnDebug)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CSysDlg::OnNMClickList1)
END_MESSAGE_MAP()


// CSysDlg 消息处理程序

CString string2wstring(char* lpcwszStr)  
{     
	CString strValue;
	int nLength = strlen(lpcwszStr);
	int nWide = MultiByteToWideChar( CP_ACP, 0, lpcwszStr, nLength, NULL, 0 );
	LPWSTR pszOutput = strValue.GetBuffer( nWide + 1 );
	MultiByteToWideChar( CP_ACP, 0, lpcwszStr, nLength, pszOutput, nWide );
	pszOutput[ nWide ] = 0;
	strValue.ReleaseBuffer();
	return strValue;
}
BOOL CSysDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	CString str;
	((CComboBox*)GetDlgItem(IDC_COMBO_NET))->ResetContent();
	for(int i=0; i<dlg->m_imc.m_cardnum; i++){
		str = string2wstring(dlg->m_imc.m_cardInfo.description[i]);
		((CComboBox*)GetDlgItem(IDC_COMBO_NET))->AddString(str);
	}

	UpdateCtr();
	
#if defined(WINCE)
	GetKeySipEnum();
#endif
	if(dlg->m_imc.IsOpen()){
		if(g_verinfo.isTest){
			__int64 time = g_verinfo.endtime - g_verinfo.starttime;
			int da = (int)(time/86400);
			str.Format(_T("试用版剩余使用天数: %d"), da);
			SetDlgItemText(IDC_STATIC_TEST_TIP, str);
		}
	}

//	m_edit[8].SetFloatFlag(EDIT_INT);
	InitListCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CSysDlg::InitListCtrl()
{
	//通过GetWindowLong来获取CListCtrl已有的样式
	int i=0;
	DWORD dwStyle = GetWindowLong(m_listctr.m_hWnd, GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;   //清除显示方式位 
	dwStyle|= LVS_REPORT; //LVS_LIST;//设置报表风格
	dwStyle|= LVS_SHOWSELALWAYS | LVS_SINGLESEL; ///始终高亮被选中的表项
	//在原有样式的基本上，添加LVS_REPORT扩展样式
	SetWindowLong(m_listctr.m_hWnd, GWL_STYLE, dwStyle);
	//获取已有的扩展样式
	DWORD dwStyles = m_listctr.GetExStyle();
	//取消复选框样式
	dwStyles &= ~LVS_EX_CHECKBOXES;
	dwStyles   |=LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES/*  | LVS_EX_CHECKBOXES */;
	//添加整行选择和表格线扩展样式
	m_listctr.SetExtendedStyle(dwStyles);
	//固定列宽
	CHeaderCtrl* pHeaderCtrl = (CHeaderCtrl*)m_listctr.GetHeaderCtrl();   
	pHeaderCtrl->EnableWindow( FALSE ) ;
	if(m_listFont == NULL){//
		m_listFont = new CFont;
		m_listFont->CreateFont(18,0,0,0,0,FALSE,FALSE,0,0,0,0,0,0,_T("宋体"));//创建字体
	}
	m_listctr.SetFont(m_listFont, TRUE);//设置字体改变行高
//	m_edit[9].SetFont(m_listFont, TRUE);
	//*/
	//设置列
	CRect rc;
	m_listctr.GetClientRect(&rc);
	int width = rc.Width() - 18;
	m_listctr.InsertColumn(0, _T("轴"),LVCFMT_LEFT,45);//width/15);
	m_listctr.InsertColumn(1, _T("工作速度"),LVCFMT_LEFT,90);//width*2/15);
	m_listctr.InsertColumn(2, _T("快移速度"),LVCFMT_LEFT,90);//width*2/15);
	m_listctr.InsertColumn(3, _T("点动速度"),LVCFMT_LEFT,90);//width*2/15);
	m_listctr.InsertColumn(4, _T("加速度"),LVCFMT_LEFT,90);//width*2/15);
	m_listctr.InsertColumn(5, _T("搜零速度"),LVCFMT_LEFT,90);//width*2/15);
	m_listctr.InsertColumn(6, _T("搜零方向"),LVCFMT_LEFT,90);//width*2/15);
	m_listctr.InsertColumn(7, _T("平滑因子"),LVCFMT_LEFT,90);//width*2/15);
	

}

#ifdef USE_JINGDU_4
#define FMT_VEL_STR _T("%0.04lf")
#else
#define FMT_VEL_STR _T("%0.02lf")
#endif

void CSysDlg::UpdateCtr()
{	
	int i;
	CString str;
	m_listctr.DeleteAllItems();
	memcpy(m_dir, g_cfg.homeDir, sizeof(char)*MAX_NAXIS);
	for(i=0; i<g_Naxis; i++){
		m_listctr.InsertItem(i, _T(""));
		m_listctr.SetItemText(i, 0, g_AxisName[i]);
		str.Format(FMT_VEL_STR, g_cfg.workVel[i]);
		m_listctr.SetItemText(i, 1, str);
		str.Format(FMT_VEL_STR, g_cfg.fastVel[i]);
		m_listctr.SetItemText(i, 2, str);
		str.Format(FMT_VEL_STR, g_cfg.jogVel[i]);
		m_listctr.SetItemText(i, 3, str);
		str.Format(FMT_VEL_STR, g_cfg.accel[i]);
		m_listctr.SetItemText(i, 4, str);
		str.Format(FMT_VEL_STR, g_cfg.homeVel[i]);
		m_listctr.SetItemText(i, 5, str);
		if(g_cfg.homeDir[i] == 0)
			m_listctr.SetItemText(i, 6, _T("正方向"));
		else
			m_listctr.SetItemText(i,6, _T("负方向"));
		str.Format(_T("%d"), g_cfg.smooth[i]);
		m_listctr.SetItemText(i, 7, str);
	}
	m_listctr.InsertItem(i, _T(""));
	i++;
	m_listctr.InsertItem(i, _T(""));
	m_listctr.SetItemText(i, 0, _T("轨迹"));
	str.Format(FMT_VEL_STR, g_cfg.locusVel);
	m_listctr.SetItemText(i, 1, str);
	str.Format(FMT_VEL_STR, g_cfg.locusFastVel);
	m_listctr.SetItemText(i, 2, str);
	m_listctr.SetItemText(i, 3, _T(""));
	str.Format(FMT_VEL_STR, g_cfg.locusAcc);
	m_listctr.SetItemText(i, 4, str);
//	m_listctr.SetItemText(i, 4, _T(""));
	m_listctr.SetItemText(i, 5, _T(""));

	SetDlgItemInt(IDC_EDIT_DEV_ID, g_cfg.devID);
	((CComboBox*)GetDlgItem(IDC_COMBO_NET))->SetCurSel(g_cfg.NetSel);
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(g_cfg.machinSel);
}

void CSysDlg::OnBnClickedBnFactCfg()
{
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	dlg->ShowDlg(JM_SINFO);
}
LRESULT CSysDlg::OnFactLgin(WPARAM wparam,LPARAM lparam)
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(!dlg->IsPasswordOK(MY_PW_FACT)) return 0;
	dlg->ShowDlg(JM_FACT);
	return 0;
}


void CSysDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	BOOL isOpen = GetCfg();
	dlg->m_imc.SetAccel();
	SaveCfg();
	dlg->ShowDlg(JM_MAIN);
	if(isOpen)
		MessageBox(_T("\r\n注意\r\n退出后需要重新搜零！\r\n"), _T("提示"));
//	CDialog::OnOK();
}

void CSysDlg::OnBnClickedBnOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetCfg();
}

void CSysDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	dlg->ShowDlg(JM_MAIN);
//	CDialog::OnCancel();
}

long CSysDlg::GetEditFloat(UINT id, double fac)
{
	WCHAR data[16];
	double dval;
	int len = GetDlgItemText(id, data, 15);
	if(len == 0) return 0;
	data[len] = 0;
	swscanf(data, _T("%lf"),&dval);
	return (long)(dval * fac);
}
double CSysDlg::GetEditFloat(UINT id)
{
	WCHAR data[16];
	double dval;
	int len = GetDlgItemText(id, data, 15);
	if(len == 0) return 0;
	data[len] = 0;
	swscanf(data, _T("%lf"),&dval);
	return dval;
}
double CSysDlg::GetListFloat(int row, int lie)
{
	WCHAR data[16];
	double dval;
	int len;
	len = m_listctr.GetItemText(row, lie, data, 15);
	if(len == 0) return 0;
	data[len] = 0;
	swscanf(data, _T("%lf"),&dval);
	return dval;
}
int CSysDlg::GetHomeDir(int row)
{
	WCHAR data[16];
	CString str = _T("正方向");
	int len;
	len = m_listctr.GetItemText(row, 6, data, 15);
	if(len == 0) return 0;
	data[len] = 0;
	if(str.CompareNoCase(data) == 0)
		return 0;
	return 1;
}
BOOL CSysDlg::GetCfg()
{
	double data;
	int i;
	HideEdit();
	for(i=0; i<g_Naxis; i++){
		data = GetListFloat(i, 1);
		if(data != 0) g_cfg.workVel[i] = data;
		data = GetListFloat(i, 2);
		if(data != 0) g_cfg.fastVel[i] = data;
		data = GetListFloat(i, 3);
		if(data != 0) g_cfg.jogVel[i] = data;
		data = GetListFloat(i, 4);
		if(data != 0) g_cfg.accel[i] = data;
		data = GetListFloat(i, 5);
		if(data != 0) g_cfg.homeVel[i] = data;
		
	//	g_cfg.homeDir[i] = GetHomeDir(i);
		data = GetListFloat(i, 7);
		g_cfg.smooth[i] = data;
	}
	memcpy(g_cfg.homeDir, m_dir, sizeof(char)*MAX_NAXIS);
	i++;
	data = GetListFloat(i, 1);
	if(data != 0) g_cfg.locusVel = data;
	data = GetListFloat(i, 2);
	if(data != 0) g_cfg.locusFastVel = data;
	data = GetListFloat(i, 4);
	if(data != 0) g_cfg.locusAcc = data;

	g_cfg.machinSel = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();

//	g_cfg.isAutoAddCMD = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
	WORD id;
	BOOL isOpen = FALSE;
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	id = GetDlgItemInt(IDC_EDIT_DEV_ID);
	if(id>=0 && id <64){
		if(id != g_cfg.devID){
			g_cfg.devID = id;
			isOpen = TRUE;
		}
	}
	id = ((CComboBox*)GetDlgItem(IDC_COMBO_NET))->GetCurSel();
	if(id != g_cfg.NetSel){
		g_cfg.NetSel = id;
		isOpen = TRUE;
	}
	if(isOpen)
		dlg->StartOpenTimer();
	return isOpen;
}

BOOL CSysDlg::IsPasswordOK(UINT id, int type)
{
	CString str;
	GetDlgItemText(id, str);
	WCHAR *pw;
	switch(type)
	{
//	case MY_PW_FACT:	pw = g_factcfg.PWfact; break;
	case MY_PW_LOGIN:	pw = g_cfg.PWlogin; break;
	case MY_PW_EDIT:	pw = g_cfg.PWEdit; break;
	case MY_PW_SYS:		pw = g_cfg.PWSys; break;
	case MY_PW_RUN:		pw = g_cfg.PWRun; break;
	}
	if(pw[0] == 0) return TRUE;
	if(str.GetLength() != PASSWORD_USE_LEN){
		MessageBox(_T("密码错误"));
		SetDlgItemText(id, _T(""));
		return FALSE;
	}
	for(int i=0; i<PASSWORD_USE_LEN; i++)
	{
		if(str.GetAt(i) != pw[i]){
			MessageBox(_T("密码错误"));
			SetDlgItemText(id, _T(""));
			return FALSE;
		}
	}
	return TRUE;
}

void CSysDlg::OnBnClickedBnChpwLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(!IsPasswordOK(IDC_EDIT_PWLOGIN_OLD, MY_PW_LOGIN)) return;
	WCHAR pw[16];
	int len;
	len = GetDlgItemText(IDC_EDIT_PWLOGIN_NEW, pw, 16);
	if(len == 0){
		memset(g_cfg.PWlogin, 0, PASSWORD_USE_LEN * sizeof(WCHAR));
	}else {
		if(len != PASSWORD_USE_LEN){
			MessageBox(_T("密码长度为6个字符"));
			return;
		}
		memcpy(g_cfg.PWlogin, pw, PASSWORD_USE_LEN * sizeof(WCHAR));
	}
}


void CSysDlg::OnBnClickedBnChpwEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(!IsPasswordOK(IDC_EDIT_PWEDIT_OLD, MY_PW_EDIT)) return;
	WCHAR pw[16];
	int len;
	len = GetDlgItemText(IDC_EDIT_PWEDIT_NEW, pw, 16);
	
	if(len == 0){
		memset(g_cfg.PWEdit, 0, PASSWORD_USE_LEN * sizeof(WCHAR));
	}else {
		if(len != PASSWORD_USE_LEN){
			MessageBox(_T("密码长度为6个字符"));
			return;
		}
		memcpy(g_cfg.PWEdit, pw, PASSWORD_USE_LEN * sizeof(WCHAR));
	}
}


void CSysDlg::OnBnClickedBnChpwSys()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(!IsPasswordOK(IDC_EDIT_PWSYS_OLD, MY_PW_SYS)) return;
	WCHAR pw[16];
	int len;
	len = GetDlgItemText(IDC_EDIT_PWSYS_NEW, pw, 16);
	
	if(len == 0){
		memset(g_cfg.PWSys, 0, PASSWORD_USE_LEN * sizeof(WCHAR));
	}else {
		if(len != PASSWORD_USE_LEN){
			MessageBox(_T("密码长度为6个字符"));
			return;
		}
		memcpy(g_cfg.PWSys, pw, PASSWORD_USE_LEN * sizeof(WCHAR));
	}
}


void CSysDlg::OnBnClickedBnChpwRun()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(!IsPasswordOK(IDC_EDIT_PWRUN_OLD, MY_PW_RUN)) return;
	WCHAR pw[16];
	int len;
	len = GetDlgItemText(IDC_EDIT_PWRUN_NEW, pw, 16);
	
	if(len == 0){
		memset(g_cfg.PWRun, 0, PASSWORD_USE_LEN * sizeof(WCHAR));
	}else {
		if(len != PASSWORD_USE_LEN){
			MessageBox(_T("密码长度为6个字符"));
			return;
		}
		memcpy(g_cfg.PWRun, pw, PASSWORD_USE_LEN * sizeof(WCHAR));
	}
}


void CSysDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: 在此处添加消息处理程序代码
	if(bShow){
	//	InitCtr();
		SetDlgItemText(IDC_EDIT_PWLOGIN_OLD, _T(""));
		SetDlgItemText(IDC_EDIT_PWLOGIN_NEW, _T(""));
		SetDlgItemText(IDC_EDIT_PWEDIT_OLD, _T(""));
		SetDlgItemText(IDC_EDIT_PWEDIT_NEW, _T(""));
		SetDlgItemText(IDC_EDIT_PWSYS_OLD, _T(""));
		SetDlgItemText(IDC_EDIT_PWSYS_NEW, _T(""));
		SetDlgItemText(IDC_EDIT_PWRUN_OLD, _T(""));
		SetDlgItemText(IDC_EDIT_PWRUN_NEW, _T(""));
	}
}


//*************************************************************************************************

#if defined(WINCE)
CTypedPtrMap<CMapStringToPtr,CString,CLSID*> g_SipMap;
int SipEnumIMProc(IMENUMINFO *pIMInfo) 
{ 
	CLSID* pCLSID = new CLSID; 
	memcpy(pCLSID,&pIMInfo->clsid,sizeof(CLSID)); 
	g_SipMap.SetAt(CString(pIMInfo->szName),pCLSID); 
	TRACE(_T("%sn"),CString(pIMInfo->szName)); 
	return 1; 
} 
//http://dev.yesky.com/452/2426452.shtml
void CSysDlg::GetKeySipEnum() 
{ //获取软键盘列表
	SipEnumIM(SipEnumIMProc); 
	CLSID CurrSip; 
	SipGetCurrentIM(&CurrSip); 
	int nCurrSip = LB_ERR, nSipCount = 0; 
	CString sSipName, sCurrSipName; 
	CLSID *pCLSID = NULL; 
	for (POSITION pos = g_SipMap.GetStartPosition(); pos; ) 
	{ 
		g_SipMap.GetNextAssoc(pos,sSipName,pCLSID); 
		((CComboBox*)GetDlgItem(IDC_COMBO_KEYBOARD))->AddString(sSipName); 
		if ( memcmp(&CurrSip,pCLSID,sizeof(CLSID)) == 0 ) 
		{ 
			nCurrSip = nSipCount; 
			sCurrSipName = sSipName; 
		} 
		nSipCount++; 
	} 
	((CComboBox*)GetDlgItem(IDC_COMBO_KEYBOARD))->SelectString(0,sCurrSipName); 
}

void CSysDlg::OnSipSelect() 
{ //选择软键盘
	int nSel = ((CComboBox*)GetDlgItem(IDC_COMBO_KEYBOARD))->GetCurSel(); 
	if ( LB_ERR == nSel ) 
		return; 
	CString sSipName; 
	((CComboBox*)GetDlgItem(IDC_COMBO_KEYBOARD))->GetLBText(nSel,sSipName); 
	CLSID *pCLSID = NULL; 
	if ( !g_SipMap.Lookup(sSipName,pCLSID) ) 
		return; 
	BOOL bRes = SipSetCurrentIM(pCLSID); 
	memcpy(&g_cfg.SipID, pCLSID, sizeof(CLSID));
	if ( !bRes ) 
		TRACE(L"SipSetCurrentIM returned %lun",GetLastError()); 
}
void CSysDlg::SetDefSip()
{
	CLSID *pCLSID = NULL; 
	CString sSipName; 
	int nCurrSip = 0;
	for (POSITION pos = g_SipMap.GetStartPosition(); pos; ) 
	{ 
		g_SipMap.GetNextAssoc(pos,sSipName,pCLSID); 
		if ( memcmp(&g_cfg.SipID,pCLSID,sizeof(CLSID)) == 0 ) 
		{ 
			if ( !g_SipMap.Lookup(sSipName,pCLSID) ) 
				return;
			BOOL bRes = SipSetCurrentIM(pCLSID);
			break;
		}
		nCurrSip ++;
	} 
	((CComboBox*)GetDlgItem(IDC_COMBO_KEYBOARD))->SetCurSel(nCurrSip);
}
void CSysDlg::OnCbnSelendokComboKeyboard()
{
	// TODO: 在此添加控件通知处理程序代码
	OnSipSelect();
}
#endif

BOOL CSysDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_LBUTTONUP){
		UINT buttonID=GetWindowLong(pMsg->hwnd,   GWL_ID);//获得按钮ID
		switch(buttonID)
		{
		case IDC_STATIC_FACT_IN1: m_factID = 1; return TRUE;
		case IDC_STATIC_FACT_IN2: if(m_factID == 1) m_factID = 2; else m_factID = 0; return TRUE;
		case IDC_STATIC_FACT_IN3: if(m_factID == 2) m_factID = 3; else m_factID = 0; return TRUE;
		case IDC_STATIC_FACT_IN4: if(m_factID == 3) m_factID = 4; else m_factID = 0; return TRUE;
		case IDC_STATIC_FACT_IN5: 
			if(m_factID == 4) 
				::PostMessage(this->m_hWnd, WM_MY_FACT_LOGIN, (WPARAM)0, (LPARAM)0);
			else m_factID = 0; 
			break; 
		default : m_factID = 0;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CSysDlg::OnBnClickedBnDebug()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	dlg->ShowDlg(JM_DEBUG);
}

//移动Edit
void CSysDlg::MoveEdit(int row, int lie)
{
	CRect rect,rc;
	CString str;
	if(row < 0) return;
	m_row = row;
	m_lie = lie;

		m_listctr.GetWindowRect(&rc);
		ScreenToClient(&rc);
		m_listctr.GetSubItemRect(row, lie, LVIR_LABEL,rect);//得到该单元格矩形的位置大小信息。
		rect.OffsetRect(rc.left+2, rc.top+1);
		str = m_listctr.GetItemText(row, lie);				//获取该单元格已存在的文本内容。


//	rect.top -= 1;
	m_edit[9].MoveWindow(rect);
	m_edit[9].SetWindowText(str);	
	m_edit[9].ShowWindow(SW_SHOW);	
	m_edit[9].SetSel(0,-1);						//全选编辑框的内容。
	m_edit[9].SetFocus();
}
//隐藏Edit
BOOL CSysDlg::HideEdit()
{
	CString str;
	if(!m_edit[9].IsWindowVisible()) return TRUE;
	m_edit[9].GetWindowText(str);
	m_listctr.SetItemText(m_row, m_lie, str);
	m_edit[9].ShowWindow(SW_HIDE);	
	return TRUE;
}
void CSysDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	HideEdit();
	if(phdr->iItem >= 0){
		if(phdr->iButton != 0){
			if(phdr->iItem == g_Naxis){
			}else if(phdr->iItem == g_Naxis+1){
				if(phdr->iButton == 1 || phdr->iButton == 2 || phdr->iButton == 4 ){
					m_row = phdr->iItem;
					MoveEdit( m_row, phdr->iButton);
				}
			}else{
				m_row = phdr->iItem;
				if(phdr->iButton != 6){
					MoveEdit( m_row, phdr->iButton);
				}else{
					m_dir[m_row] = ! m_dir[m_row];
					if(m_dir[m_row] == 0)
						m_listctr.SetItemText(m_row, 6, _T("正方向"));
					else
						m_listctr.SetItemText(m_row,6, _T("负方向"));
				}
			}
		}
	}
	*pResult = 0;
}
