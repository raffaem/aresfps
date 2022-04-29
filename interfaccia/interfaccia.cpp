// interfaccia.cpp : Defines the class behaviors for the application.
//


#include "stdafx.h"

#include <string>
#include <fstream>

#include "interfaccia.h"
#include "interfacciaDlg.h"
#include "LicenseDialog.h"

#include "ares_runtime_wrap.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

float ares_version;
/////////////////////////////////////////////////////////////////////////////
// CInterfacciaApp

BEGIN_MESSAGE_MAP(CInterfacciaApp, CWinApp)
	//{{AFX_MSG_MAP(CInterfacciaApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterfacciaApp construction

CInterfacciaApp::CInterfacciaApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CInterfacciaApp object

CInterfacciaApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CInterfacciaApp initialization

BOOL CInterfacciaApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	//ARES SPEC
	//get program path
	std::string prog_path=raf::GetWin32ProgramPathWithoutExtension();

	//ares version and copyright info
	ares_version=raf::GetAresVerFromConfigFile(prog_path);

	//CECK IF YOU MOVE ARES!! IF YES;UPLOAD THE REGISTRY
	std::string filename=prog_path+"\\config\\ares.reg";

	if(raf::GetAresFPSHome()=="") {
		std::string command="erase "+filename;
		system(command.c_str());
	}
	
	//REGISTRY SET
	//STEP 1: ceck if ares.reg file exist
	FILE* f = fopen(filename.c_str(), "rb");
	if (!f) {
	//the file does not exist
		CLicenseDialog d;
		d.DoModal();

	//STEP 2:Build ares.reg file
	std::ofstream ares_reg_out(filename.c_str());

	/*
	ares_reg_out<<"REGEDIT\n"
		<<"HKEY_CLASSES_ROOT\\.aresmap = AresFPSMapFile\n"
		<<"HKEY_CLASSES_ROOT\\.aresm2 = AresFPSMapFile\n"
		<<"HKEY_CLASSES_ROOT\\AresFPSMapFile\\shell\\open\\command = \""+prog_path+"\\ares.exe\" %1\n"
		<<"HKEY_CLASSES_ROOT\\AresFPSMapFile\\shell\\open\\ddeexec = [open(\"%1\")]\n"
		<<"HKEY_CLASSES_ROOT\\AresFPSMapFile\\shell\\open\\ddeexecapplication = LEVEL EDITOR.EXE\n"
		<<"HKEY_CLASSES_ROOT\\AresFPSMapFile = Ares map\n"
		<<"HKEY_CLASSES_ROOT\\MancusoRaffaele\\AresFPS\\Ver = "+raf::conv::NumString(raf::GetAresVerFromConfigFile(prog_path))+"\n"
		<<"HKEY_CLASSES_ROOT\\MancusoRaffaele\\AresFPS\\InstallDir = "+prog_path+"\n";
		ares_reg_out.close();
		*/

	ares_reg_out<<"REGEDIT\n"
		<<"HKEY_CLASSES_ROOT\\.aresmap = AresFPSMapFile\n"
		<<"HKEY_CLASSES_ROOT\\.aresm2 = AresFPSMapFile\n"
		<<"HKEY_CLASSES_ROOT\\AresFPSMapFile\\shell\\open\\command = \""+prog_path+"\\ares.exe\" %1\n"
		<<"HKEY_CLASSES_ROOT\\AresFPSMapFile = Ares map\n"
		<<"HKEY_CLASSES_ROOT\\MancusoRaffaele\\AresFPS\\Ver = "+raf::conv::NumString(ares_version)+"\n"
		<<"HKEY_CLASSES_ROOT\\MancusoRaffaele\\AresFPS\\InstallDir = "+prog_path+"\n";
	ares_reg_out.close();
	
	//STEP 3: add ares.reg information to the window registry
	std::string command="regedit.exe /s \""+filename+"\"";
	system(command.c_str());

	}//the file does not exist
	else fclose(f);
	//END OF REGISTRY SET

	//CECK PACKAGE
	filename=prog_path+"\\config\\package.txt";
	f = fopen(filename.c_str(), "rb");
	if (!f) {
		std::ofstream out(filename.c_str());
		out.close();
	}
	else fclose(f);
	//end of package

	//CECK FOR CONFIG.INI
	filename=prog_path+"\\config\\config.ini";
	FILE* test_if_exist=fopen(filename.c_str(),"r");
	if(!test_if_exist) {
		std::ofstream out(filename.c_str());
		out<<"dx9\n"
			<<"1024\n"
			<<"768\n"
			<<"32\n"
			<<"yes\n"
			<<"no\n"
			<<"no\n"
			<<"NULL\n"
			<<"no\n"
			<<"yes\n"
			<<"1\n"
			<<"cas\n"
			<<"yes\n"
			<<"city of the damned.aresm2\n"
			<<"ofq\n"
			<<"yes\n"
			<<"yes";
			out.close();
		}
	else 
		fclose(test_if_exist);
	//end of ceck

	CInterfacciaDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
