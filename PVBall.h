/*==========================================================
 Copyright (c) Peter Vasil, 2008
 ==========================================================*/

#include "PVNode.h"

class PVBall : public PVNode
	{
		static int m_ballCount;
	public:
		PVBall();
		PVBall(SceneNode *node, Entity *entity);
		virtual ~PVBall();
		bool intersect();
		int getId() { return m_ballId; }
		void setBallId(int id);
		static int getBallCount() { return m_ballCount; }
	private:
		
		int m_ballId;
		
	};