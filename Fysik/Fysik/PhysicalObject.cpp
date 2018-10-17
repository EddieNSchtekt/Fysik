#include "PhysicalObject.h"

PhysicalObject::PhysicalObject(const Vec & pos, const Vec & vel, const Vec & acc)
{
	this->pos = pos;
	this->vel = vel;
	this->acc = acc;
}

void PhysicalObject::update(float t)
{
	pos += vel * t;
	vel += acc * t;
}

Vec PhysicalObject::getPos() const
{
	return pos;
}

Vec PhysicalObject::getVel() const
{
	return vel;
}

Vec PhysicalObject::getAcc() const
{
	return acc;
}

void PhysicalObject::setPos(const Vec & val)
{
	pos = val;
}

void PhysicalObject::setVel(const Vec & val)
{
	vel = val;
}

void PhysicalObject::setAcc(const Vec & val)
{
	acc = val;
}
