#include "./OGLCamera.h"

OGLCamera::OGLCamera(int screenWidth, int screenHeight)
{
	this->mDirection	= OGLVector3f();
	this->mPosition		= OGLVector3f();
	this->mStride		= OGLVector3f();
	this->mLookAt		= OGLVector3f();
	this->mUp			= OGLVector3f();

	this->mScreenHeight = screenHeight;
	this->mScreenWidth	= screenWidth;
}

OGLCamera::~OGLCamera()
{
}

void OGLCamera::setScrHeight(int screenHeight)
{
	this->mScreenHeight = screenHeight;
}

void OGLCamera::setScrWidth(int screenWidth)
{
	this->mScreenWidth = screenWidth;
}

int	OGLCamera::getScrHeight(void)
{
	return(this->mScreenHeight);
}

int	OGLCamera::getScrWidth(void)
{
	return(this->mScreenWidth);
}

void OGLCamera::setDirection(const OGLVector3f &vDirection)
{
	this->mDirection = vDirection;
}

void OGLCamera::setPosition(const OGLVector3f &vPosition)
{
	this->mPosition = vPosition;
}

void OGLCamera::setStride(const OGLVector3f &vStride)
{
	this->mStride = vStride;
}

void OGLCamera::setLookAt(const OGLVector3f &vLookAt)
{
	this->mLookAt = vLookAt;
}

void OGLCamera::setUp(const OGLVector3f &vUp)
{
	this->mUp = vUp;
}


void OGLCamera::addDirection(const OGLVector3f &vDirection)
{
	this->mDirection = this->mDirection + vDirection;
}

void OGLCamera::addPosition(const OGLVector3f &vPosition)
{
	this->mPosition = this->mPosition + vPosition;
}

void OGLCamera::addStride(const OGLVector3f &vStride)
{
	this->mStride = this->mStride + vStride;
}

void OGLCamera::addLookAt(const OGLVector3f &vLookAt)
{
	this->mLookAt = this->mLookAt + vLookAt;
}

void OGLCamera::addUp(const OGLVector3f &vUp)
{
	this->mUp = this->mUp + vUp;
}

OGLVector3f	OGLCamera::getDirection(void)
{
	return(this->mDirection);
}

OGLVector3f	OGLCamera::getPosition	(void)
{
	return(this->mPosition);
}

OGLVector3f	OGLCamera::getStride(void)
{
	return(this->mStride);
}

OGLVector3f	OGLCamera::getLookAt(void)
{
	return(this->mLookAt);
}

OGLVector3f	OGLCamera::getUp(void)
{
	return(this->mUp);
}