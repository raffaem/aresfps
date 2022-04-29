#if !defined(AFX_ARMOURPROP_H__6CE03413_8655_47A1_8A14_E88B3E89B5C0__INCLUDED_)
#define AFX_ARMOURPROP_H__6CE03413_8655_47A1_8A14_E88B3E89B5C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ArmourProp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArmourProp dialog

class CArmourProp : public CDialog
{
// Construction
public:
	CArmourProp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CArmourProp)
	enum { IDD = IDD_ARMOUR_PROP };
	CString	m_num_of_armour;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArmourProp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CArmourProp)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARMOURPROP_H__6CE03413_8655_47A1_8A14_E88B3E89B5C0__INCLUDED_)
