/*==========================================================
	Copyright (c) Peter Vasil, 2008
 ==========================================================*/
#include <Carbon/Carbon.h>
#include "PVNode.h"

float PVNode::m_angle	=   5.0;
float PVNode::m_maxH	=  65.0;
float PVNode::m_minH 	= -65.0;
float PVNode::m_maxV	=  75.0;
float PVNode::m_minV	=   0.0;

PVNode::PVNode(const String &name, SceneNode *node, Entity *entity)
:
m_name(name),
m_node(node),
m_entity(entity),
m_position(Vector3(0,0,0)),
m_velocity(Vector3(0,0,0)),
m_acceleration(Vector3(0,0,0)),
m_yaw(0.0),
m_pitch(0.0)
{
	m_node->pitch(Degree(m_pitch));
}

PVNode::~PVNode()
{
}

void PVNode::setPosition(const Ogre::Vector3 &p)
{
	m_node->setPosition(p);
}

void PVNode::setAcceleration(const Ogre::Vector3 &a)
{
	m_acceleration = a;
}

void PVNode::setVelocity(const Ogre::Vector3 &v)
{
	m_velocity = v;
}


Vector3 PVNode::getOrientation()
{
	m_orientation = m_node->getOrientation() * Vector3(0.0, 0.0, -1.0);
	return m_orientation;
}

Vector3 PVNode::getNormal()
{
	Vector3 position = this->getPosition();
	Vector3 normal = Vector3(-position.x, position.y, -position.z);
	return normal.normalisedCopy();
}

void PVNode::translateNode(Vector3 trans)
{
	m_node->translate(trans);
}

void PVNode::rotateNode(Direction dir)
{
	m_node->setOrientation( Quaternion(1.0, 0.0, 0.0, 0.0) );
	switch (dir) {
		case UP:	if ( (m_pitch +=  m_angle) >= m_maxV ) m_pitch = m_maxV;	break;
		case DOWN:	if ( (m_pitch -=  m_angle) <= m_minV ) m_pitch = m_minV;	break;
		case RIGHT:	if ( (m_yaw	+=  m_angle) >= m_maxH ) m_yaw = m_maxH;	break;
		case LEFT:	if ( (m_yaw	-=  m_angle) <= m_minH ) m_yaw = m_minH;	break;
		default:
			break;
	}
	m_node->pitch( Degree( m_pitch ) );
	m_node->yaw( Degree( m_yaw ) );
}

bool PVNode::hasAcceleration()
{
	int value = this->m_acceleration[0] * this->m_acceleration[0] + this->m_acceleration[1] * this->m_acceleration[1] + this->m_acceleration[2] * this->m_acceleration[2];
	if ( value > 0) return true;
	return false;
}