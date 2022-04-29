#include "stdafx.h"

//ARES SPECIFIC FUNCTION
std::string raf::GetAresFPSHome() {
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
	//ceck if the key don't exist
	if(!open_key) {
		return "";
	}

	RegQueryValueExA(
		open_key,
		"",//value to query
		NULL,//reserved
		&type,
		(unsigned char*)data,
		&size_of_data);
	RegCloseKey(open_key);
	std::string returned(data);
	delete data;

	//ceck if the path is correct
	std::string ares_game_exe_path=returned+"\\bin\\ares_game.exe";
	FILE* f=fopen(ares_game_exe_path.c_str(),"rb");
	if(!f) {
		//fail!
		return "";
	}
	else fclose(f);
	return returned;
}
bool raf::CeckPackage(std::string ares_home,std::string package_name) {
	//insert package.txt into a vector
	std::string filename=ares_home+"\\config\\package.txt";
	std::ifstream pkg_file(filename.c_str());
	std::vector<std::string> s;
	std::string temp;
	while(std::getline(pkg_file,temp))
		s.push_back(temp);
	pkg_file.close();
	//end of insert package.txt into a vector

	for(int i=0;i<s.size();i++) {
		if(s[i]==package_name) return true;
	}
	return false;
}
float raf::GetAresVerFromConfigFile(std::string ares_home) {
	std::string filename=ares_home+="\\config\\ares_ver.txt";
	std::ifstream in(filename.c_str());
	std::string ver_string;
	std::getline(in,ver_string);
	in.close();
	float ver=atof(ver_string.c_str());
	return ver;
}

std::string raf::GetWin32ProgramPathWithoutExtension() {
	std::string cml=GetCommandLine();
	int pos=cml.find_first_of('\"',1);
	++pos;
	if(pos>0) {
		cml.erase(pos,(cml.size()-pos));
	}
	//erase extension
	pos=cml.find_last_of('\\');
	cml.erase(pos,(cml.size()-pos));
	cml.erase(0,1);
	return cml;
}

bool raf::IsFileExist(std::string file) {
	FILE* in=fopen(file.c_str(),"rb");
	if(in) {
		//the file exist
		fclose(in);
		return true;
	}
	else return false;
}
