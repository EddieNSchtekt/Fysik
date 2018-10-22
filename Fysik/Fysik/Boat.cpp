#include "Boat.h"

Boat::Boat(const float & mass, const Vec & pos, const Vec & vel, const Vec & acc, const Jib & jib, const SailMain & sailMain, const Keel & keel, const Keel & rudder) : PhysicalObject(pos, vel, acc), sailDrag(0.0f, 0.0f, 0.0f), sailLift(0.0f, 0.0f, 0.0f), keelDrag(0.0f, 0.0f, 0.0f), keelLift(0.0f, 0.0f, 0.0f)
{
	this->mass = mass;
	sails = new Sail*[2];
	sails[0] = new Jib(jib);
	sails[1] = new SailMain(sailMain);
	nrOfSails = 2;
	mainSail = 1;
	this->keel = new Keel(keel);
	this->rudder = new Keel(rudder);
}

Boat::Boat(const float & mass, const Vec & pos, const Vec & vel, const Vec & acc, const SailMain & sailMain, const Keel & keel, const Keel & rudder) : PhysicalObject(pos, vel, acc), sailDrag(0.0f, 0.0f, 0.0f), sailLift(0.0f, 0.0f, 0.0f), keelDrag(0.0f, 0.0f, 0.0f), keelLift(0.0f, 0.0f, 0.0f)
{
	this->mass = mass;
	sails = new Sail*[1];
	sails[0] = new SailMain(sailMain);
	nrOfSails = 1;
	mainSail = 0;
	this->keel = new Keel(keel);
	this->rudder = new Keel(rudder);
}

Boat::Boat(const float & mass, const Vec & pos, const Vec & vel, const Vec & acc, const Jib & jib, const Keel & keel, const Keel & rudder) : PhysicalObject(pos, vel, acc), sailDrag(0.0f, 0.0f, 0.0f), sailLift(0.0f, 0.0f, 0.0f), keelDrag(0.0f, 0.0f, 0.0f), keelLift(0.0f, 0.0f, 0.0f)
{
	this->mass = mass;
	sails = new Sail*[1];
	sails[0] = new Jib(jib);
	nrOfSails = 1;
	mainSail = -1;
	this->keel = new Keel(keel);
	this->rudder = new Keel(rudder);
}

Vec Boat::windCalc(Vec trueWind)
{
	Vec apparentWind = trueWind - vel;

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

	float mastHeight = 16.9;
	float aspectRatio = 0;
	float averageFreeBoard = 1.30;

	float angle = keel->getAngle().dot(apparentWind);
	angle = angle / (sqrt(apparentWind.getX()*apparentWind.getX() + apparentWind.getY()*apparentWind.getY())*keel->getAngle().getLength());
	angle = acos(angle) * 360 / (2 * PI);
	angle = 180 - angle;

	if(angle < 45)
		aspectRatio = 1.1*(mastHeight + averageFreeBoard);
	else
		aspectRatio = 1.1*(mastHeight);

	aspectRatio *= aspectRatio / nomArea;

	float inducedDrag = lift * lift*(1 / (PI*aspectRatio) + 0.005);
	
	float maxBeam = 3.71;
	float avgMastDiameter = 0.173;
	float hullAndMastDrag = 1.13*((maxBeam*averageFreeBoard) + (mastHeight*avgMastDiameter)) / nomArea;

	drag += inducedDrag + hullAndMastDrag;

	float liftForceLength = 0.5*(float)DENSITY_AIR*lift*sails[0]->area()*(apparentWind).getLength()*(apparentWind).getLength();

	float dragForceLength = 0.5*(float)DENSITY_AIR*drag*sails[0]->area()*(apparentWind).getLength()*(apparentWind).getLength();

	sailDrag = apparentWind * (dragForceLength/apparentWind.getLength());
	
	sailLift = Vec(apparentWind.getY(), -apparentWind.getX())*(liftForceLength / apparentWind.getLength());
	
	Vec res = sailLift + sailDrag;

	return res;
}

Vec Boat::waterDragCalc()
{
	if (vel.getLength() > 0.01)
	{

		Vec waterFlow = vel * -1;
		// viscous drag and lift calculated for the keel.
		float drag = 0;
		float lift = 0;

		drag = keel->CD(waterFlow);
		lift = keel->CL(waterFlow);

		float liftForceLength = 0.5*(float)DENSITY_WATER*lift*keel->area()*(waterFlow).getLength()*(waterFlow).getLength();

		float dragForceLength = 0.5*(float)DENSITY_WATER*drag*keel->area()*(waterFlow).getLength()*(waterFlow).getLength();

		keelDrag = waterFlow * (dragForceLength / waterFlow.getLength());
		keelLift = Vec(waterFlow.getY(), -waterFlow.getX())*(liftForceLength / waterFlow.getLength());
	}
	
	Vec res = keelDrag + keelLift;

	return res;
}

Vec Boat::hullResistance()
{
	float v = vel.getLength();
	Vec res = Vec(0.f, 0.f, 0.f);
	if (v > 0)
	{
		float µ, wA = 30.9, wL = 10, CH, CF, CW = 0, Re, salt = 1.08, T = 20 + 273.15;
		res = vel * (-1 / v);

		µ = 2.41 * 0.00001 * salt * pow(10, (247.8 / (T - 140)));
		Re = ((float)DENSITY_WATER*v*0.7*wL) / µ;
		CF = 3 / (40 * (log10(Re) - 2) * (log10(Re) - 2));
		CH = CF + CW;
		float F = 0.5*(float)DENSITY_WATER*wA*CH*v*v;
		res *= F;
	}
	return res;
}

Vec Boat::rudderCalc()
{
	if (vel.getLength() > 0.01)
	{
		Vec waterFlow = vel * -1;

		// viscous drag and lift calculated for the keel.
		float drag = 0;
		float lift = 0;

		drag = rudder->CD(waterFlow);
		lift = rudder->CL(waterFlow);

		float liftForceLength = 0.5*(float)DENSITY_WATER*lift*rudder->area()*(waterFlow).getLength()*(waterFlow).getLength();

		float dragForceLength = 0.5*(float)DENSITY_WATER*drag*rudder->area()*(waterFlow).getLength()*(waterFlow).getLength();

		rudderDrag = waterFlow * (dragForceLength / waterFlow.getLength());
		rudderLift = Vec(waterFlow.getY(), -waterFlow.getX())*(liftForceLength / waterFlow.getLength());
	}

	Vec res = rudderDrag + rudderLift;

	return res;
}

void Boat::rudderRot(float time)
{
	// Determine the angle in comparison to the rest of the boat.
	Vec force = rudderDrag + rudderLift;
	if (force.getLength() > 0.00001)
	{
		double keelX = keel->getAngle().getX()/keel->getAngle().getLength();
		double keelY = keel->getAngle().getY() / keel->getAngle().getLength();

		double forceX = force.getX() / force.getLength();
		double forceY = force.getY() / force.getLength();

		double angleToKeel = atan2f(keelX * forceY - keelY * forceX, keelX * forceX + keelY * forceY);

		// torque = F * sin(angle) * r
		double forceSize = force.getLength() * sin(angleToKeel);
		double torque = forceSize * 1.5;
		double boatWidth = 3.7;
		double boatLen = 12.2;

		double inertia = (1.0f / 12.0f)* mass * boatLen*boatLen + mass*boatWidth*boatWidth / 16.0f;

		double angleAcceleration = torque / inertia;

		double angleSpeed = angleAcceleration * time;

		Vec keelAngle = keel->getAngle();

		keelAngle = Vec(keelAngle.getX()*cos(angleSpeed) + keelAngle.getY()*sin(angleSpeed), keelAngle.getY()*cos(angleSpeed) - keelAngle.getX()*sin(angleSpeed));

		keelAngle *= (1/keelAngle.getLength());
		keel->setAngle(keelAngle);
	}
}

void Boat::calcForce(float time, Vec trueWind)
{
	Vec res = this->windCalc(trueWind) + this->waterDragCalc() + this->rudderCalc() + this->hullResistance();

	this->rudderRot(time);
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

Vec Boat::getMainSailAngle() const
{
	Vec angle;
	if (mainSail != -1)
		angle = sails[mainSail]->getAngle();
	else
		angle = Vec(0.f, 0.f, 0.f);

	return angle;
}

void Boat::setMainSailAngle(Vec angle)
{
	float displacement = atan2f(angle.getX(), -angle.getY());

	if (mainSail != -1)
		sails[mainSail]->setAngle(Vec(keel->getAngle().getX()*cos(displacement) + keel->getAngle().getY()*sin(displacement), -keel->getAngle().getX()*sin(displacement) + keel->getAngle().getY()*cos(displacement)));
}

Vec Boat::getRudderAngle() const
{
	return rudder->getAngle();
}

void Boat::setRudderAngle(Vec angle) const
{
	float displacement = atan2f(angle.getX(), -angle.getY());
	rudder->setAngle(Vec(keel->getAngle().getX()*cos(displacement) + keel->getAngle().getY()*sin(displacement), -keel->getAngle().getX()*sin(displacement) + keel->getAngle().getY()*cos(displacement)));
}

float Boat::getAngle()
{
	return atan2f(keel->getAngle().getX(), -keel->getAngle().getY());
}

void Boat::setAngle(Vec angle)
{
	keel->setAngle(angle);
}

