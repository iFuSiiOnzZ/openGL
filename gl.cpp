 #include "gl.h"												// Contiene los header y estructuras
																// de datos utilizado en la app

//P rototipos de funciones                      		
void inicialitzar(void); 									// Configuració bàsica del pipeline d’OpenGL
void representarEscena();									// Procés de dibuixat de l’escena
void processaTecles(unsigned char tecla, int x, int y);		// Processat dels events de teclat
void finalitzar(void);										// Espai per a l’alliberament de memòria
void reshape(int width, int height);						// Tamaño viewport


// Variables globales
int bDrawAxis = 1;											// Nos dice si dibujamos o no los ejes (A)
strObject cube = {0, 0, NULL, NULL};						// El cubo a mostrar

Vertex3D cameraPosition = {0.0f, 1.0f, 5.0f};				// Posicion inicial de la camera
Vertex3D lookAtPosition = {0.0f, 0.0f, 0.0f};				// Posicion inicial de done miramos		


int main(int argc, char **argv)
{
	// Inicialització de la finestra GLUT
	// AQUÍ HEU DE FER LES CRIDES PERTINENTS A:

	// 1) glutInit
	glutInit(&argc, argv);

	// 2) glutInitDisplayMode
	glutInitDisplayMode(GLUT_RGB);

	// 3) glutInitWindowPosition
	glutInitWindowPosition(0, 0);

	// 4) glutInitWindowSize
	glutInitWindowSize(1024, 768);

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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);										// Borrar la pantalla

	gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z,		// Posicion de la camera
			  lookAtPosition.x, lookAtPosition.y, lookAtPosition.z,		// Donde mira la camera
			  0.0f, 1.0f, 0.0f);										// Esta de pie

	if(bDrawAxis == 1){ drawAxis(2);}									// Si se dibujan o no los ejes
	drawLines(&cube);													// Dibujamos el cubo
}

void processaTecles(unsigned char tecla, int x, int y)
{
	if(tecla == 27){ exit(0); } // Si l'usuari polsa la tecla ESC sortim
	if(tecla == 97){ bDrawAxis = (bDrawAxis == 1)? 0 : 1; }
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);							// Porcion en la cual se puede dibujar

	glMatrixMode(GL_PROJECTION);								// Modo proyección
	glLoadIdentity();											// Cargamos la matriz identidad

	if(0){ glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f); }	// Proyección ortográfica
	else{ gluPerspective(60.0f, width/height, 1.0f, 20.0f); }

	glMatrixMode(GL_MODELVIEW);
}