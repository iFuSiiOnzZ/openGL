#include "OGLFpsCamera.h"
#include "./OGLInputManager.h"

OGLFpsCamera::OGLFpsCamera(int sWidth, int sHeight, float  fov, int zNear, int zFar) : OGLCamera(sWidth, sHeight)
{
	this->mFov		= fov;
	this->mZFar		= zFar;
	this->mZNear	= zNear;

	this->mYaw		= 0.0f;
	this->mPitch	= 0.0f;

	OGLInputManager::getInstance()->addKey("w", 'w');
	OGLInputManager::getInstance()->addKey("s", 's');
	OGLInputManager::getInstance()->addKey("a", 'a');
	OGLInputManager::getInstance()->addKey("d", 'd');
}

OGLFpsCamera::OGLFpsCamera(int sWidth, int sHeight) : OGLCamera(sWidth, sHeight)
{
	this->mFov		= 60.0f;
	this->mZFar		= 1000;
	this->mZNear	= 1;

	this->mYaw		= 0.0f;
	this->mPitch	= 0.0f;

	OGLInputManager::getInstance()->addKey("w", 'w');
	OGLInputManager::getInstance()->addKey("s", 's');
	OGLInputManager::getInstance()->addKey("a", 'a');
	OGLInputManager::getInstance()->addKey("d", 'd');
}

OGLFpsCamera::~OGLFpsCamera()
{
}


void OGLFpsCamera::update(float dt)
{
	float mYaw		= this->getYaw();
	float mPitch	= this->getPitch();

	if(mYaw > OGL2PI){ mYaw -= OGL2PI; this->setYaw(mYaw); }
	if(mYaw < 0.0f){ mYaw += OGL2PI; this->setYaw(mYaw); }

	if(mPitch > OGL12PI){ mPitch = OGL12PI; this->setPitch(mPitch); }
	if(mPitch < -OGL12PI){ mPitch = -OGL12PI; this->setPitch(mPitch); }

	OGLVector3f vDirection(cosf(mPitch) * sinf(mYaw),
						   sinf(mPitch),
						   cosf(mPitch) * cosf(mYaw));

	OGLVector3f vStride(sinf(mYaw - OGL12PI),
						0.0f,
						cosf(mYaw - OGL12PI));

	if(OGLInputManager::getInstance()->isKeyPressed("UP"))
		this->setPosition(this->getPosition() + vDirection * 5 * dt);
	if(OGLInputManager::getInstance()->isKeyPressed("DOWN"))
		this->setPosition(this->getPosition() - vDirection * 5 * dt);
	if(OGLInputManager::getInstance()->isKeyPressed("LEFT"))
		this->setPosition(this->getPosition() - vStride * 5 * dt);
	if(OGLInputManager::getInstance()->isKeyPressed("RIGHT"))
		this->setPosition(this->getPosition() + vStride * 5 * dt);

	OGLVector3f vUp(vStride.crossProduct(vDirection));
	OGLVector3f vLookAt(vDirection + this->getPosition());

	this->setDirection(vDirection);
	this->setStride(vStride);
	this->setLookAt(vLookAt);
	this->setUp(vUp);
}

void OGLFpsCamera::render(void)
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
