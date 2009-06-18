/*==========================================================
 Copyright (c) Peter Vasil, 2008
 ==========================================================*/

#include <Carbon/Carbon.h>
#include "PVPhysics.h"
#include "PVTimer.h"

const Vector3 PVPhysics::GRAVITY = Vector3(0, -9.81, 0);
const float PVPhysics::DAMPING = 0.85;

PVPhysics::PVPhysics() :
m_dtime(0.0f)
{
}

PVPhysics::~PVPhysics()
{
}

void PVPhysics::simulate(std::vector<PVBall*>& balls, double timeMs)
{
	m_dtime = timeMs;
	
	for(unsigned int i = 0; i < balls.size(); ++i)
	{
		move(balls.at(i), m_dtime);
		std::cout << "test" << std::endl;
	}
}

void PVPhysics::move(PVBall* ball, double timeMs)
{
	Vector3 position = ball->getPosition();
	Vector3 velocity = ball->getVelocity();
	Vector3 acceleration = ball->getAcceleration();
	
	velocity += (acceleration * timeMs);
	
	position += ((velocity * timeMs) + (acceleration * (timeMs * timeMs) / 2));
	
	ball->setVelocity(velocity);
	ball->setPosition(position);
}