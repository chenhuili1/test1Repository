// dlg/FactAxis.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "FactAxis.h"

#include "IMC_GenericDlg.h"

// CFactAxis 对话框

IMPLEMENT_DYNAMIC(CFactAxis, CDialog)

CFactAxis::CFactAxis(CWnd* pParent /*=NULL*/)
	: CDialog(CFactAxis::IDD, pParent)
{
	m_isInit = FALSE;
	m_listFont = NULL;
}

CFactAxis::~CFactAxis()
{
	if(m_listFont) delete m_listFont;
}

void CFactAxis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listctr);
	DDX_Control(pDX, IDC_EDIT_UNIT_0, m_listEdit);
//	DDX_Control(pDX, IDC_COMBO1, m_listbox);
	DDX_Control(pDX, IDC_EDIT_NAXIS, m_edit);
}


BEGIN_MESSAGE_MAP(CFactAxis, CDialog)
	ON_EN_CHANGE(IDC_EDIT_NAXIS, &CFactAxis::OnEnChangeEditNaxis)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CFactAxis::OnNMClickList1)
	ON_EN_KILLFOCUS(IDC_EDIT_UNIT_0, &CFactAxis::OnEnKillfocusEditUnit0)
//	ON_CBN_SELENDOK(IDC_COMBO1, &CFactAxis::OnCbnSelendokCombo1)
	ON_WM_WINDOWPOSCHANGED()
END_MESSAGE_MAP()


// CFactAxis 消息处理程序


BOOL CFactAxis::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitListCtrl();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CFactAxis::InitListCtrl()
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

	if(m_listFont == NULL){//
		m_listFont = MyGetFonts(18,_T("宋体"), FW_NORMAL);//创建字体
	}
	m_listctr.SetFont(m_listFont, TRUE);//设置字体改变行高*/
	m_listEdit.SetFont(m_listFont, TRUE);
	//设置列
	CRect rc;
	m_listctr.GetClientRect(&rc);
	int width = rc.Width() - 18;
	m_listctr.InsertColumn(0, _T("轴号"),LVCFMT_LEFT,width/11);
	m_listctr.InsertColumn(1, _T("位移因子"),LVCFMT_LEFT,width*2/11);
	m_listctr.InsertColumn(2, _T("移动单位"),LVCFMT_LEFT,width*2/11);
	m_listctr.InsertColumn(3, _T("脉冲宽度"),LVCFMT_LEFT,width*2/11);
//	m_listctr.InsertColumn(4, _T("伺服报警"),LVCFMT_LEFT,width*2/13);
	m_listctr.InsertColumn(4, _T("外部反馈"),LVCFMT_LEFT,width*2/11);
	m_listctr.InsertColumn(5, _T("反馈倍率"),LVCFMT_LEFT,width*2/11);

//	m_listctr.SetBkColor(MY_COLOR_BACKGROUND_1);        //设置背景色
//	m_listctr.SetTextBkColor(MY_COLOR_BACKGROUND_1);        //设置背景色
//	m_listctr.SetTextColor(MY_COLOR_WHITE);        //设置背景色

}

WCHAR boxName[2][8] = {_T("不使用"), _T("启用")};
void CFactAxis::UpdateCtr(BOOL isUpAxis)
{
	int i;
	CString str;
	if(isUpAxis)
		SetDlgItemInt(IDC_EDIT_NAXIS, g_factcfg.Naxis);
	m_listctr.DeleteAllItems();
	for(i=0; i<g_Naxis; i++){
		m_listctr.InsertItem(i, _T(""));
		m_listctr.SetItemText(i, 0, g_AxisName[i]);
		str.Format(_T("%0.2lf"), g_factcfg.distFac[i]);
		m_listctr.SetItemText(i, 1, str);
		m_listctr.SetItemText(i, 2, g_factcfg.Unit[i]);
		str.Format(_T("%0.2lf"), 15.26*g_factcfg.steptime[i] / 1000.0);
		m_listctr.SetItemText(i, 3, str);
	//	m_listctr.SetItemText(i, 4, boxName[g_factcfg.Alm[i]]);
		m_listctr.SetItemText(i, 4, boxName[g_factcfg.encpctr[i]]);
		str.Format(_T("%0.2lf"), g_factcfg.encpfac[i]);
		m_listctr.SetItemText(i, 5, str);

	}
}

double CFactAxis::GetListFloat(int row, int lie)
{
	WCHAR data[16];
	double dval;
	int len = m_listctr.GetItemText(row, lie, data, 15);
	if(len == 0) return 0;
	data[len] = 0;
	swscanf(data, _T("%lf"),&dval);
	return dval;
}

BOOL CFactAxis::GetCfg()
{
	int i, len;
	WCHAR Unit[16];
	CString str;

	HideEdit();

	for(i=0; i<g_Naxis; i++){
		len = m_listctr.GetItemText(i, 2, Unit, 15);
		if(len >6){
			MessageBox(_T("位移单位的长度不能超过6个字符！"));			
			return FALSE;
		}
		Unit[len] = 0;
		memcpy(g_factcfg.Unit[i], Unit, (len +1)*sizeof(WCHAR));
	}
	for(i=0; i<g_Naxis; i++){
		g_factcfg.distFac[i] = GetListFloat(i, 1);
		g_factcfg.g_mapAxis[i] = i;
		g_factcfg.steptime[i] = GetListFloat(i, 3) * 1000/15.26;
	//	str = m_listctr.GetItemText(i,4);
	//	g_factcfg.Alm[i] = m_listbox.SelectString(0, str);
		str = m_listctr.GetItemText(i, 4);
//		g_factcfg.encpctr[i] = m_listbox.SelectString(0, str);
		g_factcfg.encpfac[i] = GetListFloat(i, 5);
	}
	return TRUE;
}



void CFactAxis::OnEnChangeEditNaxis()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	int Naxis = GetDlgItemInt(IDC_EDIT_NAXIS);
	if(Naxis < 2) return;
	if(Naxis > MAX_NAXIS || Naxis%2){
		SetDlgItemInt(IDC_EDIT_NAXIS, g_factcfg.Naxis);
		return;
	}
	g_factcfg.Naxis = Naxis;
	g_Naxis = g_factcfg.Naxis;
	UpdateCtr(FALSE);
}

BOOL CFactAxis::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
#if defined(WINCE)
	if(pMsg->message==WM_KEYDOWN || pMsg->message==WM_KEYUP )
	{ 	
		if(pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return TRUE;
	}
#endif
	return CDialog::PreTranslateMessage(pMsg);
}
//移动Edit
void CFactAxis::MoveEdit(int row, int lie)
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
	m_listEdit.MoveWindow(rect);
	m_listEdit.SetWindowText(str);	
	m_listEdit.ShowWindow(SW_SHOW);	
	m_listEdit.SetSel(0,-1);						//全选编辑框的内容。
	m_listEdit.SetFocus();
}
//隐藏Edit
BOOL CFactAxis::HideEdit()
{
	if(!m_listEdit.IsWindowVisible()) return TRUE;
	CString str;
	m_listEdit.GetWindowText(str);
	m_listctr.SetItemText(m_row, m_lie, str);
	m_listEdit.ShowWindow(SW_HIDE);	
		
	return TRUE;
}
void CFactAxis::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	HideEdit();
//	HideBox();
	if(phdr->iItem >= 0){
		if((phdr->iButton > 0 && phdr->iButton < 4) || 
			phdr->iButton == 5){
			m_row = phdr->iItem;
			MoveEdit(m_row, phdr->iButton);
		}else
		if(phdr->iButton == 4){
			m_row = phdr->iItem;
		//	MoveBox(m_row, phdr->iButton);
			g_factcfg.encpctr[m_row] = !g_factcfg.encpctr[m_row];
			m_listctr.SetItemText(m_row, phdr->iButton, boxName[g_factcfg.encpctr[m_row]]);
		}
	}
	*pResult = 0;
}


void CFactAxis::OnEnKillfocusEditUnit0()
{
	// TODO: 在此添加控件通知处理程序代码
	HideEdit();
}


void CFactAxis::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialog::OnWindowPosChanged(lpwndpos);

	// TODO: 在此处添加消息处理程序代码
	if (lpwndpos->flags & SWP_SHOWWINDOW){ //对话框显示 
		UpdateCtr();
	}else if(lpwndpos->flags & SWP_HIDEWINDOW) //对话框隐藏  
	{
//		KillTimer(TIMER_MANUAL_TIMING);
	}
}
