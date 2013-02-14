#pragma once

#include "./OGLVector3f.h"

class OGLCamera
{
	private:
		OGLVector3f mDirection;
		OGLVector3f mPosition;
		OGLVector3f mStride;
		OGLVector3f mLookAt;
		OGLVector3f mUp;

		float mYaw;
		float mPitch;

		int mScreenHeight;
		int mScreenWidth;
		
	public:
		OGLCamera					(int, int);
		~OGLCamera					();

		void		setYaw			(float);
		void		setPitch		(float);

		void		addYaw			(float);
		void		addPitch		(float);

		float		getYaw			(void);
		float		getPitch		(void);

		void		setDirection	(const OGLVector3f &);
		void		setPosition		(const OGLVector3f &);
		void		setStride		(const OGLVector3f &);
		void		setLookAt		(const OGLVector3f &);
		void		setUp			(const OGLVector3f &);

		void		addDirection	(const OGLVector3f &);
		void		addPosition		(const OGLVector3f &);
		void		addStride		(const OGLVector3f &);
		void		addLookAt		(const OGLVector3f &);
		void		addUp			(const OGLVector3f &);

		OGLVector3f	getDirection	(void);
		OGLVector3f	getPosition		(void);
		OGLVector3f	getStride		(void);
		OGLVector3f	getLookAt		(void);
		OGLVector3f	getUp			(void);

		void		setScrHeight	(int);
		void		setScrWidth		(int);

		int			getScrHeight	(void);
		int			getScrWidth		(void);

		virtual void render			(void);
		virtual void update			(float);
};
