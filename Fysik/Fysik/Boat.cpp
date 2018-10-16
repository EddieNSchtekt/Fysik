#include "Boat.h"

Boat::Boat(const float & mass, const Vec & pos, const Vec & vel, const Vec & acc, const Jib & jib, const SailMain & sailMain, const Keel & keel) : PhysicalObject(pos, vel, acc)
{
	this->mass = mass;
	sails = new Sail*[2];
	sails[0] = new Jib(jib);
	sails[1] = new SailMain(sailMain);
	nrOfSails = 2;
	this->keel = new Keel(keel);
}

Boat::Boat(const float & mass, const Vec & pos, const Vec & vel, const Vec & acc, const SailMain & sailMain, const Keel & keel) : PhysicalObject(pos, vel, acc)
{
	this->mass = mass;
	sails = new Sail*[1];
	sails[0] = new SailMain(sailMain);
	nrOfSails = 1;
	this->keel = new Keel(keel);
}

Boat::Boat(const float & mass, const Vec & pos, const Vec & vel, const Vec & acc, const Jib & jib, const Keel & keel) : PhysicalObject(pos, vel, acc)
{
	this->mass = mass;
	sails = new Sail*[1];
	sails[0] = new Jib(jib);
	nrOfSails = 1;
	this->keel = new Keel(keel);
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

	Vec dragForce = apparentWind * (dragForceLength/apparentWind.getLength());
	Vec liftForce = Vec(-apparentWind.getY(), apparentWind.getX())*(liftForceLength / apparentWind.getLength());
	
	Vec res = liftForce + dragForce;

	acc = res*(1/mass);

	update(time);
}

void Boat::waterDragCalc(float time)
{
	Vec waterFlow = vel * -1;

	// viscous drag and lift calculated for the keel.
	float drag = 0;
	float lift = 0;

	drag = keel->CD(waterFlow);
	lift = keel->CL(waterFlow);

	float liftForceLength = (float)DENSITY_WATER*lift*keel->area()*(waterFlow).getLength();

	float dragForceLength = (float)DENSITY_WATER*drag*keel->area()*(waterFlow).getLength();

	Vec dragForce = waterFlow * (dragForceLength / waterFlow.getLength());
	Vec liftForce = Vec(-waterFlow.getY(), waterFlow.getX())*(liftForceLength / waterFlow.getLength());

	Vec res = liftForce + dragForce;

	acc = res * (1 / mass);

	update(time);

}
