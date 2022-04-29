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
#ifndef MANCUO_RAFFAELE_LIBRERIA_OGGETTO_ANIMATO_54068468472877
#define MANCUO_RAFFAELE_LIBRERIA_OGGETTO_ANIMATO_54068468472877

#include "dll_exports.hpp"
#include <irrlicht.h>
#include <string>
using namespace irr;

namespace raf{
class ARES_API OggettoAnimato:public irr::scene::IAnimatedMeshSceneNode {
	public:
		//class scenenode
		//inline functions
		inline void Cammina(float speed, char direzione);
		inline void MuoviAvanti(float speed);
		inline void MuoviX(float speed);
		inline void MuoviY(float speed);
		inline void MuoviZ(float speed);
		inline void RuotaY(float speed);
		inline void RuotaX(float speed);
		inline void RuotaZ(float speed);
		inline void NewPosX(float new_pos);
		inline void NewPosY(float new_pos);
		inline void NewPosZ(float new_pos);
		//end of inline functions

		void NewRotationX(float speed);
		void NewRotationY(float speed);
		void NewRotationZ(float speed);		
		//fine
		void LevaTrasparente(std::string percorso_texture);
		scene::ISceneNodeAnimatorCollisionResponse* Collisione(f32& yradius_return,scene::ITriangleSelector* world_selector=NULL,float radiusx=0,float radiusy=0,float radiusz=0,float gravityx=0,float gravityy=-100.0f,float gravityz=0);
		scene::ISceneNodeAnimatorCollisionResponse* Collisione2(f32& yradius_return,scene::ITriangleSelector* world_selector=NULL,float radiusx=0,float radiusy=0,float radiusz=0,float gravityx=0,float gravityy=-100.0f,float gravityz=0);
		void Trasparente(std::string percorso_texture="nero.jpg");
		void AnimaMs3d(int inizio, int fine,int totale);
	};//della classe OggettoAnimato
}

//-----------------INLINE FUNCTION--------------------------
inline void raf::OggettoAnimato::MuoviX(float speed) {
	core::vector3df pos=this->getPosition();
	pos.X+=speed;
	this->setPosition(pos);
}
//-----------------------------------------------------
inline void raf::OggettoAnimato::MuoviAvanti(float speed){
	core::vector3df coord=this->getPosition();
	float yrotation=this->getRotation().Y;

	/*
	if(raf::sign(rotaz.Y)=='-') {
		rotaz.Y=-rotaz.Y;
	}
	*/

	//converting y rotation into radiant
	float rad=yrotation*irr::core::GRAD_PI2;
	coord.X+=cosf(rad)*speed;
	coord.Z-=sinf(rad)*speed;
	this->setPosition(coord);
}
//-------------------------------------------------------------------
inline void raf::OggettoAnimato::MuoviY(float speed) {
	core::vector3df pos=this->getPosition();
	pos.Y+=speed;
	this->setPosition(pos);
}
//----------------------------------------------------
inline void raf::OggettoAnimato::MuoviZ(float speed) {
	core::vector3df pos=this->getPosition();
	pos.Z+=speed;
	this->setPosition(pos);
}
//-------------------------------------------------------------------
inline void raf::OggettoAnimato::Cammina(float speed,char direzione) {
	switch(direzione) {

	case 'u': 
		this->RuotaY(-90); 
		this->MuoviAvanti(speed); 
		this->RuotaY(90); 
		break;

	case 'd':

		this->RuotaY(90); 
		this->MuoviAvanti(speed); 
		this->RuotaY(-90); 
		break;

	case 'l':
		this->MuoviAvanti(-speed);
		break;

	case 'r':
		this->MuoviAvanti(speed);
	}//switch
}//function
//------------------------------------------------------------------
inline void raf::OggettoAnimato::RuotaX(float speed){
	core::vector3df rotaz=this->getRotation();
	rotaz.X+=speed;
	if (rotaz.X>360)rotaz.X=rotaz.X-360;
	if (rotaz.X<0)rotaz.X=rotaz.X+360;
	this->setRotation(rotaz);
}
//--------------------------------------------------------
inline void raf::OggettoAnimato::RuotaY(float speed){
	core::vector3df rotaz=this->getRotation();
	rotaz.Y+=speed;
	this->setRotation(rotaz);
}
//------------------------------------------------------------------
inline void raf::OggettoAnimato::RuotaZ(float speed){
	core::vector3df rotaz=this->getRotation();
	rotaz.Z+=speed;
	//if (rotaz.X>360)rotaz.X=rotaz.X-360;
	//if (rotaz.X<0)rotaz.X=rotaz.X+360;
	this->setRotation(rotaz);
}
//-----------------------------------------------------------------
inline void raf::OggettoAnimato::NewPosX(float new_pos) {
	core::vector3df pos=this->getPosition();
	pos.X=new_pos;
	this->setPosition(pos);
} 
inline void raf::OggettoAnimato::NewPosY(float new_pos) {
	core::vector3df pos=this->getPosition();
	pos.Y=new_pos;
	this->setPosition(pos);
}
inline void raf::OggettoAnimato::NewPosZ(float new_pos) {
	core::vector3df pos=this->getPosition();
	pos.Z=new_pos;
	this->setPosition(pos);
}
#endif