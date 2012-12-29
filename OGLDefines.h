#pragma once

#include "./OGLVector3f.h"
#include <vector>
#include <string>
#include <map>

#define	OGLPI	3.141592f

typedef std::map<std::string, std::map<unsigned char, bool> > CharKeysMap;
typedef std::map<std::string, std::map<unsigned int, bool> > IntKeysMap;

typedef struct InfoMinBox	InfoMinBox;
typedef struct InfoVertex	InfoVertex;
typedef struct InfoFace 	InfoFace;

typedef std::vector<InfoFace>		faceVector;
typedef std::vector<InfoVertex>		vertexVector;
typedef std::vector<unsigned int>	intVector;


struct InfoVertex
{
	int tx, ty;
	OGLVector3f vertexNormal;
	OGLVector3f vertexPosition;
};

struct InfoFace
{
	intVector vCara;
	OGLVector3f faceNormal;
	OGLVector3f faceCenter;
};

struct InfoMinBox
{
	OGLVector3f	minCoordenates;
	OGLVector3f maxCoordenates;
};
