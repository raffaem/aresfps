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
#ifndef MANCUSO_RAFFAELE_ARES_ADD_HPP_CODE_AFSDFAS65168462168ASFAXCASDFD6516816984ASCFASFEFEFREAF
#define MANCUSO_RAFFAELE_ARES_ADD_HPP_CODE_AFSDFAS65168462168ASFAXCASDFD6516816984ASCFASFEFEFREAF
#include "evar.hpp"

//add functions
void AddMedikit(irr::core::vector3df posizione,irr::core::vector3df rotazione,int life);
void AddFalgat(irr::core::vector3df posizione,irr::core::vector3df rotazione);
void AddRhino(irr::core::vector3df posizione,irr::core::vector3df rotazione);
void AddZombie(irr::core::vector3df posizione,irr::core::vector3df rotazione);
void AddArmour(irr::core::vector3df posizione,irr::core::vector3df rotazione,int value);

void AddAmmunationShotGun(core::vector3df posizione,core::vector3df rotazione,int value);
void AddAmmunationMachineGun(core::vector3df posizione,core::vector3df rotazione,int value);
void AddAmmunationRifleGun(core::vector3df posizione,core::vector3df rotazione,int valuef);

#endif
