/*==========================================================
	Copyright (c) Peter Vasil, 2008
 ==========================================================*/
#include <Carbon/Carbon.h>
#include "PVBall.h"

int PVBall::m_ballCount = 1;

PVBall::PVBall() : PVNode()
{
}

PVBall::PVBall(Ogre::SceneNode *node, Ogre::Entity *entity)
: PVNode(node, entity)
{
	m_ballId = ++m_ballCount;
}

PVBall::~PVBall()
{
}

void PVBall::setBallId(int id)
{
	m_ballId = id;
}

bool PVBall::intersect()
{
	return false;
}