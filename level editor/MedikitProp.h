#if !defined(AFX_MEDIKITPROP_H__4664CC6B_B80D_4614_9A51_2E52DCBA469B__INCLUDED_)
#define AFX_MEDIKITPROP_H__4664CC6B_B80D_4614_9A51_2E52DCBA469B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MedikitProp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMedikitProp dialog

class CMedikitProp : public CDialog
{
// Construction
public:
	CMedikitProp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMedikitProp)
	enum { IDD = IDD_MEDIKIT_PROP };
	CString	m_life_value;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMedikitProp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMedikitProp)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDIKITPROP_H__4664CC6B_B80D_4614_9A51_2E52DCBA469B__INCLUDED_)
