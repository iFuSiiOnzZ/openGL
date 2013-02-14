#pragma once

#include "./OGLCamera.h"
#include "./OGLTimer.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

class OGLPerspectiveCamera : public OGLCamera
{
	private:
		float mFov;
		int   mZFar;
		int	  mZNear;
		float mAngle;
		OGLTimer *mTimer;

	public:
		OGLPerspectiveCamera	(int, int, float, int, int);
		OGLPerspectiveCamera	(int, int);
		~OGLPerspectiveCamera	();

		void	update			(float);
		void	render			(void);
};
