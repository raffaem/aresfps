// interfacciaDlg.h : header file
//

#if !defined(AFX_INTERFACCIADLG_H__62D9902F_D54D_4968_AB4D_CA5438660E0E__INCLUDED_)
#define AFX_INTERFACCIADLG_H__62D9902F_D54D_4968_AB4D_CA5438660E0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CInterfacciaDlg dialog

class CInterfacciaDlg : public CDialog
{
// Construction
public:
	CInterfacciaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CInterfacciaDlg)
	enum { IDD = IDD_INTERFACCIA_DIALOG };
	CButton	m_user_level_to_start_c;
	CButton	m_default_level_to_start_c;
	CComboBox	m_level_to_start_c;
	BOOL	m_antialias;
	BOOL	m_fullscreen;
	BOOL	m_play_ut;
	BOOL	m_stencylbuffer;
	CString	m_utvolume;
	BOOL	m_vsync;
	CString	m_res;
	int		m_boc;
	int		m_render;
	int		m_uthowtoplay;
	int		m_level_to_start;
	BOOL	m_default_level_to_start_val;
	BOOL	m_user_level_to_start_val;
	CString	m_extern_level_val;
	int		m_texturequality;
	CString	m_ares_cop_info;
	BOOL	m_specularhightlights;
	BOOL	m_hightprecisionfpu;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterfacciaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CInterfacciaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnUtsequentially();
	afx_msg void OnUtcasually();
	afx_msg void OnOpenUserTracksDirectory();
	afx_msg void OnOpenleveleditor();
	afx_msg void OnDefaultLevelToStart();
	afx_msg void OnUserLevelToStart();
	afx_msg void OnUserLevelBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERFACCIADLG_H__62D9902F_D54D_4968_AB4D_CA5438660E0E__INCLUDED_)
