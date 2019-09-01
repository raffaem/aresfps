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
#ifndef VAR_HPP_RAFFAELE_MANCUSO_2135786432168
#define VAR_HPP_RAFFAELE_MANCUSO_2135786432168

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <wchar.h>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <irrlicht.h>
#include "..\\ares_runtime\\raf.hpp"
#include "func.hpp"
#include "classi.hpp"
#include "irrlicht class.hpp"
#include "script.hpp"
#include <winuser.h>
using namespace irr;
using namespace std;
#include "level model.hpp"
#include "add.hpp"

//sound
#include "sound.hpp"
game_sound sound;
bool play_back_mus;
float weapon_speed_for_millisecond=0.5;
float back_mus_volume;
bool back_mus_play_cas;
bool use_speculars=true;

//VARIABILI GLOBALI
scene::IMetaTriangleSelector* world_selector;

const float distance_between_enemy_weapon_to_active=1200.0;
const float distance_between_enemy_weapon_to_move=350.0;
const float enemy_BOT_moving_end_if_weapon_pos_change=800;

float move_speed;
bool immortal=false;
float shl_dimension_weapon=8.0f;
video::SColor shl_color_weapon=video::SColor(255,255,255,255);
float shl_dimension_enemy=20.0f;
video::SColor shl_color_enemy=video::SColor(255,255,255,255);

//to jump
const float start_speed_jump=5.75f;
const float loop_decrement_jump=0.15f;
bool now_jumping=false;
core::vector3df last_pos_for_jump;
float value_to_jump=start_speed_jump;
//end of jump

std::vector<obj_to_collide> collides_obj;
wchar_t* message_w;
std::string message_for_objs;
raf::VxHealthSceneNode* life_progress_bar;
raf::VxHealthSceneNode* armour_progress_bar;
int weapon_armour=0;
raf::VxHealthSceneNode* loading_bar;
core::vector3df life_progress_bar_pos;

bool now_restarting=false;
float this_file_ver=ares_version;
shot_guns_anim_callback_class shot_guns_anim_callback;
bool can_shoot=true;
bool tracks_list_empty=true;
int sound_tracks_index=-1;
std::string prog_path;
core::vector3df armour_progress_bar_pos;
core::vector3df armour_text_pos;
scene::ITextSceneNode* armour_text=NULL;
scene::ITextSceneNode* ammunation_text=NULL;
bool lose=false;
u32 text_time;
bool event_receiver_jump=false;
scene::ISceneNodeAnimator* anim_testo;
int anim_weapon=0;
scene::ISceneCollisionManager* collision_smgr;
scene::ISceneManager* loading_smgr;
raf::CAMERA loading_camera;
int anim=0;
core::vector3df rotaz;
core::vector3df coord;
int vita_weapon=100;
gui::IGUIFont* font;
gui::IGUIFont* font_to_show_objs_value;
//per i livelli
std::string script_file;
//fine per i livelli
bool prima_volta=true;
long int centro_x,centro_y;
video::ITexture* mirino;//il cursore che rappresenta il mirino
video::ITexture* proiettile_texture;//il proiettile_texture
video::ITexture* life_icon;
video::ITexture* armour_icon;
IrrlichtDevice *device=0;//per caricare l'engine e il device
io::IFileSystem* file_system;
scene::ISceneManager* smgr;//per gestire la scena
video::IVideoDriver* driver;//per gestire il video
raf::CAMERA camera=0;//la camera
arma* weapon;
HINSTANCE hInstance;

//classi del gioco
std::vector<nemici> nem;
std::vector<armour_class> armours;
std::vector<enemies_shoot_class> enemies_shoot;

gui::ICursorControl* cursor_control; 
core::position2d<s32> centro_mirino;
video::SColor colore_rettangolo(255,0,0,0);
core::vector3df posizione_testo_vita;
core::vector3df pos_text_fin;
core::vector3df pos_text_ini;
core::position2d<s32> life_icon_position;
core::position2d<s32> armour_icon_position;
core::position2d<s32> ammunation_icon_position;
core::vector3df ammunation_text_pos;
video::ITexture* ammunation_icon;

//core::rect<s32> pos_rett(centro_x-300,300,centro_x-300,600);
//per gestire gli eventi
MyEventReceiver eventi;
scene::ISceneNodeAnimatorCollisionResponse* gravityanim=NULL;
float yradius=50.0f;
float ares_version;
f32 return_yradius;
bool dl;
bool mirino_bool=true;
bool puo_saltare=false;
int temp;
//static blood
scene::IMesh* static_blood_file_mesh;
video::ITexture* static_blood_texture;

//dynamic blood
video::ITexture* dynamic_blood_texture;
video::ITexture* falgat_bullet;
video::ITexture* rhino_bullet;
video::ITexture* smoke_texture;
YouLoseEventReceiver you_lose_event_receiver;

//text variables
//the milliseconds after trascareed it the text is removed
u32 time_text_remove=0;
u32 last_time;
//te time in milliseconds that the text is created
u32 time_text_creation=1;
std::vector<SingleSound> tracks_list; 
std::vector<text_class> textes;

//Phisic
//raf::Newt::World* p_world;
std::vector<LevelModel> world_nodes;

//event receiver
bool cammina_avanti=false,cammina_indietro=false,cammina_sinistra=false,cammina_destra=false,chinato=false,spara_bool=false;

scene::ITextSceneNode * testo = 0;
scene::ITextSceneNode * testo_vita = 0;
core::stringw	vita_da_visualizzare;
core::vector3df pos_temp;
irr::scene::IParticleSystemSceneNode* smoke_campFire;
#endif
