// UserDefinedSkyBox.cpp : implementation file
//

#include "stdafx.h"
#include "level editor.h"
#include "UserDefinedSkyBox.h"
#include <windows.h>
#include "evar.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//OPENFILENAME STRUCT
//HEIGHTMAP
OPENFILENAME OpenFileName;
TCHAR  szFile[MAX_PATH]      = "\0";
//strcpy( szFile, "");

/////////////////////////////////////////////////////////////////////////////
// CUserDefinedSkyBox dialog


CUserDefinedSkyBox::CUserDefinedSkyBox(CWnd* pParent /*=NULL*/)
	: CDialog(CUserDefinedSkyBox::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserDefinedSkyBox)
	m_back = _T("");
	m_bottom = _T("");
	m_front = _T("");
	m_left = _T("");
	m_right = _T("");
	m_top = _T("");
	//}}AFX_DATA_INIT

	OpenFileName.lStructSize       = sizeof(OPENFILENAME);
    OpenFileName.hwndOwner         = NULL;
    OpenFileName.hInstance         = NULL;
    OpenFileName.lpstrCustomFilter = NULL;
    OpenFileName.nMaxCustFilter    = 0;
    OpenFileName.nFilterIndex      = 0;
    OpenFileName.lpstrFile         = szFile;
    OpenFileName.nMaxFile          = sizeof(szFile);
    OpenFileName.lpstrFileTitle    = NULL;
    OpenFileName.nMaxFileTitle     = 0;
    OpenFileName.lpstrInitialDir   = NULL;
    OpenFileName.nFileOffset       = 0;
    OpenFileName.nFileExtension    = 0;
    OpenFileName.lpstrDefExt       = NULL;
    OpenFileName.lCustData         = 0;
	OpenFileName.lpfnHook 		   = NULL;
	OpenFileName.lpTemplateName    = NULL;
	OpenFileName.Flags             = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_EXPLORER|OFN_HIDEREADONLY;
	OpenFileName.lpstrFilter="BMP\0*.bmp\0JPG\0*.jpg\0TGA\0*.tga\0PCX\0*.pcx\0PNG\0*.png\0PSD\0*.psd\0Tutti i formati supportati\0*.bmp;*.jpg;*.tga;*.pcx;*.png;*.psd\0Tutti i file (*.*)\0*.*\0\0";
	OpenFileName.lpstrTitle= "";
}


void CUserDefinedSkyBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserDefinedSkyBox)
	DDX_Text(pDX, IDC_BACK_EDIT, m_back);
	DDX_Text(pDX, IDC_BOTTOM_EDIT, m_bottom);
	DDX_Text(pDX, IDC_FRONT_EDIT, m_front);
	DDX_Text(pDX, IDC_LEFT_EDIT, m_left);
	DDX_Text(pDX, IDC_RIGHT_EDIT, m_right);
	DDX_Text(pDX, IDC_TOP_EDIT, m_top);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserDefinedSkyBox, CDialog)
	//{{AFX_MSG_MAP(CUserDefinedSkyBox)
	ON_BN_CLICKED(IDC_TOP_BROWSE, OnTopBrowse)
	ON_BN_CLICKED(IDC_BOTTOM_BROWSE, OnBottomBrowse)
	ON_BN_CLICKED(IDC_LEFT_BROWSE, OnLeftBrowse)
	ON_BN_CLICKED(IDC_RIGHT_BROWSE, OnRightBrowse)
	ON_BN_CLICKED(IDC_FRONT_BROWSE, OnFrontBrowse)
	ON_BN_CLICKED(IDC_BACK_BROWSE, OnBackBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserDefinedSkyBox message handlers

void CUserDefinedSkyBox::OnOK() 
{
	this->UpdateData();	
	//get the textures
	video::ITexture* top_texture=driver->getTexture(m_top);
	video::ITexture* bottom_texture=driver->getTexture(m_bottom);
	video::ITexture* left_texture=driver->getTexture(m_left);
	video::ITexture* right_texture=driver->getTexture(m_right);
	video::ITexture* front_texture=driver->getTexture(m_front);
	video::ITexture* back_texture=driver->getTexture(m_back);

	//ceck if all texture are loaded correctly. If not return
	if(top_texture==NULL) {
		raf::errore("the top texture don't exist or it is in a unknow file format");
		return;
	}
	if(bottom_texture==NULL) {
		raf::errore("the bottom texture don't exist or it is in a unknow file format");
		return;
	}
	if(left_texture==NULL) {
		raf::errore("the left texture don't exist or it is in a unknow file format");
		return;
	}
	if(right_texture==NULL) {
		raf::errore("the right texture don't exist or it is in a unknow file format");
		return;
	}
	if(front_texture==NULL) {
		raf::errore("the front texture don't exist or it is in a unknow file format");
		return;
	}
	if(back_texture==NULL) {
		raf::errore("the back texture don't exist or it is in a unknow file format");
		return;
	}

	//erase previous sky box
	if(skyboxNode!=NULL) {
		skyboxNode->remove();
		skyboxNode=NULL;
	}

	//create the sky box
	skyboxNode=smgr->addSkyBoxSceneNode(
		top_texture,
		bottom_texture,
		left_texture,
		right_texture,
		front_texture,
		back_texture); 
	CDialog::OnOK();
}

//----------------BROWSE BUTONS------------------------------
void CUserDefinedSkyBox::OnTopBrowse() 
{
	OpenFileName.lpstrTitle="Choose a image for the top of the sky box";
	if(GetOpenFileName(&OpenFileName)==FALSE) {
		string err="errore numero ";
		DWORD errore_numero=CommDlgExtendedError();
		err+=raf::conv::NumString(errore_numero);

		if(errore_numero==0) {
			//non ha selezionato nessun file
			return;
		}	
		
		raf::errore(err);
	}
	m_top=OpenFileName.lpstrFile;
	this->UpdateData(FALSE);	
}

void CUserDefinedSkyBox::OnBottomBrowse() 
{
	OpenFileName.lpstrTitle="Choose a image for the bottom of the sky box";
	if(GetOpenFileName(&OpenFileName)==FALSE) {
		string err="errore numero ";
		DWORD errore_numero=CommDlgExtendedError();
		err+=raf::conv::NumString(errore_numero);

		if(errore_numero==0) {
			//non ha selezionato nessun file
			return;
		}	
		
		raf::errore(err);
	}
	m_bottom=OpenFileName.lpstrFile;
	this->UpdateData(FALSE);
	
}

void CUserDefinedSkyBox::OnLeftBrowse() 
{
	OpenFileName.lpstrTitle="Choose a image for the left of the sky box";
	if(GetOpenFileName(&OpenFileName)==FALSE) {
		string err="errore numero ";
		DWORD errore_numero=CommDlgExtendedError();
		err+=raf::conv::NumString(errore_numero);

		if(errore_numero==0) {
			//non ha selezionato nessun file
			return;
		}	
		
		raf::errore(err);
	}
	m_left=OpenFileName.lpstrFile;
	this->UpdateData(FALSE);
	
}

void CUserDefinedSkyBox::OnRightBrowse() 
{
	OpenFileName.lpstrTitle="Choose a image for the right of the sky box";
	if(GetOpenFileName(&OpenFileName)==FALSE) {
		string err="errore numero ";
		DWORD errore_numero=CommDlgExtendedError();
		err+=raf::conv::NumString(errore_numero);

		if(errore_numero==0) {
			//non ha selezionato nessun file
			return;
		}	
		
		raf::errore(err);
	}
	m_right=OpenFileName.lpstrFile;
	this->UpdateData(FALSE);
	
}

void CUserDefinedSkyBox::OnFrontBrowse() 
{
	OpenFileName.lpstrTitle="Choose a image for the front of the sky box";
	if(GetOpenFileName(&OpenFileName)==FALSE) {
		string err="errore numero ";
		DWORD errore_numero=CommDlgExtendedError();
		err+=raf::conv::NumString(errore_numero);

		if(errore_numero==0) {
			//non ha selezionato nessun file
			return;
		}	
		
		raf::errore(err);
	}
	m_front=OpenFileName.lpstrFile;
	this->UpdateData(FALSE);
	
}

void CUserDefinedSkyBox::OnBackBrowse() 
{
	OpenFileName.lpstrTitle="Choose a image for the back of the sky box";
	if(GetOpenFileName(&OpenFileName)==FALSE) {
		string err="errore numero ";
		DWORD errore_numero=CommDlgExtendedError();
		err+=raf::conv::NumString(errore_numero);

		if(errore_numero==0) {
			//non ha selezionato nessun file
			return;
		}	
		
		raf::errore(err);
	}
	m_back=OpenFileName.lpstrFile;
	this->UpdateData(FALSE);
}
