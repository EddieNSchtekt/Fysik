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

Vec Sail::getAngle() const
{
	return angle;
}

float Sail::getRotation() const
{
	float res = acos(angle.getX());
	return res;
}

void Sail::setHeight(float newHeight)
{
	height = newHeight;
}

void Sail::setBase(float newBase)
{
	base = newBase;
}

void Sail::setAngle(const Vec & value)
{
	angle = value * (1/sqrtf(value.getX()*value.getX() + value.getY()*value.getY() + value.getZ()*value.getZ()));
}

void Sail::setRotation(const float & value)
{
	angle = Vec(cos(value), -sin(value));
}

void Sail::rotate(const float & value)
{
	angle = Vec(angle.getX()*cos(value) + angle.getY()*sin(value), -angle.getX()*sin(value) + angle.getY()*cos(value));
}
