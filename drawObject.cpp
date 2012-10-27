#include "drawObject.h"

void drawPoints(strObject *object)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POINTS);
	for(int i = 0; i < object->nVertices; i++)
	{
		GLfloat x = (GLfloat) object->pVertices[i][0];
		GLfloat y = (GLfloat) object->pVertices[i][1];
		GLfloat z = (GLfloat) object->pVertices[i][2];

		glVertex3f(x, y, z);
	}

	glEnd();
	glFlush();
}

void drawLines(strObject *object)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	for(int i = 0; i < object->nCaras; i++)
	{
			for(int j = 1; j <= object->uCaras[i][0]; j++)
			{
				GLfloat x = (GLfloat) object->pVertices[object->uCaras[i][j]][0];
				GLfloat y = (GLfloat) object->pVertices[object->uCaras[i][j]][1];
				GLfloat z = (GLfloat) object->pVertices[object->uCaras[i][j]][2];

				glVertex3f(x, y, z);
			}
	}
	glEnd();
	glFlush();
}

void drawAxis(int sz)
{
	// Eje X - Rojo
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(sz * 1.0f, 0.0f, 0.0f);
	glEnd();

	// Eje Y -Verde
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

	glFlush();
}