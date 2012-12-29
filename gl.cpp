<<<<<<< HEAD
#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "./OGLTimer.h"
#include "./OGLVector3f.h"
#include "./OGLOrthoCamera.h"
#include "./OGLInputManager.h"
#include "./OGLObjectManager.h"
#include "./OGLPerspectiveCamera.h"

void	render		(void);
void	finish		(void);
void	start		(void);

void	reshape		(int, int);
void	keyDown		(unsigned char, int, int);
void	keyUp		(unsigned char, int, int);

void	mouseProcess(int, int, int, int);
void	mouseMotion	(int, int);

int sWidth	= 1024;
int sHeight	= 768;

OGLTimer		 *oglTimer		= NULL;
OGLCamera		 *oglCamera		= NULL;
OGLInputManager	 *inpManager	= NULL;
OGLObjectManager *objManager	= NULL;

void start(void)
{
	oglTimer	= new OGLTimer(0);
	objManager	= OGLObjectManager::getInstance();
	inpManager	= OGLInputManager::getInstance(sWidth, sHeight);

	oglCamera	= new OGLPerspectiveCamera(sWidth, sHeight, 60.0f, 1, 1000);
	oglCamera->setPosition(OGLVector3f(3.0f, 2.0f, 5.0f));
	oglCamera->setLookAt(OGLVector3f(0.0f, 0.0f, 0.0f));
	oglCamera->setUp(OGLVector3f(0.0f, 1.0f, 0.0f));

	objManager->loadObject("CUB", "./3d/0_cub.3d");
	objManager->setSelectedObject("CUB");
	objManager->setDrawAxis();

	atexit(finish);
}

void finish(void)
{
	delete(oglTimer);	oglTimer	= NULL;
	delete(oglCamera);	oglCamera	= NULL;
	delete(inpManager);	inpManager	= NULL;
	delete(objManager);	objManager	= NULL;
}

void render()
{
	oglTimer->update();
	oglCamera->update(oglTimer->getDeltaTime());

	oglCamera->render();
	objManager->drawObject();

	/*objectVector o = objManager->getObjects();
	for(objectVector::iterator it = o.begin(); it != o.end(); it++)
	{
		it->second.draw();
	}*/

	char text[100];
	sprintf(text, "Grafics per computador (FPS: %d)", oglTimer->getFps());
	glutSetWindowTitle(text);

	glutSwapBuffers();
	glutPostRedisplay();
}

void keyDown(unsigned char key, int x, int y)
{
	if(key == 27) exit(EXIT_SUCCESS);

	inpManager->updateKey(key);
	inpManager->updateMouse(x, y, oglTimer->getDeltaTime());
}

void keyUp(unsigned char key, int x, int y)
{
	inpManager->updateKey(key);
	inpManager->updateMouse(x, y, oglTimer->getDeltaTime());
}

void mouseProcess(int button, int state, int x, int y)
{
	inpManager->updateMouse(button, state, x, y, oglTimer->getDeltaTime());
}

void mouseMotion(int x, int y)
{
	inpManager->updateMouse(x, y, oglTimer->getDeltaTime());
}

void reshape(int bWidth, int bHeight)
{
	sWidth = bWidth;
	sHeight = bHeight;

	if(bWidth <= bHeight)
	{
			sWidth = bHeight;
			sHeight = bWidth;
	}

	glViewport(0, 0, sWidth, sHeight);

	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/
}

int main(int argc, char *argv[])
{
	// 01) glutInit
	glutInit(&argc, argv);

	// 02) glutInitDisplayMode
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// 03) glutInitWindowPosition
	glutInitWindowPosition(0, 0);

	// 04) glutInitWindowSize
	glutInitWindowSize(sWidth, sHeight);

	// 05) glutCreateWindow
	glutCreateWindow("Practica 04");

	// other
	start();

	// 06)
	glutDisplayFunc(render);

	// 07)
	glutKeyboardFunc(keyDown);

	// 08)
	glutKeyboardUpFunc(keyUp);

	// 09
	glutMouseFunc(mouseProcess);

	// 10
	glutMotionFunc(mouseMotion);

	// 11)
	glutPassiveMotionFunc(mouseMotion);

	// 12)
	glutReshapeFunc(reshape);

	// 13)
	glutMainLoop();


	return(EXIT_SUCCESS);
}
=======
 #include "gl.h"											// Contiene los header y estructuras
															// de datos utilizado en la app

//P rototipos de funciones                      		
void inicialitzar(void); 									// Configuració bàsica del pipeline d’OpenGL
void representarEscena();									// Procés de dibuixat de l’escena
void processaTecles(unsigned char tecla, int x, int y);		// Processat dels events de teclat
void finalitzar(void);										// Espai per a l’alliberament de memòria
void reshape(int width, int height);						// Tamaño viewport

// Defines
#define kExitGl		27										// ESC - salir de openGL
#define kProyect	'p'										// p   - proyeccion ortografica o perspectiva

// Variables globales
int bProyeccion	= 1;										// Nos dice si la camera es de pespectiva o ortografca
cDrawObject *drawObject = NULL;

int bWidth		= 1024;										// Ancho pantalla
int bHeight		= 768;										// Alto pantalla

Vertex3D cameraPosition = {3.0f, 3.0f, 5.0f};				// Posicion inicial de la camera
Vertex3D lookAtPosition = {0.0f, 0.0f, 0.0f};				// Posicion inicial de done miramos		


int main(int argc, char **argv)
{
	// Inicialització de la finestra GLUT
	// AQUÍ HEU DE FER LES CRIDES PERTINENTS A:

	// 1) glutInit
	glutInit(&argc, argv);

	// 2) glutInitDisplayMode
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// 3) glutInitWindowPosition
	glutInitWindowPosition(0, 0);

	// 4) glutInitWindowSize
	glutInitWindowSize(bWidth, bHeight);

	// 5) glutCreateWindow
	glutCreateWindow("Practica 01");
	
	
	inicialitzar();							// Funció que inicialitza l’estat del pipeline
											// OpenGL i altres variables d’entorn que pugueu
											// necessitar al llarg de la pràctica.
	// 6)
	glutDisplayFunc(representarEscena); 	// Configuració del callback a la funció
											// encarregada del dibuixat.
	// 7)
	glutKeyboardFunc(processaTecles);		// Configuració del callback a la funció
											// encarregada de la gestió de teclat

	glutReshapeFunc(reshape);				// Otra funcion de callback, en caso de reescalar
											// la ventana, sera la encargada de cambiar el tamaño
											// del plano de proyeccion

	glutMainLoop();							// Bucle de processament l'aplicació GLUT
	
	return 0;
}

void inicialitzar(void)
{
	// AQUI VA LA VOSTRA IMPLEMENTACIÓ
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	cLoadObject::getInstance()->loadObject("0", "cubo.txt");
	cLoadObject::getInstance()->loadObject("1", "1.txt");
	cLoadObject::getInstance()->loadObject("2", "2.txt");

	cMotion::getInstance()->addKey("Lineas", 'w');
	cMotion::getInstance()->addKey("Puntos", 'q');
	cMotion::getInstance()->addKey("Planos", 'e');
	cMotion::getInstance()->addKey("Cargar", '1');

	cMotion::getInstance()->addKey("Object0", '0');
	cMotion::getInstance()->addKey("Object1", '1');
	cMotion::getInstance()->addKey("Object2", '2');

	drawObject = new cDrawLines();


	atexit(finalitzar);							// Funció que es cridarà en acabar. ALERTA:
												// Els usuaris de la llibreria freeglut poden
												// substituir-la pel mecanisme de control de la
												// funció glutLeaveMainLoop (evitant l’exit(0) a
												// la gestió d’events de teclat i assegurant la
												// crida de la funció finalitzar();).

}

void finalitzar(void)
{ 
	// Es crida just abans de sortir, després de l'exit(0), i és on alliberarem la memòria
	delete(drawObject);
	cLoadObject::getInstance()->release();
}

void representarEscena(void)
{
	// Procés de dibuixat de l’escena
	// AQUI VA LA VOSTRA IMPLEMENTACIÓ
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(!bProyeccion){ glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f); }
	else{ gluPerspective(60.0f, bWidth/bHeight, 1.0f, 20.0f); }

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();		

	if(bProyeccion)
	{		
		gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z,
			  	  lookAtPosition.x, lookAtPosition.y, lookAtPosition.z,
			      0.0f, 1.0f, 0.0f);
	}

	drawObject->drawAxis(2);
	drawObject->drawObject(cLoadObject::getInstance()->getObject());

	glutSwapBuffers();
}

void processaTecles(unsigned char tecla, int x, int y)
{
	if(tecla == kExitGl){ exit(0); }
	if(tecla == kProyect){ bProyeccion = (bProyeccion == 1)? 0 : 1; }

	cMotion::getInstance()->update(tecla, x, y);
	if(cMotion::getInstance()->isKeyPressed("Cargar"))
	{
		cLoadObject::getInstance()->loadObject("0", "1.txt");
	}

	if(cMotion::getInstance()->isKeyPressed("Object0"))
	{
		cLoadObject::getInstance()->setSelectedObject("0");
	}

	if(cMotion::getInstance()->isKeyPressed("Object1"))
	{
		cLoadObject::getInstance()->setSelectedObject("1");
	}

	if(cMotion::getInstance()->isKeyPressed("Object2"))
	{
		cLoadObject::getInstance()->setSelectedObject("2");
	}

	if(cMotion::getInstance()->isKeyPressed("Lineas"))
	{
		delete(drawObject);
		drawObject = new cDrawLines();
	}

	if(cMotion::getInstance()->isKeyPressed("Puntos"))
	{
		delete(drawObject);
		drawObject = new cDrawPoints();
	}

	if(cMotion::getInstance()->isKeyPressed("Planos"))
	{
		delete(drawObject);
		drawObject = new cDrawPolygons();
	}

	glutPostRedisplay();
}

void reshape(int width, int height)
{
	bWidth = width; bHeight = height;

	if(width <= height)
	{
		bWidth = height;
		bHeight = width;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(!bProyeccion){ glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f); }
	else{ gluPerspective(60.0f, width/height, 1.0f, 20.0f); }

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
>>>>>>> fdb96498f719d8ca462cbedfc2c128a7c20887f9
