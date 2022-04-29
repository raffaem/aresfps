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
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "level editor.h"
#include "MainFrm.h"
#include "AmmunationPropietaries.h"
#include "LightPropietaries.h"
#include "ArmourProp.h"
#include "medikitprop.h"
#include "PosRotScaleDlg.h"
#include "InsertModelFromZipDlg.h"
#include "DirectionalLight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "SkyBoxDialogPropietaries.h"
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_RELOAD, OnFileReload)
	ON_COMMAND(ID_FILE_VIEW_FILE, OnFileViewFile)
	ON_COMMAND(ID_WORLD_ACTIVEDIFFUSELIGHT, OnWorldActivediffuselight)
	ON_COMMAND(ID_INSERT_MODEL, OnInsertModel)
	ON_COMMAND(ID_INSERT_AMMUNATION, OnInsertAmmunation)
	ON_COMMAND(ID_INSERT_LIGHT, OnInsertLight)
	ON_COMMAND(ID_INSERT_MEDIKIT, OnInsertMedikit)
	ON_COMMAND(ID_INSERT_MONSTER_FALGAT, OnInsertMonsterFalgat)
	ON_COMMAND(ID_INSERT_MONSTER_RHINO, OnInsertMonsterRhino)
	ON_COMMAND(ID_INSERT_TERRAIN, OnInsertTerrain)
	ON_COMMAND(ID_WORLD_SKYBOXPROPIETARIES, OnWorldSkyboxpropietaries)
	ON_COMMAND(IDD_OBJ_PROPIETARIES, OnObjPropietaries)
	ON_COMMAND(ID_CAMERA_ONOFFFPSCAM, OnCameraOnofffpscam)
	ON_COMMAND(ID_INSERT_ARMOUR, OnInsertArmour)
	ON_COMMAND(ID_INSERT_MONSTER_ZOMBIE, OnInsertMonsterZombie)
	ON_COMMAND(ID_INSERT_AMMUNATION_SHOTGUN, OnInsertAmmunationShotgun)
	ON_COMMAND(ID_INSERT_AMMUNATION_RIFLEGUN, OnInsertAmmunationRiflegun)
	ON_COMMAND(ID_INSERT_AMMUNATION_MACHINEGUN, OnInsertAmmunationMachinegun)
	ON_COMMAND(ID_OBJECT_POSROTSCALESHOW, OnObjectPosrotscaleshow)
	ON_COMMAND(ID_INSERT_MODEL_FROM_ZIP_FILE, OnInsertModelFromZipFile)
	ON_COMMAND(ID_CAMERA_SETPOSLIKEWEAPON, OnCameraSetposlikeweapon)
	ON_COMMAND(ID_FILE_EXPORT_IRR, OnFileExportIrr)
	ON_COMMAND(ID_WORLD_DIRECTIONAL_LIGHT, OnWorldDirectionalLight)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style=WS_CLIPSIBLINGS|WS_CLIPCHILDREN;
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() & ~CBRS_HIDE_INPLACE);
	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}
	m_wndReBar.SetBarStyle(m_wndReBar.GetBarStyle() & ~CBRS_HIDE_INPLACE);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnFileReload() 
{
	ClearLevel();
	Load(actual_file);
}

void CMainFrame::OnFileViewFile() 
{
	bool save=raf::AddYesNoMessagebox("Do you want to save your file?\n WARNING: If you save the file, you see the lines of this level, if you don't save the file, you see the lines of the loaded file, comprehensive of corrupt or wrong line that are unloaded. If you don't load any file and you say no (don't save the file), you see a white screen","Question");
	if(save)
		Save();
	string command="call %windir%\\notepad.exe "+actual_file;
	system(command.c_str());
}

void CMainFrame::OnWorldActivediffuselight() 
{
	dl=!dl;
	DiffuseLight();	
}
void CMainFrame::OnInsertModel() 
{
	string modello,texture;
	GetMapName(modello,texture);
	AddLevelModel(modello,texture,raf::GetPointInFrontOfCamera(),core::vector3df(0,0,0),core::vector3df(1,1,1));
	
}

void CMainFrame::OnInsertAmmunation() 
{
	AddAmmunationShotgun(raf::GetPointInFrontOfCamera(),core::vector3df(0,0,0));
}

void CMainFrame::OnInsertLight() 
{
	AddLight(raf::GetPointInFrontOfCamera(),100.0f);
}

void CMainFrame::OnInsertMedikit() 
{
	AddMedikit(raf::GetPointInFrontOfCamera(),core::vector3df(0,0,0),15);
}

void CMainFrame::OnInsertMonsterFalgat() 
{
	AddFalgat(raf::GetPointInFrontOfCamera(),core::vector3df(0,0,0));
}

void CMainFrame::OnInsertMonsterRhino() 
{
	AddRhino(raf::GetPointInFrontOfCamera(),core::vector3df(0,0,0));
}

void CMainFrame::OnInsertTerrain() 
{
	string heightmap,texture,dtexture;
	GetTerrainName(heightmap,texture,dtexture);
	AddTerrain(heightmap,texture,dtexture,raf::GetPointInFrontOfCamera(),core::vector3df(0,0,0));
}

void CMainFrame::OnWorldSkyboxpropietaries() 
{
	CSkyBoxDialogPropietaries dialog;
	dialog.DoModal();
}


void CMainFrame::OnObjPropietaries() 
{
	if(selectnode!=NULL) {
	//get id of a select node
	string ID=raf::conv::NumString(selectnode->getID());
	char type=ID[0];
	
	//if it is an ammunation, show ammunation propietaries
	if(type==type::ammunation) {
		CAmmunationPropietaries prop;
		prop.DoModal();
	}
	else if(type==type::medikit) {
		CMedikitProp prop;
		prop.DoModal();
	}
	else if(type==type::armour) {
		CArmourProp prop;
		prop.DoModal();
	}
	else if(type==type::light) {
		CLightPropietaries prop;
		prop.DoModal();
	}
	else
		MessageBox("There are no propietaries for selected node","Error",MB_OK|MB_SYSTEMMODAL);

	}//if(selectnode!=NULL)
	else
		MessageBox("You have selected no object. Please select an object to use this option","Error",MB_OK|MB_SYSTEMMODAL);
}

void CMainFrame::OnCameraOnofffpscam() 
{
	ChangeFPSCam();
}

void CMainFrame::OnInsertArmour() 
{
	AddArmour(raf::GetPointInFrontOfCamera(),core::vector3df(0,0,0),15);
}

void CMainFrame::OnInsertMonsterZombie() 
{
	AddZombie(raf::GetPointInFrontOfCamera(),core::vector3df(0,0,0));
}


void CMainFrame::OnInsertAmmunationShotgun() 
{
	AddAmmunationShotgun(raf::GetPointInFrontOfCamera(),core::vector3df(0,0,0));
}

void CMainFrame::OnInsertAmmunationRiflegun() 
{
	AddAmmunationRiflegun(raf::GetPointInFrontOfCamera(),core::vector3df(0,0,0));
}

void CMainFrame::OnInsertAmmunationMachinegun() 
{
	AddAmmunationMachinegun(raf::GetPointInFrontOfCamera(),core::vector3df(0,0,0));

}

void CMainFrame::OnObjectPosrotscaleshow() 
{
	CPosRotScaleDlg p;
	p.DoModal();	
}

void CMainFrame::OnInsertModelFromZipFile() 
{
	CInsertModelFromZipDlg d;
	d.DoModal();	
}

void CMainFrame::OnCameraSetposlikeweapon() 
{
	camera->setPosition(weapon->getPosition());	
}

void CMainFrame::OnFileExportIrr() 
{
		OPENFILENAME SaveFileName;
	TCHAR         szFile[MAX_PATH]      = "\0";
    strcpy( szFile, "");

	// Fill in the OPENFILENAME structure to support a template and hook.
	SaveFileName.lStructSize       = sizeof(OPENFILENAME);
    SaveFileName.hwndOwner         = NULL;
    SaveFileName.hInstance         = NULL;
    SaveFileName.lpstrFilter       = "Irrlicht file (.irr)\0*.irr\0Irrlicht file (.xml)\0*.xml\0All files (*.*)\0*.*\0\0";
    SaveFileName.lpstrCustomFilter = NULL;
    SaveFileName.nMaxCustFilter    = 0;
    SaveFileName.nFilterIndex      = 0;
    SaveFileName.lpstrFile         = szFile;
    SaveFileName.nMaxFile          = sizeof(szFile);
    SaveFileName.lpstrFileTitle    = NULL;
    SaveFileName.nMaxFileTitle     = 0;
    SaveFileName.lpstrInitialDir   = NULL;
    SaveFileName.lpstrTitle        = "Export to irr";
    SaveFileName.nFileOffset       = 0;
    SaveFileName.nFileExtension    = 0;
    SaveFileName.lpstrDefExt       = "irr";
    SaveFileName.lCustData         = 0;
	SaveFileName.lpfnHook 		   = NULL;
	SaveFileName.lpTemplateName    = NULL;
    SaveFileName.Flags             = OFN_OVERWRITEPROMPT|OFN_EXPLORER|OFN_HIDEREADONLY;
	
	if(GetSaveFileName(&SaveFileName)==false) {
		return;
	}
	smgr->saveScene(SaveFileName.lpstrFile);
}

void CMainFrame::OnWorldDirectionalLight() 
{
	CDirectionalLight p;
	p.DoModal();	
}
