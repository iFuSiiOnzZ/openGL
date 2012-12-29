#include "loadObject.h"


cLoadObject *cLoadObject::hInstance = NULL;

cLoadObject::cLoadObject()
{
	memset(&this->selectedObject, 0, sizeof(strObject));
}

cLoadObject::~cLoadObject()
{
	
}

cLoadObject *cLoadObject::getInstance()
{
	if(hInstance == NULL)
	{
		hInstance = new cLoadObject();
	}

	return(hInstance);
}

void cLoadObject::release(void)
{
	for(std::map<std::string, strObject>::iterator it = this->cloObjects.begin(); it != this->cloObjects.end(); it++)
	{
		this->unloadObject(it->first);
	}

	this->cloObjects.clear();
}

void cLoadObject::setSelectedObject(std::string oName)
{
	strObject object;
	memset(&object, 0, sizeof(strObject));

	std::map<std::string, strObject>::iterator it = this->cloObjects.find(oName);
	this->selectedObject = (it == this->cloObjects.end())? object : it->second;
}

strObject cLoadObject::getObject(std::string oName)
{
	strObject object;
	memset(&object, 0, sizeof(strObject));

	std::map<std::string, strObject>::iterator it = this->cloObjects.find(oName);
	return((it == this->cloObjects.end())? object : it->second);
}

strObject cLoadObject::getObject()
{
	return(this->selectedObject);
}


bool cLoadObject::loadObject(std::string oName, std::string fName)
{
	strObject object;

	FILE *pFile = NULL;
	if((pFile = fopen(fName.c_str(), "r")) == NULL)
	{
		return(false);
	}

	std::map<std::string, strObject>::iterator it = this->cloObjects.find(oName);
	if(it != this->cloObjects.end()){this->unloadObject(oName);}

	fscanf(pFile, "%d", &object.nVertices);
	object.pVertices = (float **) malloc (object.nVertices * sizeof(float *));

	for(int i = 0; i < object.nVertices; i++)
	{
		object.pVertices[i] = (float *) malloc (3 * sizeof(float));
		fscanf(pFile, "%f %f %f",&object.pVertices[i][0], &object.pVertices[i][1], &object.pVertices[i][2]);
	}


	fscanf(pFile, "%d", &object.nCaras);
	object.uCaras = (int **) malloc (object.nCaras * sizeof(int *));

	for(int i = 0; i < object.nCaras; i++)
	{
		int m = 0;
		fscanf(pFile, "%d", &m);
		object.uCaras[i] = (int *) malloc ((m + 1) * sizeof(int));
		
		object.uCaras[i][0] = m;
		for(int j = 1; j <= object.uCaras[i][0]; j++)
		{
			fscanf(pFile, "%d", &object.uCaras[i][j]);
		}
	}

	fclose(pFile);
	this->cloObjects.insert(std::pair<std::string, strObject>(oName, object));

	return(true);
}

bool cLoadObject::unloadObject(std::string oName)
{
	std::map<std::string, strObject>::iterator it = this->cloObjects.find(oName);

	if(it == this->cloObjects.end())
	{
		return(false);
	}


	for(int i = 0; i < it->second.nVertices; i++)
	{
		free(it->second.pVertices[i]);
		it->second.pVertices[i] = NULL;
	}

	for(int i = 0; i < it->second.nCaras; i++)
	{
		free(it->second.uCaras[i]);
		it->second.uCaras[i] = NULL;
	}

	free(it->second.pVertices);
	it->second.pVertices = NULL;

	free(it->second.uCaras);
	it->second.uCaras = NULL;

	this->cloObjects.erase(oName);
	return(true);
}