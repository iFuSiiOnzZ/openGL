#pragma once
#include <cmath>
#include <cstdio>
#include <GL/gl.h>
#include <GL/glut.h>

class OGLMouseInput
{
	private:
		int v_ScreenCenterX;
		int v_ScreenCenterY;

		int v_CurrentX;
		int v_CurrentY;

		int v_LastX;
		int v_LastY;

		float v_Yaw;
		float v_Pitch;
		float v_Angle;

		bool v_LeftButton;
		bool v_RightButton;
		
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

		int 	getLastX	(void);
		int 	getLastY	(void);
		
};
