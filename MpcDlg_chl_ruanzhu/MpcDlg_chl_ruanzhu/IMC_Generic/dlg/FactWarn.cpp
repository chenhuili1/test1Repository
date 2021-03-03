// dlg/FactWarn.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "FactWarn.h"

#include "FactWarnEdit.h"

// CFactWarn 对话框

IMPLEMENT_DYNAMIC(CFactWarn, CDialog)

CFactWarn::CFactWarn(CWnd* pParent /*=NULL*/)
	: CDialog(CFactWarn::IDD, pParent)
{
	m_listFont = NULL;
	m_row = -1;
}

CFactWarn::~CFactWarn()
{
	if(m_listFont) delete m_listFont;
}

void CFactWarn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listctr1);
}


BEGIN_MESSAGE_MAP(CFactWarn, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CFactWarn::OnNMClickList1)
	ON_MESSAGE(WM_MY_WARNEDIT_SHOW, &CFactWarn::EditWarnDlg)
	ON_BN_CLICKED(IDC_BUTTON1, &CFactWarn::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CFactWarn::OnBnClickedButton2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CFactWarn::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON3, &CFactWarn::OnBnClickedButton3)
END_MESSAGE_MAP()


// CFactWarn 消息处理程序


BOOL CFactWarn::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitListCtrl();
	UpdateCtr();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CFactWarn::InitListCtrl()
{
	//通过GetWindowLong来获取CListCtrl已有的样式
	int i=0;
	DWORD dwStyle = GetWindowLong(m_listctr1.m_hWnd, GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;   //清除显示方式位 
	dwStyle|= LVS_REPORT; //LVS_LIST;//设置报表风格
	dwStyle|= LVS_SHOWSELALWAYS | LVS_SINGLESEL; ///始终高亮被选中的表项
	//在原有样式的基本上，添加LVS_REPORT扩展样式
	SetWindowLong(m_listctr1.m_hWnd, GWL_STYLE, dwStyle);
	//获取已有的扩展样式
	DWORD dwStyles = m_listctr1.GetExStyle();
	//取消复选框样式
	dwStyles &= ~LVS_EX_CHECKBOXES;
	dwStyles   |=LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES/*  | LVS_EX_CHECKBOXES */;
	//添加整行选择和表格线扩展样式
	m_listctr1.SetExtendedStyle(dwStyles);

	if(m_listFont == NULL){//
		m_listFont = MyGetFonts(18,_T("宋体"), FW_NORMAL);//创建字体
	}
	m_listctr1.SetFont(m_listFont, TRUE);//设置字体改变行高*/
	//设置列
	LVCOLUMN col;      
	col.mask = LVCF_FMT; 
	CRect rc;

	m_listctr1.GetClientRect(&rc);
	int width = rc.Width() - 18;
	m_listctr1.InsertColumn(0, _T("名称"),LVCFMT_CENTER,width/5);
	m_listctr1.InsertColumn(1, _T("警告语"),LVCFMT_LEFT,width*4/5); 
	col.fmt = LVCFMT_CENTER; 
	m_listctr1.SetColumn(0, &col);
}
void CFactWarn::UpdateCtr()
{
	FACT_WARN* pdata;
	int i;
	if(g_warnNum < 1) return;
	for(i=0; i<g_warnNum; i++)
	{
		pdata = new FACT_WARN;
		memcpy(pdata, g_warn+i, sizeof(FACT_WARN));
		m_listctr1.InsertItem(i, _T(""));
		UpdataListItem(i, pdata);
		m_listctr1.SetItemData(i, (DWORD_PTR)pdata);
	}
}
void CFactWarn::UpdataListItem(int item, FACT_WARN* pdata)
{
	CString str;
	str.Format(_T("%s"),  pdata->name);
	m_listctr1.SetItemText(item, 0, str);
	str.Format(_T("%s"),  pdata->warn);
	m_listctr1.SetItemText(item, 1, str);
}

BOOL CFactWarn::GetCfg()
{
	FACT_WARN * pdata;
	int cnt = m_listctr1.GetItemCount();
	if(cnt != g_warnNum)
		delete [] g_warn;
	g_warn = NULL;
	g_warnNum = cnt;
	if(cnt < 1) return TRUE;
	g_warn = new FACT_WARN[g_warnNum];
	for(int i=0; i<g_warnNum; i++)
	{
		pdata = (FACT_WARN*)m_listctr1.GetItemData(i);
		memcpy(g_warn + i, pdata, sizeof(FACT_WARN));
	}

	return TRUE;
}
void CFactWarn::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_row = phdr->iItem;
	if(m_row < 0){
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	}else{
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	}

	*pResult = 0;
}
void CFactWarn::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_row = phdr->iItem;
	if(phdr->iItem >= 0){
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
		PostMessage(WM_MY_WARNEDIT_SHOW, (WPARAM)phdr->iItem, (LPARAM)0);//通知主框架更新
	}else{
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	}
	*pResult = 0;
}

LRESULT CFactWarn::EditWarnDlg(WPARAM wparam,LPARAM lparam)
{
	int row = (int)wparam;
	FACT_WARN* pdata;
	CFactWarnEdit dlg;

	pdata = (FACT_WARN*)m_listctr1.GetItemData(row);
	dlg.SetWarnInfo(pdata);
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		dlg.GetWarnInfo(pdata);
		UpdataListItem(row, pdata);
	}
	return 0;
}
//新增
void CFactWarn::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	FACT_WARN* pdata;
	int cnt = m_listctr1.GetItemCount();
	pdata = new FACT_WARN;
	memset(pdata, 0, sizeof(FACT_WARN));
	m_listctr1.InsertItem(cnt, _T(""));
	m_listctr1.SetItemData(cnt, (DWORD_PTR)pdata);
	if(m_row > 0){
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	}
	PostMessage(WM_MY_WARNEDIT_SHOW, (WPARAM)cnt, (LPARAM)0);//通知主框架更新
}
//删除
void CFactWarn::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	FACT_WARN* pdata;
	if(m_row < 0)
		return;
	pdata = (FACT_WARN*)m_listctr1.GetItemData(m_row);
	if(pdata) delete pdata;
	m_listctr1.DeleteItem(m_row);
	int cnt = m_listctr1.GetItemCount();
	if(cnt <= m_row){
		m_listctr1.SetItemState(m_row, 0, -1);
		m_row --;
		if(m_row > 0)
			m_listctr1.SetItemState(m_row,LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED|LVIS_DROPHILITED);
	}
	if(m_row < 0){
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	}
}
//修改
void CFactWarn::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	PostMessage(WM_MY_WARNEDIT_SHOW, (WPARAM)m_row, (LPARAM)0);//通知主框架更新
}
