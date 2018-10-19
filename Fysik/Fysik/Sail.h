#ifndef SAIL_H
#define SAIL_H

#include "PhysicalObject.h"
class Sail: public PhysicalObject
{
protected:
	Vec angle;
	float height;
	float base;
public:
	Sail(const Vec & pos, const Vec & vel, const Vec & acc, const float & height,const float & base, const Vec & angle);
	virtual float area() = 0;
	virtual float CL(const Vec & angle) = 0;
	virtual float CD(const Vec & angle) = 0;

	//get functions
	float getHeight();
	float getBase();
	Vec getAngle() const;
	float getRotation() const;

	//set functions
	void setHeight(float newHeight);
	void setBase(float newLength);
	void setAngle(const Vec & value);
	void setRotation(const float & value);
	void rotate(const float & value);
};

#endif