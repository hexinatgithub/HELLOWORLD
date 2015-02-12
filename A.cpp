#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include <iostream>
我在这里
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, -100));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    auto size=Director::getInstance()->getVisibleSize();
    //edge
    auto node=Node::create();
    node->setPosition(size.width/2, size.height/2);
    auto edgeBody=PhysicsBody::createEdgeBox(size);
    node->setPhysicsBody(edgeBody);
    scene->addChild(node);
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

    auto closeItem = static_cast<ui::Button*>(rootNode->getChildByName("Button_1"));
    closeItem->addTouchEventListener(CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    return true;
}

void HelloWorld::load()
{
    using namespace std;
    cout<<"loading"<<endl;
}

void HelloWorld::onEnter()
{
    Layer::onEnter();
    //thread
    _thread=new std::thread(&HelloWorld::load,this);
    //touch began
    auto listner=EventListenerTouchOneByOne::create();
    listner->onTouchBegan=[this](Touch* _touch, Event* _event)->bool{
        //point
        auto point=_touch->getLocation();
        //
        auto node1=Sprite::create();
        this->addChild(node1);
        auto circle=PhysicsBody::createCircle(50);
        circle->setContactTestBitmask(0x1);
        node1->setPhysicsBody(circle);
        node1->setPosition(point.x, point.y);
        //
        auto node2=Sprite::create();
        node2->setPosition(point.x,point.y);
        this->addChild(node2);
        auto circle2=PhysicsBody::createCircle(50);
        circle2->setContactTestBitmask(0x1);
        node2->setPhysicsBody(circle2);
        
        auto physic_world=this->getScene()->getPhysicsWorld();
        auto joint=PhysicsJointDistance::construct(circle, circle2, Vec2(0,50), Vec2(0,50));
        physic_world->addJoint(joint);
        
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listner, this);
    
    //physic listner
    auto physic_listner=EventListenerPhysicsContact::create();
    physic_listner->onContactBegin=[](PhysicsContact& contact)->bool{
        using namespace std;
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(physic_listner, this);
    
    auto list=cocos2d::Vector<Sprite*> ();
    list.pushBack(Sprite::create());
}

void HelloWorld::onExit()
{
    Layer::onExit();
    _eventDispatcher->removeEventListenersForTarget(this);
    using namespace std;
    cout<<"exit loading"<<endl;
    _thread->join();
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    的撒打算的
    的撒打算的大厦大厦的的
}
