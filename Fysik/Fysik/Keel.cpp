#include "Keel.h"

Keel::Keel(const Vec & pos, const Vec & vel, const Vec & acc, const float & height, const float & length, const Vec & angle, float chordSmall) :Sail(pos, vel, acc, height, length, angle)
{
	this->chordSmall = chordSmall;
}

Keel::Keel(const Keel & other):Sail(other.pos,other.vel,other.acc,other.height,other.base,other.angle)
{
	this->chordSmall = other.chordSmall;
}

float Keel::area()
{
	float chordMean = (base + chordSmall) / 2;
	return height * chordMean;
}

float Keel::CL(const Vec & waterFlow)
{
	float angle = this->angle.dot(waterFlow);
	angle = angle / (float)sqrt(((waterFlow.getX()*waterFlow.getX() + waterFlow.getY()*waterFlow.getY())*this->angle.getLength()));
	angle = (float)acos(angle) * 360 / (float)(2 * PI);
	angle = 180 - angle;
	float res = 0;

	float chordMean = (base + chordSmall) / 2;

	float aspectRatio = height / chordMean;

	res = 0.11f*angle / (1 + 2 / aspectRatio);

	float cross = (this->angle.crossProd(waterFlow)).getZ();

	if ((cross < 0 && angle < 90) || (cross > 0 && angle > 90))
	{
		res = -res;
	}

	return res;
}

float Keel::CD(const Vec & waterFlow)
{
	float angle = this->angle.dot(waterFlow);
	angle = angle / (float)sqrt(((waterFlow.getX()*waterFlow.getX() + waterFlow.getY()*waterFlow.getY())*this->angle.getLength()));
	angle = (float)acos(angle) * 360 / (2 * (float)PI);
	angle = 180 - angle;
	float res = 0;

	float chordMean = (base + chordSmall) / 2;

	float aspectRatio = height / chordMean;

	res = 0.11f*angle / (1 + 2 / aspectRatio);

	res = res * res / ((float)PI *aspectRatio);
	return res;
}
