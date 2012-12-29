#include "drawObject.h"

cDrawObject::cDrawObject()
{
}

cDrawObject::~cDrawObject()
{
}

void cDrawObject::drawAxis(int sz)
{
	// Eje X - Rojo
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(sz * 1.0f, 0.0f, 0.0f);
	glEnd();

	// Eje Y - Verde
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, sz * 1.0f, 0.0f);
	glEnd();

	// Eje Z - Azul
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, sz * 1.0f);
	glEnd();
}

int cDrawObject::primtiveType(int nFaces)
{
	if((nFaces % 3) == 0) return(GL_TRIANGLES);
	else if((nFaces % 4) == 0) return(GL_QUADS);
	else return(GL_POLYGON);
}

cDrawPoints::cDrawPoints()
{
}

cDrawPoints::~cDrawPoints()
{
}

void cDrawPoints::drawObject(strObject object)
{
	glPointSize(2.0f);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_POINTS);
	for(int i = 0; i < object.nVertices; i++)
	{
		GLfloat x = (GLfloat) object.pVertices[i][0];
		GLfloat y = (GLfloat) object.pVertices[i][1];
		GLfloat z = (GLfloat) object.pVertices[i][2];

		glVertex3f(x, y, z);
	}
	glEnd();
}

cDrawLines::cDrawLines()
{
}

cDrawLines::~cDrawLines()
{
}

void cDrawLines::drawObject(strObject object)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	for(int i = 0; i < object.nCaras; i++)
	{
		glBegin(GL_LINE_LOOP);
			for(int j = 1; j <= object.uCaras[i][0]; j++)
			{
				GLfloat x = (GLfloat) object.pVertices[object.uCaras[i][j]][0];
				GLfloat y = (GLfloat) object.pVertices[object.uCaras[i][j]][1];
				GLfloat z = (GLfloat) object.pVertices[object.uCaras[i][j]][2];
				
				glVertex3f(x, y, z);
			}
		glEnd();
	}
}

cDrawPolygons::cDrawPolygons()
{
}

cDrawPolygons::~cDrawPolygons()
{
}

void cDrawPolygons::drawObject(strObject object)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	for(int i = 0; i < object.nCaras; i++)
	{
		glBegin(this->primtiveType(object.uCaras[i][0]));
			for(int j = 1; j <= object.uCaras[i][0]; j++)
			{
				GLfloat x = (GLfloat) object.pVertices[object.uCaras[i][j]][0];
				GLfloat y = (GLfloat) object.pVertices[object.uCaras[i][j]][1];
				GLfloat z = (GLfloat) object.pVertices[object.uCaras[i][j]][2];

				glVertex3f(x, y, z);
			}
		glEnd();
	}
}