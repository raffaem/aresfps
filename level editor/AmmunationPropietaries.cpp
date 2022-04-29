// AmmunationPropietaries.cpp : implementation file
//

#include "stdafx.h"
#include "level editor.h"
#include "AmmunationPropietaries.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAmmunationPropietaries dialog


CAmmunationPropietaries::CAmmunationPropietaries(CWnd* pParent /*=NULL*/)
	: CDialog(CAmmunationPropietaries::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAmmunationPropietaries)
	m_num_of_bullet = _T("");
	//}}AFX_DATA_INIT

	//get id of a select node
	string ID=raf::conv::NumString(selectnode->getID());
	char type=ID[0];
	string pos_string=raf::String::SubString(ID,1,ID.size()-1);
	int pos=atoi(pos_string.c_str());
	m_num_of_bullet=raf::conv::NumString(ammunation[pos]->num_of_bullets).c_str();
}


void CAmmunationPropietaries::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAmmunationPropietaries)
	DDX_Text(pDX, IDC_NUM_OF_BULLET, m_num_of_bullet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAmmunationPropietaries, CDialog)
	//{{AFX_MSG_MAP(CAmmunationPropietaries)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAmmunationPropietaries message handlers

void CAmmunationPropietaries::OnOK() 
{
	this->UpdateData();
	string ID=raf::conv::NumString(selectnode->getID());
	string pos_string=raf::String::SubString(ID,1,ID.size()-1);
	int pos=atoi(pos_string.c_str());
	ammunation[pos]->num_of_bullets=atoi(m_num_of_bullet);
	CDialog::OnOK();
}
