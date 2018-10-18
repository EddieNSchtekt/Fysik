#include "Keel.h"

Keel::Keel(const Vec & pos, const Vec & vel, const Vec & acc, const float & height, const float & length, const Vec & angle) :Sail(pos, vel, acc, height, length, angle)
{
}

float Keel::area()
{
	float draft = 1.3;
	float chord1 = 1.3;
	float chord2 = 0.7;

	float chordMean = (chord1 + chord2) / 2;
	return draft * chordMean;
}

float Keel::CL(const Vec & waterFlow)
{
	float angle = this->angle.dot(waterFlow);
	angle = angle / sqrt(((waterFlow.getX()*waterFlow.getX() + waterFlow.getY()*waterFlow.getY())*this->angle.getLength()));
	angle = acos(angle) * 360 / (2 * PI);
	angle = 180 - angle;
	float res = 0;

	float draft = 1.3;
	float chord1 = 1.3;
	float chord2 = 0.7;

	float chordMean = (chord1 + chord2) / 2;

	float aspectRatio = draft / chordMean;

	res = 0.11*angle / (1 + 2 / aspectRatio);

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
	angle = angle / sqrt(((waterFlow.getX()*waterFlow.getX() + waterFlow.getY()*waterFlow.getY())*this->angle.getLength()));
	angle = acos(angle) * 360 / (2 * PI);
	angle = 180 - angle;
	float res = 0;


	float draft = 1.3;
	float chord1 = 1.3;
	float chord2 = 0.7;

	float chordMean = (chord1 + chord2) / 2;

	float aspectRatio = draft / chordMean;

	res = 0.11*angle / (1 + 2 / aspectRatio);

	res = res * res / (PI *aspectRatio);
	return res;
}
