#if !defined(AFX_POSROTSCALEDLG_H__E19C7EFB_9414_4CD2_ACF6_C5C791C297D0__INCLUDED_)
#define AFX_POSROTSCALEDLG_H__E19C7EFB_9414_4CD2_ACF6_C5C791C297D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PosRotScaleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPosRotScaleDlg dialog

class CPosRotScaleDlg : public CDialog
{
// Construction
public:
	CPosRotScaleDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPosRotScaleDlg)
	enum { IDD = IDR_POSROTSCALEDIALOG };
	CString	m_posx;
	CString	m_posy;
	CString	m_posz;
	CString	m_rotx;
	CString	m_roty;
	CString	m_rotz;
	CString	m_scalex;
	CString	m_scaley;
	CString	m_scalez;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPosRotScaleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPosRotScaleDlg)
	afx_msg void OnButton2();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POSROTSCALEDLG_H__E19C7EFB_9414_4CD2_ACF6_C5C791C297D0__INCLUDED_)
