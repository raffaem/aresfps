// InsertModelFromZipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "level editor.h"
#include "InsertModelFromZipDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsertModelFromZipDlg dialog


CInsertModelFromZipDlg::CInsertModelFromZipDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInsertModelFromZipDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInsertModelFromZipDlg)
	m_zipfile = _T("");
	m_model = _T("");
	m_texture = _T("");
	//}}AFX_DATA_INIT
}


void CInsertModelFromZipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsertModelFromZipDlg)
	DDX_Text(pDX, IDC_ZIPFILE, m_zipfile);
	DDX_Text(pDX, IDC_MODEL, m_model);
	DDX_Text(pDX, IDC_TEXTURE, m_texture);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsertModelFromZipDlg, CDialog)
	//{{AFX_MSG_MAP(CInsertModelFromZipDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsertModelFromZipDlg message handlers

void CInsertModelFromZipDlg::OnOK() 
{
	UpdateData();

	//test if exist
	if(!device->getFileSystem()->existFile(m_zipfile)) {
		MessageBox("Zip file does not exist","Error");
		return;
	}
	//if yes add
	device->getFileSystem()->addZipFileArchive(m_zipfile);
	std::string zipfile_cppstring(m_zipfile);

	//ceck if model exist
	std::string zip_file_path=raf::String::EraseFileNameFromPath(zipfile_cppstring);
	std::string model_full_path=zip_file_path+"\\";

	const char* model_filename_cstring=m_model;
	std::string model_file_name_cppstring(model_filename_cstring);
	model_full_path+=model_file_name_cppstring;

	if(!device->getFileSystem()->existFile(model_full_path.c_str())) {
		MessageBox("Model file does not exist","Error");
		return;
	}

	//ceck if texture exist
	//ceck if model exist
	std::string texture_full_path=zip_file_path+"\\";

	const char* texture_filename_cstring=m_texture;
	std::string texture_file_name_cppstring(model_filename_cstring);
	texture_full_path+=texture_file_name_cppstring;

	if(texture_file_name_cppstring=="") {
		texture_full_path="noTexture";
	}

	if(texture_full_path!="noTexture"&&
		!device->getFileSystem()->existFile(model_full_path.c_str())) {
		MessageBox("Texture file does not exist","Error");
		return;
	}

	AddLevelModel(
		model_full_path,//model
		texture_full_path,//texture
		core::vector3df(0,0,0),//pos
		core::vector3df(0,0,0),//rot
		core::vector3df(1,1,1)//scale
		);

	zip_files.push_back(zipfile_cppstring);
	CDialog::OnOK();
}

void CInsertModelFromZipDlg::OnButton1() 
{
	OPENFILENAME OpenFileName;
	TCHAR         szFile[MAX_PATH]      = "\0";
	strcpy( szFile, "");
	OpenFileName.lStructSize       = sizeof(OPENFILENAME);
    OpenFileName.hwndOwner         = NULL;
    OpenFileName.hInstance         = NULL;
    OpenFileName.lpstrFilter       = "Zip (.zip) \0*.zip\0BZip2 (.bz2) \0*.bz2\0All supported files format (*.zip *.bz2)\0*.zip;*.bz2\0All files (*.*)\0*.*\0\0";
    OpenFileName.lpstrCustomFilter = NULL;
    OpenFileName.nMaxCustFilter    = 0;
    OpenFileName.nFilterIndex      = 0;
    OpenFileName.lpstrFile         = szFile;
    OpenFileName.nMaxFile          = sizeof(szFile);
    OpenFileName.lpstrFileTitle    = NULL;
    OpenFileName.nMaxFileTitle     = 0;
    OpenFileName.lpstrInitialDir   = NULL;
    OpenFileName.lpstrTitle        = "Open a zip file";
    OpenFileName.nFileOffset       = 0;
    OpenFileName.nFileExtension    = 0;
    OpenFileName.lpstrDefExt       = NULL;
    OpenFileName.lCustData         = 0;
	OpenFileName.lpfnHook 		   = NULL;
	OpenFileName.lpTemplateName    = NULL;
    OpenFileName.Flags             = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_EXPLORER|OFN_HIDEREADONLY;


	if(GetOpenFileName(&OpenFileName)==FALSE) {
		string err="errore numero ";
		DWORD errore_numero=CommDlgExtendedError();
		err+=raf::conv::NumString(errore_numero);

		if(errore_numero==0) {
			return;
		}	
		
		MessageBox(err.c_str(),"error",MB_SYSTEMMODAL);
	};

	m_zipfile=OpenFileName.lpstrFile;
	UpdateData(FALSE);
	return;
}
