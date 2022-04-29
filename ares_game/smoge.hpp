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
#ifndef MANCUSO_RAFFAELE_ARES_SMOKE_HPP_5416874165434352
#define MANCUSO_RAFFAELE_ARES_SMOKE_HPP_5416874165434352
#pragma once

#include <irrlicht.h>
#include <windows.h>
#include "sound.hpp"

//extern variable
extern irr::IrrlichtDevice* device;
extern irr::scene::ISceneManager* smgr;
extern irr::video::IVideoDriver* driver;
extern game_sound sound;

struct SParticleImpact
{
	irr::u32 when;
	irr::core::vector3df pos;
	irr::core::vector3df outVector;
};
extern irr::scene::IParticleSystemSceneNode* smoke_campFire;
extern irr::core::array<SParticleImpact> smoke_Impacts;

void IniSmoke();
void ImpactsPushBack(SParticleImpact c);

inline void UseSmoke();

//-----------------------INLINE FUNCTION---------------------
inline void UseSmoke() {
	irr::u32 now = device->getTimer()->getTime();
	for (irr::s32 i=0; i<(irr::s32)smoke_Impacts.size(); ++i)
		if (now > smoke_Impacts[i].when)
		{
			// create smoke particle system
			irr::scene::IParticleSystemSceneNode* pas = 0;

			pas = smgr->addParticleSystemSceneNode(false,
				0,
				-1,
				smoke_Impacts[i].pos);

			pas->setParticleSize(irr::core::dimension2d<irr::f32>(10.0f, 10.0f));

			irr::scene::IParticleEmitter* em = pas->createBoxEmitter(
				irr::core::aabbox3d<irr::f32>(-5,-5,-5,5,5,5),
				smoke_Impacts[i].outVector,
				20,
				40,
				irr::video::SColor(0,255,255,255),
				irr::video::SColor(0,255,255,255),
				1200,
				1600,
				20);

			pas->setEmitter(em);
			em->drop();

			irr::scene::IParticleAffector* paf = smoke_campFire->createFadeOutParticleAffector();
			pas->addAffector(paf);
			paf->drop();

			pas->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			pas->setMaterialTexture(0, driver->getTexture("media\\texture\\smoke.bmp"));
			pas->setMaterialType(irr::video::EMT_TRANSPARENT_VERTEX_ALPHA);

			irr::scene::ISceneNodeAnimator* anim = smgr->createDeleteAnimator(2000);
			pas->addAnimator(anim);
			anim->drop();

			// delete entry
			smoke_Impacts.erase(i);
			i--;			

			// play impact sound
			sound.Play(sound.impactSound);
	}
}

#endif
