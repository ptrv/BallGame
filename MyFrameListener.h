/*==========================================================
 Copyright (c) Peter Vasil, 2008
 ==========================================================*/

#ifndef _MYFRAMELISTENER_H_
#define _MYFRAMELISTENER_H_

//#include "ExampleFrameListener.h"

class MyFrameListener : public ExampleFrameListener
	{
	public:
		MyFrameListener(RenderWindow* win, Camera* cam, SceneManager *sceneMgr);
		
		bool processUnbufferedKeyInput(const FrameEvent& evt);
		
		bool processUnbufferedMouseInput(const FrameEvent& evt);
		
		bool frameStarted(const FrameEvent &evt);
		
		void moveSphere(void);
		
	protected:
		//class ExampleFrameListener(RenderWindow* win, Camera* cam, SceneManager *sceneMgr);
		bool mMouseDownBool;       // Whether or not the left mouse button was down last frame
		Real mToggle;          // The time left until next toggle
		Real mRotate;          // The rotate constant
		Real mMove;            // The movement constant
		SceneManager *mSceneMgr;   // The current SceneManager
		SceneNode *mCamNode;   // The SceneNode the camera is currently attached to
		//MyTimer* myTimer;
		int speed;
		float dtime;
		bool first;
		Vector3 v;
		
	private:
	

	};

#endif //_MYFRAMELISTENER_H_
