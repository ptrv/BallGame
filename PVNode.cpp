/*==========================================================
	Copyright (c) Peter Vasil, 2008
 ==========================================================*/
#include <Carbon/Carbon.h>
#include "PVNode.h"

PVNode::PVNode()
{
}

PVNode::PVNode(SceneNode *node, Entity *entity)
:
m_velocity(Vector3(0,0,0)),
m_acceleration(Vector3(0,0,0))
{
}

PVNode::~PVNode()
{
}

void PVNode::setPosition(Ogre::Vector3 p)
{
	m_node->setPosition(p);
}

void PVNode::setAcceleration(Ogre::Vector3 a)
{
	m_acceleration = a;
}

void PVNode::setVelocity(Ogre::Vector3 v)
{
	m_velocity = v;
}

void PVNode::setMax(Ogre::Vector3 max)
{
	m_max = max;
}

void PVNode::setMin(Ogre::Vector3 min)
{
	m_min = min;
}

//bool PVNode::intersect()
//{
//	return false;
//}