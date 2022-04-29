/*
PLEASE DON'T DELETE THIS NOTE IF YOU REDISTRIBUTE THIS PROGRAM

This file is a part of Ares, a first person shooter (
fps) game 
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
#ifndef RAFFAELE_MANCUSO_IRRLICHT_HELP_LIBRERY_VERSIONE_1_00_00_IRR_HELP_H_LIB_COD_135463843513843543843513431012
#define RAFFAELE_MANCUSO_IRRLICHT_HELP_LIBRERY_VERSIONE_1_00_00_IRR_HELP_H_LIB_COD_135463843513843543843513431012

#ifndef __cplusplus
#error E' richiesto un compilatore c++
#endif

#ifdef WIN32
#include <windows.h>
#endif

#include <string>
#include <cmath>
#include <iostream>
#include <irrlicht.h>
#include <fstream>
//using namespace std;
using namespace irr;
#include "raf.hpp"

#include <direct.h>
scene::ISceneManager* smgr_drag=NULL;
video::IVideoDriver* driver_drag=NULL;
IrrlichtDevice* device_drag=NULL;
scene::IMetaTriangleSelector* meta_selector=NULL;

std::string current_dir;

#pragma auto_inline(on)
#pragma warning (disable:4786)

#pragma comment(lib,"newton.lib")

void raf::conv::String3dVector(std::string vettore3d,char carattere_separatore,float& num1,float& num2,float& num3) {
	int virgola=0;//per sapere a che virgola siamo arrivati
	bool spazio=false;
	std::string temp;
	int stringa_size=vettore3d.size();
	int last_virgola;
	for(int i=0;i<=stringa_size;i++) {
		if((vettore3d[i]==carattere_separatore)&&(virgola==0)) {
			temp=raf::String::SubString(vettore3d,0,i-1);
			num1=atof(temp.c_str());
			virgola=1;
			last_virgola=i;
			i++;
		}
		if((vettore3d[i]==carattere_separatore)&&(virgola==1)) {
			temp=raf::String::SubString(vettore3d,last_virgola+1,i-1);
			num2=atof(temp.c_str());
			last_virgola=i;
			temp=raf::String::SubString(vettore3d,last_virgola+1,stringa_size-1);
			num3=atof(temp.c_str());
			break;
		}
	}//for
}

ARES_API float raf::conv::WChar_tFloat(wchar_t* s) {
	std::string num_s=raf::conv::WChar_tString(s);
	float num=atof(num_s.c_str());
	return num;
}

ARES_API core::vector3df raf::conv::String3dVector(std::string vettore3d,char carattere_separatore) {
	float x,y,z;
	raf::conv::String3dVector(vettore3d,carattere_separatore,x,y,z);
	return irr::core::vector3df(x,y,z);
}

ARES_API char* raf::conv::WChar_tChar(wchar_t* s,int max_char_size)	{
	char *ResultChar = new char[max_char_size]; 
	wcstombs(ResultChar,s,max_char_size);
	return ResultChar;
}
ARES_API std::string raf::conv::WChar_tString(wchar_t* s,int max_char_size) {
	char* s_char=raf::conv::WChar_tChar(s,max_char_size);
	std::string s_string(s_char);
	delete s_char;
	return s_string;
}
ARES_API wchar_t* raf::conv::CharWChar_T(char* s,int max_char_size) {
	wchar_t* w_string=new wchar_t[max_char_size];
	mbstowcs(w_string,s,max_char_size);
	return w_string;
}
std::vector<std::string> raf::conv::FilelistVector(io::IFileList* the_list) {
	std::vector<std::string> r;
	for(int i=0;i<the_list->getFileCount();i++) {
		r.push_back(the_list->getFullFileName(i));
	}
	return r;
}
ARES_API bool raf::conv::StringBool (std::string value) {
	if(value=="yes") return true;
	else if(value=="no") return false;
	else raf::FatalError("Error in function raf::conv::StringBool.\nPassed std::string is "+value+"\nThe std::string is not in the format yes\\no");
}
std::string raf::conv::UnixDirToWinDir(std::string unix_dir) {
	for(int i=0;i<unix_dir.size();i++) {
		if(unix_dir[i]=='/') 
			unix_dir[i]='\\';
	}//for(int i=0;i<unix_dir.size();i++) 
	return unix_dir;
}
//calsse sceneNode
void raf::SceneNode::MuoviAvanti(int speed){
	irr::core::vector3df coord=this->getPosition();
	irr::core::vector3df rotaz=this->getRotation();
	const double PG=3.14159265358979;
	double rad; 
	rad=(rotaz.Y*PG)/180;
	if (rotaz.Y>=0&&rotaz.Y<=180){
		coord.X+=cos(rad)*speed;coord.Z-=sin(rad)*speed;}
	if (rotaz.Y>180/*&&rotaz.Y<360*/){
		coord.X+=cos(rad)*speed;coord.Z-=sin(rad)*speed;}
	irr::core::vector3df old_coord=this->getPosition();
	irr::core::vector3df old_rotaz=this->getRotation();
	this->setPosition(coord);
	this->setRotation(rotaz);
}
//-------------------------------------------------------------------
void raf::SceneNode::MuoviX(int speed) {
	core::vector3df pos=this->getPosition();
	pos.X+=speed;
	this->setPosition(pos);
	
}
void raf::SceneNode::MuoviY(double speed) {
	core::vector3df pos=this->getPosition();
	pos.Y+=speed;
	this->setPosition(pos);
	
}
void raf::SceneNode::MuoviZ(int speed) {
	core::vector3df pos=this->getPosition();
	pos.Z+=speed;
	this->setPosition(pos);
}

//-------------------------------------------------------------------
void raf::SceneNode::Cammina(int speed,std::string direzione) {
	if(direzione=="up"){ 
		this->RuotaY(-90); 
		this->MuoviAvanti(speed); 
		this->RuotaY(90); 
	}
	if(direzione=="down"){ 
		this->RuotaY(90); 
		this->MuoviAvanti(speed); 
		this->RuotaY(-90); 
	}
	if(direzione=="left"){this->MuoviAvanti(-speed);}
	if(direzione=="right"){this->MuoviAvanti(speed);}
} 
//------------------------------------------------------------------
void raf::SceneNode::RuotaX(double speed){
	core::vector3df rotaz=this->getRotation();
	rotaz.X+=speed;
	if (rotaz.X>360)rotaz.X=rotaz.X-360;
	if (rotaz.X<0)rotaz.X=rotaz.X+360;
	this->setRotation(rotaz);
}
//--------------------------------------------------------
void raf::SceneNode::RuotaY(double speed){
	core::vector3df rotaz=this->getRotation();
	rotaz.Y+=speed;
	if (rotaz.Y>360)rotaz.Y=rotaz.Y-360;
	if (rotaz.Y<0)rotaz.Y=rotaz.Y+360;
	//if (rotaz.Y==360-speed)rotaz.Y=0;
	//if (rotaz.Y==-1-speed)rotaz.Y=360-speed;
	//if (rotaz.Y>360)rotaz.Y=0;
	//if (rotaz.Y<0)rotaz.Y=360-speed;
	this->setRotation(rotaz);
}
//------------------------------------------------------------------
void raf::SceneNode::RuotaZ(double speed){
	core::vector3df rotaz=this->getRotation();
	rotaz.Z+=speed;
	if (rotaz.X>360)rotaz.X=rotaz.X-360;
	if (rotaz.X<0)rotaz.X=rotaz.X+360;
	this->setRotation(rotaz);
}
void raf::SceneNode::NewRotationX(double speed) {
	core::vector3df rot=this->getRotation();
	rot.X=speed;
	this->setRotation(rot);

}
void raf::SceneNode::NewRotationY(double speed) {
	core::vector3df rot=this->getRotation();
	rot.Y=speed;
	this->setRotation(rot);

}
void raf::SceneNode::NewRotationZ(double speed) {
	core::vector3df rot=this->getRotation();
	rot.Z=speed;
	this->setRotation(rot);

}
//fine
//****************************************************************
//***********FUNZIONI PER LA CLASSE OggettoAnimato****************
//****************************************************************
//*********************************************************
//***************INIZIO FUNZIONI PER LA CLASSE CAMERA******
//*********************************************************
void raf::Camera::Muovi(int speed){
	core::vector3df coord=this->getPosition();
	core::vector3df rotaz=this->getRotation();
	const double PG=3.14159265358979;
	double rad; 
	rotaz.Y+=90;
	rad=(rotaz.Y*PG)/180;
	if (rotaz.Y>=0&&rotaz.Y<=180){
		coord.X+=cos(rad)*speed;coord.Z-=sin(rad)*speed;}
	if (rotaz.Y>180&&rotaz.Y<360){
		coord.X+=cos(rad)*speed;coord.Z-=sin(rad)*speed;}
	rotaz.Y-=90;
	this->setPosition(coord);
	this->setRotation(rotaz);
}
/////////////////////////////////////////////
void raf::Camera::MuoviY(int speed) {
	core::vector3df pos=this->getPosition();
	pos.Y+=speed;
	this->setPosition(pos);
}
////////////////////////////////////////////
void raf::Camera::RuotaY(int speed){
	core::vector3df rotaz=this->getRotation();
	rotaz.Y+=90;
	rotaz.Y+=speed;
	if (rotaz.Y==361)rotaz.Y=1;
	if (rotaz.Y==-1)rotaz.Y=359;
	rotaz.Y-=90;
	this->setRotation(rotaz);
}
////////////////////////////////////////////
void raf::Camera::RuotaX(int speed){
	core::vector3df rotaz=this->getRotation();
	rotaz.Y+=90;
	rotaz.X+=speed;
	if (rotaz.X==361)rotaz.X=1;
	if (rotaz.X==-1)rotaz.X=359;
	rotaz.Y-=90;
	this->setRotation(rotaz);
}
////////////////////////////////////////////
void raf::Camera::RuotaZ(int speed){
	core::vector3df rotaz=this->getRotation();
	rotaz.Y+=90;
	rotaz.Z+=speed;
	if (rotaz.Z==361)rotaz.Z=1;
	if (rotaz.Z==-1)rotaz.Z=359;
	rotaz.Y-=90;
	this->setRotation(rotaz);
}
////////////////////////////////////////////
void raf::Camera::LegaOggettoaCamera(raf::OggettoAnimato* ogg2, int distanza){
	core::vector3df coord1=this->getPosition();
	core::vector3df rotaz1=this->getRotation();
	ogg2->setPosition(coord1);
	ogg2->setRotation(rotaz1);
	ogg2->MuoviAvanti(distanza);
}
////////////////////////////////////////////
void raf::Camera::LegaCameraaOggetto(raf::OggettoAnimato* arma){
	this->setTarget(arma->getAbsolutePosition()); //la camera segue weapon
}
///////////////////////////////////////////////////////////////
void raf::Camera::Collisione(scene::ITriangleSelector* world_selector,float radiusx,float radiusy,float radiusz,float gravityx,float gravityy,float gravityz) {
	if(world_selector==NULL) {world_selector=raf::PrendiSelector();}
	core::aabbox3d<f32> box = this->getBoundingBox();
    core::vector3df radius = box.MaxEdge - box.getCenter();
	radius.X+=radiusx;
	radius.Y+=radiusy;
	radius.Z+=radiusz;
	core::vector3df gravity(gravityx,gravityy,gravityz);
	scene::ISceneNodeAnimatorCollisionResponse* anim=smgr_drag->createCollisionResponseAnimator(
			world_selector,this,radius,gravity);
	this->addAnimator(anim);
	anim->drop();
	return;
}
//**********************************************************
//*************FINE FUNZIONI PER LA CLASSE CAMERA***********
//**********************************************************

//**********************************************************
//*************INIZIO FUNZIONI PER LA CLASSE BILLBOARD***********
//**********************************************************
void raf::BillBoard::Collisione(scene::ITriangleSelector* world_selector,float radiusx,float radiusy,float radiusz,float gravityx,float gravityy,float gravityz){
	if(world_selector==NULL) {world_selector=raf::PrendiSelector();}
	core::aabbox3d<f32> box = this->getBoundingBox();
    core::vector3df radius = box.MaxEdge - box.getCenter();
	radius.X+=radiusx;
	radius.Y+=radiusy;
	radius.Z+=radiusz;
	core::vector3df gravity(gravityx,gravityy,gravityz);
	scene::ISceneNodeAnimatorCollisionResponse* anim=smgr_drag->createCollisionResponseAnimator(
			world_selector,this,radius,gravity);
	this->addAnimator(anim);
	anim->drop();
	

}
void raf::BillBoard::MuoviAvanti(int speed) {
	core::vector3df coord=this->getPosition();
	core::vector3df rotaz=this->getRotation();
	const double PG=3.14159265358979;
	double rad; 
	rad=(rotaz.Y*PG)/180;
	if (rotaz.Y>=0&&rotaz.Y<=180){
		coord.X+=cos(rad)*speed;coord.Z-=sin(rad)*speed;}
	if (rotaz.Y>180&&rotaz.Y<360){
		coord.X+=cos(rad)*speed;coord.Z-=sin(rad)*speed;}
	core::vector3df old_coord=this->getPosition();
	core::vector3df old_rotaz=this->getRotation();
	this->setPosition(coord);
	this->setRotation(rotaz);
}

void raf::BillBoard::MuoviX(int speed) {
	core::vector3df pos=this->getPosition();
	pos.X+=speed;
	this->setPosition(pos);
}
void raf::BillBoard::MuoviY(int speed) {
	core::vector3df pos=this->getPosition();
	pos.Y+=speed;
	this->setPosition(pos);	
}
void raf::BillBoard::MuoviZ(int speed) {
	core::vector3df pos=this->getPosition();
	pos.Z+=speed;
	this->setPosition(pos);
}
//-------------------------------------------------------
void raf::BillBoard::Cammina(int speed,std::string direzione) {
	if(direzione=="up"){ 
		this->RuotaY(-90); 
		this->MuoviAvanti(speed); 
		this->RuotaY(90); 
	}
	if(direzione=="down"){ 
		this->RuotaY(90); 
		this->MuoviAvanti(speed); 
		this->RuotaY(-90); 
	}
	if(direzione=="left"){this->MuoviAvanti(-speed);}
	if(direzione=="right"){this->MuoviAvanti(speed);}
} 

///////////////////////////////////////////////////////////////////
void raf::BillBoard::RuotaY(int speed){
	core::vector3df rotaz=this->getRotation();
	rotaz.Y+=speed;
	this->setRotation(rotaz);
}
//////////////////////////////////////////////////////////////////
void raf::BillBoard::Trasparente(const char* percorso_texture) {
	this->setMaterialTexture(0, driver_drag->getTexture(percorso_texture)); 
	this->setMaterialFlag(video::EMF_LIGHTING, false); 
	this->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR ); 
}
//**********************************************************
//*************FINE FUNZIONI PER LA CLASSE BILLBOARD***********
//**********************************************************
scene::ISceneNode* raf::CaricaMappa(std::string file) {
	raf::esiste(file.c_str());
	scene::IAnimatedMesh* filemappa = smgr_drag->getMesh(file.c_str());
	scene::ISceneNode* mappa = 0;
	if (filemappa)
		mappa = smgr_drag->addOctTreeSceneNode(filemappa->getMesh(0));
	if (mappa){		
		scene::ITriangleSelector* tri = smgr_drag->createOctTreeTriangleSelector(
			 filemappa->getMesh(0), mappa, 128);
		  mappa->setTriangleSelector(tri);
		  meta_selector->addTriangleSelector(tri);
		  tri->drop();
	 }
	return mappa;
}
///////////////////////////////////////////////////////////////////
void raf::InizializzaRaf(IrrlichtDevice* device2) {
	//world_selector_drag=world_selector;
	device_drag=device2;
	driver_drag=device_drag->getVideoDriver();
	smgr_drag=device_drag->getSceneManager();

	if(meta_selector!=NULL)
		meta_selector->drop();
	meta_selector=smgr_drag->createMetaTriangleSelector();
}
core::vector3df raf::GetPointInFrontOfCamera() {
	core::dimension2d<s32> screen_size=driver_drag->getScreenSize();
	core::position2d<s32> center_of_the_screen(screen_size.Width,screen_size.Height);
	center_of_the_screen.X/=2;
	center_of_the_screen.Y/=2;

	core::vector3df pos;
	core::line3d<f32> line=smgr_drag->getSceneCollisionManager()->getRayFromScreenCoordinates(center_of_the_screen);

	pos=line.getMiddle();
	core::line3d<f32> line1(line.start,pos);
	pos=line1.getMiddle();
	core::line3d<f32> line2(line.start,pos);
	pos=line2.getMiddle();
	core::line3d<f32> line3(line.start,pos);
	pos=line3.getMiddle();
	return pos;
}
//yesno message box
//------------------------------------------------------------------
#ifndef WIN32
bool ok_yn_messagebox=false;
bool yes;
class yes_no_messagebox_class:public IEventReceiver{
public:
	virtual bool OnEvent(SEvent event) {
		if(event.EventType==EET_GUI_EVENT&&
			event.GUIEvent.EventType==gui::EGET_MESSAGEBOX_YES) {
				yes=true;
				ok_yn_messagebox=true;
		}
		if(event.EventType==EET_GUI_EVENT&&
			event.GUIEvent.EventType==gui::EGET_MESSAGEBOX_NO) {
				yes=false;
				ok_yn_messagebox=true;
		}
		return false;
	}
}yn_messagebox_event;
#endif

bool raf::AddYesNoMessagebox(std::string message,std::string caption) {
#ifndef WIN32
	ok_yn_messagebox=false;
	IEventReceiver* last_receiver=device_drag->getEventReceiver();
	wchar_t* w_message=raf::conv::CharWChar_T(message.c_str());
	wchar_t* w_caption=raf::conv::CharWChar_T(caption.c_str());
	device_drag->getGUIEnvironment()->addMessageBox(w_caption,w_message,true,gui::EMBF_YES|gui::EMBF_NO);
	device_drag->setEventReceiver(&yn_messagebox_event);
	while(!ok_yn_messagebox&&device_drag->run()) {
		driver_drag->beginScene(true,true,video::SColor(0,0,0,0));
		smgr_drag->drawAll();
		device_drag->getGUIEnvironment()->drawAll();
		driver_drag->endScene();
	}	
	device_drag->setEventReceiver(last_receiver);
	delete w_message;
	delete w_caption;
	return yes;

#else
	int value=MessageBoxA(NULL,message.c_str(),caption.c_str(),MB_YESNO|MB_SYSTEMMODAL);
	if(value==IDYES) return true;
	else if(value==IDNO) return false;
	else raf::FatalError("Fatal error in function AddYesNoMessageBox. Parameters: "+message+" "+caption);
#endif
}
//end of yesno messagebox
//------------------------------------------------------------
//error runtime
#ifndef WIN32
bool ok=false;
class error_event_class:public IEventReceiver{
public:
	virtual bool OnEvent(SEvent event) {
		if(event.EventType==EET_GUI_EVENT&&
			event.GUIEvent.EventType==gui::EGET_MESSAGEBOX_OK) {
				ok=true;
		}
		return false;
	}
}error_event;
#endif

#ifndef WIN32
void raf::errore(std::string message,std::string caption/*="Error"*/) {
	ok=false;
	IEventReceiver* last_receiver=device_drag->getEventReceiver();
	wchar_t* w_message=raf::conv::CharWChar_T(message.c_str());
	wchar_t* w_caption=raf::conv::CharWChar_T(caption.c_str());
	device_drag->getGUIEnvironment()->addMessageBox(w_caption,w_message);
	device_drag->setEventReceiver(&error_event);
	while(!ok&&device_drag->run()) {
		driver_drag->beginScene(true,true,video::SColor(0,0,0,0));
		smgr_drag->drawAll();
		device_drag->getGUIEnvironment()->drawAll();
		driver_drag->endScene();
	}	
	device_drag->setEventReceiver(last_receiver);
	delete w_message;
	delete w_caption;
}

#else

void raf::errore(std::string message,std::string caption/*="Error"*/) {
	MessageBoxA(NULL,message.c_str(),caption.c_str(),MB_ICONERROR|MB_SYSTEMMODAL);
}
#endif

ARES_API void raf::Message(std::string message,std::string caption/*="Error"*/) {
	MessageBoxA(NULL,message.c_str(),caption.c_str(),MB_SYSTEMMODAL);
}
ARES_API float raf::GetMeshRay(scene::IMesh* m) {
	core::aabbox3d<f32> box=m->getBoundingBox();
	return box.MaxEdge.Y/2;
}

//----------------------------------------------------
void raf::FatalError(std::string message,std::string caption/*="Error"*/) {
	raf::errore(message,caption);
	exit(-1);
}
//end of error runtime
//-------------------------------------------------------------
u32 raf::itime(core::vector3df start,core::vector3df end,f32 speed) {
	f32 length = (f32)(end - start).getLength();
	u32 time = (u32)(length / speed);
	return time;
}
//--------------------------------------------------------------
void raf::esiste(std::string file) {
	if(!device_drag->getFileSystem()->existFile(file.c_str())) {
		raf::errore("The file "+file+" does not exist");
		exit(-1);
	}
}
//-------------------------------------------------------------------
void raf::DiffuseLight(irr::scene::ISceneNode* node,bool dl) {
	if(dl) {
		node->setMaterialFlag(video::EMF_LIGHTING,false);
	}
	else {
		node->setMaterialFlag(video::EMF_LIGHTING,true);
	}
}
//----------------------------------------------------------
ARES_API scene::ITriangleSelector* raf::PrendiSelector() {return meta_selector;}
//------------------------------------------------------------
std::string raf::conv::BoolString(bool b) {
	if(b==true) {
		return "yes";
	}
	else{
		return "no";
	}
}

void raf::ChWorkingDirectoryToThisProg(char* argv0) {
	std::string path=raf::String::EraseFileNameFromPath(argv0);
	_chdir(path.c_str());
}
//-------------------------------------------------------------
core::vector3df raf::Land(
						  core::vector3df pos,
						  scene::ITriangleSelector* world_selector,
						  float radius) {

	core::vector3df pos_backup=pos;
	//per farlo atterrare	 
	core::line3d<f32>	line;
	core::vector3df		contatto;
	core::triangle3df	tri;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	line.start = pos;
	//modifico pos. per questo prima gli faccio il backup
	pos.Y -= 99999999;
	line.end = pos;
	if(smgr_drag->
		getSceneCollisionManager()->
		getCollisionPoint(line, world_selector, contatto, tri))
	{
		contatto.Y+=radius;
		return contatto;
	}
	return pos_backup;
}

void raf::Land(
			   scene::ISceneNode* node,
			   scene::ITriangleSelector* world_selector,
			   float radius) {
	node->setPosition(
		raf::Land(node->getPosition(),world_selector,radius));
}
//--------------------------------------------------------
std::string raf::GetWin32ProgramFullPath() {
	std::string cml(GetCommandLineA());
	int pos=cml.find('\"',2); 
	//elimina quello che non fa parte del path ma della riga di comando
	if(pos>0) {
		cml.erase(pos,(cml.size()-pos));
	}
	cml+='\"';
	return cml;
}
//--------------------------------------------------------------
void raf::ChangeCurrentDirTo(std::string destdir) {
	current_dir=device_drag->getFileSystem()->getWorkingDirectory();
	device_drag->getFileSystem()->changeWorkingDirectoryTo(destdir.c_str());
	_chdir(destdir.c_str());
}
//-------------------------------------------------------------
void raf::RestoreDir() {
	device_drag->getFileSystem()->changeWorkingDirectoryTo(current_dir.c_str());
}
//-------------------------------------------------------------
std::string raf::UpDir(std::string dir) {
	int pos=dir.find_last_of('\\');
	std::string returned=raf::String::SubString(dir,0,pos-1);
	return returned;
}
//-------------------------------------------------------------
bool file_open_ok=false;
std::string selected_file;
gui::IGUIFileOpenDialog* file_dialog;
class fil_open_event_class:public IEventReceiver {
public:
	virtual bool OnEvent(SEvent event) {
		if(event.EventType==EET_GUI_EVENT&&
			event.GUIEvent.EventType==gui::EGET_FILE_SELECTED) {
				const wchar_t* file_selected_w=file_dialog->getFilename();
				char* file_c=raf::conv::WChar_tChar(file_selected_w);
				selected_file=file_c;
				delete file_c;
				file_open_ok=true;				
		}
		if(event.EventType==EET_GUI_EVENT&&
			event.GUIEvent.EventType==gui::EGET_FILE_CHOOSE_DIALOG_CANCELLED) {
				file_open_ok=true;
		}
		return false;
	}
}file_open_event;
//-----------------------------------------------------
std::string raf::AddFileOpenDialog(const wchar_t* title,bool modal/*=true*/,gui::IGUIElement* parent/*=0*/,s32 id/*=-1*/) {
	file_open_ok=false;

	IEventReceiver* last_event_receiver=device_drag->getEventReceiver();

	file_dialog=device_drag->getGUIEnvironment()->addFileOpenDialog(title,modal,parent,id);
	device_drag->setEventReceiver(&file_open_event);

	while(!file_open_ok&&device_drag->run()) {
		driver_drag->beginScene(true,true,video::SColor(255,0,0,0));
		smgr_drag->drawAll();
		device_drag->getGUIEnvironment()->drawAll();
		driver_drag->endScene();
	}

	device_drag->setEventReceiver(last_event_receiver);
	return selected_file;
}
//ARES SPECIFIC FUNCTION
std::string raf::GetAresFPSHome() {
	HKEY open_key;
	DWORD type;
	DWORD size_of_data=2000;
	char* data=new char[2000];
	BOOL err=RegOpenKeyExA(
		HKEY_CLASSES_ROOT,
		"MancusoRaffaele\\AresFPS\\InstallDir",
		0,//reserved
		KEY_QUERY_VALUE,
		&open_key);

	if(err==FALSE)
		return "";

	RegQueryValueExA(
		open_key,
		"",//value to query
		NULL,//reserved
		&type,
		(unsigned char*)data,
		&size_of_data);
	RegCloseKey(open_key);
	std::string returned(data);
	delete data;

	//ceck if the path is correct
	std::string ares_game_exe_path=returned+"\\bin\\ares_game.exe";
	FILE* f=fopen(ares_game_exe_path.c_str(),"rb");
	if(!f) {
		//fail!
		return "";
	}
	else fclose(f);
	return returned;
}
bool raf::CeckPackage(std::string ares_home,std::string package_name) {
	//insert package.txt into a vector
	raf::file pkg_file(ares_home+"\\config\\package.txt");
	std::vector<std::string> s=pkg_file.GetVector();

	for(int i=0;i<s.size();i++) {
		if(s[i]==package_name) return true;
	}
	return false;
}
float raf::GetAresFPSVerFromReg() {
	HKEY open_key;
	DWORD type;
	DWORD size_of_data=2000;
	char* data=new char[2000];
	RegOpenKeyExA(
		HKEY_CLASSES_ROOT,
		"MancusoRaffaele\\AresFPS\\Ver",
		0,//reserved
		KEY_QUERY_VALUE,
		&open_key);

	//ceck if the key don't exist
	if(!open_key)
		return -1;

	RegQueryValueExA(
		open_key,
		"",//value to query
		NULL,//reserved
		&type,
		(unsigned char*)data,
		&size_of_data);
	RegCloseKey(open_key);
	std::string returned(data);
	delete data;
	return atof(returned.c_str());
}
#endif






