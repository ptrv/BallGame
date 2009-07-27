/*==========================================================
 Copyright (c) Peter Vasil, 2008
 ==========================================================*/

#include <Carbon/Carbon.h>
#include "PVPhysics.h"

const Vector3 PVPhysics::GRAVITY = Vector3(0, -9.81, 0);
const float PVPhysics::DAMPING = 0.85;

PVPhysics::PVPhysics()
{
}

PVPhysics::~PVPhysics()
{
}

void PVPhysics::simulate(std::map<std::string, PVNode*>& objectMap, std::vector<PVNode*>& balls, int numberOfFlyingBalls, float time)
{
	for(unsigned int i = 0; i < numberOfFlyingBalls; ++i)
	{
		move(balls.at(i), time);
		//std::cout << time << std::endl;
	}
	collisionDetection(objectMap, balls, numberOfFlyingBalls);
}

void PVPhysics::move(PVNode* ball, float time)
{
	double deltaT = time;
	if (deltaT < 0.0)
	{
		deltaT = 0.2;
	}
	ball->setVelocity( ball->getVelocity() += ball->getAcceleration() * deltaT);
	ball->setPosition( ball->getPosition() += (ball->getVelocity() * deltaT) + (ball->getAcceleration() * (deltaT * deltaT)/2));
	
	if (ball->getAcceleration() != GRAVITY) 
	{
		ball->setAcceleration(GRAVITY);
	}
					  
}

void PVPhysics::collisionDetection(std::map<std::string, PVNode*>& objectMap, std::vector<PVNode*>& balls, int numberOfFlyingBalls)
{
	std::map<std::string, PVNode*>::iterator itArena = objectMap.find("arena");
	std::map<std::string, PVNode*>::iterator itWall = objectMap.find("wall");
	std::map<std::string, PVNode*>::iterator itP1 = objectMap.find("p1");
	std::map<std::string, PVNode*>::iterator itP2 = objectMap.find("p2");
	std::map<std::string, PVNode*>::iterator itCannon = objectMap.find("kanone");

	
	for (unsigned int i = 0; i <= numberOfFlyingBalls; ++i) {
		collisionWithArena(itArena->second, balls.at(i));
		collisionWithWall(itWall->second, balls.at(i));
		collisionWithPillar(itP1->second, balls.at(i));
		collisionWithPillar(itP2->second, balls.at(i));
		for( int j = (i+1); j <= numberOfFlyingBalls; j++ )
		{
			collisionWithBall( balls.at(i), balls.at(j) );
		}
		
	}
}

void PVPhysics::collisionWithArena(PVNode *arena, PVNode *ball)
{
	float arenaRadius = (arena->getSceneNode()->_getWorldAABB().getSize()).x / 2;
	float arenaHeight = arena->getSceneNode()->_getWorldAABB().getSize().y;
	float ballRadius = (ball->getSceneNode()->_getWorldAABB().getSize()).x / 2;
	float toleranz = ballRadius + ballRadius;
	Vector3 ballPosition = ball->getPosition();
	
	if (ballPosition.length() >= (arenaRadius + toleranz)) return;
	
	if (ballPosition.y >= arenaHeight) return;
	
	if (ballPosition.length() > (arenaRadius - toleranz)) 
	{
		handleCollision(arena, ball);
		return;
	}
	
	if ((ballPosition.y - ballRadius) < 0) 
	{
		handleCollisionWithGround(arena, ball);
		return;
	}
}

void PVPhysics::collisionWithWall(PVNode *wall, PVNode *ball)
{
	AxisAlignedBox box1 = wall->getSceneNode()->_getWorldAABB();
	AxisAlignedBox box2 = ball->getSceneNode()->_getWorldAABB();
	
	
	if(box1.intersects(box2))
	{
		Vector3 upperLeftHole = wall->getPosition() + Vector3(-10.0, 11.0, 0);
		Vector3 lowerRichtHole = wall->getPosition() + Vector3(10.0, 6.0, 0.0);

		if ( ((ball->getPosition() - upperLeftHole).length() > 3.2) &&
			((ball->getPosition() - lowerRichtHole).length() > 3.2))
		{
			handleCollision(wall, ball);
		}
	}
}


void PVPhysics::collisionWithBall(PVNode *ball1, PVNode *ball2)
{
	AxisAlignedBox box1 = ball1->getSceneNode()->_getWorldAABB();
	AxisAlignedBox box2 = ball2->getSceneNode()->_getWorldAABB();
	
	if(box1.intersects(box2))
	{
		handleCollisionWithBall(ball1, ball2);
	}

}

void PVPhysics::handleCollision(PVNode *node, PVNode *ball)
{
	Vector3 normale = ball->getNormal();
	Vector3 ballVelocity = ball->getVelocity();
	
	ballVelocity = ballVelocity.reflect(normale);
	
	Vector3 normalizedVelocity = ballVelocity.normalisedCopy();
	ball->setPosition(ball->getPosition() + normalizedVelocity);

	ball->setVelocity(ballVelocity * DAMPING);
}

void PVPhysics::handleCollisionWithGround(PVNode * ground, PVNode *ball)
{
	Vector3 normale = Vector3(0.0, 1.0, 0.0);
	Vector3 ballVelocity = ball->getVelocity();
	
	ballVelocity = ballVelocity.reflect(normale);
	
	Vector3 normalizedVelocity = ballVelocity.normalisedCopy();
	ball->setPosition(ball->getPosition() + normalizedVelocity);
	
	ball->setVelocity(ballVelocity * DAMPING);
}

void PVPhysics::handleCollisionWithBall(PVNode *ball1, PVNode *ball2)
{
	Vector3 velocityBall1 = ball1->getVelocity();
	Vector3 velocityBall2 = ball2->getVelocity();
	
	velocityBall1 = velocityBall1.reflect(velocityBall2.normalisedCopy());
	velocityBall2 = velocityBall2.reflect(ball1->getVelocity().normalisedCopy());
	
	Vector3 normalizedVelocity = velocityBall1.normalisedCopy();
	float length = ball1->getSceneNode()->_getWorldAABB().getSize().length();
	ball1->setPosition( ball1->getPosition() + normalizedVelocity*length );
	
	ball1->setVelocity( velocityBall1 * DAMPING );
	ball2->setVelocity( velocityBall2 * DAMPING );
	
}

void PVPhysics::collisionWithPillar(PVNode* pillar, PVNode* ball){
	
	collisionWithWall(pillar, ball);
}