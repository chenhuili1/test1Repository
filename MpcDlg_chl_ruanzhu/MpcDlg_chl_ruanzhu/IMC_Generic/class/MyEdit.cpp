// MyEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "MyEdit.h"
//键盘头文件
#if defined(WINCE)
#include "sip.h"
#include "SIPAPI.H"
#endif
//http://blog.csdn.net/zhangyinze123/article/details/5294364 有使用范例
// CMyEdit

IMPLEMENT_DYNAMIC(CMyEdit, CEdit)

CMyEdit::CMyEdit()
{
#if defined(WINCE)
	g_isSipShow = FALSE;
#endif
	m_isHide = FALSE;
	m_isFloat = EDIT_STRING;
}

CMyEdit::~CMyEdit()
{
#if defined(WINCE)
	if(g_isSipShow) 
		SipShowIM(SIPF_OFF);
#endif
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	//{{AFX_MSG_MAP(CMyEdit)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
//	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



// CMyEdit 消息处理程序

/*
void CMyEdit::OnMoveSip()
{
	SIPINFO SipInfo;
	memset(&SipInfo,0,sizeof(SipInfo));
	SipInfo.cbSize=sizeof(SIPINFO);
	BOOL bRes = SipGetInfo(&SipInfo);
	if ( bRes )
	{
		CRect rc(SipInfo.rcSipRect), rc1;
		GetWindowRect(&rc1);
	//	ScreenToClient(&rc1);
		rc.OffsetRect(80,0);
		SipSetDefaultRect(&rc);
		CLSID clsid;
		if ( SipGetCurrentIM(&clsid))
		{
			SipSetCurrentIM(&clsid);
		}
		SipShowIM(SIPF_ON);
	}
}*/
#if defined(WINCE)
void CMyEdit::OnShowSip(BOOL show)
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
	}
}
#endif
void CMyEdit::OnSetFocus(CWnd* pOldWnd) 
{
	CEdit::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
/*	if(g_init){
	//	OnMoveSip();
	//	SHSipPreference(m_hWnd,SIP_UP);
	//	SipShowIM(SIPF_ON);//调用软键盘
		g_isSipShow = TRUE;
		OnShowSip(g_isSipShow);
	}*/
//	m_end = GetWindowTextLength();
//	SetSel(0, m_end);
	SetSel(0, -1);
	
}
void CMyEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
//	GetSel(m_start, m_end);
#if defined(WINCE)
	Change2Float();
	if(g_isSipShow) {
	//	SipShowIM(SIPF_OFF);
		g_isSipShow = FALSE;
		OnShowSip(g_isSipShow);
	//	SetFocus();
	}
	if(m_isHide)
		ShowWindow(SW_HIDE);
#endif
	//SHSipPreference(m_hWnd,SIP_FORCEDOWN);
}

void CMyEdit::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	if(g_init)
	{
	//	SipShowIM(SIPF_ON);//调用软键盘
#if defined(WINCE)
		g_isSipShow = TRUE;
		OnShowSip(g_isSipShow);
#endif
	}
	CEdit::OnLButtonUp(nFlags, point);
}
BOOL CMyEdit::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
#if defined(WINCE)
	if(pMsg->message==WM_KEYUP || pMsg->message==WM_KEYDOWN){
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE){
			Change2Float();
			if(g_isSipShow) {
				CWnd::SetFocus();
			//	SipShowIM(SIPF_OFF);
				g_isSipShow = FALSE;
				OnShowSip(g_isSipShow);
			}	
			return TRUE;
		}
	}
#endif
	return CEdit::PreTranslateMessage(pMsg);
}
void CMyEdit::SetFloatFlag(BOOL flag)
{
	m_isFloat = flag;
}
void CMyEdit::Change2Float()
{//转换为浮点类型数据
#if defined(WINCE)
	if(g_isSipShow){
		CString cs;
		if(m_isFloat == EDIT_FLOAT){
			GetWindowText(cs);
			double f = wcstod(cs,NULL);
			cs.Format(STR_FMT_7, f);
			SetWindowText(cs);
			PostMessage(WM_KILLFOCUS, 0, 0);
		}else if(m_isFloat == EDIT_INT){
			GetWindowText(cs);
			int f = wcstol(cs, NULL, 10);
			cs.Format(STR_FMT_d, f);
			SetWindowText(cs);
			PostMessage(WM_KILLFOCUS, 0, 0);
		}
	}
#endif
}

void CMyEdit::SetHideFlag(BOOL flag)
{
	m_isHide = flag;
}
