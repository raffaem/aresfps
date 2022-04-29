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
// level editor.cpp : Defines the class behaviors for the application.
//


#include "stdafx.h"
#include "level editor.h"

#include "MainFrm.h"
#include "level editorDoc.h"
#include "level editorView.h"
#include "var.hpp"
#include "PosRotScaleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeveleditorApp

BEGIN_MESSAGE_MAP(CLeveleditorApp, CWinApp)
	//{{AFX_MSG_MAP(CLeveleditorApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeveleditorApp construction

CLeveleditorApp::CLeveleditorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLeveleditorApp object

CLeveleditorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CLeveleditorApp initialization

BOOL CLeveleditorApp::InitInstance()
{
	costructor_execute=true;

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Ares' level editor by Mancuso Raffaele"));

	LoadStdProfileSettings(5);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CLeveleditorDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CLeveleditorView));
	pDocTemplate->SetContainerInfo(IDR_CNTR_INPLACE);
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();

	//DON'T REGISTER THE FILE TYPE
	//RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	//copy cmdINfo
	cmd_to_execute.m_bRunAutomated=cmdInfo.m_bRunAutomated;
	cmd_to_execute.m_bRunEmbedded=cmdInfo.m_bRunEmbedded;
	cmd_to_execute.m_bShowSplash=cmdInfo.m_bShowSplash;
	cmd_to_execute.m_nShellCommand=cmdInfo.m_nShellCommand;
	cmd_to_execute.m_strDriverName=cmdInfo.m_strDriverName;
	cmd_to_execute.m_strFileName=cmdInfo.m_strFileName;
	cmd_to_execute.m_strPortName=cmdInfo.m_strPortName;
	cmd_to_execute.m_strPrinterName=cmdInfo.m_strPrinterName;
	//end of copy cmdInfo

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;	

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	costructor_execute=false;
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CLeveleditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

////////////////////////////////////////////////////////////////////////////
// CLeveleditorApp message handlers
int CLeveleditorApp::Run() 
{
	scene::ITextSceneNode* mouse_pos_text=NULL;

	while(device->run()) {
		driver->beginScene(true,true,irr::video::SColor(255,0,0,0));
		smgr->drawAll();
/*
#ifdef _DEBUG
		//mouse position
		if(mouse_pos_text!=NULL)
			mouse_pos_text->remove();

		core::position2d<s32> mpos=device->getCursorControl()->getPosition();
		string mpos_s;
		mpos_s+=raf::conv::NumString(mpos.X);
		mpos_s+=",";
		mpos_s+=raf::conv::NumString(mpos.Y);
		wchar_t* mpos_w=raf::conv::CharWChar_T(mpos_s.c_str());

		mouse_pos_text=smgr->addTextSceneNode(
			device->getGUIEnvironment()->getSkin()->getFont(),
			mpos_w,
			video::SColor(0,255,255,255),
			camera,
			core::vector3df(50,-550,999));
		delete mpos_w;
		//end of mouse position
#endif
		*/

		driver->endScene();
	}
	return 0;
}
