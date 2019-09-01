/*
** Lua binding: AresLua
** Generated automatically by tolua++-1.0.92 on 08/26/06 15:00:28.
*/
#include "tolua_lua.h"

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_AresLua_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_AresVec3d (lua_State* tolua_S)
{
 AresVec3d* self = (AresVec3d*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"AresVec3d");
}

/* method: new of class  AresVec3d */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresVec3d_new00
static int tolua_AresLua_AresVec3d_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AresVec3d",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   AresVec3d* tolua_ret = (AresVec3d*)  new AresVec3d();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"AresVec3d");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  AresVec3d */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresVec3d_new00_local
static int tolua_AresLua_AresVec3d_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AresVec3d",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   AresVec3d* tolua_ret = (AresVec3d*)  new AresVec3d();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"AresVec3d");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  AresVec3d */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresVec3d_new01
static int tolua_AresLua_AresVec3d_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AresVec3d",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float X = ((float)  tolua_tonumber(tolua_S,2,0));
  float Y = ((float)  tolua_tonumber(tolua_S,3,0));
  float Z = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   AresVec3d* tolua_ret = (AresVec3d*)  new AresVec3d(X,Y,Z);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"AresVec3d");
  }
 }
 return 1;
tolua_lerror:
 return tolua_AresLua_AresVec3d_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  AresVec3d */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresVec3d_new01_local
static int tolua_AresLua_AresVec3d_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AresVec3d",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float X = ((float)  tolua_tonumber(tolua_S,2,0));
  float Y = ((float)  tolua_tonumber(tolua_S,3,0));
  float Z = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   AresVec3d* tolua_ret = (AresVec3d*)  new AresVec3d(X,Y,Z);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"AresVec3d");
  }
 }
 return 1;
tolua_lerror:
 return tolua_AresLua_AresVec3d_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: x of class  AresVec3d */
#ifndef TOLUA_DISABLE_tolua_get_AresVec3d_x
static int tolua_get_AresVec3d_x(lua_State* tolua_S)
{
  AresVec3d* self = (AresVec3d*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->x);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: x of class  AresVec3d */
#ifndef TOLUA_DISABLE_tolua_set_AresVec3d_x
static int tolua_set_AresVec3d_x(lua_State* tolua_S)
{
  AresVec3d* self = (AresVec3d*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->x = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: y of class  AresVec3d */
#ifndef TOLUA_DISABLE_tolua_get_AresVec3d_y
static int tolua_get_AresVec3d_y(lua_State* tolua_S)
{
  AresVec3d* self = (AresVec3d*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->y);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: y of class  AresVec3d */
#ifndef TOLUA_DISABLE_tolua_set_AresVec3d_y
static int tolua_set_AresVec3d_y(lua_State* tolua_S)
{
  AresVec3d* self = (AresVec3d*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->y = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: z of class  AresVec3d */
#ifndef TOLUA_DISABLE_tolua_get_AresVec3d_z
static int tolua_get_AresVec3d_z(lua_State* tolua_S)
{
  AresVec3d* self = (AresVec3d*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'z'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->z);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: z of class  AresVec3d */
#ifndef TOLUA_DISABLE_tolua_set_AresVec3d_z
static int tolua_set_AresVec3d_z(lua_State* tolua_S)
{
  AresVec3d* self = (AresVec3d*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'z'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->z = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* function: AresSetWeaponDiffuseLight */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresSetWeaponDiffuseLight00
static int tolua_AresLua_AresSetWeaponDiffuseLight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isboolean(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool value = ((bool)  tolua_toboolean(tolua_S,1,0));
  {
   AresSetWeaponDiffuseLight(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AresSetWeaponDiffuseLight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AresGetWeaponPos */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresGetWeaponPos00
static int tolua_AresLua_AresGetWeaponPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   AresVec3d tolua_ret = (AresVec3d)  AresGetWeaponPos();
   {
#ifdef __cplusplus
    void* tolua_obj = new AresVec3d(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"AresVec3d");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(AresVec3d));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"AresVec3d");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AresGetWeaponPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AresSetWeaponPos */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresSetWeaponPos00
static int tolua_AresLua_AresSetWeaponPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AresVec3d",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AresVec3d new_pos = *((AresVec3d*)  tolua_tousertype(tolua_S,1,0));
  {
   AresSetWeaponPos(new_pos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AresSetWeaponPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AresGetWeaponSpeed */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresGetWeaponSpeed00
static int tolua_AresLua_AresGetWeaponSpeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   float tolua_ret = (float)  AresGetWeaponSpeed();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AresGetWeaponSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AresSetWeaponSpeed */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresSetWeaponSpeed00
static int tolua_AresLua_AresSetWeaponSpeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float s = ((float)  tolua_tonumber(tolua_S,1,0));
  {
   AresSetWeaponSpeed(s);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AresSetWeaponSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AresSetDiffuseLightEnemie */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresSetDiffuseLightEnemie00
static int tolua_AresLua_AresSetDiffuseLightEnemie00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int num = ((int)  tolua_tonumber(tolua_S,1,0));
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
  {
   AresSetDiffuseLightEnemie(num,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AresSetDiffuseLightEnemie'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AresEraseEnemie */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresEraseEnemie00
static int tolua_AresLua_AresEraseEnemie00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int num = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   AresEraseEnemie(num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AresEraseEnemie'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AresGetTotalEnemieCount */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresGetTotalEnemieCount00
static int tolua_AresLua_AresGetTotalEnemieCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  AresGetTotalEnemieCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AresGetTotalEnemieCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AresGetEnemiePos */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresGetEnemiePos00
static int tolua_AresLua_AresGetEnemiePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int num = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   AresVec3d tolua_ret = (AresVec3d)  AresGetEnemiePos(num);
   {
#ifdef __cplusplus
    void* tolua_obj = new AresVec3d(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"AresVec3d");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(AresVec3d));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"AresVec3d");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AresGetEnemiePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AresGetEnemieRot */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresGetEnemieRot00
static int tolua_AresLua_AresGetEnemieRot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int num = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   AresVec3d tolua_ret = (AresVec3d)  AresGetEnemieRot(num);
   {
#ifdef __cplusplus
    void* tolua_obj = new AresVec3d(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"AresVec3d");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(AresVec3d));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"AresVec3d");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AresGetEnemieRot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AresSetEnemiePos */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresSetEnemiePos00
static int tolua_AresLua_AresSetEnemiePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"AresVec3d",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int num = ((int)  tolua_tonumber(tolua_S,1,0));
  AresVec3d new_pos = *((AresVec3d*)  tolua_tousertype(tolua_S,2,0));
  {
   AresSetEnemiePos(num,new_pos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AresSetEnemiePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AresSetEnemieRot */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresSetEnemieRot00
static int tolua_AresLua_AresSetEnemieRot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"AresVec3d",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int num = ((int)  tolua_tonumber(tolua_S,1,0));
  AresVec3d new_rot = *((AresVec3d*)  tolua_tousertype(tolua_S,2,0));
  {
   AresSetEnemieRot(num,new_rot);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AresSetEnemieRot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AresWeaponSetShininess */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresWeaponSetShininess00
static int tolua_AresLua_AresWeaponSetShininess00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float value = ((float)  tolua_tonumber(tolua_S,1,0));
  {
   AresWeaponSetShininess(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AresWeaponSetShininess'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AresEnemiesSetShininess */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresEnemiesSetShininess00
static int tolua_AresLua_AresEnemiesSetShininess00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float value = ((float)  tolua_tonumber(tolua_S,1,0));
  {
   AresEnemiesSetShininess(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AresEnemiesSetShininess'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AresWeaponGetShininess */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresWeaponGetShininess00
static int tolua_AresLua_AresWeaponGetShininess00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   float tolua_ret = (float)  AresWeaponGetShininess();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AresWeaponGetShininess'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AresEnemiesGetShininess */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresEnemiesGetShininess00
static int tolua_AresLua_AresEnemiesGetShininess00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   float tolua_ret = (float)  AresEnemiesGetShininess();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AresEnemiesGetShininess'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AresShowMessageBox */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresShowMessageBox00
static int tolua_AresLua_AresShowMessageBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string caption = ((std::string)  tolua_tocppstring(tolua_S,1,0));
  std::string message = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   AresShowMessageBox(caption,message);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AresShowMessageBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AresShowErrorMessageBox */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresShowErrorMessageBox00
static int tolua_AresLua_AresShowErrorMessageBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string caption = ((std::string)  tolua_tocppstring(tolua_S,1,0));
  std::string message = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   AresShowErrorMessageBox(caption,message);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AresShowErrorMessageBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AresExit */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresExit00
static int tolua_AresLua_AresExit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   AresExit();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AresExit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AresSetImmortal */
#ifndef TOLUA_DISABLE_tolua_AresLua_AresSetImmortal00
static int tolua_AresLua_AresSetImmortal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isboolean(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool value = ((bool)  tolua_toboolean(tolua_S,1,0));
  {
   AresSetImmortal(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AresSetImmortal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_AresLua_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"AresVec3d","AresVec3d","",tolua_collect_AresVec3d);
  #else
  tolua_cclass(tolua_S,"AresVec3d","AresVec3d","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"AresVec3d");
   tolua_function(tolua_S,"new",tolua_AresLua_AresVec3d_new00);
   tolua_function(tolua_S,"new_local",tolua_AresLua_AresVec3d_new00_local);
   tolua_function(tolua_S,".call",tolua_AresLua_AresVec3d_new00_local);
   tolua_function(tolua_S,"new",tolua_AresLua_AresVec3d_new01);
   tolua_function(tolua_S,"new_local",tolua_AresLua_AresVec3d_new01_local);
   tolua_function(tolua_S,".call",tolua_AresLua_AresVec3d_new01_local);
   tolua_variable(tolua_S,"x",tolua_get_AresVec3d_x,tolua_set_AresVec3d_x);
   tolua_variable(tolua_S,"y",tolua_get_AresVec3d_y,tolua_set_AresVec3d_y);
   tolua_variable(tolua_S,"z",tolua_get_AresVec3d_z,tolua_set_AresVec3d_z);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"AresSetWeaponDiffuseLight",tolua_AresLua_AresSetWeaponDiffuseLight00);
  tolua_function(tolua_S,"AresGetWeaponPos",tolua_AresLua_AresGetWeaponPos00);
  tolua_function(tolua_S,"AresSetWeaponPos",tolua_AresLua_AresSetWeaponPos00);
  tolua_function(tolua_S,"AresGetWeaponSpeed",tolua_AresLua_AresGetWeaponSpeed00);
  tolua_function(tolua_S,"AresSetWeaponSpeed",tolua_AresLua_AresSetWeaponSpeed00);
  tolua_function(tolua_S,"AresSetDiffuseLightEnemie",tolua_AresLua_AresSetDiffuseLightEnemie00);
  tolua_function(tolua_S,"AresEraseEnemie",tolua_AresLua_AresEraseEnemie00);
  tolua_function(tolua_S,"AresGetTotalEnemieCount",tolua_AresLua_AresGetTotalEnemieCount00);
  tolua_function(tolua_S,"AresGetEnemiePos",tolua_AresLua_AresGetEnemiePos00);
  tolua_function(tolua_S,"AresGetEnemieRot",tolua_AresLua_AresGetEnemieRot00);
  tolua_function(tolua_S,"AresSetEnemiePos",tolua_AresLua_AresSetEnemiePos00);
  tolua_function(tolua_S,"AresSetEnemieRot",tolua_AresLua_AresSetEnemieRot00);
  tolua_function(tolua_S,"AresWeaponSetShininess",tolua_AresLua_AresWeaponSetShininess00);
  tolua_function(tolua_S,"AresEnemiesSetShininess",tolua_AresLua_AresEnemiesSetShininess00);
  tolua_function(tolua_S,"AresWeaponGetShininess",tolua_AresLua_AresWeaponGetShininess00);
  tolua_function(tolua_S,"AresEnemiesGetShininess",tolua_AresLua_AresEnemiesGetShininess00);
  tolua_function(tolua_S,"AresShowMessageBox",tolua_AresLua_AresShowMessageBox00);
  tolua_function(tolua_S,"AresShowErrorMessageBox",tolua_AresLua_AresShowErrorMessageBox00);
  tolua_function(tolua_S,"AresExit",tolua_AresLua_AresExit00);
  tolua_function(tolua_S,"AresSetImmortal",tolua_AresLua_AresSetImmortal00);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_AresLua (lua_State* tolua_S) {
 return tolua_AresLua_open(tolua_S);
};
#endif

