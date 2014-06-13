#include <string>
#include <sstream>
#include "HelloWorldScene.h"
#include "SelectLevelScene.h"
#include "Constant.h"
#include "MyButton.h"

#define IMAGEPOOL CCTextureCache::sharedTextureCache()
#define CONSTANT Constant::getInstance()

USING_NS_CC;
using namespace std;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

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
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	winSize = CCDirector::sharedDirector()->getVisibleSize();


    /////////////////////////////
    // 3. add your codes below...
	
    // add a label shows "Hello World"
    // create and initialize a label


	current = 0;
	amount = CONSTANT->getAllPicPath().size();



	for (int i = 1; i <= amount; i++)
	{
		string path = CONSTANT->getAllPicPath()[i - 1];
		CCLog(path.c_str());
		IMAGEPOOL->addImageAsync(path.c_str(), this, callfuncO_selector(HelloWorld::callback));
	}

	


	CCDictionary *dict = CCDictionary::createWithContentsOfFile("/word/words.xml");
	const char *name = ((CCString*)dict->objectForKey("name"))->m_sString.c_str();
    
	CCLabelTTF* pLabel = CCLabelTTF::create(name, "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

	pLabel->setColor(ccc3(126, 126, 126));
    // add the label as a child to this layer
    this->addChild(pLabel, 1);


	CCSprite *m_pBackGround1 = CCSprite::create("/pic/background.png");    
	CCSprite *m_pBackGround2 = CCSprite::create("/pic/background.png");    
	CCAssert(m_pBackGround1 && m_pBackGround2, "");
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCRect rcBounding = m_pBackGround1->boundingBox();
	m_pBackGround1->setPosition(ccp(rcBounding.size.width / 2, size.height / 2));    
	m_pBackGround2->setPosition(ccp(rcBounding.size.width * 3 / 2, size.height / 2));
	this->addChild(m_pBackGround1, 0, 100);    // 0
	this->addChild(m_pBackGround2, 0, 200);

	scheduleUpdate();
    
    return true;
}


void HelloWorld::update(float delta)
{
	CCSprite *m_pBackGround1 = (CCSprite*)this->getChildByTag(100);
	CCSprite *m_pBackGround2 = (CCSprite*)this->getChildByTag(200);
	CCAssert(m_pBackGround1 && m_pBackGround2, "");
	m_pBackGround1->setPositionX(m_pBackGround1->getPositionX() - 1);    
	m_pBackGround2->setPositionX(m_pBackGround2->getPositionX() - 1);
	CCRect rcBounding1 = m_pBackGround1->boundingBox();
	CCRect rcBounding2 = m_pBackGround2->boundingBox();
	if (rcBounding1.getMaxX() <= 0)   
	{
		m_pBackGround1->setPositionX(rcBounding1.size.width * 3 / 2);
	}
	if (rcBounding2.getMaxX() <= 0)   
	{
		m_pBackGround2->setPositionX(rcBounding2.size.width * 3 / 2);
	}
}


void HelloWorld::callback(CCObject *object)
{
	current++;

	if (current == amount)
	{
		MyButton *p = MyButton::createWithTexture(IMAGEPOOL->textureForKey("/pic/forward.png"));
		p->setTag(0);
		p->setNavigation(SelectLevel::scene());
		p->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		this->addChild(p, 1);
	}


}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
