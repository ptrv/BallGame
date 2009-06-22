/*==========================================================
 Copyright (c) Peter Vasil, 2008
 ==========================================================*/

#ifndef _PVPHYSICS_H_
#define _PVPHYSICS_H_

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
		
		void collisionDetection(std::map<std::string, PVNode*>& objectMap, std::vector<PVNode*>& balls, int numberOfFlyingBalls);
		
		void collisionWithArena(PVNode *arena, PVNode *ball);
		void collisionWithWall(PVNode *wall, PVNode *ball);
		void collisionWithCannon(PVNode *kanone, PVNode *ball);
		void collisionWithBall(PVNode *ball1, PVNode *ball2);
		
		void handleCollision(PVNode *fixedNode, PVNode *ball);
		void handleCollisionWithGround(PVNode * fixedNode, PVNode *ball);
		void handleCollisionWithBall(PVNode *ball1, PVNode *ball2);
		
		Vector3 invert(Vector3 vec);
		
	private:
		
	};

#endif // _PVPHYSICS_H_