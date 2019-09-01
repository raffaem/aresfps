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

string GetAresMapName() {
	string script_file="mymap.aresm2";

	OPENFILENAME OpenFileName;
	TCHAR         szFile[MAX_PATH]      = "\0";
    strcpy( szFile, "");

	// Fill in the OPENFILENAME structure to support a template and hook.
	OpenFileName.lStructSize       = sizeof(OPENFILENAME);
    OpenFileName.hwndOwner         = NULL;
    OpenFileName.hInstance         = NULL;
    OpenFileName.lpstrFilter       = "Ares map 2 (*.aresm2)\0*.aresm2\0Ares map (*.aresmap)\0*.aresmap\0Tutti i file (*.*)\0*.*\0\0";
    OpenFileName.lpstrCustomFilter = NULL;
    OpenFileName.nMaxCustFilter    = 0;
    OpenFileName.nFilterIndex      = 0;
    OpenFileName.lpstrFile         = szFile;
    OpenFileName.nMaxFile          = sizeof(szFile);
    OpenFileName.lpstrFileTitle    = NULL;
    OpenFileName.nMaxFileTitle     = 0;
    OpenFileName.lpstrInitialDir   = NULL;
    OpenFileName.lpstrTitle        = "Choose a level";
    OpenFileName.nFileOffset       = 0;
    OpenFileName.nFileExtension    = 0;
    OpenFileName.lpstrDefExt       = NULL;
    OpenFileName.lCustData         = 0;
	OpenFileName.lpfnHook 		   = NULL;
	OpenFileName.lpTemplateName    = NULL;
    OpenFileName.Flags             = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_EXPLORER|OFN_HIDEREADONLY;



	if(GetOpenFileName(&OpenFileName)==FALSE) {
		string err="errore numero ";
		DWORD errore_numero=CommDlgExtendedError();
		err+=raf::conv::NumString(errore_numero);

		if(errore_numero==0) {
			//non ha selezionato nessun file
			return "";		
		}	
		
		MessageBox(NULL,err.c_str(),"error",MB_SYSTEMMODAL);
		exit(1);
	};

	return OpenFileName.lpstrFile;
}

void Load(std::string script_file/*=""*/) {
	loader_execute=true;

	if(script_file=="")
		script_file=GetAresMapName();

	if(script_file=="") {
		//l'utente ha premuto annulla
		return;
	}

	//ClearLevel();
	raf::ChangeCurrentDirTo(prog_dir);

	//load a new level
	scene::IMetaTriangleSelector* world_selector=smgr->createMetaTriangleSelector();
	string script_path=raf::String::EraseFileNameFromPath(script_file);
	
	//INIZIO DEL LINGUAGGIO DI SCRIPT "OC LEVEL BUILD"
	raf::file script;
	if(!script.Open(script_file)) {
		raf::errore("Error during load file "+script_file);
		return;
	}
	int a=0;

	//---------------------FOR OLD COMPATIBILITY----------------------
	//diffuse light?
	script.SetRecordNumber(0);
	if(script.GetRecord()=="yes"||
		script.GetRecord()=="no") {
			raf::errore("This file is in an old format. Pease resave it");
			a=2;
			if(script.GetRecord()=="yes")
				dl=true;
			else 
				dl=false;
			//to set world->diffuse light item correctly
			DiffuseLight();
			//weapon
			script.SetRecordNumber(1);
			string weapon_file=script.GetRecord();
			//motore di scansione per capire la posizione e la rotazione su y di weapon
			float posx,posy,posz,rot_y;
			//int posizione_finale_del_vettore;
			vector<int> v_a,v_b;
			vector<string> weapon_sub;
			script.FindInRecord(" ",v_a,v_b,weapon_sub);
			//posizione_finale_del_vettore+=2;
			raf::conv::String3dVector(weapon_sub[0],',',posx,posy,posz);
			rot_y=atoi(weapon_sub[1].c_str());	
			weapon->setPosition(core::vector3df(posx,posy,posz));
			weapon->setRotation(core::vector3df(0,rot_y,0));
	}//if(script.GetRecord()=="yes"||
	//---------------------FOR OLD COMPATIBILITY----------------------


	//FOR ESTERNO
	string comando,riga_attuale;
	int spazio_command;
	//for esterno
	int size_of_file=script.GetFileSize();
	vector<string> sub;
	for(;a<size_of_file;a++) {//for esterno che scandisce il restante file
		script.SetRecordNumber(a);

		//if it is a comment,ignore it
		if(script.GetRecord()[0]=='/'&&
			script.GetRecord()[1]=='/') 
			continue;

		//mi ricavo tutte le informazioni che mi servono
		script.Information(comando,spazio_command,riga_attuale);
		sub.clear();
		script.FindInRecord(" ",sub);	

		if(comando=="diffuselight") {
			if(sub[1]=="yes")
				dl=true;
			else
				dl=false;
			DiffuseLight();
		}

		else if(comando=="weapon"){
			//weapon
			weapon->setPosition(raf::conv::String3dVector(sub[1],','));
			weapon->setRotation(core::vector3df(0,atof(sub[2].c_str()),0));
		}

		else if(comando=="ver") {
			this_file_ver=atof(sub[1].c_str());
			if(this_file_ver>ares_version) { 
				bool err=raf::AddYesNoMessagebox("This file has been produced with a following version of Ares. Please download from the site http://aresfps.sf.net the currently version of Ares to load this file correctly. Try to load it?","Error");
				if(err==true)
					continue;
				else
					break;
			}//if(this_file_ver>ARES_VER) {
		}

		else if(comando=="levelmodel") {
			//aggiunge un modello
			//sintassi
			//addmodel nomedodello texture posx,posy,posz rotx,roty,rotz
			///per la posizione
			core::vector3df posizione=raf::conv::String3dVector(sub[3],',');
			//per la rotazione
			core::vector3df rotazione=raf::conv::String3dVector(sub[4],',');	

			//scale
			core::vector3df scale;
			if(sub.size()>5)
				scale=raf::conv::String3dVector(sub[5],',');
			else
				scale=core::vector3df(1,1,1);

			//test
			sub[1]=script_path+"\\"+sub[1];
			if(!script.IsExist(sub[1])) continue;

			if(sub[2]!="noTexture") {
				sub[2]=script_path+"\\"+sub[2];
				if(!script.IsExist(sub[2])) continue;
			}
			//end of test

			AddLevelModel(sub[1],sub[2],posizione,rotazione,scale);
		}

		else if(comando=="falgat") {//aggiunge un falgat
			core::vector3df position=raf::conv::String3dVector(sub[1],',');
			core::vector3df rotation(0,atoi(sub[2].c_str()),0);
			AddFalgat(position,rotation);
		}//if(riga_attuale_semi=="falgat")	
		else if(comando=="rhino") {//aggiunge un falgat
			core::vector3df position=raf::conv::String3dVector(sub[1],',');
			core::vector3df rotation(0,atoi(sub[2].c_str()),0);
			AddRhino(position,rotation);
		}//if(riga_attuale_semi=="falgat")	
		else if(comando=="zombie") {//aggiunge un falgat
			core::vector3df position=raf::conv::String3dVector(sub[1],',');
			core::vector3df rotation(0,atoi(sub[2].c_str()),0);
			AddZombie(position,rotation);
		}//if(riga_attuale_semi=="falgat")
		//fine codice per falgat

		//ammunation
		else if(comando=="ammunation_shot_gun") {//aggiunge un falgat
			core::vector3df position=raf::conv::String3dVector(sub[1],',');
			core::vector3df rotation(0,atoi(sub[2].c_str()),0);
			int num_of_bullets=atoi(sub[3].c_str());
			AddAmmunationShotgun(position,rotation,num_of_bullets);
		}//if(riga_attuale_semi=="falgat")	
		else if(comando=="ammunation_machine_gun") {//aggiunge un falgat
			core::vector3df position=raf::conv::String3dVector(sub[1],',');
			core::vector3df rotation(0,atoi(sub[2].c_str()),0);
			int num_of_bullets=atoi(sub[3].c_str());
			AddAmmunationMachinegun(position,rotation,num_of_bullets);
		}//if(riga_attuale_semi=="falgat")	
		else if(comando=="ammunation_rifle_gun") {//aggiunge un falgat
			core::vector3df position=raf::conv::String3dVector(sub[1],',');
			core::vector3df rotation(0,atoi(sub[2].c_str()),0);
			int num_of_bullets=atoi(sub[3].c_str());
			AddAmmunationRiflegun(position,rotation,num_of_bullets);
		}//if(riga_attuale_semi=="falgat")	
		//end of ammunation

		else if(comando=="armour") {//aggiunge un falgat
			core::vector3df position=raf::conv::String3dVector(sub[1],',');
			core::vector3df rotation(0,atoi(sub[2].c_str()),0);
			int num_of_bullets=atoi(sub[3].c_str());
			AddArmour(position,rotation,num_of_bullets);
		}//if(riga_attuale_semi=="falgat")	

		else if(comando=="addzip") {//aggiunge un archivio zip
			sub[1]=script_path+"\\"+sub[1];
			//test
			if(!script.IsExist(sub[1])) continue;

			device->getFileSystem()->addZipFileArchive(sub[1].c_str());
			zip_files.push_back(script_path+"\\"+sub[1]);
		}

		else if(comando=="medikit") {//aggiunge un medikit
			core::vector3df position=raf::conv::String3dVector(sub[1],',');
			core::vector3df rotation(0,atoi(sub[2].c_str()),0);
			AddMedikit(position,rotation,15);
		}//if(medikit)

		else if(comando=="medikitEx") {//aggiunge un medikit
			core::vector3df position=raf::conv::String3dVector(sub[1],',');
			core::vector3df rotation(0,atoi(sub[2].c_str()),0);
			int life=atoi(sub[3].c_str());
			AddMedikit(position,rotation,life);
		}//if(medikit)

		//aggiunge una luce
		else if(comando=="light") {//aggiunge una lampadina
				core::vector3df position=raf::conv::String3dVector(sub[1],',');
				float raggio=atof(sub[2].c_str());
				AddLight(position,raggio);
		}//if(light)
		/*else if(comando=="addfire") {
			scene::IParticleSystemSceneNode* ps = smgr->addParticleSystemSceneNode(false, 0, -1, 
			core::vector3df(100,120,600), core::vector3df(0,0,0),
			core::vector3df(2,2,2));
			ps->setParticleSize(core::dimension2d<f32>(20.0f, 10.0f));
			scene::IParticleAffector* paf =ps->createFadeOutParticleAffector();
			ps->addAffector(paf);
			paf->drop();
			ps->setMaterialFlag(video::EMF_LIGHTING, false);
			ps->setMaterialTexture(0,driver->getTexture("media\\texture\\fire.bmp"));
			ps->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
			double posx,posy,posz;
			string vettore=script.RigaAttualeSubString(spazio_command+1);
			raf::conv::String3dVector(vettore,',',posx,posy,posz);
			ps->setPosition(core::vector3df(posx,posy,posz));
			//per fare atterrare il fuoco
			core::line3d<f32> line;
			core::vector3df temp_vec,contatto;
			core::triangle3df tri;
			temp_vec=ps->getPosition();
			line.start=temp_vec;
			temp_vec.Y-=99999999;
			line.end=temp_vec;
			if(smgr->getSceneCollisionManager()->getCollisionPoint(line,world_selector, contatto, tri)) {
				ps->setPosition(contatto);
			}
			//fine per farlo atterrare
			scene::IParticleEmitter* em = ps->createBoxEmitter(
				core::aabbox3d<f32>(-7,0,-7,7,1,7), 
				core::vector3df(0.0f,0.03f,0.0f),
				80,100, video::SColor(0,255,255,255),video::SColor(0,255,255,255), 800,2000);
			ps->setEmitter(em);
			em->drop();
		}*/
		//DEFAULT SKYBOX
		else if(comando=="addskybox") {
			// create sky box
			AddDefaultSkyBox();
		}
		
		//USER SKYBOX
		else if(comando=="skybox") {
			//test
			if(!script.IsExist(sub[1])||
				!script.IsExist(sub[2])||
				!script.IsExist(sub[3])||
				!script.IsExist(sub[4])||
				!script.IsExist(sub[5])||
				!script.IsExist(sub[6])) continue;
			//end of test

			skyboxNode=smgr->addSkyBoxSceneNode(
				driver->getTexture(sub[1].c_str()),
				driver->getTexture(sub[2].c_str()),
				driver->getTexture(sub[3].c_str()),
				driver->getTexture(sub[4].c_str()),
				driver->getTexture(sub[5].c_str()),
				driver->getTexture(sub[6].c_str())
				);
		}

		else if(comando=="terrain") {
			core::vector3df position=raf::conv::String3dVector(sub[1],',');
			core::vector3df rotation=raf::conv::String3dVector(sub[2],',');
			core::vector3df scale=raf::conv::String3dVector(sub[3],',');
			string heightmap=sub[4];
			string texture=sub[5];
			string detail_texture=sub[6];
			float scale1=atof(sub[7].c_str());
			float scale2=atof(sub[8].c_str());

			//test
			if(!script.IsExist(heightmap)||
				!script.IsExist(texture)||
				!script.IsExist(detail_texture)) continue;
			//end of test

			AddTerrain(heightmap,texture,detail_texture,position,rotation,scale,scale1,scale2);
		}

		//comando usato solo da questo loader. il loader di ares ignora questo comando
		else if(comando=="camera") {
			core::vector3df position=raf::conv::String3dVector(sub[1],',');
			core::vector3df rotation=raf::conv::String3dVector(sub[2],',');
			camera->setRotation(rotation);
			camera->setPosition(position);
		}
		else {
			if(this_file_ver>ares_version) {
				raf::errore("This file has been produced with a following version of Ares and it is not possible to load it correctly. Please download from the site http://aresfps.sf.net the current version of Ares to load this file correctly. Press ok.");
				ClearLevel();
			}
			else
				script.ComandoNonValidoFatal();
		}
	}//for esterno

	actual_file=script_file;
	//FINE LINGUAGGIO DI SCRIPT "OC LEVEL BUILD"

	loader_execute=false;
}