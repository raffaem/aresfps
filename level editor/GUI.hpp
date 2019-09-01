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
#ifndef MANCUSO_RAFFAELE_ARES_LEVEL_EDITOR_589746210684062167012610
#define MANCUSO_RAFFAELE_ARES_LEVEL_EDITOR_589746210684062167012610

#include <irrlicht.h>
void CreateGUI(irr::gui::IGUIEnvironment*& mygui);
void GUIManager(irr::SEvent& irrevent,irr::gui::IGUIEnvironment* mygui);

namespace menu{
	enum MENU_CODE{
		FILE_NEW=0,
		FILE_OPEN,
		FILE_SAVE,
		FILE_VIEW,
		FILE_RELOAD,
		FILE_EXIT,
		HELP_HELP=0,
		WORLD_ADD_DEFAULT_SKY_BOX=0,
		WORLD_USER_SKY_BOX,
		WORLD_REMOVE_SKY_BOX,
		WORLD_ACTIVE_DEACTIVE_DIFFUSE_LIGHT,
		INSERT_MODEL=1,
		INSERT_MEDIKIT,
		INSERT_AMMUNATION,
		INSERT_LIGHT,
		INSERT_TERRAIN,
		INSERT_MONSTER_FALGAT=0,
		INSERT_MONSTER_RHINO,
		CAMERA_UP=0,
		CAMERA_POS_AS_WEAPON,
		OBJECT_SELECT=0,
		OBJECT_UNSELECT,
		OBJECT_MOVE,
		OBJECT_ERASE,
		OBJECT_PROPIETARIES
	};
}//namespace menu

namespace element {
		enum EDIT_BOX_CODE {
			POS_X=0,
			POS_Y,
			POS_Z,
			ROT_X,
			ROT_Y,
			ROT_Z,
			SCALE_X,
			SCALE_Y,
			SCALE_Z
		};
}//namespace element
#endif