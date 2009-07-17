/*==========================================================
 Copyright (c) Peter Vasil, 2008
 ==========================================================*/
#ifndef _BALLAPP_H_
#define _BALLAPP_H_

#include <Carbon/Carbon.h>
#include "ExampleApplication.h"
#include "PVNode.h"
#include <vector>
#include <map>

#include "ExampleFrameListener.h"
#include "PVPhysics.h"
//#include "PVApplication.h"

class PVApplication;
class PVFrameListener : public ExampleFrameListener, public OIS::KeyListener
{
public:
	PVFrameListener();
	PVFrameListener( RenderWindow* win, Camera* cam, SceneManager *sceneMgr, std::map<std::string, PVNode*>& objectMap, std::vector<PVNode*>& balls, PVApplication *app );

	bool frameStarted(const FrameEvent &evt);
	bool keyPressed( const OIS::KeyEvent &arg );
	bool keyReleased( const OIS::KeyEvent &arg );  
	
protected:
	bool mMouseDownBool;       // Whether or not the left mouse button was down last frame
	Real mToggle;          // The time left until next toggle
	Real mRotate;          // The rotate constant
	Real mMove;            // The movement constant
	SceneManager *mSceneMgr;   // The current SceneManager
	SceneNode *mCamNode;   // The SceneNode the camera is currently attached to
	
	
	
	bool mContinue;
private:
	PVPhysics *m_physicsNode;
	//PVTimer *m_timer;
	std::map<std::string, PVNode*>& m_objectMap;
	std::map<std::string, PVNode*>::iterator it;
	
	PVNode *kanone;
	
	std::vector<PVNode*>& m_balls;
	int m_index;
	
	float m_shootingSpeedFactor;
	
	void shootBall();
	
		
	PVApplication *m_app;
};

class PVApplication : public ExampleApplication
	{
	public:
		PVApplication();
		
		~PVApplication();
		
		//void createBall();
		//std::vector<PVBall*>& getBalls();
		int m_numberOfBalls;
		void clearAllBalls();
		void createBalls();
	protected:
		void createCamera(void);
		
		void createViewports(void);
		
		void createScene(void);
		
		void createFrameListener(void);
		
		std::map<std::string, PVNode*> m_objectMap;
		std::vector<PVNode*> m_balls;
		
		
		
	};

#endif // _PVAPPLICATION_H_#endif //_BALLAPP_H_
