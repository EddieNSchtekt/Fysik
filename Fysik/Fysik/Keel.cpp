#include "Keel.h"

Keel::Keel(const Vec & pos, const Vec & vel, const Vec & acc, const float & draft, const float & chord1, const float & chord2, const Vec & angle) :Sail(pos, vel, acc, draft, chord1, angle)
{
	this->draft = draft;
	this->chord1 = chord1;
	this->chord2 = chord2;
}

float Keel::area()
{
	float chordMean = (chord1 + chord2) / 2;
	return draft * chordMean;
}

float Keel::CL(const Vec & waterFlow)
{
	float angle = this->angle.dot(waterFlow);
	angle = angle / (sqrt(waterFlow.getX()*waterFlow.getX() + waterFlow.getY()*waterFlow.getY())*this->angle.getLength());
	angle = acos(angle) * 360 / (2 * PI);
	angle = 180 - angle;
	float res = 0;

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
	angle = angle / (sqrt(waterFlow.getX()*waterFlow.getX() + waterFlow.getY()*waterFlow.getY())*this->angle.getLength());
	angle = acos(angle) * 360 / (2 * PI);
	angle = 180 - angle;
	float res = 0;

	float chordMean = (chord1 + chord2) / 2;

	float aspectRatio = draft / chordMean;

	res = 0.11*angle / (1 + 2 / aspectRatio);

	res = res * res / (PI *aspectRatio);
	return res;
}
