/******************************************************************* 
* Copyright (C) 2006 Brett R. Jones issued to public domain 
*********************************************************************/ 
/*
I have modified the original code to adapt it to Ares.
You can find the original code here: http://irrlicht.sourceforge.net/phpBB2/viewtopic.php?t=13961&highlight=loading+bar
*/

#include "CHealthSceneNode.hpp" 

using namespace irr;
using namespace scene;
using namespace core;

//! constructor 
raf::VxHealthSceneNode::VxHealthSceneNode( ISceneNode* parent, 
ISceneManager* mgr, 
s32 id, 
scene::ISceneCollisionManager* coll, 
s32 width, 
s32 height, 
const core::vector3df& position, 
video::SColor BarColorIn, 
video::SColor BkgColorIn, 
video::SColor BorderColorIn ) 
: ISceneNode(parent, mgr, id, position), 
Coll(coll), 
BarColor(BarColorIn), 
BkgColor(BkgColorIn), 
BorderColor(BorderColorIn), 
m_gDim( width, height ), 
m_bBorder(1), 
isVisible(1), 
m_s32Percent(100) 
{ 
#ifdef _DEBUG 
setDebugName("VxHealthSceneNode"); 
#endif 

setAutomaticCulling(false); 
////////////////////////////////////////////////////////// 
//Set Bounding box 
f32 halfWidth = (f32)m_gDim.Width/2; 
f32 halfHeight = (f32)m_gDim.Height/2; 
Box.MinEdge.set(-halfWidth,-halfHeight,-1.0); 
Box.MaxEdge.set(halfWidth,halfHeight,1.0); 
} 

//! destructor 
raf::VxHealthSceneNode::~VxHealthSceneNode() 
{ 
} 

void raf::VxHealthSceneNode::OnPreRender() 
{ 
if (IsVisible) 
SceneManager->registerNodeForRendering(this, ESNRP_SHADOW); 

ISceneNode::OnPreRender(); 
} 

//! renders the node. 
void raf::VxHealthSceneNode::render() 
{ 
if( !Coll ) 
return; 
if(!isVisible) 
{ 
return; 
} 

///////////////////////////////////////////////////////////////////// 
video::IVideoDriver* driver = SceneManager->getVideoDriver(); 
ICameraSceneNode* camera = SceneManager->getActiveCamera(); 

if (!camera || !driver) 
return; 

if (DebugDataVisible) 
{ 
driver->setTransform(video::ETS_WORLD, AbsoluteTransformation); 
video::SMaterial m; 
m.Lighting = false; 
driver->setMaterial(m); 
driver->draw3DBox(Box, video::SColor(0,208,195,152)); 
} 
////////////////////////////////////////////////////////////////////// 

core::position2d<s32> pos = Coll->getScreenCoordinatesFrom3DPosition(getAbsolutePosition(), 
SceneManager->getActiveCamera()); 

// calculate health bar rectangle 
f32 halfWidth = (f32)m_gDim.Width/2; 
core::rect<s32> AbsoluteRect( pos, m_gDim ); 
// center the bar 
AbsoluteRect.UpperLeftCorner.X -= halfWidth; 
AbsoluteRect.LowerRightCorner.X -= halfWidth; 

core::rect<s32> BarRect = AbsoluteRect; 

// draw boarder if needed 
if( m_bBorder ) 
{ 
driver->draw2DRectangle( BorderColor, AbsoluteRect, &AbsoluteRect); 
// shrink by one for bar 
BarRect.UpperLeftCorner.X += 1; 
BarRect.UpperLeftCorner.Y += 1; 
BarRect.LowerRightCorner.X -= 1; 
BarRect.LowerRightCorner.Y -= 1; 
} 
// calculate progress bar 
MaxNum = (BarRect.LowerRightCorner.X - BarRect.UpperLeftCorner.X) - 1; 
s32 PercentNum = (s32)((m_s32Percent * MaxNum) / 100); 

// draw progress part 
core::rect<s32> LoadRect = BarRect; 
LoadRect.LowerRightCorner.X = BarRect.UpperLeftCorner.X + PercentNum; 
driver->draw2DRectangle( BarColor, LoadRect, &LoadRect ); 

// draw empty part 
LoadRect.UpperLeftCorner.X = BarRect.UpperLeftCorner.X + PercentNum; 
LoadRect.LowerRightCorner.X = BarRect.LowerRightCorner.X; 
driver->draw2DRectangle( BkgColor, LoadRect, &LoadRect ); 
} 


//! returns the axis aligned bounding box of this node 
const core::aabbox3d<f32>& raf::VxHealthSceneNode::getBoundingBox() const 
{ 
return Box; 
} 

//! returns amount of materials used by this scene node. 
s32 raf::VxHealthSceneNode::getMaterialCount() 
{ 
return 0; 
} 

//! sets the progress percentage ( or health ) 
void raf::VxHealthSceneNode::setProgress( s32 s32Percent ) 
{ 
m_s32Percent = s32Percent; 
if( m_s32Percent < 0 ) 
{ 
m_s32Percent = 0; 
} 
if( m_s32Percent > 100 ) 
{ 
m_s32Percent = 100; 
} 

} 

//! sets the color of the progress 
void raf::VxHealthSceneNode::setProgressColor(video::SColor color) 
{ 
BarColor = color; 
} 

//! sets the color of the progress bar background 
void raf::VxHealthSceneNode::setBackgroundColor(video::SColor color) 
{ 
BkgColor = color; 
} 

//! sets the color of the progress bar border 
void raf::VxHealthSceneNode::setBorderColor(video::SColor color) 
{ 
BorderColor = color; 
} 

