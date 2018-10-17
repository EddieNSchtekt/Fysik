#include "Vec.h"

Vec::Vec(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	length = sqrtf(x * x + y * y + z * z);
}

Vec::Vec(const Vec & other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	length = -1;
}

float Vec::getX() const
{
	return x;
}

float Vec::getY() const
{
	return y;
}

float Vec::getZ() const
{
	return z;
}

void Vec::setX(const float val)
{
	x = val;
	length = -1;
}

void Vec::setY(const float val)
{
	y = val;
	length = -1;
}

void Vec::setZ(const float val)
{
	z = val;
	length = -1;
}

float Vec::getLength()
{
	if (length < 0)
	{
		length = sqrtf(x * x + y * y + z * z);
	}
	return length;
}

Vec Vec::crossProd(const Vec & other) const
{
	Vec res(0.0f,0.0f,0.0f);
	res.setX(y * other.z - z * other.y);
	res.setY(z * other.x - x * other.z);
	res.setZ(x * other.y - y * other.x);
	return res;
}

float Vec::dot(const Vec & other) const
{
	return x * other.x + y * other.y + z * other.z;
}
/*outputs angle between vectors in radians*/
float Vec::angle(const Vec & other) const
{
	float Dot = dot(other);
	float angle = (float)acos(Dot / (sqrt(x*x + y*y + z*z)*sqrt(other.x*other.x + other.y*other.y + other.z*other.z)));
	return angle;
}

Vec & Vec::operator+=(const Vec & other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	length = -1;
	return *this;
}

Vec Vec::operator+(const Vec & other) const
{
	Vec res;
	res.x = x + other.x;
	res.y = y + other.y;
	res.z = z + other.z;
	return res;
}

Vec Vec::operator-=(const Vec & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	length = -1;
	return *this;
}

Vec Vec::operator-(const Vec & other) const
{
	Vec res(x-other.x, y-other.y, z - other.z);
	return res;
}

Vec & Vec::operator*=(const Vec & other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	length = -1;
	return *this;
}

Vec & Vec::operator*=(const float & other)
{
	x = other * x;
	y = other * y;
	z = other * z;
	length = -1;
	return *this;
}

Vec Vec::operator*(const float & other) const
{
	Vec res;
	res.x = x * other;
	res.y = y * other;
	res.z = z * other;
	return res;
}

Vec & Vec::operator=(const Vec & other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	length = -1;
	return *this;
}
