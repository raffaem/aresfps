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
#ifndef MANCUSO_RAFFAELE_LEVEL_EDITOR_FOR_ARES_5843514200743587041570670
#define MANCUSO_RAFFAELE_LEVEL_EDITOR_FOR_ARES_5843514200743587041570670

#include "evar.hpp"

void AddFalgat(core::vector3df posizione,core::vector3df rotazione);
void AddRhino(core::vector3df posizione,core::vector3df rotazione);
int AddLight(core::vector3df position,float raggio=100.0f);
void AddMedikit(core::vector3df posizione,core::vector3df rotazione,int life);
void AddLevelModel(std::string& modello,std::string& texture,core::vector3df posizione,core::vector3df rotazione,core::vector3df scale);
void AddDefaultSkyBox();
void AddTerrain(std::string heightmap,
				std::string texture="",
				std::string detail_texture="",
				core::vector3df position=core::vector3df(0,0,0),
				core::vector3df rotation=core::vector3df(0,0,0),
				core::vector3df scale=core::vector3df(1,1,1),
				float scale1=1,
				float scale2=0);
void AddAmmunationShotgun(core::vector3df posizione,core::vector3df rotazione,int num_of_bullets=15);
void AddAmmunationMachinegun(core::vector3df posizione,core::vector3df rotazione,int num_of_bullets=15);
void AddAmmunationRiflegun(core::vector3df posizione,core::vector3df rotazione,int num_of_bullets=15);
void AddArmour(core::vector3df posizione,core::vector3df rotazione,int armour);
void AddZombie(irr::core::vector3df posizione,irr::core::vector3df rotazione);
#endif