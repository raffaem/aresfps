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
#include "sound.hpp"
#include <iostream>
#include "evar.hpp"

void game_sound::Initialize() {
	raf::ChangeCurrentDirTo(prog_path);
	FMOD_RESULT result;

	//inizialize the system
	result=FMOD::System_Create(&this->device);
	if(result!=FMOD_OK) 
		raf::FatalError("Cannot create FMOD system");

	result=this->device->init(50,FMOD_INIT_NORMAL,0);
	if(result!=FMOD_OK) {
		string s="Cannot initialize FMOD system. FMOD error description: ";
		s+=FMOD_ErrorString(result);
		raf::FatalError(s);
	}

   	//load the sounds
    result = this->device->createSound("media\\sound\\passi.ogg",FMOD_DEFAULT,0,&this->passi.sound);
	if(result!=FMOD_OK) {
		string s="Cannot create FMOD sound. FMOD error description: ";
		s+=FMOD_ErrorString(result);
		raf::FatalError(s);
	}

	result = this->device->createSound("media\\sound\\mitragliatore.ogg",FMOD_DEFAULT,0,&this->sparo_di_mitragliatrice.sound);
	if(result!=FMOD_OK) {
		string s="Cannot create FMOD sound. FMOD error description: ";
		s+=FMOD_ErrorString(result);
		raf::FatalError(s);
	}

	result = this->device->createSound("media\\sound\\shotgun.ogg",FMOD_DEFAULT,0,&this->shotgun.sound);
	if(result!=FMOD_OK) {
		string s="Cannot create FMOD sound. FMOD error description: ";
		s+=FMOD_ErrorString(result);
		raf::FatalError(s);
	}

	result = this->device->createSound("media\\sound\\ammunation.ogg",FMOD_DEFAULT,0,&this->ammunation.sound);
	if(result!=FMOD_OK) {
		string s="Cannot create FMOD sound. FMOD error description: ";
		s+=FMOD_ErrorString(result);
		raf::FatalError(s);
	}

	result = this->device->createSound("media\\sound\\medikit.ogg",FMOD_DEFAULT,0,&this->medikit.sound);
	if(result!=FMOD_OK) {
		string s="Cannot create FMOD sound. FMOD error description: ";
		s+=FMOD_ErrorString(result);
		raf::FatalError(s);
	}

	result = this->device->createSound("media\\sound\\punch.ogg",FMOD_DEFAULT,0,&this->punch.sound);
	if(result!=FMOD_OK) {
		string s="Cannot create FMOD sound. FMOD error description: ";
		s+=FMOD_ErrorString(result);
		raf::FatalError(s);
	}

	result = this->device->createSound("media\\sound\\impact.ogg",FMOD_DEFAULT,0,&this->impactSound.sound);
	if(result!=FMOD_OK) {
		string s="Cannot create FMOD sound. FMOD error description: ";
		s+=FMOD_ErrorString(result);
		raf::FatalError(s);
	}

	result = this->device->createSound("media\\sound\\shoot.ogg",FMOD_DEFAULT,0,&this->enemies_shoot.sound);
	if(result!=FMOD_OK) {
		string s="Cannot create FMOD sound. FMOD error description: ";
		s+=FMOD_ErrorString(result);
		raf::FatalError(s);
	}

	result = this->device->createSound("media\\sound\\noammo.ogg",FMOD_DEFAULT,0,&this->noammo.sound);
	if(result!=FMOD_OK) {
		string s="Cannot create FMOD sound. FMOD error description: ";
		s+=FMOD_ErrorString(result);
		raf::FatalError(s);
	}

	result = this->device->createSound("media\\sound\\me_death.ogg",FMOD_DEFAULT,0,&this->me_death.sound);
	if(result!=FMOD_OK) {
		string s="Cannot create FMOD sound. FMOD error description: ";
		s+=FMOD_ErrorString(result);
		raf::FatalError(s);
	}

	result = this->device->createSound("media\\sound\\me_jump.ogg",FMOD_DEFAULT,0,&this->me_jump.sound);
	if(result!=FMOD_OK) {
		string s="Cannot create FMOD sound. FMOD error description: ";
		s+=FMOD_ErrorString(result);
		raf::FatalError(s);
	}

	result = this->device->createSound("media\\sound\\rifle.ogg",FMOD_DEFAULT,0,&this->rifle.sound);
	if(result!=FMOD_OK) {
		string s="Cannot create FMOD sound. FMOD error description: ";
		s+=FMOD_ErrorString(result);
		raf::FatalError(s);
	}

	result = this->device->createSound("media\\sound\\armor.ogg",FMOD_DEFAULT,0,&this->armor.sound);
	if(result!=FMOD_OK) {
		string s="Cannot create FMOD sound. FMOD error description: ";
		s+=FMOD_ErrorString(result);
		raf::FatalError(s);
	}

	result = this->device->createSound("media\\sound\\weapon_pain.ogg",FMOD_DEFAULT,0,&this->weapon_pain.sound);
	if(result!=FMOD_OK) {
		string s="Cannot create FMOD sound. FMOD error description: ";
		s+=FMOD_ErrorString(result);
		raf::FatalError(s);
	}

	//special ini
	this->rifle.restart_if_not_finish=true;
}
//destructor
game_sound::~game_sound() {
	this->device->release();
}