#ifndef KEEL_H
#define KEEL_H

#include "Sail.h"
class Keel :
	public Sail
{
private:
	float chordSmall;
public:
	Keel(const Vec & pos, const Vec & vel, const Vec & acc, const float & height, const float & base, const Vec & angle, float chordSmall = 0.7f);
	Keel(const Keel & other);
	float area();
	float CL(const Vec & waterFlow);
	float CD(const Vec & waterFlow);
};
#endif