// LightPropietaries.cpp : implementation file
//

#include "stdafx.h"
#include "level editor.h"
#include "LightPropietaries.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLightPropietaries dialog


CLightPropietaries::CLightPropietaries(CWnd* pParent /*=NULL*/)
	: CDialog(CLightPropietaries::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLightPropietaries)
	m_lightray = _T("");
	//}}AFX_DATA_INIT

	//get id of a select node
	string ID=raf::conv::NumString(selectnode->getID());
	char type=ID[0];
	string pos_string=raf::String::SubString(ID,1,ID.size()-1);
	int pos=atoi(pos_string.c_str());
	m_lightray=raf::conv::NumString(lights[pos]->ray).c_str();
}

void CLightPropietaries::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLightPropietaries)
	DDX_Text(pDX, IDC_LIGHTRAY, m_lightray);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLightPropietaries, CDialog)
	//{{AFX_MSG_MAP(CLightPropietaries)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLightPropietaries message handlers

void CLightPropietaries::OnOK() 
{
	this->UpdateData();
	string ID=raf::conv::NumString(selectnode->getID());
	string pos_string=raf::String::SubString(ID,1,ID.size()-1);
	int pos=atoi(pos_string.c_str());
	lights[pos]->ray=atof(m_lightray);

	//remove and recreate it
	core::vector3df new_light_pos=lights[pos]->light->getPosition();
	s32 new_light_ID=lights[pos]->light->getID();

	lights[pos]->light->remove();
	lights[pos]->light=smgr->addLightSceneNode(
		NULL,
		new_light_pos,
		video::SColorf(1.0f,1.0f,1.0f,0.0f),
		lights[pos]->ray);
	lights[pos]->light->setID(new_light_ID);

	selectnode=lights[pos]->light;
	selectnode->setDebugDataVisible(true);
	CDialog::OnOK();
}
