/******************************************************************* 
* Copyright (C) 2006 Brett R. Jones issued to public domain 
*********************************************************************/ 

/*
I have modified the original code to adapt it to Ares.
You can find the original code here: http://irrlicht.sourceforge.net/phpBB2/viewtopic.php?t=13961&highlight=loading+bar
*/

#ifndef VX_HEALTH_SCENE_NODE_H 
#define VX_HEALTH_SCENE_NODE_H 

#include <irrlicht.h>
#include "dll_exports.hpp"

namespace raf
{ 

class ARES_API VxHealthSceneNode : public irr::scene::ISceneNode 
{ 
public: 

//! constructor 
	VxHealthSceneNode( irr::scene::ISceneNode* parent, 
irr::scene::ISceneManager* mgr, 
irr::s32 id, 
irr::scene::ISceneCollisionManager* coll, 
irr::s32 width = 100, 
irr::s32 height = 10, 
const irr::core::vector3df& position = irr::core::vector3df(0,0,0), 
irr::video::SColor BarColor=irr::video::SColor(150,0,200,0), 
irr::video::SColor BkgColor=irr::video::SColor(150,200,0,0), 
irr::video::SColor BoarderColor=irr::video::SColor(200,220,220,220) ); 

//! destructor 
virtual ~VxHealthSceneNode(); 

virtual void OnPreRender(); 

//! renders the node. 
virtual void render(); 

//! returns the axis aligned bounding box of this node 
virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const; 

//! returns amount of materials used by this scene node. 
virtual irr::s32 getMaterialCount(); 

//! sets progress percentage ( or health ) 
virtual void setProgress( irr::s32 s32Percent ); 

//! sets the color of the progress bar 
virtual void setProgressColor(irr::video::SColor color); 

//! sets the color of the progress bar background 
virtual void setBackgroundColor(irr::video::SColor color); 

//! sets the color of the progress bar border 
virtual void setBorderColor(irr::video::SColor color); 


private: 

irr::core::aabbox3d< irr::f32 > Box; 
irr::video::SColor BarColor; 
irr::video::SColor BorderColor; 
irr::video::SColor BkgColor; 
irr::scene::ISceneCollisionManager* Coll; 
irr::core::dimension2d<irr::s32> m_gDim; //dimension width, height 
irr::s32 m_bBorder; 
irr::s32 MaxNum; 
irr::s32 isVisible; 
irr::s32 m_s32Percent; 
}; 

} // end namespace raf 

#endif // VX_HEALTH_SCENE_NODE_H 
