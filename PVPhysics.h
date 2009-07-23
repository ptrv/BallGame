/*==========================================================
 Copyright (c) Peter Vasil, 2008
 ==========================================================*/

#ifndef _PVPHYSICS_H_
#define _PVPHYSICS_H_

#include "Ogre.h"
#include "PVNode.h"

using namespace Ogre;
class PVPhysics
	{
		/// Constant for gravity g = -9.81
		const static Vector3 GRAVITY;
		/// Damping factor
		const static float DAMPING;
		
	public:
		/// Constructor
		PVPhysics();
		/// Destructor
		~PVPhysics();
		
		/**
		 * \brief simulate function which calls move function and collision detection.
		 * \param objectMap map with objects.
		 * \param numberOfFlyingBalls current sooted balls.
		 * \param time delta time elapsed since last frame in seconds.
		 */
		void simulate(std::map<std::string, PVNode*>& objectMap, 
					  std::vector<PVNode*>& balls, 
					  int numberOfFlyingBalls, 
					  float time);
		/**
		 * \brief function for shooting a ball.
		 * \param ball a PVnode.
		 * \param time a float for the time since last frame.
		 */
		void move(PVNode* ball, float time);
		/**
		 * \brief function for calling the particular collision detection function for each node type.
		 * \param objectMap map with all scene nodes.
		 * \param balls vector with all balls.
		 */
		void collisionDetection(std::map<std::string, PVNode*>& objectMap, 
								std::vector<PVNode*>& balls, 
								int numberOfFlyingBalls);
		/**
		 * \brief detects collision between arena and a ball.
		 * \param *arena scene node.
		 * \param *ball
		 */
		void collisionWithArena(PVNode *arena, PVNode *ball);
		/**
		 * \brief detects collision between wall and a ball.
		 * \param *wall scene node.
		 * \param *ball
		 */
		void collisionWithWall(PVNode *wall, PVNode *ball);
		/**
		 * \brief detects collision between arena and a ball.
		 * \param *kanone scene node
		 * \param *ball
		 */
		void collisionWithCannon(PVNode *kanone, PVNode *ball);
		/**
		 * \brief detects collisionbetween balls.
		 * \param *ball1 scene node.
		 * \param *ball2
		 */
		void collisionWithBall(PVNode *ball1, PVNode *ball2);
		/**
		 * \brief detects collisionbetween pillar and a ball.
		 * \param *pillar scene node.
		 * \param *ball
		 */
		void collisionWithPillar(PVNode *pillar, PVNode *ball);
		
		/**
		 * \brief handles collision between a ball and a scene node.
		 * \param node a scene node.
		 * \param ball a ball.
		 */
		void handleCollision(PVNode *node, PVNode *ball);
		/**
		 * \brief handles collision between ground and a ball.
		 * \param ground a scene node.
		 * \param ball a ball.
		 */
		void handleCollisionWithGround(PVNode * ground, PVNode *ball);
		/**
		 * \brief handles collision between balls.
		 * \param ball1 first ball.
		 * \param ball2 second ball.
		 */
		void handleCollisionWithBall(PVNode *ball1, PVNode *ball2);
				
	private:
		
	};

#endif // _PVPHYSICS_H_