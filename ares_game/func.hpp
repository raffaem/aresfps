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
#pragma once
#ifndef OUTLAW_CHILDREN_MANCUSO_RAFFAELE_V_1_00_FUNC_HPP_1343547843514387354
#define OUTLAW_CHILDREN_MANCUSO_RAFFAELE_V_1_00_FUNC_HPP_1343547843514387354
#include <irrlicht.h>
using namespace irr;
#include <string>
#include "evar.hpp"
#include "classi.hpp"

void IniNowLoadingWindow();
void LuaScript();
void ShowNowLoading(int progress);
void ClearLevel();
void Restart();
void ChangeWeaponCollision(bool diminuisci=false,bool no_gravity=false);
void IniText();
void Initialize();
void EnemiesAnimation(int num,int n);
void SpecularHightLights();

void esci(bool valore);
void CorrectExit();

void leggi_impostazioni_utente();	
void CaptureTheCurrentScreen();
void CreateDynamicBlood(core::vector3df position,core::vector3df rotation);
void LoadTracks();

//inline function definition
inline void CreateSmokeParticleSystem(core::vector3df pos,core::vector3df out);
inline void Shoot();
inline void ShootForPunch();
inline void WeaponAnimation(int n);
inline void CreateProgressBars();
inline void PlayTracks();
inline void CreateStaticBlood(int i);
inline void AI_BOT(int num);
inline void collisione_weapon_con_oggetti();
inline void CeckIfEnemiesStrikeWeapon();
inline void WeaponDamned(int damn);
inline void UpdateLife(bool elimina=true);
inline void UpdateArmour();
inline void UpdateAmmunation();
inline void gestione_messaggi(const wchar_t* stringa,bool remove_prev_text=true,bool create_remove_animator=true,bool execute_string_test=true);

//--------------------------INLINE FUNCTION---------------------------
inline void PlayTracks() {
	//the first time
	if(sound_tracks_index==-1) {
		++sound_tracks_index;

		//start the sound paused
		FMOD_RESULT result=sound.device->playSound(FMOD_CHANNEL_FREE,tracks_list[sound_tracks_index].sound,true,&tracks_list[sound_tracks_index].channel);
		if(result!=FMOD_OK)
			raf::FatalError("Cannot start FMOD stream.");
		//set volume
		tracks_list[sound_tracks_index].channel->setVolume(back_mus_volume);
		tracks_list[sound_tracks_index].channel->setPaused(false);
		return;
	}
	
	//play next song
	bool isPlaying;

	if(tracks_list[sound_tracks_index].channel)
		tracks_list[sound_tracks_index].channel->isPlaying(&isPlaying);
	else isPlaying=false;

	if(isPlaying==false) {
		++sound_tracks_index;

		if(sound_tracks_index>=tracks_list.size())
			sound_tracks_index=0;

		//start the sound paused
		FMOD_RESULT result=sound.device->playSound(FMOD_CHANNEL_FREE,tracks_list[sound_tracks_index].sound,true,&tracks_list[sound_tracks_index].channel);
		if(result!=FMOD_OK)
			raf::FatalError("Cannot start FMOD stream");
		//set volume
		tracks_list[sound_tracks_index].channel->setVolume(back_mus_volume);
		tracks_list[sound_tracks_index].channel->setPaused(false);
	}
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
//rotate
/*
	TO ERASE, slow

	core::vector3df weaponPos = weapon->actual_weapon->ogg->getPosition(); 
	core::vector3df enemyPos = nem[num].ogg->getPosition(); 
    float cateto1 = enemyPos.X - weaponPos.X; 
    float cateto2 = enemyPos.Z - weaponPos.Z; 
    float ipotenusa = sqrt((cateto1*cateto1)+(cateto2*cateto2)); 
    float radians = asinf(cateto1/ipotenusa); 
	float degrees = radians*irr::core::GRAD_PI;
	//la seguente riga serve per controllare se i triangolo si forma a destra     o a sinistra del nemico. 
    if(enemyPos.Z < weaponPos.Z)degrees = -degrees+180; 
	if(nem[num].type!=ET_ZOMBIE) degrees+=90;
    nem[num].ogg->NewRotationY(degrees); 
*/

inline void AI_BOT(int num)
{
	//active enemy
	nem[num].active=true;

	/*
			3D up view

	            Z
				^
				|
				|
				|
		--------+------> X
			    |
				|
				|
				|

			3d up view

     C(enemy)
	|\
	| \
	|  \
	|   \
	|-----
	A     B(weapon) 

    AC=enemy_pos_y-weapon_pos_y 
	AB=enemy_pos_x-weapon_pos_x 
	A_angle=90 degrees
	B_angle_radians=atan(AC/AB)
	B_angle_degrees=B_angle_radians*(180/3.1514)
	C_angle_degrees=90-B_angle_degrees
	*/

	core::vector3df weapon_pos= weapon->actual_weapon->ogg->getPosition(); 
	core::vector3df enemy_pos = nem[num].ogg->getPosition(); 
	float AB_segment=enemy_pos.X-weapon_pos.X; 
	float AC_segment=enemy_pos.Z-weapon_pos.Z; 
    float B_angle_degrees=atan2f(AC_segment,AB_segment)*irr::core::GRAD_PI; 
    float C_angle_degrees=90-B_angle_degrees; 

	if(nem[num].type!=ET_ZOMBIE)
		C_angle_degrees+=90;

	/*
	if(nem[num].type==ET_ZOMBIE)
		C_angle_degrees-=90;
		*/

    nem[num].ogg->NewRotationY(C_angle_degrees); 
	//END OF ROTATE

	//LINE BETWEEN ENEMY AND WEAPON
	core::line3d<f32> line;
	line.start=nem[num].ogg->getPosition();
	line.end=weapon->actual_weapon->ogg->getPosition();

	core::vector3df temp_out_for_collide;
	core::triangle3d<f32> temp_tri_for_collide;
	bool collide=smgr->getSceneCollisionManager()->getCollisionPoint(
		line,
		world_selector,
		temp_out_for_collide,
		temp_tri_for_collide);

	if(nem[num].type==ET_FALGAT)
		line.start=nem[num].attached_weapon->getAbsolutePosition();
	else
		line.start=nem[num].ogg->getPosition();
	//END

	//MOVE ENEMIE
	bool anim_bool=false;

	unsigned int current_time=device->getTimer()->getTime();
	if(nem[num].is_moving) {
		anim_bool=true;

		//moving end if it is finished
		if(current_time>=nem[num].time_moving_end) {
			nem[num].is_moving=false;
			anim_bool=false;

				//land the enemy
				core::vector3df position=nem[num].ogg->getPosition();
				raf::Land(
					position,
					world_selector,
					nem[num].yradius
					);
				//position.Y+=nem[num].yradius;
				nem[num].ogg->setPosition(position);
		}

		//if weapon position changes and x seconds has pass
		//moving ends
		if(weapon->actual_weapon->ogg->getPosition()!=nem[num].AI_last_weapon_pos&&
			current_time>=nem[num].time_moving_end_if_weapon_pos_change) {
				nem[num].is_moving=false;
				anim_bool=false;

				//land the enemy
				core::vector3df position=nem[num].ogg->getPosition();
				raf::Land(
					position,
					world_selector,
					nem[num].yradius
					);
				//position.Y+=nem[num].yradius;
				nem[num].ogg->setPosition(position);

		}

	}

	//if enemy is far from weapon and between enemy and weapon there is no walls and enemy isn't moving
	//move the enemy
	if((nem[num].ogg->getPosition().getDistanceFrom(
		weapon->actual_weapon->ogg->getPosition())>=distance_between_enemy_weapon_to_move)&&
		(!collide)&&
		!nem[num].is_moving) {
		
		core::line3d<f32> line_for_move;
		line_for_move.start=nem[num].ogg->getPosition();
		line_for_move.end=weapon->actual_weapon->ogg->getPosition();

		//reduce its lenght
		line_for_move.end=(line_for_move.end-line_for_move.start)/2.0+line_for_move.start; 

		//the end of the line is on floor?	
		core::line3d<f32> test_line;
		test_line.start=line_for_move.end;
		test_line.end=test_line.start;
		test_line.end.Y-=999999;
		core::vector3df out;
		core::triangle3df tri;
		if(smgr->getSceneCollisionManager()->getCollisionPoint(
		test_line,world_selector,out,tri)) {
			//if yes
			line_for_move.end=out;
			line_for_move.end.Y+=nem[num].yradius;
		}
		//end of test

		//animate
		unsigned int need_time=raf::itime(
				line_for_move.start,
				line_for_move.end,
				nem[num].speed
			);

		scene::ISceneNodeAnimator* move_anim=smgr->createFlyStraightAnimator(
			line_for_move.start,
			line_for_move.end,
			need_time
		); 

		nem[num].ogg->addAnimator(move_anim);
		move_anim->drop();
		anim_bool=true;
		EnemiesAnimation(num,1);

		nem[num].is_moving=true;
		nem[num].time_moving_end_if_weapon_pos_change=current_time+enemy_BOT_moving_end_if_weapon_pos_change;
		nem[num].AI_last_weapon_pos=weapon->actual_weapon->ogg->getPosition();
		nem[num].time_moving_end=current_time+need_time;

		nem[num].blood=false;
	}
	//END OF MOVE ENEMIE

	//ATTACK
	u32 time=device->getTimer()->getTime();
	u32 time_trascorred=time-nem[num].last_shoot;

	if(time_trascorred>=nem[num].time_between_two_shots&&
		!collide) {

		nem[num].last_shoot=time;

	//attack animation
	if(!anim_bool) {
		EnemiesAnimation(num,3);
		anim_bool=true;
	}

	// create fire ball 
	scene::IBillboardSceneNode* node = 0;
	node=smgr->addBillboardSceneNode(0, core::dimension2d<f32> (5, 5), line.start);

	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setMaterialTexture(0, *nem[num].bullet);
	node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

	//start.Y+=6.3f;

	//lenghtthen line BETA
	line.end=(line.end-line.start)*5+line.start; 

	u32 needed_time = raf::itime(line.start, line.end, 1.35f);

	scene::ISceneNodeAnimator* anim=smgr->createFlyStraightAnimator(
		line.start,
		line.end,
		needed_time);
	node->addAnimator(anim);
	anim->drop();

	//lo metto nel vettore
	enemies_shoot_class temp;
	temp.ogg=node;
	//temp.time_create=device->getTimer()->getTime();
	temp.time_erase=device->getTimer()->getTime()+needed_time;
	temp.damage=nem[num].damage;
	enemies_shoot.push_back(temp);

	//play the sound
	sound.Play(sound.enemies_shoot);
	//END OF ATTACK

	if(!anim_bool) {
		EnemiesAnimation(num,0);
	}

	}//if(time_trascorred>1000) {
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

inline void collisione_weapon_con_oggetti()
{
	for(int i = 0;i<collides_obj.size();i++)
	{
		float distance=weapon->actual_weapon->ogg->getPosition().getDistanceFrom(collides_obj[i].ogg->getPosition());

		if(distance>200.0f) {
			if(collides_obj[i].text!=NULL) {
			//erase text
			collides_obj[i].text->remove();
			collides_obj[i].text=NULL;
			}//if(collides_obj[i].text!=NULL) {
		}

		else {
			//show text
			if(collides_obj[i].text==NULL) {
				std::string text_to_show=raf::conv::NumString(collides_obj[i].int_value);
				wchar_t* text_to_show_w=raf::conv::CharWChar_T(text_to_show.c_str());
				core::vector3df pos=collides_obj[i].ogg->getPosition();
				pos.Y+=15.0f;
				collides_obj[i].text=smgr->addTextSceneNode(
					font_to_show_objs_value,
					text_to_show_w,
					video::SColor(0,0,0,0),
					0,//parent
					pos
					);
				delete text_to_show_w;

				collides_obj[i].text->setMaterialFlag(video::EMF_ZBUFFER,true);
				//collides_obj[i].text->setMaterialFlag(video::EMF_ZWRITE_ENABLE,true);
			}//if(collides_obj[i].text==NULL) {
		}//else {

		if(distance<=70.0f) {

			//erase the text
			if(collides_obj[i].text!=NULL) {
				collides_obj[i].text->remove();
				collides_obj[i].text=NULL;
			}//if(collides_obj[i].text!=NULL) {

			bool remove_medikit;
			int life_reload;
			int life_weapon_copy;

			switch(collides_obj[i].type) {

			case OWC_MEDIKIT:
				remove_medikit=true;

				if(vita_weapon == 100)
				{
					gestione_messaggi(L"YOU CAN'T TAKE OTHERS MEDIKITS");
					return;
				}

				life_weapon_copy=vita_weapon;

				life_reload=collides_obj[i].int_value;
				vita_weapon += life_reload;
	
				if(vita_weapon > 100)
				{
					life_reload=100-life_weapon_copy;
					collides_obj[i].int_value-=life_reload;

					vita_weapon = 100;
					remove_medikit=false;
				}

				UpdateLife();

				//play the sound
				sound.Play(sound.medikit);

				message_for_objs="LIFE +";
				message_for_objs+=raf::conv::NumString(life_reload);
				message_for_objs+="%";
				message_w=raf::conv::CharWChar_T(message_for_objs.c_str()); 
				gestione_messaggi(message_w);
				delete message_w;

				if(remove_medikit) {
					//elimina il medikit dalla scena
					collides_obj[i].ogg->remove();
					//lo elimina dal vettore
					collides_obj.erase(collides_obj.begin()+i);
				}
				break;

				//MUNITIONS
			case OWC_AMMUNATION_SHOT_GUN:
				weapon->shot_gun.ammunation+=collides_obj[i].int_value;
				UpdateAmmunation();
				message_for_objs="SHOT GUN BULLETS +";
				message_for_objs+=raf::conv::NumString(collides_obj[i].int_value);
				message_w=raf::conv::CharWChar_T(message_for_objs.c_str());
				gestione_messaggi(message_w);
				delete message_w;

				//elimina la munizione dalla scena
				collides_obj[i].ogg->remove();
				//lo elimina dal vettore
				collides_obj.erase(collides_obj.begin()+i);

				sound.Play(sound.ammunation);
				break;

			case OWC_AMMUNATION_MACHINE_GUN:
				weapon->machine_gun.ammunation+=collides_obj[i].int_value;
				UpdateAmmunation();
				message_for_objs="MACHINE GUN BULLETS +";
				message_for_objs+=raf::conv::NumString(collides_obj[i].int_value);
				message_w=raf::conv::CharWChar_T(message_for_objs.c_str());
				gestione_messaggi(message_w);
				delete message_w;

				//elimina la munizione dalla scena
				collides_obj[i].ogg->remove();
				//lo elimina dal vettore
				collides_obj.erase(collides_obj.begin()+i);

				sound.Play(sound.ammunation);

				break;

			case OWC_AMMUNATION_RIFLE_GUN:
				weapon->rifle_gun.ammunation+=collides_obj[i].int_value;
				UpdateAmmunation();
				message_for_objs="RIFLE GUN BULLETS +";
				message_for_objs+=raf::conv::NumString(collides_obj[i].int_value);
				message_w=raf::conv::CharWChar_T(message_for_objs.c_str());
				gestione_messaggi(message_w);
				delete message_w;

				//elimina la munizione dalla scena
				collides_obj[i].ogg->remove();
				//lo elimina dal vettore
				collides_obj.erase(collides_obj.begin()+i);

				sound.Play(sound.ammunation);

				break;
				//END OF MUNITIONS

			case OWC_ARMOUR:
				weapon_armour+=collides_obj[i].int_value;
				UpdateArmour();

				//play the sound
				sound.Play(sound.armor);

				//show message
				message_for_objs="ARMOUR +";
				message_for_objs+=raf::conv::NumString(collides_obj[i].int_value);
				message_for_objs+="%";
				message_w=raf::conv::CharWChar_T(message_for_objs.c_str());
				gestione_messaggi(message_w);
				delete message_w;

				//erase from the scene
				collides_obj[i].ogg->remove();
				//erase from the vector
				collides_obj.erase(collides_obj.begin()+i);
				break;

			}//switch

		}//if(distance<=70.0f) {
	}//for
}//function

//--------------------------------------------------------------------
//--------------------------------------------------------------------

inline void CeckIfEnemiesStrikeWeapon() {
	for(int i=0;i<enemies_shoot.size();i++) {

		//cek for strike
		if(weapon->actual_weapon->ogg->getPosition().getDistanceFrom(enemies_shoot[i].ogg->getPosition())<=20.0f) {
			//elimina il billboard
			enemies_shoot[i].ogg->remove();
			enemies_shoot.erase(enemies_shoot.begin()+i);
			WeaponDamned(enemies_shoot[i].damage);
			if(i>=enemies_shoot.size()) {break;}
		}

		//ceck if bullet complete its runs
		if(device->getTimer()->getTime()>=enemies_shoot[i].time_erase) {
			//erase the billboard if it complete its run
			enemies_shoot[i].ogg->remove();
			enemies_shoot.erase(enemies_shoot.begin()+i);
			if(i>=enemies_shoot.size()) {break;}
		}
	}
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

inline void gestione_messaggi(const wchar_t* stringa,bool remove_prev_text/*=true*/,bool create_remove_animator/*=true*/,bool execute_string_test/*=true*/)
{
	static const wchar_t* last_string=NULL;
	if(last_string==stringa&&
		weapon->last_weapon_pos==weapon->actual_weapon->ogg->getPosition()&&
		execute_string_test
		) {
		return;
	}
	last_string=stringa;

	//u32 time_trascorred=device->getTimer()->getTime()-time_text_creation;
	if((testo != NULL) && (remove_prev_text == true))
	{
		testo->remove();
		testo=NULL;
	}

	testo = smgr->addTextSceneNode
		(
			font,
			stringa,
			video::SColor(0, 255, 255, 255),
			weapon->actual_weapon->ogg,
			pos_text_ini
		);
	anim_testo = smgr->createFlyStraightAnimator(pos_text_ini, pos_text_fin, text_time,create_remove_animator?false:true);
	testo->addAnimator(anim_testo);
	anim_testo->drop();

	time_text_creation=device->getTimer()->getTime();

	/*
	if(create_remove_animator==true) {
		scene::ISceneNodeAnimator* anim_testo_delete=smgr->createDeleteAnimator(text_time);
		testo->addAnimator(anim_testo_delete);
		anim_testo_delete->drop();
	}
	*/

	/*
	else {
	//per farlo scorrere senza aspettare
		testo->removeAnimator(anim_testo);

		core::dimension2d<s32> screen_size=driver->getScreenSize();
		
		core::vector3df new_pos_text_fin;
		core::vector3df new_pos_text_ini=pos_text_ini;
		float speed=(0.3f*((centro.X*2)*(centro.Y*2)))/(800*600);

		//z e y uguali
		new_pos_text_fin.Z=pos_text_fin.Z;
		new_pos_text_fin.Y=pos_text_fin.Y;

		//x diverso
		new_pos_text_fin.X=-centro.X;

		int new_text_time=raf::itime(new_pos_text_ini,new_pos_text_fin,speed);

		anim_testo = smgr->createFlyStraightAnimator(new_pos_text_ini, new_pos_text_fin,new_text_time,true);
		testo->addAnimator(anim_testo);
		anim_testo->drop();				
	}
	*/
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

inline void UpdateLife(bool elimina)
{
	if(vita_weapon<=0) {
		vita_weapon=0;
		if(lose==false) {
			device->setEventReceiver(&you_lose_event_receiver);

			//play the sound
			sound.Play(sound.me_death);
			//visualizza il messaggio che hai perso
			gestione_messaggi(L"YOU LOSE. PRESS ENTER TO RESTART OR ESC TO EXIT....",true,false);
			weapon->actual_weapon->ogg->Trasparente("media\\texture\\nero.jpg");
			lose=true;
		}//if(lose==false) {
	}//if(vita_weapon<=0) {
	if(testo_vita != NULL && elimina == true)
	{
		testo_vita->remove();
	}

	vita_da_visualizzare = L"";
	vita_da_visualizzare += vita_weapon;
	vita_da_visualizzare +=L"%";

	testo_vita = smgr->addTextSceneNode
		(
			font,
			vita_da_visualizzare.c_str(),
			video::SColor(0, 0,0,0),
			weapon->actual_weapon->ogg,
			posizione_testo_vita,
			9999999
		);
	life_progress_bar->setProgress(vita_weapon);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

inline void UpdateArmour() {
	if(armour_text!= NULL)
	{
		armour_text->remove();
	}

	core::stringw armour_to_show = L"";
	armour_to_show += weapon_armour;
	armour_to_show +=L"%";

	armour_text = smgr->addTextSceneNode
	(
		font,
		armour_to_show.c_str(),
		video::SColor(0, 0,0,0),
		weapon->actual_weapon->ogg,
		armour_text_pos
	);
	armour_progress_bar->setProgress(weapon_armour);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

inline void UpdateAmmunation() {
	if(ammunation_text!= NULL)
	{
		ammunation_text->remove();
	}

	core::stringw ammunation_to_show = L"";
	ammunation_to_show += weapon->actual_weapon->ammunation;

	if(weapon->actual_weapon->infinite_munition) {
		//infinite symbol in unicode 221E
		ammunation_to_show=L"Infinite";
	}

	ammunation_text = smgr->addTextSceneNode
	(
		font,
		ammunation_to_show.c_str(),
		video::SColor(0, 0,0,0),
		weapon->actual_weapon->ogg,
		ammunation_text_pos
	);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

inline void CreateProgressBars() {
	life_progress_bar=new raf::VxHealthSceneNode(
		weapon->actual_weapon->ogg,//parent
		smgr,
		-1,//id
		smgr->getSceneCollisionManager(),
		65,//width 
		13,//height
		life_progress_bar_pos,//position
		video::SColor(150,0,200,0), // bar color 
		video::SColor(150,220,0,0), // background color 
		video::SColor(255,255,255,255) // boarder color 
		);

	armour_progress_bar=new raf::VxHealthSceneNode(
		weapon->actual_weapon->ogg,//parent
		smgr,
		-1,//id
		smgr->getSceneCollisionManager(),
		65,//width 
		13,//height
		armour_progress_bar_pos,//position
		video::SColor(150,0,0,200), // bar color 
		video::SColor(150,255,255,255), // background color 
		video::SColor(255,255,255,255) // boarder color 
		);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

inline void WeaponAnimation(int n)
{
	if(weapon->actual_weapon->type==MACHINE_GUN) {
		static int last_anim=-1;
		if(last_anim!=n) {
			last_anim=n;
			if(n==2) {
				weapon->actual_weapon->ogg->setMD2Animation("pow");
				weapon->actual_weapon->ogg->setAnimationSpeed(180);
			}
			if(n==0||n==1)  {
				weapon->actual_weapon->ogg->setMD2Animation("scene");
			}
		}//if(last_anim!=n) {
	}//if(weapon->actual_weapon->type==SHOT_GUN) {

	else if(n==2) {
			weapon->actual_weapon->ogg->setMD2Animation("pow");
			weapon->actual_weapon->ogg->setAnimationSpeed(100);
			weapon->actual_weapon->ogg->setLoopMode(false);
			can_shoot=false;
			weapon->actual_weapon->ogg->setAnimationEndCallback(&shot_guns_anim_callback);

			if(weapon->actual_weapon->type==PUNCH_GUN) {
				weapon->actual_weapon->ogg->setAnimationSpeed(150);
			}
	}//if(weapon->actual_weapon->type==SHOT_GUN) {
}//end of function

//--------------------------------------------------------------------
//--------------------------------------------------------------------

inline void WeaponDamned(int damn) {
	if(!immortal){

	sound.Play(sound.weapon_pain);

	driver->beginScene(true,true, video::SColor(127,255,0,0));
	driver->endScene();
	driver->beginScene(true,true, video::SColor(127,255,0,0));
	driver->endScene();
 
	weapon->actual_weapon->ogg->Cammina(4,'d');

	//substract life and armour	
	weapon_armour-=damn;

	if(weapon_armour<0) {
		//weapon_armour is negative
		vita_weapon+=weapon_armour; 
		weapon_armour=0;
		UpdateLife();
	}

	UpdateArmour();

	/*
	//PROPORTIONAL, INCOMPLETE
	total_armature:total_absorbed=this_armature:damn_absorbed
	damn_absorbed=(total_absorbed*this_armature)/total_armature
	int damn_armour=(damn*weapon_armour)/100;
	weapon_armour-=damn_armour;
	vita_weapon-=damn-damn_armour;
	UpdateLife();
	UpdateArmour();
	*/

	}
	//end
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

inline void ShootForPunch() {
	if(can_shoot==false)
		return;

	WeaponAnimation(2);

	for(int i=0;i<nem.size();i++) {
		float distance=weapon->actual_weapon->ogg->getPosition().getDistanceFrom(nem[i].ogg->getPosition());

		if(distance<35.0f) {

			CreateStaticBlood(i);

			nem[i].vita-=weapon->actual_weapon->damage;

			sound.Play(sound.punch);

			//create dynamic blood
			CreateDynamicBlood(nem[i].ogg->getPosition(),core::vector3df(0,0,0));

			if(nem[i].vita<=0) {
				//DIE!!
				nem[i].ogg->setLoopMode(false);
				EnemiesAnimation(i,2);

				/*				
				nem[i].p_node=p_world->AddSceneNode((scene::ISceneNode*)nem[i].ogg,nem[i].mesh);
				nem[i].p_node->AddForce(core::vector3df(300*nem[i].p_node->GetMass(),0,300*nem[i].p_node->GetMass()));
				nem[i].p_node->SetPosition(nem[i].ogg->getPosition());
				*/

				nem.erase(nem.begin()+i);

				//congratulations!!!you win
				if(nem.size()==0) {
					weapon->actual_weapon->ogg->Trasparente("media\\texture\\nero.jpg");
					lose=true;
					gestione_messaggi(L"CONGRATULATIONS!!YOU WIN. PRESS ENTER TO RESTART OR ESC TO EXIT.....",true,false);
					device->setEventReceiver(&you_lose_event_receiver);
					weapon->actual_weapon->ogg->Trasparente("media\\texture\\nero.jpg");
					WeaponAnimation(0);
				}//if(nem.size()==0) {
			}//if(nem[i]->vita<=0) {
		}//if(smgr->getSceneCollisionManager()->getCollisionPoint(
	}//for
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

inline void Shoot() {
	if(weapon->actual_weapon->type==PUNCH_GUN) {
		ShootForPunch();
		return;
	}

	if(weapon->actual_weapon->machine_gun_style==false&&
		can_shoot==false)
		return;

	if(weapon->actual_weapon->ammunation<=0)
	{
		sound.Stop(*weapon->actual_weapon->sound_shoot);
		sound.Play(sound.noammo);
		return;
	}

	weapon->actual_weapon->ammunation-=1;
	UpdateAmmunation();

	//play sound
	sound.Play(*weapon->actual_weapon->sound_shoot);

	anim_weapon=2;

	if (!world_selector)
		return;

	// get line 
	core::line3d<f32> line=smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(core::position2d<s32>(centro_x,centro_y));
	//end
	core::vector3df start=line.start;
	core::vector3df end=line.end;
	core::triangle3df triangle;
	// get intersection point with enemies
	core::vector3df contatto;
	bool hit=false;

	for(int i=0;i<nem.size();i++) {

		//ceck if the enemy is near
		if(nem[i].ogg->getPosition().getDistanceFrom(weapon->actual_weapon->ogg->getPosition())<distance_between_enemy_weapon_to_active) {
		
		if(smgr->getSceneCollisionManager()->getCollisionPoint(
				line,
				nem[i].ogg->getTriangleSelector(),
				contatto,
				triangle)) {
			
			hit=true;

			CreateStaticBlood(i);

			nem[i].vita-=weapon->actual_weapon->damage;

			//create dynamic blood
			CreateDynamicBlood(contatto,core::vector3df(0,0,0));

			if(nem[i].vita<=0) {
				//DIE!!
				nem[i].ogg->setLoopMode(false);
				EnemiesAnimation(i,2);

				/*				
				nem[i].p_node=p_world->AddSceneNode((scene::ISceneNode*)nem[i].ogg,nem[i].mesh);
				nem[i].p_node->AddForce(core::vector3df(300*nem[i].p_node->GetMass(),0,300*nem[i].p_node->GetMass()));
				nem[i].p_node->SetPosition(nem[i].ogg->getPosition());
				*/

				nem.erase(nem.begin()+i);

				//congratulations!!!you win
				if(nem.size()==0) {
					device->setEventReceiver(&you_lose_event_receiver);
					lose=true;
					gestione_messaggi(L"CONGRATULATIONS!!YOU WIN. PRESS ENTER TO RESTART OR ESC TO EXIT.....",true,false);
					weapon->actual_weapon->ogg->Trasparente("media\\texture\\nero.jpg");
					WeaponAnimation(0);
				}//if(nem.size()==0) {

			}//if(nem[i]->vita<=0) {
		}//if(smgr->getSceneCollisionManager()->getCollisionPoint(
		}//ceck if the enemy is near
	}//for

	if(hit==false) {
	if (smgr->getSceneCollisionManager()->getCollisionPoint(
		line, world_selector, end, triangle))
	{
		if(end.getDistanceFrom(weapon->actual_weapon->ogg->getPosition())<distance_between_enemy_weapon_to_active) {
			// collide with wall
			core::vector3df out = triangle.getNormal();
			out.setLength(0.03f);
			CreateSmokeParticleSystem(end,out);
		}
	}
	}//if(hit==false) {

	// create fire ball
	/*
	scene::ISceneNode* node = 0;
	node = smgr->addBillboardSceneNode(0,
		core::dimension2d<f32>(5,5), start);

	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setMaterialTexture(0, device->getVideoDriver()->getTexture("media\\texture\\particle.bmp"));
	node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
		
	u32 time=raf::itime(start,end,0.6f);

	scene::ISceneNodeAnimator* anim = 0;

	// set flight line

	anim = smgr->createFlyStraightAnimator(start, end, time);
	node->addAnimator(anim);	
	anim->drop();

	anim = smgr->createDeleteAnimator(time);
	node->addAnimator(anim);
	anim->drop();

	if (imp.when)
	{
		// create impact note
		imp.when = device->getTimer()->getTime() + (time - 100);
		ImpactsPushBack(imp);
	}
	*/
} //fine funzione

//--------------------------------------------------------------------
//--------------------------------------------------------------------

inline void CreateSmokeParticleSystem(core::vector3df pos,core::vector3df out) {
	// create smoke particle system
	irr::scene::IParticleSystemSceneNode* smoke_particle_system = smgr->addParticleSystemSceneNode(
		false
		/*
		0,
		-1,
		pos
		*/);

	smoke_particle_system->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	smoke_particle_system->setMaterialTexture(0, smoke_texture);
	smoke_particle_system->setMaterialType(irr::video::EMT_TRANSPARENT_VERTEX_ALPHA);
	smoke_particle_system->setParticleSize(irr::core::dimension2d<irr::f32>(10.0f, 10.0f));
	smoke_particle_system->setPosition(pos);

	irr::scene::IParticleAffector* paf = smoke_particle_system->createFadeOutParticleAffector();
	smoke_particle_system->addAffector(paf);
	paf->drop();

	irr::scene::IParticleEmitter* em = smoke_particle_system->createBoxEmitter(
		core::aabbox3d<f32>(-5,-5,-5,5,5,5),
		out,
		20,
		40,
		irr::video::SColor(0,255,255,255),
		irr::video::SColor(0,255,255,255),
		1200,
		1600,
		20);
	smoke_particle_system->setEmitter(em);
	em->drop();

	irr::scene::ISceneNodeAnimator* anim = smgr->createDeleteAnimator(2000);
	smoke_particle_system->addAnimator(anim);
	anim->drop();

	// play impact sound
	sound.Play(sound.impactSound);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

inline void CreateStaticBlood(int i) {
			//create static blood
			if(nem[i].blood==false) {
				nem[i].blood=true;
				scene::ISceneNode* static_blood=smgr->addMeshSceneNode(static_blood_file_mesh);
				static_blood->setMaterialTexture(0,static_blood_texture);
	
				core::vector3df pos=nem[i].ogg->getPosition();
				pos.Y-=nem[i].yradius-0.012;
				
				//INI CALC
				/*
				core::aabbox3d<f32> aabb=nem[i].ogg->getTransformedBoundingBox();
				core::line3d<f32> diagonal(aabb.MaxEdge,aabb.MinEdge);
				diagonal.start.Y=diagonal.end.Y;
				core::vector3df pos=diagonal.getMiddle();
				*/
				//END CALC

				static_blood->setPosition(pos);	
				static_blood->updateAbsolutePosition();
				raf::DiffuseLight(static_blood,dl);
			}
			}
#endif



