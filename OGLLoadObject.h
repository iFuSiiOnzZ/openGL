#pragma once

#include <iostream>
#include <fstream>
#include <GL/gl.h>
#include <cstdlib>
#include <cmath>

#include "./OGLDefines.h"
#include "./OGLObject.h"

class OGLLoadObject
{
	private:
		
	public:
		OGLLoadObject		();
		~OGLLoadObject		();

		OGLObject loadObject	(std::string);
};
