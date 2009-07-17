/*==========================================================
 Copyright (c) Peter Vasil, 2008
 ==========================================================*/

#ifndef _PVNODE_H_
#define _PVNODE_H_

#include "Ogre.h"

using namespace Ogre;

enum Direction 
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class PVNode
	{
	public:
		PVNode(const String& name, SceneNode *node, Entity *entity);
		~PVNode();
		
		SceneNode *getSceneNode() { return m_node; }
		Entity *getEntity() { return m_entity; }
		const String &getName() { return m_name; }
		
		Vector3 getVelocity() { return m_velocity; }
		Vector3 getAcceleration() { return m_acceleration; }
		Vector3 getPosition() { return m_node->getPosition(); }
		Vector3 getOrientation();
		Vector3 getNormal();
		
		void setVelocity(const Vector3 &v);
		void setAcceleration(const Vector3 &a);
		void setPosition(const Vector3 &p);
		void setOrientation(const Vector3 &o);
		
		void translateNode(Vector3 trans);
		void rotateNode(Direction dir);
		bool hasAcceleration();
		
	private:
		SceneNode *m_node;
		Entity *m_entity;
		const String &m_name;
		
		static float m_angle;
		static float m_minH;
		static float m_maxH;
		static float m_minV;
		static float m_maxV;
		
		float m_pitch;
		float m_yaw;
		
		Vector3 m_velocity;
		Vector3 m_acceleration;
		Vector3 m_position;
		Vector3	m_orientation;

	};

#endif // _PVNODE_H_