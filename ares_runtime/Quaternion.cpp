#include "Quaternion.h"
#include "Phisics_math_functions.h"
float tol = 0.0001f;		// float type tolerance 


Quaternion::Quaternion(void)
{
	n = 0;
	v.X = 0;
	v.Y =  0;
	v.Z = 0;

}

	Quaternion::Quaternion(float e0, float e1, float e2, float e3)
{
	n = e0;
	v.X = e1;
	v.Y = e2;
	v.Z = e3;
}

	float	Quaternion::Magnitude(void)
{
	return (float) sqrt(n*n + v.X*v.X + v.Y*v.Y + v.Z*v.Z);
}

	irr::core::vector3df	Quaternion::Getvector3df(void)
{
	return irr::core::vector3df(v.X, v.Y, v.Z);
}

	float	Quaternion::GetScalar(void)
{
	return n;
}

	Quaternion	Quaternion::operator+=(Quaternion q)
{
	n += q.n;
	v.X += q.v.X;
	v.Y += q.v.Y;
	v.Z += q.v.Z;
	return *this;
}

	Quaternion	Quaternion::operator-=(Quaternion q)
{
	n -= q.n;
	v.X -= q.v.X;
	v.Y -= q.v.Y;
	v.Z -= q.v.Z;
	return *this;
}

	Quaternion Quaternion::operator*=(float s)
{
	n *= s;
	v.X *= s;
	v.Y *= s;
	v.Z *= s;
	return *this;
}

	Quaternion Quaternion::operator/=(float s)
{
	n /= s;
	v.X /= s;
	v.Y /= s;
	v.Z /= s;
	return *this;
}
//--------------------------------------------------------------
 	Quaternion operator+(Quaternion q1, Quaternion q2)

 
{
	return	Quaternion(	q1.n + q2.n,
							q1.v.X + q2.v.X,
							q1.v.Y + q2.v.Y,
							q1.v.Z + q2.v.Z);
}

	Quaternion operator-(Quaternion q1, Quaternion q2)
{
	return	Quaternion(	q1.n - q2.n,
							q1.v.X - q2.v.X,
							q1.v.Y - q2.v.Y,
							q1.v.Z - q2.v.Z);
}
 
	Quaternion operator*(Quaternion q1, Quaternion q2)
{
	return	Quaternion(	q1.n*q2.n - q1.v.X*q2.v.X - q1.v.Y*q2.v.Y - q1.v.Z*q2.v.Z,
							q1.n*q2.v.X + q1.v.X*q2.n + q1.v.Y*q2.v.Z - q1.v.Z*q2.v.Y,
							q1.n*q2.v.Y + q1.v.Y*q2.n + q1.v.Z*q2.v.X - q1.v.X*q2.v.Z,
							q1.n*q2.v.Z + q1.v.Z*q2.n + q1.v.X*q2.v.Y - q1.v.Y*q2.v.X);							
}
 
	Quaternion operator*(Quaternion q, float s)
{
	return	Quaternion(q.n*s, q.v.X*s, q.v.Y*s, q.v.Z*s);
}

	Quaternion operator*(float s, Quaternion q)
{
	return	Quaternion(q.n*s, q.v.X*s, q.v.Y*s, q.v.Z*s);
}

	Quaternion operator*(Quaternion q, irr::core::vector3df v)
{
	return	Quaternion(	-(q.v.X*v.X + q.v.Y*v.Y + q.v.Z*v.Z),
							q.n*v.X + q.v.Y*v.Z - q.v.Z*v.Y,
							q.n*v.Y + q.v.Z*v.X - q.v.X*v.Z,
							q.n*v.Z + q.v.X*v.Y - q.v.Y*v.X);
}

	Quaternion operator*(irr::core::vector3df v, Quaternion q)
{
	return	Quaternion(	-(q.v.X*v.X + q.v.Y*v.Y + q.v.Z*v.Z),
							q.n*v.X + q.v.Z*v.Y - q.v.Y*v.Z,
							q.n*v.Y + q.v.X*v.Z - q.v.Z*v.X,
							q.n*v.Z + q.v.Y*v.X - q.v.X*v.Y);
}

	Quaternion operator/(Quaternion q, float s)
{
	return	Quaternion(q.n/s, q.v.X/s, q.v.Y/s, q.v.Z/s);
}

	float QGetAngle(Quaternion q)
{
	return	(float) (2*acos(q.n));
}

	irr::core::vector3df QGetAxis(Quaternion q)
{
	irr::core::vector3df v;
	float m;

	v = q.Getvector3df();
	m = (float) v.getLength();
	
	if (m <= tol)
		return irr::core::vector3df();
	else
		return v/m;	
}

	Quaternion QRotate(Quaternion q1, Quaternion q2)
{
	return	q1*q2*(~q1);
}

	irr::core::vector3df	QVRotate(Quaternion q, irr::core::vector3df v)
{
	Quaternion t;


	t = q*v*(~q);

	return	t.Getvector3df();
}

	/*
Quaternion	MakeQFromEulerAngles(float x, float y, float z)
{
	Quaternion	q;
	double	roll = DegreesToRadians(x);
	double	pitch = DegreesToRadians(y);
	double	yaw = DegreesToRadians(z);
	
	double	cyaw, cpitch, croll, syaw, spitch, sroll;
	double	cyawcpitch, syawspitch, cyawspitch, syawcpitch;

	cyaw = cos(0.5f * yaw);
	cpitch = cos(0.5f * pitch);
	croll = cos(0.5f * roll);
	syaw = sin(0.5f * yaw);
	spitch = sin(0.5f * pitch);
	sroll = sin(0.5f * roll);

	cyawcpitch = cyaw*cpitch;
	syawspitch = syaw*spitch;
	cyawspitch = cyaw*spitch;
	syawcpitch = syaw*cpitch;

	q.n = (float) (cyawcpitch * croll + syawspitch * sroll);
	q.v.X = (float) (cyawcpitch * sroll - syawspitch * croll); 
	q.v.Y = (float) (cyawspitch * croll + syawcpitch * sroll);
	q.v.Z = (float) (syawcpitch * croll - cyawspitch * sroll);

	return q;
}

irr::core::vector3df	MakeEulerAnglesFromQ(Quaternion q)
{
	double	r11, r21, r31, r32, r33, r12, r13;
	double	q00, q11, q22, q33;
	double	tmp;
	irr::core::vector3df	u;

	q00 = q.n * q.n;
	q11 = q.v.X * q.v.X;
	q22 = q.v.Y * q.v.Y;
	q33 = q.v.Z * q.v.Z;

	r11 = q00 + q11 - q22 - q33;
	r21 = 2 * (q.v.X*q.v.Y + q.n*q.v.Z);
	r31 = 2 * (q.v.X*q.v.Z - q.n*q.v.Y);
	r32 = 2 * (q.v.Y*q.v.Z + q.n*q.v.X);
	r33 = q00 - q11 - q22 + q33;

	tmp = fabs(r31);
	if(tmp > 0.999999)
	{
		r12 = 2 * (q.v.X*q.v.Y - q.n*q.v.Z);
		r13 = 2 * (q.v.X*q.v.Z + q.n*q.v.Y);

		u.X = RadiansToDegrees(0.0f); //roll
		u.Y = RadiansToDegrees((float) (-(PI/2) * r31/tmp)); // pitch
		u.Z = RadiansToDegrees((float) atan2(-r12, -r31*r13)); // yaw
		return u;
	}

	u.X = RadiansToDegrees((float) atan2(r32, r33)); // roll
	u.Y = RadiansToDegrees((float) asin(-r31));		 // pitch
	u.Z = RadiansToDegrees((float) atan2(r21, r11)); // yaw
	return u;
}
*/
