#include "./OGLObject.h"
#include <cstdio>

OGLObject::OGLObject()
{
	this->v_Draw = true;
	this->v_DrawAxis = false;
	this->v_DrawLines = true;
	this->v_DrawMinBox = false;
	this->v_DrawPoints = false;
	this->v_DrawNormals = false;
	this->v_DisplayList = false;
	this->v_DrawPolygons = false;

	this->v_Pos = OGLVector3f();
	this->v_Yaw = 0.0f;
	this->v_Size = 1.0f;
	this->v_Pitch = 0.0f;
}

OGLObject::~OGLObject()
{
	this->v_Caras.clear();
	this->v_Vertices.clear();

	this->vertexArray.clear();
	this->indexArray.clear();
}

int OGLObject::getCSize(void)
{
	return(this->v_Caras.size());
}

int OGLObject::getVSize(void)
{
	return(this->v_Vertices.size());
}

InfoFace OGLObject::getCara(int nCara) const
{
	return(this->v_Caras.at(nCara));
}

faceVector OGLObject::getCaras(void) const
{
	return(this->v_Caras);
}

InfoVertex OGLObject::getVertice(int nVertice) const
{
	return(this->v_Vertices.at(nVertice));
}

vertexVector OGLObject::getVertices(void) const
{
	return(this->v_Vertices);
}

void OGLObject::setCara(const InfoFace &iCara)
{
	this->v_Caras.push_back(iCara);
}

void OGLObject::setCaras(const faceVector &vCaras)
{
	this->v_Caras = vCaras;
}

void OGLObject::setVertice(const InfoVertex &iVertice)
{
	this->v_Vertices.push_back(iVertice);
}

void OGLObject::setVertices(const vertexVector &vVertices)
{
	this->v_Vertices = vVertices;
}

InfoMinBox OGLObject::getMinBox(void) const
{
	return(this->v_MinBox);
}

void OGLObject::setMinBox(InfoMinBox minBox)
{
	this->v_MinBox.maxCoordenates = minBox.maxCoordenates;
	this->v_MinBox.minCoordenates = minBox.minCoordenates;

	this->v_Pos.x  = ((this->v_MinBox.maxCoordenates.x - this->v_MinBox.minCoordenates.x) / 2.0f) + this->v_MinBox.minCoordenates.x;
	this->v_Pos.y  = ((this->v_MinBox.maxCoordenates.y - this->v_MinBox.minCoordenates.y) / 2.0f) + this->v_MinBox.minCoordenates.y;
	this->v_Pos.z  = ((this->v_MinBox.maxCoordenates.z - this->v_MinBox.minCoordenates.z) / 2.0f) + this->v_MinBox.minCoordenates.z;
}
void OGLObject::setNormalC(float nx, float ny, float nz, int n)
{
	this->v_Caras.at(n).faceNormal.x = nx;
	this->v_Caras.at(n).faceNormal.y = ny;
	this->v_Caras.at(n).faceNormal.z = nz;
}

void OGLObject::setNormalV(float nx, float ny, float nz, int n)
{
	this->v_Vertices.at(n).vertexNormal.x = nx;
	this->v_Vertices.at(n).vertexNormal.y = ny;
	this->v_Vertices.at(n).vertexNormal.z = nz;
}

void OGLObject::setPos(const OGLVector3f &pos)
{
	this->v_Pos = this->v_Pos + pos;
}

void OGLObject::setAngle(float yaw, float pitch)
{
	this->v_Yaw += yaw;
	this->v_Pitch += pitch;

	if(this->v_Yaw > (2.0f * 3.141592f)) this->v_Yaw -= (2.0f * 3.141592f);
	if(this->v_Yaw < (0.0f)) this->v_Yaw += (2.0f * 3.141592f);

	if(this->v_Pitch > (2.0f * 3.141592f)) this->v_Pitch -= (2.0f * 3.141592f);
	if(this->v_Pitch < (0.0f)) this->v_Pitch += (2.0f * 3.141592f);
}

void OGLObject::rDraw(void)
{
	this->v_DrawLines = false;
	this->v_DrawPoints = false;
	this->v_DrawPolygons = false;
}

bool OGLObject::getDraw(void)
{
	return(this->v_Draw);
}

void OGLObject::setDraw(void)
{
	this->v_Draw = !this->v_Draw;
}

void OGLObject::setDrawAxis(void)
{
	this->v_DrawAxis = !this->v_DrawAxis;
}

void OGLObject::setDrawMinBox(void)
{
	this->v_DrawMinBox = !this->v_DrawMinBox;
}

void OGLObject::setDrawNormals(void)
{
	this->v_DrawNormals = !this->v_DrawNormals;
}

void OGLObject::setDrawLines(void)
{
	this->rDraw();
	this->v_DrawLines = !this->v_DrawLines;
}

void OGLObject::setDrawPoints(void)
{
	this->rDraw();
	this->v_DrawPoints = !this->v_DrawPoints;
}

void OGLObject::setDrawPolygons(void)
{
	this->rDraw();
	this->v_DrawPolygons = !this->v_DrawPolygons;
}


OGLVector3f OGLObject::getPosition(void)
{
	return(this->v_Pos);
}

float OGLObject::getPitch(void)
{
	return(this->v_Pitch);
}

float OGLObject::getYaw(void)
{
	return(this->v_Yaw);
}

void OGLObject::setSize(float sz)
{
	this->v_Size *= sz;
}

float OGLObject::getSize(void)
{
	return(this->v_Size);
}

void OGLObject::draw(void)
{
	if(this->v_Draw)
	{
		if(this->v_DrawAxis) this->DrawAxis();
		if(this->v_DrawLines) this->DrawLines();
		if(this->v_DrawMinBox) this->DrawMinBox();
		if(this->v_DrawPoints) this->DrawPoints();
		if(this->v_DrawNormals) this->DrawNormals();
		if(this->v_DrawPolygons) this->DrawPolygons();
	}
}

void OGLObject::genVertexArray(void)
{

	for(vertexVector::iterator it1 = this->v_Vertices.begin(); it1 != this->v_Vertices.end(); it1++)
	{
		this->vertexArray.push_back((*it1).vertexPosition.x);
		this->vertexArray.push_back((*it1).vertexPosition.y);
		this->vertexArray.push_back((*it1).vertexPosition.z);
	}

	for(faceVector::iterator it1 = this->v_Caras.begin(); it1 != this->v_Caras.end(); it1++)
	{
		for(intVector::iterator it2 = it1->vCara.begin(); it2 != it1->vCara.end(); it2++)
		{
			this->indexArray.push_back((*it2));
		}
	}
}

void OGLObject::DrawAxis(void)
{
	float x  = ((this->v_MinBox.maxCoordenates.x - this->v_MinBox.minCoordenates.x) / 2.0f) + this->v_MinBox.minCoordenates.x;
	float y  = ((this->v_MinBox.maxCoordenates.y - this->v_MinBox.minCoordenates.y) / 2.0f) + this->v_MinBox.minCoordenates.y;
	float z  = ((this->v_MinBox.maxCoordenates.z - this->v_MinBox.minCoordenates.z) / 2.0f) + this->v_MinBox.minCoordenates.z;
	float sz = 3.0f;

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
			glVertex3f(x, y, z);
			glVertex3f(x + sz * 1.0f, y, z);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
			glVertex3f(x, y, z);
			glVertex3f(x, y + sz * 1.0f, z);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
			glVertex3f(x, y, z);
			glVertex3f(x, y, z + sz * 1.0f);
	glEnd();
}

void OGLObject::DrawLines(void)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, &this->vertexArray[0]);
		glDrawElements(GL_LINE_LOOP, this->indexArray.size(), GL_UNSIGNED_INT, &this->indexArray[0]);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void OGLObject::DrawPoints(void)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, &this->vertexArray[0]);
		glDrawElements(GL_POINTS, this->indexArray.size(), GL_UNSIGNED_INT, &this->indexArray[0]);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void OGLObject::DrawPolygons(void)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, &this->vertexArray[0]);
		glDrawElements(GL_TRIANGLES, this->indexArray.size(), GL_UNSIGNED_INT, &this->indexArray[0]);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void OGLObject::DrawNormals(void)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		for(faceVector::iterator it = this->v_Caras.begin(); it != this->v_Caras.end(); it++)
		{
			OGLVector3f v3f = it->faceCenter + it->faceNormal;
			glVertex3f(it->faceCenter.x, it->faceCenter.y, it->faceCenter.z);
			glVertex3f(v3f.x, v3f.y, v3f.z);
		}
	glEnd();
}

void OGLObject::DrawMinBox(void)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex3f(this->v_MinBox.minCoordenates.x, this->v_MinBox.minCoordenates.y, this->v_MinBox.minCoordenates.z);		// 0
		glVertex3f(this->v_MinBox.maxCoordenates.x, this->v_MinBox.minCoordenates.y, this->v_MinBox.minCoordenates.z);		// 1

		glVertex3f(this->v_MinBox.maxCoordenates.x, this->v_MinBox.minCoordenates.y, this->v_MinBox.minCoordenates.z);		// 1
		glVertex3f(this->v_MinBox.maxCoordenates.x, this->v_MinBox.minCoordenates.y, this->v_MinBox.maxCoordenates.z);		// 2

		glVertex3f(this->v_MinBox.maxCoordenates.x, this->v_MinBox.minCoordenates.y, this->v_MinBox.maxCoordenates.z);		// 2
		glVertex3f(this->v_MinBox.minCoordenates.x, this->v_MinBox.minCoordenates.y, this->v_MinBox.maxCoordenates.z);		// 3

		glVertex3f(this->v_MinBox.minCoordenates.x, this->v_MinBox.minCoordenates.y, this->v_MinBox.maxCoordenates.z);		// 3
		glVertex3f(this->v_MinBox.minCoordenates.x, this->v_MinBox.minCoordenates.y, this->v_MinBox.minCoordenates.z);		// 0

		glVertex3f(this->v_MinBox.minCoordenates.x, this->v_MinBox.maxCoordenates.y, this->v_MinBox.maxCoordenates.z);		// 4
		glVertex3f(this->v_MinBox.minCoordenates.x, this->v_MinBox.maxCoordenates.y, this->v_MinBox.minCoordenates.z);		// 5

		glVertex3f(this->v_MinBox.minCoordenates.x, this->v_MinBox.maxCoordenates.y, this->v_MinBox.minCoordenates.z);		// 5
		glVertex3f(this->v_MinBox.maxCoordenates.x, this->v_MinBox.maxCoordenates.y, this->v_MinBox.minCoordenates.z);		// 6

		glVertex3f(this->v_MinBox.maxCoordenates.x, this->v_MinBox.maxCoordenates.y, this->v_MinBox.minCoordenates.z);		// 6
		glVertex3f(this->v_MinBox.maxCoordenates.x, this->v_MinBox.maxCoordenates.y, this->v_MinBox.maxCoordenates.z);		// 7

		glVertex3f(this->v_MinBox.maxCoordenates.x, this->v_MinBox.maxCoordenates.y, this->v_MinBox.maxCoordenates.z);		// 7
		glVertex3f(this->v_MinBox.minCoordenates.x, this->v_MinBox.maxCoordenates.y, this->v_MinBox.maxCoordenates.z);		// 4

		glVertex3f(this->v_MinBox.minCoordenates.x, this->v_MinBox.minCoordenates.y, this->v_MinBox.minCoordenates.z);		// 0
		glVertex3f(this->v_MinBox.minCoordenates.x, this->v_MinBox.maxCoordenates.y, this->v_MinBox.minCoordenates.z);		// 5

		glVertex3f(this->v_MinBox.maxCoordenates.x, this->v_MinBox.minCoordenates.y, this->v_MinBox.minCoordenates.z);		// 1
		glVertex3f(this->v_MinBox.maxCoordenates.x, this->v_MinBox.maxCoordenates.y, this->v_MinBox.minCoordenates.z);		// 6

		glVertex3f(this->v_MinBox.maxCoordenates.x, this->v_MinBox.minCoordenates.y, this->v_MinBox.maxCoordenates.z);		// 2
		glVertex3f(this->v_MinBox.maxCoordenates.x, this->v_MinBox.maxCoordenates.y, this->v_MinBox.maxCoordenates.z);		// 7

		glVertex3f(this->v_MinBox.minCoordenates.x, this->v_MinBox.minCoordenates.y, this->v_MinBox.maxCoordenates.z);		// 3
		glVertex3f(this->v_MinBox.minCoordenates.x, this->v_MinBox.maxCoordenates.y, this->v_MinBox.maxCoordenates.z);		// 4
	glEnd();
}
