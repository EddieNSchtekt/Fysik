#include "Boat.h"

Boat::Boat(const float & mass, const Vec & pos, const Vec & vel, const Vec & acc, const Jib & jib, const SailMain & sailMain, const Keel & keel) : PhysicalObject(pos, vel, acc), sailDrag(0.0f, 0.0f, 0.0f), sailLift(0.0f, 0.0f, 0.0f), keelDrag(0.0f, 0.0f, 0.0f), keelLift(0.0f, 0.0f, 0.0f)
{
	this->mass = mass;
	sails = new Sail*[2];
	sails[0] = new Jib(jib);
	sails[1] = new SailMain(sailMain);
	nrOfSails = 2;
	this->keel = new Keel(keel);
	angle = 0;
}

Boat::Boat(const float & mass, const Vec & pos, const Vec & vel, const Vec & acc, const SailMain & sailMain, const Keel & keel, const Keel & rudder) : PhysicalObject(pos, vel, acc), sailDrag(0.0f, 0.0f, 0.0f), sailLift(0.0f, 0.0f, 0.0f), keelDrag(0.0f, 0.0f, 0.0f), keelLift(0.0f, 0.0f, 0.0f)
{
	this->mass = mass;
	sails = new Sail*[1];
	sails[0] = new SailMain(sailMain);
	nrOfSails = 1;
	this->keel = new Keel(keel);
	this->rudder = new Keel(rudder);
	angle = 0;
}

Boat::Boat(const float & mass, const Vec & pos, const Vec & vel, const Vec & acc, const Jib & jib, const Keel & keel) : PhysicalObject(pos, vel, acc), sailDrag(0.0f, 0.0f, 0.0f), sailLift(0.0f, 0.0f, 0.0f), keelDrag(0.0f, 0.0f, 0.0f), keelLift(0.0f, 0.0f, 0.0f)
{
	this->mass = mass;
	sails = new Sail*[1];
	sails[0] = new Jib(jib);
	nrOfSails = 1;
	this->keel = new Keel(keel);
	angle = 0;
}

//TODO!!!! fixa en riktig vinkel mellan segel o vind.
void Boat::windCalc(float time, Vec trueWind)
{
	Vec apparentWind = trueWind - vel;
	
	// viscous drag and lift calculated for a mainsail. Assuming sail is angled as the boat for now.
	float drag = 0;
	float lift = 0;
	float nomArea = 0;

	for (int i = 0; i < nrOfSails; i++)
	{
		drag += sails[i]->CD(apparentWind)*sails[i]->area();
		lift += sails[i]->CL(apparentWind)*sails[i]->area();

		nomArea += sails[i]->area();
	}

	lift = lift / nomArea;
	drag = drag / nomArea;

	float liftForceLength = (float)DENSITY_AIR*lift*sails[0]->area()*(apparentWind).getLength();

	float dragForceLength = (float)DENSITY_AIR*drag*sails[0]->area()*(apparentWind).getLength();

	sailDrag = apparentWind * (dragForceLength/apparentWind.getLength());
	
	sailLift = Vec(apparentWind.getY(), -apparentWind.getX())*(liftForceLength / apparentWind.getLength());
	
	Vec res = sailLift + sailDrag;

	acc = res*(1/mass);

	update(time);
}

void Boat::waterDragCalc(float time)
{
	if (vel.getLength() > 0.000001)
	{
		Vec waterFlow = vel * -1;

		// viscous drag and lift calculated for the keel.
		float drag = 0;
		float lift = 0;

		drag = keel->CD(waterFlow);
		lift = keel->CL(waterFlow);

		float liftForceLength = (float)DENSITY_WATER*lift*keel->area()*(waterFlow).getLength();

		float dragForceLength = (float)DENSITY_WATER*drag*keel->area()*(waterFlow).getLength();

		keelDrag = waterFlow * (dragForceLength / waterFlow.getLength());
		keelLift = Vec(waterFlow.getY(), -waterFlow.getX())*(liftForceLength / waterFlow.getLength());
	}
	
	Vec res = keelDrag + keelLift;

	acc = res * (1 / mass);

	update(time);
}

void Boat::rudderDragCalc(float time)
{
	if (vel.getLength() > 0.000001)
	{
		Vec waterFlow = vel * -1;

		// viscous drag and lift calculated for the keel.
		float drag = 0;
		float lift = 0;

		drag = rudder->CD(waterFlow);
		lift = rudder->CL(waterFlow);

		float liftForceLength = (float)DENSITY_WATER*lift*rudder->area()*(waterFlow).getLength();

		float dragForceLength = (float)DENSITY_WATER*drag*rudder->area()*(waterFlow).getLength();

		rudderDrag = waterFlow * (dragForceLength / waterFlow.getLength());
		rudderLift = Vec(waterFlow.getY(), -waterFlow.getX())*(liftForceLength / waterFlow.getLength());
	}

	Vec res = rudderDrag + rudderLift;

	acc = res * (1 / mass);

	update(time);
}

Vec Boat::getSailDrag() const
{
	return sailDrag;
}

Vec Boat::getSailLift() const
{
	return sailLift;
}

Vec Boat::getKeelDrag() const
{
	return keelDrag;
}

Vec Boat::getKeelLift() const
{
	return keelLift;
}
