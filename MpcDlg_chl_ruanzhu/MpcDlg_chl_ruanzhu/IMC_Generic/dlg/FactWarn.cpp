// dlg/FactWarn.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "FactWarn.h"

#include "FactWarnEdit.h"

// CFactWarn �Ի���

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


// CFactWarn ��Ϣ�������


BOOL CFactWarn::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitListCtrl();
	UpdateCtr();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CFactWarn::InitListCtrl()
{
	//ͨ��GetWindowLong����ȡCListCtrl���е���ʽ
	int i=0;
	DWORD dwStyle = GetWindowLong(m_listctr1.m_hWnd, GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;   //�����ʾ��ʽλ 
	dwStyle|= LVS_REPORT; //LVS_LIST;//���ñ�����
	dwStyle|= LVS_SHOWSELALWAYS | LVS_SINGLESEL; ///ʼ�ո�����ѡ�еı���
	//��ԭ����ʽ�Ļ����ϣ����LVS_REPORT��չ��ʽ
	SetWindowLong(m_listctr1.m_hWnd, GWL_STYLE, dwStyle);
	//��ȡ���е���չ��ʽ
	DWORD dwStyles = m_listctr1.GetExStyle();
	//ȡ����ѡ����ʽ
	dwStyles &= ~LVS_EX_CHECKBOXES;
	dwStyles   |=LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES/*  | LVS_EX_CHECKBOXES */;
	//�������ѡ��ͱ������չ��ʽ
	m_listctr1.SetExtendedStyle(dwStyles);

	if(m_listFont == NULL){//
		m_listFont = MyGetFonts(18,_T("����"), FW_NORMAL);//��������
	}
	m_listctr1.SetFont(m_listFont, TRUE);//��������ı��и�*/
	//������
	LVCOLUMN col;      
	col.mask = LVCF_FMT; 
	CRect rc;

	m_listctr1.GetClientRect(&rc);
	int width = rc.Width() - 18;
	m_listctr1.InsertColumn(0, _T("����"),LVCFMT_CENTER,width/5);
	m_listctr1.InsertColumn(1, _T("������"),LVCFMT_LEFT,width*4/5); 
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_row = phdr->iItem;
	if(phdr->iItem >= 0){
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
		PostMessage(WM_MY_WARNEDIT_SHOW, (WPARAM)phdr->iItem, (LPARAM)0);//֪ͨ����ܸ���
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
//����
void CFactWarn::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	PostMessage(WM_MY_WARNEDIT_SHOW, (WPARAM)cnt, (LPARAM)0);//֪ͨ����ܸ���
}
//ɾ��
void CFactWarn::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
//�޸�
void CFactWarn::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	PostMessage(WM_MY_WARNEDIT_SHOW, (WPARAM)m_row, (LPARAM)0);//֪ͨ����ܸ���
}
