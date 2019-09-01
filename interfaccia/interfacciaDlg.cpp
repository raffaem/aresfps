// interfacciaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "interfaccia.h"
#include "interfacciaDlg.h"

#include <fstream>
#include <vector>
#include <string>
#include <sstream> 

#include <io.h>
#include <fcntl.h>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool sequentially=false;
extern float ares_version;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterfacciaDlg dialog

CInterfacciaDlg::CInterfacciaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInterfacciaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInterfacciaDlg)
	m_antialias = FALSE;
	m_fullscreen = FALSE;
	m_play_ut = FALSE;
	m_stencylbuffer = FALSE;
	m_utvolume = _T("");
	m_vsync = FALSE;
	m_res = _T("");
	m_boc = -1;
	m_render = -1;
	m_uthowtoplay = -1;
	m_level_to_start = -1;
	m_default_level_to_start_val = FALSE;
	m_user_level_to_start_val = FALSE;
	m_extern_level_val = _T("");
	m_texturequality = -1;
	m_ares_cop_info = _T("");
	m_specularhightlights = FALSE;
	m_hightprecisionfpu = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_ares_cop_info="Ares ver. ";
	m_ares_cop_info+=raf::conv::NumString(ares_version).c_str();
	m_ares_cop_info+=" by Mancuso Raffaele\nCopyright (C) 2006 Mancuso Raffaele";
}

void CInterfacciaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInterfacciaDlg)
	DDX_Control(pDX, IDC_USER_LEVEL_TO_START, m_user_level_to_start_c);
	DDX_Control(pDX, IDC_DEFAULT_LEVEL_TO_START, m_default_level_to_start_c);
	DDX_Control(pDX, IDC_LEVEL_TO_START, m_level_to_start_c);
	DDX_Check(pDX, IDC_ANTIALIAS, m_antialias);
	DDX_Check(pDX, IDC_FULLSCREEN, m_fullscreen);
	DDX_Check(pDX, IDC_PLAY_UT, m_play_ut);
	DDX_Check(pDX, IDC_STENCYLBUFFER, m_stencylbuffer);
	DDX_Text(pDX, IDC_UTVOLUME, m_utvolume);
	DDX_Check(pDX, IDC_VSYNC, m_vsync);
	DDX_CBString(pDX, IDC_RESOLUTION, m_res);
	DDX_CBIndex(pDX, IDC_BIT_OF_COLOUR, m_boc);
	DDX_CBIndex(pDX, IDC_RENDER, m_render);
	DDX_CBIndex(pDX, IDC_UTHOWTOPLAY, m_uthowtoplay);
	DDX_CBIndex(pDX, IDC_LEVEL_TO_START, m_level_to_start);
	DDX_Check(pDX, IDC_DEFAULT_LEVEL_TO_START, m_default_level_to_start_val);
	DDX_Check(pDX, IDC_USER_LEVEL_TO_START, m_user_level_to_start_val);
	DDX_Text(pDX, IDC_EXTER_LEVEL_EDIT, m_extern_level_val);
	DDX_CBIndex(pDX, IDC_TEXTUREQUALITYCOMBOBOX, m_texturequality);
	DDX_Text(pDX, IDC_ARESCOPINFO, m_ares_cop_info);
	DDX_Check(pDX, IDC_SPECULARHIGHTLIGHTS, m_specularhightlights);
	DDX_Check(pDX, IDC_HIGHTPRECISIONFPU, m_hightprecisionfpu);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInterfacciaDlg, CDialog)
	//{{AFX_MSG_MAP(CInterfacciaDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnOpenUserTracksDirectory)
	ON_BN_CLICKED(ID_OPENLEVELEDITOR, OnOpenleveleditor)
	ON_BN_CLICKED(IDC_DEFAULT_LEVEL_TO_START, OnDefaultLevelToStart)
	ON_BN_CLICKED(IDC_USER_LEVEL_TO_START, OnUserLevelToStart)
	ON_BN_CLICKED(IDC_USER_LEVEL_BROWSE, OnUserLevelBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterfacciaDlg message handlers
extern CInterfacciaApp theApp;

BOOL CInterfacciaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//inizializza
	//LETTURA DELLE IMPOSTAZIONI
	string config_ini_file=raf::GetWin32ProgramPathWithoutExtension()+"\\config\\config.ini";
	string a;
	vector<string> v;
	ifstream in(config_ini_file.c_str());
	string temp;
	string device_sett;
	//bool antialias;

	while(getline(in,temp))
		v.push_back(temp);
	device_sett=v[0];

	m_res=v[1].c_str();
	m_res+="x";
	m_res+=v[2].c_str();

	if(v[3]=="16")
		m_boc=0;
	else
		m_boc=1;

	a=v[4];//fullscreen
	if(a=="yes") {m_fullscreen=TRUE;}
	else if(a=="no") {m_fullscreen=FALSE;}
	a=v[5];//stencylbuffer
	if(a=="yes") {m_stencylbuffer=TRUE;}
	else if(a=="no") {m_stencylbuffer=FALSE;}
	a=v[6];//vsync
	if(a=="yes") {m_vsync=TRUE;}
	else if(a=="no") {m_vsync=FALSE;}
	a=v[8];//antialias
	if(a=="yes") {m_antialias=TRUE;}
	else if(a=="no") {m_antialias=FALSE;}

	//crea il device
	if(device_sett=="dx9") {
		m_render=0;
	}
	else if(device_sett=="dx8") {
		m_render=1;
	}
	else if(device_sett=="ogl") {
		m_render=2;
	}
	else if(device_sett=="soft2") {
		m_render=3;
	}
	else if(device_sett=="soft") {
		m_render=4;
	}

	//level
	string temp1=raf::GetWin32ProgramPathWithoutExtension()+"\\levels\\*.aresmap";
	string temp2=raf::GetWin32ProgramPathWithoutExtension()+"\\levels\\*.aresm2";

	m_level_to_start_c.Dir(DDL_READONLY,temp1.c_str());
	m_level_to_start_c.Dir(DDL_READONLY,temp2.c_str());
	int cur_sel=0;

	if(v[12]=="yes") {
		cur_sel=m_level_to_start_c.FindStringExact(0,v[13].c_str());
		if(cur_sel<0) cur_sel=0;
	}
	else{
		FILE* in=fopen(v[13].c_str(),"r");
		if(in) {
			fclose(in);
			m_extern_level_val=v[13].c_str();
		}//if(in){
	}//else{

	//play background music
	a=v[9];
	if(a=="yes") {m_play_ut=TRUE;}
	else if(a=="no") {m_play_ut=FALSE;}

	//background music volume
	m_utvolume+=v[10].c_str();

	//how to play back music
	if(v[11]=="cas")
		m_uthowtoplay=0;
	else if(v[11]=="seq")
		m_uthowtoplay=1;

	//texture quality
	if(v[14]=="ofq") //optimize for quality
		m_texturequality=0;
	else if(v[14]=="ofs") //optimize for speed
		m_texturequality=1;
	else if(v[14]=="32") //32bit
		m_texturequality=2;
	else if(v[14]=="16") //16bit
		m_texturequality=3;

	//specular hightlights
	if(v[15]=="yes") m_specularhightlights=TRUE;
	else m_specularhightlights=FALSE;

	//specular hightlights
	if(v[16]=="yes") m_hightprecisionfpu=TRUE;
	else m_hightprecisionfpu=FALSE;

	//fine inizializza
	m_default_level_to_start_val=TRUE;
	m_user_level_to_start_val=FALSE;
	this->UpdateData(FALSE);//aggiorna

	m_level_to_start_c.SetCurSel(cur_sel);//altrimenti all'inizio il combo box sarebbe vuoto causando un crash
	if(v[12]=="yes") {
		m_default_level_to_start_c.SetCheck(TRUE);
		m_user_level_to_start_c.SetCheck(FALSE);
	}
	else {
		m_default_level_to_start_c.SetCheck(FALSE);
		m_user_level_to_start_c.SetCheck(TRUE);
	}

	//COMMAND LINE
	/*
	CCommandLineInfo cmdInfo;
	theApp.ParseCommandLine(cmdInfo);
	if(cmdInfo.m_nShellCommand==CCommandLineInfo::FileOpen) {
		m_extern_level_val=cmdInfo.m_strFileName;
		this->UpdateData(FALSE);

		m_level_to_start_c.SetCurSel(cur_sel);//altrimenti all'inizio il combo box sarebbe vuoto causando un crash
		m_default_level_to_start_c.SetCheck(FALSE);
		m_user_level_to_start_c.SetCheck(TRUE);
	}
	*/

	//COMMAND LINE
	std::string cmdline=GetCommandLineA();
	int pos=cmdline.find("\"");
	pos=cmdline.find("\"",pos+1);
	cmdline.erase(0,pos+2);
	if(cmdline!="") {
		if(cmdline[0]==' ')
			cmdline.erase(0,1);
	}
	if(cmdline!=""&&
		!raf::IsFileExist(cmdline)) {
		std::string message="Error. The file "+cmdline+" does not exist. Click ok to continue";
		MessageBox(message.c_str(),NULL,MB_OK|MB_SYSTEMMODAL);
		cmdline="";
	}
	if(cmdline!="") {
		m_extern_level_val=cmdline.c_str();
		this->UpdateData(FALSE);
		m_level_to_start_c.SetCurSel(cur_sel);//altrimenti all'inizio il combo box sarebbe vuoto causando un crash
		m_default_level_to_start_c.SetCheck(FALSE);
		m_user_level_to_start_c.SetCheck(TRUE);
	}
	//END OF COMMAND LINE

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInterfacciaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CInterfacciaDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CInterfacciaDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//-----------------------------------------------------------------
#include <string>
using namespace std;
void CInterfacciaDlg::OnOK() 
{
	this->UpdateData();
	//back music
	float back_m_v=atof(((string)m_utvolume).c_str());
	if(back_m_v>1.0f||
		back_m_v<0.0f) {
		MessageBoxA("Error. Background music volume value must be in a value between 0.0 and 1.0","Error",MB_SYSTEMMODAL);
		UpdateData(FALSE);
		return;
	}


	CString ris1,ris2;
	//codice per etrarre da m_res le singole risoluzioni
	//alla fine del codice ris1 conterrà la prima risoluzione
	//e ris2 la seconda
	//es. m_res=800x600 ris1=800 ris2=600
	int i=m_res.Find("x");
	CString temp_ris=m_res;
	int grandezza=temp_ris.GetLength()-1;
	int caratteri=(grandezza-i)+1;
	temp_ris.Delete(i,caratteri);
	ris1=temp_ris;
	temp_ris=m_res;
	temp_ris.Delete(0,i+1);
	ris2=temp_ris;
	//fine del codice
	//ora ris1 e ris2 sono corretti

	string fpuhightprecision,use_default_level,fullscreen,vsync,stencyl,antialias,play_b_m,sequentially_to_write,boc_to_write,shl_to_write;
	if(m_fullscreen==TRUE) {fullscreen="yes";}
	else if(m_fullscreen==FALSE) {fullscreen="no";}

	if(m_stencylbuffer==TRUE) {stencyl="yes";}
	else if(m_stencylbuffer==FALSE) {stencyl="no";}

	if(m_vsync==TRUE) {vsync="yes";}
	else if(m_vsync==FALSE) {vsync="no";}

	if(m_antialias==TRUE) {antialias="yes";}
	else if(m_antialias==FALSE) {antialias="no";}

	if(m_play_ut==TRUE) {play_b_m="yes";}
	else if(m_play_ut==FALSE) {play_b_m="no";}

	if(m_uthowtoplay==0) {sequentially_to_write="cas";}
	else if(m_uthowtoplay==1) {sequentially_to_write="seq";}

	if(m_user_level_to_start_val==TRUE) {use_default_level="no";}
	else {use_default_level="yes";}

	if(m_specularhightlights==TRUE) {shl_to_write="yes";}
	else {shl_to_write="no";}

	if(m_hightprecisionfpu==TRUE) {fpuhightprecision="yes";}
	else {fpuhightprecision="no";}
	
	string device;
	if(m_render==0) {device="dx9";}
	else if(m_render==1) {device="dx8";}
	else if(m_render==2) {device="ogl";}
	else if(m_render==3) {device="soft2";}
	else if(m_render==4) {device="soft";}
	
	if(m_boc==0)
		boc_to_write="16";
	else
		boc_to_write="32";

	//LEVEL TO START
	string level_to_start;
	if(use_default_level=="yes") {
		LPTSTR s=new char[5000];
		m_level_to_start_c.GetLBText(m_level_to_start,s);
		level_to_start=s;
		delete s;
	}
	else {
		//ceck if the file exist
		string filename=m_extern_level_val;
		int f = _open(filename.c_str(), _O_RDONLY);
		if (f!=-1) {
			_close(f);
			//the file exist
			level_to_start=filename;
		}
		else {
			//the file does not exist
			this->MessageBox("The file selected in \"extern level\" does not exist, Please click on browse to select an exist file or click on \"Default level\" to load a default level","error");
			return;
		}
	}
	//END OF LEVEL TO START

	//texture quality string
	string texture_quality_to_write;

	if(m_texturequality==0) //optimize for quality
		texture_quality_to_write="ofq";

	else if(m_texturequality==1) //optimize for speed
		texture_quality_to_write="ofs";

	else if(m_texturequality==2) //32bit
		texture_quality_to_write="32";

	else if(m_texturequality==3) //16bit
		texture_quality_to_write="16";

	else{
		MessageBox("error at texture quality");
		exit(-1);
	}


	ostringstream back_m_v_s;back_m_v_s<<back_m_v;
	
	string config_ini_file=raf::GetWin32ProgramPathWithoutExtension()+"\\config\\config.ini";
	ofstream out(config_ini_file.c_str());

	out<<device
		<<endl
		<<(string)ris1
		<<endl
		<<(string)ris2
		<<endl
		<<boc_to_write
		<<endl
		<<fullscreen
		<<endl
		<<stencyl
		<<endl
		<<vsync
		<<endl
		<<"NULL"
		<<endl
		<<antialias
		<<endl
		<<play_b_m
		<<endl
		<<back_m_v_s.str()
		<<endl
		<<sequentially_to_write
		<<endl
		<<use_default_level
		<<endl
		<<level_to_start
		<<endl
		<<texture_quality_to_write
		<<endl
		<<shl_to_write
		<<endl
		<<fpuhightprecision;

	out.close();

	UpdateData(FALSE);

	string command="\""+raf::GetWin32ProgramPathWithoutExtension()+"\\bin\\ares_game.exe"+"\"";
	system(command.c_str());
}

void CInterfacciaDlg::OnOpenUserTracksDirectory() 
{
	string command="explorer.exe "+raf::GetWin32ProgramPathWithoutExtension()+"\\tracks"+"\"";
	system(command.c_str());
	
}

void CInterfacciaDlg::OnOpenleveleditor() 
{
	if(!raf::CeckPackage(raf::GetWin32ProgramPathWithoutExtension(),"Stdpkg Ares ufficial level editor")) {
		MessageBoxA("Ares' level editor was not installed. Since version 0.3 you need to download the level editor separately. To download it open ares homeapge at this web-site : http://aresfps.sf.net and click on tools button. Click ok to return to the interface","Error",MB_SYSTEMMODAL|MB_OK);
		return;
	}

	this->UpdateData();
	string command="\""+raf::GetWin32ProgramPathWithoutExtension()+"\\bin\\level editor.exe"+"\"";

	if(m_user_level_to_start_val==TRUE) {
		command+=" \""+m_extern_level_val+"\"";
	}

	system(command.c_str());
	system("pause");
}

void CInterfacciaDlg::OnDefaultLevelToStart() 
{
	this->UpdateData(TRUE);
	int cur=m_level_to_start_c.GetCurSel();

	m_default_level_to_start_val=TRUE;
	m_user_level_to_start_val=FALSE;
	this->UpdateData(FALSE);	

	m_level_to_start_c.SetCurSel(cur);
}

void CInterfacciaDlg::OnUserLevelToStart() 
{
	this->UpdateData(TRUE);
	int cur=m_level_to_start_c.GetCurSel();

	m_default_level_to_start_val=FALSE;
	m_user_level_to_start_val=TRUE;
	this->UpdateData(FALSE);	

	m_level_to_start_c.SetCurSel(cur);
}

void CInterfacciaDlg::OnUserLevelBrowse() 
{
	this->UpdateData(TRUE);
	int cur=m_level_to_start_c.GetCurSel();

	OPENFILENAME OpenFileName;
	TCHAR  szFile[MAX_PATH]      = "\0";
    strcpy( szFile, "");

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
	OpenFileName.lpstrFilter="Ares 0.2 level (*.aresm2)\0*.aresm2\0Ares 0.1 level (*.aresmap)\0*.aresmap\0All supported file formats (*.aresmap,*.aresm2)\0*.aresmap;*.aresm2\0All files (*.*)\0*.*\0\0";
    OpenFileName.lpstrTitle= "Choose a level";

	if(GetOpenFileName(&OpenFileName)==FALSE) {
		DWORD errore_numero=CommDlgExtendedError();
		if(errore_numero==0) {
			//non ha selezionato nessun file
			return;
		}			
	};

	m_extern_level_val=OpenFileName.lpstrFile;
	m_default_level_to_start_val=FALSE;
	m_user_level_to_start_val=TRUE;
	this->UpdateData(FALSE);	

	m_level_to_start_c.SetCurSel(cur);
}
