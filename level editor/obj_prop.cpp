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
gui::IGUIEditBox* y_edit_box;
gui::IGUIEditBox* x_edit_box;
gui::IGUIWindow* obj_prop_win;
gui::IGUIButton* ok_button;
class obj_prop_event_receiver_class:public IEventReceiver{
public:
	virtual bool OnEvent(SEvent event) {
		if(event.EventType==EET_GUI_EVENT) {
			if(event.GUIEvent.EventType==gui::EGET_BUTTON_CLICKED) {
				if(event.GUIEvent.Caller->getID()==101) {
					string x_scale_string=raf::conv::WChar_tString(x_edit_box->getText());
					string y_scale_string=raf::conv::WChar_tString(y_edit_box->getText());

					float x_scale=atof(x_scale_string.c_str());
					float y_scale=atof(y_scale_string.c_str());
					
					scene::ITerrainSceneNode* select_terrain_node=(scene::ITerrainSceneNode*)selectnode;
					select_terrain_node->scaleTexture(x_scale,y_scale);

					//memorizza le impostazioni salvate
					string ID=raf::conv::NumString(selectnode->getID());
					ID.erase(0,1);
					int pos=atoi(ID.c_str());
					terrain_nodes[pos]->scale1=x_scale;
					terrain_nodes[pos]->scale2=y_scale;

					obj_prop_win->remove();
					device->setEventReceiver(&env);	
				}//if(event.GUIEvent.Caller->getID()==101) {
			}//if(event.GUIEvent.EventType==gui::EGET_BUTTON_CLICKED) {
		}//if(event.EventType=EET_GUI_EVENT) {
		return false;
	}//virtual bool OnEvent(SEvent event) {
}obj_prop_event_receiver;
void ShowTerrainProp() {
	obj_prop_win=GUI->addWindow(core::rect<s32>(257,216,800,700),true,L"Terrain node propietaries");
	obj_prop_win->getCloseButton()->remove();
	
	ok_button=GUI->addButton(core::rect<s32>(288, 248, 360, 272), obj_prop_win, 101, L"Ok");
	y_edit_box=GUI->addEditBox(L"0", core::rect<s32>(280, 216, 380, 236), true, obj_prop_win, 102);
	x_edit_box=GUI->addEditBox(L"1", core::rect<s32>(280, 184, 380, 204), true, obj_prop_win, 103);
	GUI->addStaticText(L"Y", core::rect<s32>(256, 216, 271, 236), false, false, obj_prop_win, 104);
	GUI->addStaticText(L"X", core::rect<s32>(256, 184, 271, 204), false, false, obj_prop_win, 105);
	GUI->addStaticText(L"Scale texture", core::rect<s32>(256, 152, 376, 172), false, false, obj_prop_win, 106);

	//posizione nel vettore
	string ID=raf::conv::NumString(selectnode->getID());
	ID.erase(0,1);
	int pos=atoi(ID.c_str());
	x_edit_box->setText(raf::conv::NumWChar_t(terrain_nodes[pos]->scale1));
	y_edit_box->setText(raf::conv::NumWChar_t(terrain_nodes[pos]->scale2));

	device->setEventReceiver(&obj_prop_event_receiver);	
}

//-------LIGHT PROPIETARIES----------------------------------
gui::IGUIEditBox* light_ray;
class light_prop_event_receiver_class:public IEventReceiver{
public:
	virtual bool OnEvent(SEvent event) {
		if(event.EventType==EET_GUI_EVENT) {
			if(event.GUIEvent.EventType==gui::EGET_BUTTON_CLICKED) {
				if(event.GUIEvent.Caller->getID()==101) {
					//get new light ray
					const wchar_t* light_ray_w=light_ray->getText();
					string light_ray_string=raf::conv::WChar_tString(light_ray_w);
					float light_ray=atof(light_ray_string.c_str());

					//recreate the light
					core::vector3df pos=selectnode->getPosition();
					EraseANode();
					loader_execute=true;
					int vector_pos=AddLight(pos,light_ray);
					loader_execute=false;

					//select the light
					selectnode=lights[vector_pos]->light;
					SelectANode();

					obj_prop_win->remove();
					device->setEventReceiver(&env);	
				}//if(event.GUIEvent.Caller->getID()==101) {
			}//if(event.GUIEvent.EventType==gui::EGET_BUTTON_CLICKED) {
		}//if(event.EventType=EET_GUI_EVENT) {
		return false;
	}//virtual bool OnEvent(SEvent event) {
}light_prop_event_receiver;

void ShowLightProp() {
	obj_prop_win=GUI->addWindow(core::rect<s32>(161,192,315,270),true,L"Light propietaries");
	obj_prop_win->getCloseButton()->remove();

	light_ray=GUI->addEditBox(L"", core::rect<s32>(64, 24, 134, 44), true, obj_prop_win, -1);
	GUI->addStaticText(L"Light ray:", core::rect<s32>(8, 24, 58, 44), false, false, obj_prop_win, -1);
	GUI->addButton(core::rect<s32>(40, 48, 80, 72), obj_prop_win, 101, L"Ok");	//set light ray
	
	string ID=raf::conv::NumString(selectnode->getID());
	ID.erase(0,1);
	int pos=atoi(ID.c_str());
	wchar_t* light_ray_w=raf::conv::NumWChar_t(lights[pos]->ray);
	light_ray->setText(light_ray_w);
	delete light_ray_w;	

	device->setEventReceiver(&light_prop_event_receiver);
}