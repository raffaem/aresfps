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
//LIBRERIE
#include <irrlicht.h>
#include <string>
#include <windows.h>
#include "func.hpp"
#include "..\\ares_runtime\\raf.hpp"
#include "classi.hpp"
#include "irrlicht class.hpp"
#include "script.hpp"
using namespace irr;
using namespace std;
//VARIABILI GLOBALI
#include "evar.hpp"
//CLASSI
bool MyEventReceiver::OnEvent(SEvent event) {
	camera->OnEvent(event);
	anim_weapon=0;
	if(event.EventType == EET_KEY_INPUT_EVENT) {
		if(event.KeyInput.PressedDown == true) {

			if(event.KeyInput.Key==KEY_CONTROL&&chinato==false) {
				chinato=true;
				ChangeWeaponCollision(true);
			}

			if(event.KeyInput.Key==KEY_UP)
				cammina_avanti=true;
			else if(event.KeyInput.Key==KEY_DOWN)
				cammina_indietro=true;	
			else if(event.KeyInput.Key==KEY_LEFT)
				cammina_sinistra=true;
			else if(event.KeyInput.Key==KEY_RIGHT)
				cammina_destra=true;	

			else if (event.KeyInput.Key==KEY_ESCAPE)  {
				//exit(0);
				device->closeDevice();
			} 
			else if(event.KeyInput.Key==irr::KEY_END) {
				core::vector3df rot=weapon->actual_weapon->ogg->getRotation();
				rot.X=0;
				weapon->actual_weapon->ogg->setRotation(rot);
			}
				
			else if(event.KeyInput.Key==KEY_KEY_A) {
				CaptureTheCurrentScreen();
			}
		}//	if(event.KeyInput.PressedDown == true)
		else  {//se un tasto è stato rilasciato
			if(event.KeyInput.Key==KEY_CONTROL&&chinato==true) {
				chinato=false;

				weapon->actual_weapon->ogg->MuoviY(return_yradius/2);
				ChangeWeaponCollision(); 
			}

			if(event.KeyInput.Key==KEY_KEY_M)
				mirino_bool=!mirino_bool;

			if(event.KeyInput.Key==KEY_UP)
				cammina_avanti=false;
			else if(event.KeyInput.Key==KEY_DOWN)
				cammina_indietro=false;
			else if(event.KeyInput.Key==KEY_LEFT)
				cammina_sinistra=false;
			else if(event.KeyInput.Key==KEY_RIGHT)
				cammina_destra=false;
			
			//guns
			else if(event.KeyInput.Key == KEY_KEY_1)
				weapon->ChangeWeapon(PUNCH_GUN);
			else if(event.KeyInput.Key == KEY_KEY_2)
				weapon->ChangeWeapon(SHOT_GUN);
			else if(event.KeyInput.Key == KEY_KEY_3)
				weapon->ChangeWeapon(MACHINE_GUN);
			else if(event.KeyInput.Key == KEY_KEY_4)
				weapon->ChangeWeapon(RIFLE_GUN);
			//end of guns
	
		}//else
	}//	if(event.EventType == EET_KEY_INPUT_EVENT) {
	//fine per la tastiera
	//inizio mouse
	else if(event.EventType == EET_MOUSE_INPUT_EVENT) {
		if(event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)
		{
		 spara_bool=true;				
		} 
		
		else if(event.MouseInput.Event == EMIE_LMOUSE_LEFT_UP) {
			sound.Stop(sound.sparo_di_mitragliatrice);
			spara_bool=false;
		}

		else if (event.MouseInput.Event==EMIE_RMOUSE_PRESSED_DOWN)
			event_receiver_jump=true;
	
		else if (event.MouseInput.Event==EMIE_RMOUSE_LEFT_UP)
			event_receiver_jump=false;
		
		else if (event.MouseInput.Event==EMIE_MOUSE_MOVED)  {
			core::position2d<s32> point=cursor_control->getPosition();
			weapon->actual_weapon->ogg->RuotaY((point.X-centro_x)*0.5);
			weapon->actual_weapon->ogg->RuotaX((point.Y-centro_y)*0.5);

			//per evitare che weapon->actual_weapon->ogg si metta al contrario
			f32 rotx=weapon->actual_weapon->ogg->getRotation().X;
			if(rotx<185&&rotx>89) {
				weapon->actual_weapon->ogg->NewRotationX(89);
			}
			if(rotx>186&&rotx<271) {
				weapon->actual_weapon->ogg->NewRotationX(271);
			}
			//fine
		}

		else if(event.MouseInput.Event==EMIE_MOUSE_WHEEL) {
			short type=weapon->actual_weapon->type;
			char sign=raf::sign(event.MouseInput.Wheel);
			if(sign=='+') type+=1;
			else if(sign=='-') type-=1;
			if(type>max_weapon_type_value)	type=1;
			else if(type<1) type=max_weapon_type_value;
			weapon->ChangeWeapon(type);
		}	
	}//	if(event.EventType == EET_MOUSE_INPUT_EVENT) {
	if(spara_bool==true) {Shoot();}

	int copy_weapon_animation=anim_weapon;
	if(anim_weapon==2)
		WeaponAnimation(2);

	//to jump
	if(event_receiver_jump) {
	if(!gravityanim->isFalling()) {
		now_jumping=true;
		ChangeWeaponCollision(false,true);
		sound.Play(sound.me_jump);
	}
	}
	//end

	move_speed=weapon_speed_for_millisecond*(device->getTimer()->getTime()-last_time);
	//if yump make the weapon more slow
	if(now_jumping)
		move_speed/=2;

	//per farlo camminare
	if(cammina_avanti==true) {
		anim_weapon=1;
		weapon->actual_weapon->ogg->Cammina(move_speed,'u');
		sound.Play(sound.passi);
	}
	if(cammina_indietro==true) {
		anim_weapon=1;
		weapon->actual_weapon->ogg->Cammina(move_speed,'d');
		sound.Play(sound.passi);
	}
	if(cammina_sinistra==true) {
		anim_weapon=1;
		weapon->actual_weapon->ogg->Cammina(move_speed,'l');
		//camera->setPosition(core::vector3df(-0.5,0,-4.8));
		sound.Play(sound.passi);
	}
	if(cammina_destra==true) {
		anim_weapon=1;
		weapon->actual_weapon->ogg->Cammina(move_speed,'r');
		//camera->setPosition(core::vector3df(0.5,0,-4.8));
		sound.Play(sound.passi);
	}

	/*
	if(!cammina_destra&&!cammina_sinistra&&!cammina_avanti&&!cammina_indietro){
		camera->setPosition(core::vector3df(0,0,-4.8));
	}
	*/

	//update phisics
	/*
	weapon->actual_weapon->ogg->updateAbsolutePosition();
	weapon->actual_weapon->p_node->SetPosition(weapon->actual_weapon->ogg->getPosition());
	weapon->actual_weapon->p_node->SetRotation(weapon->actual_weapon->ogg->getRotation());
	*/

	if(anim_weapon!=1) {
		sound.Stop(sound.passi);
	}

	if(copy_weapon_animation!=2) 
		WeaponAnimation(anim_weapon);
	return true;
}//di onevent

//---------------------------YOU LOSE EVENT RECEIVER------------
bool YouLoseEventReceiver::OnEvent(irr::SEvent event) {
	if(event.EventType == EET_KEY_INPUT_EVENT&&
		event.KeyInput.PressedDown == true&&
		event.KeyInput.Key==KEY_ESCAPE) {
			exit(0);
		}
	if(event.EventType == EET_KEY_INPUT_EVENT&&
		event.KeyInput.PressedDown == true&&
		event.KeyInput.Key==KEY_RETURN) {
			Restart();
		}
	return true;
}