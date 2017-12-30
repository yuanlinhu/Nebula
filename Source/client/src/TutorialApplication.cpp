/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
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


#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include <winsock2.h>

#ifndef _WINSOCKAPI_           // 没有包含winsock.h
	#define _WINSOCKAPI_           // 避免再包含winsock.h

	#ifndef _WINSOCK2API_      // 没有包含winsock2.h
	#define _WINSOCK2API_      // 避免再包含winsock2.h
	#include <winsock2.h>
	#endif
#endif

#include "TutorialApplication.h"
#include "Example25FrameListener.h"
#include "EntityBaseManager.h"
#include "EntityBase.h"
#include "OgreMovableObject.h"

#include <string>


#include "event2/event.h"
#include<event2/bufferevent.h>  
#include<event2/buffer.h>  
#include<event2/util.h>  

#include "address.pb.h"
#include <iostream>

using namespace Ogre;
using namespace std;



void cmd_msg_cb(int fd, short events, void* arg);  
void server_msg_cb(struct bufferevent* bev, void* arg);  
void event_cb(struct bufferevent *bev, short event, void *arg);  


void cmd_msg_cb(int fd, short events, void* arg)  
{  
// 	char msg[1024];  
// 
// 	int ret = read(fd, msg, sizeof(msg));  
// 	if( ret < 0 )  
// 	{  
// 		perror("read fail ");  
// 		exit(1);  
// 	}  
// 
// 	struct bufferevent* bev = (struct bufferevent*)arg;  
// 
// 	//把终端的消息发送给服务器端  
// 	bufferevent_write(bev, msg, ret);  
}  


void server_msg_cb(struct bufferevent* bev, void* arg)  
{  
	char msg[1024];  

	size_t len = bufferevent_read(bev, msg, sizeof(msg));  
	msg[len] = '\0';  

	printf("recv %s from server\n", msg);  
}  

void write_to_server(bufferevent *bev)
{
	tutorial::Person person;

	person.set_name("flamingo32345 eewwsd ");     
	person.set_id(1234565);     

	cout<<person.name()<<endl;  
	cout<<person.id()<<endl;  

	std::string str;
	person.SerializeToString(&str); // 将对象序列化到字符串，除此外还可以序列化到fstream等

	bufferevent_write(bev, str.c_str(), str.size());

}


void event_cb(struct bufferevent *bev, short event, void *arg)  
{  

	if (event & BEV_EVENT_EOF)  
		printf("connection closed\n");  
	else if (event & BEV_EVENT_ERROR)  
		printf("some other error\n");  
	else if( event & BEV_EVENT_CONNECTED)  
	{  
		printf("the client has connected to server\n");  
		write_to_server(bev);
		return ;  
	}  

	//这将自动close套接字和free读写缓冲区  
	bufferevent_free(bev);  

	struct event *ev = (struct event*)arg;  
	if(NULL != ev)
	{
		event_free(ev);  

	}
}  



static void Hello() {
	// 睡眠一秒以模拟数据处理。

	int port = 9876;
	std::string ip = "127.0.0.1";


 	event_base* new_event_base = event_base_new();
 

	struct bufferevent* bev = bufferevent_socket_new(new_event_base, -1,  
		BEV_OPT_CLOSE_ON_FREE);  


	sockaddr_in server_addr;  
	memset(&server_addr, 0, sizeof(server_addr) );  
	server_addr.sin_family = AF_INET;  
	server_addr.sin_port = htons(port);  
	server_addr.sin_addr.s_addr = inet_addr(ip.c_str());
	//inet_aton(ip.c_str(), &server_addr.sin_addr);  

	bufferevent_socket_connect(bev, (struct sockaddr *)&server_addr,  
		sizeof(server_addr));  


	bufferevent_setcb(bev, server_msg_cb, NULL, event_cb, NULL);  
	bufferevent_enable(bev, EV_READ | EV_PERSIST);  

 	event_base_dispatch(new_event_base);

	std::cout << "Hello, World!" << std::endl;
}



//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
	mSinbadEntity = NULL;

	mSinbadNode = NULL;
	mHeadNode = NULL;

	mFrameListener = NULL;

	mEntityBaseManager = NULL;
}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
	if(NULL != mFrameListener) 
	{
		delete mFrameListener;
		mFrameListener = NULL;
	}

}

//---------------------------------------------------------------------------
void TutorialApplication::createManual(void)
{
	Ogre::ManualObject* manual = mSceneMgr->createManualObject("Quad");
	manual->begin("BaseWhiteNoLighting", RenderOperation::OT_TRIANGLE_LIST);

	manual->position(5.0, 0.0, 0.0);
	manual->textureCoord(0,1);
	manual->position(-5.0, 10.0,0.0);
	manual->textureCoord(1,0);
	manual->position(-5.0, 0.0,0.0);
	manual->textureCoord(1,1);
	manual->position(5.0, 10.0, 0.0);
	manual->textureCoord(0,0);

	manual->index(0);
	manual->index(1);
	manual->index(2);
	manual->index(0);
	manual->index(3);
	manual->index(1);

	manual->end();
	manual->convertToMesh("Quad");

// 	Ogre::Entity * ent = mSceneMgr->createEntity("Quad");
// 	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Node1");
// 	node->attachObject(ent);
}

void TutorialApplication::init()
{
 	WORD wVersionRequested;
 	WSADATA wsaData;
 	int err;
 
 	wVersionRequested = MAKEWORD( 2, 2 );
 
 	err = WSAStartup( wVersionRequested, &wsaData );
 	if ( err != 0 ) {
 		/* Tell the user that we could not find a usable */
 		/* WinSock DLL.                                  */
 		return;
 	}

	boost::thread hello_thread(Hello);

	

	return ;
}

//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	init();

	mEntityBaseManager = new EntityBaseManager(mSceneMgr);
	mEntityBaseManager->loadEntity();

	//设置天空
	createSky();

	//设置光源
	createLight();

	//设置地面
	createPlane();
	

	createManual();

	createGrass();

	//设置自己角色
	createEntity();

	//设置怪物
	createMonster();

	//设置阴影
	//mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	return;
	
}


void TutorialApplication::loadCsv()
{
}

void TutorialApplication::createPlane()
{
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -10);

	Ogre::MeshManager::getSingleton().createPlane("plane",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
		1500, 1500, 200,200,true, 1,5,5,Ogre::Vector3::UNIT_Z);

	Ogre::Entity* planeEntity = mSceneMgr->createEntity("LightPlaneEntity", "plane");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(planeEntity);
	planeEntity->setMaterialName("Examples/BeachStones");
	
}

void TutorialApplication::createLight()
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(10.0, 10.0, 10.0));

	Ogre::Light* light = mSceneMgr->createLight("Light1");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDiffuseColour(Ogre::ColourValue(1.0, 1.0, 1.0));
	light->setDirection(Ogre::Vector3(1, -1, 0));
}

void TutorialApplication::createMonster()
{
	mEntityBaseManager->createEntity(2, 30, 4, 60);

	mEntityBaseManager->createEntity(1, 120, 4, 320);
	mEntityBaseManager->createEntity(1, -150, 4, 120);
	mEntityBaseManager->createEntity(1, 170, 4, 110);
	mEntityBaseManager->createEntity(3, 1130, 4, 1210);
}

void TutorialApplication::createSky()
{
	mSceneMgr->setSkyBox(true, "Examples/SceneCubeMap1", 5000);  // set our skybox
}

void TutorialApplication::createEntity()
{
	EntityBase* newEntity = mEntityBaseManager->createEntity(1);
	mSinbadEntity = newEntity->getEntity();
	mSinbadNode = newEntity->getSceneNode();
	mSinbadEntity->setMaterialName("Example/Sinbad");
}

void TutorialApplication::createCamera( void )
{
	mCamera = mSceneMgr->createCamera("MyCamera1");

	mCamera->setPosition(0, 100, 200);
	mCamera->lookAt(0,0,0);
	mCamera->setNearClipDistance(15);

	mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // Create a default camera controller
}

void TutorialApplication::createViewports( void )
{
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth())/ Ogre::Real(vp->getActualHeight()));

	ColourValue fadeColour(0.3, 0.3, 0.4);
	mWindow->getViewport(0)->setBackgroundColour(fadeColour);
	//mSceneMgr->setFog(FOG_LINEAR, fadeColour, 0.0, 50, 500);
}

void TutorialApplication::createFrameListener( void )
{
	BaseApplication::createFrameListener();

	mFrameListener = new Example25FrameListener(mSinbadEntity, mSinbadNode, mKeyboard, mCamera, mMouse);
	mRoot->addFrameListener(mFrameListener);
}

void TutorialApplication::createGrass()
{
	
	Ogre::ManualObject* manual = mSceneMgr->createManualObject("grass");
	manual->begin("Examples/GrassBlades", Ogre::RenderOperation::OT_TRIANGLE_LIST);


	
	manual->position(5.0, 0, 0);
	manual->textureCoord(1,1);
	
	manual->position(-5.0, 10, 0);
	manual->textureCoord(0,0);
	
	manual->position(-5.0, 0, 0);
	manual->textureCoord(0,1);

	manual->position(5.0, 0, 0);
	manual->textureCoord(1,1);

	manual->position(5.0, 10, 0);
	manual->textureCoord(1,0);

	manual->position(-5.0, 10, 0);
	manual->textureCoord(0,0);
	
	
	manual->end();

	manual->convertToMesh("BladesOfGrass");

	for (int i=0; i<1; ++i)
	{
		for (int j=0; j<1; ++j)
		{
			Entity* ent = mSceneMgr->createEntity("BladesOfGrass");
			Ogre::SceneNode* grassNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(
				Vector3(i*3, -10, j*3));
			grassNode->attachObject(ent);
		}
	}

	//Ogre::SceneNode* grassNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("grassNode2");
	//grassNode->attachObject(manual);

	
}


//---------------------------------------------------------------------------

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;
		//Example41 app;

        try {
			app.init();
            app.go();
        } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
