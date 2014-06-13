#include "FifthLevel.h"
#include "Constant.h"
#include "SelectLevelScene.h"

#define IMAGEPOOL CCTextureCache::sharedTextureCache()
#define CONSTANT Constant::getInstance()
#define userDefault CCUserDefault::sharedUserDefault()

CCScene* FifthLevel::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	FifthLevel *layer = FifthLevel::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool FifthLevel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	this->setTouchEnabled(true);

	winSize = CCDirector::sharedDirector()->getVisibleSize();
	size = 30;
	key = rand() % 10;
	isRemoved = false;
	isDone = false;

	CCSprite *bg = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/background.png"));
	bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(bg, 0);

	setRule();
	setResult();

	CCLabelBMFont *lbLife = CCLabelBMFont::create("2", "/word/font09.fnt");
	lbLife->setAnchorPoint(ccp(0, 1));
	lbLife->setScale(0.6f);
	lbLife->setPosition(ccp(winSize.width - 70, winSize.height - 1));
	lbLife->setVisible(false);
	this->addChild(lbLife, 1, 15);

	return true;
}

void FifthLevel::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

void FifthLevel::setRule()
{
	rule_img = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/level5.png"));
	rule_img->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	rule_img->setScale(0.4f);
	this->addChild(rule_img, 1);

	forward_button = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/forward.png"));
	forward_button->setPosition(ccp(350,
		forward_button->getContentSize().height / 2 + CCDirector::sharedDirector()->getVisibleOrigin().y));
	rule_img->addChild(forward_button);
}

void FifthLevel::display()
{
	isRemoved = true;

	CCSprite *tian = NULL;
	CCLabelTTF *t = NULL;
	CCDictionary *dict = CCDictionary::createWithContentsOfFile("/word/words.xml");
	const char *level5_1 = ((CCString*)dict->objectForKey("level5_1"))->m_sString.c_str();
	const char *level5_2 = ((CCString*)dict->objectForKey("level5_2"))->m_sString.c_str();
	for (int i = 0; i < 10; i++)
	{
		if (i == key)
		{
			t = CCLabelTTF::create(level5_1, "Arial", 44);
		}
		else
		{
			t = CCLabelTTF::create(level5_2, "Arial", 44);
			
		}
		t->setPosition(ccp(25, 25));
		t->setColor(ccc3(0, 0, 0));

		tian = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/tian_level5.png"));
		tian->setPosition(ccp(CONSTANT->getLevelFivePosition()[i].x, CONSTANT->getLevelFivePosition()[i].y));
		this->addChild(tian, 1);

		tian->addChild(t, 1);

	}
	time = 3;
	CCLabelBMFont *label1 = (CCLabelBMFont *)this->getChildByTag(15);
	label1->setVisible(true);
	this->schedule(schedule_selector(FifthLevel::timeCallback), 1.0f);
}

void FifthLevel::timeCallback(float dt)
{
	time -= dt;
	if (time < 1)
	{
		isDone = true;
		CCDictionary *dict = CCDictionary::createWithContentsOfFile("/word/words.xml");
		const char *lose_word = ((CCString*)dict->objectForKey("lose"))->m_sString.c_str();

		CCLabelTTF *lose = CCLabelTTF::create(lose_word, "Arial", 24);
		lose->setColor(ccc3(255, 0, 0));
		lose->setPosition(ccp(150, 150));
		result->addChild(lose);

		int score = userDefault->getIntegerForKey("score");

		stringstream ss;
		ss << (score);
		CCLabelAtlas *lable = CCLabelAtlas::create(ss.str().c_str(), "/pic/numbers.png", 23, 26, '0');
		lable->setPosition(ccp(150, 100));
		result->addChild(lable);

		result->setVisible(true);

		this->unschedule(schedule_selector(FifthLevel::timeCallback));
	}
	char time_str[20];
	sprintf(time_str, "%d", (int)time);
	CCLabelBMFont *label1 = (CCLabelBMFont *)this->getChildByTag(15);
	label1->setString(time_str);
}

void FifthLevel::setResult()
{
	result = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/result.png"));
	result->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	result->setVisible(false);
	this->addChild(result, 3);

	CCSprite *back = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/back.png"));
	back->setPosition(ccp(60, 100));
	back->setScale(0.7f);
	result->addChild(back);
}



bool FifthLevel::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	CCPoint p = touch->getLocation();
	if (!isRemoved && (p.x > 218 && p.x < 250) && (p.y > 30 && p.y < 59))
	{
		return true;
	}
	int state = isContain(p);
	if (isRemoved && !isDone && state != -1)
	{
		return true;
	}
	if (isDone && p.x > 129 && p.x < 172 && p.y > 101 && p.y < 132)
	{
		return true;
	}
	return false;
}

void FifthLevel::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
	CCPoint p = touch->getLocation();
	if (!isRemoved && (p.x > 218 && p.x < 250) && (p.y > 30 && p.y < 59))
	{
		CCFadeOut *fadeOut = CCFadeOut::create(1.0f);
		rule_img->runAction(CCSequence::create(fadeOut, NULL));
		forward_button->runAction(CCSequence::create((CCFadeOut*)fadeOut->copy()->autorelease(), CCCallFunc::create(this, callfunc_selector(FifthLevel::display)), NULL));
	}
	int state = isContain(p);
	if (isRemoved && !isDone && state != -1)
	{
		isDone = true;
		CCDictionary *dict = CCDictionary::createWithContentsOfFile("/word/words.xml");
		const char *win_word = ((CCString*)dict->objectForKey("win"))->m_sString.c_str();
		const char *lose_word = ((CCString*)dict->objectForKey("lose"))->m_sString.c_str();
		if (state == 1)
		{
			//correct
			int level = userDefault->getIntegerForKey("level");
			if (level == 5)
				level++;
			userDefault->setIntegerForKey("level", level);

			int score = userDefault->getIntegerForKey("score");
			score += 5;
			userDefault->setIntegerForKey("score", score);

			CCLabelTTF *win = CCLabelTTF::create(win_word, "Arial", 24);
			win->setColor(ccc3(255, 0, 0));
			win->setPosition(ccp(150, 150));
			result->addChild(win);

			stringstream ss;
			ss << (score);
			CCLabelAtlas *lable = CCLabelAtlas::create(ss.str().c_str(), "/pic/numbers.png", 23, 26, '0');
			lable->setPosition(ccp(150, 100));
			result->addChild(lable);

			result->setVisible(true);
			this->unschedule(schedule_selector(FifthLevel::timeCallback));
		}
		else if (state == 0)
		{
			//wrong
			CCLabelTTF *lose = CCLabelTTF::create(lose_word, "Arial", 24);
			lose->setColor(ccc3(255, 0, 0));
			lose->setPosition(ccp(150, 150));
			result->addChild(lose);

			int score = userDefault->getIntegerForKey("score");

			stringstream ss;
			ss << (score);
			CCLabelAtlas *lable = CCLabelAtlas::create(ss.str().c_str(), "/pic/numbers.png", 23, 26, '0');
			lable->setPosition(ccp(150, 100));
			result->addChild(lable);

			result->setVisible(true);
			this->unschedule(schedule_selector(FifthLevel::timeCallback));
		}
	}
	if (isDone && p.x > 129 && p.x < 172 && p.y > 101 && p.y < 132)
	{
		CCDirector::sharedDirector()->replaceScene(SelectLevel::scene());
	}
}

int FifthLevel::isContain(CCPoint p)
{
	for (int i = 0; i < 10; i++)
	{
		if (p.x > CONSTANT->getLevelFivePosition()[i].x - 25 && p.x < CONSTANT->getLevelFivePosition()[i].x + 25 &&
			p.y > CONSTANT->getLevelFivePosition()[i].y - 25 && p.y < CONSTANT->getLevelFivePosition()[i].y + 25)
		{
			if (i == key)
				return 1;//correct
			else
				return 0;//wrong
		}	
	}
	return -1;//not contain
}