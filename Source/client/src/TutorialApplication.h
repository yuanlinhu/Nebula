/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/

#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"


/*
TODO:

1. 生成 uid
2. 重构 createEntity 生成多个实体 方便测试九宫格
3. WorldCore 编写
4. 接入网络
5. protobuf







*/


class EntityBaseManager;
//---------------------------------------------------------------------------

class TutorialApplication : public BaseApplication
{
public:
    TutorialApplication(void);
    virtual ~TutorialApplication(void);

protected:
	virtual bool setup();

    virtual void createScene(void);
	virtual void createCamera(void);
	virtual void createViewports(void);
	virtual void createFrameListener(void);
	//virtual void chooseSceneManager(void);

private:
	void loadCsv();
	void createManual();
	void createPlane();
	void createLight();
	void createEntity();
	void createGrass();
	void createSky();

	//怪物 非控制实体
	void createMonster();

private:
	Ogre::Entity*		mSinbadEntity;
	Ogre::SceneNode*		mSinbadNode;
	Ogre::FrameListener*	mFrameListener;
	Ogre::SceneNode*		mHeadNode;

	EntityBaseManager*		mEntityBaseManager;

private:
	//ShrewMouseManager* mMiceManager;
};

//---------------------------------------------------------------------------

#endif // #ifndef __TutorialApplication_h_

//---------------------------------------------------------------------------
