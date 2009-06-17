/*==========================================================
 Copyright (c) Peter Vasil, 2008
 ==========================================================*/

#ifndef _PVNODE_H_
#define _PVNODE_H_

#include "Ogre.h"

using namespace Ogre;
class PVNode
	{
	public:
		PVNode();
		PVNode(SceneNode *node, Entity *entity);
		virtual ~PVNode();
		
		SceneNode *getSceneNode() { return m_node; };
		Entity *getEntity() { return m_entity; };
		Vector3 getVelocity() { return m_velocity; }
		Vector3 getAcceleration() { return m_acceleration; }
		Vector3 getPosition() { return m_node->getPosition(); }
		Vector3 getMin() { return m_min; }
		Vector3 getMax() { return m_max; } 
		
		void setVelocity(Vector3 v);
		void setAcceleration(Vector3 a);
		void setPosition(Vector3 p);
		void setMax(Vector3 max);
		void setMin(Vector3 min);
		
		virtual bool intersect() = 0;
		
	private:
		SceneNode *m_node;
		Entity *m_entity;
		Vector3 m_min;
		Vector3 m_max;
		Vector3 m_velocity;
		Vector3 m_acceleration;
	};

#endif // _PVNODE_H_