#pragma once

#include "./OGLDefines.h"

class OGLKeyboardInput
{
	private:
		CharKeysMap charKeys;
		IntKeysMap	intKeys;

	public:
		OGLKeyboardInput				();
		~OGLKeyboardInput				();

		void			update			(unsigned int);
		void 			update			(unsigned char);

		void 			addKey			(std::string, unsigned char);
		void			addKey			(std::string, unsigned int);

		bool 			isKeyPressed	(std::string);
};
