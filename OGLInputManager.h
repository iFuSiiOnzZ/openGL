#pragma once

#include "./OGLKeyboardInput.h"
#include "./OGLMouseInput.h"

class OGLInputManager
{
	private:
		OGLInputManager			(int, int);

		static OGLInputManager	*hInstance;
		OGLMouseInput 			*mMouseInput;
		OGLKeyboardInput		*mKeyboardInput;

	public:
		~OGLInputManager						(void);
		static OGLInputManager	*getInstance	(int, int);

		void	addKey				(std::string, unsigned char);
		//void	addKey				(std::string, unsigned int);

		void	updateKey			(unsigned char);
		void	updateKey			(unsigned int);

		bool	isKeyPressed		(std::string);

		void	updateMouse			(int, int, float);
		void	updateMouse			(int, int, int, int, float);

		float	getAngle			(void);
		float	getPitch			(void);
		float	getYaw				(void);

		bool	isLeftButtonPress	(void);
		bool	isRightButtonPress	(void);

		int 	getMouseX			(void);
		int 	getMouseY			(void);

		int 	getLastMouseX		(void);
		int 	getLastMouseY		(void);
};
