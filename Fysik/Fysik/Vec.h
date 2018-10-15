#ifndef VEC_H
#define VEC_H
#include <math.h>
class Vec
{
private:
	float x;
	float y;
	float z;
	float length;
public:

	Vec(float x = 0, float y = 0, float z = 0);
	Vec(const Vec & other);

	//gets
	float getX() const;
	float getY() const;
	float getZ() const;

	// sets
	void setX(const float val);
	void setY(const float val);
	void setZ(const float val);

	//practical stuff
	float getLength();
	Vec crossProd(const Vec & other) const;
	float dot(const Vec & other) const;
	float angle(const Vec & other) const;

	//operators
	Vec & operator+=(const Vec & other);
	Vec operator+(const Vec & other)const;
	Vec operator-=(const Vec & other);
	Vec operator-(const Vec & other) const;
	Vec & operator*=(const Vec & other);
	Vec & operator*=(const float & other);
	Vec operator*(const float & other) const;
	Vec & operator=(const Vec & other);
};


#endif