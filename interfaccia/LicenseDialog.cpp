// LicenseDialog.cpp : implementation file
//

#include "stdafx.h"
#include "interfaccia.h"
#include "LicenseDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLicenseDialog dialog


CLicenseDialog::CLicenseDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CLicenseDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLicenseDialog)
	m_license_text = _T("");
	//}}AFX_DATA_INIT
}


void CLicenseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLicenseDialog)
	DDX_Text(pDX, IDC_LICENSETEXT, m_license_text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLicenseDialog, CDialog)
	//{{AFX_MSG_MAP(CLicenseDialog)
	ON_BN_CLICKED(IDYES, OnYes)
	ON_BN_CLICKED(IDNO, OnNo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLicenseDialog message handlers
void CLicenseDialog::OnYes() 
{
	this->EndModalLoop(0);
	return;	
}

void CLicenseDialog::OnNo() 
{
	exit(0);	
}

int CLicenseDialog::DoModal() 
{
	m_license_text+="Ares FPS ,a First Shooter Person game\n";
	m_license_text+=" Copyright (C) 2006  Mancuso Raffaele\n";
    m_license_text+="This program is free software; you can redistribute it and/or modify\n";
    m_license_text+="it under the terms of the GNU General Public License as published by\n";
    m_license_text+="the Free Software Foundation; either version 2 of the License, or\n";
    m_license_text+="(at your option) any later version.\n";
    m_license_text+="This program is distributed in the hope that it will be useful,\n";
    m_license_text+="but WITHOUT ANY WARRANTY; without even the implied warranty of\n";
    m_license_text+="MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n";
    m_license_text+="GNU General Public License for more details.\n";
    m_license_text+="You should have received a copy of the GNU General Public License\n";
    m_license_text+="along with this program; if not, write to the Free Software\n";
    m_license_text+="Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA\n";
	return CDialog::DoModal();
}
