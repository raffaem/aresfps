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
#include "evar.hpp"

void CreateGUI(gui::IGUIEnvironment*& mygui)
{
	//position,rotation and scale text
	GUI->addStaticText(L"Scale z",core::rect<s32>(648, 384, 688, 404), true, true, 0, -1,true);
	GUI->addStaticText(L"Scale y", core::rect<s32>(648, 344, 688, 364), true, true, 0, -1,true);
	GUI->addStaticText(L"Scale x", core::rect<s32>(648, 304, 688, 324), true, true, 0, -1,true);
	GUI->addStaticText(L"Rotation z", core::rect<s32>(640, 264, 700, 284), true, true, 0, -1,true);
	GUI->addStaticText(L"Rotation y", core::rect<s32>(640, 224, 700, 244), true, true, 0, -1,true);
	GUI->addStaticText(L"Rotation x", core::rect<s32>(640, 184, 700, 204), true, true, 0, -1,true);
	GUI->addStaticText(L"Position z", core::rect<s32>(640, 144, 698, 164), true, true, 0, -1,true);
	GUI->addStaticText(L"Position y", core::rect<s32>(640, 104, 698, 124), true, true, 0, -1,true);
	GUI->addStaticText(L"Position x", core::rect<s32>(640, 64,  698,  84), true, true, 0, -1,true);
	//create edit box
	scale_z=GUI->addEditBox(L"", core::rect<s32>(704, 384, 754, 404), true, 0, element::SCALE_Z);
	scale_y=GUI->addEditBox(L"",core::rect<s32>(704, 344, 754, 364), true, 0, element::SCALE_Y);
	scale_x=GUI->addEditBox(L"", core::rect<s32>(704, 304, 754, 324), true, 0, element::SCALE_X);
	rot_z=GUI->addEditBox(L"", core::rect<s32>(704, 264, 754, 284), true, 0, element::ROT_Z);
	rot_y=GUI->addEditBox(L"", core::rect<s32>(704, 224, 754, 244), true, 0, element::ROT_Y);
	rot_x=GUI->addEditBox(L"", core::rect<s32>(704, 184, 754, 204), true, 0, element::ROT_X);
	pos_z=GUI->addEditBox(L"", core::rect<s32>(704, 144, 754, 164), true, 0, element::POS_Z);
	pos_y=GUI->addEditBox(L"", core::rect<s32>(704, 104, 754, 124), true, 0, element::POS_Y);
	pos_x=GUI->addEditBox(L"", core::rect<s32>(704, 64, 754, 84), true, 0, element::POS_X);

	//MENU
	mymenu=mygui->addMenu(0);
	//aggiunge il menu file
	s32 file_menu_index=mymenu->addItem(L"File",-1,true,true);	
	s32 insert_menu_index=mymenu->addItem(L"Insert",-1,true,true);
	s32 object_menu_index=mymenu->addItem(L"Object",-1,true,true);	
	s32 world_menu_index=mymenu->addItem(L"World",-1,true,true);
	s32 camera_menu_index=mymenu->addItem(L"Camera",-1,true,true);
	s32 help_menu_index=mymenu->addItem(L"?",-1,true,true);	
	
	//get menu indexs
	file_menu=mymenu->getSubMenu(file_menu_index);
	help_menu=mymenu->getSubMenu(help_menu_index);
	insert_menu=mymenu->getSubMenu(insert_menu_index);
	world_menu=mymenu->getSubMenu(world_menu_index);
	camera_menu=mymenu->getSubMenu(camera_menu_index);
	object_menu=mymenu->getSubMenu(object_menu_index);

	//sub menu
	s32 monster_menu_index=insert_menu->addItem(L"Monster",-1,true,true);
	insert_monster_menu=insert_menu->getSubMenu(monster_menu_index);

	//crea gli oggetti del menu file
	file_menu->addItem(L"New",menu::FILE_NEW);
	file_menu->addItem(L"Load",menu::FILE_OPEN);
	file_menu->addItem(L"Save",menu::FILE_SAVE);
	file_menu->addItem(L"View code",menu::FILE_VIEW);
	file_menu->addItem(L"Reload",menu::FILE_RELOAD);
	file_menu->addItem(L"Exit",menu::FILE_EXIT);


	//crea gli oggetti del menu help
	help_menu->addItem(L"Help",menu::HELP_HELP);

	//crea gli oggetti del menu insert
	insert_menu->addItem(L"Model",menu::INSERT_MODEL);
	insert_menu->addItem(L"Medikit",menu::INSERT_MEDIKIT);
	insert_menu->addItem(L"Ammunation",menu::INSERT_AMMUNATION);
	insert_menu->addItem(L"Light",menu::INSERT_LIGHT);
	insert_menu->addItem(L"Terrain",menu::INSERT_TERRAIN);

	//crea gli oggetti del menu world
	world_menu->addItem(L"Add default sky box",menu::WORLD_ADD_DEFAULT_SKY_BOX);
	world_menu->addItem(L"User sky box",menu::WORLD_USER_SKY_BOX);
	world_menu->addItem(L"Remove sky box",menu::WORLD_REMOVE_SKY_BOX);

	if(dl==true)
		world_menu->addItem(L"Deactive diffuse light",menu::WORLD_ACTIVE_DEACTIVE_DIFFUSE_LIGHT);
	else
		world_menu->addItem(L"Active diffuse light",menu::WORLD_ACTIVE_DEACTIVE_DIFFUSE_LIGHT);

	//crea gli oggetti del menu camera
	camera_menu->addItem(L"Up",menu::CAMERA_UP);
	camera_menu->addItem(L"Set camera position as weapon position",menu::CAMERA_POS_AS_WEAPON);

	//crea gli oggetti del menu object
	object_menu->addItem(L"Select",menu::OBJECT_SELECT);
	object_menu->addItem(L"Unselect (U key)",menu::OBJECT_UNSELECT);
	object_menu->addItem(L"Move",menu::OBJECT_MOVE);
	object_menu->addItem(L"Erase (R key)",menu::OBJECT_ERASE);
	object_menu->addItem(L"Propietaries",menu::OBJECT_PROPIETARIES);

	//insert_monster
	insert_monster_menu->addItem(L"Falgat",menu::INSERT_MONSTER_FALGAT);
	insert_monster_menu->addItem(L"Rhino",menu::INSERT_MONSTER_RHINO);
}
void GUIManager(SEvent& irrevent,gui::IGUIEnvironment* mygui) {
	//GUI EVENT
	if (irrevent.EventType == EET_GUI_EVENT)
    {
    	s32 id = irrevent.GUIEvent.Caller->getID();
		switch(irrevent.GUIEvent.EventType)
    	{
    	//menu events
		case gui::EGET_MENU_ITEM_SELECTED:
			id=file_menu->getSelectedItem();
			if(id!=-1) {
				if(id==menu::FILE_NEW)
					ClearLevel();
				else if(id==menu::FILE_OPEN)
					Load();
				else if(id==menu::FILE_SAVE)
					Save();
				else if(id==menu::FILE_VIEW) {
					bool save=raf::AddYesNoMessagebox("Do you want to save your file?\n WARNING: If you save the file, you see the lines of this level, if you don't save the file, you see the lines of the loaded file, comprehensive of corrupt or wrong line that are unloaded. If you don't load any file and you say no (don't save the file), you see a white screen","Question");
					if(save)
						Save();

					string command="call %windir%\\notepad.exe "+actual_file;
					system(command.c_str());
				}
				else if(id==menu::FILE_RELOAD) {
					ClearLevel();
					Load(actual_file);
				}
				else if(id==menu::FILE_EXIT) 
					Exit(true);
			//end of case
				break;
			}
			id=help_menu->getSelectedItem();
			if(id!=-1) {
				if(id==menu::HELP_HELP) {
					GUI->addMessageBox(L"Ares level editor help",
						L"TASTO                            OPERAZIONE\n"
						L"SHIFT                              passa dalla modalità FPS alla modalità non-FPS e viceversa\n"
						L"E                                  aggiunge un nemico (oppure fai clic sul pulsante add falgat)\n"
						L"M                                  aggiunge un medikit (oppure fai clic sul pulsante add medikit)\n"
						L"L                                  aggiunge una luce\n"
						L"V                                  aggiunge un nuovo modello di livello (oppure fai clic sul pulsante add model)\n"
						L"S                                  seleziona un oggetto (oppure punta sull'oggeto e fai clic con il tasto destro del mouse in modalità non-fps)\n"
						L"U                                  deseleziona un oggetto\n"
						L"O                                  muove l'oggetto selezionato\n"
						L"R                                  elimina l'oggetto selezionato\n"
						L"D                                  attiva\disattiva l'illuminazione diffusa\n"
						L"ESC                                esce (oppure fai clic su file->exit)\n"
						L"file->new                          crea un nuovo livello \n"
						L"file->load                         carica un livello precedentemente salvato\n"
						L"file->save                         salva il livello \n"
						L"Per maggiori informazione vedi la guida (start->programmi->ares->readme) nelle sezioni \"level editor\" e \"livelli aggiuntivi\"\n"
						);
				}
				break;
			}//id!=-1

			//insert_monster
			id=insert_monster_menu->getSelectedItem();
			if(id!=-1) {
				if(id==menu::INSERT_MONSTER_FALGAT) {
					AddFalgat(camera->getPosition(),core::vector3df(0,0,0));
				}
				else if(id==menu::INSERT_MONSTER_RHINO) {
					AddRhino(camera->getPosition(),core::vector3df(0,0,0));
				}
			}

			id=insert_menu->getSelectedItem();
			if(id!=-1) {
				if(id==menu::INSERT_MODEL) {
					string modello,texture;
					LoadMap(modello,texture);
					AddLevelModel(modello,texture,camera->getPosition(),core::vector3df(0,0,0),core::vector3df(1,1,1));
				}
				else if(id==menu::INSERT_MEDIKIT) {
					AddMedikit(camera->getPosition(),core::vector3df(0,camera->getRotation().Y,0));
				}
				else if(id==menu::INSERT_AMMUNATION) {
					AddAmmunation(camera->getPosition(),core::vector3df(0,camera->getRotation().Y,0));
				}
				else if(id==menu::INSERT_LIGHT) {
					AddLight(camera->getPosition());
				}
				else if(id==menu::INSERT_TERRAIN) {
					string heightmap=raf::AddFileOpenDialog(L"Select a heightmap");
					if(heightmap=="") {return;}
					string texture=raf::AddFileOpenDialog(L"Select a texture");
					if(texture=="") {AddTerrain(heightmap,texture,"");}
					string detail_texture=raf::AddFileOpenDialog(L"Select detail texture");
					AddTerrain(heightmap,texture,detail_texture);
				}

			}
			
			//world menu events
			id=world_menu->getSelectedItem();
			if(id!=-1) {
				if(id==menu::WORLD_USER_SKY_BOX) {
					ShowUserSkyBox();
				}
				else if(id==menu::WORLD_ADD_DEFAULT_SKY_BOX) {
					AddDefaultSkyBox();
				}
				else if(id==menu::WORLD_REMOVE_SKY_BOX) {
					if(skyboxNode!=NULL) {
						skyboxNode->remove();
						skyboxNode=NULL;
					}
				}//else if(id==menu::WORLD_REMOVE_SKY_BOX) {
				else if(id==menu::WORLD_ACTIVE_DEACTIVE_DIFFUSE_LIGHT) {
					dl=!dl;
					DiffuseLight();					
				}//else if(id==menu::WORLD_ACTIVE_DEACTIVE_DIFFUSE_LIGHT) {
			}//if(id!=-1) {
			//camera menu
			id=camera_menu->getSelectedItem();
			if(id!=-1) {
				if(id==menu::CAMERA_UP) {
					core::vector3df pos=camera->getPosition();
					core::vector3df rot=camera->getRotation();
					pos.Y=150;
					rot.X=90;
					camera->setPosition(pos);
					camera->setRotation(rot);
				}
				if(id==menu::CAMERA_POS_AS_WEAPON) 
					camera->setPosition(weapon->getPosition());
				}//if(id!=-1)

			id=object_menu->getSelectedItem();
			if(id!=-1) {
				if(id==menu::OBJECT_SELECT) {
					GUI->addMessageBox(L"Readme",L"1)Point with your mouse to the object you want to select\n2)Press right muose button");
				}
				if(id==menu::OBJECT_UNSELECT) {
					UnselectANode();
				}
				if(id==menu::OBJECT_MOVE) {
					string message="1)Select the object you want to move (see Object->select for more information)\n"
						"2)Point with your mouse to the point in wich you want to move the object\n"
						"3)Press middle mouse button or ctrl key\n\nOr:\n\n"
						"1)Select the object you want to move (see Object->select for more information)\n"
						"2)Press shift key or click on Camera->Active\\deactive FPS mode to switch into FPS mode\n"
						"3)Hold pressed middle mouse button or ctrl key while use the arrows key to move\n"
						"4)Press shift to switch off from FPS mode";
					wchar_t* message_w=raf::conv::CharWChar_T(message.c_str());
					GUI->addMessageBox(L"Readme",message_w);
					delete message_w;
				}
				if(id==menu::OBJECT_ERASE) {
					EraseANode();
				}
				if(id==menu::OBJECT_PROPIETARIES) {
					if(selectnode!=NULL) {
						if(obj_type==type::terrain) {
							ShowTerrainProp();
						}//if(obj_type==type::terrain) {
						else if(obj_type==type::light) {
							ShowLightProp();
						}//if(obj_type==type::terrain) {
						else
							raf::errore("No propietaries for selected object");
					}//if(selectnode!=NULL) {
					else
						raf::errore("No selected object. See object->Select");
				}//if(id==menu::OBJECT_PROPIETARIES) {
			}//if(id!=-1) {
			break;
			case gui::EGET_EDITBOX_ENTER:
				if(selectnode!=NULL) {
					float posx=raf::conv::WChar_tFloat(pos_x->getText());
					float posy=raf::conv::WChar_tFloat(pos_y->getText());
					float posz=raf::conv::WChar_tFloat(pos_z->getText());
					float rotx=raf::conv::WChar_tFloat(rot_x->getText());
					float roty=raf::conv::WChar_tFloat(rot_y->getText());
					float rotz=raf::conv::WChar_tFloat(rot_z->getText());
					float scalex=raf::conv::WChar_tFloat(scale_x->getText());
					float scaley=raf::conv::WChar_tFloat(scale_y->getText());
					float scalez=raf::conv::WChar_tFloat(scale_z->getText());

					selectnode->setPosition(core::vector3df(
						posx,
						posy,
						posz
						));
					selectnode->setRotation(core::vector3df(
						rotx,
						roty,
						rotz
						));
					selectnode->setScale(core::vector3df(
						scalex,
						scaley,
						scalez
						));
				}//if(selectnode!=NULL) {
				break;
		}//switch
	}//if (irrevent.EventType == EET_GUI_EVENT)
}//function
