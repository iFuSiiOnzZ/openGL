#include "loadObject.h"

int loadObject(strObject *object, char *fName)
{
	FILE *pFile = NULL;
	bzero(object, sizeof(strObject));

	if((pFile = fopen(fName, "r")) == NULL)
	{
		return(0);
	}

	fscanf(pFile, "%d", &object->nVertices);
	object->pVertices = (float **) malloc (object->nVertices * sizeof(float *));

	for(int i = 0; i < object->nVertices; i++)
	{
		object->pVertices[i] = (float *) malloc (3 * sizeof(float));
		fscanf(pFile, "%f %f %f",&object->pVertices[i][0], &object->pVertices[i][1], &object->pVertices[i][2]);
	}

	fscanf(pFile, "%d", &object->nCaras);
	object->uCaras = (int **) malloc (object->nCaras * sizeof(int *));

	for(int i = 0; i < object-> nCaras; i++)
	{
		int m = 0;
		fscanf(pFile, "%d", &m);
		object->uCaras[i] = (int *) malloc ((m + 1) * sizeof(int));
		
		object->uCaras[i][0] = m;
		for(int j = 1; j <= object->uCaras[i][0]; j++)
		{
			fscanf(pFile, "%d", &object->uCaras[i][j]);
		}
	}

	fclose(pFile);
	return(1);
}

void unloadObject(strObject *object)
{

	for(int i = 0; i < object->nVertices; i++)
	{
		free(object->pVertices[i]);
		object->pVertices[i] = NULL;
	}

	for(int i = 0; i < object->nCaras; i++)
	{
		free(object->uCaras[i]);
		object->uCaras[i] = NULL;
	}

	free(object->pVertices);
	object->pVertices = NULL;

	free(object->uCaras);
	object->uCaras = NULL;
}