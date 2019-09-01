#if !defined(AFX_AMMUNATIONPROPIETARIES_H__BF0F29A8_DD7C_400E_AA9C_827644E4609A__INCLUDED_)
#define AFX_AMMUNATIONPROPIETARIES_H__BF0F29A8_DD7C_400E_AA9C_827644E4609A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AmmunationPropietaries.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAmmunationPropietaries dialog

class CAmmunationPropietaries : public CDialog
{
// Construction
public:
	CAmmunationPropietaries(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAmmunationPropietaries)
	enum { IDD = IDD_AMMUNATION_PROP };
	CString	m_num_of_bullet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAmmunationPropietaries)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAmmunationPropietaries)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AMMUNATIONPROPIETARIES_H__BF0F29A8_DD7C_400E_AA9C_827644E4609A__INCLUDED_)
