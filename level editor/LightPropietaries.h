#if !defined(AFX_LIGHTPROPIETARIES_H__F0B2F951_8B6A_4896_89AA_3FE794CF46C2__INCLUDED_)
#define AFX_LIGHTPROPIETARIES_H__F0B2F951_8B6A_4896_89AA_3FE794CF46C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LightPropietaries.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLightPropietaries dialog

class CLightPropietaries : public CDialog
{
// Construction
public:
	CLightPropietaries(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLightPropietaries)
	enum { IDD = IDD_LIGHTPROPIETARIES };
	CString	m_lightray;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLightPropietaries)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLightPropietaries)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTPROPIETARIES_H__F0B2F951_8B6A_4896_89AA_3FE794CF46C2__INCLUDED_)
