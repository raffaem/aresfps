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
#ifndef MANCUSO_RAFFAELE_ARES_LEVEL_EDITOR_USER_SKY_BOX_2158487949874562410687064
#define MANCUSO_RAFFAELE_ARES_LEVEL_EDITOR_USER_SKY_BOX_2158487949874562410687064

//10-25 riservati user sky box
enum USER_SKY_BOX_ELEMENT{
	//BUTTONS
	TOP_BUTTON=10,
	BOTTOM_BUTTON,
	LEFT_BUTTON,
	RIGHT_BUTTON,
	FRONT_BUTTON,
	BACK_BUTTON,
	OK_BUTTON,
	CANCEL_BUTTON,
	//EDIT BOXES
	TOP_TEXT,
	BOTTOM_TEXT,
	LEFT_TEXT,
	RIGHT_TEXT,
	FRONT_TEXT,
	BACK_TEXT,
};

#include <irrlicht.h>
class user_sky_box_event_receiver_class:public irr::IEventReceiver{
public:
	virtual bool OnEvent(irr::SEvent event);
};

class sky_box_window_element_class{
public:
	irr::gui::IGUIEditBox* top_text,*bottom_text,*left_text,*right_text,*front_text,*back_text;
	void set(
		irr::gui::IGUIEditBox* TOP_TEXT,
		irr::gui::IGUIEditBox* BOTTOM_TEXT,
		irr::gui::IGUIEditBox* LEFT_TEXT,
		irr::gui::IGUIEditBox* RIGHT_TEXT,
		irr::gui::IGUIEditBox* FRONT_TEXT,
		irr::gui::IGUIEditBox* BACK_TEXT) {

			this->top_text=TOP_TEXT;
			this->bottom_text=BOTTOM_TEXT;
			this->left_text=LEFT_TEXT;
			this->right_text=RIGHT_TEXT;
			this->front_text=FRONT_TEXT;
			this->back_text=BACK_TEXT;
	}
};

void ShowUserSkyBox();
#endif