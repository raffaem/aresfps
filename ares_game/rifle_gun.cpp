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
#include "rifle_gun.hpp"
#include "evar.hpp"
void rifle_gun_class::Load() {
	//MACHINE GUN
	scene::IAnimatedMesh* machine_gun_file=smgr->getMesh("media\\models\\rifle_gun.md2");
	this->ogg=(raf::OGGETTOANIMATO)smgr->addAnimatedMeshSceneNode(machine_gun_file); 
	this->ogg->setMaterialTexture(0,driver->getTexture("media\\texture\\rifle_gun.jpg")); 
	//PER LE COLLISIONI
	this->ogg->addShadowVolumeSceneNode();
	scene::ITriangleSelector* tri=smgr->createTriangleSelector(machine_gun_file->getMesh(2),this->ogg);
	this->ogg->setTriangleSelector(tri);
	tri->drop();
	raf::DiffuseLight(this->ogg,dl);
	this->ogg->setMD2Animation("active");

	this->ammunation=0;
	this->damage=70;
	this->machine_gun_style=false;
	this->type=RIFLE_GUN;
	this->texture_file="media\\texture\\rifle_gun.jpg";
	this->sound_shoot=&sound.rifle;
	//TO ACTIVE
	//this->p_node=p_world->AddSceneNode(this->ogg,machine_gun_file->getMesh(1));
	return;
}