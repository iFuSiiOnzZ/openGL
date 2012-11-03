 #include "gl.h"												// Contiene los header y estructuras
																// de datos utilizado en la app

//P rototipos de funciones                      		
void inicialitzar(void); 									// Configuració bàsica del pipeline d’OpenGL
void representarEscena();									// Procés de dibuixat de l’escena
void processaTecles(unsigned char tecla, int x, int y);		// Processat dels events de teclat
void finalitzar(void);										// Espai per a l’alliberament de memòria
void reshape(int width, int height);						// Tamaño viewport

// Defines
#define kExitGl		27										// ESC - salir de openGL

#define kDrawAxis	'a'										// a   - dibujar o no ejes
#define kProyect	'p'										// p   - proyeccion ortografica o perspectiva

#define kDrawPns	'q'										// q   - dibujar puntos
#define kDrawLns	'w'										// w   - dibujar lineas
#define KDrawPls	'e'										// e   - dibujar poligonos

// Variables globales
int bDrawAxis 	= 1;										// Nos dice si dibujamos o no los ejes (A)
int bProyeccion	= 1;										// Nos dice si la camera es de pespectiva o ortografca

int bDrawLns	= 1;										// No dice si hay que dibujar lineas
int bDrawPns	= 0;										// No dice si hay que dibujar puntos
int bDrawPls	= 0;										// No dice si hay que dibujar planos

int bWidth		= 1024;										// Ancho pantalla
int bHeight		= 768;										// Alto pantalla

strObject cube = {0, 0, NULL, NULL};						// El cubo a mostrar

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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Color con el cual se resetea la pantalla
	glClear(GL_COLOR_BUFFER_BIT);			// Borrar la pantalla

	loadObject(&cube, (char *) "cubo.txt");	// Caragmos el cubo

	atexit(finalitzar);						// Funció que es cridarà en acabar. ALERTA:
											// Els usuaris de la llibreria freeglut poden
											// substituir-la pel mecanisme de control de la
											// funció glutLeaveMainLoop (evitant l’exit(0) a
											// la gestió d’events de teclat i assegurant la
											// crida de la funció finalitzar();).

}

void finalitzar(void)
{
	// Es crida just abans de sortir, després de l'exit(0), i és on alliberarem la memòria
	unloadObject(&cube);
}

void representarEscena(void)
{
	// Procés de dibuixat de l’escena
	// AQUI VA LA VOSTRA IMPLEMENTACIÓ
	glClear(GL_COLOR_BUFFER_BIT);										// Borrar la pantalla

	glMatrixMode(GL_PROJECTION);										// Modo proyección (Mundo)
	glLoadIdentity();													// Cargamos la matriz identidad

	if(!bProyeccion){ glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f); }	// Proyección ortográfica
	else{ gluPerspective(60.0f, bWidth/bHeight, 1.0f, 20.0f); }			// Proyeccion de perspectiva

	glMatrixMode(GL_MODELVIEW);											// Modo proyeccion (Objeto)
	glLoadIdentity();		

	if(bProyeccion)														// Si estamos en pryeccion de pespectiva
	{		
		gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z,	// Posicion de la camera
			  	  lookAtPosition.x, lookAtPosition.y, lookAtPosition.z,	// Donde mira la camera
			      0.0f, 1.0f, 0.0f);									// Esta de pie
	}

	if(bDrawAxis == 1){ drawAxis(2);}									// Si se dibujan o no los ejes

	if(bDrawLns) drawLines(&cube);										// Dibujamos el cubo con lineas
	else if(bDrawPls) drawPlans(&cube);									// Dibujamos el cubo con planos
	else if(bDrawPns) drawPoints(&cube, 2);								// Dibujamos el cubo con puntos

	glutSwapBuffers();													// Forzar el dibujo
}

void processaTecles(unsigned char tecla, int x, int y)
{
	if(tecla == kExitGl){ exit(0); } // Si l'usuari polsa la tecla ESC sortim

	if(tecla == kDrawAxis){ bDrawAxis = (bDrawAxis == 1)? 0 : 1; }
	if(tecla == kProyect){ bProyeccion = (bProyeccion == 1)? 0 : 1; }

	if(tecla == kDrawLns){ bDrawLns = 1; bDrawPls = 0; bDrawPns = 0; }
	if(tecla == KDrawPls){ bDrawLns = 0; bDrawPls = 1; bDrawPns = 0; }
	if(tecla == kDrawPns){ bDrawLns = 0; bDrawPls = 0; bDrawPns = 1; }

	glutPostRedisplay();
}

void reshape(int width, int height)
{
	bWidth = width; bHeight = height;
	glViewport(0, 0, width, height);									// Porcion en la cual se puede dibujar

	glMatrixMode(GL_PROJECTION);										// Modo proyección (Mundo)
	glLoadIdentity();													// Cargamos la matriz identidad

	if(!bProyeccion){ glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f); }	// Proyección ortográfica
	else{ gluPerspective(60.0f, width/height, 1.0f, 20.0f); }			// Proyeccion de perspetiva

	glMatrixMode(GL_MODELVIEW);											// Modo pryeccion (Objeto)
	glLoadIdentity();													// Cargamos la matriz identida
}