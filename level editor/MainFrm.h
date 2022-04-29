/*
PLEASE DON'T DELETE THIS NOTE IF YOU REDISTRIBUTE THIS PROGRAM

This file is a part of Ares, a first person shooter (fps) game 
based on irrlicht engine

Copyright (C) 2006  Mancuso Raffaele

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

Ares web-site: http://aresfps.sourceforge.net
Ares e-mail: ares_support@virgilio.it
*/
// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__0EA431CB_27EE_4B04_B811_9F69EDF599EC__INCLUDED_)
#define AFX_MAINFRM_H__0EA431CB_27EE_4B04_B811_9F69EDF599EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CToolBar    m_wndPosRotScaleTool;
	CReBar      m_wndReBar;
	CDialogBar      m_wndDlgBar;
	CDialogBar      m_wndPosRotScaleDialog;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileReload();
	afx_msg void OnFileViewFile();
	afx_msg void OnWorldActivediffuselight();
	afx_msg void OnInsertModel();
	afx_msg void OnInsertAmmunation();
	afx_msg void OnInsertLight();
	afx_msg void OnInsertMedikit();
	afx_msg void OnInsertMonsterFalgat();
	afx_msg void OnInsertMonsterRhino();
	afx_msg void OnInsertTerrain();
	afx_msg void OnWorldSkyboxpropietaries();
	afx_msg void OnObjPropietaries();
	afx_msg void OnCameraOnofffpscam();
	afx_msg void OnInsertArmour();
	afx_msg void OnInsertMonsterZombie();
	afx_msg void OnInsertAmmunationShotgun();
	afx_msg void OnInsertAmmunationRiflegun();
	afx_msg void OnInsertAmmunationMachinegun();
	afx_msg void OnObjectPosrotscaleshow();
	afx_msg void OnInsertModelFromZipFile();
	afx_msg void OnCameraSetposlikeweapon();
	afx_msg void OnFileExportIrr();
	afx_msg void OnWorldDirectionalLight();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__0EA431CB_27EE_4B04_B811_9F69EDF599EC__INCLUDED_)
