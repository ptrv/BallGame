/*==========================================================
 Copyright (c) Peter Vasil, 2008
 ==========================================================*/

//#include <Carbon/Carbon.h>
//#include "ExampleApplication.h"
//#include <Carbon/Carbon.h>
#include "Ogre.h"
//#include <string>
#include "PVBall.h"

using namespace Ogre;
class PVPhysics
	{
	public:
		PVPhysics();
		~PVPhysics();
		
		void setDtime(float t) { m_dtime = t; };
		
		void move(std::vector<PVBall*>& balls);
		
	private:
		float m_dtime;
		Vector3 m_g;
	};