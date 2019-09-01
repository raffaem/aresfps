#if !defined(AFX_INSERTMODELFROMZIPDLG_H__C01FE385_1B79_4B5B_835B_8768AE26771A__INCLUDED_)
#define AFX_INSERTMODELFROMZIPDLG_H__C01FE385_1B79_4B5B_835B_8768AE26771A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsertModelFromZipDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInsertModelFromZipDlg dialog

class CInsertModelFromZipDlg : public CDialog
{
// Construction
public:
	CInsertModelFromZipDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInsertModelFromZipDlg)
	enum { IDD = IDD_INSERTMODELFROMZIP };
	CString	m_zipfile;
	CString	m_model;
	CString	m_texture;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsertModelFromZipDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInsertModelFromZipDlg)
	virtual void OnOK();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSERTMODELFROMZIPDLG_H__C01FE385_1B79_4B5B_835B_8768AE26771A__INCLUDED_)
