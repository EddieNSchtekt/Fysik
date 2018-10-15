#ifndef PHYSICALOBJECT_H
#define PHYSICALOBJECT_H
#include "Vec.h"
class PhysicalObject
{
protected:
	Vec pos;
	Vec vel;
	Vec acc;
public:
	PhysicalObject(const Vec & pos, const Vec & vel, const Vec & acc);
	void update(float t);

	// gets
	Vec getPos() const;
	Vec getVel() const;
	Vec getAcc() const;

	// sets
	void setPos(const Vec & val);
	void setVel(const Vec & val);
	void setAcc(const Vec & val);
};

#endif