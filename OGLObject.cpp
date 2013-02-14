#include "./OGLObject.h"
#include <cstdio>

OGLObject::OGLObject()
{
	this->mDraw = true;
	this->mDrawAxis = false;
	this->mDrawLines = true;
	this->mDrawMinBox = false;
	this->mDrawPoints = false;
	this->mDrawNormals = false;
	this->mDisplayList = false;
	this->mDrawPolygons = false;

	this->mPos = OGLVector3f();
	this->mYaw = 0.0f;
	this->mSize = 1.0f;
	this->mPitch = 0.0f;
}

OGLObject::~OGLObject()
{
	this->mCaras.clear();
	this->mVertices.clear();

	this->vertexArray.clear();
	this->indexArray.clear();
}

int OGLObject::getCSize(void)
{
	return(this->mCaras.size());
}

int OGLObject::getVSize(void)
{
	return(this->mVertices.size());
}

InfoFace OGLObject::getCara(int nCara) const
{
	return(this->mCaras.at(nCara));
}

faceVector OGLObject::getCaras(void) const
{
	return(this->mCaras);
}

InfoVertex OGLObject::getVertice(int nVertice) const
{
	return(this->mVertices.at(nVertice));
}

vertexVector OGLObject::getVertices(void) const
{
	return(this->mVertices);
}

void OGLObject::setCara(const InfoFace &iCara)
{
	this->mCaras.push_back(iCara);
}

void OGLObject::setCaras(const faceVector &vCaras)
{
	this->mCaras = vCaras;
}

void OGLObject::setVertice(const InfoVertex &iVertice)
{
	this->mVertices.push_back(iVertice);
}

void OGLObject::setVertices(const vertexVector &vVertices)
{
	this->mVertices = vVertices;
}

InfoMinBox OGLObject::getMinBox(void) const
{
	return(this->mMinBox);
}

void OGLObject::setMinBox(InfoMinBox minBox)
{
	this->mMinBox.maxCoordenates = minBox.maxCoordenates;
	this->mMinBox.minCoordenates = minBox.minCoordenates;

	this->mPos.x  = ((this->mMinBox.maxCoordenates.x - this->mMinBox.minCoordenates.x) / 2.0f) + this->mMinBox.minCoordenates.x;
	this->mPos.y  = ((this->mMinBox.maxCoordenates.y - this->mMinBox.minCoordenates.y) / 2.0f) + this->mMinBox.minCoordenates.y;
	this->mPos.z  = ((this->mMinBox.maxCoordenates.z - this->mMinBox.minCoordenates.z) / 2.0f) + this->mMinBox.minCoordenates.z;
}
void OGLObject::setNormalC(float nx, float ny, float nz, int n)
{
	this->mCaras.at(n).faceNormal.x = nx;
	this->mCaras.at(n).faceNormal.y = ny;
	this->mCaras.at(n).faceNormal.z = nz;
}

void OGLObject::setNormalV(float nx, float ny, float nz, int n)
{
	this->mVertices.at(n).vertexNormal.x = nx;
	this->mVertices.at(n).vertexNormal.y = ny;
	this->mVertices.at(n).vertexNormal.z = nz;
}

void OGLObject::setPos(const OGLVector3f &pos)
{
	this->mPos = this->mPos + pos;
}

void OGLObject::setAngle(float yaw, float pitch)
{
	this->mYaw += yaw;
	this->mPitch += pitch;

	if(this->mYaw > (2.0f * 3.141592f)) this->mYaw -= (2.0f * 3.141592f);
	if(this->mYaw < (0.0f)) this->mYaw += (2.0f * 3.141592f);

	if(this->mPitch > (2.0f * 3.141592f)) this->mPitch -= (2.0f * 3.141592f);
	if(this->mPitch < (0.0f)) this->mPitch += (2.0f * 3.141592f);
}

void OGLObject::rDraw(void)
{
	this->mDrawLines = false;
	this->mDrawPoints = false;
	this->mDrawPolygons = false;
}

bool OGLObject::getDraw(void)
{
	return(this->mDraw);
}

void OGLObject::setDraw(void)
{
	this->mDraw = !this->mDraw;
}

void OGLObject::setDrawAxis(void)
{
	this->mDrawAxis = !this->mDrawAxis;
}

void OGLObject::setDrawMinBox(void)
{
	this->mDrawMinBox = !this->mDrawMinBox;
}

void OGLObject::setDrawNormals(void)
{
	this->mDrawNormals = !this->mDrawNormals;
}

void OGLObject::setDrawLines(void)
{
	this->rDraw();
	this->mDrawLines = !this->mDrawLines;
}

void OGLObject::setDrawPoints(void)
{
	this->rDraw();
	this->mDrawPoints = !this->mDrawPoints;
}

void OGLObject::setDrawPolygons(void)
{
	this->rDraw();
	this->mDrawPolygons = !this->mDrawPolygons;
}


OGLVector3f OGLObject::getPosition(void)
{
	return(this->mPos);
}

float OGLObject::getPitch(void)
{
	return(this->mPitch);
}

float OGLObject::getYaw(void)
{
	return(this->mYaw);
}

void OGLObject::setSize(float sz)
{
	this->mSize *= sz;
}

float OGLObject::getSize(void)
{
	return(this->mSize);
}

void OGLObject::resize(void)
{
	glTranslatef(this->mPos.x, this->mPos.y, this->mPos.z);
			glScalef(this->mSize, this->mSize, this->mSize);
	glTranslatef(-this->mPos.x, -this->mPos.y, -this->mPos.z);
}

void OGLObject::rotate(void)
{
	glTranslatef(this->mPos.x, this->mPos.y, this->mPos.z);
		glRotatef(-this->mYaw * 180.0f / 3.141592, 0.0f, 1.0f, 0.0f);
		glRotatef(-this->mPitch * 180.0f / 3.141592, 1.0f, 0.0f, 0.0f);
	glTranslatef(-this->mPos.x, -this->mPos.y, -this->mPos.z);
}

void OGLObject::translate(void)
{
	glTranslatef(this->mPos.x, this->mPos.y, this->mPos.z);
}

void OGLObject::draw(void)
{
	if(this->mDraw)
	{
		glPushMatrix();
			this->resize();
			glPushMatrix();
				this->rotate();
				glPushMatrix();
					this->translate();
					if(this->mDrawAxis) this->DrawAxis();
					if(this->mDrawLines) this->DrawLines();
					if(this->mDrawMinBox) this->DrawMinBox();
					if(this->mDrawPoints) this->DrawPoints();
					if(this->mDrawNormals) this->DrawNormals();
					if(this->mDrawPolygons) this->DrawPolygons();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	}
}

void OGLObject::genVertexArray(void)
{

	for(vertexVector::iterator it1 = this->mVertices.begin(); it1 != this->mVertices.end(); it1++)
	{
		this->vertexArray.push_back(it1->vertexPosition.x);
		this->vertexArray.push_back(it1->vertexPosition.y);
		this->vertexArray.push_back(it1->vertexPosition.z);

		this->normalArray.push_back(it1->vertexNormal.x);
		this->normalArray.push_back(it1->vertexNormal.y);
		this->normalArray.push_back(it1->vertexNormal.z);
	}

	for(faceVector::iterator it1 = this->mCaras.begin(); it1 != this->mCaras.end(); it1++)
	{
		for(intVector::iterator it2 = it1->vCara.begin(); it2 != it1->vCara.end(); it2++)
		{
			this->indexArray.push_back((*it2));
		}

		this->normalArray.push_back(it1->faceNormal.x);
		this->normalArray.push_back(it1->faceNormal.y);
		this->normalArray.push_back(it1->faceNormal.z);
	}
}

void OGLObject::DrawAxis(void)
{
	float x  = ((this->mMinBox.maxCoordenates.x - this->mMinBox.minCoordenates.x) / 2.0f) + this->mMinBox.minCoordenates.x;
	float y  = ((this->mMinBox.maxCoordenates.y - this->mMinBox.minCoordenates.y) / 2.0f) + this->mMinBox.minCoordenates.y;
	float z  = ((this->mMinBox.maxCoordenates.z - this->mMinBox.minCoordenates.z) / 2.0f) + this->mMinBox.minCoordenates.z;
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
	glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
			glNormalPointer(GL_FLOAT, 0, &this->normalArray[0]);
			glVertexPointer(3, GL_FLOAT, 0, &this->vertexArray[0]);
			glDrawElements(GL_TRIANGLES, this->indexArray.size(), GL_UNSIGNED_INT, &this->indexArray[0]);
		glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void OGLObject::DrawNormals(void)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		for(faceVector::iterator it = this->mCaras.begin(); it != this->mCaras.end(); it++)
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
		glVertex3f(this->mMinBox.minCoordenates.x, this->mMinBox.minCoordenates.y, this->mMinBox.minCoordenates.z);		// 0
		glVertex3f(this->mMinBox.maxCoordenates.x, this->mMinBox.minCoordenates.y, this->mMinBox.minCoordenates.z);		// 1

		glVertex3f(this->mMinBox.maxCoordenates.x, this->mMinBox.minCoordenates.y, this->mMinBox.minCoordenates.z);		// 1
		glVertex3f(this->mMinBox.maxCoordenates.x, this->mMinBox.minCoordenates.y, this->mMinBox.maxCoordenates.z);		// 2

		glVertex3f(this->mMinBox.maxCoordenates.x, this->mMinBox.minCoordenates.y, this->mMinBox.maxCoordenates.z);		// 2
		glVertex3f(this->mMinBox.minCoordenates.x, this->mMinBox.minCoordenates.y, this->mMinBox.maxCoordenates.z);		// 3

		glVertex3f(this->mMinBox.minCoordenates.x, this->mMinBox.minCoordenates.y, this->mMinBox.maxCoordenates.z);		// 3
		glVertex3f(this->mMinBox.minCoordenates.x, this->mMinBox.minCoordenates.y, this->mMinBox.minCoordenates.z);		// 0

		glVertex3f(this->mMinBox.minCoordenates.x, this->mMinBox.maxCoordenates.y, this->mMinBox.maxCoordenates.z);		// 4
		glVertex3f(this->mMinBox.minCoordenates.x, this->mMinBox.maxCoordenates.y, this->mMinBox.minCoordenates.z);		// 5

		glVertex3f(this->mMinBox.minCoordenates.x, this->mMinBox.maxCoordenates.y, this->mMinBox.minCoordenates.z);		// 5
		glVertex3f(this->mMinBox.maxCoordenates.x, this->mMinBox.maxCoordenates.y, this->mMinBox.minCoordenates.z);		// 6

		glVertex3f(this->mMinBox.maxCoordenates.x, this->mMinBox.maxCoordenates.y, this->mMinBox.minCoordenates.z);		// 6
		glVertex3f(this->mMinBox.maxCoordenates.x, this->mMinBox.maxCoordenates.y, this->mMinBox.maxCoordenates.z);		// 7

		glVertex3f(this->mMinBox.maxCoordenates.x, this->mMinBox.maxCoordenates.y, this->mMinBox.maxCoordenates.z);		// 7
		glVertex3f(this->mMinBox.minCoordenates.x, this->mMinBox.maxCoordenates.y, this->mMinBox.maxCoordenates.z);		// 4

		glVertex3f(this->mMinBox.minCoordenates.x, this->mMinBox.minCoordenates.y, this->mMinBox.minCoordenates.z);		// 0
		glVertex3f(this->mMinBox.minCoordenates.x, this->mMinBox.maxCoordenates.y, this->mMinBox.minCoordenates.z);		// 5

		glVertex3f(this->mMinBox.maxCoordenates.x, this->mMinBox.minCoordenates.y, this->mMinBox.minCoordenates.z);		// 1
		glVertex3f(this->mMinBox.maxCoordenates.x, this->mMinBox.maxCoordenates.y, this->mMinBox.minCoordenates.z);		// 6

		glVertex3f(this->mMinBox.maxCoordenates.x, this->mMinBox.minCoordenates.y, this->mMinBox.maxCoordenates.z);		// 2
		glVertex3f(this->mMinBox.maxCoordenates.x, this->mMinBox.maxCoordenates.y, this->mMinBox.maxCoordenates.z);		// 7

		glVertex3f(this->mMinBox.minCoordenates.x, this->mMinBox.minCoordenates.y, this->mMinBox.maxCoordenates.z);		// 3
		glVertex3f(this->mMinBox.minCoordenates.x, this->mMinBox.maxCoordenates.y, this->mMinBox.maxCoordenates.z);		// 4
	glEnd();
}
