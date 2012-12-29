#include "./OGLLoadObject.h"

OGLLoadObject::OGLLoadObject()
{

}

OGLLoadObject::~OGLLoadObject()
{

}

OGLObject OGLLoadObject::loadObject(std::string fName)
{
	OGLObject object;	InfoMinBox minBox;
	InfoFace iCara;		InfoVertex iVertex;

	bool V = false, VC = false, VNC = false, VTC = false;
	bool VNTC = false, VNCN = false, VTCN = false, VNTCN = false;

	std::string fType;
	std::ifstream objectStream;
	objectStream.open(fName.c_str(), std::ifstream::in);

	if(!objectStream.is_open())
	{
		printf("Error al abrir el archivo (%s)\n", fName.c_str());
		exit(EXIT_FAILURE);
	}

	printf("Cargando %s...\t",  fName.c_str());

	std::getline(objectStream, fType, '\n');
	if(fType.size() == 1) V = true;
	else if(fType.size() == 2) VC = true;
	else if(fType.size() == 3 && fType == "VNC") VNC = true;
	else if(fType.size() == 3 && fType == "VTC") VTC = true;
	else if(fType.size() == 4 && fType == "VNTC") VNTC = true;
	else if(fType.size() == 4 && fType == "VNCN") VNCN = true;
	else if(fType.size() == 4 && fType == "VTCN") VTCN = true;
	else if(fType.size() == 5) VNTCN = true;

	int nVertices = 0;
	objectStream >> nVertices;

	for(int i = 0; i < nVertices; i++)
	{
		float v = 0;
		objectStream >> v; iVertex.vertexPosition.x = v;
		objectStream >> v; iVertex.vertexPosition.y = v;
		objectStream >> v; iVertex.vertexPosition.z = v;

		if(i == 0)
		{
			minBox.minCoordenates.x = iVertex.vertexPosition.x;
			minBox.maxCoordenates.x = iVertex.vertexPosition.x;

			minBox.minCoordenates.y = iVertex.vertexPosition.y;
			minBox.maxCoordenates.y = iVertex.vertexPosition.y;

			minBox.minCoordenates.z = iVertex.vertexPosition.z;
			minBox.maxCoordenates.z = iVertex.vertexPosition.z;
		}

		if(minBox.maxCoordenates.x < iVertex.vertexPosition.x) minBox.maxCoordenates.x = iVertex.vertexPosition.x;
		if(minBox.minCoordenates.x > iVertex.vertexPosition.x) minBox.minCoordenates.x = iVertex.vertexPosition.x;

		if(minBox.maxCoordenates.y < iVertex.vertexPosition.y) minBox.maxCoordenates.y = iVertex.vertexPosition.y;
		if(minBox.minCoordenates.y > iVertex.vertexPosition.y) minBox.minCoordenates.y = iVertex.vertexPosition.y;

		if(minBox.maxCoordenates.z < iVertex.vertexPosition.z) minBox.maxCoordenates.z = iVertex.vertexPosition.z;
		if(minBox.minCoordenates.z > iVertex.vertexPosition.z) minBox.minCoordenates.z = iVertex.vertexPosition.z;

		if(VNC || VNTC || VNCN || VNTCN)
		{
			objectStream >> v; iVertex.vertexNormal.x = v;
			objectStream >> v; iVertex.vertexNormal.y = v;
			objectStream >> v; iVertex.vertexNormal.z = v;
		}

		if(VTCN || VNTCN || VNTC || VTC)
		{
			objectStream >> iVertex.tx;
			objectStream >> iVertex.ty;
		}

		object.setVertice(iVertex);
	}

	object.setMinBox(minBox);
	if(V)
	{
		return(object);
	}

	int nCaras = 0;
	objectStream >> nCaras;

	for(int i = 0; i < nCaras; i++)
	{
		int n = 0;
		int nV = 0;
		objectStream >> nV;

		for(int j = 0; j < nV; j++)
		{
			objectStream >> n;
			iCara.vCara.push_back(n);
		}

		if(VNTCN || VTCN || VNCN)
		{
			objectStream >> n; iCara.faceNormal.x = n;
			objectStream >> n; iCara.faceNormal.y = n;
			objectStream >> n; iCara.faceNormal.z = n;
		}
		else if(VC || VNC || VTC || VNTC)
		{
			vertexVector Vertices = object.getVertices();
			OGLVector3f v3f1 = Vertices[iCara.vCara[1]].vertexPosition - Vertices[iCara.vCara[0]].vertexPosition;
			OGLVector3f v3f2 = Vertices[iCara.vCara[2]].vertexPosition - Vertices[iCara.vCara[0]].vertexPosition;

			v3f1.normalize(); v3f2.normalize();
			iCara.faceNormal = v3f1.crossProduct(v3f2);
			iCara.faceNormal.normalize();

			for(unsigned int k = 0; k < iCara.vCara.size(); k++)
			{
				iCara.faceCenter = iCara.faceCenter + Vertices[iCara.vCara[k]].vertexPosition;
			}

			iCara.faceCenter = iCara.faceCenter / iCara.vCara.size();
		}

		object.setCara(iCara);
		iCara.vCara.clear();
	}

	if(VC || VTC || VTCN)
	{
		vertexVector iVertices = object.getVertices();
		faceVector iCaras = object.getCaras();

		for(unsigned int i = 0; i < iVertices.size(); i++)
		{
			for(unsigned int j = 0; j < iCaras.size(); j++)
			{
				for(unsigned int l = 0; l < iCaras[j].vCara.size(); l++)
				{
					if(iCaras[j].vCara[l] == i)
					{
						iVertices[i].vertexNormal = iVertices[i].vertexNormal + iCaras[j].faceNormal;
					}
				}
			}

			iVertices[i].vertexNormal.normalize();
			object.setNormalV(iVertices[i].vertexNormal.x, iVertices[i].vertexNormal.y, iVertices[i].vertexNormal.z, i);
		}
	}

	printf("echo\n");
	return(object);
}
