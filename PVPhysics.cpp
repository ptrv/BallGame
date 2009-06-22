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
		std::cout << time << std::endl;
	}
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