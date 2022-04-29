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
#ifndef RAFFAELE_MANCUSO_IRRLICHT_HELP_LIBRERY_VERSIONE_1_00_00_IRR_HELP_H_HEADER_COD_135463843513843543843513431012
#define RAFFAELE_MANCUSO_IRRLICHT_HELP_LIBRERY_VERSIONE_1_00_00_IRR_HELP_H_HEADER_COD_135463843513843543843513431012

#if !defined(__cplusplus)
#error E' richiesto un compilatore c++
#endif

#pragma auto_inline(on)
#pragma warning (disable:4786)


//librerie
#include <string>
#include "oggetto_animato.hpp"
#include "dll_exports.hpp"
#include "file_class.hpp"
#include "string.hpp"
#include "CHealthSceneNode.hpp"

//#include "Phisics.hpp"

#include <vector>
#include <sstream>
#include <irrlicht.h>
#include <time.h>
using namespace irr;

namespace raf {
	//SCENENODE
	class ARES_API SceneNode:public irr::scene::ISceneNode {
	public:
		void Cammina(int speed, std::string direzione);
		void MuoviAvanti(int speed);
		void MuoviX(int speed);
		void MuoviY(double speed);
		void MuoviZ(int speed);
		void RuotaY(double speed);
		void RuotaX(double speed);
		void RuotaZ(double speed);
		void NewRotationX(double speed);
		void NewRotationY(double speed);
		void NewRotationZ(double speed);
	};
	//BILLBOARD
	class ARES_API BillBoard:public irr::scene::IBillboardSceneNode {
	public:
		void Collisione(scene::ITriangleSelector* world_selector=NULL,float radiusx=0,float radiusy=0,float radiusz=0,float gravityx=0,float gravityy=-100.0f,float gravityz=0);
		void Cammina(int speed, std::string direzione);
		void MuoviAvanti(int speed);
		void MuoviX(int speed);
		void MuoviY(int speed);
		void MuoviZ(int speed);
		void RuotaX(int speed);
		void RuotaY(int speed);
		void RuotaZ(int speed);
		void Trasparente(const char* percorso_texture);
		scene::IBillboardSceneNode* TornaParticellaCapo();
	};
	//CAMERA
	class ARES_API Camera:public irr::scene::ICameraSceneNode {
	public:
		void Collisione(scene::ITriangleSelector* world_selector=NULL,float radiusx=0,float radiusy=0,float radiusz=0,float gravityx=0,float gravityy=-100.0f,float gravityz=0);
		void Muovi(int speed);
		void MuoviX(int speed);
		void MuoviY(int speed);
		void MuoviZ(int speed);
		void RuotaX(int speed);
		void RuotaY(int speed);
		void RuotaZ(int speed);
		void LegaOggettoaCamera(raf::OggettoAnimato* ogg2, int distanza);
		void LegaCameraaOggetto(raf::OggettoAnimato* arma);
	};//della classe Camera
	typedef ARES_API OggettoAnimato*		OGGETTOANIMATO;
	typedef	ARES_API BillBoard*			BILLBOARD;
	typedef ARES_API Camera*				CAMERA;
	typedef ARES_API SceneNode*			SCENENODE;
	//fine classi del gioco

	ARES_API inline char sign(long double num) {return num>0?'+':(num<0?'-':'0');}

	template <class T>void copyVectorToVector(T& a,T& b) {
		for(int i=0;i<b.size();i++) {//scandisce tutto il vetor b
			a.push_back(b[i]);
		}
	}

	ARES_API  u32 itime(core::vector3df start,core::vector3df end,f32 speed);
	//ARES_API void Pause();
	ARES_API bool AddYesNoMessagebox(std::string message,std::string caption);
	ARES_API void errore(std::string message,std::string caption="Error");
	ARES_API void Message(std::string message,std::string caption="Error");
	ARES_API void FatalError(std::string message,std::string caption="Error");
	ARES_API void InizializzaRaf(irr::IrrlichtDevice* device2);
	ARES_API scene::ISceneNode* CaricaMappa(std::string file);
	ARES_API scene::ITriangleSelector* PrendiSelector();
	ARES_API core::vector3df GetPointInFrontOfCamera();
	ARES_API float GetMeshRay(scene::IMesh* m);

	ARES_API inline int Random(int min,int max) {
		return ((rand() % (int)(((max) + 1) - (min))) + (min));
	}

	template<class T> void MixRandomVector(std::vector<T>& c) {
		vector<T> dest;
		while(!c.empty()) {
			srand( (unsigned)time( NULL ) );
			int n=raf::Random(0,c.size()-1);
			dest.push_back(c[n]);
			c.erase(c.begin()+n);
		}
		c=dest;
	}

	//!This namespace contain type conversion function
	namespace conv{
		//!Convert a number into a string
		template<class Num> ARES_API std::string NumString(Num num) {
			std::ostringstream stringa;
			stringa<<num;
			return stringa.str();
		}
		//convert a bool into a string
		ARES_API std::string BoolString(bool b);

		//Convert a string like "0,0,0" or "0-0-0" into a 3d vector
		ARES_API void String3dVector(std::string vettore3d,char carattere_separatore,float& num1,float& num2,float& num3);
		ARES_API core::vector3df String3dVector(std::string vettore3d,char carattere_separatore);

		//!Convert a wchar_t sequence into a char sequence. The return pointer must be deleted
		ARES_API char* WChar_tChar(wchar_t* s,int max_char_size=2000);
		ARES_API inline char* WChar_tChar(const wchar_t* s,int max_char_size=2000) {return WChar_tChar(const_cast<wchar_t*>(s),max_char_size);}

		//!Convert a wchar_t sequence into a string
		ARES_API std::string WChar_tString(wchar_t* s,int max_char_size=2000);
		ARES_API inline std::string WChar_tString(const wchar_t* s,int max_char_size=2000) {return WChar_tString(const_cast<wchar_t*>(s),max_char_size);}

		//!Convert a wchar_t sequence into a float
		ARES_API float WChar_tFloat(wchar_t* s);
		ARES_API inline float WChar_tFloat(const wchar_t* s) {return raf::conv::WChar_tFloat(const_cast<wchar_t*>(s));}
		
		//!Convert a char sequence into a wchar_t sequence. The return pointer must be deleted
		ARES_API wchar_t* CharWChar_T(char* s,int max_char_size=2000);
		ARES_API inline wchar_t* CharWChar_T(const char* s,int max_char_size=2000) {return CharWChar_T(const_cast<char*>(s),max_char_size);}

		//Convert a num into a wchar_t string. The return pointer must be deleted
		template<class Num> ARES_API wchar_t* NumWChar_t(Num number) {
			std::string string_num;
			string_num=raf::conv::NumString(number);
			const char* c_string_num=string_num.c_str();
			wchar_t* w_string_num=raf::conv::CharWChar_T(c_string_num);
			return w_string_num;
		}

		//Convert a file list into a string vector
		ARES_API std::vector<std::string> FilelistVector(io::IFileList* the_list);

		//Convert a string yes\no into a bool
		ARES_API bool StringBool (std::string value);

		//Convert a unix dir into a windows dir
		ARES_API std::string UnixDirToWinDir(std::string unix_dir);
		
	}

	ARES_API std::string AddFileOpenDialog(const wchar_t* title,bool modal=true,gui::IGUIElement* parent=0,s32 id=-1);
	ARES_API void esiste(std::string file);
	ARES_API void DiffuseLight(irr::scene::ISceneNode* node,bool dl);

	ARES_API void Land(
		scene::ISceneNode* node,
		scene::ITriangleSelector* world_selector,
		float radius);
	ARES_API core::vector3df Land(
		core::vector3df pos,
		scene::ITriangleSelector* world_selector,
		float radius);

	//DIR FUNCTIONS
	#ifdef WIN32
	ARES_API std::string GetWin32ProgramFullPath();
	#endif

	ARES_API void ChWorkingDirectoryToThisProg(char* argv0);
	ARES_API void ChangeCurrentDirTo(std::string destdir);
	ARES_API void RestoreDir();
	ARES_API std::string UpDir(std::string dir);

	//scene node functions
	ARES_API inline void NewRotationY(scene::ISceneNode* node,float value) {
		core::vector3df rot=node->getRotation();
		rot.Y=value;
		node->setRotation(rot);
	}

	ARES_API inline void MuoviY(scene::ISceneNode* node,float value) {
		core::vector3df rot=node->getPosition();
		rot.Y+=value;
		node->setPosition(rot);
	}
	//ARES SPECIFIC FUNCTION
	ARES_API std::string GetAresFPSHome();
	ARES_API bool CeckPackage(std::string ares_home,std::string package_name);
	ARES_API float GetAresFPSVerFromReg();
}//del namespace
#endif








