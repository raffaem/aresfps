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
#ifndef MANCUSO_RAFFAELE_ARES_RUNTIME_DLL_EXPORTS_876902106469048740
#define MANCUSO_RAFFAELE_ARES_RUNTIME_DLL_EXPORTS_876902106469048740

#define ARES_RUNTIME_DLL_EXPORTS

#ifdef ARES_RUNTIME_DLL_EXPORTS
#define ARES_API __declspec(dllexport)
#else 
#define ARES_API __declspec(dllimport)
#endif

#endif