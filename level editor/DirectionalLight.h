#if !defined(AFX_DIRECTIONALLIGHT_H__E40A02F7_5954_4B74_AB96_309150DE3F98__INCLUDED_)
#define AFX_DIRECTIONALLIGHT_H__E40A02F7_5954_4B74_AB96_309150DE3F98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DirectionalLight.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDirectionalLight dialog

class CDirectionalLight : public CDialog
{
// Construction
public:
	CDirectionalLight(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDirectionalLight)
	enum { IDD = IDD_DIRECTIONALLIGHT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirectionalLight)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDirectionalLight)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRECTIONALLIGHT_H__E40A02F7_5954_4B74_AB96_309150DE3F98__INCLUDED_)
