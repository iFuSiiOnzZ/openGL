#include "./OGLMouseInput.h"

OGLMouseInput::OGLMouseInput(int sWidth, int sHeight)
{
	this->mScreenCenterX 	= (int) (sWidth / 2);
	this->mScreenCenterY 	= (int) (sHeight / 2);

	this->mYaw				= 0.0f;
	this->mPitch 			= 0.0f;
	this->mAngle 			= 0.0f;

	this->mCurrentX 		= 0;
	this->mCurrentY 		= 0;

	this->mLeftButton 		= false;
	this->mRightButton		= false;
}

OGLMouseInput::~OGLMouseInput()
{
}

void OGLMouseInput::update(int x, int y, float dt)
{
	this->mCurrentX 	= x;
	this->mCurrentY 	= y;

	this->mPitch		= (this->mScreenCenterY - y);
	this->mYaw			= (this->mScreenCenterX - x);

	this->mAngle = atan2((this->mScreenCenterY - y), (this->mScreenCenterX - x));
	if(fabs(this->mPitch) > 1 || fabs(this->mYaw) > 1)
	{
		glutWarpPointer(this->mScreenCenterX, this->mScreenCenterY);
	}
}

void OGLMouseInput::update(int button, int state, int x, int y, float dt)
{
	this->update(x, y, dt);

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		this->mLeftButton = true;
	}
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		this->mLeftButton = false;
	}

	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		this->mRightButton = true;
	}
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		this->mRightButton = false;
	}
}

bool OGLMouseInput::isLeftPress(void)
{
	return(this->mLeftButton);
}

bool OGLMouseInput::isRightPress(void)
{
	return(this->mRightButton);
}

float OGLMouseInput::getAngle(void)
{
	return(this->mAngle * OGLPI / 180.0f);
}

float OGLMouseInput::getPitch(void)
{
	return(this->mPitch * OGLPI / 180.0f);
}

float OGLMouseInput::getYaw(void)
{
	return(this->mYaw * OGLPI / 180.0f);
}

int OGLMouseInput::getX(void)
{
	return(this->mCurrentX);
}

int OGLMouseInput::getY(void)
{
	return(this->mCurrentY);
}
