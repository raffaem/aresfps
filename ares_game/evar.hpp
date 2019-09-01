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
#ifndef MANCUSO_RAFFAELE_ARES_EVAR_HPP_571698756423425845213584036846984021
#define MANCUSO_RAFFAELE_ARES_EVAR_HPP_571698756423425845213584036846984021

#include <string>
#include <vector>
#include <fstream>
#include <cmath>

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>

#include <irrlicht.h>
#include "..\\ares_runtime\\raf.hpp"
#include "classi.hpp"
#include "irrlicht class.hpp"
#include "script.hpp"
#include "level model.hpp"
#include "add.hpp"

using namespace irr;
using namespace std;
#pragma warning (disable:4786)

//for the sound
#include "sound.hpp"
extern game_sound sound;
extern float weapon_speed_for_millisecond;
extern bool play_back_mus;
extern float back_mus_volume;

//VARIABILI GLOBALI
extern scene::IMetaTriangleSelector* world_selector;

extern const float distance_between_enemy_weapon_to_active;
extern const float distance_between_enemy_weapon_to_move;
extern const float enemy_BOT_moving_end_if_weapon_pos_change;

extern float move_speed;
extern bool immortal;
extern float shl_dimension_weapon;
extern bool use_speculars;
extern video::SColor shl_color_weapon;
extern float shl_dimension_enemy;
extern video::SColor shl_color_enemy;

extern const float start_speed_jump;
extern const float loop_decrement_jump;
extern bool now_jumping;
extern core::vector3df last_pos_for_jump;
extern float value_to_jump;

extern std::vector<obj_to_collide> collides_obj;
extern bool now_restarting; 
extern scene::ITextSceneNode* testo;
extern raf::VxHealthSceneNode* armour_progress_bar;
extern core::position2d<s32> ammunation_icon_position;
extern core::vector3df ammunation_text_pos;
extern scene::ITextSceneNode* testo_vita;
extern core::stringw vita_da_visualizzare;
extern core::vector3df pos_temp;
extern core::vector3df armour_progress_bar_pos;
extern irr::scene::IParticleSystemSceneNode* smoke_campFire;
extern video::ITexture* smoke_texture;
extern u32 last_time;

extern raf::VxHealthSceneNode* life_progress_bar;
extern raf::VxHealthSceneNode* loading_bar;
extern core::vector3df life_progress_bar_pos;
extern video::ITexture* armour_icon;
extern core::position2d<s32> armour_icon_position;
extern scene::ISceneManager* loading_smgr;
extern raf::CAMERA loading_camera;
extern int weapon_armour;
extern core::vector3df ammunation_text_pos;

extern float this_file_ver;
extern float ares_version;
extern bool back_mus_play_cas;
extern int sound_tracks_index;
extern std::string prog_path;
extern bool lose;
extern u32 text_time;
extern scene::ISceneNodeAnimator* anim_testo;
extern int anim_weapon;
extern scene::ISceneCollisionManager* collision_smgr;
extern int anim;
extern core::vector3df rotaz;
extern core::vector3df coord;
extern int vita_weapon;
extern gui::IGUIFont* font;
extern core::vector3df armour_text_pos;
extern scene::ITextSceneNode* armour_text;
extern scene::ITextSceneNode* ammunation_text;
extern video::ITexture* life_icon;
extern video::ITexture* ammunation_icon;
//per i livelli
extern std::string script_file;
//fine per i livelli
extern bool prima_volta;
extern long int centro_x,centro_y;
extern video::ITexture* mirino;//il cursore che rappresenta il mirino
extern video::ITexture* proiettile_texture;//il proiettile_texture
extern IrrlichtDevice *device;//per caricare l'engine e il device
extern io::IFileSystem* file_system;
extern scene::ISceneManager* smgr;//per gestire la scena
extern video::IVideoDriver* driver;//per gestire il video
extern raf::CAMERA camera;//la camera
extern arma* weapon;
extern HINSTANCE hInstance;
//classi del gioco
extern std::vector<nemici> nem;
extern core::position2d<s32> life_icon_position;
extern video::ITexture* falgat_bullet;
extern video::ITexture* rhino_bullet;

extern gui::ICursorControl* cursor_control; 
extern core::position2d<s32> centro_mirino;
extern core::rect<s32> dimensione_mirino;
extern video::SColor colore_mirino;
extern video::SColor colore_rettangolo;
extern core::vector3df posizione_testo_vita;
extern core::vector3df pos_text_ini;
extern core::vector3df pos_text_fin;
extern core::rect<s32> pos_rett;
//per gestire gli eventi
extern MyEventReceiver eventi;
//extern MyEventReceiver_hai_vinto hai_vinto;
extern bool dl;
extern int temp;
extern wchar_t* message_w;
extern std::string message_for_objs;
extern gui::IGUIFont* font_to_show_objs_value;
extern bool event_receiver_jump;
extern scene::ISceneNodeAnimatorCollisionResponse* gravityanim;
extern float yradius;
extern bool mirino_bool;
extern bool puo_saltare;
extern f32 return_yradius;
extern scene::IMesh* static_blood_file_mesh;
extern video::ITexture* static_blood_texture;

extern std::vector<enemies_shoot_class> enemies_shoot;
extern YouLoseEventReceiver you_lose_event_receiver;
extern shot_guns_anim_callback_class shot_guns_anim_callback;

//the milliseconds after trascareed it the text is removed
extern u32 time_text_remove;
//te time in milliseconds that the text is created
extern u32 time_text_creation;
extern video::ITexture* dynamic_blood_texture;
extern std::vector<SingleSound> tracks_list; 
extern bool tracks_list_empty;
extern bool can_shoot;

//Phisic
//extern raf::Newt::World* p_world;


extern std::vector<LevelModel> world_nodes;
extern std::vector<text_class> textes;
//event receiver
extern bool cammina_avanti,cammina_indietro,cammina_sinistra,cammina_destra,chinato,spara_bool;
#endif



