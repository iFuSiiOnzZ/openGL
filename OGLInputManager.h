#pragma once

#include "./OGLKeyboardInput.h"
#include "./OGLMouseInput.h"

class OGLInputManager
{
	private:
		OGLInputManager			(int, int);
		OGLInputManager			(void);

		static OGLInputManager	*hInstance;
		OGLMouseInput 			*mMouseInput;
		OGLKeyboardInput		*mKeyboardInput;

	public:
		~OGLInputManager						(void);
		static OGLInputManager	*getInstance	(int, int);
		static OGLInputManager	*getInstance	(void);

		void	addKey				(const std::string &, unsigned char);
		void	addKeyS				(const std::string &, unsigned int);

		void	updateKey			(unsigned char);
		void	updateKeyS			(unsigned int);

		bool	isKeyPressed		(const std::string &);

		void	updateMouse			(int, int, float);
		void	updateMouse			(int, int, int, int, float);

		float	getAngle			(void);
		float	getPitch			(void);
		float	getYaw				(void);

		bool	isLeftButtonPress	(void);
		bool	isRightButtonPress	(void);

		int 	getMouseX			(void);
		int 	getMouseY			(void);
};
