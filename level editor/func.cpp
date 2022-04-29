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
#include "stdafx.h"
#include "evar.hpp"
using namespace irr;

//FREE POSITION FUNCTION
int LevelmodelGetFreePosition() {
	if(level_models_free.size()>-1) {
		int pos=level_models_free[0];
		level_models_free.erase(level_models_free.begin());
		return pos;
	}
	else{
		level_models.push_back(NULL);
		int pos=level_models.size()-1;
		return pos;
	}
}
int MedikitsGetFreePosition() {
	if(medikits_free.size()>-1) {
		int pos=medikits_free[0];
		medikits_free.erase(medikits_free.begin());
		return pos;
	}
	else{
		medikit_class c;
		medikits.push_back(c);
		int pos=medikits.size()-1;
		return pos;
	}
}
int LightsGetFreePosition() {
	if(lights_free.size()>-1) {
		int pos=lights_free[0];
		lights_free.erase(lights_free.begin());
		return pos;
	}
	else{
		lights.push_back(NULL);
		int pos=lights.size()-1;
		return pos;
	}
}

int EnemiesGetFreePosition() {
	if(enemies_free.size()>-1) {
		int pos=enemies_free[0];
		enemies_free.erase(enemies_free.begin());
		return pos;
	}
	else{
		enemies.push_back(NULL);
		int pos=enemies.size()-1;
		return pos;
	}
}
int TerrainGetFreePosition() {
	if(terrain_free.size()>-1) {
		int pos=terrain_free[0];
		terrain_free.erase(terrain_free.begin());
		return pos;
	}
	else{
		terrain_nodes.push_back(NULL);
		int pos=terrain_nodes.size()-1;
		return pos;
	}
}
int AmmunationGetFreePosition() {
	if(ammunation_free.size()>-1) {
		int pos=ammunation_free[0];
		ammunation_free.erase(ammunation_free.begin());
		return pos;
	}
	else{
		ammunation.push_back(NULL);
		int pos=ammunation.size()-1;
		return pos;
	}
}

int ArmourGetFreePosition() {
	if(armours_free.size()>-1) {
		int pos=armours_free[0];
		armours_free.erase(armours_free.begin());
		return pos;
	}
	else{
		armour_class c;
		armours.push_back(c);
		int pos=armours.size()-1;
		return pos;
	}
}
//END OF FREE POSITION FUNCTION

void LoadMedia() {
	raf::ChangeCurrentDirTo(prog_dir);
	camera =(raf::CAMERA) smgr->addCameraSceneNode();

	 //load weapon
	
	weapon=smgr->addMeshSceneNode(smgr->getMesh("media\\models\\shot_gun.md2")->getMesh(1));
	weapon->setMaterialTexture(0,driver->getTexture("media\\texture\\shot_gun.jpg"));
	raf::DiffuseLight(weapon,dl);

	//load the texture of the light
	bill_texture=driver->getTexture("media\\texture\\particle.bmp");

	//create a meta triangle selector
	world_selector=smgr->createMetaTriangleSelector();

	//set event receiver
	device->setEventReceiver(&env_rec);
}

void Exit() {
	//dealloca le luci
	for(int i=0;i<lights.size();i++) {
		if(lights[i]!=NULL) {
			delete lights[i];
		}
	}
	//elimina i modelli
	for(i=0;i<level_models.size();i++) {
		if(level_models[i]!=NULL) {
			delete level_models[i];
		}
	}
	//dealloca terreni
	for(i=0;i<terrain_nodes.size();i++) {
		if(terrain_nodes[i]!=NULL) {
			delete terrain_nodes[i];
		}
	}

	//AMMUNATION
	for(i=0;i<ammunation.size();i++) {
		if(ammunation[i]!=NULL) {
			delete ammunation[i];
		}
	}

	device->closeDevice();
	return;
}
void GetMapName(string& modello,string& texture) {
	OPENFILENAME OpenFileName;
	TCHAR         szFile[MAX_PATH]      = "\0";
    strcpy( szFile, "");

	OpenFileName.lStructSize       = sizeof(OPENFILENAME);
    OpenFileName.hwndOwner         = NULL;
    OpenFileName.hInstance         = NULL;
    OpenFileName.lpstrFilter       = "Directx X model(.x)\0*.x\0 3d Studio (.3ds)\0*.3ds\0Maya (.obj)\0*.obj\0Cartography shop 4 (.csm)\0*.csm\0COLLADA (.dae)\0*.dae\0COLLADA (.xml)\0*.xml\0Delgine DeleD (.dmf)\0*.dmf\0Milkshape (.ms3d)\0*.ms3d\0My3D (.my3d) \0*.my3d\0OCT (.oct)\0*.oct\0Pulsar LMTools (.lmts) \0*.lmts\0Quake 3 levels (.bsp) \0*.bsp\0Quake 2 models (.md2) \0*.md2\0All files (*.*)\0*.*\0\0";
    OpenFileName.lpstrCustomFilter = NULL;
    OpenFileName.nMaxCustFilter    = 0;
    OpenFileName.nFilterIndex      = 0;
    OpenFileName.lpstrFile         = szFile;
    OpenFileName.nMaxFile          = sizeof(szFile);
    OpenFileName.lpstrFileTitle    = NULL;
    OpenFileName.nMaxFileTitle     = 0;
    OpenFileName.lpstrInitialDir   = NULL;
    OpenFileName.lpstrTitle        = "Open a level model";
    OpenFileName.nFileOffset       = 0;
    OpenFileName.nFileExtension    = 0;
    OpenFileName.lpstrDefExt       = NULL;
    OpenFileName.lCustData         = 0;
	OpenFileName.lpfnHook 		   = NULL;
	OpenFileName.lpTemplateName    = NULL;
    OpenFileName.Flags             = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_EXPLORER|OFN_HIDEREADONLY;


	if(GetOpenFileName(&OpenFileName)==FALSE) {
		string err="errore numero ";
		DWORD errore_numero=CommDlgExtendedError();
		err+=raf::conv::NumString(errore_numero);

		if(errore_numero==0) {
			//non ha selezionato nessun file
			modello="";
			texture="";
			return;
		}	
		
		MessageBox(NULL,err.c_str(),"error",MB_SYSTEMMODAL);
	};

	modello=OpenFileName.lpstrFile;

	//texture
	OpenFileName.lpstrFilter="BMP\0*.bmp\0JPG\0*.jpg\0TGA\0*.tga\0PCX\0*.pcx\0PNG\0*.png\0PSD\0*.psd\0Tutti i formati supportati\0*.bmp;*.jpg;*.tga;*.pcx;*.png;*.psd\0Tutti i file (*.*)\0*.*\0\0";
    OpenFileName.lpstrTitle= "Choose a texture.You can press cancel if you don't want a texture";
	BOOL result=GetOpenFileName(&OpenFileName);
	DWORD error_number=CommDlgExtendedError();

	if(result==false&&error_number==0) {
		texture="noTexture";
	}

	else if(result==false&&error_number!=0) {
		string err="errore numero ";
		err+=raf::conv::NumString(error_number);
		MessageBox(NULL,err.c_str(),"error",MB_SYSTEMMODAL);
		exit(1);
	}
	else {
		texture=OpenFileName.lpstrFile;	
	}

	return;
}
void GetTerrainName(std::string& heightmap,std::string& texture,std::string& dtexture) {

	//HEIGHTMAP
	OPENFILENAME OpenFileName;
	TCHAR  szFile[MAX_PATH]      = "\0";
    strcpy( szFile, "");

	OpenFileName.lStructSize       = sizeof(OPENFILENAME);
    OpenFileName.hwndOwner         = NULL;
    OpenFileName.hInstance         = NULL;
    OpenFileName.lpstrCustomFilter = NULL;
    OpenFileName.nMaxCustFilter    = 0;
    OpenFileName.nFilterIndex      = 0;
    OpenFileName.lpstrFile         = szFile;
    OpenFileName.nMaxFile          = sizeof(szFile);
    OpenFileName.lpstrFileTitle    = NULL;
    OpenFileName.nMaxFileTitle     = 0;
    OpenFileName.lpstrInitialDir   = NULL;
    OpenFileName.nFileOffset       = 0;
    OpenFileName.nFileExtension    = 0;
    OpenFileName.lpstrDefExt       = NULL;
    OpenFileName.lCustData         = 0;
	OpenFileName.lpfnHook 		   = NULL;
	OpenFileName.lpTemplateName    = NULL;
    OpenFileName.Flags             = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_EXPLORER|OFN_HIDEREADONLY;
	OpenFileName.lpstrFilter="BMP\0*.bmp\0JPG\0*.jpg\0TGA\0*.tga\0PCX\0*.pcx\0PNG\0*.png\0PSD\0*.psd\0Tutti i formati supportati\0*.bmp;*.jpg;*.tga;*.pcx;*.png;*.psd\0Tutti i file (*.*)\0*.*\0\0";
    OpenFileName.lpstrTitle= "Choose a heightmap to create the terrain";

	if(GetOpenFileName(&OpenFileName)==FALSE) {
		string err="errore numero ";
		DWORD errore_numero=CommDlgExtendedError();
		err+=raf::conv::NumString(errore_numero);

		if(errore_numero==0) {
			//non ha selezionato nessun file
			heightmap="";
			texture="";
			dtexture="";
			return;
		}	
		
		raf::errore(err);
	};
	heightmap=OpenFileName.lpstrFile;

	//TEXTURE
    OpenFileName.lpstrTitle= "Choose a texture for your terrain. You can press cancel";
	BOOL result=GetOpenFileName(&OpenFileName);
	DWORD error_number=CommDlgExtendedError();

	//press cancel
	if(result==false&&error_number==0) {
		texture="";
		dtexture="";
		return;
	}
	//error
	else if(result==false&&error_number!=0) {
		string err="errore numero ";
		err+=raf::conv::NumString(error_number);
		raf::errore(err);
		exit(1);
	}
	//texture
	else {
		texture=OpenFileName.lpstrFile;	
	}

	//DETAIL TEXTURE
	OpenFileName.lpstrTitle= "Choose a detail texture for your terrain. You can press cancel";
	result=GetOpenFileName(&OpenFileName);
	error_number=CommDlgExtendedError();

	//press cancel
	if(result==false&&error_number==0) {
		dtexture="";
		return;
	}
	//error
	else if(result==false&&error_number!=0) {
		string err="errore numero ";
		err+=raf::conv::NumString(error_number);
		raf::errore(err);
		exit(1);
	}
	//texture
	else {
		dtexture=OpenFileName.lpstrFile;	
	}
	return;
}

void ClearLevel() {
	bool load_media=true;

	//erase all scene node
	if(smgr)
		smgr->clear();
	else 
		load_media=false;
			
	//clear the vector
	enemies.clear();
	lights.clear();
	medikits.clear();
	level_models.clear();
	terrain_nodes.clear();
	ammunation.clear();
	armours.clear();

	enemies_free.clear();
	lights_free.clear();
	medikits_free.clear();
	level_models_free.clear();
	terrain_free.clear();
	ammunation_free.clear();

	selectnode=NULL;

	//restore camera,weapon and other medias
	if(load_media)
		LoadMedia();	
}
void SelectANode() {
	if(selectnode!=NULL) {
		selectnode->setDebugDataVisible(true); 
		string ID=raf::conv::NumString(selectnode->getID());
		obj_type=ID[0];

		//se è una luce
		if(obj_type==type::light) {
			//prende la posizione nel vettore
			//elimina il 4
			ID.erase(0,1);
			int pos=atoi(ID.c_str());
			lights[pos]->light->setDebugDataVisible(true); 
			lights[pos]->bill->setDebugDataVisible(true); 
			selectnode=lights[pos]->light;
		}//fine se è una luce

		if(obj_type==type::level_model) //è un modello di livello
			IsRotable(true);
		if(obj_type==type::terrain) //è un terreno
			IsRotable(true);
		//set the edit box to the right value
		SetPosRotScale();

	}//if(selectnode!=NULL) {
	else //if(selectnode!=NULL) {
		UnselectANode();
}
void UnselectANode() {
	if(selectnode!=NULL) {
		selectnode->setDebugDataVisible(false);
		selectnode=NULL;
	}
	/*
	pos_x->setText(L"");
	pos_y->setText(L"");
	pos_z->setText(L"");
	rot_x->setText(L"");
	rot_y->setText(L"");
	rot_z->setText(L"");
	scale_x->setText(L"");
	scale_y->setText(L"");
	scale_z->setText(L"");
	*/
	
	IsRotable(true);
}
void MoveANode() {
	if(selectnode!=NULL) {

	//get the ID
	string ID=raf::conv::NumString(selectnode->getID());
	if(ID!="") {

	//se è un medikit
	if(ID[0]==type::medikit) {
		//prende la posizione nel vettore
		//elimina il 2
		ID.erase(0,1);
		int pos=atoi(ID.c_str());
		raf::Land(medikits[pos].ogg,
			raf::PrendiSelector(),0);
	}

	//se è un nemico
	else if(ID[0]==type::enemie) {
		//prende la posizione nel vettore
		//elimina il 2
		ID.erase(0,1);
		int pos=atoi(ID.c_str());
		raf::Land(enemies[pos],
			raf::PrendiSelector(),
			enemies[pos]->GetRadius());
	}//else if(ID[0]=='3') {
	//se è una luce
	else if(ID[0]==type::light) {
		core::vector3df cam_pos=camera->getPosition();
		//prende la posizione nel vettore
		//elimina il 4
		ID.erase(0,1);
		int pos=atoi(ID.c_str());

		//rimuova la luce
		lights[pos]->light->setPosition(cam_pos);

		//posizione del billboard uguale a quella della luce
		lights[pos]->bill->setPosition(cam_pos);
	}//if(ID[0]=='4') {
	//se è una munizione
	else if(ID[0]==type::ammunation) {
		//prende la posizione nel vettore
		//elimina il 2
		ID.erase(0,1);
		int pos=atoi(ID.c_str());
		raf::Land(ammunation[pos]->ogg,
			raf::PrendiSelector(),0);
	}
	else if(ID[0]==type::armour) {
		//prende la posizione nel vettore
		//elimina il 2
		ID.erase(0,1);
		int pos=atoi(ID.c_str());
		raf::Land(armours[pos].ogg,world_selector,0);
	}
	}//if(ID!=NULL)
	else{raf::errore("Error in function MoveANode. ID=\"\" and selectnode= .Please contact support. Press ok to continue");}

	//refresh the editboxes
	/*
	TO ACTIVE
	SetPosRotScale();
	*/

	}//if(selectnode!=NULL) {
}//void MoveANode() {
void EraseANode() {
	if(selectnode!=NULL) {
	//get the ID
	string ID=raf::conv::NumString(selectnode->getID());
	//se è una mappa
	if(ID[0]==type::level_model) {
		//prende la posizione nel vettore
		//elimina l'1
		ID.erase(0,1);
		int pos=atoi(ID.c_str());
		//rimuove l'oggetto
		level_models[pos]->ogg->remove();
		//dealloca la memoria dinamica allocata
		delete level_models[pos];
		//setta il puntatore a null
		level_models[pos]=NULL;		
		//indica che c'è una nuova posizione libera nel vettore
		level_models_free.push_back(pos);
		//oggetto selezionato settato a NULL
		selectnode=NULL;
	}//if(ID[0]==type::level_model) {
	//se è un medikit
	else if(ID[0]==type::medikit) {
		//prende la posizione nel vettore
		//elimina il 2
		ID.erase(0,1);
		int pos=atoi(ID.c_str());
		medikits[pos].ogg->remove();
		medikits[pos].ogg=NULL;
		medikits_free.push_back(pos);
		selectnode=NULL;
	}//else if(ID[0]==type::medikit) {
	//se è un nemico
	else if(ID[0]==type::enemie) {
		//prende la posizione nel vettore
		//elimina il 3
		ID.erase(0,1);
		int pos=atoi(ID.c_str());
		enemies[pos]->remove();
		enemies[pos]=NULL;
		enemies_free.push_back(pos);
		selectnode=NULL;
	}//else if(ID[0]=='3') {
	//se è un billboard che rappresenta una luce o una luce
	else if(ID[0]==type::light) {
		//prende la posizione nel vettore
		//elimina il 4
		ID.erase(0,1);
		int pos=atoi(ID.c_str());
		//elimina la luce dalla scena
		lights[pos]->light->remove();
		//elimina il billboard dalla scena
		lights[pos]->bill->remove();
		//dealloca la memoria allocata
		delete lights[pos];
		//setta il puntatore a NULL
		lights[pos]=NULL;
		//c'è una nuova zona nel vettore libera
		lights_free.push_back(pos);
		//oggetto selezionato settato a NULL
		selectnode=NULL;						
	}//else if(ID[0]=='3') {
	else if(ID[0]==type::terrain) {
		//prende la posizione nel vettore
		//elimina il 5
		ID.erase(0,1);
		int pos=atoi(ID.c_str());
		//rimuove l'oggetto
		terrain_nodes[pos]->ogg->remove();
		//dealloca la memoria dinamica allocata
		delete terrain_nodes[pos];
		//setta il puntatore a null
		terrain_nodes[pos]=NULL;		
		//indica che c'è una nuova posizione libera nel vettore
		terrain_free.push_back(pos);
		//oggetto selezionato settato a NULL
		selectnode=NULL;
	}//else if(ID[0]==type::terrain) {
	else if(ID[0]==type::ammunation) {
		//prende la posizione nel vettore
		//elimina il 2
		ID.erase(0,1);
		int pos=atoi(ID.c_str());
		ammunation[pos]->ogg->remove();
		ammunation[pos]=NULL;
		ammunation_free.push_back(pos);
		selectnode=NULL;
	}//else if(ID[0]==type::ammunation) {
	else if(ID[0]==type::armour) {
		//prende la posizione nel vettore
		//elimina il 2
		ID.erase(0,1);
		int pos=atoi(ID.c_str());
		armours[pos].ogg->remove();
		armours[pos].ogg=NULL;
		armours_free.push_back(pos);
		selectnode=NULL;
	}//else if(ID[0]==type::ammunation) {
	else {
		raf::errore("Impposible to erase selected node");
	}//else{
	UnselectANode();
	}//if(selectnode!=NULL) {
	else{////if(selectnode!=NULL) {
		raf::errore("No selected object. See object->Select");
	}//else{
}//void EraseANode() {
//-----------------------------------------------------
void DiffuseLight() {
	//diffuse light at the maps
	for(int i=0;i<level_models.size();i++) {
		if(level_models[i]!=NULL) {
			raf::DiffuseLight(level_models[i]->ogg,dl);
		}
	}
	//diffuse light for the weapon
	raf::DiffuseLight(weapon,dl);

	//diffuse light at the enemies
	for(i=0;i<enemies.size();i++) {
		if(enemies[i]!=NULL) {
			raf::DiffuseLight(enemies[i],dl);
			scene::ISceneNode* attached_weapon=enemies[i]->GetAttachedWeapon();
			if(attached_weapon!=NULL)
				raf::DiffuseLight(attached_weapon,dl);						
		}
	}
	//diffuse light at the medikit
	for(i=0;i<medikits.size();i++) {
		if(medikits[i].ogg!=NULL) {
			raf::DiffuseLight(medikits[i].ogg,dl);
		}
	}

	//diffuse light at the armours
	for(i=0;i<armours.size();i++) {
		if(armours[i].ogg!=NULL) {
			raf::DiffuseLight(armours[i].ogg,dl);
		}
	}
}//void DiffuseLight() {
/*
void SetPosRotScale() {
	if(selectnode!=NULL) {
		//position
		wchar_t* w=raf::conv::NumWChar_t(selectnode->getPosition().X);
		pos_x->setText(w);
		delete w;
		w=raf::conv::NumWChar_t(selectnode->getPosition().Y);
		pos_y->setText(w);
		delete w;
		w=raf::conv::NumWChar_t(selectnode->getPosition().Z);
		pos_z->setText(w);
		delete w;

		//rotation
		w=raf::conv::NumWChar_t(selectnode->getRotation().X);
		rot_x->setText(w);
		delete w;
		w=raf::conv::NumWChar_t(selectnode->getRotation().Y);
		rot_y->setText(w);
		delete w;
		w=raf::conv::NumWChar_t(selectnode->getRotation().Z);
		rot_z->setText(w);
		delete w;

		//scale
		w=raf::conv::NumWChar_t(selectnode->getScale().X);
		scale_x->setText(w);
		delete w;
		w=raf::conv::NumWChar_t(selectnode->getScale().Y);
		scale_y->setText(w);
		delete w;
		w=raf::conv::NumWChar_t(selectnode->getScale().Z);
		scale_z->setText(w);
		delete w;		
	}//if(selectnode!=NULL) {
}
void IsRotable(bool val) {
	if(val==false) {
		rot_x->setVisible(false);
		rot_z->setVisible(false);
		scale_x->setVisible(false);
		scale_y->setVisible(false);
		scale_z->setVisible(false);
	}//if(val==false) {
	else if(val==true) {
		rot_x->setVisible(true);
		rot_z->setVisible(true);
		scale_x->setVisible(true);
		scale_y->setVisible(true);
		scale_z->setVisible(true);
	}//if(val==false) {
}*/
void SetPosRotScale() {
}
void IsRotable(bool val) {}
void ChangeFPSCam() {
				FPS_camera=!FPS_camera;
				if(FPS_camera) {
					core::vector3df pos=camera->getPosition();
					core::vector3df lookat=camera->getTarget();
						camera->remove();
					camera=(raf::CAMERA)smgr->addCameraSceneNodeFPS();
					camera->setPosition(pos);
					camera->setTarget(lookat);
					device->getCursorControl()->setVisible(false);
				}
				else{
					device->getCursorControl()->setVisible(true);
					core::vector3df pos=camera->getPosition();
					core::vector3df lookat=camera->getTarget();
					camera->remove();
					camera=(raf::CAMERA)smgr->addCameraSceneNode();
					camera->setPosition(pos);
					camera->setTarget(lookat);					
				}
}
