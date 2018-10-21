#ifndef BOAT_H
#define BOAT_H

#include "SailMain.h"
#include "Jib.h"
#include "Keel.h"

#define DENSITY_AIR 1.22
#define DENSITY_WATER 1025.f

class Boat : public PhysicalObject
{
private:
	float mass;
	Sail ** sails; // max size = 2
	int nrOfSails;
	int mainSail;
	Keel *keel;
	Keel * rudder;

	Vec sailLift;
	Vec sailDrag;

	Vec keelLift;
	Vec keelDrag;

public:
	Boat(const float & mass, const Vec & pos, const Vec & vel, const Vec & acc, const Jib & jib, const SailMain & sailMain, const Keel & keel, const Keel & rudder);

	Boat(const float & mass, const Vec & pos, const Vec & vel, const Vec & acc, const SailMain & sailMain, const Keel & keel, const Keel & rudder);
	
	Boat(const float & mass, const Vec & pos, const Vec & vel, const Vec & acc, const Jib & jib, const Keel & keel, const Keel & rudder);

	Vec windCalc(Vec trueWind);

	Vec waterDragCalc();

	Vec hullResistance();

	void calcForce(float time, Vec trueWind);

	Vec getSailDrag() const;
	Vec getSailLift() const;

	Vec getKeelDrag() const;
	Vec getKeelLift() const;

	Vec getMainSailAngle() const;
	void setMainSailAngle(Vec angle);
};

#endif
