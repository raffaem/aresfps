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
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

bool package=false;

string EraseFileNameFromPath(string s) {
	int pos=s.find_last_of("\\");
	if(pos>0) {
		s.erase(pos,s.size()-1);
	}
	return s;
}

int main(int argc, char* argv[])
{
	if(argc<2) {
		cout<<"error,you don't call Ares' level install correctly.";
		system("pause");
		exit(-1);
	}
	//controlla se installare un livello o un package
	string argv1=argv[1];
	//-p
	if(argv1[0]=='-'&&argv1[1]=='p') {
		//è un package
		package=true;
		//elimina il -p
		argv1.erase(0,2);
	}

	//setta il path nella cartella del file
	string filepath=EraseFileNameFromPath(argv1);
	
	//mette il file in un vettore
	ifstream file(argv1.c_str());
	vector<string> v;
	string temp;
	while(getline(file,temp))
		v.push_back(temp);
	//ora il file è nel vettore
		
	string copy,progpath=EraseFileNameFromPath(argv[0]);
	
	for(int i=0;i<v.size();i++) {
		//scandisce tutto il file
		copy="copy \""+filepath+"\\"+v[i]+"\" \""+progpath;
		if(!package) {
			//li copia nella cartella dei livelli
			copy+="\\levels";	
		}
		copy+="\"";
		system(copy.c_str());
	}
	string com="erase "+progpath+"\\levels\\*.aresmi";
	system(com.c_str());
	system("pause");
	return 0;
}
