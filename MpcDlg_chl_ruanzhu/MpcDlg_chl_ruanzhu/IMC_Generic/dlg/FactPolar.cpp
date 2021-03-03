// dlg/FactPolar.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "FactPolar.h"


// CFactPolar �Ի���

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


// CFactPolar ��Ϣ�������

BOOL CFactPolar::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitListCtrl();
	UpdateCtr();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CFactPolar::InitListCtrl()
{
	//ͨ��GetWindowLong����ȡCListCtrl���е���ʽ
	int i=0;
	DWORD dwStyle = GetWindowLong(m_listctr2.m_hWnd, GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;   //�����ʾ��ʽλ 
	dwStyle|= LVS_REPORT; //LVS_LIST;//���ñ�����
	dwStyle|= LVS_SHOWSELALWAYS | LVS_SINGLESEL; ///ʼ�ո�����ѡ�еı���
	//��ԭ����ʽ�Ļ����ϣ����LVS_REPORT��չ��ʽ
//	SetWindowLong(m_listctr1.m_hWnd, GWL_STYLE, dwStyle);
	SetWindowLong(m_listctr2.m_hWnd, GWL_STYLE, dwStyle);
	//��ȡ���е���չ��ʽ
	DWORD dwStyles = m_listctr2.GetExStyle();
	//ȡ����ѡ����ʽ
	dwStyles &= ~LVS_EX_CHECKBOXES;
	dwStyles   |=LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES/*  | LVS_EX_CHECKBOXES */;
	//�������ѡ��ͱ������չ��ʽ
//	m_listctr1.SetExtendedStyle(dwStyles);
	m_listctr2.SetExtendedStyle(dwStyles);

	if(m_listFont == NULL){//
		m_listFont = MyGetFonts(18,_T("����"), FW_NORMAL);//��������
	}
//	m_listctr1.SetFont(m_listFont, TRUE);//��������ı��и�*/
	m_listctr2.SetFont(m_listFont, TRUE);//��������ı��и�*/
	//������
	LVCOLUMN col;      
	col.mask = LVCF_FMT; 
	CRect rc;
/*
	m_listctr1.GetClientRect(&rc);
	int width = rc.Width() - 18;
	m_listctr1.InsertColumn(0, _T("����˿�"),LVCFMT_CENTER,width*3/5);
	m_listctr1.InsertColumn(1, _T("����"),LVCFMT_LEFT,width*2/5); 
	col.fmt = LVCFMT_CENTER; 
	m_listctr1.SetColumn(0, &col);
*/
	m_listctr2.GetClientRect(&rc);
	int width = rc.Width() - 18;
	m_listctr2.InsertColumn(0, _T("����˿�"),LVCFMT_CENTER,width*3/5);
	m_listctr2.InsertColumn(1, _T("����"),LVCFMT_LEFT,width*2/5); 
	col.fmt = LVCFMT_CENTER; 
	m_listctr2.SetColumn(0, &col);
/*
	CString str;
	for(i=0; i<INPUT_NUM; i++)
	{
		m_listctr1.InsertItem(i, _T(""));
		str.Format(_T("����˿� %d"),  i+1);
		m_listctr1.SetItemText(i, 0, str);
	}*/
	m_listctr2.InsertItem(0, _T(""));
	m_listctr2.SetItemText(0, 0, _T("��ͣ����˿�"));
	
}

void CFactPolar::UpdateCtr()
{
	CString str;
	int i, k;
	memcpy(&m_polar, &g_polar, sizeof(FACT_POLAR));
/*	for(i=0; i<INPUT_NUM; i++)
	{
		if(m_polar.gin[i])
			m_listctr1.SetItemText(i, 1, _T("�ߵ�ƽ��Ч"));
		else
			m_listctr1.SetItemText(i, 1, _T("�͵�ƽ��Ч"));
	}
*/
	m_listctr2.DeleteAllItems();
	m_listctr2.InsertItem(0, _T(""));
	m_listctr2.SetItemText(0, 0, _T("��ͣ����˿�"));
	if(m_polar.stopin)
		m_listctr2.SetItemText(0, 1, _T("�ߵ�ƽ��Ч"));
	else
		m_listctr2.SetItemText(0, 1, _T("�͵�ƽ��Ч"));
	k = 1;
	for(i=0; i<g_Naxis; i++)
	{
		m_listctr2.InsertItem(k, _T(""));
		str.Format(_T("%s����λ"),  g_AxisName[i]);
		m_listctr2.SetItemText(k, 0, str);
		if(m_polar.aioP[i])
			m_listctr2.SetItemText(k, 1, _T("�ߵ�ƽ��Ч"));
		else
			m_listctr2.SetItemText(k, 1, _T("�͵�ƽ��Ч"));
		k++;

		m_listctr2.InsertItem(k, _T(""));
		str.Format(_T("%s����λ"),  g_AxisName[i]);
		m_listctr2.SetItemText(k, 0, str);
		if(m_polar.aioN[i])
			m_listctr2.SetItemText(k, 1, _T("�ߵ�ƽ��Ч"));
		else
			m_listctr2.SetItemText(k, 1, _T("�͵�ƽ��Ч"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(phdr->iItem >= 0 && phdr->iItem < INPUT_NUM){
		if(phdr->iButton == 1){
			m_polar.gin[phdr->iItem] = !m_polar.gin[phdr->iItem];
			if(m_polar.gin[phdr->iItem])
				m_listctr1.SetItemText(phdr->iItem, 1, _T("�ߵ�ƽ��Ч"));
			else
				m_listctr1.SetItemText(phdr->iItem, 1, _T("�͵�ƽ��Ч"));
		}
	}
	*pResult = 0;
}
void CFactPolar::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(phdr->iItem == 0){
		if(phdr->iButton == 1){
			m_polar.stopin = !m_polar.stopin;
			if(m_polar.stopin)
				m_listctr2.SetItemText(phdr->iItem, 1, _T("�ߵ�ƽ��Ч"));
			else
				m_listctr2.SetItemText(phdr->iItem, 1, _T("�͵�ƽ��Ч"));
		}
	}
	else if(phdr->iItem > 0 && phdr->iItem <= 2*g_Naxis){
		if(phdr->iButton == 1){
			int index = (phdr->iItem - 1)/2;	//�ڼ���
			if(phdr->iItem%2 == 1){
				m_polar.aioP[index] = !m_polar.aioP[index];
				if(m_polar.aioP[index])
					m_listctr2.SetItemText(phdr->iItem, 1, _T("�ߵ�ƽ��Ч"));
				else
					m_listctr2.SetItemText(phdr->iItem, 1, _T("�͵�ƽ��Ч"));
			}else{
				m_polar.aioN[index] = !m_polar.aioN[index];
				if(m_polar.aioN[index])
					m_listctr2.SetItemText(phdr->iItem, 1, _T("�ߵ�ƽ��Ч"));
				else
					m_listctr2.SetItemText(phdr->iItem, 1, _T("�͵�ƽ��Ч"));
			}
		}
	}
	*pResult = 0;
}