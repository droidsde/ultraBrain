#include "SeventhLevel.h"
#include "Constant.h"
#include "SelectLevelScene.h"

#define IMAGEPOOL CCTextureCache::sharedTextureCache()
#define CONSTANT Constant::getInstance()
#define userDefault CCUserDefault::sharedUserDefault()

CCScene* SeventhLevel::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	SeventhLevel *layer = SeventhLevel::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool SeventhLevel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	this->setTouchEnabled(true);

	winSize = CCDirector::sharedDirector()->getVisibleSize();
	size = 30;
	key = rand() % 30;
	isRemoved = false;
	isDone = false;

	CCSprite *bg = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/background.png"));
	bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(bg, 0);

	setRule();
	setResult();

	CCLabelBMFont *lbLife = CCLabelBMFont::create("5", "/word/font09.fnt");
	lbLife->setAnchorPoint(ccp(0, 1));
	lbLife->setScale(0.6f);
	lbLife->setPosition(ccp(winSize.width - 70, winSize.height - 1));
	lbLife->setVisible(false);
	this->addChild(lbLife, 1, 15);

	return true;
}

void SeventhLevel::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

void SeventhLevel::setRule()
{
	rule_img = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/level7.png"));
	rule_img->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	rule_img->setScale(0.4f);
	this->addChild(rule_img, 1);

	forward_button = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/forward.png"));
	forward_button->setPosition(ccp(350,
		forward_button->getContentSize().height / 2 + CCDirector::sharedDirector()->getVisibleOrigin().y));
	rule_img->addChild(forward_button);
}

void SeventhLevel::display()
{
	isRemoved = true;

	CCSprite *tian = NULL;
	CCLabelTTF *t = NULL;
	for (int i = 0; i < 30; i++)
	{
		if (i == key)
		{
			t = CCLabelTTF::create("F", "Arial", 24);
		}
		else
		{
			t = CCLabelTTF::create("E", "Arial", 24);

		}
		t->setPosition(ccp(10, 10));
		t->setColor(ccc3(0, 0, 0));

		tian = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/tian_level7.png"));
		tian->setPosition(ccp(CONSTANT->getLevelSevenPosition()[i].x, CONSTANT->getLevelSevenPosition()[i].y));
		this->addChild(tian, 1);

		tian->addChild(t, 1);

	}
	time = 6;
	CCLabelBMFont *label1 = (CCLabelBMFont *)this->getChildByTag(15);
	label1->setVisible(true);
	this->schedule(schedule_selector(SeventhLevel::timeCallback), 1.0f);
}

void SeventhLevel::timeCallback(float dt)
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

		this->unschedule(schedule_selector(SeventhLevel::timeCallback));
	}
	char time_str[20];
	sprintf(time_str, "%d", (int)time);
	CCLabelBMFont *label1 = (CCLabelBMFont *)this->getChildByTag(15);
	label1->setString(time_str);
}

void SeventhLevel::setResult()
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



bool SeventhLevel::ccTouchBegan(CCTouch *touch, CCEvent *event)
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

void SeventhLevel::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
	CCPoint p = touch->getLocation();
	if (!isRemoved && (p.x > 218 && p.x < 250) && (p.y > 30 && p.y < 59))
	{
		CCFadeOut *fadeOut = CCFadeOut::create(1.0f);
		rule_img->runAction(CCSequence::create(fadeOut, NULL));
		forward_button->runAction(CCSequence::create((CCFadeOut*)fadeOut->copy()->autorelease(), CCCallFunc::create(this, callfunc_selector(SeventhLevel::display)), NULL));
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
			if (level == 7)
				level = 7;
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
			this->unschedule(schedule_selector(SeventhLevel::timeCallback));
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
			this->unschedule(schedule_selector(SeventhLevel::timeCallback));
		}
	}
	if (isDone && p.x > 129 && p.x < 172 && p.y > 101 && p.y < 132)
	{
		CCDirector::sharedDirector()->replaceScene(SelectLevel::scene());
	}
}

int SeventhLevel::isContain(CCPoint p)
{
	for (int i = 0; i < 30; i++)
	{
		if (p.x > CONSTANT->getLevelSevenPosition()[i].x - 10 && p.x < CONSTANT->getLevelSevenPosition()[i].x + 10 &&
			p.y > CONSTANT->getLevelSevenPosition()[i].y - 10 && p.y < CONSTANT->getLevelSevenPosition()[i].y + 10)
		{
			if (i == key)
				return 1;//correct
			else
				return 0;//wrong
		}
	}
	return -1;//not contain
}