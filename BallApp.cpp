/*==========================================================
	Copyright (c) Peter Vasil, 2008
 ==========================================================*/


#include "BallApp.h"

PVApplication::PVApplication()
{
}

PVApplication::~PVApplication()
{
}

void PVApplication::createCamera(void)
{
	mCamera = mSceneMgr->createCamera("PlayerCam");
	//steht etwas oben und zu mir
	mCamera->setPosition(Vector3(0,50,100));
	//guckt zum nullpunkt
	//mit lookAt() umgehen von rotieren der camera
	mCamera->lookAt(Vector3(0,0,0));
	//???
	mCamera->setNearClipDistance(5);		
	
}

void PVApplication::createViewports(void)
{
	Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(ColourValue(0,0,0));
	//Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));  
}


void PVApplication::createScene(void)
{
	Light *light;
	
	light = mSceneMgr->createLight("Light");
	light->setType( Light::LT_DIRECTIONAL);
	light->setDiffuseColour(0.01, 0.01, 0.35);
	light->setSpecularColour(0.01, 0.01, 0.35);
	light->setDirection(0, 0, -50);
	light->setPosition(Vector3(0,0,100));
	
	float intensity = 0.5;
	light = mSceneMgr->createLight("Light2");
	light->setType( Light::LT_POINT);
	light->setPosition(Vector3(0,100,0));
	light->setDiffuseColour(intensity, intensity, intensity);
	light->setSpecularColour(intensity, intensity, intensity);
	
	
	
	
	sphereEntity = mSceneMgr->createEntity( "SphereEntity", "sphere.mesh" );
	sphereNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( "SphereNode" );
	sphereNode->attachObject(sphereEntity);
	sphereNode->translate(-40, 0, 0);
	sphereNode->scale(0.03, 0.03,0.03);
	
	arenaEntity = mSceneMgr->createEntity("AreneEntity", "arena.mesh");
	arenaNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( "ArenaNode" );
	arenaNode->attachObject(arenaEntity);
	
	torwandEntity = mSceneMgr->createEntity("TorwandEntity", "torwand.mesh");
	torwandNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("TorwandNode");
	torwandNode->attachObject(torwandEntity);
	
	kanoneEntity = mSceneMgr->createEntity("KanoneEntity", "kanone.mesh");
	kanoneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("KanoneNode");
	kanoneNode->attachObject(kanoneEntity);
	
	
}

void PVApplication::createFrameListener(void)
{
	// Create the FrameListener
	mFrameListener = new PVFrameListener(mWindow, mCamera, mSceneMgr);//, this);
	mRoot->addFrameListener(mFrameListener);
	
	// infos links unten
	mFrameListener->showDebugOverlay(true);
}

void PVApplication::createBalls()
{
	
}

