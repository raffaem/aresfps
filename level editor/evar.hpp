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
#ifndef MANCSUO_RAFFAELE_ARES_LEVEL_EDITOR_EVAR_6849510210654968046210680462
#define MANCSUO_RAFFAELE_ARES_LEVEL_EDITOR_EVAR_6849510210654968046210680462

#include <windows.h>
#include "..\\ares_runtime\\raf.hpp"
#include "save.hpp"
#include "light.hpp"
#include "enemies.hpp"
#include "event.hpp"
#include <irrlicht.h>
#include "level_model.hpp"
#include "medikit_class.hpp"

//#include "user_sky_box.hpp"
//#include "obj_prop.hpp"

#include "sky_box.hpp"
#include <vector>
using namespace irr;
#include <string>
#include "object_type.hpp"
#include "func.hpp"
#include "loader.hpp"
#include "save.hpp"
#include "add.hpp"
#include "terrain.hpp"
#include <afxwin.h>
#include "ammunation.hpp"

using namespace std;
using namespace raf::conv;

#include "level editor.h"

#ifdef _DEBUG
extern scene::ITextSceneNode* mouse_pos_text;
#endif 

extern std::vector<scene::ILightSceneNode*> directional_lights;
extern float ares_version;
extern float this_file_ver;
extern bool loader_execute;
extern vector<string> zip_files;
extern string actual_file;
extern char obj_type;
extern video::ITexture* bill_texture;
extern bool dl;//diffuse light
extern scene::ISceneNode* weapon;
extern vector<level_editor::Enemies*> enemies;
extern vector<medikit_class> medikits;
extern vector<armour_class> armours;
extern vector<level_editor::Light*> lights;
extern vector<level_editor::LevelModel*> level_models;
extern vector<Ammunation*> ammunation;
extern vector<int> enemies_free;
extern vector<int> medikits_free;
extern vector<int> lights_free;
extern vector<int> level_models_free;
extern vector<int> ammunation_free;
extern vector<int> armours_free;
extern string prog_dir;
extern IrrlichtDevice* device;
extern video::IVideoDriver* driver;
extern scene::ISceneManager* smgr;
extern raf::CAMERA camera;
extern scene::ISceneNode* selectnode;
extern bool FPS_camera;
extern scene::ISceneNode* skyboxNode;
extern SkyBox sky_box;
extern actual_sky_box_type;

extern vector<int> terrain_free;
extern vector<level_editor::Terrain*> terrain_nodes;

extern scene::IMetaTriangleSelector* world_selector;
extern string last_saved_file;

extern CLeveleditorApp theApp;
extern MyEventReceiver env_rec;
extern bool costructor_execute;
extern CCommandLineInfo cmd_to_execute;

#endif