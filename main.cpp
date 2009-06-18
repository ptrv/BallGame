
#include "BallApp.h"
//#include "PVApplication.h"
//#include "PVFrameListener.h"
#include <sstream>

using namespace Ogre;


PVFrameListener::PVFrameListener( RenderWindow* win, Camera* cam, SceneManager *sceneMgr, PVApplication *pvApp )
: ExampleFrameListener(win, cam, true, false), m_pvApp(pvApp)
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
	////PVTimer = new PVTimer();
	//speed = 1;
	//dtime = 0.0;
	//first = true;
	//v = Vector3(0,0,0);
	//move = false;
	//physicsNode = new PVPhysicsNode(mSceneMgr->getSceneNode("SphereNode"));
	physicsNode = new PVPhysics();
	kanoneMoveDelta = Radian(0.02);
	escPressed = true;
	
}

// //Overriding the default processUnbufferedKeyInput so the key updates we define
// //later on work as intended.
//bool PVFrameListener::processUnbufferedKeyInput(const FrameEvent& evt)
//{
//	return true;
//}
//
//// Overriding the default processUnbufferedMouseInput so the Mouse updates we define
//// later on work as intended. 
//bool PVFrameListener::processUnbufferedMouseInput(const FrameEvent& evt)
//{
//	return true;
//}

bool PVFrameListener::frameStarted(const FrameEvent &evt)
{
	physicsNode->simulate(m_pvApp->getBalls(), evt.timeSinceLastFrame);
	return escPressed;
}

bool PVFrameListener::keyPressed(const OIS::KeyEvent &arg)
{
	bool handled = true;
	Radian rad;
	Vector3 pos;
	switch(arg.key)
	{
		case OIS::KC_ESCAPE:
			handled = false;
			escPressed = false;
			break;
		case OIS::KC_SPACE:
			handled = true;
			m_pvApp->createBall();
			break;
		case OIS::KC_A:
			rad = mSceneMgr->getSceneNode("KanoneNode")->getOrientation().getYaw();
			//pos = mSceneMgr->getSceneNode("KanoneNode")->getPosition();
			//mSceneMgr->getSceneNode("KanoneNode")->setPosition(-pos);
			mSceneMgr->getSceneNode("KanoneNode")->yaw(-rad);
			mSceneMgr->getSceneNode("KanoneNode")->yaw(rad+kanoneMoveDelta);
			//mSceneMgr->getSceneNode("KanoneNode")->setPosition(pos);
			handled = true;
			break;
		case OIS::KC_D:
			rad = mSceneMgr->getSceneNode("KanoneNode")->getOrientation().getYaw();
			mSceneMgr->getSceneNode("KanoneNode")->yaw(-rad);
			mSceneMgr->getSceneNode("KanoneNode")->yaw(rad-kanoneMoveDelta);
			handled = true;
			break;
		case OIS::KC_W:
			rad = mSceneMgr->getSceneNode("KanoneNode")->getOrientation().getPitch();
			mSceneMgr->getSceneNode("KanoneNode")->pitch(-rad);
			mSceneMgr->getSceneNode("KanoneNode")->pitch(rad+kanoneMoveDelta);
			handled = true;
			break;
		case OIS::KC_S:
			rad = mSceneMgr->getSceneNode("KanoneNode")->getOrientation().getPitch();
			mSceneMgr->getSceneNode("KanoneNode")->pitch(-rad);
			mSceneMgr->getSceneNode("KanoneNode")->pitch(rad-kanoneMoveDelta);
			handled = true;
			break;
	}
	return escPressed;
}

bool PVFrameListener::keyReleased(const OIS::KeyEvent &arg)
{
	bool handled = true;
	
	return handled;
}

// -----------------------------------------------------------------------------


PVApplication::PVApplication() : ExampleApplication()
{
}

PVApplication::~PVApplication()
{
	for(unsigned int i = 0; m_balls.size(); ++i)
	{
		delete m_balls[i];
	}
}
void PVApplication::createCamera(void)
{
	mCamera = mSceneMgr->createCamera("PlayerCam");
	//steht etwas oben und zu mir
	mCamera->setPosition(Vector3(0, 15, 50));
	//guckt zum nullpunkt
	//mit lookAt() umgehen von rotieren der camera
	mCamera->lookAt(Vector3(0,0, -26.0f));
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
	// All objects are exported without knowing their position in the real world. 
	// You have to translate them manually.
	
	// arena
	Entity* arenaEntity = mSceneMgr->createEntity( "ArenaEntity", "arena.mesh" );
	SceneNode* arenaNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( "ArenaNode", Vector3(0.0f, 6.5f,  0.0f) );
	arenaNode->attachObject( arenaEntity );
	
	// goal wall
	Entity* wallEntity = mSceneMgr->createEntity( "TorwandEntity", "wall.mesh" );
	SceneNode* wallNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( "TorwandNode", Vector3(0.0f, 0.0f, -26.0f) );
	wallNode->attachObject( wallEntity );
	
	// pillar
//	Entity* p1Entity = mSceneMgr->createEntity( "p1", "pillar.mesh" );
//	SceneNode* p1Node = mSceneMgr->getRootSceneNode()->createChildSceneNode( "p1Node", Vector3(26.0f, 14.6f, -12.0f) );
//	p1Node->attachObject( p1Entity );
//	
//	Entity* p2Entity = mSceneMgr->createEntity( "p2", "pillar.mesh" );
//	SceneNode* p2Node = mSceneMgr->getRootSceneNode()->createChildSceneNode( "p2Node", Vector3(-26.0f, 14.6f, -12.0f) );
//	p2Node->attachObject( p2Entity );
	
	// cannon
	Entity* cannonEntity = mSceneMgr->createEntity( "KanoneEntity", "cannon.mesh" );
	SceneNode* cannonNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( "KanoneNode", Vector3(0.0f, 4.3f, 37.5f) );
	cannonNode->pitch( Degree( 15.0 ) );
	cannonNode->attachObject( cannonEntity );
}

void PVApplication::createFrameListener(void)
{
	// Create the FrameListener
	mFrameListener = new PVFrameListener(mWindow, mCamera, mSceneMgr, this);
	mRoot->addFrameListener(mFrameListener);
	
	// infos links unten
	mFrameListener->showDebugOverlay(true);
}

void PVApplication::createBall()
{
	int number = PVBall::getBallCount();
	std::stringstream s;
	s << "Sphere" << number;
	Entity *sphereEntity = mSceneMgr->createEntity(s.str(), "sphere.mesh"); 
	s << "node";
	SceneNode *sphereNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(s.str() , Vector3(0.0f, 4.3f, 37.5f));
	sphereNode->scale(Vector3(0.02,0.02,0.02));
	sphereNode->attachObject( sphereEntity );
	PVBall *ball = new PVBall(sphereNode, sphereEntity);
	ball->setAcceleration((mSceneMgr->getSceneNode("KanoneNode")->getOrientation()*Vector3(0,0,-1)*55.0));//wie fest. t
	ball->setVelocity(mSceneMgr->getSceneNode("KanoneNode")->getOrientation()*Vector3(0,0,-1)*15.0);//wie schnell fällt er
	
	m_balls.push_back(ball);
	
}

std::vector<PVBall*>& PVApplication::getBalls()
{
	return m_balls;
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
