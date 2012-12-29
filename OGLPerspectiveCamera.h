#pragma once

#include "./OGLCamera.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

class OGLPerspectiveCamera : public OGLCamera
{
	private:
		float mFov;
		int   mZFar;
		int	  mZNear;

	public:
		OGLPerspectiveCamera	(int, int, float, int, int);
		OGLPerspectiveCamera	(int, int);
		~OGLPerspectiveCamera	();

		void	update			(float);
		void	render			(void);
};