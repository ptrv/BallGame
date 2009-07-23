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
	/**
	 * \brief Constructor.
	 * \param win the window for rendering.
	 * \param sceneMgr the scene manager.
	 * \param objectMap a map with PVNodes.
	 * \param app an instance of PVApplication.
	 */
	PVFrameListener(RenderWindow* win, 
					Camera* cam, 
					SceneManager *sceneMgr, 
					std::map<std::string, PVNode*>& objectMap, 
					std::vector<PVNode*>& balls, 
					PVApplication *app );

	/**
	 * \brief Ogre callback function for simulation.
	 *
	 * \param &evt an event.
	 */
	bool frameStarted(const FrameEvent &evt);
	/**
	 * \brief callback function for pressing key.
	 * \param &arg a key event.
	 */
	bool keyPressed( const OIS::KeyEvent &arg );
	/**
	 * \brief callback function for releasing a key.
	 * \param &arg a key event.
	 */
	bool keyReleased( const OIS::KeyEvent &arg );  
	
protected:
	bool mMouseDownBool;       ///< Whether or not the left mouse button was down last frame
	Real mToggle;          ///< The time left until next toggle
	Real mRotate;          ///< The rotate constant
	Real mMove;            ///< The movement constant
	SceneManager *mSceneMgr;   ///< The current SceneManager
	SceneNode *mCamNode;   ///< The SceneNode the camera is currently attached to	
	bool mContinue;
private:
	/// Physics class.
	PVPhysics *m_physicsNode;
	/// Map with scene objects.
	std::map<std::string, PVNode*>& m_objectMap;
	/// object map iterator.
	std::map<std::string, PVNode*>::iterator it;
	/// Scene item Kanone
	PVNode *kanone;
	///vector with balls
	std::vector<PVNode*>& m_balls;
	/// index of balls
	int m_index;
	/// Ball shooting factor for multiplying with start velocity of a ball.
	float m_shootingSpeedFactor;
	/**
	 * \brief funktion for shooting balls out of cannon
	 *
	 */
	void shootBall();
	
	/// An instance of PVApplication
	PVApplication *m_app;
};

class PVApplication : public ExampleApplication
	{
	public:
		/// Constructor
		PVApplication();
		/// Destructor
		~PVApplication();
		/// max number of balls.
		int m_numberOfBalls;
		/// function for deleting all balls in the scene.
		void clearAllBalls();
		/// creates a vector with balls. 
		void createBalls();
	protected:
		/// Set camera settings.
		void createCamera(void);
		/// Set viewport settings.
		void createViewports(void);
		/// Create scene
		void createScene(void);
		/// Create Framelistener
		void createFrameListener(void);
		/// map with scene objects.
		std::map<std::string, PVNode*> m_objectMap;
		/// vector with balls.
		std::vector<PVNode*> m_balls;
	};

#endif // _PVAPPLICATION_H_#endif //_BALLAPP_H_
