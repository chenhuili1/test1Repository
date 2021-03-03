// dlg/MyFileMg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "MyFileMg.h"

#include "IMC_GenericDlg.h"

#define MY_ID_MASK	0x80000000

// CMyFileMg �Ի���

IMPLEMENT_DYNAMIC(CMyFileMg, CDialog)

CMyFileMg::CMyFileMg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyFileMg::IDD, pParent)
{
	m_listFont = 0;
	m_isSDEx = FALSE;

}

CMyFileMg::~CMyFileMg()
{
	delete m_listFont;
}

void CMyFileMg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listctrl1);
	DDX_Control(pDX, IDC_LIST2, m_listctrl2);
	DDX_Control(pDX, IDC_TREE1, m_TreeCtrl);
}


BEGIN_MESSAGE_MAP(CMyFileMg, CDialog)
//	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE1, &CMyFileMg::OnTvnItemexpandingTree1)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE1, &CMyFileMg::OnTvnEndlabeleditTree1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMyFileMg::OnTvnSelchangedTree1)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CMyFileMg::OnNMClickTree1)
	ON_BN_CLICKED(IDC_BN_NEW, &CMyFileMg::OnBnClickedBnNew)
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_TREE1, &CMyFileMg::OnTvnBeginlabeleditTree1)
	ON_BN_CLICKED(IDC_BN_COPY_TO_SYS, &CMyFileMg::OnBnClickedBnCopyToSys)
	ON_BN_CLICKED(IDC_BN_COPY_TO_SD, &CMyFileMg::OnBnClickedBnCopyToSd)
	ON_BN_CLICKED(IDOK, &CMyFileMg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BN_DELETE, &CMyFileMg::OnBnClickedBnDelete)
END_MESSAGE_MAP()


// CMyFileMg ��Ϣ�������

BOOL CMyFileMg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitListCtrl();
	InitTree();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMyFileMg::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case TIMER_FILE_MG:
		if(!m_isSDEx){
			if(IsFileDirExist(WINCE_SD_DIR)){
				m_TreeCtrl.SetItemText(m_hRoot, _T("U��"));
				FindSDDir(m_hRoot);
				m_TreeCtrl.Expand(m_hRoot, TVE_EXPAND);
				m_hcur = m_hRoot;
				m_isSDEx = TRUE;
			}
		}else{
			if(!IsFileDirExist(WINCE_SD_DIR)){
				m_TreeCtrl.SetItemText(m_hRoot, _T("û���ҵ�U��"));
				DeleteAllChildNodes(m_hRoot);
				m_listctrl2.DeleteAllItems();
				m_hcur = m_hRoot;
				m_isSDEx = FALSE;
			}
		}
		break;
	}
}
void CMyFileMg::InitTree()
{
//	m_TreeCtrl.SetBkColor( MY_COLOR_BACKGROUND);//������ɫ
	m_imgList.Create(IDB_BITMAP_LIST,16, 1, RGB(255,255,255));

	m_TreeCtrl.SetImageList(&m_imgList,TVSIL_NORMAL);//ѡ�����ѡ��
	m_hRoot = m_TreeCtrl.InsertItem(_T("U��"),0, 1);
	if(!IsFileDirExist(WINCE_SD_DIR)){
		m_TreeCtrl.SetItemText(m_hRoot, _T("û���ҵ�U��"));
	}
	m_TreeCtrl.SelectItem(m_hRoot);
//	m_TreeCtrl.InsertItem(NULL, m_hRoot);
//	FindSDDir(m_hRoot);
//	m_TreeCtrl.Expand(m_hRoot, TVE_EXPAND);  
	m_hcur = m_hRoot;
//	m_TreeCtrl.SetExtendedStyle(TVS_EX_FADEINOUTEXPANDOS | TVS_EX_DOUBLEBUFFER | TVS_EX_RICHTOOLTIP, TVS_EX_FADEINOUTEXPANDOS | TVS_EX_DOUBLEBUFFER | TVS_EX_RICHTOOLTIP);

}
void CMyFileMg::InitListCtrl()
{
	//ͨ��GetWindowLong����ȡCListCtrl���е���ʽ
	int i=0;
	DWORD dwStyle = GetWindowLong(m_listctrl1.m_hWnd, GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;   //�����ʾ��ʽλ 
	dwStyle|= LVS_REPORT; //LVS_LIST;//���ñ�����
	dwStyle|= LVS_SHOWSELALWAYS; ///ʼ�ո�����ѡ�еı���
	//��ԭ����ʽ�Ļ����ϣ����LVS_REPORT��չ��ʽ
	SetWindowLong(m_listctrl1.m_hWnd, GWL_STYLE, dwStyle);
	SetWindowLong(m_listctrl2.m_hWnd, GWL_STYLE, dwStyle);
	//��ȡ���е���չ��ʽ
	DWORD dwStyles = m_listctrl1.GetExStyle();
	//ȡ����ѡ����ʽ
	dwStyles &= ~LVS_EX_CHECKBOXES;
	dwStyles   |=LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES  | LVS_EX_CHECKBOXES ;
	//�������ѡ��ͱ������չ��ʽ
	m_listctrl1.SetExtendedStyle(dwStyles);
	m_listctrl2.SetExtendedStyle(dwStyles);

	if(m_listFont == NULL){//
		m_listFont = new CFont;
		m_listFont->CreateFont(22,0,0,0,0,FALSE,FALSE,0,0,0,0,0,0,_T("����"));//��������
	}
	m_listctrl1.SetFont(m_listFont, TRUE);//��������ı��и�
	m_listctrl2.SetFont(m_listFont, TRUE);//��������ı��и�
	//������
	m_listctrl1.InsertColumn(0, _T("��"),LVCFMT_LEFT,30);
	m_listctrl1.InsertColumn(1, _T("������"),LVCFMT_LEFT,120);
	m_listctrl2.InsertColumn(0, _T("��"),LVCFMT_LEFT,30);
	m_listctrl2.InsertColumn(1, _T("������"),LVCFMT_LEFT,120);


}
void CMyFileMg::MyHideWindow()
{
	KillTimer(TIMER_FILE_MG);
	ShowWindow(SW_HIDE);
}
void CMyFileMg::MyShowWindow()
{
	SetTimer(TIMER_FILE_MG, 1000, NULL);
	
	FindFIle(0, m_listctrl1);
	CString dir = GetFullPath(m_hcur);
	FindFIle(MY_ID_MASK, m_listctrl2, dir);

	ShowWindow(SW_SHOW);
}
void CMyFileMg::FindFIle(int type, CListCtrl & list, CString str)
{
#if defined(WINCE)
	int i=0, k=0, n = 0;
	CString dir, path, fstr;	

	WIN32_FIND_DATA fd;
	HANDLE hFind;
	//�������
	if(type & MY_ID_MASK)
		path = str;
	else
		path = SAV_FILE_PATH;
	path += SEACH_FILE_EXP;
	list.DeleteAllItems();
	hFind = ::FindFirstFile (path, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
			}else{
				for(i=0; i<MAX_PATH; i++){
					if(fd.cFileName[i] == 0){
						fd.cFileName[i-4] = 0;
						break;
					}
				}
				list.InsertItem(k, _T(""));
				list.SetCheck(k);
				list.SetItemText(k++,1,fd.cFileName);
			}
		} while (::FindNextFile (hFind, &fd));
		::FindClose (hFind);
	}
#endif
}
CString CMyFileMg::GetFullPath(HTREEITEM hNode)
{
	CString str, dir;
#if defined(WINCE)
	if(hNode == m_hRoot)
		return WINCE_SD_PATH;
	CString szPath = m_TreeCtrl.GetItemText(hNode);
	szPath += _T("\\");
	while((hNode = m_TreeCtrl.GetParentItem(hNode)) != m_hRoot)
	{//����丸Ŀ¼����SD��
		if(hNode == NULL) break;
		dir = m_TreeCtrl.GetItemText(hNode);
		szPath =  dir + _T("\\") + szPath;
	}
	str = WINCE_SD_PATH + szPath;
#endif
	return str;
}
void CMyFileMg::FindSDDir(HTREEITEM hNode)
{
#if defined(WINCE)
	int i=0, k=0, n = 0;
	CString dir, path, fstr;	
	WCHAR* ptr;

	WIN32_FIND_DATA fd;
	HANDLE hFind;
	
	fstr = FILE_EXP;
	dir = GetFullPath(hNode);
	dir += _T("*.*");

//	dir += _T("*.sgc");
	m_listctrl2.DeleteAllItems();
	hFind = ::FindFirstFile (dir, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
				m_TreeCtrl.InsertItem(fd.cFileName, 0, 1, hNode);
			}else{
				for(i=0; i<MAX_PATH; i++){
					if(fd.cFileName[i] == 0){
						fd.cFileName[i-4] = 0;
						ptr = &fd.cFileName[i-3];
						break;
					}
				}
				if(fstr.GetAt(1) == ptr[0] && fstr.GetAt(2) == ptr[1] && fstr.GetAt(3) == ptr[2])
				{
					m_listctrl2.InsertItem(k, _T(""));
					m_listctrl2.SetCheck(k);
					m_listctrl2.SetItemText(k++,1,fd.cFileName);
				}
			}
		} while (::FindNextFile (hFind, &fd));
		::FindClose (hFind);
	}
#endif
}

BOOL CMyFileMg::DeleteAllChildNodes(HTREEITEM hNode)
{
	if(m_TreeCtrl.ItemHasChildren(hNode))
	{
		HTREEITEM hNext, hChild = m_TreeCtrl.GetChildItem(hNode);
		while(hChild != NULL)
		{
			hNext = m_TreeCtrl.GetNextSiblingItem(hChild);
			m_TreeCtrl.DeleteItem(hChild);
			hChild = hNext; 
		}
	}
	return TRUE;
}
void CMyFileMg::OnTvnItemexpandingTree1(NMHDR *pNMHDR, LRESULT *pResult)
{//����չ��Ŀ¼���Ľڵ�
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	// �����۵�״̬��ʱ��Ų����ӽڵ�
	if(!(TVIS_EXPANDED & m_TreeCtrl.GetItemState(hItem, TVIS_EXPANDED)))
	{
		// �����ӽڵ�ǰ��ɾ���ýڵ��µ������ӽڵ㣬�Ա����
	//	this->DeleteAllChildNodes(hItem);
	//	FindSDDir(hItem);
//		CString dir = GetFullPath(hItem);
//		m_hcur = hItem;
//		FindFIle(m_id | MY_ID_MASK, m_listctrl2, dir);
	}
	*pResult = 0;
}

void CMyFileMg::OnTvnBeginlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult)
{///��ʼ�༭
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_hcur == m_hRoot)
	{
		*pResult = 1;
	}else{
#if defined(WINCE)
		OnShowSip(TRUE);
#endif
		*pResult = 0;
	}
}
void CMyFileMg::OnTvnEndlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult)
{//��������ǩ�ı༭
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str, str1, dir;
	CEdit *pEdit = m_TreeCtrl.GetEditControl();
	if(pEdit != NULL)
	{
		str1 = GetFullPath(m_hcur);//�õ��ϵ��ļ���·��
		pEdit->GetWindowText(str);
		if(!str.IsEmpty()){
			m_TreeCtrl.SetItemText(m_hcur, str);
			dir = GetFullPath(m_hcur);//�õ��µ��ļ���·��
		//	dir += str;
			if(!IsFileDirExist(str1)){//�������򴴽�
				SECURITY_ATTRIBUTES attrib;
				attrib.bInheritHandle = FALSE;
				attrib.lpSecurityDescriptor = NULL;
				attrib.nLength = sizeof(SECURITY_ATTRIBUTES);
				::CreateDirectory(dir, &attrib);
			}else{//�������
			//	::MoveFile(str1, dir);
				CFile::Rename(str1, dir);
			}
		}
	}
	m_TreeCtrl.SetFocus();
#if defined(WINCE)
	OnShowSip(FALSE);
#endif
	*pResult = 0;
}

//http://hi.baidu.com/zhuhuigong/item/f01497e7eceb7f0d8d3ea8cc
void CMyFileMg::OnBnClickedBnNew()
{//�½��ļ���
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString dir, path, str;
	int i=1;
	path = GetFullPath(m_hcur);
	while(1){
		str.Format(_T("�½��ļ���%d"), i);
		dir = path + str;
		if(!IsFileDirExist(dir)){//�������򴴽�
			SECURITY_ATTRIBUTES attrib;
			attrib.bInheritHandle = FALSE;
			attrib.lpSecurityDescriptor = NULL;
			attrib.nLength = sizeof(SECURITY_ATTRIBUTES);
			::CreateDirectory(dir, &attrib);
			break;
		}
		i++;
	}
	m_hcur = m_TreeCtrl.InsertItem(str, 0, 1, m_hcur);
	m_TreeCtrl.Expand(m_hcur, TVE_EXPAND);
	m_TreeCtrl.SetFocus();
	m_TreeCtrl.SelectItem(m_hcur);
	m_TreeCtrl.EditLabel(m_hcur);

}
void CMyFileMg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{//�Ѵ�һ���Ϊ��һ��
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_listctrl2.DeleteAllItems();
	HTREEITEM hNode = pNMTreeView->itemNew.hItem;
//	if(hNode == m_hRoot)
//		return;
	m_hcur = hNode;
	CString dir = GetFullPath(hNode);
	FindFIle(MY_ID_MASK, m_listctrl2, dir);
	*pResult = 0;
}

void CMyFileMg::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 CPoint point;
	::GetCursorPos(&point);
	CPoint ptInTree = point;
	m_TreeCtrl.ScreenToClient(&ptInTree);
	UINT uFlags;
	HTREEITEM hNode = m_TreeCtrl.HitTest(ptInTree, &uFlags);
//	if(m_TreeCtrl.ItemHasChildren(hNode))
	if(hNode != NULL){
		m_hcur = hNode;
	// �����۵�״̬��ʱ��Ų����ӽڵ�
		if(!(TVIS_EXPANDED & m_TreeCtrl.GetItemState(hNode, TVIS_EXPANDED)))
		{
			// �����ӽڵ�ǰ��ɾ���ýڵ��µ������ӽڵ㣬�Ա����
			this->DeleteAllChildNodes(hNode);
			FindSDDir(hNode);
			m_TreeCtrl.Expand(hNode, (TVIS_EXPANDED & m_TreeCtrl.GetItemState(hNode, TVIS_EXPANDED)) ? TVE_COLLAPSE : TVE_EXPAND);
		}
	}
	*pResult = 0;
}

#if defined(WINCE)
void CMyFileMg::OnShowSip(BOOL show)
{
	SIPINFO SipInfo;
	memset(&SipInfo,0,sizeof(SipInfo));
	SipInfo.cbSize=sizeof(SIPINFO);
	BOOL bRes = SipGetInfo(&SipInfo);
	if ( bRes )
	{
		if(show){
			SipInfo.fdwFlags |= SIPF_ON;
		}else{
			SipInfo.fdwFlags = SIPF_OFF;
		}
		bRes = SipSetInfo(&SipInfo);
		g_isSipShow = show;
	}
}
#endif
BOOL CMyFileMg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
#if defined(WINCE)
	if(pMsg->message==WM_KEYUP || pMsg->message==WM_KEYDOWN){
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE){
			if(g_isSipShow) {
				CWnd::SetFocus();
			//	SipShowIM(SIPF_OFF);
				OnShowSip(FALSE);
			}	
			return TRUE;
		}
	}
#endif
	return CDialog::PreTranslateMessage(pMsg);
}
void CMyFileMg::OnBnClickedBnCopyToSys()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
#if defined(WINCE)
	CString dir, path, newp;
	dir = GetFullPath(m_hcur);
	int rows=m_listctrl2.GetItemCount();
	for(int i=0; i<rows; i++)
	{
		if(m_listctrl2.GetCheck(i)){
			path = m_listctrl2.GetItemText(i,1);
			newp = SAV_FILE_PATH;
			path += FILE_EXP;
			newp += path;
			path = dir + path;
			::CopyFile(path, newp, FALSE);
			newp.Empty();
			path.Empty();
		}
	}
	FindFIle(0, m_listctrl1);
#endif
}

void CMyFileMg::OnBnClickedBnCopyToSd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
#if defined(WINCE)
	CString dir, path, newp, oldp;
	dir = GetFullPath(m_hcur);
	int rows=m_listctrl1.GetItemCount();
	for(int i=0; i<rows; i++)
	{
		if(m_listctrl1.GetCheck(i)){
			path = m_listctrl1.GetItemText(i,1);
			oldp = SAV_FILE_PATH;
			path += FILE_EXP;
			newp = dir +  path;
			oldp = oldp + path;
			::CopyFile(oldp, newp, FALSE);
			oldp.Empty();
			newp.Empty();
		}
	}
	FindFIle(MY_ID_MASK, m_listctrl2, dir);
#endif
}

void CMyFileMg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CIMC_GenericDlg* dlg = (CIMC_GenericDlg*)m_mdlg;//GetParent();
	dlg->ShowDlg(JM_MAIN);
//	OnOK();
}

void CMyFileMg::OnBnClickedBnDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
#if defined(WINCE)
	CString dir, path, oldp;
	int rows=m_listctrl1.GetItemCount();
	for(int i=0; i<rows; i++)
	{
		if(m_listctrl1.GetCheck(i)){
			path = m_listctrl1.GetItemText(i,1);
			oldp = SAV_FILE_PATH;
			path += FILE_EXP;
			oldp = oldp + path;
			::DeleteFile(oldp);
			oldp.Empty();
		}
	}
	FindFIle(0, m_listctrl1);
#endif
}
