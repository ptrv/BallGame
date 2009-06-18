/*==========================================================
 Copyright (c) Peter Vasil, 2008
 ==========================================================*/
#ifndef _BALLAPP_H_
#define _BALLAPP_H_

#include <Carbon/Carbon.h>
#include "ExampleApplication.h"
#include "PVBall.h"
#include <vector>

#include "ExampleFrameListener.h"
#include "PVPhysics.h"
//#include "PVApplication.h"

class PVApplication;
class PVFrameListener : public ExampleFrameListener, public OIS::KeyListener
{
public:
	PVFrameListener();
	PVFrameListener( RenderWindow* win, Camera* cam, SceneManager *sceneMgr, PVApplication *pvApp );
	// //Overriding the default processUnbufferedKeyInput so the key updates we define
	// //later on work as intended.
	//bool processUnbufferedKeyInput(const FrameEvent& evt);
	
	// //Overriding the default processUnbufferedMouseInput so the Mouse updates we define
	// //later on work as intended. 
	//bool processUnbufferedMouseInput(const FrameEvent& evt);
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
	
	//int speed;
	//float dtime;
	//bool first;
	//Vector3 v;
	
	//bool move;
	PVPhysics *physicsNode;
	PVApplication *m_pvApp;
	
	Radian kanoneMoveDelta ;
	bool escPressed;
};

class PVApplication : public ExampleApplication
	{
	public:
		PVApplication();
		
		~PVApplication();
		
		void createBall();
		std::vector<PVBall*>& getBalls();
	protected:
		void createCamera(void);
		
		void createViewports(void);
		
		void createScene(void);
		
		void createFrameListener(void);
		
	private:
		//Entity* sphereEntity;
		//Entity *arenaEntity;
		//Entity *torwandEntity;
		//Entity *kanoneEntity;
		//SceneNode* sphereNode;
		//SceneNode *arenaNode;
		//SceneNode *torwandNode;
		//SceneNode *kanoneNode;
		//Light *light;
		std::vector<PVBall*> m_balls;
		
	};

#endif // _PVAPPLICATION_H_#endif //_BALLAPP_H_
