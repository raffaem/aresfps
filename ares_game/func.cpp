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
#ifndef MANCUSO_RAFFAELE_ARES_FPS_FUNC_CPP_CODE_1684684651231684984651348046516
#define MANCUSO_RAFFAELE_ARES_FPS_FUNC_CPP_CODE_1684684651231684984651348046516

/* INCLUDE */
#include "irrlicht class.hpp"
#include "script.hpp"
#include <sstream>
#include "func.hpp"
#include "lua.hpp"
#include "tolua_lua.h"
#include "classi.hpp"

//windows
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN /* Exclude rarely-used stuff from Windows headers */
#include <windows.h>
#endif//#ifdef WIN32

#include <string>
#include <vector>
#include <fstream>
#include <irrlicht.h>

using namespace raf;
using namespace std;

/* VARIABILI */
#include "evar.hpp"

bool isdir(string file) {
	//retrun false if the file does not exist or if it is a directory
	fstream in(file.c_str());
	return !in.is_open();
}

void LuaScript() {
	//scripting
	lua_State* LS=lua_open();

	//open needed libs
	luaopen_base(LS);
	luaopen_string(LS);
	luaopen_table(LS);
	luaopen_math(LS);
	luaopen_debug(LS);

	//luaopen_package();
	//luaopen_io();
	//end

	luaopen_AresLua(LS);

	//execute all scripts
	//STEP 1:insert all scripts into a vector
	string tracks_dir=prog_path+"\\scripts";
	raf::ChangeCurrentDirTo(tracks_dir);
	io::IFileList* scripts_list_irr=file_system->createFileList();
	raf::RestoreDir();
	vector<string> scripts_list=raf::conv::FilelistVector(scripts_list_irr);
	
	//STEP 2:erase unsupported file format and dirs
	for(int i=0;i<scripts_list.size();i++) {
		//erase all dir from the list
		if(isdir(scripts_list[i])) {
			scripts_list.erase(scripts_list.begin()+i);
			--i;
			continue;
		}

		//erase unsupported file format
		string extention=raf::String::GetExtention(scripts_list[i]);
		if(extention!="lua"&&
			extention!="out") { 
				//erase the file from the list
				scripts_list.erase(scripts_list.begin()+i);
				--i;
				continue;
		}
	}

	//STEP 3:execute all scripts
	for(i=0;i<scripts_list.size();i++) {
		/*
		luaL_loadfile(LS,scripts_list[i].c_str());
		lua_pcall(LS, 0, 0, 0);
		*/
		luaL_dofile(LS,scripts_list[i].c_str());
	}//for

	lua_close(LS);
	//end of scripting
}

// these macros will return the scaled value 
// based on current screen size 
// (i assume 800x600 is the normal res) 
#define SX(val) ( (float)(device->getVideoDriver()->getScreenSize().Width*(float)(val)/800.0f) ) 
#define SY(val) ( (float)(device->getVideoDriver()->getScreenSize().Height*(float)(val)/600.0f) ) 

double SXf(double val) {
	double rapport=(double)device->getVideoDriver()->getScreenSize().Width*(double)val;
	return (double)(rapport/(double)800.0); 
}
double SYf(double val) {
	double rapport=(double)device->getVideoDriver()->getScreenSize().Height*(double)val;
	return (double)(rapport/(double)600.0); 
}

void IniResFile(std::string file,std::string resolution,core::vector3df& vector3d_to_init) {
	raf::INIFile inires;
	raf::INISection section;
	std::string x_s,y_s,z_s;

	file="config\\std\\"+file+".inires";

	if(!inires.Open(file))
		raf::FatalError("inires file not found. File:"+file);

	if(!inires.GetSection(resolution,section)) 
		raf::FatalError("inires file error. Section or variables not found. Maybe unsupported resolution or unknow file format or file damaged. File: "+file);

	if(!section.GetVarValue("x",x_s))
		raf::FatalError("inires file error. Section found but var x not found. File: "+file);

	if(!section.GetVarValue("y",y_s))
		raf::FatalError("inires file error. Section found but var y not found. File: "+file);

	if(!section.GetVarValue("z",z_s))
		raf::FatalError("inires file error. Section found but var z not found. File: "+file);


	/*
	for(int i=0;i<param.size();i++)
		std::string temp=param[i];
	*/
	vector3d_to_init.X=(float)atof(x_s.c_str());
	vector3d_to_init.Y=(float)atof(y_s.c_str());
	vector3d_to_init.Z=(float)atof(z_s.c_str());
}

void IniText() {
	core::position2d<s32> resolution(centro_x,centro_y);
	resolution.X*=2;
	resolution.Y*=2;
	std::string resolution_s=raf::conv::NumString(resolution.X)+"x"+raf::conv::NumString(resolution.Y);
	
	float res_molt=(float)resolution.X*(float)resolution.Y;
	float molt_800_600=((float)800*(float)600);
	
	//posizione del testo
	//position_on_800_600:(800x600)=position_on_other_resolution:(other_resx*other_resy)
	//position_on_other_resolution=(position_on_800_600*other_resx*other_resy)/(800*600)
	pos_text_ini.X=(800*res_molt)/molt_800_600;
	pos_text_ini.Y=pos_text_fin.Y=(-600*res_molt)/molt_800_600;
	pos_text_ini.Z=pos_text_fin.Z=(999*res_molt)/molt_800_600;

	pos_text_fin.X=((-2500*res_molt)/molt_800_600);

	float speed=(0.3f*res_molt)/molt_800_600;
	text_time=raf::itime(pos_text_ini,pos_text_fin,speed);

	//icon position
	life_icon_position.X=SX(11);
	life_icon_position.Y=SY(450);

	armour_icon_position.X=SX(11);
	armour_icon_position.Y=SY(480);

	ammunation_icon_position.X=SX(11);
	ammunation_icon_position.Y=SY(510);
	//end of icon position

	//progress bars
	//x:800=Xrisultato:RESX
	//Xrisultato=(x*RESX)/800
	//y:600=Yrisultato:RESY
	//Yrisultato=(y*RESY)/600

	IniResFile("life_bar",resolution_s,life_progress_bar_pos);
	IniResFile("armour_bar",resolution_s,armour_progress_bar_pos);
	
	/*
	life_progress_bar_pos.X=(float)((float)-3.85f*(float)resolution.X)/(float)800.0f;
	life_progress_bar_pos.Y=(float)((float)-1.745f*(float)resolution.Y)/(float)600.0f;
	life_progress_bar_pos.Z=0;
	
	life_progress_bar_pos.X=(float)((float)-3.85f*(float)resolution.X)/(float)800.0f;
	life_progress_bar_pos.Y=(float)((float)-1.745f*(float)resolution.Y)/(float)600.0f;
	life_progress_bar_pos.Z=0;

	armour_progress_bar_pos.X=SX(-3.8);
	armour_progress_bar_pos.Y=SY(-2.1);
	armour_progress_bar_pos.Z=0;
	*/

	//posizione testo_vita
	/*
	posizione_testo_vita.X=(50*res_molt)/molt_800_600;
	posizione_testo_vita.Y=(-550*res_molt)/molt_800_600;
	posizione_testo_vita.Z=(999*res_molt)/molt_800_600;
	*/

	
	posizione_testo_vita.X=(-780.0f*res_molt)/molt_800_600;
	posizione_testo_vita.Y=(-365.0f*res_molt)/molt_800_600;
	posizione_testo_vita.Z=(999*res_molt)/molt_800_600;

	armour_text_pos.X=(-780.0f*res_molt)/molt_800_600;
	armour_text_pos.Y=(-437.0f*res_molt)/molt_800_600;
	armour_text_pos.Z=(999*res_molt)/molt_800_600;

	ammunation_text_pos.X=(-785.0f*res_molt)/molt_800_600;
	ammunation_text_pos.Y=(-500.0f*res_molt)/molt_800_600;
	ammunation_text_pos.Z=(999*res_molt)/molt_800_600;
}

/*
void IniText() {
	core::position2d<s32> resolution(centro_x,centro_y);
	resolution.X*=2;
	resolution.Y*=2;

	float res_molt=(float)resolution.X*(float)resolution.Y;
	float molt_800_600=((float)800*(float)600);

//usage 
rect = rect<irr::s32> buttonpos(SX(10),SY(200),SX(140),SY(240)); 

	//posizione del testo
	//position_on_800_600:(800x600)=position_on_other_resolution:(other_resx*other_resy)
	//position_on_other_resolution=(position_on_800_600*other_resx*other_resy)/(800*600)
	pos_text_ini.X=(800*res_molt)/molt_800_600;
	pos_text_ini.Y=pos_text_fin.Y=(-600*res_molt)/molt_800_600;
	pos_text_ini.Z=pos_text_fin.Z=(999*res_molt)/molt_800_600;

	pos_text_fin.X=((-2500*res_molt)/molt_800_600);

	float speed=(0.3f*res_molt)/molt_800_600;
	text_time=raf::itime(pos_text_ini,pos_text_fin,speed);

	//icon position
	life_icon_position.X=(float)(11*res_molt)/molt_800_600;
	life_icon_position.Y=(float)(450*res_molt)/molt_800_600;

	armour_icon_position.X=(11*res_molt)/molt_800_600;
	armour_icon_position.Y=(480*res_molt)/molt_800_600;

	ammunation_icon_position.X=(11*res_molt)/molt_800_600;
	ammunation_icon_position.Y=(510*res_molt)/molt_800_600;
	//end of icon position

	//progress bars
	life_progress_bar_pos.X=(-3.85*res_molt)/molt_800_600;
	life_progress_bar_pos.Y=(-1.745*res_molt)/molt_800_600;
	life_progress_bar_pos.Z=0;

	armour_progress_bar_pos.X=(-3.8*res_molt)/molt_800_600;
	armour_progress_bar_pos.Y=(-2.1*res_molt)/molt_800_600;
	armour_progress_bar_pos.Z=0;

	//posizione testo_vita
	posizione_testo_vita.X=(50*res_molt)/molt_800_600;
	posizione_testo_vita.Y=(-550*res_molt)/molt_800_600;
	posizione_testo_vita.Z=(999*res_molt)/molt_800_600;

	posizione_testo_vita=life_progress_bar_pos;
	posizione_testo_vita.Y-=(0.07*res_molt)/molt_800_600;

	armour_text_pos=posizione_testo_vita;
	armour_text_pos.Y-=(0.355*res_molt)/molt_800_600;

	ammunation_text_pos=armour_text_pos;
	ammunation_text_pos.Y-=(0.32*res_molt)/molt_800_600;
}
*/

void Initialize(){
	camera=(raf::CAMERA)smgr->addCameraSceneNode();
	weapon=new arma();
	weapon->LoadWeapons();

	IniText();
	CreateProgressBars();
}

void esci(bool valore)
{
	if(device!=NULL) {
		device->closeDevice();
		//device->drop();
		device=NULL;
	}
	if(weapon!=NULL){
		delete weapon;
		weapon=NULL;
	}

}
void CorrectExit() {esci(true);}

void EnemiesAnimation(int num, int n)
{
	if(nem[num].last_animation!=n) {
		nem[num].last_animation=n;
	if(nem[num].type==ET_FALGAT) {
		/* Fermo or attack*/
		if(n == 0||n==3)
		{
			nem[num].ogg->AnimaMs3d(0, 32, 94);
			nem[num].ogg->setAnimationSpeed(1000);
		}
		/* Cammina */
		else if(n == 1)
		{
			nem[num].ogg->AnimaMs3d(34, 55, 94);
			nem[num].ogg->setAnimationSpeed(1000);
		}
		/* Muore */
		else if(n == 2)
		{	
			nem[num].ogg->AnimaMs3d(56, 94, 94);
			nem[num].ogg->setAnimationSpeed(1000);
		}//muore
	}//if(nem[num].type==ET_FALGAT) {

	else if(nem[num].type==ET_RHINO) {
		/* Fermo */
		if(n == 0)
		{
			nem[num].ogg->setMD2Animation("stand");
		}
		/* Cammina */
		else if(n == 1)
		{
			nem[num].ogg->setMD2Animation("run");
			nem[num].ogg->setAnimationSpeed(100);
		}
		/* Muore */
		else if(n == 2)
		{	
			nem[num].ogg->setMD2Animation("death");
		}//muore

		//SPECIAL:
		//Attack
		else if(n == 3)
		{	
			nem[num].ogg->setMD2Animation("attack");
		}
	}//if(nem[num].type==ET_RHINO) {

	//zombie
	else if(nem[num].type==ET_ZOMBIE) {
		// Fermo 
		if(n == 0)
		{
			nem[num].ogg->setFrameLoop(114,127);
			nem[num].ogg->setAnimationSpeed(1000);
		}
		// Cammina 
		else if(n == 1)
		{
			nem[num].ogg->setMD2Animation("run");
			nem[num].ogg->setAnimationSpeed(800);
		}
		// Muore 
		else if(n == 2)
		{	
			nem[num].ogg->setMD2Animation("die");
			nem[num].ogg->setAnimationSpeed(160);
			nem[num].ogg->setLoopMode(false);
		}//muore
		//SPECIAL:
		//Attack
		else if(n == 3)
		{	
			nem[num].ogg->setMD2Animation("attack");
			nem[num].ogg->setAnimationSpeed(140);
		}
	}//if(nem[num].type==ET_ZOMBIE) {

	}//if(nem[num].last_animation!=n) {
}//function

void leggi_impostazioni_utente()
{
	/* LETTURA DELLE IMPOSTAZIONI */
	string temp,device_sett;
	u32 ris1,ris2,color;
	bool fullscreen,stencylbuffer,vsync,antialias,hightprecisionfpu;
	/*~~~~~~~~~~~~~~~~~~~~~~*/
	string setting_file=prog_path+"\\config\\config.ini";
	raf::file setting(setting_file.c_str());

	vector<string> v(setting.GetVector());
	setting.Close();
	
	device_sett = v[0];
	ris1 = (u32) atoi(v[1].c_str());
	ris2 = (u32) atoi(v[2].c_str());
	centro_x = (long) ris1 / 2;
	centro_y = (long) ris2 / 2;
	color = (u32) atoi(v[3].c_str());
	fullscreen = raf::conv::StringBool(v[4]);
	stencylbuffer =raf::conv::StringBool(v[5]);	
	vsync =raf::conv::StringBool(v[6]);	
	antialias = raf::conv::StringBool(v[8]);
	play_back_mus= raf::conv::StringBool(v[9]);/*play background music?*/

	back_mus_volume=atof(v[10].c_str());
	if(v[11]=="cas")
		back_mus_play_cas=true;
	else
		back_mus_play_cas=false;

	//speculars
	if(v[15]=="yes") use_speculars=true;
	else use_speculars=false;

	//hight precision fpu
	if(v[16]=="yes") hightprecisionfpu=true;
	else hightprecisionfpu=false;
	
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/* crea la struct */
	SIrrlichtCreationParameters device_parametres;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	device_parametres.Bits = color;
	device_parametres.Fullscreen = fullscreen;
	device_parametres.Stencilbuffer = stencylbuffer;
	device_parametres.Vsync = vsync;
	device_parametres.WindowSize = core::dimension2d<s32> (ris1, ris2);
	device_parametres.AntiAlias = antialias;
	device_parametres.HighPrecisionFPU=hightprecisionfpu;

	//setta il render
	if(device_sett == "dx9")
	{
		device_parametres.DriverType = video::EDT_DIRECT3D9;
	}
	else if(device_sett == "dx8")
	{
		device_parametres.DriverType = video::EDT_DIRECT3D8;
	}
	else if(device_sett == "ogl")
	{
		device_parametres.DriverType = video::EDT_OPENGL;
	}
	else if(device_sett == "soft")
	{
		device_parametres.DriverType = video::EDT_SOFTWARE;
	}
	else if(device_sett == "soft2")
	{
		device_parametres.DriverType = video::EDT_SOFTWARE2;
	}
	else
	{
		raf::errore("Si è verificato un errore nel file config.ini (riga:1) del gioco.\nIl device non è stato riconosciuto\nquesto programma sarà terminato\nPremere ok per continuare...");
		exit(false);
	}
	
	if(v[12]=="yes")
		script_file = "levels\\" + v[13];
	else
		script_file = v[13];

	//queste righe servono per evitare un fastidioso problema 
	//che si verifica con le directx  se lo stencylbuffer 
	//è attivo e l'illuminazione diffusa pure.
	//in sostanza si vede tutto nero,
	//per cui se l'illuminazione diffusa è attiva, disattiva lo stecylbuffer.
	//in ogni caso questo problema non si verfica con le OGL
	
	if(device_parametres.DriverType==video::EDT_DIRECT3D9||
		device_parametres.DriverType==video::EDT_DIRECT3D8) {

	raf::file script;

	if(!script.Open(script_file))
		raf::FatalError("error in init_user_options(). script file "+script_file+" not found");

	string command,all_record;
	int command_space;
	vector<string> sub;

	// FOR BACKWARD COMPATIBILITY
	if(script.GetVector()[0]=="yes"||
		script.GetVector()[0]=="no") {
		sub=script.GetVector();
		if(sub[0]=="yes")
			device_parametres.Stencilbuffer = false;
	}
	//end for backward compatibility

	else{
	for(int i=0;i<script.GetFileSize();i++) {
		script.SetRecordNumber(i);

		//comment
		if(script.GetRecord()[0]=='/'&&
			script.GetRecord()[1]=='/')
			continue;

		script.Information(command,command_space,all_record);
		sub.clear();
		script.FindInRecord(" ",sub);

		if(command=="diffuselight"&&sub[1]=="yes") {
			device_parametres.Stencilbuffer = false;
			break;
		}
	}

	}//else{
	}//if(device_parametres.DriverType==video::EDT_DIRECT3D9||

	//crea il device
	device = createDeviceEx(device_parametres);	

	//texture quality
	device->getVideoDriver()->setTextureCreationFlag(video::ETCF_OPTIMIZED_FOR_QUALITY,false);
	device->getVideoDriver()->setTextureCreationFlag(video::ETCF_OPTIMIZED_FOR_SPEED,false);
	device->getVideoDriver()->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT,false);
	device->getVideoDriver()->setTextureCreationFlag(video::ETCF_ALWAYS_16_BIT,false);

	if(v[14]=="ofq") //optimize for quality
		device->getVideoDriver()->setTextureCreationFlag(video::ETCF_OPTIMIZED_FOR_QUALITY,true);
	else if(v[14]=="ofs") //optimize for speed
		device->getVideoDriver()->setTextureCreationFlag(video::ETCF_OPTIMIZED_FOR_SPEED,true);
	else if(v[14]=="32") //32bit
		device->getVideoDriver()->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT,true);
	else if(v[14]=="16") //16bit
		device->getVideoDriver()->setTextureCreationFlag(video::ETCF_ALWAYS_16_BIT,true);

}	
void CaptureTheCurrentScreen()
{
    // save the bitmap in a file
	string name_of_file = "screenshots\\screenshot";
	int number = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(;; number++)
	{
		string file = name_of_file + raf::conv::NumString(number) + ".bmp";

		if(device->getFileSystem()->existFile(file.c_str()) == false)
		{
			// se il file non esiste lo salva 
			video::IImage* screen_shot=driver->createScreenShot();
			if(screen_shot) {
				driver->writeImageToFile(screen_shot,file.c_str());
				gestione_messaggi(L"SCREEN SAVED",true,true,false);
				screen_shot->drop();
				return;
			}
		}
	}
}

void AddFalgat(core::vector3df posizione, core::vector3df rotazione)
{
	const float yradius=35.0f;

	raf::ChangeCurrentDirTo(prog_path);

	raf::OGGETTOANIMATO	temp;

	//decidiamo la posizione
	/*
	core::vector3df correct_pos=raf::Land(posizione,world_selector);
	if(correct_pos!=posizione)
		correct_pos.Y+=yradius;
		*/
	core::vector3df correct_pos=posizione;

	
	scene::IAnimatedMesh * falgatfile = smgr->getMesh("media\\models\\rigell.ms3d");
	temp = static_cast<raf::OGGETTOANIMATO>(smgr->addAnimatedMeshSceneNode(
		falgatfile,
		0,//parent
		-1,//id
		correct_pos,
		rotazione
		));

	//temp->time_shoot=0;

	temp->addShadowVolumeSceneNode();
	temp->setMaterialTexture(0, driver->getTexture("media\\texture\\rigell.bmp"));
	temp->AnimaMs3d(0, 32, 94);
	temp->setAnimationSpeed(1000);
	raf::DiffuseLight(temp,dl);

	scene::ITriangleSelector * triangle_selector = smgr->createTriangleSelector(falgatfile->getMesh(1500), temp);
	temp->setTriangleSelector(triangle_selector);
	triangle_selector->drop();

	//prende la mano destra
	scene::ISceneNode* right_hand=temp->getMS3DJointNode("Bip01 R Hand");
	if(right_hand==0||right_hand==NULL) {
		raf::errore("error joint","error");
		exit(0);
	}

	//carica l'arma da attaccare alla mano destra
	scene::ISceneNode* falgat_weapon=smgr->addMeshSceneNode(
		smgr->getMesh("media\\models\\spacegun.ms3d")->getMesh(1));
	falgat_weapon->setMaterialTexture(0,driver->getTexture("media\\texture\\spacegun.bmp"));
	raf::DiffuseLight(falgat_weapon,dl);
	
	//attacca l'arma
	right_hand->addChild(falgat_weapon);

	//illuminazione diffusa all'arma
	raf::DiffuseLight(falgat_weapon, dl);

	//sistema la posizione dell'arma
	//prende posizione e rotazione
	core::vector3df rot=falgat_weapon->getRotation();
	core::vector3df scale=falgat_weapon->getScale();

	//la ruota per metterla diritta
	rot.X+=90.0f;
	rot.Z+=90.0f;

	//ne riduce le dimensioni perchè è troppo grande
	float scale_factor=-0.4f;
	scale.X+=scale_factor;
	scale.Y+=scale_factor;
	scale.Z+=scale_factor;

	//applica le modifiche
	//setta la nuova rotazione e la nuova scala
	falgat_weapon->setRotation(rot);
	falgat_weapon->setScale(scale);
		 
	/* lo metto nel vettore */
	nemici this_enemie;
	this_enemie.ogg=temp;
	this_enemie.blood=false;
	this_enemie.vita=30;
	this_enemie.time_between_two_shots=150;
	this_enemie.damage=2;
	this_enemie.type=ET_FALGAT;
	this_enemie.attached_weapon=(raf::SCENENODE)falgat_weapon;
	this_enemie.bullet=&falgat_bullet;
	this_enemie.yradius=yradius;
	this_enemie.speed=0.5;
	this_enemie.mesh=falgatfile->getMesh(1500);
	nem.push_back(this_enemie);

	raf::RestoreDir();
}

void AddZombie(irr::core::vector3df posizione,irr::core::vector3df rotazione) {
	raf::ChangeCurrentDirTo(prog_path);

	float yradius=44.0f;

	raf::OGGETTOANIMATO	temp;

	//decidiamo la posizione
	/*
	core::vector3df correct_pos=raf::Land(posizione,world_selector);
	if(correct_pos!=posizione)
		correct_pos.Y+=yradius;
		*/
	core::vector3df correct_pos=posizione;

	
	scene::IAnimatedMesh * zombiefile = smgr->getMesh("media\\models\\zombie.md2");
	temp = static_cast<raf::OGGETTOANIMATO>(smgr->addAnimatedMeshSceneNode(
		zombiefile,
		0,//parent
		-1,//id
		correct_pos,
		rotazione
		));
	temp->setScale(core::vector3df(3.9f,3.9f,3.9f));
	temp->setMaterialFlag(video::EMF_NORMALIZE_NORMALS,true); 

	temp->addShadowVolumeSceneNode();
	temp->setMaterialTexture(0, driver->getTexture("media\\texture\\zombie.jpg"));
	raf::DiffuseLight(temp,dl);
	scene::ITriangleSelector * triangle_selector = smgr->createTriangleSelector(zombiefile->getMesh(1), temp);
	temp->setTriangleSelector(triangle_selector);
	triangle_selector->drop();

	temp->setMD2Animation("stand");
		 
	/* lo metto nel vettore */
	nemici this_enemie;
	this_enemie.ogg=temp;
	this_enemie.blood=false;
	this_enemie.vita=40;
	this_enemie.type=ET_ZOMBIE;
	this_enemie.time_between_two_shots=180;
	this_enemie.damage=3;
	this_enemie.bullet=&rhino_bullet;
	this_enemie.yradius=yradius;
	this_enemie.speed=0.25;
	this_enemie.mesh=zombiefile->getMesh(1);
	nem.push_back(this_enemie);
}

void AddRhino(core::vector3df posizione, core::vector3df rotazione)
{
	const float yradius=30.0f;

	raf::ChangeCurrentDirTo(prog_path);

	raf::OGGETTOANIMATO	temp;

	//decidiamo la posizione
	/*
	core::vector3df correct_pos=raf::Land(posizione,world_selector);
	if(correct_pos!=posizione)
		correct_pos.Y+=24;
		*/
	core::vector3df correct_pos=posizione;
	
	scene::IAnimatedMesh * rhinofile = smgr->getMesh("media\\models\\rhino.md2");
	temp = static_cast<raf::OGGETTOANIMATO>(smgr->addAnimatedMeshSceneNode(
		rhinofile,
		0,//parent
		-1,//id
		correct_pos,
		rotazione
		));

	//temp->time_shoot=0;

	temp->addShadowVolumeSceneNode();
	temp->setMaterialTexture(0, driver->getTexture("media\\texture\\rhino.jpg"));
	//temp->AnimaMs3d(0, 32, 94);
	//temp->setAnimationSpeed(1000);
	raf::DiffuseLight(temp,dl);

	scene::ITriangleSelector * triangle_selector = smgr->createTriangleSelector(rhinofile->getMesh(1500), temp);
	temp->setTriangleSelector(triangle_selector);
	triangle_selector->drop();

	temp->setMD2Animation("stand");
		 
	/* lo metto nel vettore */
	nemici this_enemie;
	this_enemie.ogg=temp;
	this_enemie.blood=false;
	this_enemie.vita=35;
	this_enemie.type=ET_RHINO;
	this_enemie.time_between_two_shots=130;
	this_enemie.damage=3;
	this_enemie.bullet=&rhino_bullet;
	this_enemie.yradius=yradius;
	this_enemie.speed=0.25;
	this_enemie.mesh=rhinofile->getMesh(15);
	nem.push_back(this_enemie);
}

void ChangeWeaponCollision(bool diminuisci,bool no_gravity) {

	if(gravityanim!=NULL) {
		weapon->actual_weapon->ogg->removeAnimator(gravityanim);
		gravityanim->drop();
	}

	f32 yr;

	if(diminuisci) {
		yr=yradius/2;
	}
	else{
		yr=yradius;
	}

	//gravity on y
	float gravity_on_y=-0.5f;
	if(no_gravity) {
		gravity_on_y=0.0f;
	}

	//TO ACTIVE?
	gravityanim=weapon->actual_weapon->ogg->Collisione(return_yradius,world_selector,15.0,yr,0.0f,0,gravity_on_y,0);

	/*
	core::vector3df box_size=weapon->actual_weapon->p_node->GetBoxSize();
	box_size.Y+=5.0f;
	weapon->actual_weapon->p_node->SetBoxSize(box_size);
	*/	
}
void CreateDynamicBlood(core::vector3df position,core::vector3df rotation){
	//create a particle system
	scene::IParticleSystemSceneNode* dynamic_blood = smgr->addParticleSystemSceneNode(
		false//default emitter false
		);
	
	//dynamic_blood->setScale(core::vector3df(0.001f,0.001f,0.001f));

	dynamic_blood->setPosition(position);
	dynamic_blood->setRotation(rotation);

	dynamic_blood->setParticleSize(core::dimension2d<f32>(1.8f,1.8f));
	//dynamic_blood->setParticleSize(core::dimension2d<f32>(5.4f,5.4f));

	dynamic_blood->setMaterialFlag(video::EMF_LIGHTING, false);
	dynamic_blood->setMaterialTexture(0,dynamic_blood_texture);
	dynamic_blood->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);

	scene::IParticleAffector* paf = dynamic_blood->createFadeOutParticleAffector();
	dynamic_blood->addAffector(paf);
	paf->drop();

	const float speed=0.04f;
	//create emititer
	scene::IParticleEmitter* em = dynamic_blood->createBoxEmitter(
		core::aabbox3d<f32>(-7,0,-7,7,1,7), //box
		//core::aabbox3d<f32>(-90,-90,-90,-100,-100,-100), //box
		core::vector3df(speed,speed,speed),//direction
		170,//min particle per second
		250,//max particle per second
		video::SColor(0,255,255,255),//min start color
		video::SColor(0,255,255,255),//max start color 
		600,//min life time
		800,//max life time
		360//max angle degrees
		);
	dynamic_blood->setEmitter(em);
	em->drop();

	scene::ISceneNodeAnimator* delete_s=smgr->createDeleteAnimator(850);
	dynamic_blood->addAnimator(delete_s);
	delete_s->drop();

	//dynamic_blood->set_DEBUGDataVisible(true);
}

//CODECS
string all_codecs[22]={
	"aiff",
	"asf",
	"asx",
	"cdda",
	"dls",
	"flac",
	"fsb",
	"it",
	"m3u",
	"mid",
	"midi",
	"mod",
	"mp2",
	"mp3",
	"ogg",
	"pls",
	"raw",
	"s3m",
	"wav",
	"wax",
	"wma",
	"xm"
};
static const int most_codecs_size=9;
string most_codecs[most_codecs_size]={
	"cdda",
	"flac",
	"mod",
	"ogg",
	"wav"
};

static const int rarely_codecs_size=14;
string rarely_codecs[rarely_codecs_size]={
	"aiff",
	"asf",
	"asx",
	"dls",
	"fsb",
	"it",
	"m3u",
	"mod",
	"pls",
	"raw",
	"s3m",
	"wax",
	"xm"
};
bool IsSupportedMost(string extention) {
	for(int i=0;i<most_codecs_size;i++) {
		if(most_codecs[i]==extention) return true;		
	}
	return false;
}
bool IsSupportedRarely(string extention) {
	for(int i=0;i<rarely_codecs_size;i++) {
		if(rarely_codecs[i]==extention) return true;		
	}
	return false;
}
//END OF CODECS

void LoadTracks() {
	//first of all, ceck if you have the codec installed
	bool most_codecs_inst=raf::CeckPackage(prog_path,"Stdpkg FMOD Most Codecs");
	bool rar_codecs_inst=raf::CeckPackage(prog_path,"Stdpkg FMOD Rarely Codecs");

	//change to tracks dir
	string tracks_dir=prog_path+"\\tracks";
	raf::ChangeCurrentDirTo(tracks_dir);

	//get all file in the dir
	io::IFileList* tracks=file_system->createFileList();
	vector<string> tracks_list_v=raf::conv::FilelistVector(tracks);
	
	//erase unsupported file format and dir
	for(int i=0;i<tracks_list_v.size();i++) {
		//erase all dir from the list
		if(isdir(tracks_list_v[i])) {
			tracks_list_v.erase(tracks_list_v.begin()+i);
			--i;
			continue;
		}

		//erase unsupported file format
		string extention=raf::String::GetExtention(tracks_list_v[i]);
		if(extention!="ogg"&&
			extention!="mp3"&&
			extention!="midi"&&
			extention!="mid"&&
			extention!="mp2") { 

			//is not supported if a codec is not present 
			//STEP 1:Ceck if it is supported by most codecs pack
			bool is_supported_most=IsSupportedMost(extention);
			if(is_supported_most&&!most_codecs_inst) {
				//it is supported but codec is not installed
				raf::errore(
					"Error during load user tracks. Cannot load the file \""
					+tracks_list_v[i]+"\" because to load an audio file "
					"format is necessary a codec wich support it."
					" Ares can load just .ogg (by Vorbis) file format."
					"If you want to load an audio file in a different "
					"format you need a codec wich support it."
					" The codec for the requested format is available in the pack "
					"\"Ares most used codecs pack\" and you haven't it. "
					"To download it please visit http://aresfps.sf.net/tools.htm "
					"Press ok to ignore this file");
			
				//erase the file from the list
				tracks_list_v.erase(tracks_list_v.begin()+i);
				--i;
				continue;
			}
			else if(is_supported_most&&most_codecs_inst) continue;

			//STEP 2:not supported by most. ceck if supported by rarely
			bool is_supported_rar=IsSupportedRarely(extention);
			if(is_supported_rar&&!rar_codecs_inst) {
				//it is supported but codec is not installed
				raf::errore(
					"Error during load user tracks. Cannot load the file \""
					+tracks_list_v[i]+"\" because to load an audio file "
					"format is necessary a codec wich support it."
					" Ares can load just .ogg (by Vorbis) file format."
					"If you want to load an audio file in a different "
					"format you need a codec wich support it."
					" The codec for the requested format is available in the pack "
					"\"Ares rarely used codecs pack\" and you haven't it. "
					"To download it please visit http://aresfps.sf.net/tools.htm "
					"Press ok to ignore this file");
			
				//erase the file from the list
				tracks_list_v.erase(tracks_list_v.begin()+i);
				--i;
				continue;
			}
			else if(is_supported_rar&&rar_codecs_inst) continue;

			//STEP 3:completely not supported 
			//erase the file from the list
			raf::errore(
				"Error during load user tracks. Cannot load the file \""
				+tracks_list_v[i]+"\" because Ares can't load this file format. Please save the file in a most famous file format (like mp3,wav,wma,ogg,exc..)");

			tracks_list_v.erase(tracks_list_v.begin()+i);
			--i;
		}//if(extention!="ogg") { 

	}//for(int i=0;i<tracks_list_v.size();i++) {
	//erase file list
	tracks->drop();

	//load all file
	for(i=0;i<tracks_list_v.size();i++) {
		FMOD_RESULT result;
		FMOD::Sound* fmod_this_sound;
		
		//create the sound
		result=sound.device->createStream(tracks_list_v[i].c_str(),FMOD_DEFAULT,0,&fmod_this_sound);
		if(result!=FMOD_OK) {
			raf::errore("Cannot create FMOD stream. File "+tracks_list_v[i]);
			continue;
		}

		//insert this sound into a vector
		SingleSound this_sound;
		this_sound.sound=fmod_this_sound;
		tracks_list.push_back(this_sound);
	}

	tracks_list_empty=tracks_list.empty();

	if(play_back_mus==false) tracks_list_empty=true;

	//mix tracks!
	if(back_mus_play_cas)
		raf::MixRandomVector(tracks_list);

	//restore original dir
	raf::RestoreDir();
}
//----------------------------------------------------
void ClearLevel() {
	delete weapon;
	life_progress_bar->remove();
	armour_progress_bar->remove();
	smgr->clear();
	collides_obj.clear();
	nem.clear();
	enemies_shoot.clear();
	testo_vita=NULL;
}
//------------------------------------------------
void Restart() {
	now_restarting=true;

	//reset variables
	mirino_bool=true;
	lose=false;
	testo=NULL;
	can_shoot=true;
	vita_weapon=100;
	mirino_bool=true;
	puo_saltare=false;
	time_text_remove=0;
	time_text_creation=1;
	yradius=45.0f;
	gravityanim=NULL;
	anim=0;
	anim_weapon=0;
	cammina_avanti=false;
	cammina_indietro=false;
	cammina_sinistra=false;
	cammina_destra=false;
	event_receiver_jump=false;
	chinato=false;
	spara_bool=false;
	weapon_armour=0;
	ammunation_text=NULL;
	armour_text=NULL;
	//end of reset all variables
	
	ClearLevel();
	Initialize();
	carica_mappa();
	ChangeWeaponCollision();
	UpdateLife();
	UpdateAmmunation();
	UpdateArmour();
	weapon->ChangeWeapon(SHOT_GUN);

	LuaScript();

	SpecularHightLights();

	//execute these instructions to update the positionof all objs to not have probs with ai and weapon movement
	driver->beginScene(true,true, video::SColor(0,90,90,156));
	smgr->drawAll();
	driver->endScene();
	//end

	device->setEventReceiver(&eventi);
	now_restarting=false;
}
void IniNowLoadingWindow() {
	loading_smgr=smgr->createNewSceneManager();
	loading_camera=(raf::CAMERA)loading_smgr->addCameraSceneNode();
	loading_bar=new raf::VxHealthSceneNode(
		loading_camera,//parent
		loading_smgr,//smgr
		-1,//id
		loading_smgr->getSceneCollisionManager(),//collision manager
		100,//width
		10,//height
		core::vector3df(0,0,0),//position
		irr::video::SColor(145,255,0,0), //BarColor
		irr::video::SColor(145,255,255,255), //BkgColor
		irr::video::SColor(145,220,220,220)//BoarderColor 
	);
}
void ShowNowLoading(int progress) {
	loading_bar->setProgress(progress);
	driver->beginScene(true,true, video::SColor(255,255,255,255));
	loading_smgr->drawAll();
	driver->endScene();
}

void SpecularHightLights() {
	if(use_speculars) {

	weapon->shot_gun.ogg->getMaterial(0).Shininess=shl_dimension_weapon; 
	weapon->shot_gun.ogg->getMaterial(0).SpecularColor=shl_color_weapon;
	weapon->machine_gun.ogg->getMaterial(0).Shininess=shl_dimension_weapon; 
	weapon->machine_gun.ogg->getMaterial(0).SpecularColor=shl_color_weapon;
	weapon->rifle_gun.ogg->getMaterial(0).Shininess=shl_dimension_weapon; 
	weapon->rifle_gun.ogg->getMaterial(0).SpecularColor=shl_color_weapon;
	weapon->punch_gun.ogg->getMaterial(0).Shininess=shl_dimension_weapon; 
	weapon->punch_gun.ogg->getMaterial(0).SpecularColor=shl_color_weapon;

	for(int i=0;i<nem.size();i++) {
		nem[i].ogg->getMaterial(0).Shininess=shl_dimension_enemy;
		nem[i].ogg->getMaterial(0).SpecularColor=shl_color_enemy;
	}

	/*
	for(i=0;i<world_nodes.size();i++) {
		world_nodes[i].node->getMaterial(0).Shininess=value;
		world_nodes[i].node->getMaterial(0).SpecularColor=specular_color;
	}
	*/

	/*
	for(i=0;i<collides_obj.size();i++) {
		collides_obj[i].ogg->getMaterial(0).Shininess=value;
		collides_obj[i].ogg->getMaterial(0).SpecularColor=specular_color;
	}
	*/

	}//if(use_speculars) {
}//function

#endif
