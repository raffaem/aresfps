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

#include "dMatrix.h"
#include "dQuaternion.h"

raf::Newt::dMatrix::dMatrix (const raf::Newt::dQuaternion &rotation, const dVector &position)
{
	dFloat x2;
	dFloat y2;
	dFloat z2;
	dFloat w2;
	dFloat xy;
	dFloat xz;
	dFloat xw;
	dFloat yz;
	dFloat yw;
	dFloat zw;

	w2 = dFloat (2.0f) * rotation.m_q0 * rotation.m_q0;
	x2 = dFloat (2.0f) * rotation.m_q1 * rotation.m_q1;
	y2 = dFloat (2.0f) * rotation.m_q2 * rotation.m_q2;
	z2 = dFloat (2.0f) * rotation.m_q3 * rotation.m_q3;

  	_ASSERTE (dAbs (w2 + x2 + y2 + z2 - dFloat(2.0f)) < dFloat (1.5e-4f));

	xy = dFloat (2.0f) * rotation.m_q1 * rotation.m_q2;
	xz = dFloat (2.0f) * rotation.m_q1 * rotation.m_q3;
	xw = dFloat (2.0f) * rotation.m_q1 * rotation.m_q0;
	yz = dFloat (2.0f) * rotation.m_q2 * rotation.m_q3;
	yw = dFloat (2.0f) * rotation.m_q2 * rotation.m_q0;
	zw = dFloat (2.0f) * rotation.m_q3 * rotation.m_q0;


	m_front = dVector (w2 + x2 - dFloat(1.0f), xy + zw,                xz - yw               , dFloat(0.0f));
	m_up    = dVector (xy - zw,                w2 + y2 - dFloat(1.0f), yz + xw               , dFloat(0.0f));
	m_right = dVector (xz + yw,                yz - xw,                w2 + z2 - dFloat(1.0f), dFloat(0.0f));

	m_posit.m_x = position.m_x;
	m_posit.m_y = position.m_y;
	m_posit.m_z = position.m_z;
	m_posit.m_w = dFloat(1.0f);
}


