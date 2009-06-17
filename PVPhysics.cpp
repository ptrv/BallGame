/*==========================================================
 Copyright (c) Peter Vasil, 2008
 ==========================================================*/

#include <Carbon/Carbon.h>
#include "PVPhysics.h"
#include "PVTimer.h"

PVPhysics::PVPhysics() :
m_dtime(0.0f)
{
	m_g = Vector3(0, -9.81, 0);
}

PVPhysics::~PVPhysics()
{
}

void PVPhysics::move(std::vector<PVBall*>& balls)
{
//	//int v = 1;
//	
//	//speed += 2 * dtime;
//	//	m_node = mSceneMgr->getSceneNode("SphereNode");
//	//Vector3 position = sphereNode->getPosition();
//	m_pos = m_node->getPosition();
//	//Vector3 v = Vector3(0,0,0);
//	Vector3 a;
//	float t = m_dtime;
//	if (PVTimer::getInstance().messureTime())
//	{
//		
//		if (t < 0.09) a = m_a;
//		else a = m_g;
//		//first = false;
//		
//		m_v += a * t;
//		m_pos += m_v*t+((a*t*t)/2);
//		
//		m_dtime += 0.03;
//	}
//	
//	m_node->setPosition(m_pos);// * 0.99);
	
}