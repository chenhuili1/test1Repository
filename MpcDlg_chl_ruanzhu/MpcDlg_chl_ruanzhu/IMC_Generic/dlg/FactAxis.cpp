// dlg/FactAxis.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "FactAxis.h"

#include "IMC_GenericDlg.h"

// CFactAxis �Ի���

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


// CFactAxis ��Ϣ�������


BOOL CFactAxis::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitListCtrl();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CFactAxis::InitListCtrl()
{
	//ͨ��GetWindowLong����ȡCListCtrl���е���ʽ
	int i=0;
	DWORD dwStyle = GetWindowLong(m_listctr.m_hWnd, GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;   //�����ʾ��ʽλ 
	dwStyle|= LVS_REPORT; //LVS_LIST;//���ñ�����
	dwStyle|= LVS_SHOWSELALWAYS | LVS_SINGLESEL; ///ʼ�ո�����ѡ�еı���
	//��ԭ����ʽ�Ļ����ϣ����LVS_REPORT��չ��ʽ
	SetWindowLong(m_listctr.m_hWnd, GWL_STYLE, dwStyle);
	//��ȡ���е���չ��ʽ
	DWORD dwStyles = m_listctr.GetExStyle();
	//ȡ����ѡ����ʽ
	dwStyles &= ~LVS_EX_CHECKBOXES;
	dwStyles   |=LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES/*  | LVS_EX_CHECKBOXES */;
	//�������ѡ��ͱ������չ��ʽ
	m_listctr.SetExtendedStyle(dwStyles);

	if(m_listFont == NULL){//
		m_listFont = MyGetFonts(18,_T("����"), FW_NORMAL);//��������
	}
	m_listctr.SetFont(m_listFont, TRUE);//��������ı��и�*/
	m_listEdit.SetFont(m_listFont, TRUE);
	//������
	CRect rc;
	m_listctr.GetClientRect(&rc);
	int width = rc.Width() - 18;
	m_listctr.InsertColumn(0, _T("���"),LVCFMT_LEFT,width/11);
	m_listctr.InsertColumn(1, _T("λ������"),LVCFMT_LEFT,width*2/11);
	m_listctr.InsertColumn(2, _T("�ƶ���λ"),LVCFMT_LEFT,width*2/11);
	m_listctr.InsertColumn(3, _T("������"),LVCFMT_LEFT,width*2/11);
//	m_listctr.InsertColumn(4, _T("�ŷ�����"),LVCFMT_LEFT,width*2/13);
	m_listctr.InsertColumn(4, _T("�ⲿ����"),LVCFMT_LEFT,width*2/11);
	m_listctr.InsertColumn(5, _T("��������"),LVCFMT_LEFT,width*2/11);

//	m_listctr.SetBkColor(MY_COLOR_BACKGROUND_1);        //���ñ���ɫ
//	m_listctr.SetTextBkColor(MY_COLOR_BACKGROUND_1);        //���ñ���ɫ
//	m_listctr.SetTextColor(MY_COLOR_WHITE);        //���ñ���ɫ

}

WCHAR boxName[2][8] = {_T("��ʹ��"), _T("����")};
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
			MessageBox(_T("λ�Ƶ�λ�ĳ��Ȳ��ܳ���6���ַ���"));			
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ����ר�ô����/����û���
#if defined(WINCE)
	if(pMsg->message==WM_KEYDOWN || pMsg->message==WM_KEYUP )
	{ 	
		if(pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return TRUE;
	}
#endif
	return CDialog::PreTranslateMessage(pMsg);
}
//�ƶ�Edit
void CFactAxis::MoveEdit(int row, int lie)
{
	CRect rect,rc;
	CString str;
	if(row < 0) return;
	m_row = row;
	m_lie = lie;
	m_listctr.GetWindowRect(&rc);
	ScreenToClient(&rc);
	m_listctr.GetSubItemRect(row, lie, LVIR_LABEL,rect);//�õ��õ�Ԫ����ε�λ�ô�С��Ϣ��
	rect.OffsetRect(rc.left+2, rc.top+1);

	str = m_listctr.GetItemText(row, lie);				//��ȡ�õ�Ԫ���Ѵ��ڵ��ı����ݡ�
//	rect.top -= 1;
	m_listEdit.MoveWindow(rect);
	m_listEdit.SetWindowText(str);	
	m_listEdit.ShowWindow(SW_SHOW);	
	m_listEdit.SetSel(0,-1);						//ȫѡ�༭������ݡ�
	m_listEdit.SetFocus();
}
//����Edit
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HideEdit();
}


void CFactAxis::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialog::OnWindowPosChanged(lpwndpos);

	// TODO: �ڴ˴������Ϣ����������
	if (lpwndpos->flags & SWP_SHOWWINDOW){ //�Ի�����ʾ 
		UpdateCtr();
	}else if(lpwndpos->flags & SWP_HIDEWINDOW) //�Ի�������  
	{
//		KillTimer(TIMER_MANUAL_TIMING);
	}
}
