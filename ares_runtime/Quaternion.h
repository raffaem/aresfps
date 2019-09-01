// Quaternion.h: interface for the Quaternion class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_QUATERNION_H__08B67C6E_2133_4968_AFBD_786DC124D55C__INCLUDED_
#define AFX_QUATERNION_H__08B67C6E_2133_4968_AFBD_786DC124D55C__INCLUDED_

#include <irrlicht.h>

class Quaternion {

public:
	float	n;	// number (scalar) part
	irr::core::vector3df	v;	// vector part: v.X, v.Y, v.Z

	Quaternion(void);
	Quaternion(float e0, float e1, float e2, float e3);

	float	Magnitude(void);
	irr::core::vector3df	Getvector3df(void);
	float	GetScalar(void);
	Quaternion	operator+=(Quaternion q);
	Quaternion	operator-=(Quaternion q);
	Quaternion operator*=(float s);
	Quaternion operator/=(float s);
	Quaternion	operator~(void) const { return Quaternion(n, -v.X, -v.Y, -v.Z);}
 
};


/*	Quaternion	Quaternion::operator~()
{
	return Quaternion(n, -v.X, -v.Y, -v.Z);
}*/



 	Quaternion operator+(Quaternion q1, Quaternion q2);
	Quaternion operator-(Quaternion q1, Quaternion q2);
 	Quaternion operator*(Quaternion q1, Quaternion q2);
	Quaternion operator*(Quaternion q, float s);
	Quaternion operator*(float s, Quaternion q);
	Quaternion operator*(Quaternion q, irr::core::vector3df v);
	Quaternion operator*(irr::core::vector3df v, Quaternion q);
	Quaternion operator/(Quaternion q, float s);
	float QGetAngle(Quaternion q);
	irr::core::vector3df QGetAxis(Quaternion q);
	Quaternion QRotate(Quaternion q1, Quaternion q2);
	irr::core::vector3df	QVRotate(Quaternion q, irr::core::vector3df v);
	Quaternion	MakeQFromEulerAngles(float x, float y, float z);
	irr::core::vector3df	MakeEulerAnglesFromQ(Quaternion q);

#endif // !defined(AFX_QUATERNION_H__08B67C6E_2133_4968_AFBD_786DC124D55C__INCLUDED_)
