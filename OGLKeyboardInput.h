#pragma once

#include <map>
#include <string>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

typedef std::map<std::string, std::map<unsigned char, bool> > CharKeysMap;
typedef std::map<std::string, std::map<unsigned int, bool> > IntKeysMap;

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

		void 			addKey			(const std::string &, unsigned char);
		void			addKey			(const std::string &, unsigned int);

		bool 			isKeyPressed	(const std::string &);
};
