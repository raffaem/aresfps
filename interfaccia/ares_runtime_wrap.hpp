#ifndef MANCUSO_RAFFAELE_ARES_INTERFACCIA_ARES_RUNTIME_WRAP_HPP_CODE_1351681651319849684980495019849
#define MANCUSO_RAFFAELE_ARES_INTERFACCIA_ARES_RUNTIME_WRAP_HPP_CODE_1351681651319849684980495019849
#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <vector>

namespace raf{
	namespace conv{
		//!Convert a number into a string
		template<class Num> std::string NumString(Num num) {
			std::ostringstream stringa;
			stringa<<num;
			return stringa.str();
		}//NumString
	}//namespace conv

	std::string GetWin32ProgramPathWithoutExtension();
	bool IsFileExist(std::string file);

	//ARES SPECIFIC FUNCTION
	float GetAresVerFromConfigFile(std::string ares_home);
	std::string GetAresFPSHome();
	bool CeckPackage(std::string ares_home,std::string package_name);
}//namespace raf
#endif