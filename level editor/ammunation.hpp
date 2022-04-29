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
#ifndef MANCUSO_RAFFAELE_ARES_AMMUNATION_HPP_5416498462168798046504984709650145489
#define MANCUSO_RAFFAELE_ARES_AMMUNATION_HPP_5416498462168798046504984709650145489

#include <irrlicht.h>

enum AMMUNATION_TYPE{
	EAT_SHOTGUN,
	EAT_MACHINEGUN,
	EAT_RIFLEGUN
};

class Ammunation{
public:
	scene::ISceneNode* ogg;
	AMMUNATION_TYPE type;
	int num_of_bullets;
};

#endif
