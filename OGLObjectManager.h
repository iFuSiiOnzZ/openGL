#pragma once

#include "./OGLObject.h"
#include "./OGLLoadObject.h"

typedef std::map<std::string, OGLObject> objectVector;
typedef std::pair<std::string, OGLObject> objectPair;

class OGLObjectManager
{
	private:
		OGLObjectManager();
		OGLObject mNullObject;
		objectVector mObjects;
		OGLObject *mSelectedObject;
		static OGLObjectManager *hInstance;

	public:
		~OGLObjectManager						();
		static OGLObjectManager *getInstance	();

		int  getSize				(void);

		void  setObjSize			(float);
		float getObjSize			(void);
		bool  getDraw				(void);

		void drawObject				(void);
		void setDrawObj				(void);
		void setDrawAxis			(void);
		void setDrawLines			(void);
		void setDrawMinBox			(void);
		void setDrawPoints			(void);
		void setDrawNormals			(void);
		void setDrawPolygons		(void);

		OGLVector3f	getPosition		(void);
		float 		getPitch		(void);
		float		getYaw			(void);

		void setPosition			(const OGLVector3f &);
		void setAngle				(float, float);

		void moveObject				(void);
		void rotateObject			(void);

		void loadObject				(std::string, std::string);
		void setSelectedObject		(std::string);

		void release				(void);
		void release				(std::string);

		OGLObject getObject			(void)	const;
		OGLObject getObject			(std::string);

		objectVector	getObjects	(void)	const;
};
