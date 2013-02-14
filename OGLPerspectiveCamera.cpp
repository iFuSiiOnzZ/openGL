#include "./OGLPerspectiveCamera.h"
#include "./OGLObjectManager.h"
#include "./OGLInputManager.h"
#include "./OGLUtils.h"

OGLPerspectiveCamera::OGLPerspectiveCamera(int screenWidth, int screenHeight) : OGLCamera(screenWidth, screenHeight)
{
	this->mFov   = 60.0f;
	this->mZFar  = 1000;
	this->mAngle = 0.0f;
	this->mZNear = 1;
	this->mTimer = new OGLTimer(0);
}

OGLPerspectiveCamera::OGLPerspectiveCamera(int screenWidth, int screenHeight, float fov, int zNear, int zFar) : OGLCamera(screenWidth, screenHeight)
{
	this->mFov   = fov;
	this->mZFar  = zFar;
	this->mAngle = 0.0f;
	this->mZNear = zNear;
	this->mTimer = new OGLTimer(0);
}

OGLPerspectiveCamera::~OGLPerspectiveCamera()
{
	delete(this->mTimer);
	this->mTimer = NULL;
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
	OGLInputManager  *inpManager = OGLInputManager::getInstance();
	OGLObjectManager *objManager = OGLObjectManager::getInstance();


	if(inpManager->isKeyPressed("LEFT"))
	{
		OGLVector3f vDir = OGLVector3f(-5.0f, 0.0f , 0.0f) * deltaTime;
		objManager->setPosition(vDir);
	}

	if(inpManager->isKeyPressed("RIGHT"))
	{
		OGLVector3f vDir = OGLVector3f(5.0f, 0.0f , 0.0f) * deltaTime;
		objManager->setPosition(vDir);
	}

	if(inpManager->isKeyPressed("UP"))
	{
		OGLVector3f vDir = OGLVector3f(0.0f, 0.0f , -5.0f) * deltaTime;
		objManager->setPosition(vDir);
	}

	if(inpManager->isKeyPressed("DOWN"))
	{
		OGLVector3f vDir = OGLVector3f(0.0f, 0.0f, 5.0f) * deltaTime;
		objManager->setPosition(vDir);
	}


	if(OGLInputManager::getInstance()->isRightButtonPress())
	{
		OGLVector3f cPos = this->getPosition();
		OGLUtils utils;

		this->mAngle += deltaTime;
		if(this->mAngle > 2 * OGL2PI)
		{
			this->mAngle = 0.0f;
		}

		float r = utils.v3fDistance(cPos, OGLVector3f());
		cPos.x = r * cos(this->mAngle);
		cPos.z = r * sin(this->mAngle);

		this->setPosition(cPos);
	}
}
