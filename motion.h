#ifndef _MOTION_H_
	#define _MOTION_H_

	#include <map>
	#include <string>

	class cMotion
	{
		private:
			cMotion();
			static cMotion *hInstance;
			std::map<std::string, std::map<unsigned char, bool> > keys;
			int mouseX, mouseY;

		public:
			~cMotion							();
			static cMotion		*getInstance	();
			void 				update			(unsigned char key, int x, int y);
			void 				addKey			(std::string name, unsigned char key);
			bool 				isKeyPressed	(std::string name);
	};
#endif