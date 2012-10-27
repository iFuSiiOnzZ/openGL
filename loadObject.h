#ifndef _LOADOBJECT_H_
	#define _LOADOBJECT_H_

	#include <GL/glut.h>
	#include <stdio.h>		// FILE *
	#include <string.h>		// bzero(*, size_t)

	typedef struct Vertex3D
	{
		GLfloat x, y, z;
	}Vertex3D;

	//Estructura de informacion
	typedef struct strObject	// Informacion sobre un objeto
	{
		int 	nVertices;		// Verices que tiene el objeto,
								// damos por sentado que es un
								// objeto 3D

		int 	nCaras;			// Caras que tiene el objeto
		
		GLfloat	**pVertices;	// Pusiciones donde se encuentra
								// cada uno de los vertices del
								// objeto. Array bidimensional

		int 	**uCaras;		// Array bidimensional que contiene
								// por cuantos puntos esta formada
								// una cara y los puntos que la forma
	}strObject;

	int loadObject(strObject *object, char *fName);
	void unloadObject(strObject *object);
#endif