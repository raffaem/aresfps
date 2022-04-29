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
#ifndef RAFFAELE_MANCUSO_IRRLICHT_HELP_LIBRERY_VERSIONE_1_00_00_PHISICS_COD_123065849847958416216847984632016847984965130684984762056265065419820ASREADFASC
#define RAFFAELE_MANCUSO_IRRLICHT_HELP_LIBRERY_VERSIONE_1_00_00_PHISICS_COD_123065849847958416216847984632016847984965130684984762056265065419820ASREADFASC

#include <vector>
#include <irrlicht.h>
#include "dll_exports.hpp"
#include "newton.h"
#include "HiResTimer.h"
#include "dMatrix.h"
#include "dVector.h"
#include "dQuaternion.h"

#define NewtonToIrr   32.0
#define IrrToNewton  1/NewtonToIrr

namespace raf{
	namespace Newt{

		class SceneNode;
		class OctTreeSceneNode;
		
		class ARES_API World{
		public:
			World();
			~World();
			void Update(irr::IrrlichtDevice* device);
			raf::Newt::SceneNode*  AddSceneNode(irr::scene::ISceneNode* node,irr::scene::IMesh* iMeshBase);
			raf::Newt::OctTreeSceneNode*  AddOctTreeSceneNodeAsMap(irr::scene::ISceneNode* node,irr::scene::IAnimatedMesh* iMeshBase,bool the_model_have_lightmap=true);

			//attributes
			NewtonWorld* world;
			raf::Newt::CHiResTimer timer;
			std::vector<raf::Newt::SceneNode*> scene_nodes;
			std::vector<raf::Newt::SceneNode*> octtree_nodes;
			int group_material_ID;
		};//class ARES_API World{
		ARES_API raf::Newt::World* createPhisicsWorld();

		class ARES_API SceneNode {
		public:
			raf::Newt::SceneNode::SceneNode(raf::Newt::World* world,irr::scene::ISceneNode* node,irr::scene::IMesh* iMeshBase);
			SceneNode(){}
			~SceneNode();
			void Destroy();

			void SetPosition(irr::core::vector3df pos);
			void SetRotation(irr::core::vector3df rot);
			void SetScale(irr::core::vector3df scale);

			void PosRotScaleAsNode();

			void SetInertia(irr::core::vector3df inertia);
			irr::core::vector3df GetInertia();
			void AutoCalcInertia();

			void SetMass(float mass);
			float GetMass();

			void SetBoxSize(irr::core::vector3df new_box_size);
			inline irr::core::vector3df GetBoxSize() {
				return this->box_size;
			}
			
			void AddForce(irr::core::vector3df force);
			void AddGravityForce();
			void RotateAroundItself(irr::core::vector3df rot);

			void UpdateUserData();

			//attributes
			irr::core::vector3df gravity_force;
			raf::Newt::World* world;
			NewtonCollision* collision;
			NewtonBody* body;
			irr::scene::ISceneNode* node;
			irr::core::vector3df forces;
			std::vector<irr::core::vector3df> forces_to_cancel;
			irr::core::vector3df box_size;
			irr::core::matrix4 mat;

			//private functions
			//cannot insert private access at this function 'cause octtree scene node costructor
			static void __cdecl PhisicsSetForceAndTorqueEvent (const NewtonBody* body);
			static void __cdecl PhisicsSetTransformEvent(const NewtonBody* body, const float* matrix);
			void Create();
		private:
			void CalcBoxSize(irr::scene::IMesh* iMeshBase);
		};//class ARES_API SceneNode {

		class ARES_API OctTreeSceneNode:public raf::Newt::SceneNode {
		public:
			OctTreeSceneNode(raf::Newt::World* world,irr::scene::ISceneNode* node,irr::scene::IAnimatedMesh* iMeshBase,bool the_model_have_lightmap=true);
			~OctTreeSceneNode();
		};

	}//namespace Newt
}//namespace raf
//INLINE FUNCTIONS
#endif