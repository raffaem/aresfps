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
#include <irrlicht.h>
#include <windows.h>
#include <string>
#include "classi.hpp"
#include "irrlicht class.hpp"
#include "func.hpp"
#include <sstream>
#include "evar.hpp"
#include "script.hpp"

using namespace irr;
using namespace std;

void carica_mappa(){
	this_file_ver=ares_version;
	string p=device->getFileSystem()->getWorkingDirectory();
	world_selector=smgr->createMetaTriangleSelector();

	//INIZIO DEL LINGUAGGIO DI SCRIPT "ARES LEVEL BUILD"
	raf::file script;
	if(!script.Open(script_file)) {
		raf::FatalError("Error during load file "+script_file);
	}
	int a=0;
	

	//---------------.ARESMAP OLD COMPATIBILITY------------------------
	//diffuse light?
	script.SetRecordNumber(0);
	if(script.GetRecord()=="yes"||
		script.GetRecord()=="no") {
			a=2;
			string diffuse_light_string=script.GetRecord();
			if(script.GetRecord()=="yes")
				dl=true;
			else if(script.GetRecord()=="no")
				dl=false;
			raf::DiffuseLight(weapon->actual_weapon->ogg,dl);
			//weapon pos and rot
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
			weapon->actual_weapon->ogg->setPosition(core::vector3df(posx,posy,posz));
			weapon->actual_weapon->ogg->setRotation(core::vector3df(0,rot_y,0));
	}//if(script.GetRecord()=="yes"||
	//---------------.ARESMAP OLD COMPATIBILITY------------------------


	//FOR ESTERNO
	string comando,riga_attuale;
	int spazio_command;
	int size_of_file=script.GetFileSize();
	vector<string> sub;
	for(;a<size_of_file;a++) {//for esterno che scandisce il restante file
		script.SetRecordNumber(a);

		//if it is a comment,ignore it
		if(script.GetRecord()[0]=='/'&&
			script.GetRecord()[1]=='/') 
			continue;

		script.Information(comando,spazio_command,riga_attuale);
		sub.clear();
		script.FindInRecord(" ",sub);

		if(comando=="diffuselight") {
			if(sub[1]=="yes")
				dl=true;
			else
				dl=false;
			raf::DiffuseLight(weapon->actual_weapon->ogg,dl);
		}

		else if(comando=="weapon") {
			weapon->actual_weapon->ogg->setPosition(raf::conv::String3dVector(sub[1],','));
			weapon->actual_weapon->ogg->setRotation(core::vector3df(0,atof(sub[2].c_str()),0));
		}

		else if(comando=="ver") {
			this_file_ver=atof(sub[1].c_str());
			if(this_file_ver>ares_version&&
				!now_restarting) { 
				bool err=raf::AddYesNoMessagebox("This file has been produced with a following version of Ares. Please download from the site http://aresfps.sf.net the currently version of Ares to load this file correctly. Try to load it?","Error");
				if(err==true)
					continue;
				else
					exit(-1);
			}//if(this_file_ver>ARES_VER) {
		}

		else if(comando=="levelmodel") {
			/*
			aggiunge un modello
			sintassi
			addmodel nomedodello texture posx,posy,posz rotx,roty,rotz
			*/
			sub[1]="levels\\"+sub[1];
			raf::esiste(sub[1]);

			sub[2]="levels\\"+sub[2];
			scene::IAnimatedMesh* map_animated_mesh=smgr->getMesh(sub[1].c_str());

			if(!map_animated_mesh) {
				raf::errore("Error. Cannot load "+sub[1]+"maybe corrupted file");
				exit(-1);
			}

			scene::IMesh* map_mesh=map_animated_mesh->getMesh(0);

			scene::ISceneNode* node=smgr->addOctTreeSceneNode(map_mesh);
			//scene::ISceneNode* node=smgr->addMeshSceneNode(map_mesh);

			raf::DiffuseLight(node,dl);
			//avoid light calculation problem if scale
			node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS,true); 

			if(!(sub[2]=="levels\\noTexture")) {
				if(file_system->existFile(sub[2].c_str())==false) {
					raf::errore("File "+sub[2]+" not found");
					exit(-1);
				}
				node->setMaterialTexture(0,driver->getTexture(sub[2].c_str()));
			}
			//node->setMaterialFlag(video::EMF_FOG_ENABLE,true);
			//parallax mapping
			//node->setMaterialType(video::EMT_PARALLAX_MAP_SOLID);

			///per la posizione
			node->setPosition(raf::conv::String3dVector(sub[3],','));
			//per la rotazione
			node->setRotation(raf::conv::String3dVector(sub[4],','));

			//scale
			if(sub.size()>5)
				node->setScale(raf::conv::String3dVector(sub[5],','));
			else
				node->setScale(core::vector3df(1,1,1));
			//end of scale

			//per le collisioni
			scene::ITriangleSelector* tri;
			tri=smgr->createOctTreeTriangleSelector(
				map_mesh,
				node,128);
			//tri=smgr->createTriangleSelector(map_mesh,node);
			node->setTriangleSelector(tri);
			world_selector->addTriangleSelector(tri);
			tri->drop();
			//fine per le collisioni

			//lo metto nel vettore
			LevelModel ogg;
			ogg.mesh=map_mesh;
			ogg.node=node;
			world_nodes.push_back(ogg);
		}

		//enemies
		else if(comando=="falgat") {//aggiunge un falgat
			core::vector3df posizione(raf::conv::String3dVector(sub[1],','));
			core::vector3df rotazione(0,atoi(sub[2].c_str()),0);
			AddFalgat(posizione,rotazione);			
		}//if(comando=="falgat")	
		else if(comando=="rhino") {//aggiunge un falgat
			core::vector3df posizione(raf::conv::String3dVector(sub[1],','));
			core::vector3df rotazione(0,atoi(sub[2].c_str()),0);
			AddRhino(posizione,rotazione);			
		}//if(comando=="rhino")	
		else if(comando=="zombie") {//aggiunge un falgat
			core::vector3df posizione(raf::conv::String3dVector(sub[1],','));
			core::vector3df rotazione(0,atoi(sub[2].c_str()),0);
			AddZombie(posizione,rotazione);			
		}//if(comando=="rhino")	
		//end of enemies

		//munitions
		else if(comando=="ammunation_shot_gun") {
			core::vector3df posizione(raf::conv::String3dVector(sub[1],','));
			core::vector3df rotazione(0,atoi(sub[2].c_str()),0);
			int value=atoi(sub[3].c_str());
			AddAmmunationShotGun(posizione,rotazione,value);
		}	
		else if(comando=="ammunation_rifle_gun") {
			core::vector3df posizione(raf::conv::String3dVector(sub[1],','));
			core::vector3df rotazione(0,atoi(sub[2].c_str()),0);
			int value=atoi(sub[3].c_str());
			AddAmmunationRifleGun(posizione,rotazione,value);
		}	
		else if(comando=="ammunation_machine_gun") {
			core::vector3df posizione(raf::conv::String3dVector(sub[1],','));
			core::vector3df rotazione(0,atoi(sub[2].c_str()),0);
			int value=atoi(sub[3].c_str());
			AddAmmunationMachineGun(posizione,rotazione,value);
		}	
		//fine codice per ammunation

		else if(comando=="addzip") {//aggiunge un archivio zip
			sub[1]="levels\\"+sub[1];
			bool aperto=file_system->addZipFileArchive(sub[1].c_str());
			if(aperto==false) {
				string mess="Errore nel file \""+script_file+"\" alla riga "+raf::conv::NumString(a)+"\nImpossibile aprire il file zip "+sub[1]+"\nIl gioco sarà terminato per un errore nel livello\nSelezionare un altro livello";			
				raf::errore(mess);				
				exit(0);
			}
		}

		else if(comando=="medikit") {//aggiunge un medikit
			core::vector3df pos=raf::conv::String3dVector(sub[1],',');
			float rot_y_medikit=atof(sub[2].c_str());
			AddMedikit(pos,core::vector3df(0,rot_y_medikit,0),15);
		}//if(medikit)
		else if(comando=="medikitEx") {//aggiunge un medikit
			core::vector3df pos=raf::conv::String3dVector(sub[1],',');
			float rot_y_medikit=atof(sub[2].c_str());
			int life=atoi(sub[3].c_str());
			AddMedikit(pos,core::vector3df(0,rot_y_medikit,0),life);
		}//if(medikit)


		else if(comando=="armour") {//aggiunge un medikit
			core::vector3df pos=raf::conv::String3dVector(sub[1],',');
			float rot_y=atof(sub[2].c_str());
			int value=atoi(sub[3].c_str());
			AddArmour(pos,core::vector3df(0,rot_y,0),value);
		}//if(medikit)

		//aggiunge una lampadina
		else if(comando=="light") {//aggiunge una lampadina
			if(dl==false) {
				core::vector3df position=raf::conv::String3dVector(sub[1],',');
				float raggio=atof(sub[2].c_str());
				scene::ILightSceneNode* node=smgr->addLightSceneNode(NULL, position, video::SColorf(1.0f,1.0f,1.0f,1.0f),raggio);
			}//if(dl==false) 
		}//if(lampadina)
		else if(comando=="fire") {
			scene::IParticleSystemSceneNode* ps = smgr->addParticleSystemSceneNode(
				false,
				0, 
				-1,
				core::vector3df(100,120,600),
				core::vector3df(0,0,0),
				core::vector3df(2,2,2)
				);
			ps->setParticleSize(core::dimension2d<f32>(20.0f, 10.0f));
			scene::IParticleAffector* paf =ps->createFadeOutParticleAffector();
			ps->addAffector(paf);
			paf->drop();
			ps->setMaterialFlag(video::EMF_LIGHTING, false);
			ps->setMaterialTexture(0,driver->getTexture("media\\texture\\fire.bmp"));
			ps->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
			float posx,posy,posz;
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
		}

		else if(comando=="addskybox") {
			// create default
		scene::ISceneNode* skyboxNode = smgr->addSkyBoxSceneNode(
		driver->getTexture("media\\texture\\sky\\irrlicht2_up.jpg"),
		driver->getTexture("media\\texture\\sky\\irrlicht2_dn.jpg"),
		driver->getTexture("media\\texture\\sky\\irrlicht2_lf.jpg"),
		driver->getTexture("media\\texture\\sky\\irrlicht2_rt.jpg"),
		driver->getTexture("media\\texture\\sky\\irrlicht2_ft.jpg"),
		driver->getTexture("media\\texture\\sky\\irrlicht2_bk.jpg"));

		}

		else if(comando=="skybox") {
			sub[1]="levels\\"+sub[1];
			sub[2]="levels\\"+sub[2];
			sub[3]="levels\\"+sub[3];
			sub[4]="levels\\"+sub[4];
			sub[5]="levels\\"+sub[5];
			sub[6]="levels\\"+sub[6];

			scene::ISceneNode* skyboxNode = smgr->addSkyBoxSceneNode(
		driver->getTexture(sub[1].c_str()),
		driver->getTexture(sub[2].c_str()),
		driver->getTexture(sub[3].c_str()),
		driver->getTexture(sub[4].c_str()),
		driver->getTexture(sub[5].c_str()),
		driver->getTexture(sub[6].c_str()));
		}

		else if(comando=="terrain") {
			core::vector3df position=raf::conv::String3dVector(sub[1],',');
			core::vector3df rotation=raf::conv::String3dVector(sub[2],',');
			core::vector3df scale=raf::conv::String3dVector(sub[3],',');
			string heightmap="levels\\"+sub[4];
			string texture="levels\\"+sub[5];
			string detail_texture="levels\\"+sub[6];
			float scale1=atof(sub[7].c_str());
			float scale2=atof(sub[8].c_str());
			
			//test
			script.IsExistFatal(heightmap);
			script.IsExistFatal(texture);
			script.IsExistFatal(detail_texture);
			//end of test

			scene::ITerrainSceneNode* terr=smgr->addTerrainSceneNode(heightmap.c_str());
			terr->setPosition(position);
			terr->setRotation(rotation);
			terr->setScale(scale);
			terr->setMaterialTexture(0,driver->getTexture(texture.c_str()));
			terr->setMaterialTexture(1,driver->getTexture(detail_texture.c_str()));
			terr->scaleTexture(scale1,scale2);

			terr->setMaterialType(video::EMT_DETAIL_MAP);

			scene::ITriangleSelector* terr_tri=smgr->createTerrainTriangleSelector(terr);
			terr->setTriangleSelector(terr_tri);
			world_selector->addTriangleSelector(terr_tri);
			terr_tri->drop();
		}

		else if(comando=="camera") {
			//ignore the command
			continue;
		}
		else {
			if(this_file_ver>ares_version)
				raf::FatalError("This file has been produced with a following version of Ares and it is not possible to load it correctly. Please download from the site http://aresfps.sf.net the current version of Ares to load this file correctly. Press ok to close Ares.");
			else
				script.ComandoNonValidoFatal();
		}
	}//for esterno
	//FINE LINGUAGGIO DI SCRIPT "ARES LEVEL BUILD"
}
