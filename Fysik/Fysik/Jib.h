#ifndef JIB_H
#define JIB_H

#include "Sail.h"

class Jib:public Sail 
{
private:
	float lpg;
public:
	Jib(const Vec & pos, const Vec & vel, const Vec & acc, const float & height, const float & base, const Vec & angle, const float & LPG);
	float area();
	float CL(const Vec & apparentWind);
	float CD(const Vec & apparentWind);
};

#endif