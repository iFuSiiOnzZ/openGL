#pragma once

#include <cmath>

class OGLVector3f
{
	public:
		float x;
		float y;
		float z;

		OGLVector3f					(void);
		OGLVector3f					(const OGLVector3f &);
		OGLVector3f					(float, float, float);

		bool operator ==			(const OGLVector3f &);
		bool operator !=			(const OGLVector3f &);

		OGLVector3f operator =		(const OGLVector3f &);
		OGLVector3f operator +		(const OGLVector3f &);
		OGLVector3f operator -		(const OGLVector3f &);
		OGLVector3f operator *		(float);
		OGLVector3f operator /		(float);

		float		length			(void);
		float		dotProduct		(const OGLVector3f &);

		OGLVector3f	negative		(void);
		OGLVector3f normalize		(void);
		OGLVector3f crossProduct	(const OGLVector3f &);
};
