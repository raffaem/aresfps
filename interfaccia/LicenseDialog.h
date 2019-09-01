#if !defined(AFX_LICENSEDIALOG_H__D6624BEF_B5D6_4646_ACAE_F3EA1D42BE53__INCLUDED_)
#define AFX_LICENSEDIALOG_H__D6624BEF_B5D6_4646_ACAE_F3EA1D42BE53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LicenseDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLicenseDialog dialog

class CLicenseDialog : public CDialog
{
// Construction
public:
	CLicenseDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLicenseDialog)
	enum { IDD = IDD_LICENSEDIALOG };
	CString	m_license_text;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLicenseDialog)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLicenseDialog)
	afx_msg void OnYes();
	afx_msg void OnNo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LICENSEDIALOG_H__D6624BEF_B5D6_4646_ACAE_F3EA1D42BE53__INCLUDED_)
