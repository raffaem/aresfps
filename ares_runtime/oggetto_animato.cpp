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
#include <windows.h>
#include "oggetto_animato.hpp"
namespace raf{
	char sign(long double num);
	scene::ITriangleSelector* PrendiSelector();

	class BillBoard:public irr::scene::IBillboardSceneNode {
	public:
		void Collisione(scene::ITriangleSelector* world_selector=NULL,float radiusx=0,float radiusy=0,float radiusz=0,float gravityx=0,float gravityy=-100.0f,float gravityz=0);
		void Muovi(int speed);
		void MuoviX(int speed);
		void MuoviY(int speed);
		void MuoviZ(int speed);
		void RuotaX(int speed);
		void RuotaY(int speed);
		void RuotaZ(int speed);
		void Trasparente(std::string percorso_texture="nero.jpg");
		scene::IBillboardSceneNode* TornaParticellaCapo();
	};
	typedef BillBoard* BILLBOARD;
}

//using namespace irr;
using namespace std;

extern raf::BILLBOARD bill;
extern scene::ITriangleSelector* selector;
extern scene::ISceneManager* smgr_drag;
extern video::IVideoDriver* driver_drag;
extern IrrlichtDevice* device_drag;
extern raf::BILLBOARD  shred[];

//inizio scenenode
//oggettoanimato
void raf::OggettoAnimato::NewRotationX(float speed) {
	core::vector3df rot=this->getRotation();
	rot.X=speed;
	this->setRotation(rot);
}
void raf::OggettoAnimato::NewRotationY(float speed) {
		core::vector3df rot=this->getRotation();
	rot.Y=speed;
	this->setRotation(rot);

}
void raf::OggettoAnimato::NewRotationZ(float speed) {
		core::vector3df rot=this->getRotation();
	rot.Z=speed;
	this->setRotation(rot);

}
//fine

//----------------------------------------------------------------
void raf::OggettoAnimato::LevaTrasparente(string percorso_texture){
	this->setMaterialTexture(0, driver_drag->getTexture(percorso_texture.c_str()));
	this->setMaterialFlag(video::EMF_LIGHTING, true);
	this->setMaterialType(video::EMT_SOLID );
} 
//--------------------------------------------------------------
scene::ISceneNodeAnimatorCollisionResponse* raf::OggettoAnimato::Collisione(f32& yradius_return,scene::ITriangleSelector* world_selector,float radiusx,float radiusy,float radiusz,float gravityx,float gravityy,float gravityz){
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
	yradius_return=radius.Y;
	return anim;
}
//-------------------------------------------------------------
scene::ISceneNodeAnimatorCollisionResponse* raf::OggettoAnimato::Collisione2(f32& yradius_return,scene::ITriangleSelector* world_selector,float radiusx,float radiusy,float radiusz,float gravityx,float gravityy,float gravityz) {
	if(world_selector==NULL) {world_selector=raf::PrendiSelector();}
	core::aabbox3d<f32> box;
	box=this->getTransformedBoundingBox();
	core::vector3df radius((box.MaxEdge.X-box.MinEdge.X)/2,(box.MaxEdge.Y-box.MinEdge.Y)/2,(box.MaxEdge.Z-box.MinEdge.Z)/2);
	radius.X+=radiusx;
	radius.Y+=radiusy;
	yradius_return=radius.Y;
	radius.Z+=radiusz;
	core::vector3df gravity(gravityx,gravityy,gravityz);
	scene::ISceneNodeAnimatorCollisionResponse* anim =smgr_drag->createCollisionResponseAnimator(
		world_selector, this, radius,
		gravity, core::vector3df(0,0,0),0);
	this->addAnimator(anim);
	return anim;
}
//---------------------------------------------------------------
void raf::OggettoAnimato::Trasparente(string percorso_texture/*="nero.jpg"*/){ 
	if(device_drag->getFileSystem()->existFile(percorso_texture.c_str())==false) {
		MessageBoxA(NULL,"errore il file non esiste","errore",MB_SYSTEMMODAL|MB_OK);
		exit(-1);
	}
	this->setMaterialTexture(0, driver_drag->getTexture(percorso_texture.c_str())); 
	this->setMaterialFlag(video::EMF_LIGHTING, false); 
	this->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR); 
} 
//-------------------------------------------------------------------
void raf::OggettoAnimato::AnimaMs3d(int inizio, int fine,int totale){
	if (inizio==0)
		this->setFrameLoop((1.984*totale), (fine*41.65));
	if (inizio!=0)
		this->setFrameLoop(inizio*41.65, fine*41.65);

}
//-------------------------------------------------------------------
//*********************************************************
//*****FINE FUNZIONI PER LA CLASSE OggettoAnimato**********