//This file is a part of "BestSound", 3d cross-platform audio library
//Copyright (C) 2006 Mancuso Raffaele
//To view all terms and condition of use, see bestsound.hpp file in this directory

#include "audiolistener.hpp"

void BestSound::Listener::SetPosition(BestSound::Vector new_pos) {
	alListener3f(AL_POSITION,new_pos.x,new_pos.y,new_pos.z);
}
void BestSound::Listener::SetSpeed(BestSound::Vector speed) {
	alListener3f(AL_VELOCITY,speed.x,speed.y,speed.z);
}
