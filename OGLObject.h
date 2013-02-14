#pragma once

#include "./OGLVector3f.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <vector>

typedef struct InfoFace		InfoFace;
typedef struct InfoVertex	InfoVertex;
typedef struct InfoMinBox	InfoMinBox;

typedef std::vector<InfoFace>		faceVector;
typedef std::vector<InfoVertex>		vertexVector;
typedef std::vector<unsigned int>	intVector;

struct InfoVertex
{
	int tx, ty;
	OGLVector3f vertexNormal;
	OGLVector3f vertexPosition;
};

struct InfoFace
{
	intVector vCara;
	OGLVector3f faceNormal;
	OGLVector3f faceCenter;
};

struct InfoMinBox
{
	OGLVector3f	minCoordenates;
	OGLVector3f maxCoordenates;
};


class OGLObject
{
	private:
		vertexVector mVertices;
		InfoMinBox mMinBox;
		faceVector mCaras;
		GLuint index;

		std::vector<int>   indexArray;
		std::vector<float> vertexArray;
		std::vector<float> normalArray;

		bool mDraw;
		bool mDrawAxis;
		bool mDrawLines;
		bool mDrawMinBox;
		bool mDrawPoints;
		bool mDrawNormals;
		bool mDisplayList;
		bool mDrawPolygons;

		OGLVector3f	mPos;
		float		mYaw;
		float		mSize;
		float		mPitch;

		void	rDraw			(void);

		void	DrawAxis 		(void);
		void	DrawLines		(void);
		void	DrawMinBox 		(void);
		void	DrawPoints 		(void);
		void	DrawNormals 	(void);
		void 	DrawPolygons 	(void);

		void	resize			(void);
		void	rotate			(void);
		void	translate		(void);

	public:
		OGLObject						();
		~OGLObject						();

		void 			draw 			(void);
		void			setDraw 		(void);
		bool			getDraw			(void);

		void			setDrawAxis		(void);
		void			setDrawLines	(void);
		void			setDrawMinBox	(void);
		void			setDrawPoints	(void);
		void			setDrawNormals	(void);
		void			setDrawPolygons	(void);

		void			genVertexArray	(void);

		OGLVector3f		getPosition		(void);
		float 			getPitch		(void);
		float			getYaw			(void);

		void			setPos			(const OGLVector3f &);
		void			setAngle		(float, float);

		int 			getVSize		(void);
		int 			getCSize		(void);

		vertexVector	getVertices		(void) const;
		InfoVertex		getVertice 		(int)  const;

		void			setVertice		(const InfoVertex &);
		void			setVertices		(const vertexVector &);

		faceVector		getCaras		(void) const;
		InfoFace		getCara 		(int)  const;

		void			setSize			(float);
		float			getSize 		(void);

		void			setCara			(const InfoFace &);
		void 			setCaras		(const faceVector &);

		void			setMinBox		(InfoMinBox);
		InfoMinBox		getMinBox		(void)  const;

		void			setNormalC		(float, float, float, int);
		void			setNormalV		(float, float, float, int);
};
