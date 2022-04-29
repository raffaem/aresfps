// DirectionalLight.cpp : implementation file
//

#include "stdafx.h"
#include "level editor.h"
#include "DirectionalLight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirectionalLight dialog


CDirectionalLight::CDirectionalLight(CWnd* pParent /*=NULL*/)
	: CDialog(CDirectionalLight::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDirectionalLight)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDirectionalLight::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirectionalLight)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDirectionalLight, CDialog)
	//{{AFX_MSG_MAP(CDirectionalLight)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirectionalLight message handlers

void CDirectionalLight::OnOK() 
{
	if(directional_lights.size()<=0) {
		directional_lights.push_back(NULL);
		directional_lights[0]=smgr->addLightSceneNode();
	}
	video::SLight& ldata=directional_lights[0]->getLightData();
	ldata.Type=video::ELT_DIRECTIONAL;
	ldata.Position=core::vector3df(-7,-5,-2);
	
	CDialog::OnOK();
}
