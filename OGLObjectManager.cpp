#include "./OGLObjectManager.h"


OGLObjectManager *OGLObjectManager::hInstance = NULL;

OGLObjectManager::OGLObjectManager()
{
	this->mSelectedObject = &mNullObject;
}

OGLObjectManager::~OGLObjectManager()
{
	this->mObjects.clear();
}

OGLObjectManager *OGLObjectManager::getInstance()
{
	if(hInstance == NULL)
	{
		hInstance = new OGLObjectManager();
	}

	return(hInstance);
}

OGLObject OGLObjectManager::getObject() const
{
	return(*this->mSelectedObject);
}

int OGLObjectManager::getSize(void )
{
	return(this->mObjects.size());
}

void OGLObjectManager::release(void)
{
	this->mObjects.clear();
}

void OGLObjectManager::release(std::string oName)
{
	objectVector::iterator it = this->mObjects.find(oName);
	if(it != this->mObjects.end()) this->mObjects.erase(it);
}

void OGLObjectManager::setSelectedObject(std::string oName)
{
	OGLObject object;

	objectVector::iterator it = this->mObjects.find(oName);
	this->mSelectedObject = (it == this->mObjects.end())? &this->mNullObject : &it->second;
}

OGLObject OGLObjectManager::getObject(std::string oName)
{
	OGLObject object;

	objectVector::iterator it = this->mObjects.find(oName);
	return((it == this->mObjects.end())? this->mNullObject : it->second);
}

void OGLObjectManager::setPosition(const OGLVector3f &pos)
{
	this->mSelectedObject->setPos(pos);
}

void OGLObjectManager::setAngle(float yaw, float pitch)
{
	this->mSelectedObject->setAngle(yaw, pitch);
}

void OGLObjectManager::loadObject(std::string oName, std::string fName)
{
	OGLLoadObject loadObject; this->release(oName);
	OGLObject object = loadObject.loadObject(fName);
	object.genVertexArray();

	this->mObjects.insert(objectPair(oName, object));
}

void OGLObjectManager::drawObject(void)
{
	for(objectVector::iterator it = this->mObjects.begin(); it != this->mObjects.end(); it++)
	{
		it->second.draw();
	}
}

void OGLObjectManager::setDrawAxis(void)
{
	this->mSelectedObject->setDrawAxis();
}

void OGLObjectManager::setDrawLines(void)
{
	this->mSelectedObject->setDrawLines();
}

void OGLObjectManager::setDrawPoints(void)
{
	this->mSelectedObject->setDrawPoints();
}

void OGLObjectManager::setDrawPolygons(void)
{
	this->mSelectedObject->setDrawPolygons();
}

void OGLObjectManager::setDrawMinBox(void)
{
	this->mSelectedObject->setDrawMinBox();
}

void OGLObjectManager::setDrawNormals(void)
{
	this->mSelectedObject->setDrawNormals();
}

OGLVector3f OGLObjectManager::getPosition(void)
{
	return(this->mSelectedObject->getPosition());
}

float OGLObjectManager::getPitch(void)
{
	return(this->mSelectedObject->getPitch());
}

float OGLObjectManager::getYaw(void)
{
	return(this->mSelectedObject->getYaw());
}

void OGLObjectManager::setObjSize(float sz)
{
	this->mSelectedObject->setSize(sz);
}

float OGLObjectManager::getObjSize(void)
{
	return(this->mSelectedObject->getSize());
}

void OGLObjectManager::setDrawObj(void)
{
	this->mSelectedObject->setDraw();
}

objectVector OGLObjectManager::getObjects(void) const
{
	return(this->mObjects);
}

bool OGLObjectManager::getDraw(void)
{
	return(this->mSelectedObject->getDraw());
}
