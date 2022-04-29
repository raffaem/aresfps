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
#ifndef __dQuaternion__
#define __dQuaternion__

namespace raf{
	namespace Newt{
		class dMatrix;

class dQuaternion
{
	public:
	dQuaternion (); 
	dQuaternion (const raf::Newt::dMatrix &matrix);
	dQuaternion (dFloat q0, dFloat q1, dFloat q2, dFloat q3); 
	dQuaternion (const dVector &unit_Axis, dFloat Angle = 0.0f);
	
	void Scale (dFloat scale); 
	void Normalize (); 
	inline dFloat DotProduct (const dQuaternion &QB) const;
	dQuaternion Inverse () const; 

	dQuaternion Slerp (const dQuaternion &q1, dFloat t) const;
	dVector CalcAverageOmega (const dQuaternion &q1, dFloat dt) const;

//	friend dQuaternion operator* (const dQuaternion &A, const dQuaternion &B);
//	friend dQuaternion operator+ (const dQuaternion &A, const dQuaternion &B); 
//  friend dQuaternion operator- (const dQuaternion &A, const dQuaternion &B); 

	dQuaternion operator* (const dQuaternion &B) const;
	dQuaternion operator+ (const dQuaternion &B) const; 
	dQuaternion operator- (const dQuaternion &B) const; 

	dFloat m_q1;
	dFloat m_q2;
	dFloat m_q3;
	dFloat m_q0;
};
	}
}




inline raf::Newt::dQuaternion::dQuaternion () 
{
	m_q0 = 1.0f;
	m_q1 = 0.0f;
	m_q2 = 0.0f;
	m_q3 = 0.0f;
}

inline raf::Newt::dQuaternion::dQuaternion (dFloat Q0, dFloat Q1, dFloat Q2, dFloat Q3) 
{
	m_q0 = Q0;
	m_q1 = Q1;
	m_q2 = Q2;
	m_q3 = Q3;
	_ASSERTE (dAbs (DotProduct (*this) - 1.0f) < 1.0e-4f);
}



inline void raf::Newt::dQuaternion::Scale (dFloat scale) 
{
	m_q0 *= scale;
	m_q1 *= scale;
	m_q2 *= scale;
	m_q3 *= scale;
}

inline void raf::Newt::dQuaternion::Normalize () 
{
	Scale (1.0f / dSqrt (DotProduct (*this)));
}

inline dFloat raf::Newt::dQuaternion::DotProduct (const dQuaternion &QB) const
{
	return m_q0 * QB.m_q0 + m_q1 * QB.m_q1 + m_q2 * QB.m_q2 + m_q3 * QB.m_q3;
}

inline raf::Newt::dQuaternion raf::Newt::dQuaternion::Inverse () const 
{
	return raf::Newt::dQuaternion (m_q0, -m_q1, -m_q2, -m_q3);
}

/*
inline dQuaternion operator+ (const dQuaternion &A, const dQuaternion &B) 
{
	return dQuaternion (A.m_q0 + B.m_q0, A.m_q1 + B.m_q1, A.m_q2 + B.m_q2, A.m_q3 + B.m_q3);
}

inline dQuaternion operator- (const dQuaternion &A, const dQuaternion &B) 
{
	return dQuaternion (A.m_q0 - B.m_q0, A.m_q1 - B.m_q1, A.m_q2 - B.m_q2, A.m_q3 - B.m_q3);
}
*/

inline raf::Newt::dQuaternion raf::Newt::dQuaternion::operator+ (const dQuaternion &B) const
{
	return dQuaternion (m_q0 + B.m_q0, m_q1 + B.m_q1, m_q2 + B.m_q2, m_q3 + B.m_q3);
}

inline raf::Newt::dQuaternion raf::Newt::dQuaternion::operator- (const dQuaternion &B) const
{
	return dQuaternion (m_q0 - B.m_q0, m_q1 - B.m_q1, m_q2 - B.m_q2, m_q3 - B.m_q3);
}


inline raf::Newt::dQuaternion raf::Newt::dQuaternion::operator* (const dQuaternion &B) const
{
	return dQuaternion (B.m_q0 * m_q0 - B.m_q1 * m_q1 - B.m_q2 * m_q2 - B.m_q3 * m_q3, 
				 		 B.m_q1 * m_q0 + B.m_q0 * m_q1 - B.m_q3 * m_q2 + B.m_q2 * m_q3, 
						 B.m_q2 * m_q0 + B.m_q3 * m_q1 + B.m_q0 * m_q2 - B.m_q1 * m_q3, 
						 B.m_q3 * m_q0 - B.m_q2 * m_q1 + B.m_q1 * m_q2 + B.m_q0 * m_q3); 
}


#endif 
