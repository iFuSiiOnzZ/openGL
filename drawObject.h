#ifndef _DRAWOBJECT_H_
	#define _DRAWOBJECT_H_
	#include "loadObject.h"

	class cDrawObject
	{
		public:
			cDrawObject();
			~cDrawObject();

			virtual void drawObject(strObject object) = 0;
			void drawAxis(int sz);
			int	 primtiveType(int nFaces);
	};

	class cDrawLines : public cDrawObject
	{
		public:
			cDrawLines();
			~cDrawLines();

			void drawObject(strObject object);
	};

	class cDrawPoints : public cDrawObject
	{
		public:
			cDrawPoints();
			~cDrawPoints();

			void drawObject(strObject object);
	};

	class cDrawPolygons : public cDrawObject
	{
		public:
			cDrawPolygons();
			~cDrawPolygons();

			void drawObject(strObject object);
	};
#endif