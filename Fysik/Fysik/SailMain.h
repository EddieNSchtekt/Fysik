#ifndef SAILMAIN_H
#define SAILMAIN_H

#include "Sail.h"

class SailMain : public Sail
{
public:
	SailMain(const Vec & pos, const Vec & vel, const Vec & acc, const float & height, const float & base, const Vec & angle);
	float area();
	float CL(const Vec & apparentWind);
	float CD(const Vec & apparentWind);
};
#endif