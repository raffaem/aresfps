/*
PLEASE DON'T DELETE THIS NOTE IF YOU REDISTRIBUTE THIS PROGRAM

This file is a part of Ares, a first person shooter (fps) game 
based on irrlicht engine

Copyright (C) 2006  Mancuso Raffaele

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

Ares web-site: http://aresfps.sourceforge.net
Ares e-mail: ares_support@virgilio.it
*/
#ifndef MANCUSO_RAFFAELE_ARES_RUNTIME_FILE_CLASS_84368716541384138
#define MANCUSO_RAFFAELE_ARES_RUNTIME_FILE_CLASS_84368716541384138

#include "dll_exports.hpp"
#include <string>
#include <fstream>
#include <vector>

namespace raf{
	class ARES_API file {
	public:
		raf::file() {}
		raf::file(std::string file) {this->Open(file);}
		
		//copy constructor
		raf::file(const raf::file& f) {
			this->righe_file=f.GetVector();
			this->size_of_file=f.GetFileSize();
			this->filename=f.GetFileName();
		}

		//GET FUNCTIONS
		inline std::vector<std::string> GetVector() const  {
			return this->righe_file;
		}
		inline int GetFileSize()const {
			return this->size_of_file;
		}
		inline std::string GetFileName() const {return this->filename;}
		int GetRecordNumber();
		std::string GetRecord();

		//ERROR FUNCTIONS
		bool IsExist(std::string file);
		bool IsExistFatal(std::string file);
		void ComandoNonValidoFatal(std::string comando);
		void ComandoNonValidoFatal();

		//OTHER FUNCTIONS
		bool Open(std::string name_of_file);//costruttore
		void Close();
		void find_in_file(std::string stringa_da_cercare,std::vector<int>& riga,std::vector<int> & inizio, std::vector<int>& fine);
		void SetRecordNumber(int new_record);
		std::string ReadCommand();
		std::string ReadCommand(int& position_space);
		void Read3dVector(char carattere_separatore,double& num1,double& num2,double& num3);
		std::string RigaAttuale();
		std::string RigaAttualeSubString(int inizio,int fine);
		std::string RigaAttualeSubString(int inizio);
		void FindInRecord(std::string car,std::vector<int>& inizio,std::vector<int>& fine,std::vector<std::string>& sub,bool aumenta=true);
		void FindInRecord(std::string car,std::vector<std::string>& sub,bool aumenta=true);
		void Information(std::string& comando,int& spazio_command,std::string& riga_attuale);

	protected:
		int size_of_file;
		int record;
		std::vector<std::string> righe_file;
		std::string attuale_comando;
		std::string filename;
	};

	class ARES_API INISection{
	public:
		bool GetVarValue(std::string var_name,std::string& var_value);
		std::string name;
		std::vector<std::string> var_names,var_values;
	};

	class ARES_API INIFile:public raf::file{
	public:
		bool GetSection(std::string section_name,raf::INISection& section);
	};

}//of the namespace

#endif
