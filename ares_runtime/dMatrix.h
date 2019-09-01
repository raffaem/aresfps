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
#ifndef __dMatrix__
#define __dMatrix__

#include "Phisics_math_functions.h"
#include <Newton.h>

namespace raf{
	namespace Newt{

	class dQuaternion;
	class dVector;
	// small but fully operational 4x4 matrix class
		
class dMatrix
{
	public:
	dMatrix ();
	dMatrix (const raf::Newt::dVector &front, const raf::Newt::dVector &up, const raf::Newt::dVector &right, const raf::Newt::dVector &posit):m_front (front), m_up(up), m_right(right), m_posit(posit) {}
	dMatrix (const raf::Newt::dQuaternion &rotation, const dVector &position);

	raf::Newt::dVector& operator[] (int i);
	const raf::Newt::dVector& operator[] (int i) const;

	dMatrix Inverse () const;
	dMatrix Transpose () const;
	dMatrix Transpose4X4 () const;
	raf::Newt::dVector RotateVector (const dVector &v) const;
	raf::Newt::dVector UnrotateVector (const dVector &v) const;
	raf::Newt::dVector TransformVector (const dVector &v) const;
	raf::Newt::dVector UntransformVector (const dVector &v) const;

	void TransformTriplex (void* const dst, int dstStrideInBytes,
						   void* const src, int srcStrideInBytes, int count) const;

	dMatrix operator* (const raf::Newt::dMatrix &B) const;


	raf::Newt::dVector m_front;
	raf::Newt::dVector m_up;
	raf::Newt::dVector m_right;
	raf::Newt::dVector m_posit;
};
	}
}


inline raf::Newt::dMatrix GetIdentityMatrix()
{
	return raf::Newt::dMatrix (raf::Newt::dVector (1.0f, 0.0f, 0.0f, 0.0f),
				    raf::Newt::dVector (0.0f, 1.0f, 0.0f, 0.0f),
				    raf::Newt::dVector (0.0f, 0.0f, 1.0f, 0.0f),
				    raf::Newt::dVector (0.0f, 0.0f, 0.0f, 1.0f));
}

inline raf::Newt::dMatrix GetZeroMatrix ()
{
return raf::Newt::dMatrix (raf::Newt::dVector (0.0f, 0.0f, 0.0f, 0.0f),
					raf::Newt::dVector (0.0f, 0.0f, 0.0f, 0.0f),
					raf::Newt::dVector (0.0f, 0.0f, 0.0f, 0.0f),
					raf::Newt::dVector (0.0f, 0.0f, 0.0f, 0.0f));
}


inline raf::Newt::dMatrix::dMatrix ()
{
}

inline raf::Newt::dVector& raf::Newt::dMatrix::operator[] (int  i)
{
	return (&m_front)[i];
}

inline const raf::Newt::dVector& raf::Newt::dMatrix::operator[] (int  i) const
{
	return (&m_front)[i];
}

inline raf::Newt::dMatrix raf::Newt::dMatrix::Inverse () const
{
	return raf::Newt::dMatrix (raf::Newt::dVector (m_front.m_x, m_up.m_x, m_right.m_x, 0.0f),
					raf::Newt::dVector (m_front.m_y, m_up.m_y, m_right.m_y, 0.0f),
		            raf::Newt::dVector (m_front.m_z, m_up.m_z, m_right.m_z, 0.0f),
		            raf::Newt::dVector (- (m_posit % m_front), - (m_posit % m_up), - (m_posit % m_right), 1.0f));
}

inline raf::Newt::dMatrix raf::Newt::dMatrix::Transpose () const
{
	return raf::Newt::dMatrix (dVector (m_front.m_x, m_up.m_x, m_right.m_x, 0.0f),
					dVector (m_front.m_y, m_up.m_y, m_right.m_y, 0.0f),
					dVector (m_front.m_z, m_up.m_z, m_right.m_z, 0.0f),
					dVector (0.0f, 0.0f, 0.0f, 1.0f));
}

inline raf::Newt::dMatrix raf::Newt::dMatrix::Transpose4X4 () const
{
	return raf::Newt::dMatrix (dVector (m_front.m_x, m_up.m_x, m_right.m_x, m_posit.m_x),
					dVector (m_front.m_y, m_up.m_y, m_right.m_y, m_posit.m_y),
					dVector (m_front.m_z, m_up.m_z, m_right.m_z, m_posit.m_z),
					dVector (m_front.m_w, m_up.m_w, m_right.m_w, m_posit.m_w));
							
}

inline raf::Newt::dVector raf::Newt::dMatrix::RotateVector (const raf::Newt::dVector &v) const
{
	return raf::Newt::dVector (v.m_x * m_front.m_x + v.m_y * m_up.m_x + v.m_z * m_right.m_x,
					 v.m_x * m_front.m_y + v.m_y * m_up.m_y + v.m_z * m_right.m_y,
					 v.m_x * m_front.m_z + v.m_y * m_up.m_z + v.m_z * m_right.m_z);
}


inline raf::Newt::dVector raf::Newt::dMatrix::UnrotateVector (const raf::Newt::dVector &v) const
{
	return dVector (v % m_front, v % m_up, v % m_right);
}


inline raf::Newt::dVector raf::Newt::dMatrix::TransformVector (const raf::Newt::dVector &v) const
{
	return m_posit + RotateVector(v);
}

inline raf::Newt::dVector raf::Newt::dMatrix::UntransformVector (const raf::Newt::dVector &v) const
{
	return UnrotateVector(v - m_posit);
}


inline void raf::Newt::dMatrix::TransformTriplex (
	void* const dstPtr, 
	int dstStrideInBytes,
	void* const srcPtr, 
	int srcStrideInBytes, 
	int count) const
{
	int i;
	dFloat x;
	dFloat y;
	dFloat z;
	dFloat* dst;
	dFloat* src;

	dst = (dFloat*) dstPtr;
	src = (dFloat*) srcPtr;

	dstStrideInBytes /= sizeof (dFloat);
	srcStrideInBytes /= sizeof (dFloat);

	for (i = 0 ; i < count; i ++ ) {
		x = src[0];
		y = src[1];
		z = src[2];
		dst[0] = x * m_front.m_x + y * m_up.m_x + z * m_right.m_x + m_posit.m_x;
		dst[1] = x * m_front.m_y + y * m_up.m_y + z * m_right.m_y + m_posit.m_y;
		dst[2] = x * m_front.m_z + y * m_up.m_z + z * m_right.m_z + m_posit.m_z;
		dst += dstStrideInBytes;
		src += srcStrideInBytes;
	}
}


inline raf::Newt::dMatrix raf::Newt::dMatrix::operator* (const raf::Newt::dMatrix &B) const
{
	const raf::Newt::dMatrix& A = *this;
	return raf::Newt::dMatrix (raf::Newt::dVector (A[0][0] * B[0][0] + A[0][1] * B[1][0] + A[0][2] * B[2][0] + A[0][3] * B[3][0],
							 A[0][0] * B[0][1] + A[0][1] * B[1][1] + A[0][2] * B[2][1] + A[0][3] * B[3][1],
							 A[0][0] * B[0][2] + A[0][1] * B[1][2] + A[0][2] * B[2][2] + A[0][3] * B[3][2],
	                         A[0][0] * B[0][3] + A[0][1] * B[1][3] + A[0][2] * B[2][3] + A[0][3] * B[3][3]),
					raf::Newt::dVector (A[1][0] * B[0][0] + A[1][1] * B[1][0] + A[1][2] * B[2][0] + A[1][3] * B[3][0],
						     A[1][0] * B[0][1] + A[1][1] * B[1][1] + A[1][2] * B[2][1] + A[1][3] * B[3][1],
							 A[1][0] * B[0][2] + A[1][1] * B[1][2] + A[1][2] * B[2][2] + A[1][3] * B[3][2],
							 A[1][0] * B[0][3] + A[1][1] * B[1][3] + A[1][2] * B[2][3] + A[1][3] * B[3][3]),
					raf::Newt::dVector (A[2][0] * B[0][0] + A[2][1] * B[1][0] + A[2][2] * B[2][0] + A[2][3] * B[3][0],
							 A[2][0] * B[0][1] + A[2][1] * B[1][1] + A[2][2] * B[2][1] + A[2][3] * B[3][1],
							 A[2][0] * B[0][2] + A[2][1] * B[1][2] + A[2][2] * B[2][2] + A[2][3] * B[3][2],
							 A[2][0] * B[0][3] + A[2][1] * B[1][3] + A[2][2] * B[2][3] + A[2][3] * B[3][3]),
					raf::Newt::dVector (A[3][0] * B[0][0] + A[3][1] * B[1][0] + A[3][2] * B[2][0] + A[3][3] * B[3][0],
							 A[3][0] * B[0][1] + A[3][1] * B[1][1] + A[3][2] * B[2][1] + A[3][3] * B[3][1],
							 A[3][0] * B[0][2] + A[3][1] * B[1][2] + A[3][2] * B[2][2] + A[3][3] * B[3][2],
							 A[3][0] * B[0][3] + A[3][1] * B[1][3] + A[3][2] * B[2][3] + A[3][3] * B[3][3]));
}


// calculate an orthonormal matrix with the front vector pointing on the 
// dir direction, and the up and right are determined by using the Gramm Schidth procedure
inline raf::Newt::dMatrix dgGrammSchmidt(const raf::Newt::dVector& dir)
{
	raf::Newt::dVector up;
	raf::Newt::dVector right;
	raf::Newt::dVector front (dir); 

	front = front.Scale(1.0f / dSqrt (front % front));
	if (dAbs (front.m_z) > 0.577f) {
		right = front * raf::Newt::dVector (-front.m_y, front.m_z, 0.0f);
	} else {
	  	right = front * raf::Newt::dVector (-front.m_y, front.m_x, 0.0f);
	}
  	right = right.Scale (1.0f / dSqrt (right % right));
  	up = right * front;

	front.m_w = 0.0f;
	up.m_w = 0.0f;
	right.m_w = 0.0f;
	return raf::Newt::dMatrix (front, up, right, raf::Newt::dVector (0.0f, 0.0f, 0.0f, 1.0f));
}

inline raf::Newt::dMatrix dgPitchMatrix(dFloat ang)
{
	dFloat cosAng;
	dFloat sinAng;
	sinAng = dSin (ang);
	cosAng = dCos (ang);
	return raf::Newt::dMatrix (raf::Newt::dVector (1.0f,    0.0f,    0.0f, 0.0f), 
					raf::Newt::dVector (0.0f,  cosAng,  sinAng, 0.0f),
					raf::Newt::dVector (0.0f, -sinAng,  cosAng, 0.0f), 
					raf::Newt::dVector (0.0f,    0.0f,    0.0f, 1.0f)); 

}

inline raf::Newt::dMatrix dgYawMatrix(dFloat ang)
{
	dFloat cosAng;
	dFloat sinAng;
	sinAng = dSin (ang);
	cosAng = dCos (ang);
	return raf::Newt::dMatrix (raf::Newt::dVector (cosAng, 0.0f, -sinAng, 0.0f), 
					raf::Newt::dVector (0.0f,   1.0f,    0.0f, 0.0f), 
					raf::Newt::dVector (sinAng, 0.0f,  cosAng, 0.0f), 
					raf::Newt::dVector (0.0f,   0.0f,    0.0f, 1.0f)); 
}

inline raf::Newt::dMatrix dgRollMatrix(dFloat ang)
{
	dFloat cosAng;
	dFloat sinAng;
	sinAng = dSin (ang);
	cosAng = dCos (ang);
	return raf::Newt::dMatrix (raf::Newt::dVector ( cosAng, sinAng, 0.0f, 0.0f), 
					raf::Newt::dVector (-sinAng, cosAng, 0.0f, 0.0f),
					raf::Newt::dVector (   0.0f,   0.0f, 1.0f, 0.0f), 
					raf::Newt::dVector (   0.0f,   0.0f, 0.0f, 1.0f)); 
}			
															 
#endif
