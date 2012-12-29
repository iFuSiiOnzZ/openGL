#include "./OGLPerspectiveCamera.h"

OGLPerspectiveCamera::OGLPerspectiveCamera(int screenWidth, int screenHeight) : OGLCamera(screenWidth, screenHeight)
{
	this->mFov   = 60.0f;
	this->mZFar  = 1000;
	this->mZNear = 1;
}

OGLPerspectiveCamera::OGLPerspectiveCamera(int screenWidth, int screenHeight, float fov, int zNear, int zFar) : OGLCamera(screenWidth, screenHeight)
{
	this->mFov   = fov;
	this->mZFar  = zFar;
	this->mZNear = zNear;
}

OGLPerspectiveCamera::~OGLPerspectiveCamera()
{

}

void OGLPerspectiveCamera::render(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (float) (this->getScrWidth() / this->getScrHeight());
	aspect = (aspect < 1.0f)? (float) (this->getScrHeight() / this->getScrWidth()) : aspect;

	gluPerspective(this->mFov, aspect, this->mZNear, this->mZFar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    OGLVector3f cUp	 		= this->getUp();
    OGLVector3f cPos 		= this->getPosition();
    OGLVector3f cLooktAt	= this->getLookAt();

    gluLookAt(cPos.x, cPos.y, cPos.z, cLooktAt.x, cLooktAt.y, cLooktAt.z, cUp.x, cUp.y, cUp.z);
}

void OGLPerspectiveCamera::update(float deltaTime)
{

}