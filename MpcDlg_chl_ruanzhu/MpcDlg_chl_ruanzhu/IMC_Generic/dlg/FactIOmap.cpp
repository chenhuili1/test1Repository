// dlg/FactIOmap.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "FactIOmap.h"


// CFactIOmap �Ի���

IMPLEMENT_DYNAMIC(CFactIOmap, CDialog)

CFactIOmap::CFactIOmap(CWnd* pParent /*=NULL*/)
	: CDialog(CFactIOmap::IDD, pParent)
{
	m_listFont = NULL;

}

CFactIOmap::~CFactIOmap()
{
	delete m_listFont;
}

void CFactIOmap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listctr1);
	DDX_Control(pDX, IDC_LIST2, m_listctr2);
	DDX_Control(pDX, IDC_COMBO1, m_listbox1);
	DDX_Control(pDX, IDC_COMBO2, m_listbox2);
}


BEGIN_MESSAGE_MAP(CFactIOmap, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CFactIOmap::OnNMClickList2)
	ON_CBN_SELENDOK(IDC_COMBO1, &CFactIOmap::OnCbnSelendokCombo1)
	ON_CBN_SELENDOK(IDC_COMBO2, &CFactIOmap::OnCbnSelendokCombo2)
END_MESSAGE_MAP()


// CFactIOmap ��Ϣ�������

BOOL CFactIOmap::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitListCtrl();
	UpdateCtr();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

#define BUTTON_LIST_ID		4
#define HW_LIST_AXIS_ID		12
#define HW_LIST_OTHER_ID		(HW_LIST_AXIS_ID-4)
void CFactIOmap::InitListCtrl()
{
	//ͨ��GetWindowLong����ȡCListCtrl���е���ʽ
	int i=0, id;
	DWORD dwStyle = GetWindowLong(m_listctr1.m_hWnd, GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;   //�����ʾ��ʽλ 
	dwStyle|= LVS_REPORT; //LVS_LIST;//���ñ�����
	dwStyle|= LVS_SHOWSELALWAYS | LVS_SINGLESEL; ///ʼ�ո�����ѡ�еı���
	//��ԭ����ʽ�Ļ����ϣ����LVS_REPORT��չ��ʽ
	SetWindowLong(m_listctr1.m_hWnd, GWL_STYLE, dwStyle);
	SetWindowLong(m_listctr2.m_hWnd, GWL_STYLE, dwStyle);
	//��ȡ���е���չ��ʽ
	DWORD dwStyles = m_listctr1.GetExStyle();
	//ȡ����ѡ����ʽ
	dwStyles &= ~LVS_EX_CHECKBOXES;
	dwStyles   |=LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES/*  | LVS_EX_CHECKBOXES */;
	//�������ѡ��ͱ������չ��ʽ
	m_listctr1.SetExtendedStyle(dwStyles);
	m_listctr2.SetExtendedStyle(dwStyles);

	if(m_listFont == NULL){//
		m_listFont = MyGetFonts(18,_T("����"), FW_NORMAL);//��������
	}
	m_listctr1.SetFont(m_listFont, TRUE);//��������ı��и�*/
	m_listctr2.SetFont(m_listFont, TRUE);//��������ı��и�*/
	m_listbox1.SetFont(m_listFont, TRUE);
	m_listbox2.SetFont(m_listFont, TRUE);
	//������
	LVCOLUMN col;      
	col.mask = LVCF_FMT; 
	CRect rc;

	m_listctr1.GetClientRect(&rc);
	int width = rc.Width() - 18;
	m_listctr1.InsertColumn(0, _T("�˿ں�"),LVCFMT_CENTER,width*2/5-30);
	m_listctr1.InsertColumn(1, _T("���ƿ����������"),LVCFMT_LEFT,width*3/5+30); 
	col.fmt = LVCFMT_CENTER; 
	m_listctr1.SetColumn(0, &col);

	m_listctr2.GetClientRect(&rc);
	width = rc.Width() - 18;
	m_listctr2.InsertColumn(0, _T("����"),LVCFMT_LEFT,width*5/9+20);
	m_listctr2.InsertColumn(1, _T("���������"),LVCFMT_LEFT,width*4/9-20);
	col.fmt = LVCFMT_RIGHT; 
	m_listctr2.SetColumn(0, &col);

	CString str;
	m_listctr1.InsertItem(0, _T(""));
	m_listctr1.SetItemText(0, 0, _T("�����"));
	for(i=1; i<=INPUT_NUM; i++)
	{
		m_listctr1.InsertItem(i, _T(""));
		str.Format(_T("%d"), i);
		m_listctr1.SetItemText(i, 0, str);
		if(i<17)
			str.Format(_T("Gin1��������IN%d"),  i-1);
		else
			str.Format(_T("Gin2��������IN%d"), i - 17);
		m_listctr1.SetItemText(i, 1, str);
	}
	m_listctr1.InsertItem(i, _T(""));
	m_listctr1.SetItemText(i, 0, _T("�����"));
	m_listctr1.SetItemText(i, 1, _T("��Ӧ�������"));
	for(i=1; i<=OUTPUT_NUM; i++)
	{
		m_listctr1.InsertItem(i+INPUT_NUM+1, _T(""));
		str.Format(_T("%d"), i);
		m_listctr1.SetItemText(i+INPUT_NUM+1, 0, str);
		if(i<17)
			str.Format(_T("Gout1��������OUT%d"), i-1);
		else
			str.Format(_T("Gout2��������OUT%d"), i - 17);
		m_listctr1.SetItemText(i+INPUT_NUM+1, 1, str);
	}
	m_listctr2.InsertItem(0, _T(""));
	m_listctr2.SetItemText(0, 0, _T("���ӳ������˿�"));
	m_listctr2.InsertItem(1, _T(""));
	m_listctr2.SetItemText(1, 0, _T("�̵�ӳ������˿�"));
	m_listctr2.InsertItem(2, _T(""));
	m_listctr2.SetItemText(2, 0, _T("�Ƶ�ӳ������˿�"));
	m_listctr2.InsertItem(3, _T(""));
	m_listctr2.InsertItem(4, _T(""));
	m_listctr2.SetItemText(4, 0, _T("������ťӳ������˿�"));
	m_listctr2.InsertItem(5, _T(""));
	m_listctr2.SetItemText(5, 0, _T("��ͣ��ťӳ������˿�"));
	m_listctr2.InsertItem(6, _T(""));
	m_listctr2.SetItemText(6, 0, _T("��ͣ��ťӳ������˿�"));
	m_listctr2.InsertItem(7, _T(""));
	m_listctr2.SetItemText(7, 0, _T("��λ��ťӳ������˿�"));
	m_listctr2.InsertItem(8, _T(""));
	m_listctr2.SetItemText(8, 0, _T("���ֱ���1����˿�"));
	m_listctr2.InsertItem(9, _T(""));
	m_listctr2.SetItemText(9, 0, _T("���ֱ���10����˿�"));
	m_listctr2.InsertItem(10, _T(""));
	m_listctr2.SetItemText(10, 0, _T("���ֱ���100����˿�"));
	m_listctr2.InsertItem(11, _T(""));
	m_listctr2.SetItemText(11, 0, _T("����ȷ������˿�"));
	for(i=0; i<g_Naxis; i++)
	{
		id = HW_LIST_AXIS_ID + i;
		m_listctr2.InsertItem(id, _T(""));
		str.Format(_T("����%s����˿�"), g_AxisName[i]);
		m_listctr2.SetItemText(id, 0, str);
	}
	id++;
	m_listctr2.InsertItem(id, _T(""));
	for(i=0; i<g_Naxis; i++)
	{
		id++;
		m_listctr2.InsertItem(id, _T(""));
		str.Format(_T("�㶯%s����ť"), g_AxisName[i]);
		m_listctr2.SetItemText(id, 0, str);
		str.Format(_T("�㶯%s����ť"), g_AxisName[i]);
		m_listctr2.SetItemText(id, 0, str);
	}


	m_listbox1.AddString(_T("��"));
	for(i=1; i<=OUTPUT_NUM; i++){
		str.Format(_T("����˿�%d"), i);
		m_listbox1.AddString(str);
	}
	m_listbox2.AddString(_T("��"));
	for(i=1; i<=INPUT_NUM; i++){
		str.Format(_T("����˿�%d"), i);
		m_listbox2.AddString(str);
	}
}

void CFactIOmap::UpdateCtr()
{
	CString str;
	int i, id, n;
	n = 0;
	for(int i=0; i<LED_NUM; i++, n++)
	{
		if(g_iomap.mapLed[i].bit < (OUTPUT_NUM+1) && g_iomap.mapLed[i].bit > 0)
			str.Format(_T("����˿�%d"), g_iomap.mapLed[i].bit);
		else
			str = _T("��");
		m_listctr2.SetItemText(n, 1, str);
	}
	n++;//��һ������
	for(int i=0; i<KEY_NUM; i++, n++)
	{
		if(g_iomap.mapKey[i].bit < (INPUT_NUM+1) && g_iomap.mapKey[i].bit > 0)
			str.Format(_T("����˿�%d"), g_iomap.mapKey[i].bit);
		else
			str = _T("��");
		m_listctr2.SetItemText(n, 1, str);
	}
	//******************************
	BOOL isok;
	do{//ɾ������ģ�Ȼ��������
		isok = m_listctr2.DeleteItem(HW_LIST_AXIS_ID);
	}while(isok);
	id = HW_LIST_AXIS_ID;
	for(i=0; i<g_Naxis; i++, id++)
	{
		m_listctr2.InsertItem(id, _T(""));
		str.Format(_T("����%s����˿�"), g_AxisName[i]);
		m_listctr2.SetItemText(id, 0, str);
	}
	m_listctr2.InsertItem(id, _T(""));//����һ������
	for(i=0; i<g_Naxis; i++)
	{
		id++;
		m_listctr2.InsertItem(id, _T(""));
		str.Format(_T("�㶯%s����ť"), g_AxisName[i]);
		m_listctr2.SetItemText(id, 0, str);
		id++;
		m_listctr2.InsertItem(id, _T(""));
		str.Format(_T("�㶯%s����ť"), g_AxisName[i]);
		m_listctr2.SetItemText(id, 0, str);
	}
	//******************************
	for(i=0; i<g_Naxis+4; i++, n++){
		if(g_iomap.mapHW[i].bit < (INPUT_NUM+1) && g_iomap.mapHW[i].bit > 0)
			str.Format(_T("����˿�%d"), g_iomap.mapHW[i].bit);
		else
			str = _T("��");
		m_listctr2.SetItemText(n, 1, str);
	}
	n ++;
	for(i=0; i<g_Naxis; i++){
		if(g_iomap.mapJogBnZ[i].bit < (INPUT_NUM+1) && g_iomap.mapJogBnZ[i].bit > 0)
			str.Format(_T("����˿�%d"), g_iomap.mapJogBnZ[i].bit);
		else
			str = _T("��");
		m_listctr2.SetItemText(n, 1, str);
		n ++;
		if(g_iomap.mapJogBnF[i].bit < (INPUT_NUM+1) && g_iomap.mapJogBnF[i].bit > 0)
			str.Format(_T("����˿�%d"), g_iomap.mapJogBnF[i].bit);
		else
			str = _T("��");
		m_listctr2.SetItemText(n, 1, str);
		n ++;
	}
}

BOOL CFactIOmap::GetCfg()
{
	int Lbit[LED_NUM];
//	int mapHW[MAX_NAXIS+4];
//	int Kbit[KEY_NUM];
	int Inbit[KEY_NUM+3*MAX_NAXIS+4];
	int i, k, n;
	CString str;
	HideBox();
	n = 0;
	for(i=0; i<LED_NUM; i++, n++)
	{
		str = m_listctr2.GetItemText(n, 1);
		Lbit[i] = m_listbox1.SelectString(0, str);
		if(Lbit[i] == LB_ERR) Lbit[i] = 0;
	}
	n ++;//��һ���ո�
	for(i=0, k=0; i<KEY_NUM; i++, k++, n++)
	{
		str = m_listctr2.GetItemText(n , 1);
		Inbit[k] = m_listbox2.SelectString(0, str);
		if(Inbit[k] == LB_ERR) Inbit[k] = 0;
	}
	for(i=0; i<g_Naxis+4; i++, k++, n++){
		str = m_listctr2.GetItemText(n , 1);
		Inbit[k] = m_listbox2.SelectString(0, str);
		if(Inbit[k] == LB_ERR) Inbit[k] = 0;
	}
	n ++;//��һ���ո�
	for(i=0; i<g_Naxis*2; i++, k++, n++){
		str = m_listctr2.GetItemText(n, 1);
		Inbit[k] = m_listbox2.SelectString(0, str);
		if(Inbit[k] == LB_ERR) Inbit[k] = 0;
	}

	for(i=0; i<k-1; i++){
		for(n=i+1; n<k; n++){
			if(Inbit[i] == 0) continue;
			if(Inbit[i] == Inbit[n]){
				MessageBox(_T("����ѡ����ͬ������˿ڣ�"));
				return FALSE;
			}
		}
	}

	for(i=0; i<LED_NUM-1; i++){
		for(k=i+1; k<LED_NUM; k++){
			if(Lbit[i] == 0) continue;
			if(Lbit[i] == Lbit[k]){
				MessageBox(_T("����ѡ����ͬ������˿ڣ�"));
				return FALSE;
			}
		}
	}
	for(i=0; i<LED_NUM; i++){
		g_iomap.mapLed[i].loc = Lbit[i] > 16 ? gout2Loc : gout1Loc;
		g_iomap.mapLed[i].axis =  0;
		g_iomap.mapLed[i].bit = (BYTE)Lbit[i];
	}
	for(i=0; i<KEY_NUM; i++){
		g_iomap.mapKey[i].loc = Inbit[i] > 16 ? gin2Loc : gin1Loc;
		g_iomap.mapKey[i].axis =  0;
		g_iomap.mapKey[i].bit = (BYTE)Inbit[i];
	}
	n = i;
	for(i=0; i<g_Naxis+4; i++, n++){
		g_iomap.mapHW[i].loc = Inbit[n] > 16 ? gin2Loc : gin1Loc;
		g_iomap.mapHW[i].axis =  0;
		g_iomap.mapHW[i].bit = (BYTE)Inbit[n];
	}
	for(; i<MAX_NAXIS+4; i++){
		g_iomap.mapHW[i].loc = gin1Loc;
		g_iomap.mapHW[i].axis =  0;
		g_iomap.mapHW[i].bit = 0;
	}
	for(i=0; i<g_Naxis; i++, n++){
		g_iomap.mapJogBnZ[i].loc = Inbit[n] > 16 ? gin2Loc : gin1Loc;
		g_iomap.mapJogBnZ[i].axis =  0;
		g_iomap.mapJogBnZ[i].bit = (BYTE)Inbit[n];
		n++;
		g_iomap.mapJogBnF[i].loc = Inbit[n] > 16 ? gin2Loc : gin1Loc;
		g_iomap.mapJogBnF[i].axis =  0;
		g_iomap.mapJogBnF[i].bit = (BYTE)Inbit[n];
	}
	/*
	for(i=0; i<INPUT_NUM; i++){
		g_factcfg.mapI[i].loc = i > 15 ? gin2Loc : gin1Loc;
		g_factcfg.mapI[i].axis =  0;
		g_factcfg.mapI[i].bit = i;
	}
	for(i=0; i<OUTPUT_NUM; i++){
		g_factcfg.mapO[i].loc = i > 15 ? gin2Loc : gin1Loc;
		g_factcfg.mapO[i].axis =  0;
		g_factcfg.mapO[i].bit = i - 16;
	}*/
	return TRUE;
}
BOOL CFactIOmap::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
#if defined(WINCE)
	if(pMsg->message==WM_KEYDOWN || pMsg->message==WM_KEYUP )
	{ 	
		if(pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN){
			HideBox();
			return TRUE;
		}
	}
#endif
	return CDialog::PreTranslateMessage(pMsg);
}
void CFactIOmap::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HideBox();
	if((phdr->iItem >= 0 && phdr->iItem < 3) ||
		(phdr->iItem >= BUTTON_LIST_ID && phdr->iItem < HW_LIST_AXIS_ID+g_Naxis)||
		(phdr->iItem > HW_LIST_AXIS_ID+g_Naxis && phdr->iItem < HW_LIST_AXIS_ID+g_Naxis*3+1)){
		if(phdr->iButton == 1){
			MoveBox(phdr->iItem);
		}
	}
	*pResult = 0;
}

//�ƶ�Box
void CFactIOmap::MoveBox(int row)
{
	CRect rect,rc;
	CString str;
	if(row < 0) return;
		m_listctr2.GetWindowRect(&rc);
		ScreenToClient(&rc);
		m_listctr2.GetSubItemRect(row,1, LVIR_LABEL,rect);//�õ��õ�Ԫ����ε�λ�ô�С��Ϣ��
		rect.OffsetRect(rc.left+2, rc.top+1);
		str = m_listctr2.GetItemText(row,1);				//��ȡ�õ�Ԫ���Ѵ��ڵ��ı����ݡ�

	if(row < LED_NUM){
		rect.bottom += rect.Height()*10 + 2;
	//	rect.bottom = rect.top + m_listbox1.GetItemHeight(0) * 7;
		m_listbox1.MoveWindow(rect);
		m_listbox1.SelectString(0, str);	
		m_listbox1.ShowWindow(SW_SHOW);	
		m_listbox1.SetFocus();
	}else{
		rect.bottom += rect.Height()*10 + 2;
	//	rect.bottom = rect.top + m_listbox1.GetItemHeight(0) * 7;
		m_listbox2.MoveWindow(rect);
		m_listbox2.SelectString(0, str);	
		m_listbox2.ShowWindow(SW_SHOW);	
		m_listbox2.SetFocus();
	}
	m_row = row;
}
//����Edit
BOOL CFactIOmap::HideBox()
{
	CString str;
	if(m_row < LED_NUM){
		if(!m_listbox1.IsWindowVisible()) return TRUE;
		m_listbox1.GetLBText(m_listbox1.GetCurSel(), str);
		m_listbox1.ShowWindow(SW_HIDE);	
	}else{
		if(!m_listbox2.IsWindowVisible()) return TRUE;
		m_listbox2.GetLBText(m_listbox2.GetCurSel(), str);
		m_listbox2.ShowWindow(SW_HIDE);	
	}
	m_listctr2.SetItemText(m_row, 1, str);
	m_listctr2.SetFocus();
	return TRUE;
}
void CFactIOmap::OnCbnSelendokCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HideBox();
}

void CFactIOmap::OnCbnSelendokCombo2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HideBox();
}
