/*==========================================================
 Copyright (c) Peter Vasil, 2008
 ==========================================================*/

#include <Carbon/Carbon.h>
#include "PVPhysics.h"
//#include "PVTimer.h"

const Vector3 PVPhysics::GRAVITY = Vector3(0, -9.81, 0);
const float PVPhysics::DAMPING = 0.99;

PVPhysics::PVPhysics()
{
	//PVTimer::getInstance();
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
	
	this->collisionDetection(objectMap, balls, numberOfFlyingBalls);
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
	std::map<std::string, PVNode*>::iterator itCannon = objectMap.find("kanone");
	
	for (unsigned int i = 0; i <= numberOfFlyingBalls; ++i) {
		collisionWithArena(balls.at(i), itArena->second);
	}
}

void PVPhysics::collisionWithArena(PVNode *arena, PVNode *ball)
{
	float arenaRadius = (arena->getSceneNode()->_getWorldAABB().getSize()).x / 2;
	float arenaHeight = (arena->getSceneNode()->_getWorldAABB().getSize()).y;
	float ballRadius = (ball->getSceneNode()->_getWorldAABB().getSize()).x / 2;
	float toleranz = ballRadius + ballRadius;
	Vector3 ballPosition = ball->getPosition();
	
	if (ballPosition.length() >= (arenaRadius - toleranz)) 
	{
		return;
	}
	
	if (ballPosition.y >= arenaHeight) 
	{
		return;
	}
	
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
}

void PVPhysics::collisionWithCannon(PVNode *kanone, PVNode *ball)
{
}

void PVPhysics::collisionWithBall(PVNode *ball1, PVNode *ball2)
{
}

void PVPhysics::handleCollision(PVNode *fixedNode, PVNode *ball)
{
	Vector3 normale = fixedNode->getNormal();
	Vector3 ballVelocity = ball->getVelocity();
	
	ballVelocity = ballVelocity.reflect(normale);
	
	Vector3 normalizedVelocity = ballVelocity.normalisedCopy();
	float length = ball->getSceneNode()->_getWorldAABB().getSize().length();
	ball->setPosition(ball->getPosition() + normalizedVelocity * length);

	ball->setVelocity(ballVelocity * DAMPING);
}

void PVPhysics::handleCollisionWithGround(PVNode * fixedNode, PVNode *ball)
{
	Vector3 normale = Vector3(0.0, 1.0, 0.0);
	Vector3 ballVelocity = ball->getVelocity();
	
	ballVelocity = ballVelocity.reflect(normale);
	
	Vector3 normalizedVelocity = ballVelocity.normalisedCopy();
	float length = ball->getSceneNode()->_getWorldAABB().getSize().length();
	ball->setPosition(ball->getPosition() + normalizedVelocity * length);
	
	ball->setVelocity(ballVelocity * DAMPING);
}

void PVPhysics::handleCollisionWithBall(PVNode *ball1, PVNode *ball2)
{
}

Vector3 PVPhysics::invert(Vector3 vec)
{
	Vector3 result;
	result.x = -vec.x;
	result.y = -vec.y;
	result.z = -vec.z;
	
	return result;
}
