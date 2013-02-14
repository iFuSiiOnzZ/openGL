#include "./OGLCameraManager.h"

OGLCameraManager *OGLCameraManager::hInstance = NULL;

OGLCameraManager::OGLCameraManager(const std::string &cName, OGLCamera *tCamera)
{
	this->mCameras.insert(CameraPair(cName, tCamera));
	this->mSelCam = this->mCameras.begin();
}

OGLCameraManager::~OGLCameraManager()
{
	for(CameraVector::iterator it = this->mCameras.begin(); it != this->mCameras.end(); it++)
	{
		delete(it->second);
		it->second = NULL;
	}

	this->mCameras.clear();
}

OGLCameraManager *OGLCameraManager::getInstance(void)
{
	return(hInstance);
}

OGLCameraManager *OGLCameraManager::getInstance(std::string cName, OGLCamera *tCamera)
{
	if(hInstance == NULL)
	{
			hInstance = new OGLCameraManager(cName, tCamera);
	}

	return(hInstance);
}

void OGLCameraManager::setScreenSize(int sWidth, int sHeight)
{
	for(CameraVector::iterator it = this->mCameras.begin(); it != this->mCameras.end(); it++)
	{
		it->second->setScrWidth(sWidth);
		it->second->setScrHeight(sHeight);
	}
}

void OGLCameraManager::addCamera(std::string cName, OGLCamera *cType)
{
	CameraVector::iterator it = this->mCameras.find(cName);
	if(it != this->mCameras.end())
	{
		delete(it->second);
		this->mCameras.erase(it);
	}

	this->mCameras.insert(CameraPair(cName, cType));
}

OGLCamera *OGLCameraManager::getCamera(const std::string &cName)
{
	CameraVector::iterator it = this->mCameras.find(cName);
	if(it != this->mCameras.end()) return(it->second);
	return(this->mSelCam->second);
}

OGLCamera *OGLCameraManager::getCamera(void)
{
	return(this->mSelCam->second);
}

void OGLCameraManager::selectCamera(const std::string &cName)
{
	CameraVector::iterator it = this->mCameras.find(cName);
	if(it != this->mCameras.end()) this->mSelCam = it;
}

void OGLCameraManager::nextCamera(void)
{
	this->mSelCam++;
	if(this->mSelCam == this->mCameras.end()) this->mSelCam = this->mCameras.begin();
}

void OGLCameraManager::update(float dt)
{
	this->mSelCam->second->update(dt);
}

void OGLCameraManager::render(void)
{
	this->mSelCam->second->render();
}

