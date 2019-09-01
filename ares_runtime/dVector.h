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
#ifndef __dVector__
#define __dVector__

#include <Newton.h>

namespace raf{
	namespace Newt{
// small but very effective 4 dimetional template vector class 

template<class T>
class TemplateVector
{
	public:
	TemplateVector ();
	TemplateVector (const T *ptr);
	TemplateVector (T m_x, T m_y, T m_z, T m_w); 
	TemplateVector Scale (T s) const;

	T& operator[] (int i);
	const T& operator[] (int i) const;

	TemplateVector operator+ (const TemplateVector &A) const; 
	TemplateVector operator- (const TemplateVector &A) const; 
	TemplateVector &operator+= (const TemplateVector &A);
	TemplateVector &operator-= (const TemplateVector &A); 

	// return dot product
	T operator% (const TemplateVector &A) const; 

	// return cross product
	TemplateVector operator* (const TemplateVector &B) const; 

	// component wise multiplication
	TemplateVector CompProduct (const TemplateVector &A) const;

	T m_x;
	T m_y;
	T m_z;
	T m_w;
};


class dVector: public raf::Newt::TemplateVector<dFloat>
{
	public:
	dVector();
	dVector (const TemplateVector<dFloat>& v);
	dVector (const dFloat *ptr);
	dVector (dFloat x, dFloat y, dFloat z, dFloat w = 1.0); 
};
	}
}





template<class T>
raf::Newt::TemplateVector<T>::TemplateVector() {}

template<class T>
raf::Newt::TemplateVector<T>::TemplateVector(const T *ptr)
{
	m_x = ptr[0];
	m_y = ptr[1];
	m_z = ptr[2];
	m_w = 1.0;
}

template<class T>
raf::Newt::TemplateVector<T>::TemplateVector(T x, T y, T z, T w) 
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_w = w;
}


template<class T>
T& raf::Newt::TemplateVector<T>::operator[] (int i)
{
	return (&m_x)[i];
}	

template<class T>
const T& raf::Newt::TemplateVector<T>::operator[] (int i) const
{
	return (&m_x)[i];
}

template<class T>
raf::Newt::TemplateVector<T> raf::Newt::TemplateVector<T>::Scale (T scale) const
{
	return raf::Newt::TemplateVector<T> (m_x * scale, m_y * scale, m_z * scale, m_w);
}


template<class T>
raf::Newt::TemplateVector<T> raf::Newt::TemplateVector<T>::operator+ (const TemplateVector<T> &B) const
{
	return raf::Newt::TemplateVector<T> (m_x + B.m_x, m_y + B.m_y, m_z + B.m_z, m_w);
}

template<class T>
raf::Newt::TemplateVector<T>& raf::Newt::TemplateVector<T>::operator+= (const TemplateVector<T> &A) 
{
	m_x += A.m_x;
	m_y += A.m_y;
	m_z += A.m_z;
	return *this;
}

template<class T>
raf::Newt::TemplateVector<T> raf::Newt::TemplateVector<T>::operator- (const TemplateVector<T> &A) const
{
	return TemplateVector<T> (m_x - A.m_x, m_y - A.m_y, m_z - A.m_z, m_w);
}

template<class T>
raf::Newt::TemplateVector<T>& raf::Newt::TemplateVector<T>::operator-= (const TemplateVector<T> &A) 
{
	m_x -= A.m_x;
	m_y -= A.m_y;
	m_z -= A.m_z;
	return *this;
}


template<class T>
T raf::Newt::TemplateVector<T>::operator% (const raf::Newt::TemplateVector<T> &A) const
{
	return m_x * A.m_x + m_y * A.m_y + m_z * A.m_z;
}


template<class T>
raf::Newt::TemplateVector<T> raf::Newt::TemplateVector<T>::operator* (const raf::Newt::TemplateVector<T> &B) const
{
	return raf::Newt::TemplateVector<T> (m_y * B.m_z - m_z * B.m_y,
 							    m_z * B.m_x - m_x * B.m_z,
								m_x * B.m_y - m_y * B.m_x, m_w);
}



template<class T>
raf::Newt::TemplateVector<T> raf::Newt::TemplateVector<T>::CompProduct (const TemplateVector<T> &A) const
{
	return TemplateVector<T> (m_x * A.m_x, m_y * A.m_y, m_z * A.m_z, A.m_w);
}



inline raf::Newt::dVector::dVector()
	:raf::Newt::TemplateVector<dFloat>()
{
}

inline raf::Newt::dVector::dVector (const TemplateVector<dFloat>& v)
	:raf::Newt::TemplateVector<dFloat>(v)
{
}

inline raf::Newt::dVector::dVector (const dFloat *ptr)
	:raf::Newt::TemplateVector<dFloat>(ptr)
{
}

inline raf::Newt::dVector::dVector (dFloat x, dFloat y, dFloat z, dFloat w) 
	:raf::Newt::TemplateVector<dFloat>(x, y, z, w)
{
}

#endif
