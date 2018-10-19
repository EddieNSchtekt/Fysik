#ifndef KEEL_H
#define KEEL_H

#include "Sail.h"
class Keel :
	public Sail
{
protected:
	float draft;
	float chord1;
	float chord2;
public:
	Keel(const Vec & pos, const Vec & vel, const Vec & acc, const float & draft, const float & chord1, const float & chord2, const Vec & angle);
	float area();
	float CL(const Vec & waterFlow);
	float CD(const Vec & waterFlow);
};
#endif