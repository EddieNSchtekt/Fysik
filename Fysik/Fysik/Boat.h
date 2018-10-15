#ifndef BOAT_H
#define BOAT_H
#include "SailMain.h"
#include "Jib.h"
class Boat : public PhysicalObject
{
private:
	float mass;
	Sail ** sails; // max size = 2
	int nrOfSails;
public:
	Boat(const float & mass, const Vec & pos, const Vec & vel, const Vec & acc, const Jib & jib, const SailMain & sailMain);

	Boat(const float & mass, const Vec & pos, const Vec & vel, const Vec & acc, const SailMain & sailMain);
	
	Boat(const float & mass, const Vec & pos, const Vec & vel, const Vec & acc, const Jib & jib);

	void windCalc(float time, Vec trueWind);
};

#endif
