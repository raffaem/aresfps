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
#ifndef MANCUSO_RAFFAELE_ARES_LEVEL_EDITOR_VAR_HPP_5418748974162198406218970
#define MANCUSO_RAFFAELE_ARES_LEVEL_EDITOR_VAR_HPP_5418748974162198406218970

#include <windows.h>
#include "..\\ares_runtime\\raf.hpp"
#include "save.hpp"
#include "light.hpp"
#include "event.hpp"
#include "GUI.hpp"
#include <irrlicht.h>
#include "level_model.hpp"
#include "enemies.hpp"
#include <vector>
using namespace irr;
#include <string>
using namespace std;
using namespace raf::conv;
#include "user_sky_box.hpp"
#include "sky_box.hpp"
#include "object_type.hpp"
#include "obj_prop.hpp"
#include "func.hpp"
#include "loader.hpp"
#include "save.hpp"
#include "add.hpp"
#include "terrain.hpp"
#include "level editor.h" 
#include "ammunation.hpp"
#include <afxwin.h>

#ifdef _DEBUG
scene::ITextSceneNode* mouse_pos_text=NULL;
#endif

float ares_version;
float this_file_ver;
string actual_file;
bool loader_execute=false;
char obj_type;
scene::IMetaTriangleSelector* world_selector=NULL;
video::ITexture* bill_texture;
std::vector<scene::ILightSceneNode*> directional_lights;
vector<string> zip_files;
bool dl=true;//diffuse light
scene::ISceneNode* weapon;
vector<level_editor::Enemies*> enemies;
vector<medikit_class> medikits;
vector<level_editor::Light*> lights;
vector<armour_class> armours;
vector<level_editor::LevelModel*> level_models;
vector<level_editor::Terrain*> terrain_nodes;
vector<Ammunation*> ammunation;

vector<int> enemies_free;
vector<int> medikits_free;
vector<int> armours_free;
vector<int> lights_free;
vector<int> level_models_free;
vector<int> terrain_free;
vector<int> ammunation_free;

string prog_dir;
IrrlichtDevice* device;
video::IVideoDriver* driver;
scene::ISceneManager* smgr;
raf::CAMERA camera;
int actual_sky_box_type=0;
scene::ISceneNode* selectnode;
gui::IGUIEnvironment* GUI;
bool FPS_camera=false;
scene::ISceneNode* skyboxNode=NULL;
SkyBox sky_box;
MyEventReceiver env_rec;

string last_saved_file="";

//SPECIFIED TO DO NOT CRASH
bool costructor_execute=false;
CCommandLineInfo cmd_to_execute;

#endif
