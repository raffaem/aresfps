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
#ifndef SOUND_HPP_RAFFAELE_MANCUSO_2384687632168
#define SOUND_HPP_RAFFAELE_MANCUSO_2384687632168

#include "fmod.hpp"
#include "fmod_errors.h"

#include "..\\ares_runtime\\raf.hpp"
#include <vector>
#include <string>
#include <stdio.h>//printf
#include <process.h>//exit

#pragma comment(lib,"fmodexp_vc.lib")

class SingleSound {
public:
	FMOD::Sound* sound;
	FMOD::Channel* channel;
	bool restart_if_not_finish;
	SingleSound():sound(NULL),channel(NULL),restart_if_not_finish(false){}
};

class game_sound{
public:
	FMOD::System* device;

    //the sounds
	SingleSound	sparo_di_mitragliatrice;
	SingleSound	impactSound;
	SingleSound	passi;
	SingleSound	enemies_shoot;
	SingleSound	noammo;
	SingleSound	me_jump;
	SingleSound	me_death;
	SingleSound	armor;
	SingleSound	rifle;
	SingleSound	weapon_pain;
	SingleSound	shotgun;
	SingleSound	ammunation;
	SingleSound	medikit;
	SingleSound	punch;

	game_sound(){}
	~game_sound();
	void Initialize();
	inline void Play(SingleSound& s);
	inline void Stop(SingleSound& s);
	inline void Update();
};

inline void game_sound::Update() {
	this->device->update();
}
inline void game_sound::Play(SingleSound& s) {
	/*
	s.channel.insert(0,NULL);
	//int pos=s.channel.size()-1;
	int pos=0;
	*/
	if(s.restart_if_not_finish==true)
		s.channel->stop();

	bool isPlaying;
	s.channel->isPlaying(&isPlaying);

	if(isPlaying==false) {

	FMOD_RESULT result=this->device->playSound(FMOD_CHANNEL_FREE,s.sound,false,&s.channel);
	if(result!=FMOD_OK) {
		std::string s="Cannot play FMOD sound. FMOD description of the error: ";
		s+=FMOD_ErrorString(result);
		raf::FatalError(s);
	}

	}//if(s.play==false) {
}
inline void game_sound::Stop(SingleSound& s) {
	s.channel->stop();
}

#endif