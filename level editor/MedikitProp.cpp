// MedikitProp.cpp : implementation file
//

#include "stdafx.h"
#include "level editor.h"
#include "MedikitProp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMedikitProp dialog


CMedikitProp::CMedikitProp(CWnd* pParent /*=NULL*/)
	: CDialog(CMedikitProp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMedikitProp)
	m_life_value = _T("");
	//}}AFX_DATA_INIT

	//get id of a select node
	string ID=raf::conv::NumString(selectnode->getID());
	char type=ID[0];
	string pos_string=raf::String::SubString(ID,1,ID.size()-1);
	int pos=atoi(pos_string.c_str());
	m_life_value=raf::conv::NumString(medikits[pos].life).c_str();

}


void CMedikitProp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMedikitProp)
	DDX_Text(pDX, IDC_LIFEVALUE, m_life_value);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMedikitProp, CDialog)
	//{{AFX_MSG_MAP(CMedikitProp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedikitProp message handlers

void CMedikitProp::OnOK() 
{
	this->UpdateData();
	string ID=raf::conv::NumString(selectnode->getID());
	string pos_string=raf::String::SubString(ID,1,ID.size()-1);
	int pos=atoi(pos_string.c_str());
	medikits[pos].life=atoi(m_life_value);

	CDialog::OnOK();
}
