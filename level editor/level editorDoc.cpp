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
// level editorDoc.cpp : implementation of the CLeveleditorDoc class
//

#include "stdafx.h"
#include "level editor.h"

#include "level editorDoc.h"
#include "CntrItem.h"
#include "evar.hpp"
#include "loader.hpp"
#include "save.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeveleditorDoc

IMPLEMENT_DYNCREATE(CLeveleditorDoc, COleDocument)

BEGIN_MESSAGE_MAP(CLeveleditorDoc, COleDocument)
	//{{AFX_MSG_MAP(CLeveleditorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, COleDocument::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, COleDocument::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, COleDocument::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, COleDocument::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, COleDocument::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, COleDocument::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, COleDocument::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeveleditorDoc construction/destruction

CLeveleditorDoc::CLeveleditorDoc():COleDocument()
{
	// Use OLE compound files
	EnableCompoundFile();

	// TODO: add one-time construction code here

}

CLeveleditorDoc::~CLeveleditorDoc()
{
}

BOOL CLeveleditorDoc::OnNewDocument()
{
	//-----------------------------------------------------------
	static bool first_time=true;
	if(first_time) {
		first_time=false;
		return TRUE;
	}
	//-------------------------------------------------------
	if (!COleDocument::OnNewDocument())
			return FALSE;

	ClearLevel();
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CLeveleditorDoc diagnostics

#ifdef _DEBUG
void CLeveleditorDoc::AssertValid() const
{
	COleDocument::AssertValid();
}

void CLeveleditorDoc::Dump(CDumpContext& dc) const
{
	COleDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeveleditorDoc commands

BOOL CLeveleditorDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	
	/*DO NOT USE if (!COleDocument::OnOpenDocument(lpszPathName))
		return FALSE;*/
		
	// TODO: Add your specialized creation code here
	if(costructor_execute==false) {
		this->OnNewDocument();
		Load(lpszPathName);
		return FALSE;
	}
	else{return TRUE;}
	
}

BOOL CLeveleditorDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	Save(lpszPathName);
	
	//return COleDocument::OnSaveDocument(lpszPathName);
	return TRUE;
}

void CLeveleditorDoc::Serialize(CArchive& ar) 
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
