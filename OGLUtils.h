#pragma once

#include <cmath>
#include "./OGLDefines.h"
#include "./OGLVector3f.h"

class OGLUtils
{
	public:
		OGLUtils				(void);

		float	RAD2DEG			(float);
		float	DEG2RAD			(float);
		float 	v3fDistance		(const OGLVector3f &, const OGLVector3f &);
};
