#include "Example25FrameListener.h"
#include "TutorialApplication.h"

Example25FrameListener::Example25FrameListener( Ogre::Entity* entity, Ogre::SceneNode* node, 
											   OIS::Keyboard* keyboard, Ogre::Camera* cam, OIS::Mouse*mouse)
: mAnimationState(NULL)
,mAnimationStateTop(NULL)
{
	mEntity = entity;
	mNode = node;
	mKeyboard = keyboard;
	mCamera = cam;
	mMouse = mouse;

	/*
	mAnimationState = mEntity->getAnimationState("RunBase");
	mAnimationState->setEnabled(true);

	mAnimationStateTop = mEntity->getAnimationState("RunTop");
	mAnimationStateTop->setEnabled(true);
	*/
}

Example25FrameListener::~Example25FrameListener()
{
	
}

bool Example25FrameListener::frameStarted( const Ogre::FrameEvent& evt )
{
	const int speed = 200;
	float rotation = 0;
	mMouse->capture();

	const OIS::MouseState& mouseState = mMouse->getMouseState();

	Ogre::Vector3 sinbadTranslate(0, 0, 0);
	//mNode->translate(Ogre::Vector3(10, 0, 0) * evt.timeSinceLastFrame);
	mKeyboard->capture();
	if (mKeyboard->isKeyDown(OIS::KC_I))
	{
		Ogre::Vector3 vec(0, 0, -speed);
		rotation = 3.14f;
		mNode->resetOrientation();
		mNode->yaw(Ogre::Radian(rotation));
		sinbadTranslate += vec;

		//ÒÆ¶¯
		mNode->translate(vec * evt.timeSinceLastFrame);
	}
	if (mKeyboard->isKeyDown(OIS::KC_K))
	{
		Ogre::Vector3 vec(0, 0, speed);
		rotation = 0;
		mNode->resetOrientation();
		mNode->yaw(Ogre::Radian(rotation));
		sinbadTranslate += vec;

		mNode->translate(vec * evt.timeSinceLastFrame);
	}
	if (mKeyboard->isKeyDown(OIS::KC_J))
	{
		Ogre::Vector3 vec(-speed, 0, 0);
		rotation = -1.57f;
		mNode->resetOrientation();
		mNode->yaw(Ogre::Radian(rotation));

		sinbadTranslate += vec;

		mNode->translate(vec * evt.timeSinceLastFrame);
	}
	if (mKeyboard->isKeyDown(OIS::KC_L))
	{
		Ogre::Vector3 vec(speed, 0, 0);
		rotation = 1.57f;
		mNode->resetOrientation();
		mNode->yaw(Ogre::Radian(rotation));
		sinbadTranslate += vec;

		mNode->translate(vec * evt.timeSinceLastFrame);
	}

	if (mKeyboard->isKeyDown(OIS::KC_M))
	{
		TutorialApplication::send_msg_to_server(987654);
	}

	if(sinbadTranslate != Ogre::Vector3(0, 0, 0))
	{
		if(mAnimationState)
		{
			mAnimationState->setLoop(true);
		}

		if(mAnimationStateTop)
		{
			mAnimationStateTop->setLoop(true);
		}
	}
	else
	{
		if(mAnimationState)
		{
			mAnimationState->setLoop(false);
		}

		if(mAnimationStateTop)
		{
			mAnimationStateTop->setLoop(false);
		}
	}

	if(mouseState.buttonDown(OIS::MB_Left)) 
	{
		mNode->translate(sinbadTranslate * evt.timeSinceLastFrame);
	}

	if(mKeyboard->isKeyDown(OIS::KC_C))
	{
		/*
		static int ani_size = ani_vec.size();
		static int index = 0;
		index++;
		
		int ii = 0;


		std::string ani_name;
		Ogre::AnimationStateSet* as_set = mEntity->getAllAnimationStates();
		Ogre::AnimationStateIterator  iter = as_set->getAnimationStateIterator();
		while (iter.hasMoreElements())
		{
			ani_vec.push_back(iter.getNext()->getAnimationName());
			if(ii++ == index) 
			{
				ani_name = iter.getNext()->getAnimationName();
				break;
			}
			//std::cout<<"has more "<<iter.getNext()->getAnimationName()<<std::endl;
		}

		mAnimationState = mEntity->getAnimationState(ani_name);
		mAnimationState->setEnabled(true);
		mAnimationState->setLoop(true);
		*/
	}

	if(mAnimationState)
	{
		mAnimationState->addTime(evt.timeSinceLastFrame * 1.0);
	}

	if (mAnimationStateTop)
	{
		mAnimationStateTop->addTime(evt.timeSinceLastFrame * 1.0);
	}
	return true;
}

