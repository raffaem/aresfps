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
#include "func.hpp"
//#include "add.hpp"
#include "event.hpp"

bool moveactive=false;
bool MyEventReceiver::OnEvent(SEvent irrevent) {
	//GUIManager(irrevent,GUI);
	camera->OnEvent(irrevent);
	if(irrevent.EventType==EET_KEY_INPUT_EVENT)  {

		if(irrevent.KeyInput.PressedDown==false) {

			//esce
			if(irrevent.KeyInput.Key==KEY_ESCAPE) {
				exit(0);		
			}

			//cambia modalità fps\modalità non fps
			
			else if(irrevent.KeyInput.Key==irr::KEY_SHIFT) {
				ChangeFPSCam();
			}
			

			//select a node
			else if(irrevent.KeyInput.Key==KEY_KEY_S) {
				//TO ACTIVE
				IsRotable(false);

				if(selectnode!=NULL) {
					selectnode->setDebugDataVisible(false);
				}

				selectnode=smgr->getSceneCollisionManager()->getSceneNodeFromCameraBB(camera);
				SelectANode();				
			}//else if(irrevent.KeyInput.Key==KEY_KEY_S) {

			//unselect a node
			else if(irrevent.KeyInput.Key==KEY_KEY_U)
				UnselectANode();
	
			//active/deactive diffuse light
			else if(irrevent.KeyInput.Key==KEY_KEY_D) {
				dl=!dl;
				DiffuseLight();
			}
						
			//move selected node
			else if(irrevent.KeyInput.Key==KEY_KEY_O) {
				if(selectnode!=NULL) {
					selectnode->setPosition(camera->getPosition());
					raf::NewRotationY(selectnode,camera->getRotation().Y);
					MoveANode();	
				}//if(selectnode!=NULL) {
			}//else if(irrevent.KeyInput.Key==KEY_KEY_O) {

			//erase select node
			else if(irrevent.KeyInput.Key==KEY_KEY_R)
				EraseANode();

			//move a node
			else if(irrevent.KeyInput.Key==KEY_CONTROL)
				moveactive=false;
			}//presseddown==false

			else {//if presseddown==true
				if(irrevent.KeyInput.Key==KEY_CONTROL)
					moveactive=true;
			}//else presseddown==true

	}//if irrevent.EventType==keyinput
	if(irrevent.EventType==EET_MOUSE_INPUT_EVENT) {

		if(irrevent.MouseInput.Event==EMIE_RMOUSE_PRESSED_DOWN) {

			//TO ACTIVE
			IsRotable(false);

			if(selectnode!=NULL) {
				selectnode->setDebugDataVisible(false);
			}

			selectnode=smgr->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(device->getCursorControl()->getPosition());
			SelectANode();	
		}//if(irrevent.MouseInput.Event==irr::EMIE_RMOUSE_PRESSED_DOWN) {

		else if(irrevent.MouseInput.Event==EMIE_MMOUSE_PRESSED_DOWN)
			moveactive=true;
		else if(irrevent.MouseInput.Event==EMIE_MMOUSE_LEFT_UP)
			moveactive=false;
	}//if(irrevent.EventType==EET_MOUSE_INPUT_EVENT) {

	if(moveactive==true) {
		if(selectnode!=NULL) {
			selectnode->setPosition(raf::GetPointInFrontOfCamera());
			MoveANode();
		}
	}
	//con return true la GUI non funziona correttamente
	return true;
}