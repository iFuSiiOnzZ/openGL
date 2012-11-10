#ifndef _LOADOBJECT_H_
	#define _LOADOBJECT_H_

	#include <GL/glut.h>
	#include <stdio.h>
	
	#include <cstring>
	#include <string>
	#include <map>

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

	class cLoadObject
	{
		private:
			cLoadObject						();
			~cLoadObject					();

			strObject selectedObject;
			static cLoadObject *hInstance;
			std::map<std::string, strObject> cloObjects;

		public:
			static cLoadObject *getInstance	();

			bool loadObject 				(std::string oName, std::string fName);
			bool unloadObject 				(std::string oName);

			void setSelectedObject			(std::string oName);

			strObject getObject				(void);
			strObject getObject				(std::string oName);

			void release					(void);

	};
#endif