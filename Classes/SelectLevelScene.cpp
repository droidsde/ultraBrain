#include "SelectLevelScene.h"
#include "MyButton.h"
#include "Constant.h"
#include "HelloWorldScene.h"

#include <sstream>
#include <string>

#define userDefault CCUserDefault::sharedUserDefault()
#define CONSTANT Constant::getInstance()
#define IMAGEPOOL CCTextureCache::sharedTextureCache()



CCScene* SelectLevel::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	SelectLevel *layer = SelectLevel::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool SelectLevel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	this->setTouchEnabled(true);
	userDefault->setIntegerForKey("max_level", 7);
	winSize = CCDirector::sharedDirector()->getVisibleSize();
	
	CCSprite *back = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/back.png"));
	back->setPosition(ccp(30, winSize.height - 30));
	back->setScale(0.7f);
	this->addChild(back, 1);

	readData();

	displayLevels();

	displayScore();

	//背景滚动
	CCSprite *m_pBackGround1 = CCSprite::create("/pic/background.png");    // STR_BACKGROUND是图片的路径
	CCSprite *m_pBackGround2 = CCSprite::create("/pic/background.png");    // 加载背景
	CCAssert(m_pBackGround1 && m_pBackGround2, "");
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCRect rcBounding = m_pBackGround1->boundingBox();
	m_pBackGround1->setPosition(ccp(rcBounding.size.width / 2, size.height / 2));    // 设置在屏幕中间
	m_pBackGround2->setPosition(ccp(rcBounding.size.width * 3 / 2, size.height / 2));// 设置精灵2连接在精灵1的后面
	this->addChild(m_pBackGround1, 0, 100);    // 0
	this->addChild(m_pBackGround2, 0, 200);

	scheduleUpdate();


	return true;
}


void SelectLevel::update(float delta)
{
	// 背景无限滚动
	CCSprite *m_pBackGround1 = (CCSprite*)this->getChildByTag(100);
	CCSprite *m_pBackGround2 = (CCSprite*)this->getChildByTag(200);
	CCAssert(m_pBackGround1 && m_pBackGround2, "");
	m_pBackGround1->setPositionX(m_pBackGround1->getPositionX() - 1);    // 每次update都向左移动1点
	m_pBackGround2->setPositionX(m_pBackGround2->getPositionX() - 1);
	CCRect rcBounding1 = m_pBackGround1->boundingBox();
	CCRect rcBounding2 = m_pBackGround2->boundingBox();
	if (rcBounding1.getMaxX() <= 0)    // 如果完全消失在屏幕上，就移动精灵1到精灵2的后面
	{
		m_pBackGround1->setPositionX(rcBounding1.size.width * 3 / 2);
	}
	if (rcBounding2.getMaxX() <= 0)    // 如果完全消失在屏幕上，就移动精灵2到精灵1的后面
	{
		m_pBackGround2->setPositionX(rcBounding2.size.width * 3 / 2);
	}
}


void SelectLevel::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}


void SelectLevel::readData()
{
	if (!userDefault->getIntegerForKey("level"))
	{
		level = 1;
		userDefault->setIntegerForKey("level", 1);
	}
	else
	{
		level = userDefault->getIntegerForKey("level");
	}

	if (!userDefault->getIntegerForKey("score"))
	{
		score = 0;
		userDefault->setIntegerForKey("score", 0);
	}
	else
	{
		score = userDefault->getIntegerForKey("score");
	}
}

void SelectLevel::displayLevels()
{
	stringstream ss;
	CCLabelAtlas *lable = NULL;
	MyButton *but = NULL;
	string str_level, str_description;
	CCScene *scene = NULL;

	int max_level = userDefault->getIntegerForKey("max_level");
	float xPosition = CONSTANT->getFirstLevelPosition()[0];
	float yPosition = CONSTANT->getFirstLevelPosition()[1];
	CCDictionary *dict = CCDictionary::createWithContentsOfFile("/word/words.xml");
	
	for (int i = 0; i < max_level; i++)
	{
		ss << (i + 1);
		lable = CCLabelAtlas::create(ss.str().c_str(), "/pic/numbers.png", 23, 26, '0');

		but = MyButton::createWithTexture(IMAGEPOOL->textureForKey("/pic/level.png"));
		but->setTag(0);
		
		scene = CONSTANT->getAllLevels()[i];
		but->setNavigation(scene);

		but->addChild(lable);
		lable->setPosition(ccp(25, 25));

		but->setPosition(ccp(xPosition + i % 4 * 84, yPosition - i / 4 * 83));
		this->addChild(but, 1);

		ss.str("");

	}

	Constant::isSetLevel = false;

}

void SelectLevel::displayScore()
{
	stringstream ss;
	ss << (score);
	CCLabelAtlas *lable = CCLabelAtlas::create(ss.str().c_str(), "/pic/numbers.png", 23, 26, '0');

	CCLabelTTF *s_score = CCLabelTTF::create("SCORE:", "Arial", 34);
	s_score->setPosition(ccp(winSize.width / 2 - 80, 44));
	s_score->setColor(ccc3(255, 0, 0));
	lable->setPosition(ccp(winSize.width / 2, 30));

	this->addChild(s_score, 1);
	this->addChild(lable, 1);
}


bool SelectLevel::ccTouchBegan(CCTouch *touch, CCEvent *event)
{

	CCPoint p = touch->getLocation();
	CCLog("openGl = %f, %f", p.x, p.y);
	if (p.x > 10 && p.x < 53 && p.y < 280 && p.y > 230)
	{
		return true;
	}
	return false;
}

void SelectLevel::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCPoint p = touch->getLocation();
	if (p.x > 10 && p.x < 53 && p.y < 280 && p.y > 230)
	{
		CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
	}
}