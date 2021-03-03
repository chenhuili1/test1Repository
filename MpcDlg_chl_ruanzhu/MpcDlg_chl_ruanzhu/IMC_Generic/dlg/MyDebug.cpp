// dlg/MyDebug.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "MyDebug.h"

#include "IMC_GenericDlg.h"

// CMyDebug 对话框

IMPLEMENT_DYNAMIC(CMyDebug, CDialog)

CMyDebug::CMyDebug(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDebug::IDD, pParent)
{
	m_bmp0= (HBITMAP)::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP4));
	m_bmp1= (HBITMAP)::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP3));

}

CMyDebug::~CMyDebug()
{
	delete m_pImageList;
}

void CMyDebug::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listctr1);
	DDX_Control(pDX, IDC_LIST2, m_listctr2);
}


BEGIN_MESSAGE_MAP(CMyDebug, CDialog)
	ON_WM_TIMER()
	ON_MESSAGE(WM_MY_STATUS_INFO,&CMyDebug::OnStatusTotal)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyDebug::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMyDebug 消息处理程序

BOOL CMyDebug::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitListCtrl();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CMyDebug::InitListCtrl()
{
	//通过GetWindowLong来获取CListCtrl已有的样式
	int i=0;
	DWORD dwStyle = GetWindowLong(m_listctr1.m_hWnd, GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;   //清除显示方式位 
	dwStyle|= LVS_REPORT; //LVS_LIST;//设置报表风格
	dwStyle|= LVS_SHOWSELALWAYS | LVS_SINGLESEL; ///始终高亮被选中的表项
	//在原有样式的基本上，添加LVS_REPORT扩展样式
	SetWindowLong(m_listctr1.m_hWnd, GWL_STYLE, dwStyle);
	SetWindowLong(m_listctr2.m_hWnd, GWL_STYLE, dwStyle);
	//获取已有的扩展样式
	DWORD dwStyles = m_listctr1.GetExStyle();
	//取消复选框样式
	dwStyles &= ~LVS_EX_CHECKBOXES;
	dwStyles   |=LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES/*  | LVS_EX_CHECKBOXES */;
	//添加整行选择和表格线扩展样式
	m_listctr1.SetExtendedStyle(dwStyles);
	m_listctr2.SetExtendedStyle(dwStyles);

	CBitmap       bitmap;   
	bitmap.LoadBitmap(IDB_BITMAP2);   
	m_pImageList  =  new CImageList();   
	m_pImageList->Create(17,16,TRUE,2,2);   
	m_pImageList->Add(&bitmap, RGB(0, 0, 0));   
	m_listctr1.SetImageList(m_pImageList,LVSIL_SMALL); 
	m_listctr2.SetImageList(m_pImageList,LVSIL_SMALL); 
/*
	if(m_listFont == NULL){//
		m_listFont = MyGetFonts(20,_T("宋体"), FW_NORMAL);//创建字体
	}
	m_listctr1.SetFont(m_listFont, TRUE);//设置字体改变行高*/
	//设置列
	LVCOLUMN col;      
	col.mask = LVCF_FMT; 
	CRect rc;

	m_listctr1.GetClientRect(&rc);
	int width = rc.Width() - 30;
	m_listctr1.InsertColumn(0, _T("轴号"),LVCFMT_CENTER,50);
	m_listctr1.InsertColumn(1, _T("指令位置"),LVCFMT_LEFT,80); 
	m_listctr1.InsertColumn(2, _T("实际位置"),LVCFMT_LEFT,80); 
	m_listctr1.InsertColumn(3, _T("正限位"),LVCFMT_LEFT,65);
	m_listctr1.InsertColumn(4, _T("负限位"),LVCFMT_LEFT,65);
	m_listctr1.InsertColumn(5, _T("原点"),LVCFMT_LEFT,55);
	m_listctr1.InsertColumn(6, _T("探针"),LVCFMT_LEFT,55);
	m_listctr1.InsertColumn(7, _T("报警"),LVCFMT_LEFT,55);
	m_listctr1.InsertColumn(8, _T("到位"),LVCFMT_LEFT,55);
	m_listctr1.InsertColumn(9, _T("GIN1"),LVCFMT_LEFT,55); 
	m_listctr1.InsertColumn(10, _T("GIN2"),LVCFMT_LEFT,55); 
	m_listctr1.InsertColumn(11, _T("GOUT1"),LVCFMT_LEFT,60); 
	m_listctr1.InsertColumn(12, _T("GOUT2"),LVCFMT_LEFT,60); 
	m_listctr1.InsertColumn(13, _T("GOUT3"),LVCFMT_LEFT,60); 
	col.fmt = LVCFMT_CENTER; 
	m_listctr1.SetColumn(0, &col);

	m_listctr2.InsertColumn(0, _T("轴号"),LVCFMT_CENTER,50);
	m_listctr2.InsertColumn(1, _T("PLim"),LVCFMT_LEFT,55);
	m_listctr2.InsertColumn(2, _T("NLim"),LVCFMT_LEFT,55);
	m_listctr2.InsertColumn(3, _T("PSOF"),LVCFMT_LEFT,55);
	m_listctr2.InsertColumn(4, _T("NSOF"),LVCFMT_LEFT,55);
	m_listctr2.InsertColumn(5, _T("Stop"),LVCFMT_LEFT,55);
	m_listctr2.InsertColumn(6, _T("ALM"),LVCFMT_LEFT,45);
	m_listctr2.InsertColumn(7, _T("POSLIM"),LVCFMT_LEFT,65);
	m_listctr2.InsertColumn(8, _T("TGPOSOV"),LVCFMT_LEFT,75);
	m_listctr2.InsertColumn(9, _T("POSOV"),LVCFMT_LEFT,60);
	m_listctr2.InsertColumn(10, _T("INSERR"),LVCFMT_LEFT,65);
	m_listctr2.InsertColumn(11, _T("VELLIM"),LVCFMT_LEFT,65);
	m_listctr2.InsertColumn(12, _T("ACCLIM"),LVCFMT_LEFT,65);
	m_listctr2.InsertColumn(13, _T("DELPOS"),LVCFMT_LEFT,65);

}

void CMyDebug::MyHideWindow()
{
	m_isHide = TRUE;
	KillTimer(TIMER_DEBUG);
	ShowWindow(SW_HIDE);
}
void CMyDebug::SetNetType(int ver)
{
	switch(ver)
	{
	case 0x3041:	m_type = 0; break;	//16个输出
	case 0x3062:	
	case 0x3102:	
	case 0x3142:	m_type = 1; break;//40个输出
	case 0x3042:	
	case 0x3082:	
	case 0x3122:	
	case 0x3162:	m_type = 2; break;//48个输出
	}
}
void CMyDebug::UpdateCtr()
{
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	CString str;
	WORD ver;
	m_isHide = FALSE;
	dlg->m_imc.ReadVersion(&ver);
	SetNetType(ver);
	InitDes();
	InitVar();
	m_errNum = 0;
	SetDlgItemInt(IDC_STATIC_TIP_3, m_errNum);

	m_listctr1.DeleteAllItems();
	m_listctr2.DeleteAllItems();
	for(int i=0; i<MAX_NAXIS; i++)
	{
		m_listctr1.InsertItem(i, _T(""), -1);
		str.Format(_T("B%d"), i);
		m_listctr1.SetItemText(i, 9, str);
		m_listctr1.SetItemText(i, 10, str);
		m_listctr1.SetItemText(i, 11, str);
		m_listctr1.SetItemText(i, 12, str);
		m_listctr1.SetItemText(i, 13, str);
	}
	for(int i=0; i<g_Naxis; i++)
	{
		str.Format(_T("%s"), g_AxisName[i]);
		m_listctr1.SetItemText(i, 0, str);
		m_listctr2.InsertItem(i, _T(""), -1);
		m_listctr2.SetItemText(i, 0, str);
	}
	UpdateAio();
	UpdateGin();
	UpdateGout();
	SetTimer(TIMER_DEBUG, 40, NULL);
}
void CMyDebug::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	IMC_STATUS status;
	long data;
	short i, k, n;
	CString str;
	switch(nIDEvent)
	{
	case TIMER_DEBUG:
		KillTimer(TIMER_DEBUG);
		//获取指令位置
		status = dlg->m_imc.GetParamMul(m_posDes, g_Naxis);
		if(status == IMC_OK){
			for(i=0; i<g_Naxis; i++)
			{
				data = m_posDes[i].data[0] | (m_posDes[i].data[1] << 16);
				if(data != m_curpos[i]){
					m_curpos[i] = data;					
					str.Format(_T("%d"), data);
					m_listctr1.SetItemText(i, 1, str);
				}
			}
		}else OnStatusTotal(0, 0);//PostMessage( WM_MY_STATUS_INFO, 0, 0);
		//获取机械位置
		status = dlg->m_imc.GetParamMul( m_encpDes, g_Naxis);
		if(status == IMC_OK){
			for(i=0; i<g_Naxis; i++)
			{
				data = m_encpDes[i].data[0] | (m_encpDes[i].data[1] << 16);
				if(data != m_encp[i]){
					m_encp[i] = data;					
					str.Format(_T("%d"), data);
					m_listctr1.SetItemText(i, 2, str);
				}
			}
		}else OnStatusTotal(0, 0);//PostMessage( WM_MY_STATUS_INFO, 0, 0);
		//获取轴IO
		status = dlg->m_imc.GetParamMul( m_aioDes, g_Naxis);
		if(status == IMC_OK){
			UpdateAio();
		}else OnStatusTotal(0, 0);//PostMessage( WM_MY_STATUS_INFO, 0, 0);
		//获取输入IO
		status = dlg->m_imc.GetParamMul( m_ginDes, 2);
		if(status == IMC_OK){
			UpdateGin();
		}else OnStatusTotal(0, 0);//PostMessage( WM_MY_STATUS_INFO, 0, 0);
		//获取输出IO
		status = dlg->m_imc.GetParamMul( m_goutDes, 3);
		if(status == IMC_OK){
			UpdateGout();
		}else OnStatusTotal(0, 0);//PostMessage( WM_MY_STATUS_INFO, 0, 0);
		//其他寄存器
		status = dlg->m_imc.GetParamMul( m_OtherDes, 3);
		if(status == IMC_OK){
			CStatic *ic;
			for(i=0; i<3; i++)
			{
				if(m_OtherDes[i].data[0] != m_other[i])
				{
					ic = (CStatic*)GetDlgItem(IDC_STATIC_TIP_0 + i);
					m_other[i] = m_OtherDes[i].data[0];
					if(m_other[i])
						ic->SetBitmap(m_bmp1);
					else
						ic->SetBitmap(m_bmp0);
				}
			}
		}else OnStatusTotal(0, 0);//PostMessage( WM_MY_STATUS_INFO, 0, 0);
		//获取错误寄存器
		status = dlg->m_imc.GetParamMul( m_errDes, g_Naxis);
		if(status == IMC_OK){
			for(i=0; i<g_Naxis; i++)
			{
				if(m_errDes[i].data[0] != m_err[i]){
					m_err[i] = m_errDes[i].data[0];				
					for(k=0; k<5; k++){
						if(m_err[i] & (1 << k))
							m_listctr2.SetItem(i, 1+k, LVIF_TEXT|LVIF_IMAGE, _T(""),0, NULL, NULL, 0); //正限位
						else
							m_listctr2.SetItem(i, 1+k, LVIF_TEXT|LVIF_IMAGE, _T(""),1, NULL, NULL, 0); //正限位
					}
					n = k;
					for(k=6; k<8; k++){
						if(m_err[i] & (1 <<k))
							m_listctr2.SetItem(i, 1 + n, LVIF_TEXT|LVIF_IMAGE, _T(""),0, NULL, NULL, 0); //正限位
						else
							m_listctr2.SetItem(i, 1 + n, LVIF_TEXT|LVIF_IMAGE, _T(""),1, NULL, NULL, 0); //正限位
						n++;
					}
					for(k=9; k<11; k++){
						if(m_err[i] & (1 <<k))
							m_listctr2.SetItem(i, 1 + n, LVIF_TEXT|LVIF_IMAGE, _T(""),0, NULL, NULL, 0); //正限位
						else
							m_listctr2.SetItem(i, 1 + n, LVIF_TEXT|LVIF_IMAGE, _T(""),1, NULL, NULL, 0); //正限位
						n++;
					}
					for(k=12; k<16; k++){
						if(m_err[i] & (1 <<k))
							m_listctr2.SetItem(i, 1 + n, LVIF_TEXT|LVIF_IMAGE, _T(""),0, NULL, NULL, 0); //正限位
						else
							m_listctr2.SetItem(i, 1 + n, LVIF_TEXT|LVIF_IMAGE, _T(""),1, NULL, NULL, 0); //正限位
						n++;
					}
				}
			}
		}else OnStatusTotal(0, 0);//PostMessage( WM_MY_STATUS_INFO, 0, 0);
		if(!m_isHide) SetTimer(TIMER_DEBUG, 40, NULL);
		break;
	}

	CDialog::OnTimer(nIDEvent);
}

void CMyDebug::InitDes()
{
	int i;
	for(i=0; i<g_Naxis; i++)
	{
		m_posDes[i].axis = i;
		m_posDes[i].addr = curposLoc;
		m_posDes[i].len = 2;
		
		m_encpDes[i].axis = i;
		m_encpDes[i].addr = encpLoc;
		m_encpDes[i].len = 2;

		m_errDes[i].axis = i;
		m_errDes[i].addr = errorLoc;
		m_errDes[i].len = 1;
		m_errDes[i].data[0] = 0;

		m_aioDes[i].axis = i;
		m_aioDes[i].addr = aioLoc;
		m_aioDes[i].len = 1;
		m_aioDes[i].data[0] = 0;
	}
	m_ginDes[0].axis = 0;
	m_ginDes[0].addr = gin1Loc;
	m_ginDes[0].len = 1;
	m_ginDes[0].data[0] = -1;
	m_ginDes[1].axis = 0;
	m_ginDes[1].addr = gin2Loc;
	m_ginDes[1].len = 1;
	m_ginDes[1].data[0] = -1;

	m_goutDes[0].axis = 0;
	m_goutDes[0].addr = gout1Loc;
	m_goutDes[0].len = 1;
	m_goutDes[0].data[0] = 0;
	m_goutDes[1].axis = 0;
	m_goutDes[1].addr = gout2Loc;
	m_goutDes[1].len = 1;
	m_goutDes[1].data[0] = 0;
	m_goutDes[2].axis = 0;
	m_goutDes[2].addr = gout3Loc;
	m_goutDes[2].len = 1;
	m_goutDes[2].data[0] = 0;

	m_OtherDes[0].axis = 0;
	m_OtherDes[0].addr = stopinLoc;
	m_OtherDes[0].len = 1;
	m_OtherDes[1].axis = 0;
	m_OtherDes[1].addr = emstopLoc;
	m_OtherDes[1].len = 1;
	m_OtherDes[2].axis = 0;
	m_OtherDes[2].addr = hpauseLoc;
	m_OtherDes[2].len = 1;
}
void CMyDebug::InitVar()
{
	int i;
	for(i=0; i<g_Naxis; i++)
	{
		m_encp[i] = -100;
		m_curpos[i] = -100;
		m_err[i] = -1;
		m_aio[i] = 0;
	}
	m_gin[0] = 0;
	m_gin[1] = 0;
	m_gout[0] = -1;
	m_gout[1] = -1;
	m_gout[2] = -1;
	m_other[0] = -1;
	m_other[1] = -1;
	m_other[2] = -1;
}

void CMyDebug::UpdateAio()
{
	int i, k;
	WORD data1, data2;
	for(i=0; i<g_Naxis; i++)
	{
		if(m_aioDes[i].data[0] != m_aio[i])
		{
			for(k=0; k<6; k++){
				data1 = m_aio[i] & (1 << k);
				data2 =  m_aioDes[i].data[0] & (1 << k);
				if(data1 == data2) continue;
				if(data2){
					m_listctr1.SetItem(i, 3 + k, LVIF_TEXT|LVIF_IMAGE, _T(""),0, NULL, NULL, 0); //正限位
				}else
					m_listctr1.SetItem(i, 3 + k, LVIF_TEXT|LVIF_IMAGE, _T(""),1, NULL, NULL, 0); //正限位
			}
			m_aio[i] = m_aioDes[i].data[0];
		}
	}
}
void CMyDebug::UpdateGin()
{
	int i, k;
	WORD data1, data2;
	for(i=0; i<2; i++)
	{
		if(m_ginDes[i].data[0] != m_gin[i])
		{
			for(k=0; k<16; k++){
				data1 = m_gin[i] & (1 << k);
				data2 =  m_ginDes[i].data[0] & (1 << k);
				if(data1 == data2) continue;
				if(data2){
					m_listctr1.SetItem(k, 9 + i, LVIF_IMAGE, NULL,0, NULL, NULL, 0); //正限位
				}else
					m_listctr1.SetItem(k, 9 + i, LVIF_IMAGE, NULL,1, NULL, NULL, 0); //正限位
			}
			m_gin[i] = m_ginDes[i].data[0];
		}
	}
}
void CMyDebug::UpdateGout()
{
	int i, k, num, cnt;
	WORD data1, data2;
	if(m_type == 0) num = 1;
	else num = 3;
	for(i=0; i<num; i++)
	{
		if(m_goutDes[i].data[0] != m_gout[i])
		{
			if(i == 2 && m_type == 1)
				cnt = 8;
			else cnt = 16;
			for(k=0; k<cnt; k++){
				data1 = m_gout[i] & (1 << k);
				data2 =  m_goutDes[i].data[0] & (1 << k);
				if(data1 == data2) continue;
				if(data2){
					m_listctr1.SetItem(k, 11 + i, LVIF_IMAGE, NULL,0, NULL, NULL, 0); //正限位
				}else
					m_listctr1.SetItem(k, 11 + i, LVIF_IMAGE, NULL,1, NULL, NULL, 0); //正限位
			}
			m_gout[i] = m_goutDes[i].data[0];
		}
	}
}
LRESULT CMyDebug::OnStatusTotal(WPARAM wparam,LPARAM lparam)
{
	m_errNum ++;
	SetDlgItemInt(IDC_STATIC_TIP_3, m_errNum);
	return 0;
}
void CMyDebug::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	dlg->ShowDlg(JM_SYS);
}
