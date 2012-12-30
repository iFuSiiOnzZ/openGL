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
void	update		(void);

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
	oglCamera->setPosition(OGLVector3f(3.0f, 2.0f, 50.0f));
	oglCamera->setLookAt(OGLVector3f(0.0f, 0.0f, 0.0f));
	oglCamera->setUp(OGLVector3f(0.0f, 1.0f, 0.0f));

	inpManager->addKey("LINES",		'w');
	inpManager->addKey("POINTS",	'q');
	inpManager->addKey("POLYGONS",	'e');

	inpManager->addKey("MAPA",		'1');
	inpManager->addKey("DONA",		'2');
	inpManager->addKey("HOME",		'3');
	inpManager->addKey("TEAPOT",	'4');
	inpManager->addKey("TRIANGLE",	'5');
	inpManager->addKey("BEETHOVEN", '6');

	objManager->loadObject("MAPA",		"./3d/0_mapa.3d");
	objManager->loadObject("DONA",		"./3d/0_dona.3d");
	objManager->loadObject("HOME",		"./3d/0_home.3d");
	objManager->loadObject("TEAPOT",	"./3d/0_teapot.3d");
	objManager->loadObject("TRIANGLE",	"./3d/0_triangle.3d");
	objManager->loadObject("BEETHOVEN", "./3d/0_beethoven.3d");

	objManager->setSelectedObject("BEETHOVEN");
	objManager->setDrawAxis();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	atexit(finish);
}

void finish(void)
{
	delete(oglTimer);	oglTimer	= NULL;
	delete(oglCamera);	oglCamera	= NULL;
	delete(inpManager);	inpManager	= NULL;
	delete(objManager);	objManager	= NULL;
}

void update(void)
{
	oglTimer->update();
	oglCamera->update(oglTimer->getDeltaTime());

	if(inpManager->isKeyPressed("LINES"))		objManager->setDrawLines();
	if(inpManager->isKeyPressed("POINTS"))		objManager->setDrawPoints();
	if(inpManager->isKeyPressed("POLYGONS"))	objManager->setDrawPolygons();

	if(inpManager->isKeyPressed("MAPA"))		objManager->setSelectedObject("MAPA");
	if(inpManager->isKeyPressed("HOME"))		objManager->setSelectedObject("HOME");
	if(inpManager->isKeyPressed("DONA"))		objManager->setSelectedObject("DONA");
	if(inpManager->isKeyPressed("TEAPOT"))		objManager->setSelectedObject("TEAPOT");
	if(inpManager->isKeyPressed("TRIANGLE"))	objManager->setSelectedObject("TRIANGLE");
	if(inpManager->isKeyPressed("BEETHOVEN"))	objManager->setSelectedObject("BEETHOVEN");

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void render(void)
{
	update();
	oglCamera->render();
	objManager->drawObject();

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
	oglCamera->setScrWidth(sWidth);
	oglCamera->setScrHeight(sHeight);
}

int main(int argc, char *argv[])
{
	// 01) glutInit
	glutInit(&argc, argv);

	// 02) glutInitDisplayMode
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

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
