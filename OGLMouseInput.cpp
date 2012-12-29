#include "./OGLMouseInput.h"

OGLMouseInput::OGLMouseInput(int sWidth, int sHeight)
{
	this->v_ScreenCenterX 	= (int) (sWidth / 2);
	this->v_ScreenCenterY 	= (int) (sHeight / 2);

	this->v_Yaw 			= 0.0f;
	this->v_Pitch 			= 0.0f;
	this->v_Angle 			= 0.0f;

	this->v_CurrentX 		= 0;
	this->v_CurrentY 		= 0;

	this->v_LastX 			= 0;
	this->v_LastY 			= 0;


	this->v_LeftButton 		= false;
	this->v_RightButton 	= false;
}

OGLMouseInput::~OGLMouseInput()
{
}

void OGLMouseInput::update(int x, int y, float dt)
{
	this->v_LastX 		= this->v_CurrentX;
	this->v_LastY 		= this->v_CurrentY;

	this->v_CurrentX 	= x;
	this->v_CurrentY 	= y;

	this->v_Pitch 		= (this->v_ScreenCenterY - y) * dt;
	this->v_Yaw 		= (this->v_ScreenCenterX - x) * dt;

	this->v_Angle = atan2((this->v_ScreenCenterY - y), (this->v_ScreenCenterX - x));
	if(fabs(this->v_ScreenCenterX - x) > 1 || fabs(this->v_ScreenCenterY - y) > 1)
		glutWarpPointer(this->v_ScreenCenterX, this->v_ScreenCenterY);
}

void OGLMouseInput::update(int button, int state, int x, int y, float dt)
{
	this->update(x, y, dt);

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		this->v_LeftButton = true;
	}
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		this->v_LeftButton = false;
	}

	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		this->v_RightButton = true;
	}
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		this->v_RightButton = false;
	}
}

bool OGLMouseInput::isLeftPress(void)
{
	return(this->v_LeftButton);
}

bool OGLMouseInput::isRightPress(void)
{
	return(this->v_RightButton);
}

float OGLMouseInput::getAngle(void)
{
	return(this->v_Angle);
}

float OGLMouseInput::getPitch(void)
{
	return(this->v_Pitch);
}

float OGLMouseInput::getYaw(void)
{
	return(this->v_Yaw);
}

int OGLMouseInput::getX(void)
{
	return(this->v_CurrentX);
}

int OGLMouseInput::getY(void)
{
	return(this->v_CurrentY);
}

int OGLMouseInput::getLastX(void)
{
	return(this->v_LastX);
}

int OGLMouseInput::getLastY(void)
{
	return(this->v_LastY);
}
