#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "./OGLTimer.h"
#include "./OGLVector3f.h"
#include "./OGLFpsCamera.h"
#include "./OGLFpsCamera.h"
#include "./OGLOrthoCamera.h"
#include "./OGLInputManager.h"
#include "./OGLObjectManager.h"
#include "./OGLCameraManager.h"
#include "./OGLPerspectiveCamera.h"

void	render		(void);
void	update		(void);

void	finish		(void);
void	start		(void);

void	reshape		(int, int);

void	keySpec		(int, int, int);
void	keyNorm		(unsigned char, int, int);

void	mouseProcess(int, int, int, int);
void	mouseMotion	(int, int);


typedef struct
{
	GLfloat pos[4];
	GLfloat diffuse[4];
	GLfloat ambient[4];
	GLfloat specular[4];
}light_t;

light_t light = {
	{0.0f, 30.0f, 100.0f, 1.0f},
	{1.0f, 1.0f, 1.0f, 1.0f},
	{0.0f, 0.0f, 0.0f, 1.0f},
	{1.0f, 1.0f, 1.0f, 1.0f}
};

int sWidth	= 1024;
int sHeight	= 768;

OGLTimer			*oglTimer	= NULL;
OGLInputManager		*inpManager	= NULL;
OGLObjectManager	*objManager	= NULL;
OGLCameraManager	*camManager	= NULL;

void start(void)
{
	oglTimer	= new OGLTimer(0);
	objManager	= OGLObjectManager::getInstance();
	inpManager	= OGLInputManager::getInstance(sWidth, sHeight);

	camManager = OGLCameraManager::getInstance("2D", new OGLOrthoCamera(sWidth, sHeight, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f, -5.0f));
	camManager->addCamera("SFPS", new OGLPerspectiveCamera(sWidth, sHeight, 60.0f, 1, 1000));
	camManager->addCamera("FPS", new OGLFpsCamera(sWidth, sHeight, 60.0f, 1, 1000));

	camManager->selectCamera("FPS");
	camManager->getCamera()->setPosition(OGLVector3f(3.0f, 2.0f, 50.0f));
	camManager->getCamera()->setLookAt(OGLVector3f(0.0f, 0.0f, 0.0f));
	camManager->getCamera()->setUp(OGLVector3f(0.0f, 1.0f, 0.0f));

	camManager->selectCamera("SFPS");
	camManager->getCamera()->setPosition(OGLVector3f(3.0f, 2.0f, 50.0f));
	camManager->getCamera()->setLookAt(OGLVector3f(0.0f, 0.0f, 0.0f));
	camManager->getCamera()->setUp(OGLVector3f(0.0f, 1.0f, 0.0f));


	inpManager->addKey("LINES",		'w');
	inpManager->addKey("CAMERA",	'p');
	inpManager->addKey("POINTS",	'q');
	inpManager->addKey("POLYGONS",	'e');

	inpManager->addKey("MAPA",		'1');
	inpManager->addKey("DONA",		'2');
	inpManager->addKey("HOME",		'3');
	inpManager->addKey("TEAPOT",	'4');
	inpManager->addKey("TRIANGLE",	'5');
	inpManager->addKey("BEETHOVEN", '6');

	inpManager->addKey("SZ+",		'+');
	inpManager->addKey("SZ-",		'-');
	inpManager->addKey("DELETE",	'x');

	inpManager->addKeyS("UP", GLUT_KEY_UP);
	inpManager->addKeyS("DOWN", GLUT_KEY_DOWN);
	inpManager->addKeyS("LEFT", GLUT_KEY_LEFT);
	inpManager->addKeyS("RIGHT", GLUT_KEY_RIGHT);

	objManager->loadObject("MAPA",		"./3d/0_mapa.3d");
	objManager->loadObject("DONA",		"./3d/0_dona.3d");
	objManager->loadObject("HOME",		"./3d/0_home.3d");
	objManager->loadObject("TEAPOT",	"./3d/0_teapot.3d");
	objManager->loadObject("TRIANGLE",	"./3d/0_triangle.3d");
	objManager->loadObject("BEETHOVEN", "./3d/0_beethoven.3d");

	objManager->setSelectedObject("BEETHOVEN");
	objManager->setDrawAxis();

	atexit(finish);
}

void finish(void)
{
	delete(oglTimer);	oglTimer	= NULL;
	delete(camManager);	camManager	= NULL;
	delete(inpManager);	inpManager	= NULL;
	delete(objManager);	objManager	= NULL;
}

void update(void)
{
	oglTimer->update();
	camManager->update(oglTimer->getDeltaTime());

	if(inpManager->isKeyPressed("LINES"))		objManager->setDrawLines();
	if(inpManager->isKeyPressed("POINTS"))		objManager->setDrawPoints();
	if(inpManager->isKeyPressed("POLYGONS"))	objManager->setDrawPolygons();

	if(inpManager->isKeyPressed("CAMERA") && oglTimer->isEndTimeObject("CAMERA", 0.5f))
	{
		camManager->nextCamera();
	}

	if(inpManager->isKeyPressed("DELETE") && oglTimer->isEndTimeObject("DELETE", 0.5f))
	{
		objManager->setDrawObj();
	}

	if(inpManager->isKeyPressed("SZ+") && oglTimer->isEndTimeObject("SZ+", 0.5f))
	{
		objManager->setObjSize(2.0f);
	}

	if(inpManager->isKeyPressed("SZ-") && oglTimer->isEndTimeObject("SZ+", 0.5f))
	{
		objManager->setObjSize(0.5f);
	}

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
	camManager->render();
	objManager->drawObject();

	char text[100];
	sprintf(text, "Grafics per computador (FPS: %d)", oglTimer->getFps());
	glutSetWindowTitle(text);

	glutSwapBuffers();
	glutPostRedisplay();
}

void keySpec(int key, int x, int y)
{
	inpManager->updateKeyS(key);
	inpManager->updateMouse(x, y, oglTimer->getDeltaTime());
}

void keyNorm(unsigned char key, int x, int y)
{
	if(key == 27) exit(EXIT_SUCCESS);

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

	camManager->getCamera()->addYaw(inpManager->getYaw() * oglTimer->getDeltaTime());
	camManager->getCamera()->addPitch(inpManager->getPitch() * oglTimer->getDeltaTime());

	if(inpManager->isLeftButtonPress())
	{
		objManager->setAngle(inpManager->getYaw() * oglTimer->getDeltaTime(), inpManager->getPitch() * oglTimer->getDeltaTime());
	}
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
	camManager->setScreenSize(sWidth, sHeight);
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
	glutKeyboardFunc(keyNorm);

	// 08)
	glutKeyboardUpFunc(keyNorm);

	// 09)
	glutSpecialFunc(keySpec);

	// 10)
	glutSpecialUpFunc(keySpec);

	// 11)
	glutMouseFunc(mouseProcess);

	// 12)
	glutMotionFunc(mouseMotion);

	// 13)
	glutPassiveMotionFunc(mouseMotion);

	// 14)
	glutReshapeFunc(reshape);

	// 15)
	glutMainLoop();


	return(EXIT_SUCCESS);
}
