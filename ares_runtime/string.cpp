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
#include "string.hpp"
using namespace std;

namespace raf{
	char sign(long double num);
}

std::string raf::String::SubString(std::string s,int inizio,int fine) {
	string ris;
	ris=s;
	ris.erase(fine+1,ris.size());
	ris.erase(0,inizio);
	return ris;
}
//-------------------------------------------------------------
void raf::String::Find(std::string stringa,std::string car,std::vector<int>& inizio,std::vector<int>& fine,std::vector<std::string>& sub,bool aumenta/*=true*/) {
	//i inizio
	//a fine
	/*la funzione stringa.find non restituisce due vettori con la posizione
	iniziale e finale della sottostringa, e inoltre legge una
	sottostringa per volta
	*/
	vector<int> in;
	vector<int> fin;
	int size_stringa=stringa.size();
	int car_size=car.size()-1;
	for(int i=0;car_size<size_stringa;i++) {
		if(raf::String::SubString(stringa,i,car_size)==car) {
			in.push_back(i);
			fin.push_back(car_size);
		}
		car_size++;
	}
	inizio=in;
	fine=fin;
	if(inizio.empty()==true) return;
	//sottostringhe
	if(aumenta==true) {
		sub.push_back(raf::String::SubString(stringa,0,in[0]-1));
		for(int i=0;i<in.size()-1;i++) {
			int a=i+1;
			int inizio_temp=(fin[i])+1;
			int fine_temp=(in[a])-1;
			sub.push_back(raf::String::SubString(stringa,inizio_temp,fine_temp));
		}
		int vett_size=fin.size()-1;
		int size=(fin[vett_size])+1;
		sub.push_back(raf::String::SubString(stringa,size,stringa.size()-1));
	}
	else{
		sub.push_back(raf::String::SubString(stringa,0,in[0]));
		for(int i=0;i<in.size()-1;i++) {
			int a=i+1;
			int inizio_temp=fin[i];
			int fine_temp=in[a];
			sub.push_back(raf::String::SubString(stringa,inizio_temp,fine_temp));
		}
		int vett_size=fin.size()-1;
		int size=fin[vett_size];
		sub.push_back(raf::String::SubString(stringa,size,stringa.size()-1));
	}
}
//-----------------------------------------------------------------
string raf::String::EraseFileNameFromPath(string s) {
	bool insert=false;
	int size=s.size();
	if(s[size-1]=='\"') 
		insert=true;

	int pos=s.find_last_of("\\");
	if(raf::sign(pos)=='+') {
		s.erase(pos,s.size()-1);
	}
	if(insert)
		s+='\"';
	return s;
}
//-------------------------------------------------------
std::string raf::String::ErasePathFromFullPath(std::string s) {
	//erase all characters before the last \

	int pos=s.find_last_of("\\");
	s.erase(0,++pos);
	//erase all characters before the last /
	pos=s.find_last_of("/");
	s.erase(0,++pos);
	return s;
}
//-------------------------------------------------------
ARES_API std::string raf::String::GetExtention(std::string file_name) {
	int pos=file_name.find_last_of('.');
	file_name.erase(0,++pos);
	return file_name;
}
