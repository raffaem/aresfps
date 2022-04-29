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
// level editorView.cpp : implementation of the CLeveleditorView class
//

#include "stdafx.h"
#include "level editor.h"

#include "level editorDoc.h"
#include "CntrItem.h"
#include "level editorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _DEBUG
#pragma comment(lib,"..\\ares_runtime\\debug\\ares_runtime.lib")
#else
#pragma comment(lib,"..\\ares_runtime\\release\\ares_runtime.lib")
#endif

#include <irrlicht.h>
#pragma comment(lib,"irrlicht.lib")
extern irr::IrrlichtDevice* device;
/////////////////////////////////////////////////////////////////////////////
// CLeveleditorView

IMPLEMENT_DYNCREATE(CLeveleditorView, CView)

BEGIN_MESSAGE_MAP(CLeveleditorView, CView)
	//{{AFX_MSG_MAP(CLeveleditorView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeveleditorView construction/destruction

CLeveleditorView::CLeveleditorView()
{
	m_pSelection = NULL;
	// TODO: add construction code here
	atexit(Exit);
}

CLeveleditorView::~CLeveleditorView()
{
}

BOOL CLeveleditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return 	CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeveleditorView drawing

void CLeveleditorView::OnDraw(CDC* pDC)
{
	CLeveleditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	// TODO: also draw all OLE items in the document

	// advance virtual time
	device->getTimer()->tick();
	driver->beginScene(true,true,irr::video::SColor(255,0,0,0));
	smgr->drawAll();
	driver->endScene();


	// Draw the selection at an arbitrary position.  This code should be
	//  removed once your real drawing code is implemented.  This position
	//  corresponds exactly to the rectangle returned by CLeveleditorCntrItem,
	//  to give the effect of in-place editing.

	// TODO: remove this code when final draw code is complete.
		
	if (m_pSelection == NULL)
	{
		POSITION pos = pDoc->GetStartPosition();
		m_pSelection = (CLeveleditorCntrItem*)pDoc->GetNextClientItem(pos);
	}
	if (m_pSelection != NULL)
		m_pSelection->Draw(pDC, CRect(10, 10, 210, 210));
	
}

void CLeveleditorView::OnInitialUpdate()
{
	CView::OnInitialUpdate();


	// TODO: remove this code when final selection model code is written
	m_pSelection = NULL;    // initialize selection

	//INITIALIZZATION
	MessageBox("WARNING: This is just a BETA version!!! Please "
		"save often your work, a bug could cause a crash in any "
		"moment. If it happens,please send a bug report "
		"in the forum, if possible. I'll release a stable version as "
		"soon as possible. To upload, connect to ares website (see readme)","Important note",MB_OK|MB_SYSTEMMODAL);

	//ares ver
	ares_version=raf::GetAresFPSVerFromReg();
	this_file_ver=ares_version;
	
	//device
	irr::SIrrlichtCreationParameters param;
	param.WindowId = reinterpret_cast<irr::s32>(this->GetSafeHwnd()); // hColorButton
	param.DriverType = irr::video::EDT_OPENGL;
	param.Stencilbuffer=false;
	device = irr::createDeviceEx(param);
	driver=device->getVideoDriver();
	smgr=device->getSceneManager();

	//set a new font
	raf::InizializzaRaf(device);

	//prog_dir
	prog_dir=raf::String::EraseFileNameFromPath(raf::GetWin32ProgramFullPath());
	prog_dir=raf::UpDir(prog_dir);
	//end of prog_dir

	device->getFileSystem()->changeWorkingDirectoryTo(prog_dir.c_str());
	LoadMedia();

	//LOAD FILE
	if(cmd_to_execute.m_nShellCommand==CCommandLineInfo::FileOpen) {
		string file_to_load_string(cmd_to_execute.m_strFileName);
		FILE* f=fopen(file_to_load_string.c_str(),"rb");
		if(f) {
			//the file exist
			fclose(f);
			Load(file_to_load_string);
		}//the file exist
	}

}

void CLeveleditorView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}


/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL CLeveleditorView::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CLeveleditorCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CLeveleditorView::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CLeveleditorCntrItem object.
	COleInsertDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	BeginWaitCursor();

	CLeveleditorCntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document.
		CLeveleditorDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CLeveleditorCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Initialize the item from the dialog data.
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);
		
        if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
			pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);

		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted.

		// TODO: reimplement selection as appropriate for your application

		m_pSelection = pItem;   // set selection to last inserted item
		pDoc->UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
void CLeveleditorView::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CLeveleditorView::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}

	CView::OnSetFocus(pOldWnd);
}

void CLeveleditorView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
}

/////////////////////////////////////////////////////////////////////////////
// CLeveleditorView diagnostics

#ifdef _DEBUG
void CLeveleditorView::AssertValid() const
{
	CView::AssertValid();
}

void CLeveleditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLeveleditorDoc* CLeveleditorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLeveleditorDoc)));
	return (CLeveleditorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeveleditorView message handlers






