#include "./OGLUtils.h"

OGLUtils::OGLUtils(void)
{
}

float OGLUtils::DEG2RAD(float degrees)
{
	float radians = degrees * OGLPI / 180.0f;

	return(radians);
}

float OGLUtils::RAD2DEG(float radians)
{
	float degrees = radians * 180.0f / OGLPI;

	return(degrees);
}

float OGLUtils::v3fDistance(const OGLVector3f &v1, const OGLVector3f &v2)
{
	float x = v1.x - v2.x;
	float y = v1.y - v2.y;
	float z = v1.z - v2.z;

	return(sqrt(x * x + y * y + z * z));
}
