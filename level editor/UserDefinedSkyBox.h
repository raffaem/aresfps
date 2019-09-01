#if !defined(AFX_USERDEFINEDSKYBOX_H__DD600C82_678D_45E0_9652_6BC836FBC51F__INCLUDED_)
#define AFX_USERDEFINEDSKYBOX_H__DD600C82_678D_45E0_9652_6BC836FBC51F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserDefinedSkyBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserDefinedSkyBox dialog

class CUserDefinedSkyBox : public CDialog
{
// Construction
public:
	CUserDefinedSkyBox(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserDefinedSkyBox)
	enum { IDD = IDD_USER_DEFINED_SKY_BOX };
	CString	m_back;
	CString	m_bottom;
	CString	m_front;
	CString	m_left;
	CString	m_right;
	CString	m_top;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserDefinedSkyBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserDefinedSkyBox)
	virtual void OnOK();
	afx_msg void OnTopBrowse();
	afx_msg void OnBottomBrowse();
	afx_msg void OnLeftBrowse();
	afx_msg void OnRightBrowse();
	afx_msg void OnFrontBrowse();
	afx_msg void OnBackBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERDEFINEDSKYBOX_H__DD600C82_678D_45E0_9652_6BC836FBC51F__INCLUDED_)
