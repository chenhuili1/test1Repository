// dlg/MainDlg.cpp : ʵ���ļ�
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

// CMainDlg �Ի���

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


// CMainDlg ��Ϣ�������

BOOL CMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
//	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
//	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
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
			SetDlgItemText(IDC_BN_RUN, _T("����"));
		else
			SetDlgItemText(IDC_BN_RUN, _T("ֹͣ"));
		m_isEditEN = TRUE;
		OnBnClickedBnEditEn();
	}else
		SetDlgItemText(IDC_BN_RUN, _T("����"));
}
void CMainDlg::InitListCtrl()
{
	DWORD dwStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;   //�����ʾ��ʽλ 
	dwStyle|= LVS_REPORT; //���ñ�����
	//��ԭ����ʽ�Ļ����ϣ����LVS_REPORT��չ��ʽ
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, dwStyle);
	//��ȡ���е���չ��ʽ
	DWORD dwStyles = m_list.GetExStyle();
	//ȡ����ѡ����ʽ
	dwStyles &= ~LVS_EX_CHECKBOXES;
	dwStyles   |=LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES  ;
	//�������ѡ��ͱ������չ��ʽ
	m_list.SetExtendedStyle(dwStyles);
//	m_list.SetRowHeigt(18);//�����и߶�
//	m_list.SetFontHW(15,0);               //��������߶ȣ��Ϳ��,0��ʾȱʡ���
	if(m_listFont == NULL){//
		m_listFont = new CFont;
		m_listFont->CreateFont(20,0,0,0,0,FALSE,FALSE,0,0,0,0,0,0,_T("����"));//��������
	}
	m_listlen = 800;
	m_list.SetFont(m_listFont, TRUE);//��������ı��и�
	m_list.InsertColumn(0, _T("�к�"),LVCFMT_RIGHT,60);
	m_list.InsertColumn(1, _T("ָ��"),LVCFMT_CENTER,135);
	m_list.InsertColumn(2, _T("����"),LVCFMT_LEFT,m_listlen);
}
//����༭ģʽ
void CMainDlg::OnBnClickedBnEditEn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CIMC_GenericDlg* mdlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(!m_isEditEN){
		if(mdlg->GetThreadSt()) return;
		if(!mdlg->IsPasswordOK(MY_PW_EDIT)) return;
		SetDlgItemText(IDC_BN_EDIT_EN, _T("�˳��༭ģʽ"));
	}else
		SetDlgItemText(IDC_BN_EDIT_EN, _T("����༭ģʽ"));
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
					m_list.SetItemState(row, 0, -1);//ȡ��ѡ��
					m_list.SetSelectionMark(cnt-1);
					m_list.EnsureVisible(cnt-1, TRUE);
					m_list.SetItemState(cnt-1,LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED|LVIS_DROPHILITED);//ѡ��
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

//˫��
void CMainDlg::OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CIMC_GenericDlg* mdlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(mdlg->GetThreadSt()) {
		*pResult = 1;
		return;
	}
	int nItem=phdr->iItem;
	if(m_isEditEN){
		if(nItem!=-1){
		//	ProgramDlg(nItem);//������̶Ի���
			PostMessage(WM_MY_PROGRAM_SHOW, (WPARAM)nItem, (LPARAM)CMD_NULL);//֪ͨ����ܸ���
		}
	}
	*pResult = 0;
}
//����
void CMainDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	row = m_list.GetSelectionMark();//��õ�ǰѡ�����
	m_list.SetItemState(row, 0, -1);//ȡ��ѡ��
	if(m_machinSel == 0)//����ʱ
		row = m_startLine + line;
	else
		row = line;
	m_list.SetSelectionMark(row);
	m_list.SetItemState(row,LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED|LVIS_DROPHILITED);//ѡ��
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
{//�ӹ���ʱ:
	CString str;
	str.Format(_T("%02d:%02d:%02d"), time/3600, time/60, time%60);
	SetDlgItemText(IDC_STATIC_WORK_TIME, str);
}

void CMainDlg::ShowMachinTime(DWORD time)
{//������ʱ
	CString str;
	str.Format(_T("%02d:%02d:%02d"), time/3600, time/60, time%60);
	SetDlgItemText(IDC_STATIC_WORK_TIME_ONE, str);
}
void CMainDlg::ShowMachinNum(DWORD cnt)
{//�ӹ�����
	CString str;
	str.Format(_T("%06d "), cnt);
	SetDlgItemText(IDC_STATIC_WORKED_CNT, str);
}
void CMainDlg::ShowMachinStatus()
{//�ӹ�����
	CIMC_GenericDlg * dlg = (CIMC_GenericDlg*)m_mdlg;
	if(dlg->GetThreadSt())
		SetDlgItemText(IDC_STATIC_RUN_STATUS, _T("����״̬:  ������..."));
	else
		SetDlgItemText(IDC_STATIC_RUN_STATUS, _T("����״̬:  δ����"));
}
void CMainDlg::MahinEndTip(int tip)
{
	CString str;
	switch(tip)
	{
	case 0: str = _T(""); break;
	case 1: str = _T("���ڼӹ����һ��..."); break;
	case 2: str = _T("22��ͣ��ť���£� �ſ���ͣ��ť�ָ�"); break;
	case 3: str = _T("33��ͣ��ť���£� �ſ���ͣ��ť�ָ�"); break;
	}
	SetDlgItemText(IDC_STATIC_MACHIN_END, str);
}
void CMainDlg::MahinEndTip(CString str)
{
	SetDlgItemText(IDC_STATIC_MACHIN_END, str);
}
//�޸�
void CMainDlg::OnBnClickedBnEditChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int row = m_list.GetSelectionMark();//��õ�ǰѡ�����
	if(row != -1){
		PostMessage(WM_MY_PROGRAM_SHOW, (WPARAM)row, (LPARAM)CMD_NULL);//֪ͨ����ܸ���
	}
}

//��������
void CMainDlg::OnBnClickedBnEditAddLine()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	int row;
	row = m_list.GetSelectionMark();//��õ�ǰѡ�����
	m_list.SetItemState(row, 0, -1);//ȡ��ѡ��
	row=m_list.GetItemCount();
	str.Format(_T("%d"),row+1);
	m_list.InsertItem(row, str);
	m_list.SetSelectionMark(row);
	m_list.EnsureVisible(row, TRUE);
	m_list.SetItemState(row,LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED|LVIS_DROPHILITED);//ѡ��
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

//��������
void CMainDlg::OnBnClickedBnEditInsert()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i,rows = 0, row ;
	CString str;
	row = m_list.GetSelectionMark();//��õ�ǰѡ�����
	m_list.SetItemState(row, 0, -1);//ȡ��ѡ��
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
//ɾ��ȫ��
void CMainDlg::OnBnClickedBnEditDeleteAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(MessageBox(_T("�Ƿ�ɾ���б��е�����ָ�"), _T("��ʾ"), MB_YESNO) == IDNO)
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

//ɾ��
void CMainDlg::OnBnClickedBnEditDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

//�����ļ�
void CMainDlg::OnBnClickedBnLoadFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CIMC_GenericDlg* mh = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(mh->m_bChange){
		if(MessageBox(_T("�Ƿ���Ҫ���浱ǰ�༭�ĳ���"), _T("��ʾ"), MB_YESNO) == IDYES){
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
		MessageBox(_T("�޷��򿪱���ļ�������ʧ�ܣ�"));
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
		MessageBox(_T("�ļ���ʽ����"));
		return FALSE;
	}
	if(head.size > sizeof(PROGRAM_DATA)) size = sizeof(PROGRAM_DATA);
	else size = head.size;
	pt =new char[head.size];
	for(i=0; i<head.cnt; i++)
	{
		pdata = new PROGRAM_DATA;
		memset(pdata, 0, sizeof(PROGRAM_DATA));
		len = fread(pt, head.size, 1, pf);//��������pt��
		if(len != 1) {
			delete [] pt;
			delete pdata;
			return FALSE;
		}
		str.Format(_T("%d"),i+1);
		m_list.InsertItem(i, str);
		m_list.SetItemData(i, (DWORD)pdata);
		memcpy(pdata, pt, size);//ֻ����size��С������
		ShowListData(i, pdata);
	}
	//**********************************************
	pre = NULL;
	while(1){
		prec = new JUMP_REC;
		len = fread(prec, sizeof(JUMP_REC), 1, pf);//��������pt��
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

//�����ļ�
void CMainDlg::OnBnClickedBnSaveFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox(_T("�޷����ļ�������ʧ�ܣ�"));
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
//�½�
void CMainDlg::OnBnClickedBnNewFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CIMC_GenericDlg* mh = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(mh->m_bChange){
		if(MessageBox(_T("�Ƿ���Ҫ���浱ǰ�༭�ĳ���"), _T("��ʾ"), MB_YESNO) == IDYES){
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

//ϵͳ����
void CMainDlg::OnBnClickedBnSysCfg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(!dlg->IsPasswordOK(MY_PW_SYS)) return;
	dlg->ShowDlg(JM_SYS);
}
//����
void CMainDlg::OnBnClickedBnRun()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CIMC_GenericDlg* mdlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(!mdlg->m_imc.IsOpen()){
		MessageBox(_T("�豸û�����ӣ�"),_T("����"));
		return;
	}
	if(mdlg->m_imc.m_Naxis < g_factcfg.Naxis){
		MessageBox(_T("���ƿ���Ч������������ò�����"),_T("����"));
		return;
	}
	if(m_list.GetItemCount() < 1){
		MessageBox(_T("û��ָ���ִ�У�"));
		return;
	}
	if(!mdlg->IsPasswordOK(MY_PW_RUN)) return;
	UpdateData(TRUE);
	EnableRunKey();
	mdlg->StartMatchin(m_machinSel);
}
//��ͣ
void CMainDlg::OnBnClickedBnPause()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CIMC_GenericDlg* mdlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	mdlg->PauseMatchin();
}

//��ͣ
void CMainDlg::OnBnClickedBnEmstop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	dlg->EmstopMatchin();
}
//��λ
void CMainDlg::OnBnClickedBnReset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(!dlg->m_imc.IsOpen()){
		MessageBox(_T("�豸û�����ӣ�"),_T("����"));
		return;
	}
	CString str;
	str = GetMyMFCDir();
	str += SAV_FILE_RESET;
	str += FILE_EXP;
	if(!IsFileDirExist(str)){
		MessageBox(_T("ϵͳ�л�û�и�λ����(reset)��\r\n\r\n���ȱ༭һ����λ��������,������Ϊ��reset��"), _T("��ʾ"));
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
		SetDlgItemText(IDC_BN_RESET, _T("��λ"));
	}else
		SetDlgItemText(IDC_BN_RESET, _T("ֹͣ"));
}
//�ֶ�����
void CMainDlg::OnBnClickedBnManual()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CManual dlg;
	CIMC_GenericDlg* mdlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(!mdlg->m_imc.IsOpen()){
		MessageBox(_T("�豸û�����ӣ�"),_T("����"));
		return;
	}
	if(mdlg->m_imc.m_Naxis < g_factcfg.Naxis){
		MessageBox(_T("���ƿ���Ч������������ò�����"),_T("����"));
		return;
	}
	dlg.SetMainDlgPtr(m_mdlg);
	INT_PTR nResponse = dlg.DoModal();
}
//����
void CMainDlg::OnBnClickedBnGohome()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	if(!dlg->m_imc.IsOpen()){
		MessageBox(_T("�豸û�����ӣ�"),_T("����"));
		return;
	}
	if(dlg->m_imc.m_Naxis < g_factcfg.Naxis){
		MessageBox(_T("���ƿ���Ч������������ò�����"),_T("����"));
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
{//��ɾ��һ�л��߲���һ��ǰ���������ת���
	JUMP_REC *prec = m_jpRec;
	while(prec != NULL)
	{
		if(prec->pjdata->type != CMD_NULL){//ָ�����������ݲŸ���
			if(isNew){//����һ��
				if((prec->jumpLine-1) >= row){//ֻ���ں���������
					if(prec->jumpLine-1 != prec->line){//��ɾ������ת���к���ɾ��������ʱ���������ȵ����
						prec->pdata->jumpLine ++;
						prec->jumpLine ++;
						ShowListData(prec->line, prec->pdata);
					}
				}
			}else{
				if((prec->jumpLine-1) == row){//���ɾ��������ת�����У�
					CString str;
					str.Format(_T("�� %d �л���ת�����У���Ҫɾ������ע���޸ĵ� %d �е���ת��\r\n\r\n�Ƿ�Ҫɾ�����У�"), prec->line+1, prec->line+1);
					if(MessageBox(str, _T("��ʾ"), MB_YESNO) == IDNO)
						return FALSE;
				}if((prec->jumpLine-1) > row){
					if(prec->jumpLine-1 != prec->line){//��ɾ������ת���к���ɾ��������ʱ���������ȵ����
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
//��ʾ����༭�Ի���
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
		}else{//û����ת�ģ���ɾ������ת��
			if(prec != NULL){
				if(pRecP != NULL)//��ǰ��¼���ǵ�һ��
					pRecP->next = prec->next;
				else //��ǰ��¼���ǵ�һ��
					m_jpRec = prec->next;
				delete prec;
			}	
		}
		if(g_isUseHWok){
			if(m_list.GetItemCount() == row + 1){//�������һ�е�ʱ�������
				OnBnClickedBnEditAddLine();
				int line = m_list.GetSelectionMark();//��õ�ǰѡ�����
				pdata1 = (PROGRAM_DATA*)m_list.GetItemData(line);
				pdata1->posBit = pdata->posBit;
				pdata1->arcBit = pdata->arcBit;
				pdata1->arc[0] = pdata->arc[4];
				pdata1->arc[1] = pdata->arc[5];
				PostMessage(WM_MY_PROGRAM_SHOW, (WPARAM)line, (LPARAM)pdata->type);//֪ͨ����ܸ���
			}
		}
	}
//	dlg.StopHW();
}
//��ʾ�б���е�����
void CMainDlg::ShowListData(int row, PROGRAM_DATA*pdata)
{
	CString str;
//	str.Format(_T("%d"),i+1);
	if(pdata == NULL) return;
	m_list.SetItemText(row,1,g_cmdStr[pdata->type]);
	ShowDescription(row, pdata);
}
//��ʾ�б���е�����
void CMainDlg::ShowDescription(int row, PROGRAM_DATA*pdata)
{
	CString str,tmp, tmp1;
	int i , j;
	switch(pdata->type)
	{
	case CMD_LINKAGE://��������	
		if(pdata->InSel){//����ƶ�
			for(i=0; i<g_Naxis; i++){
				if(pdata->posBit & (1 << i)){
					tmp.Format(_T("%s �ƶ����� %.02f%s; "), g_AxisName[i], 1.0*pdata->pos[i]/*/g_factcfg.distFac[i]*/, g_factcfg.Unit[i]);
					str += tmp;
				}
			}
		}else{
			for(i=0; i<g_Naxis; i++){
				if(pdata->posBit & (1 << i)){
					tmp.Format(_T("%s Ŀ��λ�� %.02f%s; "), g_AxisName[i], 1.0*pdata->pos[i]/*/g_factcfg.distFac[i]*/, g_factcfg.Unit[i]);
					str += tmp;
				}
			}
		}
		tmp.Format(_T("�켣�� %s�ٶ� �˶������ٶȱ���Ϊ%d%%"), pdata->vel == 0 ? _T("����") : _T("����"), (pdata->velRatio+1) *10);
		str += tmp;
		break;
	case CMD_ARC:	//Բ��	
		int x[2];
		j=0;
		str = _T("��Բ������Ϊ��");
		for(i=0; i<g_Naxis; i++){
			if(pdata->arcBit & (1 << i)){
				x[j++] = i;
				tmp.Format(_T("%s��"), g_AxisName[i]);
				str += tmp;
			}
		}
		if(j<2) break;
		tmp.Format(_T("Բ���ϵĵ�����ΪP1��%.02f,%.02f)��P2��%.02f,%.02f)��P3��%.02f,%.02f)��"), 
			1.0*pdata->arc[0]/*/g_factcfg.distFac[x[0]]*/, 1.0*pdata->arc[1]/*/g_factcfg.distFac[x[1]]*/, 
			1.0*pdata->arc[2]/*/g_factcfg.distFac[x[0]]*/, 1.0*pdata->arc[3]/*/g_factcfg.distFac[x[1]]*/, 
			1.0*pdata->arc[4]/*/g_factcfg.distFac[x[0]]*/, 1.0*pdata->arc[5]/*/g_factcfg.distFac[x[1]]*/);
		str += tmp;
		if(pdata->posBit){
			str += _T("ͬ���᣺");		
			for(i=0; i<g_Naxis; i++){
				if(pdata->posBit & (1 << i)){
					tmp.Format(_T("%s Ŀ��λ�� %.02f%s;"), g_AxisName[i], 1.0*pdata->pos[i]/*/g_factcfg.distFac[i]*/, g_factcfg.Unit[i]);
					str += tmp;
				}
			}
		}
		tmp.Format(_T(" �ٶȱ���Ϊ%d%%"),  (pdata->velRatio+1) *10);
		str += tmp;
		break;
	case CMD_OUTPUT://���		
		str.Format(_T("������˿� %d ������� %s"), 
#ifdef CHANGE_DATA_0
			pdata->OutputBit +1, pdata->OutputVal ? _T("�Ͽ�") : _T("��ͨ"));
#else
			((pdata->Output >> 8)&0xFF) +1, (pdata->Output&0xFF) ? _T("�Ͽ�") : _T("��ͨ"));
#endif
		if(pdata->InSel & 0xFF){
			tmp.Format(_T("������%.02f���������� %s"), 1.0*pdata->delay/1000, ((pdata->InSel>>8) & 0xFF) ? _T("�Ͽ�") : _T("��ͨ"));
			str += tmp;
		}
		break;
	case CMD_INPUT:	//����	
		tmp1.Format(_T("��ת���� %d ��ָ��"), pdata->jumpLine);
		str.Format(_T("�� %.02f ���ڼ������˿� %d �����붯�� %s �������ʱ��%s%s%s"), 1.0*pdata->delay/1000,
#ifdef CHANGE_DATA_0
			pdata->InputBit + 1, 
			pdata->InputVal == 0  ? _T("�Ͽ�") : _T("��ͨ"),
#else
			((pdata->Input >> 8)&0xFF) + 1, 
			(pdata->Input&0xFF) == 0  ? _T("�Ͽ�") : _T("��ͨ"),
#endif
			((pdata->InSel&0xFF) == 0 ? _T("��ָͣ��") : (pdata->InSel&0xFF) == 1 ? tmp1 : _T("�޶�����ֱ��ִ����һ��ָ��")),
			((pdata->InSel>> 8)&0xFF) ? _T("����������Ʊ���") : _T(""),
			pdata->homeMode ? _T("��������ʾ") : _T(""));
		break;
	case CMD_DELAY:	//��ʱ		
		str.Format(_T("�ȴ� %.2f ���ִ����һ��ָ��"), 1.0*pdata->delay/1000);
		break;
	case CMD_JUMP:	//��ת	
		str.Format(_T("��ת���� %d ��ִ��"), pdata->jumpLine);
		break;
	case CMD_LOOP:	//ѭ����ʼ	
		str.Format(_T("��ת���� %d �п�ʼѭ������ѭ�� %d ��"), pdata->jumpLine, pdata->loopNum);
		break;
	case CMD_END:	//���������	
		str = _T("����������������ӳ���ʼλ��ִ��ָ��");
		break;
	case CMD_WEND:	//ѭ��������	
		str = _T("ѭ��������־���ж�ѭ����������������ѭ����ת�п�ʼ���Ǵ�ѭ����ʼָ�����һ��ָ�ʼִ��ָ��");
		break;
	case CMD_GOHOME://����	
		if(pdata->homeMode == 0){//ͬʱ����
			str = _T("�ƶ�����㣺");
			for(i=0; i<g_Naxis; i++){
				if(pdata->homeBit & (1 << i)){
					tmp.Format(_T("%s ˳��%d��"), g_AxisName[i], pdata->homeSort[i]+1);
					str += tmp;
				}
			}
			tmp.Format(_T("�� %s�ٶ� �ƶ������õ����;"), pdata->vel == 0 ? _T("����") : _T("����"));
			str += tmp;
			tmp.Format(_T(" �ٶȱ���Ϊ%d%%"),  (pdata->velRatio+1) *10);
			str += tmp;
		}else if(pdata->homeMode == 1){
			str = _T("������㿪�أ�");
			for(i=0; i<g_Naxis; i++){
				if(pdata->homeBit & (1 << i)){
					tmp.Format(_T("%s ˳��%d��"), g_AxisName[i], pdata->homeSort[i]+1);
					str += tmp;
				}
			}
			tmp.Format(_T("�� %s�ٶ� ������㿪��;"), pdata->vel == 0 ? _T("����") : _T("����"));
			str += tmp;
			tmp.Format(_T(" �ٶȱ���Ϊ%d%%"),  (pdata->velRatio+1) *10);
			str += tmp;
		}else if(pdata->homeMode == 2){
			str.Format(_T("��ָ�����᣺"));
			for(i=0; i<g_Naxis; i++){
				if(pdata->homeBit & (1 << i)){
					tmp.Format(_T("%d:%s��"), pdata->homeSort[i] +1, g_AxisName[i]);
					str += tmp;
				}
			}
			str += _T(" ��ǰλ������Ϊ��㣻");
		}
		break;
	case CMD_GHWHIRL://����	
		str.Format(_T("��ת�� %s ����"), g_AxisName[pdata->homeMode]);

		break;
	case CMD_VEL:	//���������˶���	
		if(pdata->vel == 2){
			str.Format(_T("ֹͣ %s ��ת��"), g_AxisName[pdata->axis]);
		}else{
			str.Format(_T("�趨 %s �� %s�ٶ� ����%s��ֱ���ı�����˶�Ϊֹ; �ٶȱ���Ϊ%d%%"), 
				g_AxisName[pdata->axis], pdata->vel == 0 ? _T("����") : _T("����"),
				pdata->dir? _T("��ת") : _T("��ת"),  (pdata->velRatio+1) *10);
		}
		break;
	case CMD_POS:	//�㵽���˶���	
		if(pdata->InSel){
			str.Format(_T("�趨 %s �� %s�ٶ� �ƶ����� %.02f%s; �ٶȱ���Ϊ%d%%"), 
				g_AxisName[pdata->axis], pdata->vel == 0 ? _T("����") : _T("����"), 1.0*pdata->pos[0]/*/g_factcfg.distFac[pdata->axis]*/, g_factcfg.Unit[pdata->axis]/*, pdata->isWT ? _T("���ȴ����ƶ�����") : _T("")*/,  (pdata->velRatio+1) *10);
		}else{
			str.Format(_T("�趨 %s �� %s�ٶ� �ӵ�ǰλ���ƶ���Ŀ��λ�� %.02f%s; �ٶȱ���Ϊ%d%%"), 
				g_AxisName[pdata->axis], pdata->vel == 0 ? _T("����") : _T("����"), 1.0*pdata->pos[0]/*/g_factcfg.distFac[pdata->axis]*/, g_factcfg.Unit[pdata->axis]/*, pdata->isWT ? _T("���ȴ����ƶ�����") : _T("")*/,  (pdata->velRatio+1) *10);
		}
		break;
	case CMD_WAIT:	//�ȴ���	
		if(pdata->WTbit == 0)
			str = _T("�ȴ��岹�˶�ֹͣ");
		else if(pdata->WTbit == 1)
			str = _T("�ȴ���λ�˶�ֹͣ");
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
	if(m_machinSel == 0){//����ʱ
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
//��ȡ��λ����
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
		MessageBox(_T("�ļ���ʽ����"));
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
		len = fread(tmp, head.size, 1, pf);//����������
		if(len != 1) {
			break;
		}
		memcpy(pdata + i, tmp, size);//ֻ����size��С������
	}
	delete tmp;
	*pnum = i;
	return pdata;
}

//��ȡ��ͣ����
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
		MessageBox(_T("�ļ���ʽ����"));
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
		len = fread(tmp, head.size, 1, pf);//����������
		if(len != 1) {
			break;
		}
		memcpy(pdata + i, tmp, size);//ֻ����size��С������
	}
	delete tmp;
	*pnum = i;
	return pdata;
}


void CMainDlg::SetBmpVal(UINT id, int val)
{
	CStatic *ic=(CStatic*)GetDlgItem(IDC_STATIC_BMP_GREED + id);
	
	if(val==0){//��
		ic->SetBitmap(m_bmp[id*2]);
	}else{//��
		ic->SetBitmap(m_bmp[id*2 + 1]);
	}
}
void CMainDlg::OnBnClickedBnFileMg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	 // MessageBox(strTmp,_T("����"));



	  
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

	 // MessageBox(strTmp,_T("����"));
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
	OnBnClickedBnEmstop();//��ͣ
}

void CMainDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMpcDlg dlg;
	CIMC_GenericDlg* mdlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();

	if(!mdlg->m_imc.IsOpen()){
		MessageBox(_T("�豸û�����ӣ�"),_T("����"));
		return;
	}
	if(mdlg->m_imc.m_Naxis < g_factcfg.Naxis){
		MessageBox(_T("���ƿ���Ч������������ò�����"),_T("����"));
		return;
	}

	dlg.SetMainDlgPtr(m_mdlg);
	INT_PTR nResponse = dlg.DoModal();
}

void CMainDlg::OnPaint()
{
 CPaintDC dc(this); // device context for painting
        // TODO: �ڴ˴������Ϣ����������
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
        // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}