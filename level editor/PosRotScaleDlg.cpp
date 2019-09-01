// PosRotScaleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "level editor.h"
#include "PosRotScaleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPosRotScaleDlg dialog


CPosRotScaleDlg::CPosRotScaleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPosRotScaleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPosRotScaleDlg)
	m_posx = _T("");
	m_posy = _T("");
	m_posz = _T("");
	m_rotx = _T("");
	m_roty = _T("");
	m_rotz = _T("");
	m_scalex = _T("");
	m_scaley = _T("");
	m_scalez = _T("");
	//}}AFX_DATA_INIT
	if(selectnode!=NULL) {
		core::vector3df pos=selectnode->getPosition();
		core::vector3df rot=selectnode->getRotation();
		core::vector3df scale=selectnode->getScale();
		m_posx=raf::conv::NumString(pos.X).c_str();
		m_posy=raf::conv::NumString(pos.Y).c_str();
		m_posz=raf::conv::NumString(pos.Z).c_str();
		m_rotx=raf::conv::NumString(rot.X).c_str();
		m_roty=raf::conv::NumString(rot.Y).c_str();
		m_rotz=raf::conv::NumString(rot.Z).c_str();
		m_scalex=raf::conv::NumString(scale.X).c_str();
		m_scaley=raf::conv::NumString(scale.Y).c_str();
		m_scalez=raf::conv::NumString(scale.Z).c_str();
	}
}


void CPosRotScaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPosRotScaleDlg)
	DDX_Text(pDX, IDC_POSX, m_posx);
	DDX_Text(pDX, IDC_POSY, m_posy);
	DDX_Text(pDX, IDC_POSZ, m_posz);
	DDX_Text(pDX, IDC_ROTX, m_rotx);
	DDX_Text(pDX, IDC_ROTY, m_roty);
	DDX_Text(pDX, IDC_ROTZ, m_rotz);
	DDX_Text(pDX, IDC_SCALEX, m_scalex);
	DDX_Text(pDX, IDC_SCALEY, m_scaley);
	DDX_Text(pDX, IDC_SCALEZ, m_scalez);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPosRotScaleDlg, CDialog)
	//{{AFX_MSG_MAP(CPosRotScaleDlg)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CPosRotScaleDlg::OnButton2() 
{
	//update button

	UpdateData();

	core::vector3df pos;
	core::vector3df rot;
	core::vector3df scale;

	pos.X=atof(m_posx);
	pos.Y=atof(m_posy);
	pos.Z=atof(m_posz);

	rot.X=atof(m_rotx);
	rot.Y=atof(m_roty);
	rot.Z=atof(m_rotz);

	scale.X=atof(m_scalex);
	scale.Y=atof(m_scaley);
	scale.Z=atof(m_scalez);

	selectnode->setPosition(pos);
	selectnode->setRotation(rot);
	selectnode->setScale(scale);
	selectnode->updateAbsolutePosition();

	driver->beginScene(true,true,irr::video::SColor(255,0,0,0));
	smgr->drawAll();
	driver->endScene();
}

void CPosRotScaleDlg::OnButton1() 
{
	//ok buttton
	CDialog::OnOK();	
}
