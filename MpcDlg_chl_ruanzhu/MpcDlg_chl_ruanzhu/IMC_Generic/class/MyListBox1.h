#if !defined(AFX_MYLISTBOX1_H__1C3C65DD_024B_40C9_AD4D_474A02155525__INCLUDED_)
#define AFX_MYLISTBOX1_H__1C3C65DD_024B_40C9_AD4D_474A02155525__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyListBox1 window

class CMyListBox1 : public CListBox
{
// Construction
public:
	CMyListBox1();
	~CMyListBox1();

// Attributes
public:
	CListCtrl * m_mf;
// Operations
public:

	void SetMainHandle(CListCtrl *mf);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListBox1)
	//}}AFX_VIRTUAL
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListBox1)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillfocus();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTBOX1_H__1C3C65DD_024B_40C9_AD4D_474A02155525__INCLUDED_)
