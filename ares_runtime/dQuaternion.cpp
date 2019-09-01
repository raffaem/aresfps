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
#include "Phisics_math_functions.h"
#include "dVector.h"
#include "dMatrix.h"
#include "dQuaternion.h"

enum QUAT_INDEX
{
   X_INDEX=0,
   Y_INDEX=1,
   Z_INDEX=2
};
static QUAT_INDEX QIndex [] = {Y_INDEX, Z_INDEX, X_INDEX};


raf::Newt::dQuaternion::dQuaternion (const raf::Newt::dMatrix &matrix)
{
	dFloat *ptr;
	dFloat trace;
	QUAT_INDEX i;
	QUAT_INDEX j;
	QUAT_INDEX k;

	trace = matrix[0][0] + matrix[1][1] + matrix[2][2];

	if (trace > dFloat(0.0f)) {
		trace = dSqrt (trace + dFloat(1.0f));
		m_q0 = dFloat (0.5f) * trace;
		trace = dFloat (0.5f) / trace;

		m_q1 = (matrix[2][1] - matrix[1][2]) * trace;
		m_q2 = (matrix[0][2] - matrix[2][0]) * trace;
		m_q3 = (matrix[1][0] - matrix[0][1]) * trace;

	} else {
		i = X_INDEX;
		if (matrix[Y_INDEX][Y_INDEX] > matrix[X_INDEX][X_INDEX]) {
			i = Y_INDEX;
		}
		if (matrix[Z_INDEX][Z_INDEX] > matrix[i][i]) {
			i = Z_INDEX;
		}
		j = QIndex [i];
		k = QIndex [j];

		trace = dFloat(1.0f) + matrix[i][i] - matrix[j][j] - matrix[k][k];
		trace = dSqrt (trace);

		ptr = &m_q1;
		ptr[i] = dFloat (0.5f) * trace;
		trace = dFloat (0.5f) / trace;
		ptr[3] = (matrix[k][j] - matrix[j][k]) * trace;
		ptr[j] = (matrix[j][i] + matrix[i][j]) * trace;
		ptr[k] = (matrix[k][i] + matrix[i][k]) * trace;
	}

	m_q1 *= dFloat (-1.0f);
	m_q2 *= dFloat (-1.0f);;
	m_q3 *= dFloat (-1.0f);;

#if _DEBUG
	dFloat err = dAbs (DotProduct(*this) - dFloat(1.0f));
	_ASSERTE (err < dFloat(1.0e-3f));
#endif

}


raf::Newt::dQuaternion::dQuaternion (const dVector &unitAxis, dFloat Angle)
{
	dFloat sinAng;

	Angle *= dFloat (0.5f);
	m_q0 = dCos (Angle);
	sinAng = dSin (Angle);

#ifdef _DEBUG
	if (dAbs (Angle) > dFloat(1.0e-6f)) {
		_ASSERTE (dAbs (dFloat(1.0f) - unitAxis % unitAxis) < dFloat(1.0e-3f));
	} 
#endif
	m_q1 = unitAxis.m_x * sinAng;
	m_q2 = unitAxis.m_y * sinAng;
	m_q3 = unitAxis.m_z * sinAng;
}


raf::Newt::dVector raf::Newt::dQuaternion::CalcAverageOmega (const raf::Newt::dQuaternion &QB, dFloat dt) const
{
	dFloat dirMag;
	dFloat dirMag2;
	dFloat omegaMag;
	dFloat dirMagInv;


	dQuaternion dq (Inverse() * QB);
	dVector omegaDir (dq.m_q1, dq.m_q2, dq.m_q3);

	dirMag2 = omegaDir % omegaDir;
	if (dirMag2	< dFloat(dFloat (1.0e-5f) * dFloat (1.0e-5f))) {
		return dVector (dFloat(0.0f), dFloat(0.0f), dFloat(0.0f), dFloat(0.0f));
	}

	dirMagInv = dFloat (1.0f) / dSqrt (dirMag2);
	dirMag = dirMag2 * dirMagInv;

	omegaMag = dFloat(2.0f) * dAtan2 (dirMag, dq.m_q0) / dt;

	return omegaDir.Scale (dirMagInv * omegaMag);
}


raf::Newt::dQuaternion raf::Newt::dQuaternion::Slerp (const dQuaternion &QB, dFloat t) const 
{
	dFloat dot;
	dFloat ang;
	dFloat Sclp;
	dFloat Sclq;
	dFloat den;
	dFloat sinAng;
	dQuaternion Q;

	dot = DotProduct (QB);

	if ((dot + dFloat(1.0f)) > dFloat(1.0e-5f)) {
		if (dot < dFloat(0.995f)) {

			ang = dAcos (dot);

			sinAng = dSin (ang);
			den = dFloat(1.0f) / sinAng;

			Sclp = dSin ((dFloat(1.0f) - t ) * ang) * den;
			Sclq = dSin (t * ang) * den;

		} else  {
			Sclp = dFloat(1.0f) - t;
			Sclq = t;
		}

		Q.m_q0 = m_q0 * Sclp + QB.m_q0 * Sclq;
		Q.m_q1 = m_q1 * Sclp + QB.m_q1 * Sclq;
		Q.m_q2 = m_q2 * Sclp + QB.m_q2 * Sclq;
		Q.m_q3 = m_q3 * Sclp + QB.m_q3 * Sclq;

	} else {
		Q.m_q0 =  m_q3;
		Q.m_q1 = -m_q2;
		Q.m_q2 =  m_q1;
		Q.m_q3 =  m_q0;

		Sclp = dSin ((dFloat(1.0f) - t) * dFloat (3.1416f *0.5f));
		Sclq = dSin (t * dFloat (3.1416f * 0.5f));

		Q.m_q0 = m_q0 * Sclp + Q.m_q0 * Sclq;
		Q.m_q1 = m_q1 * Sclp + Q.m_q1 * Sclq;
		Q.m_q2 = m_q2 * Sclp + Q.m_q2 * Sclq;
		Q.m_q3 = m_q3 * Sclp + Q.m_q3 * Sclq;
	}

	dot = Q.DotProduct (Q);
	if ((dot) < (1.0f - 1.0e-4f) ) {
		dot = dFloat(1.0f) / dSqrt (dot);
		//dot = dgRsqrt (dot);
		Q.m_q0 *= dot;
		Q.m_q1 *= dot;
		Q.m_q2 *= dot;
		Q.m_q3 *= dot;
	}
	return Q;
}

