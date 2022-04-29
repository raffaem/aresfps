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

#include "stdafx.h"
#include "ammunation.hpp"

void AddMedikit(core::vector3df posizione,core::vector3df rotazione,int life) {
	raf::ChangeCurrentDirTo(prog_dir);

	//lo atterra
	//posizione=raf::Land(posizione,raf::PrendiSelector(),0);

	scene::IMesh* medikit_mesh=smgr->getMesh("media\\models\\medikit.md2")->getMesh(1);

	scene::ISceneNode* node=smgr->addMeshSceneNode(
		medikit_mesh,
		0,//parent
		-1,//id
		posizione,
		rotazione
		);

	node->setMaterialTexture(0,driver->getTexture("media\\texture\\medikit_for_level_editor.jpg"));
	raf::DiffuseLight(node,dl);

	int pos=MedikitsGetFreePosition();
	medikits[pos].ogg=node;
	medikits[pos].life=life;

	//set the ID
	//è un medikit
	string ID;
	ID+=type::medikit;
	//e si trova nella posizione n del vettore
	ID+=raf::conv::NumString(pos);			
	node->setID(atoi(ID.c_str()));

	raf::RestoreDir();
}

void AddArmour(core::vector3df posizione,core::vector3df rotazione,int armour) {
		raf::ChangeCurrentDirTo(prog_dir);

	//lo atterra
	//posizione=raf::Land(posizione,raf::PrendiSelector(),0);

	scene::IMesh* armour_mesh=smgr->getMesh("media\\models\\armour.md2")->getMesh(0);

	scene::ISceneNode* node=smgr->addMeshSceneNode(
		armour_mesh,
		0,//parent
		-1,//id
		posizione,
		rotazione
		);

	node->setMaterialTexture(0,driver->getTexture("media\\texture\\armour.jpg"));
	raf::DiffuseLight(node,dl);

	int pos=ArmourGetFreePosition();
	armours[pos].ogg=node;
	armours[pos].armour=armour;

	//set the ID
	//è una armatura
	string ID;
	ID+=type::armour;
	//e si trova nella posizione n del vettore
	ID+=raf::conv::NumString(pos);			
	node->setID(atoi(ID.c_str()));
}

void AddFalgat(core::vector3df posizione,core::vector3df rotazione) {
	raf::ChangeCurrentDirTo(prog_dir);

	const float radius=35;

	/*
	core::vector3df correct_position=raf::Land(posizione,raf::PrendiSelector());
	if(correct_position!=posizione) 
		correct_position.Y+=radius;
		*/

	level_editor::Enemies* node=(level_editor::Enemies*)smgr->addAnimatedMeshSceneNode(
					smgr->getMesh("media\\models\\rigell.ms3d"),
					0,//parent
					-1,//id
					posizione,//position
					rotazione//rotation
					);

	node->setFrameLoop(50,50);
	node->setMaterialTexture(0,driver->getTexture("media\\texture\\rigell.bmp"));
	raf::DiffuseLight(node,dl);
	node->SetEnemieType(ET_FALGAT);
	node->SetRadius(radius);
	int pos=EnemiesGetFreePosition();
	enemies[pos]=node;
	//set the ID
	//è un nemico
	string ID;
	ID+=type::enemie;
	//e si trova nella posizione n del vettore
	ID+=raf::conv::NumString(pos);			
	node->setID(atoi(ID.c_str()));

	//prende la mano destra
	scene::ISceneNode* right_hand=node->getMS3DJointNode("Bip01 R Hand");
	if(right_hand==0||right_hand==NULL) {
		raf::FatalError("joint error");
	}

	//carica l'arma da attaccare alla mano destra
	scene::ISceneNode* falgat_weapon=smgr->addMeshSceneNode(
		smgr->getMesh("media\\models\\spacegun.ms3d")->getMesh(1));
	falgat_weapon->setMaterialTexture(0,driver->getTexture("media\\texture\\spacegun.bmp"));
	raf::DiffuseLight(falgat_weapon,dl);
	
	//attacca l'arma alla mano destra
	right_hand->addChild(falgat_weapon);
	//setta la variabile weapon all'arma appena attaccata
	node->SetAttachedWeapon(falgat_weapon);

	//sistema la posizione dell'arma
	//prende posizione e rotazione
	core::vector3df rot=falgat_weapon->getRotation();
	core::vector3df scale=falgat_weapon->getScale();

	//la ruota per metterla diritta
	rot.X+=90.0f;
	rot.Z+=90.0f;

	//ne riduce le dimensioni perchè è troppo grande
	float scale_factor=-0.4f;
	scale.X+=scale_factor;
	scale.Y+=scale_factor;
	scale.Z+=scale_factor;

	//applica le modifiche
	//setta la nuova rotazione e la nuova scala
	falgat_weapon->setRotation(rot);
	falgat_weapon->setScale(scale);
}

void AddRhino(core::vector3df posizione,core::vector3df rotazione) {
	raf::ChangeCurrentDirTo(prog_dir);

	const float radius=30;

	/*
	core::vector3df correct_position=raf::Land(posizione,raf::PrendiSelector());
	if(correct_position!=posizione) 
		correct_position.Y+=radius;
		*/

	scene::IAnimatedMeshSceneNode* irr_node=smgr->addAnimatedMeshSceneNode(
					smgr->getMesh("media\\models\\rhino.md2"),
					0,//parent
					-1,//id
					posizione,//position
					rotazione//rotation
					);

	level_editor::Enemies* node=(level_editor::Enemies*)irr_node;

	node->setMD2Animation("rhino");
	node->setMaterialTexture(0,driver->getTexture("media\\texture\\rhino.jpg"));
	raf::DiffuseLight(node,dl);
	node->SetEnemieType(ET_RHINO);
	node->SetRadius(30);
	node->SetAttachedWeapon(NULL);
	int pos=EnemiesGetFreePosition();
	enemies[pos]=node;

	//set the ID
	//è un nemico
	string ID;
	ID+=type::enemie;
	//e si trova nella posizione n del vettore
	ID+=raf::conv::NumString(pos);			
	node->setID(atoi(ID.c_str()));
}

void AddZombie(irr::core::vector3df posizione,irr::core::vector3df rotazione) {
	raf::ChangeCurrentDirTo(prog_dir);

	float yradius=44.0f;

	//decidiamo la posizione
	/*
	core::vector3df correct_pos=raf::Land(posizione,world_selector);
	if(correct_pos!=posizione)
		correct_pos.Y+=yradius;
		*/
	
	scene::IAnimatedMesh * zombiefile = smgr->getMesh("media\\models\\zombie.md2");
	level_editor::Enemies* temp = static_cast<level_editor::Enemies*>(smgr->addAnimatedMeshSceneNode(
		zombiefile,
		0,//parent
		-1,//id
		posizione,
		rotazione
		));
	temp->setScale(core::vector3df(3.9f,3.9f,3.9f));

	temp->addShadowVolumeSceneNode();
	temp->setMaterialTexture(0, driver->getTexture("media\\texture\\zombie.jpg"));
	raf::DiffuseLight(temp,dl);

	temp->setFrameLoop(1,1);
		 
	/* lo metto nel vettore */
	temp->SetEnemieType(ET_ZOMBIE);
	temp->SetRadius(yradius);
	temp->SetAttachedWeapon(NULL);
	int pos=EnemiesGetFreePosition();
	enemies[pos]=temp;

	//set the ID
	//è un nemico
	string ID;
	ID+=type::enemie;
	//e si trova nella posizione n del vettore
	ID+=raf::conv::NumString(pos);			
	temp->setID(atoi(ID.c_str()));
}

int AddLight(core::vector3df position,float raggio/*=100.0f*/) {
	if(dl==true&&loader_execute==false) 
		raf::errore("WARNING:The addition of this light won't have effects until the diffuse light it will be active.\nTo deactive diffuse light click on world->Deactive diffuse ligh");
	
	raf::ChangeCurrentDirTo(prog_dir);
	int free_position=LightsGetFreePosition();

	scene::ILightSceneNode* node=smgr->addLightSceneNode(
		NULL,
		position,
		video::SColorf(1.0f,1.0f,1.0f,0.0f),
		raggio);

	//create a billboard
	scene::IBillboardSceneNode* bill=smgr->addBillboardSceneNode(
		0,//parent
		core::dimension2d< f32 >(10.0f, 10.0f),//default size
		position
		);

	//set the texture of the billboard
	//driver->makeColorKeyTexture(bill_texture,core::position2d<s32>(0,0)); 
	bill->setMaterialTexture(0,bill_texture);
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
				
	raf::DiffuseLight(bill,true);	
				
	//set the ID at the light and at the billboard
	//è una luce
	string ID;
	ID+=type::light;
	//e si trova nella posizione n del vettore
	ID+=raf::conv::NumString(free_position);
	int ID_N=atoi(ID.c_str());
	node->setID(ID_N);
	bill->setID(ID_N);

	//li metto nel vettore
	level_editor::Light* temp=new level_editor::Light();
	temp->light=node;
	temp->bill=bill;
	temp->ray=raggio;
	lights[free_position]=temp;

	raf::RestoreDir();
	return free_position;
}
void AddLevelModel(string& modello,string& texture,core::vector3df posizione,core::vector3df rotazione,core::vector3df scale) {
	if(modello=="") return;

	scene::ISceneNode* node=raf::CaricaMappa(modello);

	if(node==NULL) {
		raf::errore("Error in the function AddLevelModel. Can't load this model. Maybe the model is carrupted or it is in an unsupported file format. Please contact Ares support. See readme for more information");
		return;
	}

	if(texture!="noTexture") {
		video::ITexture* texture_irr=driver->getTexture(texture.c_str());
		node->setMaterialTexture(0,texture_irr);
	}

	raf::DiffuseLight(node,dl);
	//avoid light calculation problem if scale
	node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS,true); 

	node->setPosition(posizione);
	node->setRotation(rotazione);
	node->setScale(scale);
	world_selector->addTriangleSelector(node->getTriangleSelector());

	//lo mette nel vettore
	level_editor::LevelModel* temp=new level_editor::LevelModel();
	temp->ogg=node;
	temp->model_path=modello;
	temp->texture_path=texture;

	int pos=LevelmodelGetFreePosition();
	level_models[pos]=temp;

	//setta l'id
	//è un modello di un livello
	string ID;
	ID+=type::level_model;
	//e si trova nella posizione n del vettore
	int size=pos;
	ID+=raf::conv::NumString(size);			
	node->setID(atoi(ID.c_str()));
}
void AddDefaultSkyBox() {
	raf::ChangeCurrentDirTo(prog_dir);

	//erase previous sky box
	if(skyboxNode!=NULL) {
		skyboxNode->remove();
		skyboxNode=NULL;
	}

	skyboxNode = smgr->addSkyBoxSceneNode(
		driver->getTexture("media\\texture\\sky\\irrlicht2_up.jpg"),
		driver->getTexture("media\\texture\\sky\\irrlicht2_dn.jpg"),
		driver->getTexture("media\\texture\\sky\\irrlicht2_lf.jpg"),
		driver->getTexture("media\\texture\\sky\\irrlicht2_rt.jpg"),
		driver->getTexture("media\\texture\\sky\\irrlicht2_ft.jpg"),
		driver->getTexture("media\\texture\\sky\\irrlicht2_bk.jpg"));
	sky_box.top="default";
}
//-----------------------------------------------------
void AddTerrain(std::string heightmap,
				std::string texture,
				std::string detail_texture,
				core::vector3df position,
				core::vector3df rotation,
				core::vector3df scale,
				float scale1,
				float scale2) {
	//convert eventual unix dir into win dir
	heightmap=raf::conv::UnixDirToWinDir(heightmap);
	texture=raf::conv::UnixDirToWinDir(texture);
	detail_texture=raf::conv::UnixDirToWinDir(detail_texture);
	//end of convert

	scene::ITerrainSceneNode* terr=smgr->addTerrainSceneNode(heightmap.c_str());
				
	raf::DiffuseLight(terr,dl);
	terr->setMaterialType(video::EMT_DETAIL_MAP);

	//set texture
	if(texture!="") {
		video::ITexture* texture_p=driver->getTexture(texture.c_str());
		if(!texture_p) {
			raf::errore("Texture not found or it is not in a supported format");
			terr->remove();
			return;
		}
		terr->setMaterialTexture(0,texture_p);
	}

	//set detail texture
	if(detail_texture!="") {
		video::ITexture* dtexture=driver->getTexture(detail_texture.c_str());
		if(!dtexture) {
			raf::errore("Detail texture not found or it is not in a supported format");
			terr->remove();
			return;
		}
		terr->setMaterialTexture(1,dtexture);
	}
	terr->setPosition(position);
	terr->setRotation(rotation);
	terr->setScale(scale);
	terr->scaleTexture(scale1,scale2);

	//compile class
	level_editor::Terrain* t=new level_editor::Terrain();
	t->ogg=terr;
	t->heightmap=heightmap;
	t->texture=texture;
	t->detail_texture=detail_texture;
	t->scale1=scale1;
	t->scale2=scale2;
	int pos=TerrainGetFreePosition();
	terrain_nodes[pos]=t;

	//set the id
	//setta l'id
	//è un terreno
	string ID;
	ID+=type::terrain;
	//e si trova nella posizione n del vettore
	ID+=raf::conv::NumString(pos);			
	terr->setID(atoi(ID.c_str()));
}
void AddAmmunationShotgun(core::vector3df posizione,core::vector3df rotazione,int num_of_bullets/*=15*/) {
	raf::ChangeCurrentDirTo(prog_dir);

	//lo atterra
	//posizione=raf::Land(posizione,raf::PrendiSelector());

	scene::IMesh* medikit_mesh=smgr->getMesh("media\\models\\shotgun_ammunation.md2")->getMesh(0);
	scene::ISceneNode* node=smgr->addMeshSceneNode(
		medikit_mesh,
		0,//parent
		-1,//id
		posizione,
		rotazione
		);
	node->setMaterialTexture(0,driver->getTexture("media\\texture\\shotgun_ammunation.jpg"));
	raf::DiffuseLight(node,dl);

	Ammunation* amm=new Ammunation;
	amm->ogg=node;
	amm->num_of_bullets=15;
	amm->type=EAT_SHOTGUN;
	int pos=AmmunationGetFreePosition();
	ammunation[pos]=amm;
								
	//set the ID
	//è una ricarica
	string ID;
	ID+=type::ammunation;
	//e si trova nella posizione n del vettore
	ID+=raf::conv::NumString(pos);			
	node->setID(atoi(ID.c_str()));
}
void AddAmmunationMachinegun(core::vector3df posizione,core::vector3df rotazione,int num_of_bullets/*=15*/) {
	raf::ChangeCurrentDirTo(prog_dir);

	//lo atterra
	//posizione=raf::Land(posizione,raf::PrendiSelector());

	scene::IMesh* medikit_mesh=smgr->getMesh("media\\models\\machinegun_ammunation.md2")->getMesh(0);
	scene::ISceneNode* node=smgr->addMeshSceneNode(
		medikit_mesh,
		0,//parent
		-1,//id
		posizione,
		rotazione
		);
	node->setMaterialTexture(0,driver->getTexture("media\\texture\\machinegun_ammunation.jpg"));
	raf::DiffuseLight(node,dl);

	Ammunation* amm=new Ammunation;
	amm->ogg=node;
	amm->num_of_bullets=15;
	amm->type=EAT_MACHINEGUN;
	int pos=AmmunationGetFreePosition();
	ammunation[pos]=amm;
								
	//set the ID
	//è una ricarica
	string ID;
	ID+=type::ammunation;
	//e si trova nella posizione n del vettore
	ID+=raf::conv::NumString(pos);			
	node->setID(atoi(ID.c_str()));
}
void AddAmmunationRiflegun(core::vector3df posizione,core::vector3df rotazione,int num_of_bullets/*=15*/) {
	raf::ChangeCurrentDirTo(prog_dir);

	//lo atterra
	//posizione=raf::Land(posizione,raf::PrendiSelector());

	scene::IMesh* medikit_mesh=smgr->getMesh("media\\models\\riflegun_ammunation.md2")->getMesh(0);
	scene::ISceneNode* node=smgr->addMeshSceneNode(
		medikit_mesh,
		0,//parent
		-1,//id
		posizione,
		rotazione
		);
	node->setMaterialTexture(0,driver->getTexture("media\\texture\\riflegun_ammunation.jpg"));
	raf::DiffuseLight(node,dl);

	Ammunation* amm=new Ammunation;
	amm->ogg=node;
	amm->num_of_bullets=15;
	amm->type=EAT_RIFLEGUN;
	int pos=AmmunationGetFreePosition();
	ammunation[pos]=amm;
								
	//set the ID
	//è una ricarica
	string ID;
	ID+=type::ammunation;
	//e si trova nella posizione n del vettore
	ID+=raf::conv::NumString(pos);			
	node->setID(atoi(ID.c_str()));
}

