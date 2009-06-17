/*==========================================================
	Copyright (c) Peter Vasil, 2008
 ==========================================================*/
#include <Carbon/Carbon.h>
//#include "ExampleFrameListener.h"
#include "MyApplication.h"
#include "MyFrameListener.h"
#include "MyTimer.h"

MyFrameListener::MyFrameListener(RenderWindow* win, Camera* cam, SceneManager *sceneMgr)
: ExampleFrameListener(win, cam, false, false)
{
	// key and mouse state tracking
	mMouseDownBool = false;
	mToggle = 0.0;
	
	// Populate the camera and scene manager containers
	mCamNode = cam->getParentSceneNode();
	mSceneMgr = sceneMgr;
	
	// set the rotation and move speed
	mRotate = 0.13;
	mMove = 250;
	//myTimer = new MyTimer();
	speed = 1;
	dtime = 0.0;
	first = true;
	v = Vector3(0,0,0);
}


bool MyFrameListener::processUnbufferedKeyInput(const FrameEvent& evt)
{
	return true;
}

bool MyFrameListener::processUnbufferedMouseInput(const FrameEvent& evt)
{
	return true;
}


bool MyFrameListener::frameStarted(const FrameEvent &evt)
{
	//myTimer->messureTime();
	mMouse->capture();
	mKeyboard->capture();
	
	/****************    keyboard   *************************************/    	
	if(mKeyboard->isKeyDown(OIS::KC_ESCAPE)){
		return false;
	}
	
	if (mKeyboard->isKeyDown(OIS::KC_N))
	{
	}
	
		moveSphere();
		
	/******************   mouse      ************************************/
	bool currMouseBool = mMouse->getMouseState().buttonDown(OIS::MB_Left);	
	mMouseDownBool = currMouseBool;
	
	return true;
}

void MyFrameListener::moveSphere(void){
	//int v = 1;
	
	//speed += 2 * dtime;
	if (MyTimer::getInstance().messureTime())
	{

		SceneNode* sphereNode = mSceneMgr->getSceneNode("SphereNode");
		Vector3 position = sphereNode->getPosition();
		
		//Vector3 v = Vector3(0,0,0);
		Vector3 a;
		float t = dtime;
		
		if (t < 0.12) a = Vector3(100, 200, 0);
		else a = Vector3(0, -9.81, 0);
		first = false;
		
		v += a * t;
		position += v*t+((a*t*t)/2);
		
		sphereNode->setPosition(position);// * 0.99);
		
		dtime += 0.03;
	}
	
}