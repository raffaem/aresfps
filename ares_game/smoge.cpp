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
#include "smoke.hpp"
#include "evar.hpp"
using namespace irr;

void IniSmoke() {
	smoke_campFire = smgr->addParticleSystemSceneNode(false, 0, -1, 
		core::vector3df(100,120,600), core::vector3df(0,0,0),
		core::vector3df(2,2,2));
	smoke_campFire->setParticleSize(core::dimension2d<f32>(20.0f, 10.0f));
	scene::IParticleAffector* paf = smoke_campFire->createFadeOutParticleAffector();
	smoke_campFire->addAffector(paf);
	paf->drop();
	smoke_campFire->setMaterialFlag(video::EMF_LIGHTING, false);
	smoke_campFire->setMaterialTexture(0, driver->getTexture("media\\texture\\particle.bmp"));
	smoke_campFire->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
}


void ImpactsPushBack(SParticleImpact c) {
	smoke_Impacts.push_back(c);
}
