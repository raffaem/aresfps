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
#include "evar.hpp"
#include "stdafx.h"
#include "light.hpp"
#include "level_model.hpp"
#include "ammunation.hpp"
#include <fstream>
#include <string>
#include <vector>
#include "..\\ares_runtime\\raf.hpp"
#include <irrlicht.h>
using namespace std;
using namespace irr;

string GetAresMapSaveFileName() {
	OPENFILENAME SaveFileName;
	TCHAR         szFile[MAX_PATH]      = "\0";
    strcpy( szFile, "");

	// Fill in the OPENFILENAME structure to support a template and hook.
	SaveFileName.lStructSize       = sizeof(OPENFILENAME);
    SaveFileName.hwndOwner         = NULL;
    SaveFileName.hInstance         = NULL;
    SaveFileName.lpstrFilter       = "Ares map 2 (.aresm2)\0*.aresm2\0Tutti i file (*.*)\0*.*\0\0";
    SaveFileName.lpstrCustomFilter = NULL;
    SaveFileName.nMaxCustFilter    = 0;
    SaveFileName.nFilterIndex      = 0;
    SaveFileName.lpstrFile         = szFile;
    SaveFileName.nMaxFile          = sizeof(szFile);
    SaveFileName.lpstrFileTitle    = NULL;
    SaveFileName.nMaxFileTitle     = 0;
    SaveFileName.lpstrInitialDir   = NULL;
    SaveFileName.lpstrTitle        = "Save the level";
    SaveFileName.nFileOffset       = 0;
    SaveFileName.nFileExtension    = 0;
    SaveFileName.lpstrDefExt       = "aresm2";
    SaveFileName.lCustData         = 0;
	SaveFileName.lpfnHook 		   = NULL;
	SaveFileName.lpTemplateName    = NULL;
    SaveFileName.Flags             = OFN_OVERWRITEPROMPT|OFN_EXPLORER|OFN_HIDEREADONLY;
	
	if(GetSaveFileName(&SaveFileName)==false) {
		return "";
	}
	return SaveFileName.lpstrFile;
}
string Convert3dVectorToString(core::vector3df vec) {
	float vecx=vec.X;
	float vecy=vec.Y;
	float vecz=vec.Z;

	string temp;
	temp+=raf::conv::NumString(vecx);
	temp+=",";
	temp+=raf::conv::NumString(vecy);
	temp+=",";
	temp+=raf::conv::NumString(vecz);

	return temp;
}

//aumenta il vettore su y
core::vector3df Correct(core::vector3df v) {
	//v.Y+=5.0f;
	return v;
}

std::string Save(string script_file_s/*=""*/) {
	bool show_message=true;
	if(script_file_s!="")
		show_message=false;

	string command;

	if(script_file_s=="")
		script_file_s=GetAresMapSaveFileName();

	if(script_file_s=="") 
		return "";

	const char* script_file=script_file_s.c_str();

	if(device->getFileSystem()->existFile(script_file)==true) {
		string com="erase ";
		com+=script_file;
		system(com.c_str());
	}

	string script_path=raf::String::EraseFileNameFromPath(script_file_s);

	ofstream out(script_file);

	//VERSION
	out<<"ver "+raf::conv::NumString(ares_version)<<endl;

	//DIFFUSE LIGHT
	out<<"diffuselight "<<raf::conv::BoolString(dl)<<endl;

	//WEAPON
	out<<"weapon "
		<<Convert3dVectorToString(weapon->getPosition())
		<<" "
		<<raf::conv::NumString(weapon->getRotation().Y)
		<<endl;

	//CAMERA
	out<<"camera "
		<<Convert3dVectorToString(camera->getPosition())
		<<" "
		<<Convert3dVectorToString(camera->getRotation())
		<<endl;

	//ZIP FILES
	for(int i=0;i<zip_files.size();i++) {
		out<<"addzip "+raf::String::ErasePathFromFullPath(zip_files[i])+"\n";

		//copy files
		command="copy "+zip_files[i]+" "+script_path;
		system(command.c_str());
	}
	
	//LEVEL MODEL
	for(i=0;i<level_models.size();i++) {
		if(level_models[i]!=NULL) {
			string model=raf::String::ErasePathFromFullPath(level_models[i]->model_path);
			string texture=raf::String::ErasePathFromFullPath(level_models[i]->texture_path);
			out<<"levelmodel "
				//name of the model
				<<model
				<<" "
				//name of the texture
				<<texture
				<<" "
				//position
				<<Convert3dVectorToString(level_models[i]->ogg->getPosition())
				//rotation
				<<" "
				<<Convert3dVectorToString(level_models[i]->ogg->getRotation())
				//scale
				<<" "
				<<Convert3dVectorToString(level_models[i]->ogg->getScale())
				<<endl;

			//copy files
			command="copy "+level_models[i]->model_path+" "+script_path;
			system(command.c_str());
			command="copy "+level_models[i]->texture_path+" "+script_path;
			system(command.c_str());
		}
	}

	//ENEMIES
	string s;
	for(i=0;i<enemies.size();i++) {
		if(enemies[i]==NULL) {
			continue;
		}

		if(enemies[i]->GetEnemieType()==ET_FALGAT)
			s="falgat ";
		else if(enemies[i]->GetEnemieType()==ET_RHINO)
			s="rhino ";
		else if(enemies[i]->GetEnemieType()==ET_ZOMBIE)
			s="zombie ";

		s+=Convert3dVectorToString(Correct(enemies[i]->getPosition()));
		s+=" "+raf::conv::NumString(enemies[i]->getRotation().Y);
		out<<s<<endl;
	}		

	//MEDIKITS
	for(i=0;i<medikits.size();i++) {
		if(medikits[i].ogg==NULL) {
			continue;
		}
		s="medikitEx ";
		s+=Convert3dVectorToString(Correct(medikits[i].ogg->getPosition()));
		s+=" "+raf::conv::NumString(medikits[i].ogg->getRotation().Y);
		s+=" "+raf::conv::NumString(medikits[i].life);
		out<<s<<endl;
	}	

	//AMMUNATIONS
	for(i=0;i<ammunation.size();i++) {
		s="";

		if(ammunation[i]==NULL) {
			continue;
		}

		if(ammunation[i]->type==EAT_SHOTGUN)
			s+="ammunation_shot_gun ";
		else if(ammunation[i]->type==EAT_MACHINEGUN)
			s+="ammunation_machine_gun ";
		else if(ammunation[i]->type==EAT_RIFLEGUN)
			s+="ammunation_rifle_gun ";

		s+=Convert3dVectorToString(Correct(ammunation[i]->ogg->getPosition()));
		s+=" "+raf::conv::NumString(ammunation[i]->ogg->getRotation().Y);
		s+=" "+raf::conv::NumString(ammunation[i]->num_of_bullets);
		out<<s<<endl;
	}	

	//ARMOURS
	for(i=0;i<armours.size();i++) {
		if(armours[i].ogg==NULL) {
			continue;
		}
		s="armour ";
		s+=Convert3dVectorToString(Correct(armours[i].ogg->getPosition()));
		s+=" "+raf::conv::NumString(armours[i].ogg->getRotation().Y);
		s+=" "+raf::conv::NumString(armours[i].armour);
		out<<s<<endl;
	}

	//LIGHTS
	for(i=0;i<lights.size();i++) {
		if(lights[i]==NULL) {
			continue;
		}
		s="light ";
		s+=Convert3dVectorToString(lights[i]->light->getPosition());
		s+=" "+raf::conv::NumString(lights[i]->ray);

		out<<s<<endl;
	}	

	//SKY BOX
	if(skyboxNode!=NULL) {

		if(sky_box.top!="default") {
			out<<"skybox "
				<<raf::String::ErasePathFromFullPath(sky_box.top)
				<<" "
				<<raf::String::ErasePathFromFullPath(sky_box.bottom)
				<<" "
				<<raf::String::ErasePathFromFullPath(sky_box.left)
				<<" "
				<<raf::String::ErasePathFromFullPath(sky_box.right)
				<<" "
				<<raf::String::ErasePathFromFullPath(sky_box.front)
				<<" "
				<<raf::String::ErasePathFromFullPath(sky_box.back)
				<<endl;

			//copy files
			command="copy "+sky_box.top+" "+script_path;
			system(command.c_str());
			command="copy "+sky_box.bottom+" "+script_path;
			system(command.c_str());
			command="copy "+sky_box.left+" "+script_path;
			system(command.c_str());
			command="copy "+sky_box.right+" "+script_path;
			system(command.c_str());
			command="copy "+sky_box.front+" "+script_path;
			system(command.c_str());
			command="copy "+sky_box.back+" "+script_path;
			system(command.c_str());
		}

		//default sky box
		else{
			out<<"addskybox t"<<endl;
		}//else{

	}//if(skyboxNode!=NULL) {

	//TERRAINS
	for(i=0;i<terrain_nodes.size();i++) {
		out<<"terrain "
			<<Convert3dVectorToString(terrain_nodes[i]->ogg->getPosition())
			<<" "
			<<Convert3dVectorToString(terrain_nodes[i]->ogg->getRotation())
			<<" "
			<<Convert3dVectorToString(terrain_nodes[i]->ogg->getScale())
			<<" "
			<<raf::String::ErasePathFromFullPath(terrain_nodes[i]->heightmap)
			<<" ";

		if(terrain_nodes[i]->texture!="") {
			out<<raf::String::ErasePathFromFullPath(terrain_nodes[i]->texture)
				<<" ";
		}
		else
			out<<"0 ";

		if(terrain_nodes[i]->detail_texture!="") {
			out<<raf::String::ErasePathFromFullPath(terrain_nodes[i]->detail_texture)
				<<" ";
		}
		else
			out<<"0 ";

		out<<raf::conv::NumString(terrain_nodes[i]->scale1)
			<<" "
			<<raf::conv::NumString(terrain_nodes[i]->scale2)
			<<endl;

		//copy files
		command="copy "+terrain_nodes[i]->heightmap+" "+script_path;
		system(command.c_str());

		if(terrain_nodes[i]->texture!="") {
			command="copy "+terrain_nodes[i]->texture+" "+script_path;
			system(command.c_str());
		}

		if(terrain_nodes[i]->detail_texture!="") {
			command="copy "+terrain_nodes[i]->detail_texture+" "+script_path;
			system(command.c_str());
		}

	}//for(int i=0;i<terrain_nodes.size();i++) {

	actual_file=script_file;

	//SHOW TEXT
	if(show_message) {
	string text;
	text+="The file has been saved in this position:\n";
	text+=script_file;
	text+="\nRemember that the models and the textures wich you use "  
		"for your level must be "
		"in the same position of the file of your level "
		"(so in the position indicates above) otherwise "
		"during the loading ares will give an error message like "
		"\"file xxx not found\".Ares' level editor has automatically "
		"copied these files in the destination folder,but this level "
		"editor can't copy texture files wich are setted as materials "
		"inside the models. So go in the folder indicates above and control "
		"if all files wich you need are present.For more information "
		"see the guide. Thanks";
	AfxMessageBox(text.c_str(),0,0);
	}//if(show_message) {

	string return_string(script_file);
	return return_string;
}