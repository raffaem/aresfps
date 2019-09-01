//TEST
#include <string>
#include <windows.h>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

/*
//THIS FUNCTION RUN BUT I DON'T NEED IT FOR THIS INSTALLER
float GetAresFPSVer() {
	HKEY open_key;
	DWORD type;
	DWORD size_of_data=2000;
	char* data=new char[2000];
	RegOpenKeyExA(
		HKEY_CLASSES_ROOT,
		"MancusoRaffaele\\AresFPS\\Ver",
		0,//reserved
		KEY_QUERY_VALUE,
		&open_key);
	RegQueryValueExA(
		open_key,
		"",//value to query
		NULL,//reserved
		&type,
		(unsigned char*)data,
		&size_of_data);
	RegCloseKey(open_key);
	string returned(data);
	delete data;
	return atof(returned.c_str());
}
*/

string GetAresFPSHome() {
	HKEY open_key;
	DWORD type;
	DWORD size_of_data=2000;
	char* data=new char[2000];
	RegOpenKeyExA(
		HKEY_CLASSES_ROOT,
		"MancusoRaffaele\\AresFPS\\InstallDir",
		0,//reserved
		KEY_QUERY_VALUE,
		&open_key);
	RegQueryValueExA(
		open_key,
		"",//value to query
		NULL,//reserved
		&type,
		(unsigned char*)data,
		&size_of_data);
	RegCloseKey(open_key);
	string returned(data);
	delete data;
	//ceck if the path is correct
	string ares_game_exe_path=returned+"\\ares_game.exe";
	FILE* f=fopen(ares_game_exe_path.c_str(),"rb");
	if(!f) {
		//fail!
		string message="The path into the registry is not the path of Ares. You probabily move Ares into another directory and not upload the registry. To upload the registry, is sufficient to start Ares and press exit. Ares will automatically realize the change and upload the registry. After please re-start this program to install the package correctly. The package is not installed. Press ok to exit";
		MessageBoxA(NULL,message.c_str(),"Error",MB_SYSTEMMODAL|MB_OK);
		exit(-1);
	}
	else fclose(f);
	return returned;
}
void RegisterPackage(string ares_home,string package_name) {
	string package_txt_string=ares_home+"\\package.txt";
	string temp;
	vector<string> s;
	ifstream in(package_txt_string.c_str());
	while(getline(in,temp))
		s.push_back(temp);
	s.push_back(package_name);
	in.close();
	ofstream out(package_txt_string.c_str());
	for(int i=0;i<s.size();i++) 
		out<<s[i]<<"\n";
	out.close();
}
void CopyFileToAres(string ares_home,string file_to_copy) {
	string command="copy "+file_to_copy+" "+ares_home;
	system(command.c_str());

	//ceck if file exist
	string new_file=ares_home+"\\"+file_to_copy;
	FILE* s=fopen(new_file.c_str(),"rb");
	if(!s) {
		//fail!
		string message="Fail to copy the file "+file_to_copy+" to Ares home ("+ares_home+"). The package is not installed correctly. Please try to reinstall it. Press ok to exit";
		MessageBoxA(NULL,message.c_str(),"Error",MB_SYSTEMMODAL|MB_OK);
		exit(-1);
	}
	else fclose(s);
}
void ShowSuccessInstMsg() {
	MessageBoxA(NULL,"The package is correctly installed. Press ok","Install finish",MB_SYSTEMMODAL|MB_OK);
}

int WINAPI WinMain(HINSTANCE h,HINSTANCE p,LPSTR cmdline,int show) {
	string ares_home=GetAresFPSHome();
	CopyFileToAres(ares_home,"main.exe");
	RegisterPackage(ares_home,"Stdpkg FMOD Codecs");
	ShowSuccessInstMsg();
	return 0;
}
