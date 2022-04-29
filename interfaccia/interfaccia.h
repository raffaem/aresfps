// interfaccia.h : main header file for the INTERFACCIA application
//

#if !defined(AFX_INTERFACCIA_H__3369CEFF_8E26_41F7_A9E8_0369859D1B41__INCLUDED_)
#define AFX_INTERFACCIA_H__3369CEFF_8E26_41F7_A9E8_0369859D1B41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CInterfacciaApp:
// See interfaccia.cpp for the implementation of this class
//

class CInterfacciaApp : public CWinApp
{
public:
	CInterfacciaApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterfacciaApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CInterfacciaApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERFACCIA_H__3369CEFF_8E26_41F7_A9E8_0369859D1B41__INCLUDED_)
