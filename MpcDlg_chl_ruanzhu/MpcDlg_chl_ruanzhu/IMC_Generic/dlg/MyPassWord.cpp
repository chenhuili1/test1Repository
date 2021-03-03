// dlg/MyPassWord.cpp : 实现文件
//

#include "stdafx.h"
#include "IMC_Generic.h"
#include "dlg/MyPassWord.h"


// CMyPassWord 对话框

IMPLEMENT_DYNAMIC(CMyPassWord, CDialog)

CMyPassWord::CMyPassWord(CWnd* pParent /*=NULL*/)
	: CDialog(CMyPassWord::IDD, pParent)
{

}

CMyPassWord::~CMyPassWord()
{
}

void CMyPassWord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyPassWord, CDialog)
	ON_BN_CLICKED(IDOK, &CMyPassWord::OnBnClickedOk)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CMyPassWord 消息处理程序


void CMyPassWord::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!IsPasswordOK()){
		SetDlgItemText(IDC_STATIC_WARN, _T("密码错误！"));
		return;
	}
//	GetPassword();
	CDialog::OnOK();
}

void CMyPassWord::SetType(int type)
{
	m_type = type;
}
BOOL CMyPassWord::IsPasswordOK()
{
	CString str;
	GetDlgItemText(IDC_EDIT_POSSWORD, str);
	if(str.GetLength() != PASSWORD_USE_LEN)
		return FALSE;
	WCHAR *pw;
	switch(m_type)
	{
	case MY_PW_FACT:	pw = g_factcfg.PWfact; break;
	case MY_PW_LOGIN:	pw = g_cfg.PWlogin; break;
	case MY_PW_EDIT:	pw = g_cfg.PWEdit; break;
	case MY_PW_SYS:		pw = g_cfg.PWSys; break;
	case MY_PW_RUN:		pw = g_cfg.PWRun; break;
	}
	for(int i=0; i<PASSWORD_USE_LEN; i++)
	{
		if(str.GetAt(i) != pw[i])
			return FALSE;
	}
	return TRUE;
}
void CMyPassWord::GetPassword()
{
	WCHAR *pw;
	switch(m_type)
	{
	case MY_PW_FACT:	pw = g_factcfg.PWfact; break;
	case MY_PW_LOGIN:	pw = g_cfg.PWlogin; break;
	case MY_PW_EDIT:	pw = g_cfg.PWEdit; break;
	case MY_PW_SYS:		pw = g_cfg.PWSys; break;
	case MY_PW_RUN:		pw = g_cfg.PWRun; break;
	}
	GetDlgItemText(IDC_EDIT_POSSWORD, pw, PASSWORD_USE_LEN);
}

void CMyPassWord::OnPaint()
{
 CPaintDC dc(this); // device context for painting
        // TODO: 在此处添加消息处理程序代码
 CRect  rect;
 GetClientRect(&rect);
 CDC  dcMem;
 dcMem.CreateCompatibleDC(&dc);
 CBitmap  bmpBackground;
 bmpBackground.LoadBitmap(IDB_BITMAP5);
 BITMAP  bitmap;
 bmpBackground.GetBitmap(&bitmap);
 CBitmap* pbmpOld = dcMem.SelectObject(&bmpBackground); 
 dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
        // 不为绘图消息调用 CDialog::OnPaint()
}