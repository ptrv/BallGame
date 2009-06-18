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
		const static Vector3 GRAVITY;
		const static float DAMPING;
		
	public:
		PVPhysics();
		~PVPhysics();
		
		void setDtime(float t) { m_dtime = t; };
		
		void simulate(std::vector<PVBall*>& balls, double timeMs);
		void move(PVBall* ball, double timeMs);
		
	private:
		float m_dtime;
		//Vector3 m_g;
	};