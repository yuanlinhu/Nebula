
#ifndef Example25FrameListener_h_
#define Example25FrameListener_h_

#include "BaseApplication.h"

static std::vector<std::string> ani_vec;

class Example25FrameListener : public Ogre::FrameListener
{
public:
	Example25FrameListener(Ogre::Entity* entity, Ogre::SceneNode* node, OIS::Keyboard* keyboard, Ogre::Camera* cam, OIS::Mouse*mouse);
	~Example25FrameListener();

	virtual bool frameStarted(const Ogre::FrameEvent& evt);
	


private:
	Ogre::Entity* mEntity;
	Ogre::AnimationState* mAnimationState;
	Ogre::AnimationState* mAnimationStateTop;
	Ogre::SceneNode* mNode;

	OIS::Keyboard* mKeyboard;

	Ogre::Camera* mCamera;

	OIS::Mouse*	mMouse;
};


#endif