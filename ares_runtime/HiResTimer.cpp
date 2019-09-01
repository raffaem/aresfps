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
#ifndef MANCUSO_RAFFAELE_ARES_RUNTIME_HI_RES_TIMER_HPP_CODE_61498746541SEADFSASDFE09521984AWEFSDFSDASDFWQER
#define MANCUSO_RAFFAELE_ARES_RUNTIME_HI_RES_TIMER_HPP_CODE_61498746541SEADFSASDFE09521984AWEFSDFSDASDFWQER

#include "HiResTimer.h"
#include <gl\\glut.h>

#define LOCK_FRAME_RATE

const dFloat TICKS2SEC = 1.0e-3f;

raf::Newt::CHiResTimer::CHiResTimer() 
{
	m_prevTime = 0;
}

dFloat raf::Newt::CHiResTimer::GetElapsedSeconds()
{
	dFloat timeStep;
	unsigned miliseconds;



	
	miliseconds = glutGet (GLUT_ELAPSED_TIME);

	// optimal keep the fps below 70 fps
	#ifdef LOCK_FRAME_RATE
	while ((miliseconds - m_prevTime) < 14) {
		miliseconds = glutGet (GLUT_ELAPSED_TIME);
	}
	#endif

	timeStep = dFloat (miliseconds - m_prevTime) * TICKS2SEC;
	m_prevTime = miliseconds;
	
	if (timeStep > 0.1f) {
		timeStep = 0.1f;
	}
	if (timeStep < 0.005f) {
		timeStep = 0.005f;
	}


#ifdef RECORD_LOG
//	Sleep (100);
	extern FILE * file;
	fwrite (&timeStep, sizeof (float), 1, file);
	fflush (file);
#endif

#ifdef READ_LOG
	extern FILE * file;
	//Sleep (150);
	fread (&timeStep, sizeof (float), 1, file);
#endif

	
	return timeStep;
} 

#endif