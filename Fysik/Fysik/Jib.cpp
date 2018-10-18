#include "Jib.h"

Jib::Jib(const Vec & pos, const Vec & vel, const Vec & acc, const float & height, const float & base, const Vec & angle, const float & LPG):Sail(pos, vel, acc, height,base, angle)
{
	lpg = LPG;
}

float Jib::area()
{
	return 0.5f*(float)sqrt(height*height + base*base)*lpg;
}

float Jib::CL(const Vec & apparentWind)
{
	float angle = this->angle.dot(apparentWind);
	angle = angle / (float)sqrt(((apparentWind.getX()*apparentWind.getX() + apparentWind.getY()*apparentWind.getY())*this->angle.getLength()));
	angle = (float)acos(angle) * 360 / (float)(2 * PI);

	float res = 0;

	if (angle < 27 || angle > 100)
	{
		res = 0;
	}
	else
	{
		res = 5.8904257305f - 0.2654715271f*angle - 0.0047059949f*angle*angle + 0.0000357062f*angle*angle*angle - 0.000000093f*angle*angle*angle*angle; // Regression made from geogebra
	}
	return res;
}

float Jib::CD(const Vec & apparentWind)
{
	float angle = this->angle.dot(apparentWind);
	angle = angle / (float)sqrt(((apparentWind.getX()*apparentWind.getX() + apparentWind.getY()*apparentWind.getY())*this->angle.getLength()));
	angle = (float)acos(angle) * 360 / (float)(2 * PI);

	float res = 0;

	if (angle > 27 && angle < 100)
	{
		res = -0.915232051f + 0.0527800616f*angle - 0.0007782523f*angle*angle + 0.00000413f*angle*angle*angle - 0.0000000071f*angle*angle*angle*angle;
	}
	else
	{
		res = 0;
	}
	return res;
}
