// dlg/FactPolar.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "FactPolar.h"


// CFactPolar 对话框

IMPLEMENT_DYNAMIC(CFactPolar, CDialog)

CFactPolar::CFactPolar(CWnd* pParent /*=NULL*/)
	: CDialog(CFactPolar::IDD, pParent)
{
	m_listFont = NULL;
}

CFactPolar::~CFactPolar()
{
	delete m_listFont;
}

void CFactPolar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listctr1);
	DDX_Control(pDX, IDC_LIST2, m_listctr2);
}


BEGIN_MESSAGE_MAP(CFactPolar, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CFactPolar::OnNMClickList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CFactPolar::OnNMClickList2)
END_MESSAGE_MAP()


// CFactPolar 消息处理程序

BOOL CFactPolar::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitListCtrl();
	UpdateCtr();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CFactPolar::InitListCtrl()
{
	//通过GetWindowLong来获取CListCtrl已有的样式
	int i=0;
	DWORD dwStyle = GetWindowLong(m_listctr2.m_hWnd, GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;   //清除显示方式位 
	dwStyle|= LVS_REPORT; //LVS_LIST;//设置报表风格
	dwStyle|= LVS_SHOWSELALWAYS | LVS_SINGLESEL; ///始终高亮被选中的表项
	//在原有样式的基本上，添加LVS_REPORT扩展样式
//	SetWindowLong(m_listctr1.m_hWnd, GWL_STYLE, dwStyle);
	SetWindowLong(m_listctr2.m_hWnd, GWL_STYLE, dwStyle);
	//获取已有的扩展样式
	DWORD dwStyles = m_listctr2.GetExStyle();
	//取消复选框样式
	dwStyles &= ~LVS_EX_CHECKBOXES;
	dwStyles   |=LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES/*  | LVS_EX_CHECKBOXES */;
	//添加整行选择和表格线扩展样式
//	m_listctr1.SetExtendedStyle(dwStyles);
	m_listctr2.SetExtendedStyle(dwStyles);

	if(m_listFont == NULL){//
		m_listFont = MyGetFonts(18,_T("宋体"), FW_NORMAL);//创建字体
	}
//	m_listctr1.SetFont(m_listFont, TRUE);//设置字体改变行高*/
	m_listctr2.SetFont(m_listFont, TRUE);//设置字体改变行高*/
	//设置列
	LVCOLUMN col;      
	col.mask = LVCF_FMT; 
	CRect rc;
/*
	m_listctr1.GetClientRect(&rc);
	int width = rc.Width() - 18;
	m_listctr1.InsertColumn(0, _T("输入端口"),LVCFMT_CENTER,width*3/5);
	m_listctr1.InsertColumn(1, _T("极性"),LVCFMT_LEFT,width*2/5); 
	col.fmt = LVCFMT_CENTER; 
	m_listctr1.SetColumn(0, &col);
*/
	m_listctr2.GetClientRect(&rc);
	int width = rc.Width() - 18;
	m_listctr2.InsertColumn(0, _T("输入端口"),LVCFMT_CENTER,width*3/5);
	m_listctr2.InsertColumn(1, _T("极性"),LVCFMT_LEFT,width*2/5); 
	col.fmt = LVCFMT_CENTER; 
	m_listctr2.SetColumn(0, &col);
/*
	CString str;
	for(i=0; i<INPUT_NUM; i++)
	{
		m_listctr1.InsertItem(i, _T(""));
		str.Format(_T("输入端口 %d"),  i+1);
		m_listctr1.SetItemText(i, 0, str);
	}*/
	m_listctr2.InsertItem(0, _T(""));
	m_listctr2.SetItemText(0, 0, _T("急停输入端口"));
	
}

void CFactPolar::UpdateCtr()
{
	CString str;
	int i, k;
	memcpy(&m_polar, &g_polar, sizeof(FACT_POLAR));
/*	for(i=0; i<INPUT_NUM; i++)
	{
		if(m_polar.gin[i])
			m_listctr1.SetItemText(i, 1, _T("高电平有效"));
		else
			m_listctr1.SetItemText(i, 1, _T("低电平有效"));
	}
*/
	m_listctr2.DeleteAllItems();
	m_listctr2.InsertItem(0, _T(""));
	m_listctr2.SetItemText(0, 0, _T("急停输入端口"));
	if(m_polar.stopin)
		m_listctr2.SetItemText(0, 1, _T("高电平有效"));
	else
		m_listctr2.SetItemText(0, 1, _T("低电平有效"));
	k = 1;
	for(i=0; i<g_Naxis; i++)
	{
		m_listctr2.InsertItem(k, _T(""));
		str.Format(_T("%s正限位"),  g_AxisName[i]);
		m_listctr2.SetItemText(k, 0, str);
		if(m_polar.aioP[i])
			m_listctr2.SetItemText(k, 1, _T("高电平有效"));
		else
			m_listctr2.SetItemText(k, 1, _T("低电平有效"));
		k++;

		m_listctr2.InsertItem(k, _T(""));
		str.Format(_T("%s负限位"),  g_AxisName[i]);
		m_listctr2.SetItemText(k, 0, str);
		if(m_polar.aioN[i])
			m_listctr2.SetItemText(k, 1, _T("高电平有效"));
		else
			m_listctr2.SetItemText(k, 1, _T("低电平有效"));
		k++;
	}
}

BOOL CFactPolar::GetCfg()
{
	memcpy(&g_polar, &m_polar, sizeof(FACT_POLAR));

	return TRUE;
}
void CFactPolar::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if(phdr->iItem >= 0 && phdr->iItem < INPUT_NUM){
		if(phdr->iButton == 1){
			m_polar.gin[phdr->iItem] = !m_polar.gin[phdr->iItem];
			if(m_polar.gin[phdr->iItem])
				m_listctr1.SetItemText(phdr->iItem, 1, _T("高电平有效"));
			else
				m_listctr1.SetItemText(phdr->iItem, 1, _T("低电平有效"));
		}
	}
	*pResult = 0;
}
void CFactPolar::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if(phdr->iItem == 0){
		if(phdr->iButton == 1){
			m_polar.stopin = !m_polar.stopin;
			if(m_polar.stopin)
				m_listctr2.SetItemText(phdr->iItem, 1, _T("高电平有效"));
			else
				m_listctr2.SetItemText(phdr->iItem, 1, _T("低电平有效"));
		}
	}
	else if(phdr->iItem > 0 && phdr->iItem <= 2*g_Naxis){
		if(phdr->iButton == 1){
			int index = (phdr->iItem - 1)/2;	//第几轴
			if(phdr->iItem%2 == 1){
				m_polar.aioP[index] = !m_polar.aioP[index];
				if(m_polar.aioP[index])
					m_listctr2.SetItemText(phdr->iItem, 1, _T("高电平有效"));
				else
					m_listctr2.SetItemText(phdr->iItem, 1, _T("低电平有效"));
			}else{
				m_polar.aioN[index] = !m_polar.aioN[index];
				if(m_polar.aioN[index])
					m_listctr2.SetItemText(phdr->iItem, 1, _T("高电平有效"));
				else
					m_listctr2.SetItemText(phdr->iItem, 1, _T("低电平有效"));
			}
		}
	}
	*pResult = 0;
}