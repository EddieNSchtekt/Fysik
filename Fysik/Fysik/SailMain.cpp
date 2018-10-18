#include "SailMain.h"

SailMain::SailMain(const Vec & pos, const Vec & vel, const Vec & acc, const float & height, const float & length, const Vec & angle):Sail(pos, vel, acc, height, length, angle)
{
}

float SailMain::area()
{
	return height*base/2;
}

float SailMain::CL(const Vec & apparentWind)
{
	float angle = this->angle.dot(apparentWind);
	angle = angle / sqrt(((apparentWind.getX()*apparentWind.getX() + apparentWind.getY()*apparentWind.getY())*this->angle.getLength()));
	angle = acos(angle)*360/(2* PI);
	angle = 180 - angle;
	float res = 0;
	if (angle < 100 && angle > 27)
		res = -0.4745031571f + 0.1382159744f*angle - 0.0030069261f*angle*angle + 0.0000237741f*angle*angle*angle - 0.0000000625f*angle*angle*angle*angle; // Regression made from geogebra
	else if (angle > 100 && angle < 180)
		res = 1.8f - 0.01f*angle; //regression made from geogebra
	else if (angle < 27)
		res = 1.5f;
	else
		res = 0.00f;

	float cross = (this->angle.crossProd(apparentWind)).getZ();
	if (cross < 0 && angle < 90 || cross > 0 && angle > 90)
	{
		res = -res;
	}

	return res;
}

float SailMain::CD(const Vec & apparentWind)
{
	float angle = this->angle.dot(apparentWind);
	angle = angle / sqrt(((apparentWind.getX()*apparentWind.getX() + apparentWind.getY()*apparentWind.getY())*this->angle.getLength()));
	angle = acos(angle) * 360 / (2 * PI);
	angle = 180 - angle;
	float res = 0;

	if (angle > 50 && angle < 100)
	{
		res = 1.6509575627f - 0.1191069136f * angle + 0.0027076357f * angle * angle - 0.0000212186f * angle * angle * angle + 0.000000054f*angle*angle*angle*angle;
	}
	else if (angle < 50 && angle > 27)
	{
		res = -0.1326086957f + 0.00656521739f*angle;
	}
	else if (angle > 100)
	{
		res = 1.125f - 0.00125f*angle;
	}
	else
	{
		res = 0.02;
	}
	return res;
}
