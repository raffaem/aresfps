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
#include <windows.h>
#include "file_class.hpp"
#include "raf.hpp"
#include <iostream>
using namespace std;

//externs
extern irr::IrrlichtDevice* device_drag;

//costructor
bool raf::file::Open(std::string nome_del_file) {
	if(nome_del_file=="") 
		return false;

	//ceck if the file exist
	FILE* f=fopen(nome_del_file.c_str(),"rb");
	if(!f)
		return false;
	fclose(f);
	//end of ceck

	ifstream in(nome_del_file.c_str());

	if(!in.is_open())
		return false;

	std::string temp;
	while(getline(in,temp))//mette il contenuto del file nel vettore
		this->righe_file.push_back(temp);
	//ore righe_file contiene tutto il file
	this->size_of_file=this->righe_file.size();
	this->filename=nome_del_file;
	return true;
}
//------------------------------------------------
int raf::file::GetRecordNumber() {
	return this->record;
}
std::string raf::file::GetRecord() {
	return this->righe_file[this->record];
}

//-----------------------------------------------------------------
void raf::file::Close() {
	this->righe_file.clear();
}

//questa funzione deve essere chiamata dopo il for
void raf::file::SetRecordNumber(int new_record) {
	this->record=new_record;
}
//legge un comando separato da uno spazio
std::string raf::file::ReadCommand() {
	int a;
	std::string ret=this->ReadCommand(a);
	return ret;
}
std::string raf::file::ReadCommand(int& position_space) {
	std::string riga_attuale=file::righe_file[file::record];
	int res=riga_attuale.find(" ");

	if(res!=-1) {
		file::attuale_comando=raf::String::SubString(riga_attuale,0,--res);
		//per compensare il --res di sopra
		position_space=++res;
	}
	else {
		file::attuale_comando=riga_attuale;
		//per compensare il --res di sopra
		position_space=-1;
	}

	return(attuale_comando);
}
//errore, comando non valido
void raf::file::ComandoNonValidoFatal(std::string comando) {
	std::string messaggio="The command "+comando+" are invalid. This program will be terminated. Please open Ares' level editor to correct the level. Press ok...\n";
	MessageBoxA(NULL,messaggio.c_str(),"Error",MB_SYSTEMMODAL);
	exit(1);
}
void raf::file::ComandoNonValidoFatal() {
	std::string messaggio="The command "+file::attuale_comando+" are invalid. This program will be terminated. Please open Ares' level editor to correct the level. Press ok...\n";
	MessageBoxA(NULL,messaggio.c_str(),"Error",MB_SYSTEMMODAL);
	exit(1);
}
//cerca nel file una std::stringa
void raf::file::find_in_file(std::string stringa_da_cercare,std::vector<int>& riga,std::vector<int> & inizio, std::vector<int>& fine) {
	std::string riga_attuale;
	vector<int> ini,fin;
	vector<std::string> temp;
	for(int i=0;i<file::size_of_file;i++) {
		riga_attuale=file::righe_file[i];
		raf::String::Find(riga_attuale,stringa_da_cercare,ini,fin,temp);
		for(int a=0;a<ini.size();a++) {
			riga.push_back(i);
		}
		raf::copyVectorToVector(inizio,ini);
		raf::copyVectorToVector(fine,fin);
	}//for
}
//////////////////////////////////////////////////////////////
void raf::file::Read3dVector(char carattere_separatore,double& num1,double& num2,double& num3) {
	float temp_num1,temp_num2,temp_num3;
	raf::conv::String3dVector(file::righe_file[file::record],carattere_separatore,temp_num1,temp_num2,temp_num3);
	num1=temp_num1;
	num2=temp_num2;
	num3=temp_num3;
	return;
}
/////////////////////////////////////////////////////////////////
std::string raf::file::RigaAttuale()  {
	return (file::righe_file[file::record]);
}
////////////////////////////////////////////////////////
std::string raf::file::RigaAttualeSubString(int inizio,int fine) {
	return(raf::String::SubString(file::righe_file[file::record],inizio,fine));
}
////////////////////////////////////////////////////////
std::string raf::file::RigaAttualeSubString(int inizio) {
	return(raf::String::SubString(file::righe_file[file::record],inizio,file::righe_file[file::record].size()-1));
}
void raf::file::Information(std::string& comando,int& spazio_command,std::string& riga_attuale) {
	comando=file::ReadCommand(spazio_command);
	++spazio_command;
	riga_attuale=file::RigaAttuale();
	comando=file::ReadCommand();
	return;
}
//////////////////////////////////////////////////////
void raf::file::FindInRecord(std::string car,std::vector<int>& inizio,std::vector<int>& fine,std::vector<std::string>& sub,bool aumenta/*=true*/) {
	raf::String::Find(file::righe_file[file::record],car,inizio,fine,sub,aumenta);
	return;
}
////////////////////////////////////////////////
void raf::file::FindInRecord(std::string car,std::vector<std::string>& sub,bool aumenta/*=true*/) {
	//this variable are local and they are deleted qhen the function finish
	vector<int> inizio,fine;
	this->FindInRecord(car,inizio,fine,sub,aumenta);
	return;
}
//------------------------------------------------------------------
bool raf::file::IsExist(std::string file) {
	if(file=="noTexture") return true;
	else if(!device_drag->getFileSystem()->existFile(file.c_str())) {
		raf::errore("Error in the file "+this->GetFileName()+" at line: "+raf::conv::NumString(this->GetRecordNumber())+"\nThe file "+file+" not exist\nThis line will be ignored. Please:\n1)click on file->View code\n2)say no\n3)correct the wrong file-name at the line above\n4)from notepad,click on file-save\n5)from notepad, click on file->exit\n6)From ares' level editor, click on file->reload.");
		return false;
	}
	return true;
}
bool raf::file::IsExistFatal(std::string file) {
	if(file=="noTexture") return true;
	else if(!device_drag->getFileSystem()->existFile(file.c_str())) {
		raf::errore("Error in the file "+this->GetFileName()+" at line: "+raf::conv::NumString(this->GetRecordNumber())+"\nThe file "+file+" not exist\nPlease contact the author of the level or open the level with Ares' level editor to correct the file\nPress ok to close the game");
		return false;
	}
	return true;
}
///////////////RESFILE///////////////////////////////////////
bool raf::INIFile::GetSection(std::string section_name,raf::INISection& section) {
	//STEP 1:TESTS
	if(this->righe_file.empty())
		return false;
	if(this->size_of_file<=0)
		return false;
	if(this->filename=="")
		return false;

	//STEP 2:INITIALIZE
	std::string copy_section_name=section_name;
	section_name='['+copy_section_name+']';
	int start_pos=-1;
	int end_pos=-1;

	//STEP 3:GET START POSITION
	for(int i=0;i<this->righe_file.size();i++) {
		if(this->righe_file[i]==section_name) {
			start_pos=++i;
			break;
		}
	}
	if(start_pos<0)
		return false;

	//STEP 4:GET END POS
	for(i=start_pos+1;i<this->righe_file.size();i++) {
		if(this->righe_file[i][0]=='[') {
			end_pos=i-1;
			break;
		}
	}
	if(end_pos<0) 
		end_pos=this->righe_file.size()-1;

	//STEP 5: GET ALL RECORDS
	std::vector<std::string> params;
	for(i=start_pos;i<=end_pos;i++){
		params.push_back(this->righe_file[i]);
	}

	//STEP 6:SUBDIVIDE VARIABLES NAMES AND VARIABLES VALUES
	std::vector<std::string> var_names,var_values;
	for(i=0;i<params.size();i++) {
		int pos=params[i].find('=');
		if(pos<0) return false;
		std::string var_name=raf::String::SubString(params[i],0,pos-1);
		if(var_name.empty()) return false;
		std::string var_value=raf::String::SubString(params[i],pos+1,params[i].size()-1);
		if(var_value.empty()) return false;
		var_names.push_back(var_name);
		var_values.push_back(var_value);
	}

	section.name=section_name;
	section.var_names=var_names;
	section.var_values=var_values;

	return true;	
}
bool raf::INISection::GetVarValue(std::string var_name,std::string& var_value) {
	int pos=-1;
	for(int i=0;i<this->var_names.size();i++) {
		if(this->var_names[i]==var_name) {
			pos=i;
			break;
		}
	};
	if(pos<0) return false;

	if((this->var_values.size()-1)<pos) return false;
	var_value=this->var_values[pos];
	return true;
}


