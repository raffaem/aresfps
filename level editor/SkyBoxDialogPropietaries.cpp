// SkyBoxDialogPropietaries.cpp : implementation file
//

#include "stdafx.h"
#include "level editor.h"
#include "SkyBoxDialogPropietaries.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "UserDefinedSkyBox.h"

/////////////////////////////////////////////////////////////////////////////
// CSkyBoxDialogPropietaries dialog


CSkyBoxDialogPropietaries::CSkyBoxDialogPropietaries(CWnd* pParent /*=NULL*/)
	: CDialog(CSkyBoxDialogPropietaries::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CSkyBoxDialogPropietaries)
	m_sky_box_type = -1;
	//}}AFX_DATA_INIT
}


void CSkyBoxDialogPropietaries::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CSkyBoxDialogPropietaries::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkyBoxDialogPropietaries)
	DDX_CBIndex(pDX, IDC_SKY_BOX, m_sky_box_type);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSkyBoxDialogPropietaries, CDialog)
	//{{AFX_MSG_MAP(CSkyBoxDialogPropietaries)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CSkyBoxDialogPropietaries, CDialog)
	//{{AFX_DISPATCH_MAP(CSkyBoxDialogPropietaries)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ISkyBoxDialogPropietaries to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {CE443FB6-C1F3-4E53-99E9-88CE0B70C159}
static const IID IID_ISkyBoxDialogPropietaries =
{ 0xce443fb6, 0xc1f3, 0x4e53, { 0x99, 0xe9, 0x88, 0xce, 0xb, 0x70, 0xc1, 0x59 } };

BEGIN_INTERFACE_MAP(CSkyBoxDialogPropietaries, CDialog)
	INTERFACE_PART(CSkyBoxDialogPropietaries, IID_ISkyBoxDialogPropietaries, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkyBoxDialogPropietaries message handlers

void CSkyBoxDialogPropietaries::OnOK() 
{
	CDialog::OnOK();
	this->UpdateData();

	if(m_sky_box_type==0) {
		if(skyboxNode!=NULL) {
			skyboxNode->remove();
			skyboxNode=NULL;
		}
	}

	else if(m_sky_box_type==1) {
		AddDefaultSkyBox();
	}
	
	else if(m_sky_box_type==2) {
		CUserDefinedSkyBox dialog;
		dialog.DoModal();		
	}

	actual_sky_box_type=m_sky_box_type;
}

int CSkyBoxDialogPropietaries::DoModal() 
{
	m_sky_box_type=actual_sky_box_type;
	return CDialog::DoModal();
}
