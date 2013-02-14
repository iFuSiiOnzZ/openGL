#include "./OGLVector3f.h"

OGLVector3f::OGLVector3f(void)
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

OGLVector3f::OGLVector3f(const OGLVector3f &v3f)
{
    this->x = v3f.x;
    this->y = v3f.y;
    this->z = v3f.z;
}

OGLVector3f::OGLVector3f(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

bool OGLVector3f::operator == (const OGLVector3f &v3f)
{
	bool x = this->x == v3f.x;
	bool y = this->y == v3f.y;
	bool z = this->z == v3f.z;

	return(x && y &&  z);
}

bool OGLVector3f::operator != (const OGLVector3f &v3f)
{
	bool x = this->x != v3f.x;
	bool y = this->y != v3f.y;
	bool z = this->z != v3f.z;

	return(x || y ||  z);
}

OGLVector3f OGLVector3f::operator = (const OGLVector3f &v3f)
{
	this->x = v3f.x;
    this->y = v3f.y;
    this->z = v3f.z;

    return(*this);
}

OGLVector3f OGLVector3f::operator + (const OGLVector3f &v3f)
{
    float x = this->x + v3f.x;
    float y = this->y + v3f.y;
    float z = this->z + v3f.z;

    return(OGLVector3f(x, y, z));
}

OGLVector3f OGLVector3f::operator - (const OGLVector3f &v3f)
{
	float x = this->x - v3f.x;
    float y = this->y - v3f.y;
    float z = this->z - v3f.z;

    return(OGLVector3f(x, y, z));
}

OGLVector3f OGLVector3f::operator * (float s)
{
	float x = this->x * s;
    float y = this->y * s;
    float z = this->z * s;

    return(OGLVector3f(x, y, z));
}

OGLVector3f OGLVector3f::operator / (float s)
{
	float x = this->x / s;
    float y = this->y / s;
    float z = this->z / s;

    return(OGLVector3f(x, y, z));
}

OGLVector3f OGLVector3f::normalize(void)
{
	float l = this->length();
	float x = this->x / l;
    float y = this->y / l;
    float z = this->z / l;

    return(OGLVector3f(x, y, z));
}

OGLVector3f OGLVector3f::negative(void)
{
	float x = -this->x;
	float y = -this->y;
	float z = -this->z;

	return(OGLVector3f(x, y, z));
}

OGLVector3f OGLVector3f::crossProduct(const OGLVector3f &v3f)
{
	float x = this->y * v3f.z - this->z * v3f.y;
    float y = this->z * v3f.x - this->x * v3f.z;
    float z = this->x * v3f.y - this->y * v3f.x;

    return(OGLVector3f(x, y, z));
}

float OGLVector3f::dotProduct(const OGLVector3f &v3f)
{
	float x = this->x * v3f.x;
	float y = this->y * v3f.y;
	float z = this->z * v3f.z;

	return(x + y + z);
}

float OGLVector3f::length(void)
{
	float x = this->x * this->x;
	float y = this->y * this->y;
	float z = this->z * this->z;

	return(sqrt(x + y + z));
}
