#include "./OGLInputManager.h"

OGLInputManager *OGLInputManager::hInstance = NULL;

OGLInputManager *OGLInputManager::getInstance(int screenWidth, int screenHeight)
{
	if(hInstance == NULL)
	{
		hInstance = new OGLInputManager(screenWidth, screenHeight);
	}

	return(hInstance);
}

OGLInputManager *OGLInputManager::getInstance(void)
{
	if(hInstance == NULL)
	{
		hInstance = new OGLInputManager();
	}

	return(hInstance);
}

OGLInputManager::OGLInputManager(int screenWidth, int screenHeight)
{
	this->mMouseInput 		= new OGLMouseInput(screenWidth, screenHeight);
	this->mKeyboardInput	= new OGLKeyboardInput();
}

OGLInputManager::OGLInputManager(void)
{
	this->mMouseInput 		= new OGLMouseInput(1024, 768);
	this->mKeyboardInput	= new OGLKeyboardInput();
}

OGLInputManager::~OGLInputManager()
{
	delete(this->mMouseInput);
	delete(this->mKeyboardInput);

	this->mMouseInput 		= NULL;
	this->mKeyboardInput 	= NULL;
}

void OGLInputManager::addKey(const std::string &keyName, unsigned char key)
{
	this->mKeyboardInput->addKey(keyName, key);
}

void OGLInputManager::addKeyS(const std::string &keyName, unsigned int key)
{
	this->mKeyboardInput->addKey(keyName, key);
}

void OGLInputManager::updateKey(unsigned char key)
{
	this->mKeyboardInput->update(key);
}

void OGLInputManager::updateKeyS(unsigned int key)
{
	this->mKeyboardInput->update(key);
}

bool OGLInputManager::isKeyPressed(const std::string &keyName)
{
	return(this->mKeyboardInput->isKeyPressed(keyName));
}

void OGLInputManager::updateMouse(int x, int y, float dt)
{
	this->mMouseInput->update(x, y, dt);
}

void OGLInputManager::updateMouse(int button, int state, int x, int y, float dt)
{
	this->mMouseInput->update(button, state, x, y, dt);
}

float OGLInputManager::getAngle(void)
{
	return(this->mMouseInput->getAngle());
}

float OGLInputManager::getPitch(void)
{
	return(this->mMouseInput->getPitch());
}

float OGLInputManager::getYaw(void)
{
	return(this->mMouseInput->getYaw());
}

bool OGLInputManager::isLeftButtonPress(void)
{
	return(this->mMouseInput->isLeftPress());
}

bool OGLInputManager::isRightButtonPress(void)
{
	return(this->mMouseInput->isRightPress());
}

int OGLInputManager::getMouseX(void)
{
	return(this->mMouseInput->getX());
}

int OGLInputManager::getMouseY(void)
{
	return(this->mMouseInput->getY());
}
