#ifndef _DRAWOBJECT_H_
	#define _DRAWOBJECT_H_
	#include "loadObject.h"

	void drawPoints(strObject *object, float sz);
	void drawPlans(strObject *object);
	void drawLines(strObject *object);

	void drawAxis(int sz);
#endif