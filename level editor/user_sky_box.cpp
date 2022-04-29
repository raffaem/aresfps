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
#include "user_sky_box.hpp"
#include "evar.hpp"

gui::IGUIWindow* sky_box_windows;
gui::IGUIFileOpenDialog* t=NULL;
gui::IGUIEditBox* selected_browse_edit_box;

bool user_sky_box_event_receiver_class::OnEvent(SEvent event) {
	if(event.EventType==irr::EET_GUI_EVENT) {
		if(event.GUIEvent.EventType==gui::EGET_BUTTON_CLICKED) {
			s32 id=event.GUIEvent.Caller->getID();
			if(id==TOP_BUTTON) {
				t=GUI->addFileOpenDialog(L"Top texture for sky box");
				selected_browse_edit_box=sky_box_window_element.top_text;
			}
			else if(id==BOTTOM_BUTTON) {
				t=GUI->addFileOpenDialog(L"Bottom texture for sky box");
				selected_browse_edit_box=sky_box_window_element.bottom_text;
			}
			else if(id==LEFT_BUTTON) {
				t=GUI->addFileOpenDialog(L"Left texture for sky box");
				selected_browse_edit_box=sky_box_window_element.left_text;
			}
			else if(id==RIGHT_BUTTON) {
				t=GUI->addFileOpenDialog(L"Right texture for sky box");
				selected_browse_edit_box=sky_box_window_element.right_text;
			}
			else if(id==FRONT_BUTTON) {
				t=GUI->addFileOpenDialog(L"Front texture for sky box");
				selected_browse_edit_box=sky_box_window_element.front_text;
			}
			else if(id==BACK_BUTTON) {
				t=GUI->addFileOpenDialog(L"Back texture for sky box");
				selected_browse_edit_box=sky_box_window_element.back_text;
			}

			else if(id==OK_BUTTON) {
				//GET THE SELECTED TEXTURE
				const wchar_t* top=sky_box_window_element.top_text->getText();
				const wchar_t* bottom=sky_box_window_element.bottom_text->getText();
				const wchar_t* left=sky_box_window_element.left_text->getText();
				const wchar_t* right=sky_box_window_element.right_text->getText();
				const wchar_t* front=sky_box_window_element.front_text->getText();
				const wchar_t* back=sky_box_window_element.back_text->getText();

				//CONVERTING THE TEXTURES TO CHAR
				char* top_string=raf::conv::WChar_tChar(top);
				char* bottom_string=raf::conv::WChar_tChar(bottom);
				char* left_string=raf::conv::WChar_tChar(left);
				char* right_string=raf::conv::WChar_tChar(right);
				char* front_string=raf::conv::WChar_tChar(front);
				char* back_string=raf::conv::WChar_tChar(back);

				//CECK IF TEXTURES EXIST
				if(device->getFileSystem()->existFile(top_string)==false) {
					raf::errore("The top texture doesn't exist. Please select a texture that exist");
					return false;
				}
				if(device->getFileSystem()->existFile(bottom_string)==false) {
					raf::errore("The bottom texture doesn't exist. Please select a texture that exist");
					return false;
				}
				if(device->getFileSystem()->existFile(left_string)==false) {
					raf::errore("The left texture doesn't exist. Please select a texture that exist");
					return false;
				}
				if(device->getFileSystem()->existFile(right_string)==false) {
					raf::errore("The right texture doesn't exist. Please select a texture that exist");
					return false;
				}
				if(device->getFileSystem()->existFile(front_string)==false) {
					raf::errore("The front texture doesn't exist. Please select a texture that exist");
					return false;
				}
				if(device->getFileSystem()->existFile(back_string)==false) {
					raf::errore("The back texture doesn't exist. Please select a texture that exist");
					return false;
				}
				
				//GET THE TEXTURES
				video::ITexture* top_texture=driver->getTexture(top_string);
				video::ITexture* bottom_texture=driver->getTexture(bottom_string);
				video::ITexture* left_texture=driver->getTexture(left_string);
				video::ITexture* right_texture=driver->getTexture(right_string);
				video::ITexture* front_texture=driver->getTexture(front_string);
				video::ITexture* back_texture=driver->getTexture(back_string);

				//CECK IF THE TEXTURE WAS LOADED CORRECTLY
				if(top_texture==NULL) {
					raf::errore("The top texture isn't a texture or it is in an unsupported format. The supported format are BMP,JPG,TGA,PCX,PNG and PSD. Please select a valid texture and\\or a supported-format texture");
					return false;
				}
				if(bottom_texture==NULL) {
					raf::errore("The bottom texture isn't a texture or it is in an unsupported format. The supported format are BMP,JPG,TGA,PCX,PNG and PSD. Please select a valid texture and\\or a supported-format texture");
					return false;
				}
				if(left_texture==NULL) {
					raf::errore("The left texture isn't a texture or it is in an unsupported format. The supported format are BMP,JPG,TGA,PCX,PNG and PSD. Please select a valid texture and\\or a supported-format texture");
					return false;
				}
				if(right_texture==NULL) {
					raf::errore("The right texture isn't a texture or it is in an unsupported format. The supported format are BMP,JPG,TGA,PCX,PNG and PSD. Please select a valid texture and\\or a supported-format texture");
					return false;
				}
				if(front_texture==NULL) {
					raf::errore("The front texture isn't a texture or it is in an unsupported format. The supported format are BMP,JPG,TGA,PCX,PNG and PSD. Please select a valid texture and\\or a supported-format texture");
					return false;
				}
				if(back_texture==NULL) {
					raf::errore("The back texture isn't a texture or it is in an unsupported format. The supported format are BMP,JPG,TGA,PCX,PNG and PSD. Please select a valid texture and\\or a supported-format texture");
					return false;
				}
				
				//CREATE THE SKYBOX
				skyboxNode=smgr->addSkyBoxSceneNode(
					top_texture,
					bottom_texture,
					left_texture,
					right_texture,
					front_texture,
					back_texture
					);

				//COMPILE THE SKY_BOX OBJECT
				sky_box.top=top_string;
				sky_box.bottom=bottom_string;
				sky_box.left=left_string;
				sky_box.right=right_string;
				sky_box.front=front_string;
				sky_box.back=back_string;
								
				//DELETE THE STRINGS THAT RAPPRESENTS THE TEXTURE
				delete top_string;
				delete bottom_string;
				delete left_string;
				delete right_string;
				delete front_string;
				delete back_string;

				//DELETE THE WINDOW
				sky_box_windows->remove();

				//SET THE LEVEL EDITOR EVENT RECEIVER
				device->setEventReceiver(&env);
			}
			else if(id==CANCEL_BUTTON) {
				//DELETE THE WINDOW
				sky_box_windows->remove();

				//SET THE LEVEL EDITOR EVENT RECEIVER
				device->setEventReceiver(&env);
				return false;
			}
			//file selected
		}//if(event.GUIEvent.EventType==gui::EGET_BUTTON_CLICKED ) {

		if(event.GUIEvent.EventType==gui::EGET_FILE_SELECTED) {
			selected_browse_edit_box->setText(t->getFilename());
		}//if(event.GUIEvent.EventType==EGET_FILE_SELCTED) {

	}//if(event.EventType==irr::EET_GUI_EVENT) {	
	return false;
}//virtual bool OnEvent(SEvent event) {

void ShowUserSkyBox() {
	sky_box_windows=GUI->addWindow(core::rect<s32>(10, 1,400, 450),true,L"Sky box propietaries");
	sky_box_windows->getCloseButton()->remove();
	//create gui elements

	//STATIC TEXTS
	sky_box_windows->addChild(GUI->addStaticText(L"Back", core::rect<s32>(24, 327, 192, 355), false, false, 0, -1));
	sky_box_windows->addChild(GUI->addStaticText(L"Front", core::rect<s32>(24, 263, 192, 291), false, false, 0, -1));
	sky_box_windows->addChild(GUI->addStaticText(L"Right", core::rect<s32>(24, 199, 192, 227), false, false, 0, -1));
	sky_box_windows->addChild(GUI->addStaticText(L"Left", core::rect<s32>(24, 135, 192, 163), false, false, 0, -1));
	sky_box_windows->addChild(GUI->addStaticText(L"Bottom", core::rect<s32>(24, 71, 192, 99), false, false, 0, -1));
	sky_box_windows->addChild(GUI->addStaticText(L"Top", core::rect<s32>(24, 15, 192, 43), false, false, 0, -1));

	gui::IGUIEditBox* back_text=GUI->addEditBox(L"", core::rect<s32>(24, 359, 192, 387), true, 0, BACK_TEXT);
	sky_box_windows->addChild(back_text);

	gui::IGUIEditBox* front_text=GUI->addEditBox(L"", core::rect<s32>(24, 295, 192, 323), true, 0, FRONT_TEXT);
	sky_box_windows->addChild(front_text);

	sky_box_windows->addChild(GUI->addButton(core::rect<s32>(200, 359, 303, 391), 0, BACK_BUTTON, L"Browse"));
	sky_box_windows->addChild(GUI->addButton(core::rect<s32>(200, 295, 303, 327), 0, FRONT_BUTTON, L"Browse"));
	sky_box_windows->addChild(GUI->addButton(core::rect<s32>(200, 231, 303, 263), 0, RIGHT_BUTTON, L"Browse"));

	gui::IGUIEditBox* right_text=GUI->addEditBox(L"",core::rect<s32>(24, 231, 192, 259), true, 0, RIGHT_TEXT);
	sky_box_windows->addChild(right_text);

	sky_box_windows->addChild(GUI->addButton(core::rect<s32>(200, 167, 303, 199), 0, LEFT_BUTTON, L"Browse"));

	gui::IGUIEditBox* left_text=GUI->addEditBox(L"", core::rect<s32>(24, 167, 192, 195), true, 0, LEFT_TEXT);
	sky_box_windows->addChild(left_text);

	sky_box_windows->addChild(GUI->addButton(core::rect<s32>(200, 104, 303, 135), 0, BOTTOM_BUTTON, L"Browse"));

	gui::IGUIEditBox* bottom_text=GUI->addEditBox(L"", core::rect<s32>(24, 109, 192, 131), true, 0, BOTTOM_TEXT);
	sky_box_windows->addChild(bottom_text);

	sky_box_windows->addChild(GUI->addButton(core::rect<s32>(200, 39, 303, 71), 0, TOP_BUTTON, L"Browse"));

	gui::IGUIEditBox* top_text=GUI->addEditBox(L"", core::rect<s32>(24, 46, 192, 67), true, 0, TOP_TEXT);
	sky_box_windows->addChild(top_text);

	//ok e cancel button
	gui::IGUIButton* cancel_button=GUI->addButton(core::rect<s32>(154, 400, 234, 424), 0, CANCEL_BUTTON, L"Cancel");
	gui::IGUIButton* ok_button=GUI->addButton(core::rect<s32>(58, 400, 138, 424), 0, OK_BUTTON, L"Ok");
	sky_box_windows->addChild(cancel_button);
	sky_box_windows->addChild(ok_button);

	sky_box_window_element.set(
		top_text,
		bottom_text,
		left_text,
		right_text,
		front_text,
		back_text
		);

	//set new event receiver
	device->setEventReceiver(&user_sky_box_event_receiver);

	//create gui elements original
	//gui::IGUIButton* cancel_button=GUI->addButton(core::rect<s32>(114, 400, 194, 424), 0, CANCEL_BUTTON, L"Cancel");
	//gui::IGUIButton* ok_button=GUI->addButton(core::rect<s32>(18, 400, 98, 424), 0, OK_BUTTON, L"Ok");
	/*sky_box_windows->addChild(GUI->addStaticText(L"Back", core::rect<s32>(24, 320, 192, 340), false, false, 0, -1));
	sky_box_windows->addChild(GUI->addStaticText(L"Front", core::rect<s32>(24, 256, 192, 276), false, false, 0, -1));
	sky_box_windows->addChild(GUI->addStaticText(L"Right", core::rect<s32>(24, 192, 192, 212), false, false, 0, -1));
	sky_box_windows->addChild(GUI->addStaticText(L"Left", core::rect<s32>(24, 128, 192, 148), false, false, 0, -1));
	sky_box_windows->addChild(GUI->addStaticText(L"Bottom", core::rect<s32>(24, 64, 192, 84), false, false, 0, -1));
	sky_box_windows->addChild(GUI->addStaticText(L"Top", core::rect<s32>(24, 8, 192, 28), false, false, 0, -1));
	sky_box_windows->addChild(GUI->addEditBox(L"", core::rect<s32>(24, 352, 192, 372), true, 0, -1));
	sky_box_windows->addChild(GUI->addEditBox(L"", core::rect<s32>(24, 288, 192, 308), true, 0, -1));
	sky_box_windows->addChild(GUI->addButton(core::rect<s32>(200, 352, 296, 376), 0, -1, L"Browse"));
	sky_box_windows->addChild(GUI->addButton(core::rect<s32>(200, 288, 296, 312), 0, -1, L"Browse"));
	sky_box_windows->addChild(GUI->addButton(core::rect<s32>(200, 224, 296, 248), 0, -1, L"Browse"));
	sky_box_windows->addChild(GUI->addEditBox(L"",core::rect<s32>(24, 224, 192, 244), true, 0, -1));
	sky_box_windows->addChild(GUI->addButton(core::rect<s32>(200, 160, 296, 184), 0, -1, L"Browse"));
	sky_box_windows->addChild(GUI->addEditBox(L"", core::rect<s32>(24, 160, 192, 180), true, 0, -1));
	sky_box_windows->addChild(GUI->addButton(core::rect<s32>(200, 96, 296, 120), 0, -1, L"Browse"));
	sky_box_windows->addChild(GUI->addEditBox(L"", core::rect<s32>(24, 96, 192, 116), true, 0, -1));
	sky_box_windows->addChild(GUI->addButton(core::rect<s32>(200, 32, 296, 56), 0, -1, L"Browse"));
	sky_box_windows->addChild(GUI->addEditBox(L"", core::rect<s32>(24, 32, 192, 52), true, 0, -1));*/
}
