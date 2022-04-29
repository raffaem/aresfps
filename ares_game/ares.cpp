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
#include <cmath>
#include <irrlicht.h>
#include "func.hpp"
#include "classi.hpp"
#include "irrlicht class.hpp"
#include "script.hpp"
#include <direct.h>//contiene la definizione di _chdir

using namespace irr;
using namespace std;

#pragma comment(lib, "irrlicht.lib")
#pragma comment(lib, "lua5.1.lib")
#pragma comment(lib, "tolua++5.1.lib")

//importa le funzioni di ares-runtime
#ifdef _DEBUG
#pragma comment(lib,"..\\ares_runtime\\debug\\ares_runtime.lib")
#else
#pragma comment(lib,"..\\ares_runtime\\release\\ares_runtime.lib")
#endif

//GLOBALI
#include "var.hpp"
//bool _DEBUG=false;

int main(int argc,char** argv)
{
	prog_path=raf::String::EraseFileNameFromPath(argv[0]);
	if(prog_path[prog_path.size()-1]=='\"')
		prog_path.erase(prog_path.size()-1,1);
	prog_path=raf::UpDir(prog_path);
	_chdir(prog_path.c_str());

	leggi_impostazioni_utente();
	NullReceiver null_receiver;
	device->setEventReceiver(&null_receiver);

	smgr = device->getSceneManager();
	driver = device->getVideoDriver();

	//ini loading scene
	IniNowLoadingWindow();
	ShowNowLoading(0);
	//end of init loading

	atexit(CorrectExit);

	ares_version=raf::GetAresFPSVerFromReg();
	raf::InizializzaRaf(device);
	file_system=device->getFileSystem();
	collision_smgr=smgr->getSceneCollisionManager();
	cursor_control=device->getCursorControl();

	//SET CAPTION
	std::string caption="Ares FPS ver. "+raf::conv::NumString(ares_version)+" by Mancuso Raffaele";
	wchar_t* caption_w=raf::conv::CharWChar_T(caption.c_str());
	device->setWindowCaption(caption_w);
	delete caption_w;

	//INIZIALIZATION
	ShowNowLoading(10);
	//load fonts
	font = device->getGUIEnvironment()->getFont("media\\font.bmp");
	font_to_show_objs_value=device->getGUIEnvironment()->getFont("media\\font_to_show_objs_value.bmp");
	//load interface texture
	life_icon=driver->getTexture("media\\interface\\life_icon.bmp");
	armour_icon=driver->getTexture("media\\interface\\armour.bmp");
	ammunation_icon=driver->getTexture("media\\interface\\ammunation.bmp");
	//end
	mirino=driver->getTexture("media\\cursor\\mirino.bmp");
	//carica la texture del proiettile
	proiettile_texture=driver->getTexture("media\\texture\\particle.bmp");
	//rende il bianco del mirino trasparente
	driver->makeColorKeyTexture(mirino,irr::core::position2d<irr::s32>(0,0));
	driver->makeColorKeyTexture(life_icon,irr::core::position2d<irr::s32>(0,0));
	driver->makeColorKeyTexture(armour_icon,irr::core::position2d<irr::s32>(0,0));
	driver->makeColorKeyTexture(ammunation_icon,irr::core::position2d<irr::s32>(0,0));
	//ini static blood
	scene::IAnimatedMesh* static_blood_file=smgr->getMesh("media\\models\\blood.md2");
	static_blood_file_mesh=static_blood_file->getMesh(0);
	static_blood_texture=driver->getTexture("media\\texture\\blood.tga");
	//ini dynamic blood texture
	dynamic_blood_texture=driver->getTexture("media\\texture\\dynamic_blood.bmp");
	driver->makeColorKeyTexture(dynamic_blood_texture,core::position2d<s32>(0,0));
	dynamic_blood_texture->regenerateMipMapLevels();
	//textures
	falgat_bullet=driver->getTexture("media\\texture\\particlered.bmp");
	rhino_bullet=driver->getTexture("media\\texture\\rhino_bullet.bmp");
	smoke_texture=driver->getTexture("media\\texture\\smoke.bmp");

	//load phisics
	ShowNowLoading(20);
	//TO ACTIVE
	//p_world=raf::Newt::createPhisicsWorld();

	//ini sound
	ShowNowLoading(30);
	sound.Initialize();
	Initialize();
	
	ShowNowLoading(50);
	carica_mappa();	

	ShowNowLoading(60);

	//inizialize the position of the target

	centro_mirino.X=centro_x-8;
	centro_mirino.Y=centro_y-8;

	device->getCursorControl()->setPosition(centro_x,centro_y);//mette il mouse al centro;
	int lastFPS=-1;
	int anima_falgat=0;

	cursor_control->setVisible(false);

	camera->setPosition(core::vector3df(0,0,-5)); //aggiusta la posizione della telecamera 
	weapon->actual_weapon->ogg->addChild(camera);
	
	ShowNowLoading(70);
	if(play_back_mus)
		LoadTracks();
	else 
		tracks_list_empty=true;
	
	//INI PHISICS
	ShowNowLoading(80);

	/*
	weapon->actual_weapon->p_node->SetPosition(weapon->actual_weapon->ogg->getPosition());	
	for(int i=0;i<world_nodes.size();i++) {
		world_nodes[i].p_node=p_world->AddOctTreeSceneNodeAsMap(world_nodes[i].node,world_nodes[i].mesh);
	}
	*/
	/*
	for(i=0;i<nem.size();i++) {
		nem[i].p_node=p_world->AddSceneNode((scene::ISceneNode*)nem[i].ogg,nem[i].mesh);
		nem[i].p_node->SetPosition(nem[i].ogg->getPosition());
		//nem[i].p_node->AddForce(core::vector3df(0,50,0));
	}
	*/

	ChangeWeaponCollision();

	ShowNowLoading(90);

	UpdateLife();
	UpdateArmour();
	UpdateAmmunation();

	ShowNowLoading(95);
	LuaScript();

	weapon->SetLastWeaponPosUnlikeWeaponPos();
	last_time=device->getTimer()->getTime();

	SpecularHightLights();

	//driver->setAmbientLight(video::SColor(0,60,60,60));
	//deinit loading window
	//ShowNowLoading(100);
	loading_bar->remove();
	loading_bar->drop();
	loading_smgr->drop();

	for(int i=0;i<2;i++) {
	//execute these instructions to update the positionof all objs to not have probs with ai and weapon movement
	driver->beginScene(true,true, video::SColor(0,90,90,156));
	smgr->drawAll();
	driver->endScene();
	//end
	}
	
	device->setEventReceiver(&eventi);

	while(device->run()){

		//update phisic
		/*
		weapon->actual_weapon->p_node->AddGravityForce();
		weapon->actual_weapon->p_node->UpdateUserData();
		p_world->Update(device);
		*/

		//update sound
		sound.Update();

		//-----------------------------------------------------
		core::vector3df p=weapon->actual_weapon->ogg->getAbsolutePosition();
		camera->setTarget(p);		
		//-------------------------------------------------

		//to jump
		if(now_jumping) {

			value_to_jump-=loop_decrement_jump;
			weapon->actual_weapon->ogg->MuoviY(value_to_jump);

			if(value_to_jump<=0) {
				ChangeWeaponCollision();
				value_to_jump=start_speed_jump;
				now_jumping=false;
			}
		}
		//end of to jump

		//die if
		if(gravityanim->isFalling()) {}
		//end of die if

		//erase text after certain time
		u32 text_time_trascorred=device->getTimer()->getTime()-time_text_creation;
		if((testo != NULL) && text_time_trascorred>5000)
		{
			testo->remove();
			testo=NULL;
		}
		//end

		driver->beginScene(true,true, video::SColor(0,90,90,156));

		//fermo
		anim_weapon=0;

		cursor_control->setPosition(centro_x,centro_y);
		//bool falgat_cammina=false;		
		//CHIAMATA ALLE FUNZIONI
	
		//if(time_trascorred_for_enemy_ai>2500) {

		for(int i=0;i<nem.size();i++) {
			if(nem[i].ogg->getPosition().getDistanceFrom(weapon->actual_weapon->ogg->getPosition())<=distance_between_enemy_weapon_to_active&&
				!lose) {
				AI_BOT(i);
			}
		}

		collisione_weapon_con_oggetti();
		CeckIfEnemiesStrikeWeapon();
		//FINE CHIAMATA ALLE FUNZIONI
		smgr->drawAll();

		//visualizza il mirino
		if(mirino_bool)
			driver->draw2DImage(mirino,centro_mirino,core::rect<s32>(0,0,16,16),0,video::SColor(255,255,255,255),true);

		driver->draw2DImage(life_icon,life_icon_position,core::rect<s32>(0,0,16,16),0,video::SColor(255,255,255,255),true);
		driver->draw2DImage(armour_icon,armour_icon_position,core::rect<s32>(0,0,16,16),0,video::SColor(255,255,255,255),true);
		driver->draw2DImage(ammunation_icon,ammunation_icon_position,core::rect<s32>(0,0,16,16),0,video::SColor(255,255,255,255),true);
		driver->endScene();

		/*
		static int time=0;
		if(now_jumping) {
		if(weapon->last_weapon_pos.Y==weapon->actual_weapon->ogg->getPosition().Y){
		*/
				/*
				ChangeWeaponCollision();
				value_to_jump=start_speed_jump;
				now_jumping=false;
				*/
				
		/*
				time++;
			}

			if(time>=2) {
				ChangeWeaponCollision();
				value_to_jump=start_speed_jump;
				now_jumping=false;
			}
		}
		*/

		weapon->last_weapon_pos=weapon->actual_weapon->ogg->getPosition();
		last_time=device->getTimer()->getTime();

		//play user tracks
		if(!tracks_list_empty)
			PlayTracks();
	}//fine loop
	return 0;
}//fine programma

