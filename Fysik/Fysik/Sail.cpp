#include "Sail.h"

Sail::Sail(const Vec & pos, const Vec & vel, const Vec & acc, const float & height, const float & base, const Vec & angle) : PhysicalObject(pos, vel, acc)
{
	this->height = height;
	this->base = base;
	this->angle = angle;
}

float Sail::getHeight()
{
	return height;
}

float Sail::getBase()
{
	return base;
}

void Sail::setHeight(float newHeight)
{
	height = newHeight;
}

void Sail::setBase(float newBase)
{
	base = newBase;
}
