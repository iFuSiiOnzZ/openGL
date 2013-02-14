#pragma once

#include "./OGLCamera.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

class OGLOrthoCamera : public OGLCamera
{
	private:
		float mXMin;
		float mXMax;

		float mYMin;
		float mYMax;

		float mZMin;
		float mZMax;

	public:
		OGLOrthoCamera		(int, int, float, float, float, float, float, float);
		OGLOrthoCamera		(int, int);
		~OGLOrthoCamera		();

		void setXVolum		(float, float);
		void setYVolum		(float, float);
		void setZVolum		(float, float);

		void render			(void);
		void update			(float);
};
