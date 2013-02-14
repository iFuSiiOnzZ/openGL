#pragma once

#include "./OGLInputManager.h"
#include "./OGLCamera.h"
#include "./OGLUtils.h"

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

class OGLFpsCamera : public OGLCamera
{
	private:
		float mFov;
		int   mZFar;
		int	  mZNear;

		float mYaw;
		float mPitch;

	public:
		OGLFpsCamera		(int, int, float, int, int);
		OGLFpsCamera		(int, int);
		~OGLFpsCamera		();

		void	render		(void);
		void	update		(float);
};
