#include "motion.h"

cMotion *cMotion::hInstance = NULL;

cMotion *cMotion::getInstance()
{
	if(hInstance == NULL)
	{
		hInstance = new cMotion();
	}

	return(hInstance);
}

cMotion::cMotion(void)
{
	this->mouseX = 0;
	this->mouseY = 0;
}

cMotion::~cMotion()
{
	this->keys.clear();
}

void cMotion::addKey(std::string name, unsigned char key)
{
	this->keys[name][key] = false;
}

void cMotion::update(unsigned char key, int x, int y)
{
	std::map<std::string, std::map<unsigned char, bool> >::iterator it = this->keys.begin();

	for(it; it != this->keys.end(); it++)
	{
		it->second.begin()->second = (key == it->second.begin()->first)? true : false;
	}
}

bool cMotion::isKeyPressed(std::string name)
{
	bool down = false;
	std::map<std::string, std::map<unsigned char, bool> >::iterator it = this->keys.begin();

	for(it; it != this->keys.end(); it++)
	{
		if(it->first == name)
		{
			down = it->second.begin()->second; break;
		}
	}

	return(down);
}