#include "./OGLObjectManager.h"


OGLObjectManager *OGLObjectManager::hInstance = NULL;

OGLObjectManager::OGLObjectManager()
{
	this->v_selectedObject = &v_nullObject;
}

OGLObjectManager::~OGLObjectManager()
{
	this->v_objects.clear();
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
	return(*this->v_selectedObject);
}

int OGLObjectManager::getSize(void )
{
	return(this->v_objects.size());
}

void OGLObjectManager::release(void)
{
	this->v_objects.clear();
}

void OGLObjectManager::release(std::string oName)
{
	objectVector::iterator it = this->v_objects.find(oName);
	if(it != this->v_objects.end()) this->v_objects.erase(it);
}

void OGLObjectManager::setSelectedObject(std::string oName)
{
	OGLObject object;

	objectVector::iterator it = this->v_objects.find(oName);
	this->v_selectedObject = (it == this->v_objects.end())? &this->v_nullObject : &it->second;
}

OGLObject OGLObjectManager::getObject(std::string oName)
{
	OGLObject object;

	objectVector::iterator it = this->v_objects.find(oName);
	return((it == this->v_objects.end())? this->v_nullObject : it->second);
}

void OGLObjectManager::setPosition(const OGLVector3f &pos)
{
	this->v_selectedObject->setPos(pos);
}

void OGLObjectManager::setAngle(float yaw, float pitch)
{
	this->v_selectedObject->setAngle(yaw, pitch);
}

void OGLObjectManager::loadObject(std::string oName, std::string fName)
{
	OGLLoadObject loadObject; this->release(oName);
	OGLObject object = loadObject.loadObject(fName);
	object.genVertexArray();

	this->v_objects.insert(objectPair(oName, object));
}

void OGLObjectManager::drawObject(void)
{
	this->v_selectedObject->draw();
}

void OGLObjectManager::setDrawAxis(void)
{
	this->v_selectedObject->setDrawAxis();
}

void OGLObjectManager::setDrawLines(void)
{
	this->v_selectedObject->setDrawLines();
}

void OGLObjectManager::setDrawPoints(void)
{
	this->v_selectedObject->setDrawPoints();
}

void OGLObjectManager::setDrawPolygons(void)
{
	this->v_selectedObject->setDrawPolygons();
}

void OGLObjectManager::setDrawMinBox(void)
{
	this->v_selectedObject->setDrawMinBox();
}

void OGLObjectManager::setDrawNormals(void)
{
	this->v_selectedObject->setDrawNormals();
}

OGLVector3f OGLObjectManager::getPosition(void)
{
	return(this->v_selectedObject->getPosition());
}

float OGLObjectManager::getPitch(void)
{
	return(this->v_selectedObject->getPitch());
}

float OGLObjectManager::getYaw(void)
{
	return(this->v_selectedObject->getYaw());
}

void OGLObjectManager::setObjSize(float sz)
{
	this->v_selectedObject->setSize(sz);
}

float OGLObjectManager::getObjSize(void)
{
	return(this->v_selectedObject->getSize());
}

void OGLObjectManager::setDrawObj(void)
{
	this->v_selectedObject->setDraw();
}

objectVector OGLObjectManager::getObjects(void) const
{
	return(this->v_objects);
}

bool OGLObjectManager::getDraw(void)
{
	return(this->v_selectedObject->getDraw());
}
