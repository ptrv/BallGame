
#include "BallApp.h"
//#include "PVApplication.h"
//#include "PVFrameListener.h"
#include <sstream>

using namespace Ogre;


PVFrameListener::PVFrameListener( RenderWindow* win, Camera* cam, SceneManager *sceneMgr, std::map<std::string, PVNode*>& objectMap, std::vector<PVNode*>& balls)
: ExampleFrameListener(win, cam, true, false), m_objectMap(objectMap), m_balls(balls)
{
	// key and mouse state tracking
	mMouseDownBool = false;
	mToggle = 0.0;
	mKeyboard->setEventCallback(this);
	
	// Populate the camera and scene manager containers
	mCamNode = cam->getParentSceneNode();
	mSceneMgr = sceneMgr;
	
	// set the rotation and move speed
	mRotate = 0.13;
	mMove = 250;

	mContinue = true;
	
	//m_timer = PVTimer::getInstance();
	m_physicsNode = new PVPhysics();
	
	it = m_objectMap.find("kanone");
	if( it != m_objectMap.end() )
	{
		kanone = it->second;
	}
	
	m_index = 0;
}

bool PVFrameListener::frameStarted(const FrameEvent &evt)
{
	mMouse->capture();
	
	bool currMouseBool = mMouse->getMouseState().buttonDown(OIS::MB_Left);
	mMouseDownBool = currMouseBool;
	
	m_physicsNode->simulate(m_objectMap, m_balls, m_index, evt.timeSinceLastFrame);
	
	return mContinue;
}

bool PVFrameListener::keyPressed(const OIS::KeyEvent &arg)
{
	switch(arg.key)
	{
		case OIS::KC_ESCAPE:
			mContinue = false;
			break;
		case OIS::KC_SPACE:
			shootBall();
			break;
		case OIS::KC_A:
			kanone->rotateNode(LEFT);
			break;
		case OIS::KC_D:
			kanone->rotateNode(RIGHT);
			break;
		case OIS::KC_W:
			kanone->rotateNode(UP);
			break;
		case OIS::KC_S:
			kanone->rotateNode(DOWN);
			break;
	}
	return mContinue;
}

bool PVFrameListener::keyReleased(const OIS::KeyEvent &arg)
{
	bool handled = true;
	
	return handled;
}

void PVFrameListener::shootBall()
{
	m_balls[m_index]->setAcceleration( kanone->getOrientation() * Vector3(20.0, 20.0, 20.0) );
	m_balls[m_index]->setVelocity( kanone->getOrientation() * Vector3(10.0, 10.0, 10.0) );
	++m_index;
}

// -----------------------------------------------------------------------------


PVApplication::PVApplication() : ExampleApplication()
{
}

PVApplication::~PVApplication()
{
	for(unsigned int i = 0; i < m_balls.size(); ++i)
	{
		delete m_balls.at(i);
	}
}
void PVApplication::createCamera(void)
{
	mCamera = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Vector3(0, 60, 100));
	mCamera->lookAt(Vector3(0,0, 0));
	mCamera->setNearClipDistance(5);		
	
}
void PVApplication::createViewports(void)
{
	Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(ColourValue(0,0,0));
	mCamera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));  
}

void PVApplication::createScene(void)
{
	Light *light;
	
	light = mSceneMgr->createLight("Light1");
	light->setType( Light::LT_DIRECTIONAL);
	light->setDiffuseColour(0.01, 0.01, 0.35);
	light->setSpecularColour(0.01, 0.01, 0.35);
	light->setDirection(0, 0, -50);
	light->setPosition(Vector3(0,0,100));
	
	float intensity = 0.5f;
	light = mSceneMgr->createLight("Light2");
	light->setType( Light::LT_POINT);
	light->setPosition(Vector3(0,100,0));
	light->setDiffuseColour(intensity, intensity, intensity);
	light->setSpecularColour(intensity, intensity, intensity);
	// arena
	Entity* arenaEntity = mSceneMgr->createEntity( "ArenaEntity", "arena.mesh" );
	SceneNode* arenaNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( "ArenaNode", Vector3(0.0f, 6.5f,  0.0f) );
	arenaNode->attachObject( arenaEntity );
	PVNode *arena = new PVNode("Arena", arenaNode, arenaEntity);
	
	// goal wall
	Entity* wallEntity = mSceneMgr->createEntity( "TorwandEntity", "wall.mesh" );
	SceneNode* wallNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( "TorwandNode", Vector3(0.0f, 0.0f, -26.0f) );
	wallNode->attachObject( wallEntity );
	PVNode *wall = new PVNode("wall", wallNode, wallEntity);
	
	// pillar
//	Entity* p1Entity = mSceneMgr->createEntity( "p1", "pillar.mesh" );
//	SceneNode* p1Node = mSceneMgr->getRootSceneNode()->createChildSceneNode( "p1Node", Vector3(26.0f, 14.6f, -12.0f) );
//	p1Node->attachObject( p1Entity );
//	
//	Entity* p2Entity = mSceneMgr->createEntity( "p2", "pillar.mesh" );
//	SceneNode* p2Node = mSceneMgr->getRootSceneNode()->createChildSceneNode( "p2Node", Vector3(-26.0f, 14.6f, -12.0f) );
//	p2Node->attachObject( p2Entity );
	
	// cannon
	Entity* kanoneEntity = mSceneMgr->createEntity( "KanoneEntity", "cannon.mesh" );
	SceneNode* kanoneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( "KanoneNode", Vector3(0.0f, 4.3f, 37.5f) );
	kanoneNode->attachObject( kanoneEntity );
	PVNode *kanone = new PVNode("kanone", kanoneNode, kanoneEntity);
	
	m_objectMap["wall"] = wall;
	m_objectMap["arena"] = arena;
	m_objectMap["kanone"] = kanone;
	
	for (unsigned int i = 0; i < 50; ++i) 
	{
		std::stringstream s;
		s << "SphereEntity " << i;// << number;
		Entity *sphereEntity = mSceneMgr->createEntity(s.str(), "sphere.mesh"); 
		s << "node";
		SceneNode *sphereNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(s.str());
		sphereNode->attachObject( sphereEntity );
		sphereNode->scale(Vector3(0.02,0.02,0.02));
		PVNode *ball = new PVNode("sphere", sphereNode, sphereEntity);

		ball->translateNode(kanone->getPosition());
		
		m_balls.push_back(ball);
		
	}
}

void PVApplication::createFrameListener(void)
{
	// Create the FrameListener
	mFrameListener = new PVFrameListener(mWindow, mCamera, mSceneMgr, m_objectMap, m_balls);
	mRoot->addFrameListener(mFrameListener);
	
	// infos links unten
	mFrameListener->showDebugOverlay(true);
}

// -----------------------------------------------------------------------------

int main(int argc, char **argv)
{
    // Create application object
    PVApplication app;
	
    try {
        app.go();
    } catch( Exception& e ) {
        fprintf(stderr, "An exception has occurred: %s\n",
				e.getFullDescription().c_str());
    }
	
    return 0;
}
