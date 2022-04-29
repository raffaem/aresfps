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
#ifndef MANCUSO_RAFFAELE_ARES_8959846465160160874904765160804765
#define MANCUSO_RAFFAELE_ARES_8959846465160160874904765160804765

#include "..\\ares_runtime\\raf.hpp"
#include <string>
#include "sound.hpp"
extern game_sound sound;

//IMPORTANT:::
//remember to modify AresSetShininess if you create a new weapon
const short PUNCH_GUN=1;
const short SHOT_GUN =2;
const short MACHINE_GUN=3;
const short RIFLE_GUN=4;
//IMPORTANT:::
//remember to modify AresSetShininess if you create a new weapon

const short max_weapon_type_value=4;

//altrimenti fà conflitto con weapon di evar
//base class for all weapons
class weapon_class  {
public:
	//the weapon load itself
	//virtual is not necessary because the objects of the sub-class of this class 
	//are not upcasting
	void Load();
	
	//raf::Newt::SceneNode* p_node;

	short type;
	raf::OGGETTOANIMATO ogg;
	int ammunation;
	int damage;
	bool machine_gun_style;
	bool infinite_munition;
	std::string texture_file;
	SingleSound* sound_shoot;

	weapon_class():infinite_munition(false) {}
};

#endif