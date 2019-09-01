#if !defined(AFX_SKYBOXDIALOGPROPIETARIES_H__DF9088E6_8E20_4DC0_B393_358D19B4C55A__INCLUDED_)
#define AFX_SKYBOXDIALOGPROPIETARIES_H__DF9088E6_8E20_4DC0_B393_358D19B4C55A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkyBoxDialogPropietaries.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSkyBoxDialogPropietaries dialog

class CSkyBoxDialogPropietaries : public CDialog
{
// Construction
public:
	CSkyBoxDialogPropietaries(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSkyBoxDialogPropietaries)
	enum { IDD = IDD_SKY_BOX_PROP };
	int		m_sky_box_type;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkyBoxDialogPropietaries)
	public:
	virtual void OnFinalRelease();
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSkyBoxDialogPropietaries)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CSkyBoxDialogPropietaries)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKYBOXDIALOGPROPIETARIES_H__DF9088E6_8E20_4DC0_B393_358D19B4C55A__INCLUDED_)
