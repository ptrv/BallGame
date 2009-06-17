/*==========================================================
 Copyright (c) Peter Vasil, 2008
 ==========================================================*/
#ifndef _MYAPPLICATION_H_
#define _MYAPPLICATION_H_

#include "ExampleApplication.h"

class MyApplication : public ExampleApplication
	{
	public:
		MyApplication();		
		~MyApplication(); 
		
	protected:
		
		void createCamera(void);		
		void createViewports(void);
		
		void createScene(void);
		
		void createFrameListener(void);
		
	private:
		Entity* sphereEntity;
		SceneNode* sphereNode;
	};

#endif //_MYAPPLICATION_H_