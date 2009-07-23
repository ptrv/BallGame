/*==========================================================
 Copyright (c) Peter Vasil, 2008
 ==========================================================*/

#ifndef _PVNODE_H_
#define _PVNODE_H_

#include "Ogre.h"

using namespace Ogre;

/// enum for direction
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
		/**
		 * \brief Constructor.
		 * \param &name a string.
		 * \param *node an Ogre::SceneNode. 
		 * \param *entity an Ogre::Entity.
		 */
		PVNode(const String& name, SceneNode *node, Entity *entity);
		/// Destructor.
		~PVNode();
		
		/**
		 * \breif getter for SceneNode.
		 * \return m_node a SceneNode pointer.
		 */
		SceneNode *getSceneNode() { return m_node; }
		/**
		 * \breif getter for Entity.
		 * \return m_entity an Entity pointer.
		 */
		Entity *getEntity() { return m_entity; }
		/**
		 * \breif getter for PVnode name.
		 * \return name a string.
		 */
		const String &getName() { return m_name; }
		/**
		 * \breif getter for PVnode velocity.
		 * \return m_velocity a Vector3.
		 */
		Vector3 getVelocity() { return m_velocity; }
		/**
		 * \breif getter for PVnode acceleration.
		 * \return m_acceleration a Vector3.
		 */
		Vector3 getAcceleration() { return m_acceleration; }
		/**
		 * \breif getter for PVnode position.
		 * \return m_position a Vector3.
		 */
		Vector3 getPosition() { return m_node->getPosition(); }
		/**
		 * \breif getter for PVnode orietation.
		 * \return m_orientation a Vector3.
		 */
		Vector3 getOrientation();
		/**
		 * \breif getter for PVnode normal.
		 * \return m_normal a Vector3.
		 */
		Vector3 getNormal();
		
		/**
		 * \brief setter for PVNode velocity.
		 * \param &v a Vector3.
		 */
		void setVelocity(const Vector3 &v);
		/**
		 * \brief setter for PVNode acceleration.
		 * \param &a a Vector3.
		 */
		void setAcceleration(const Vector3 &a);
		/**
		 * \brief setter for PVNode position.
		 * \param &p a Vector3.
		 */
		void setPosition(const Vector3 &p);
		/**
		 * \brief setter for PVNode orientation.
		 * \param &o a Vector3.
		 */
		void setOrientation(const Vector3 &o);
		/**
		 * \brief translate a PVnode.
		 * \param trans a Vector3.
		 */
		void translateNode(Vector3 trans);
		/**
		 * \brief rotates a PVnode in a direction.
		 * \param dir a PVNode::Direction.
		 */
		void rotateNode(Direction dir);
		/**
		 * \brief checks if PVNode has acceleration.
		 * \return true if PVNode has an acceleration != 0.
		 */
		bool hasAcceleration();
		
		void setKanoneMaxLeft();
		
	private:
		/// the SceneNode.
		SceneNode *m_node;
		/// the Entity.
		Entity *m_entity;
		/// the name of the node.
		const String &m_name;
		/// angle steps for rotating kanone by user.
		static float m_angle;
		/// minimum height og kanone.
		static float m_minH;
		/// maximum height of kanone.
		static float m_maxH;
		/// minimum width of kanone.
		static float m_minV;
		/// maximum width of kanone.
		static float m_maxV;
		/// pitch of kanone.
		float m_pitch;
		/// yaw of kanone.
		float m_yaw;
		/// velocity of node.
		Vector3 m_velocity;
		/// acceleration of node.
		Vector3 m_acceleration;
		/// position of node.
		Vector3 m_position;
		/// orientation od node.
		Vector3	m_orientation;

	};

#endif // _PVNODE_H_