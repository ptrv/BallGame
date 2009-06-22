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
		
		//void setDtime(float t) { m_dtime = t; };
		
		void simulate(std::map<std::string, PVNode*>& objectMap, std::vector<PVNode*>& balls, int numberOfFlyingBalls, float time);
		void move(PVNode* ball, float time);
		
	private:
		
	};