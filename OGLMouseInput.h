#pragma once

#include <GL/glut.h>
#include "./OGLDefines.h"

class OGLMouseInput
{
	private:
		int mScreenCenterX;
		int mScreenCenterY;

		int mCurrentX;
		int mCurrentY;

		float mYaw;
		float mPitch;
		float mAngle;

		bool mLeftButton;
		bool mRightButton;

	public:
		OGLMouseInput	(int, int);
		~OGLMouseInput	();

		void	update		(int, int, float);
		void	update		(int, int, int, int, float);

		float	getAngle	(void);
		float	getPitch	(void);
		float	getYaw		(void);

		bool	isLeftPress	(void);
		bool	isRightPress(void);

		int 	getX		(void);
		int 	getY 		(void);
};
