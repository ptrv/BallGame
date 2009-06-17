/*==========================================================
	Copyright (c) Peter Vasil, 2008
 ==========================================================*/
#include <Carbon/Carbon.h>
//#include "ExampleApplication.h"
#include "MyApplication.h"
#include "MyFrameListener.h"

MyApplication::MyApplication()
{
	
}

MyApplication::~MyApplication() 
{
}

void MyApplication::createCamera(void)
{
	mCamera = mSceneMgr->createCamera("PlayerCam");
	//steht etwas oben und zu mir
	mCamera->setPosition(Vector3(0,0,1000));
	//guckt zum nullpunkt
	//mit lookAt() umgehen von rotieren der camera
	mCamera->lookAt(Vector3(0,0,0));
	//???
	mCamera->setNearClipDistance(5);
}

void MyApplication::createViewports(void)
{
	Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(ColourValue(0,0,0));
	//Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));  
}

void MyApplication::createScene(void)
{
	mSceneMgr->setAmbientLight( ColourValue( 1, 1, 1 ) );
	
	sphereEntity = mSceneMgr->createEntity( "SphereEntity", "sphere.mesh" );
	
	sphereNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( "SphereNode" );
	sphereNode->attachObject(sphereEntity);
	sphereNode->translate(0, 0, 0);
	sphereNode->scale(0.5f, 0.5f, 0.5f);
	
}

void MyApplication::createFrameListener(void)
{
	// Create the FrameListener
	mFrameListener = new MyFrameListener(mWindow, mCamera, mSceneMgr);
	mRoot->addFrameListener(mFrameListener);
	
	// infos links unten
	mFrameListener->showDebugOverlay(true);
}
