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
#ifndef MANCUSO_RAFFAELE_TERRAIN_HPP_LEVEL_EDITOR_ARES_CODE_ahtroasuiglzsdfghsntrai3uqh48723hibd
#define MANCUSO_RAFFAELE_TERRAIN_HPP_LEVEL_EDITOR_ARES_CODE_ahtroasuiglzsdfghsntrai3uqh48723hibd
#include <irrlicht.h>
#include <string>
using namespace irr;

namespace level_editor {
	class Terrain {
	public:
		scene::ITerrainSceneNode* ogg;
		float scale1,scale2;
		std::string texture,detail_texture,heightmap;	
	};
}
#endif
