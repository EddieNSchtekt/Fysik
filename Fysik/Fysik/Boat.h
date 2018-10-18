#ifndef BOAT_H
#define BOAT_H

#include "SailMain.h"
#include "Jib.h"
#include "Keel.h"

#define DENSITY_AIR 1.22
#define DENSITY_WATER 997.f

class Boat : public PhysicalObject
{
private:
	float mass;
	Sail ** sails; // max size = 2
	int nrOfSails;
	Keel *keel;
	Keel *rudder;

	Vec sailLift;
	Vec sailDrag;

	Vec keelLift;
	Vec keelDrag;

	Vec rudderDrag;
	Vec rudderLift;

	float angle;
public:
	Boat(const float & mass, const Vec & pos, const Vec & vel, const Vec & acc, const Jib & jib, const SailMain & sailMain, const Keel & keel);

	Boat(const float & mass, const Vec & pos, const Vec & vel, const Vec & acc, const SailMain & sailMain, const Keel & keel, const Keel & rudder);
	
	Boat(const float & mass, const Vec & pos, const Vec & vel, const Vec & acc, const Jib & jib, const Keel & keel);

	void windCalc(float time, Vec trueWind);

	void waterDragCalc(float time);

	void rudderDragCalc(float time);

	Vec getSailDrag() const;
	Vec getSailLift() const;

	Vec getKeelDrag() const;
	Vec getKeelLift() const;
};

#endif
