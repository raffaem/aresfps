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
#ifndef OUTLAW_CHILDREN_MANCUSO_rafFAELE_V_1_00_NEMICI_H_35143879687951054987651687
#define OUTLAW_CHILDREN_MANCUSO_rafFAELE_V_1_00_NEMICI_H_35143879687951054987651687
#pragma auto_inline(on)
#include <vector>
#include <irrlicht.h>
#include "..\\ares_runtime\\raf.hpp"

#include "weapon.hpp"
//load all weapons
#include "machine_gun.hpp"
#include "shot_gun.hpp"
#include "rifle_gun.hpp"
#include "punch_gun.hpp"

class arma {
public:
	shot_gun_class shot_gun;
	machine_gun_class machine_gun;
	rifle_gun_class rifle_gun;
	punch_gun_class punch_gun;

	//contiene l'indirizzo dell'arma attuale
	weapon_class* actual_weapon;

	core::vector3df last_weapon_pos;
	void SetLastWeaponPosUnlikeWeaponPos();
	void LoadWeapons();
	void ChangeWeapon(short new_weapon);
	void ToogleTrasparency();
};

//questa classe gestisce i nemici
enum ENEMIE_TYPE{
	ET_FALGAT,
	ET_RHINO,
	ET_ZOMBIE
};
class nemici {//classe che gestisce i nemici
public:
	//internal use
	u32 last_shoot;
	//end of internal use

	raf::OGGETTOANIMATO ogg;
	raf::SCENENODE attached_weapon;

	bool blood;
	bool active;

	bool is_moving;
	unsigned int time_moving_end;
	unsigned int time_moving_end_if_weapon_pos_change;
	core::vector3df AI_last_weapon_pos;

	int vita;
	ENEMIE_TYPE type;
	int time_between_two_shots;
	int damage;
	video::ITexture** bullet;
	float yradius;
	int last_animation;
	float speed;
	scene::IMesh* mesh;
	//raf::Newt::SceneNode* p_node;

	nemici::nemici():last_shoot(0),last_animation(-6),active(false),is_moving(false){};
};

//questa classe gestisce i billboard lanciati dai nemici
class enemies_shoot_class {
public:
	int damage;
	scene::IBillboardSceneNode* ogg;
	u32 time_create;
	u32 time_erase;
};

class shot_guns_anim_callback_class:public scene::IAnimationEndCallBack {
public:
	virtual void  OnAnimationEnd (scene::IAnimatedMeshSceneNode *node);
};

//class for management armour
class armour_class{
public:
	scene::ISceneNode* ogg;
	int value;
};

//objects that collide
const char OWC_MEDIKIT='0';
const char OWC_AMMUNATION_MACHINE_GUN='1';
const char OWC_AMMUNATION_SHOT_GUN='2';
const char OWC_AMMUNATION_RIFLE_GUN='3';
const char OWC_ARMOUR='4';

class obj_to_collide{
public:
	scene::ISceneNode* ogg;
	int int_value;
	scene::ITextSceneNode* text;
	char type;
};

class text_class{
public:
	scene::ITextSceneNode* ogg;
	u32 time_creation;
};

#endif
