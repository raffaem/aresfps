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
#include "Phisics.hpp"

using namespace irr;

//TO ERASE
#include "fstream"

//WORLD CLASS
raf::Newt::World::World() {
	this->world=NewtonCreate(NULL,NULL);
	this->group_material_ID=NewtonMaterialGetDefaultGroupID(this->world);
}
raf::Newt::World::~World() {
	NewtonDestroyAllBodies(this->world);
	NewtonDestroy(this->world);
	delete this;
}
void raf::Newt::World::Update(irr::IrrlichtDevice* device) {
	/*
	float fps = (float) device->getVideoDriver()->getFPS();
	if (fps > 0.0f) {
		NewtonUpdate(this->world, 1.0f / fps);
	}
	*/
	NewtonUpdate(this->world, this->timer.GetElapsedSeconds());
	//NewtonUpdate(this->world, 0.01);
}
raf::Newt::SceneNode*  raf::Newt::World::AddSceneNode(irr::scene::ISceneNode* node,irr::scene::IMesh* iMeshBase) {
	raf::Newt::SceneNode* p_node=new raf::Newt::SceneNode(this,node,iMeshBase); 
	this->scene_nodes.push_back(p_node);
	return p_node;
}
raf::Newt::OctTreeSceneNode*  raf::Newt::World::AddOctTreeSceneNodeAsMap(irr::scene::ISceneNode* node,irr::scene::IAnimatedMesh* iMeshBase,bool the_model_have_lightmap/*=true*/){
	raf::Newt::OctTreeSceneNode* oct_node=new raf::Newt::OctTreeSceneNode(this,node,iMeshBase,the_model_have_lightmap);
	octtree_nodes.push_back(oct_node);
	return oct_node;
}

//to create the world
raf::Newt::World* raf::Newt::createPhisicsWorld() {
	return new raf::Newt::World();
}
//------------------------------------------------------------------
//------------------------SCENE NODE CLASS--------------------------
//------------------------------------------------------------------
//PRIVATE FUNCTION
void __cdecl raf::Newt::SceneNode::PhisicsSetTransformEvent(const NewtonBody* body, const float* matrix) {
	NewtonBodySetMatrix(body,matrix);

	//set node position
	core::matrix4 irr_mat;
	memcpy(irr_mat.M, matrix, sizeof(float)*16);
	//adjust translation to set with irr
	irr_mat.setTranslation(irr_mat.getTranslation()*NewtonToIrr);
	raf::Newt::SceneNode* p_node=(raf::Newt::SceneNode*)NewtonBodyGetUserData(body);
	scene::ISceneNode* node=p_node->node;
	node->setPosition(irr_mat.getTranslation());
	node->setRotation(irr_mat.getRotationDegrees());	
}

void __cdecl raf::Newt::SceneNode::PhisicsSetForceAndTorqueEvent (const NewtonBody* body) 
{
	raf::Newt::SceneNode* p_node=(raf::Newt::SceneNode*)NewtonBodyGetUserData(body);
	raf::Newt::dVector f;
	f.m_x=p_node->forces.X;
	f.m_y=p_node->forces.Y;
	f.m_z=p_node->forces.Z;
	NewtonBodySetForce(body,&f.m_x);

	//cancel previous froce
	/*
	if(p_node->forces_to_cancel.size()>0) {
		p_node->forces-=p_node->forces_to_cancel[0];
		p_node->forces_to_cancel.erase(p_node->forces_to_cancel.begin());
	}
	*/
	return;	
}
void raf::Newt::SceneNode::Create() {
	this->collision=NewtonCreateBox(this->world->world,this->box_size.X,this->box_size.Y,this->box_size.Z,NULL);
	this->body=NewtonCreateBody(this->world->world,this->collision);
	NewtonBodySetUserData(this->body,this);
	NewtonReleaseCollision(this->world->world,this->collision);
	
	//set the same position of the node
	NewtonBodySetMatrix(this->body,&this->mat.M[0]);

	NewtonBodySetTransformCallback(this->body,this->PhisicsSetTransformEvent);
	NewtonBodySetForceAndTorqueCallback(this->body,this->PhisicsSetForceAndTorqueEvent);
	NewtonBodySetMaterialGroupID (this->body, this->world->group_material_ID);
	//NewtonBodySetLinearDamping(this->body,0);
	NewtonBodySetAutoFreeze(this->body, 0);
	NewtonWorldUnfreezeBody(this->world->world,this->body); 

	//set mass at a default value
	this->SetMass(1.0f);
	this->AutoCalcInertia();
	this->PosRotScaleAsNode();
}	
void raf::Newt::SceneNode::CalcBoxSize(irr::scene::IMesh* iMeshBase) {
	//calculate box size
	core::aabbox3d<f32> box=iMeshBase->getBoundingBox();
	//size the box in Newton units
	this->mat.setScale(node->getScale());
	this->mat.setTranslation(node->getPosition()*IrrToNewton);
	this->mat.setRotationDegrees(node->getRotation());
	this->mat.transformBoxEx(box);
	this->box_size = box.getExtent() * IrrToNewton;
	//end of calculate box size
}
//END OF PRIVATE FUNCTION

raf::Newt::SceneNode::SceneNode(raf::Newt::World* world,scene::ISceneNode* node,scene::IMesh* iMeshBase) {
	this->world=world;
	this->node=node;
	this->CalcBoxSize(iMeshBase);
	this->Create();
}

//destructor
void raf::Newt::SceneNode::Destroy() {
	if(this->world&&
		this->world->world&&
		this->body)
		NewtonDestroyBody(this->world->world,this->body);
}
raf::Newt::SceneNode::~SceneNode() {
	this->Destroy();
	delete this;
}

//various function
void raf::Newt::SceneNode::PosRotScaleAsNode() {
	/*
	core::matrix4 irr_mat;
	irr_mat.setTranslation(this->node->getPosition()*IrrToNewton);
	irr_mat.setRotationDegrees(this->node->getRotation());
	NewtonBodySetMatrix(this->body,&irr_mat.M[0]);
	*/
	this->SetPosition(this->node->getPosition());
}
void raf::Newt::SceneNode::SetInertia(core::vector3df inertia) {
	float mass,inx,iny,inz;
	NewtonBodyGetMassMatrix(this->body,&mass,&inx,&iny,&inz);
	inx=inertia.X;
	iny=inertia.Y;
	inz=inertia.Z;
	NewtonBodySetMassMatrix(this->body,mass,inx,iny,inz);
}
void raf::Newt::SceneNode::SetMass(float mass) {
	float o_mass,inx,iny,inz;
	NewtonBodyGetMassMatrix(this->body,&o_mass,&inx,&iny,&inz);
	NewtonBodySetMassMatrix(this->body,mass/*no o_mass*/,inx,iny,inz);
	this->gravity_force=core::vector3df(0,-mass*9.8,0);
}
irr::core::vector3df raf::Newt::SceneNode::GetInertia() {
	float mass,inx,iny,inz;
	NewtonBodyGetMassMatrix(this->body,&mass,&inx,&iny,&inz);
	return core::vector3df(inx,iny,inz);
}
float raf::Newt::SceneNode::GetMass(){
	float o_mass,inx,iny,inz;
	NewtonBodyGetMassMatrix(this->body,&o_mass,&inx,&iny,&inz);
	return o_mass;
}
void raf::Newt::SceneNode::AddForce(irr::core::vector3df force) {
	this->forces+=force;
	//this->forces_to_cancel.push_back(force);
	NewtonBodySetUserData(this->body,this);
}
void raf::Newt::SceneNode::AddGravityForce() {
	//core::vector3df force(0,-this->GetMass()*98.2*IrrToNewton,0);
	core::vector3df force(0,-this->GetMass()*98.2,0);
	this->forces+=force;
	this->forces_to_cancel.push_back(force);
	NewtonBodySetUserData(this->body,this);
}
void raf::Newt::SceneNode::RotateAroundItself(irr::core::vector3df rot) {
	float v[3];
	v[0]=rot.X;
	v[1]=rot.Y;
	v[2]=rot.Z;
	NewtonBodySetOmega(this->body,v);
}
void raf::Newt::SceneNode::UpdateUserData() {
	NewtonBodySetUserData(this->body,this);
}
void raf::Newt::SceneNode::AutoCalcInertia() {
	float mass=this->GetMass();
	core::vector3df size=this->box_size;

	float Ixx = 10*  mass * (size.X * size.X )/12;
	float Iyy = 10*  mass * (size.Y * size.Y )/12;
	float Izz = 10*  mass * (size.Z * size.Z )/12;

	this->SetInertia(core::vector3df(Ixx,Iyy,Izz));
}

void raf::Newt::SceneNode::SetBoxSize(irr::core::vector3df new_box_size) {
	this->box_size=new_box_size;
	this->Destroy();
	this->Create();
}
//set function
void raf::Newt::SceneNode::SetPosition(irr::core::vector3df pos) {
	this->mat.setTranslation(pos*IrrToNewton);
	NewtonBodySetMatrix(this->body,&mat.M[0]);
}
void raf::Newt::SceneNode::SetRotation(irr::core::vector3df rot) {
	this->mat.setRotationDegrees(this->node->getRotation());
	NewtonBodySetMatrix(this->body,&mat.M[0]);
}
void raf::Newt::SceneNode::SetScale(irr::core::vector3df scale) {
	this->node->setScale(scale);
	this->PosRotScaleAsNode();
}
//------------------------------------------------------------------
//------------------------OCT TREE SCENE NODE CLASS--------------------------
//------------------------------------------------------------------
raf::Newt::OctTreeSceneNode::OctTreeSceneNode(raf::Newt::World* world,irr::scene::ISceneNode* node,irr::scene::IAnimatedMesh* iMeshBase,bool the_model_have_lightmap/*=true*/) {
	this->world=world;
	this->node=node;
	float scale_value=node->getScale().X;


//////////////////////////////////////////////////////////////////////////
//
// Create the newton collision tree from the map mesh
///////////////////////////////////////////////////////////////////////////

	if(the_model_have_lightmap) {
	video::S3DVertex2TCoords* mb_vertices;
	this->collision = NewtonCreateTreeCollision(this->world->world, NULL);
	NewtonTreeCollisionBeginBuild(this->collision);
	int cMeshBuffer, j;
	int v1i, v2i, v3i;
	scene::IMeshBuffer *mb;

	core::vector3df vArray[3]; // vertex array (3*3 floats)

	int tmpCount = 0;

	for (cMeshBuffer=0; cMeshBuffer<iMeshBase->getMesh(0)->getMeshBufferCount(); cMeshBuffer++)
	{	
		mb = iMeshBase->getMesh(0)->getMeshBuffer(cMeshBuffer);

		mb_vertices = (irr::video::S3DVertex2TCoords*)mb->getVertices();

		u16* mb_indices  = mb->getIndices();

		// add each triangle from the mesh
		for (j=0; j<mb->getIndexCount(); j+=3)
		{
			v1i = mb_indices[j];
			v2i = mb_indices[j+1];
			v3i = mb_indices[j+2];
			
			// to make thing easier, her we can use engine data type
			vArray[0] = mb_vertices[v1i].Pos * IrrToNewton;
			vArray[1] = mb_vertices[v2i].Pos * IrrToNewton;
			vArray[2] = mb_vertices[v3i].Pos * IrrToNewton;
			
			// make sure we do not add degenerated polygons to the tree
			core::vector3df e0 (vArray[1] - vArray[0]);
			core::vector3df e1 (vArray[2] - vArray[0]);

			// the area of the face is the cross product
			core::vector3df area (e0.crossProduct (e1));

			// skip faces with very small area
			float mag = area.dotProduct (area);
			//if (mag > 1.0e-6f) {
				NewtonTreeCollisionAddFace(this->collision, 3, &vArray[0].X, sizeof (core::vector3df), 1);
			//} 
		}
	}
	}//if(the_model_have_a_lightmap) {

//--------------------------------------------------------------------------
//--------------------------------------------------------------------
	
	else{//if(the_model_have_a_lightmap) {
	video::S3DVertex* mb_vertices;
	this->collision = NewtonCreateTreeCollision(this->world->world, NULL);
	NewtonTreeCollisionBeginBuild(this->collision);
	int cMeshBuffer, j;
	int v1i, v2i, v3i;
	scene::IMeshBuffer *mb;

	core::vector3df vArray[3]; // vertex array (3*3 floats)

	int tmpCount = 0;

	for (cMeshBuffer=0; cMeshBuffer<iMeshBase->getMesh(0)->getMeshBufferCount(); cMeshBuffer++)
	{	
		mb = iMeshBase->getMesh(0)->getMeshBuffer(cMeshBuffer);

		mb_vertices = (irr::video::S3DVertex*)mb->getVertices();

		u16* mb_indices  = mb->getIndices();

		// add each triangle from the mesh
		for (j=0; j<mb->getIndexCount(); j+=3)
		{
			v1i = mb_indices[j];
			v2i = mb_indices[j+1];
			v3i = mb_indices[j+2];
			
			// to make thing easier, her we can use engine data type
			vArray[0] = mb_vertices[v1i].Pos * IrrToNewton;
			vArray[1] = mb_vertices[v2i].Pos * IrrToNewton;
			vArray[2] = mb_vertices[v3i].Pos * IrrToNewton;
			
			// make sure we do not add degenerated polygons to the tree
			core::vector3df e0 (vArray[1] - vArray[0]);
			core::vector3df e1 (vArray[2] - vArray[0]);

			// the area of the face is the cross product
			core::vector3df area (e0.crossProduct (e1));

			// skip faces with very small area
			float mag = area.dotProduct (area);
			if (mag > 1.0e-6f) {
				NewtonTreeCollisionAddFace(this->collision, 3, &vArray[0].X, sizeof (core::vector3df), 1);
			} 
		}
	}
	}//else{//if(the_model_have_a_lightmap) {
//----------------------------------------------------------------------
	// we definilte wan to optimize the mesh (improve performace and vehaviuor a lot)
	NewtonTreeCollisionEndBuild(this->collision, 1);
	//NewtonTreeCollisionEndBuild(this->collision, 0);

	// create a ridid body to represent the world
	this->body = NewtonCreateBody(this->world->world, this->collision);

	// release the collsion tree (this way the application does not have to do book keeping of Newton objects
	NewtonReleaseCollision (this->world->world, this->collision);
	
	// set the newton world size based on the bsp size
	core::vector3df boxP0; 
	core::vector3df boxP1; 
	core::matrix4 matrix; 
	NewtonBodyGetMatrix (this->body, &matrix.M[0]); 
	NewtonCollisionCalculateAABB (this->collision, &matrix.M[0],  &boxP0.X, &boxP1.X); 
	NewtonSetWorldSize (this->world->world, &boxP0.X, &boxP1.X);

	// the world uses the ground material
	NewtonBodySetMaterialGroupID (this->body, this->world->group_material_ID);
	NewtonBodySetUserData(this->body,this);

	//set the same position of the node
	this->PosRotScaleAsNode();

	NewtonBodySetTransformCallback(this->body,this->PhisicsSetTransformEvent);
	//NewtonBodySetForceAndTorqueCallback(this->body,this->PhisicsSetForceAndTorqueEvent);
/*
	NewtonBodySetAutoFreeze(this->body, 0);
	NewtonWorldUnfreezeBody(this->world->world,this->body); 
	*/
}
raf::Newt::OctTreeSceneNode::~OctTreeSceneNode() {
	delete this;
}
