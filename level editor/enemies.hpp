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
#ifndef MANCUSO_RAFFAELE_LEVEL_EDITOR_FOR_ARES_ENEMIES_HPP_168487498749846219084651068704
#define MANCUSO_RAFFAELE_LEVEL_EDITOR_FOR_ARES_ENEMIES_HPP_168487498749846219084651068704

#include <irrlicht.h>
using namespace irr;
#include <string>
#include "..\\ares_runtime\\raf.hpp"

enum ENEMIES_TYPE {
	ET_FALGAT,
	ET_RHINO,
	ET_ZOMBIE
};

class enemie_class{
public:
	float radius;
	ENEMIES_TYPE type;
	scene::ISceneNode* weapon;
};

namespace level_editor {
	class Enemies:public scene::IAnimatedMeshSceneNode{
	public:
		Enemies(scene::ISceneNode* parent, 
			scene::ISceneManager* mgr,
			s32 id,
			const core::vector3df& position = core::vector3df(0,0,0),
			const core::vector3df& rotation = core::vector3df(0,0,0),
			const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f))
			:scene::IAnimatedMeshSceneNode(parent,mgr,id,position,rotation,scale)
		{
				this->parameter=new enemie_class;
		}

		~Enemies() {
			delete this->parameter;
		}

		void SetEnemieType(ENEMIES_TYPE new_type) {
			this->parameter->type=new_type;
		}

		ENEMIES_TYPE GetEnemieType() {
			return this->parameter->type;
		}

		void SetAttachedWeapon(scene::ISceneNode* node) {
			this->parameter->weapon=node;
		}

		scene::ISceneNode* GetAttachedWeapon() {
			return this->parameter->weapon;
		}

		void SetRadius(float rad) {
			this->parameter->radius=rad;
		}

		float GetRadius() {
			return this->parameter->radius;
		}

		private:
		enemie_class* parameter;		
	};
}
#endif