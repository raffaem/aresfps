// ArmourProp.cpp : implementation file
//

#include "stdafx.h"
#include "level editor.h"
#include "ArmourProp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArmourProp dialog


CArmourProp::CArmourProp(CWnd* pParent /*=NULL*/)
	: CDialog(CArmourProp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CArmourProp)
	m_num_of_armour = _T("");
	//}}AFX_DATA_INIT
	//get id of a select node
	string ID=raf::conv::NumString(selectnode->getID());
	char type=ID[0];
	string pos_string=raf::String::SubString(ID,1,ID.size()-1);
	int pos=atoi(pos_string.c_str());
	m_num_of_armour=raf::conv::NumString(armours[pos].armour).c_str();

}


void CArmourProp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArmourProp)
	DDX_Text(pDX, IDC_NUM_OF_BULLET, m_num_of_armour);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArmourProp, CDialog)
	//{{AFX_MSG_MAP(CArmourProp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArmourProp message handlers

void CArmourProp::OnOK() 
{
	this->UpdateData();
	string ID=raf::conv::NumString(selectnode->getID());
	string pos_string=raf::String::SubString(ID,1,ID.size()-1);
	int pos=atoi(pos_string.c_str());
	armours[pos].armour=atoi(m_num_of_armour);
	CDialog::OnOK();

}
