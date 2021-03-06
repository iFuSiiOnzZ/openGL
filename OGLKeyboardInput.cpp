#include "./OGLKeyboardInput.h"

OGLKeyboardInput::OGLKeyboardInput(void)
{
}

OGLKeyboardInput::~OGLKeyboardInput()
{
	this->charKeys.clear();
	this->intKeys.clear();
}

void OGLKeyboardInput::addKey(const std::string &name, unsigned int key)
{
	this->intKeys[name][key] = false;
}

void OGLKeyboardInput::addKey(const std::string &name, unsigned char key)
{
	this->charKeys[name][key] = false;
}

void OGLKeyboardInput::update(unsigned int key)
{
	for(IntKeysMap::iterator it = this->intKeys.begin(); it != this->intKeys.end(); it++)
	{
		if(key == it->second.begin()->first) it->second.begin()->second = !it->second.begin()->second;
	}
}

void OGLKeyboardInput::update(unsigned char key)
{
	for(CharKeysMap::iterator it = this->charKeys.begin(); it != this->charKeys.end(); it++)
	{
		if(key == it->second.begin()->first) it->second.begin()->second = !it->second.begin()->second;
	}
}

bool OGLKeyboardInput::isKeyPressed(const std::string &name)
{
	bool down = false;

	for(CharKeysMap::iterator it = this->charKeys.begin(); it != this->charKeys.end(); it++)
	{
		if(it->first == name)
		{
			down = it->second.begin()->second; break;
		}
	}

	for(IntKeysMap::iterator it = this->intKeys.begin(); it != this->intKeys.end(); it++)
	{
		if(it->first == name)
		{
			down = it->second.begin()->second; break;
		}
	}

	return(down);
}
