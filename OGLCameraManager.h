#pragma once

#include "./OGLCamera.h"
#include <string>
#include <map>

typedef std::map<std::string, OGLCamera *> CameraVector;
typedef std::pair<std::string, OGLCamera *> CameraPair;

class OGLCameraManager
{
	private:
		OGLCameraManager(const std::string &, OGLCamera *);
		static OGLCameraManager *hInstance;
		CameraVector::iterator mSelCam;
		CameraVector mCameras;

	public:
		~OGLCameraManager();
		static		OGLCameraManager *getInstance	(void);
		static		OGLCameraManager *getInstance	(std::string, OGLCamera *);
		void		addCamera						(std::string, OGLCamera *);

		void		update			(float);
		void		render			(void);

		void		setScreenSize	(int, int);

		void		nextCamera		(void);
		void		selectCamera	(const std::string &);

		OGLCamera	*getCamera		(void);
		OGLCamera	*getCamera		(const std::string &);

};
