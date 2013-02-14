#include "./OGLOrthoCamera.h"

OGLOrthoCamera::OGLOrthoCamera(int screenWidth, int screenHeight, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax) : OGLCamera(screenWidth, screenHeight)
{
	this->mXMin = xMin;
	this->mXMax = xMax;

	this->mYMin = yMin;
	this->mYMax = yMax;

	this->mZMin = zMin;
	this->mZMax = zMax;
}

OGLOrthoCamera::OGLOrthoCamera(int screenWidth, int screenHeight) : OGLCamera(screenWidth, screenHeight)
{
	this->mXMin = -1.0f;
	this->mXMax = 1.0f;

	this->mYMin = -1.0f;
	this->mYMax = 1.0f;

	this->mZMin = -1.0f;
	this->mZMax = 1.0f;
}

OGLOrthoCamera::~OGLOrthoCamera()
{

}

void OGLOrthoCamera::setXVolum(float xMin, float xMax)
{
	this->mXMin = xMin;
	this->mXMax = xMax;
}

void OGLOrthoCamera::setYVolum(float yMin, float yMax)
{
	this->mYMin = yMin;
	this->mYMax = yMax;
}

void OGLOrthoCamera::setZVolum(float zMin, float zMax)
{
	this->mZMin = -1.0f;
	this->mZMax = 1.0f;
}

void OGLOrthoCamera::render(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    glOrtho(this->mXMin, this->mXMax, this->mYMin, this->mYMax, this->mZMin, this->mZMax);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OGLOrthoCamera::update(float deltaTime)
{

}
