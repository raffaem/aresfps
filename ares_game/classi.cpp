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
#include "classi.hpp"
#include <irrlicht.h>
#include "func.hpp"
using namespace irr;
#include "evar.hpp"
#pragma auto_inline(on)
extern bool dl;

void arma::LoadWeapons(){
	//load the weapons
	this->shot_gun.Load();

	//MACHINE_GUN
	this->machine_gun.Load();
	this->rifle_gun.Load();
	this->punch_gun.Load();
	
	//set the actual weapon
	this->actual_weapon=&this->shot_gun;

	//rende tutte le altere armi trasparenti
	this->machine_gun.ogg->Trasparente("media\\texture\\nero.jpg");
	this->rifle_gun.ogg->Trasparente("media\\texture\\nero.jpg");
	this->punch_gun.ogg->Trasparente("media\\texture\\nero.jpg");
}

void arma::SetLastWeaponPosUnlikeWeaponPos() {
	this->last_weapon_pos=core::vector3df(0,0,0);
	if(this->actual_weapon->ogg->getPosition()==core::vector3df(0,0,0)){
		this->last_weapon_pos=core::vector3df(1,0,0);
	}
}

void arma::ChangeWeapon(short new_weapon) {
	//clear variables
	ammunation_text=NULL;
	testo_vita=NULL;
	armour_text=NULL;
	testo=NULL;

	event_receiver_jump=false;

	core::vector3df pos=this->actual_weapon->ogg->getPosition();
	core::vector3df rot=this->actual_weapon->ogg->getRotation();

	this->actual_weapon->ogg->Trasparente("media\\texture\\nero.jpg");
	this->actual_weapon->ogg->removeAll();
	this->actual_weapon->ogg->removeAnimators();

	camera->setPosition(core::vector3df(0,0,-5));

	if(new_weapon==SHOT_GUN) {
		this->actual_weapon=&this->shot_gun;
		//gestione_messaggi(L"YOU HAVE THE SHOT GUN",false);
	}

	else if(new_weapon==MACHINE_GUN) {
		this->actual_weapon=&this->machine_gun;
		//gestione_messaggi(L"YOU HAVE THE MACHINE GUN",false);		
	}

	else if(new_weapon==RIFLE_GUN) {
		this->actual_weapon=&this->rifle_gun;
		//gestione_messaggi(L"YOU HAVE THE RIFLE",false);
	}

	else if(new_weapon==PUNCH_GUN) {
		this->actual_weapon=&this->punch_gun;
		//gestione_messaggi(L"YOU HAVE THE PUNCH",false);
	}


	this->actual_weapon->ogg->LevaTrasparente(weapon->actual_weapon->texture_file);
	this->actual_weapon->ogg->setPosition(pos);
	this->actual_weapon->ogg->setRotation(rot);
	this->actual_weapon->ogg->updateAbsolutePosition();
	this->SetLastWeaponPosUnlikeWeaponPos();
	can_shoot=true;
	this->actual_weapon->ogg->addChild(camera);
	raf::DiffuseLight(this->actual_weapon->ogg,dl);

	if(!now_jumping)
		ChangeWeaponCollision();
	else
		ChangeWeaponCollision(false,true);
	
	//recreate progress bar
	CreateProgressBars();
	UpdateAmmunation();
	UpdateLife();
	UpdateArmour();
}

void arma::ToogleTrasparency() {
	if(this->actual_weapon->type==SHOT_GUN) {
		this->actual_weapon->ogg->LevaTrasparente("media\\texture\\shot_gun.jpg");
	}
	else if(this->actual_weapon->type==MACHINE_GUN) {
		this->actual_weapon->ogg->LevaTrasparente("media\\texture\\machine_gun.jpg");
	}
}
//fine arma
//shot guns anim call back
void shot_guns_anim_callback_class::OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode *node) {
	can_shoot=true;
}



