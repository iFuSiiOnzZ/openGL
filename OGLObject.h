#pragma once

#include "./OGLVector3f.h"
#include "./OGLDefines.h"
#include <GL/gl.h>


class OGLObject
{
	private:
		vertexVector v_Vertices;
		InfoMinBox v_MinBox;
		faceVector v_Caras;
		GLuint index;

		std::vector<int>   indexArray;
		std::vector<float> vertexArray;
		std::vector<float> normalArray;

		bool v_Draw;
		bool v_DrawAxis;
		bool v_DrawLines;
		bool v_DrawMinBox;
		bool v_DrawPoints;
		bool v_DrawNormals;
		bool v_DisplayList;
		bool v_DrawPolygons;

		OGLVector3f	v_Pos;
		float		v_Yaw;
		float		v_Size;
		float		v_Pitch;

		void	rDraw			(void);

		void	DrawAxis 		(void);
		void	DrawLines		(void);
		void	DrawMinBox 		(void);
		void	DrawPoints 		(void);
		void	DrawNormals 	(void);
		void 	DrawPolygons 	(void);

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
