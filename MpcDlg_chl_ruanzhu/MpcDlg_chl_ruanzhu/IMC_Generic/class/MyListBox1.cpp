// MyListBox.cpp : implementation file
//

#include "stdafx.h"
#include "MyListBox1.h"
#include "MyList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListBox1

CMyListBox1::CMyListBox1()
{
	m_mf = NULL;
}

CMyListBox1::~CMyListBox1()
{
}


BEGIN_MESSAGE_MAP(CMyListBox1, CListBox)
	//{{AFX_MSG_MAP(CMyListBox1)
	ON_WM_LBUTTONUP()
	ON_CONTROL_REFLECT(LBN_KILLFOCUS, OnKillfocus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListBox1 message handlers


void CMyListBox1::SetMainHandle(CListCtrl *mf)
{
	m_mf=mf;
}

void CMyListBox1::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMyList* hwnd= (CMyList*)m_mf;
	ShowWindow(SW_HIDE);
	if(hwnd != NULL){
		CString str;
		int i = GetCurSel();
		GetText(i, str);
		hwnd->SelendokList(str);
	}
	
	CListBox::OnLButtonUp(nFlags, point);
}


void CMyListBox1::OnKillfocus() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	
}
