#include "SecondLevel.h"
#include "SelectLevelScene.h"
#include <sstream>

#define IMAGEPOOL CCTextureCache::sharedTextureCache()
#define userDefault CCUserDefault::sharedUserDefault()

using namespace std;

CCScene* SecondLevel::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	SecondLevel *layer = SecondLevel::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void SecondLevel::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool SecondLevel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	isRemoved = false;
	isDone = false;
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite *bg = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/background.png"));
	bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(bg, 0);

	rule_img = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/level2.png"));
	rule_img->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	rule_img->setScale(0.4f);
	rule_img->setTag(10);
	this->addChild(rule_img, 1);

	forward_button = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/forward.png"));
	forward_button->setPosition(ccp(350,
		forward_button->getContentSize().height / 2 + CCDirector::sharedDirector()->getVisibleOrigin().y));
	rule_img->addChild(forward_button);

	key_img = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/level2_key_face.png"));
	key_img->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	key_img->setVisible(false);
	this->addChild(key_img, 1);

	candidatite_img = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/level2_condaditate_faces.png"));
	candidatite_img->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	candidatite_img->setScale(0.5f);
	candidatite_img->setVisible(false);
	this->addChild(candidatite_img, 1);


	result = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/result.png"));
	result->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	result->setVisible(false);
	this->addChild(result, 1);

	CCSprite *back = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/back.png"));
	back->setPosition(ccp(60, 100));
	back->setScale(0.7f);
	result->addChild(back);



	CCLabelBMFont *lbLife = CCLabelBMFont::create("20", "/word/font09.fnt");
	lbLife->setAnchorPoint(ccp(0, 1));
	lbLife->setScale(0.6f);
	lbLife->setPosition(ccp(winSize.width - 70, winSize.height - 1));
	lbLife->setVisible(false);
	this->addChild(lbLife, 1, 15);

	this->setTouchEnabled(true);
	this->setTag(0);
	return true;
}


void SecondLevel::twoSecondsCallback(float dt)
{
	time -= dt;
	if (time < 1)
	{
		this->removeChild((CCNode*)key_img);
		CCFadeIn *fadeIn = CCFadeIn::create(1.0f);
		candidatite_img->setVisible(true);
		//candidatite_img->runAction(CCSequence::create(fadeIn, NULL));
		this->unschedule(schedule_selector(SecondLevel::twoSecondsCallback));
		time = 20;
		CCLabelBMFont *label1 = (CCLabelBMFont *)this->getChildByTag(15);
		label1->setVisible(true);
		this->schedule(schedule_selector(SecondLevel::tenSecondsCallback));
	}
}

void SecondLevel::tenSecondsCallback(float dt)
{
	time -= dt;
	if (time < 1)
	{
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
		this->unschedule(schedule_selector(SecondLevel::tenSecondsCallback));
	}
	char time_str[20];
	sprintf(time_str, "%d", (int)time);
	CCLabelBMFont *label1 = (CCLabelBMFont *)this->getChildByTag(15);
	label1->setString(time_str);
}


void SecondLevel::fadeOutCallback()
{
	this->removeChild((CCNode*)rule_img);
	isRemoved = true;

	time = 5;
	this->schedule(schedule_selector(SecondLevel::twoSecondsCallback), 1.0f);

	key_img->setVisible(true);
	CCFadeIn *fadeIn = CCFadeIn::create(1.0f);
	key_img->runAction(CCSequence::create(fadeIn, NULL));
}

void SecondLevel::fadeInCallback()
{

}

bool SecondLevel::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	CCPoint p = touch->getLocation();
	CCLog("openGl = %f, %f", p.x, p.y);
	if (!isRemoved && (p.x > 218 && p.x < 250) && (p.y > 30 && p.y < 59))
	{
		CCFadeOut *fadeOut = CCFadeOut::create(1.0f);
		rule_img->runAction(CCSequence::create(fadeOut, NULL));
		forward_button->runAction(CCSequence::create((CCFadeOut*)fadeOut->copy()->autorelease(), CCCallFunc::create(this, callfunc_selector(SecondLevel::fadeOutCallback)), NULL));
		return true;
	}
	if (!isDone && (p.x >313 && p.x <364 && p.y > 94 && p.y < 155))
	{
		//right
		return true;
	}
	else if (!isDone && ((p.x > 47 && p.x < 98 && p.y > 166 && p.y < 225) ||
		(p.x > 113 && p.x < 164 && p.y > 166 && p.y < 225) ||
		(p.x > 181 && p.x < 232 && p.y > 166 && p.y < 225) ||
		(p.x > 247 && p.x < 297 && p.y > 166 && p.y < 225) ||
		(p.x > 313 && p.x < 364 && p.y > 166 && p.y < 225) ||
		(p.x > 380 && p.x < 431 && p.y > 166 && p.y < 225) ||
		(p.x > 47 && p.x < 98 && p.y > 94 && p.y < 155) ||
		(p.x > 113 && p.x < 164 && p.y > 94 && p.y < 155) ||
		(p.x > 181 && p.x < 232 && p.y > 94 && p.y < 155) ||
		(p.x > 247 && p.x < 297 && p.y > 94 && p.y < 155) ||
		(p.x > 380 && p.x < 431 && p.y > 94 && p.y < 155)))
	{
		return true;
	}
	if (isDone && p.x > 129 && p.x < 172 && p.y > 101 && p.y < 132)
	{
		return true;
	}
	return false;
}

void SecondLevel::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCPoint p = touch->getLocation();
	if (!isRemoved && (p.x > 218 && p.x < 250) && (p.y > 30 && p.y < 59))
	{
		CCFadeOut *fadeOut = CCFadeOut::create(1.0f);
		rule_img->runAction(CCSequence::create(fadeOut, NULL));
		forward_button->runAction(CCSequence::create((CCFadeOut*)fadeOut->copy()->autorelease(), CCCallFunc::create(this, callfunc_selector(SecondLevel::fadeOutCallback)), NULL));
	}

	CCDictionary *dict = CCDictionary::createWithContentsOfFile("/word/words.xml");
	const char *win_word = ((CCString*)dict->objectForKey("win"))->m_sString.c_str();
	const char *lose_word = ((CCString*)dict->objectForKey("lose"))->m_sString.c_str();
	if (p.x >313 && p.x <364 && p.y > 94 && p.y < 155)
	{
		//right

		int level = userDefault->getIntegerForKey("level");
		if (level == 2)
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
		this->unschedule(schedule_selector(SecondLevel::tenSecondsCallback));
		isDone = true;


	}
	else if (!isDone && (p.x > 47 && p.x < 98 && p.y > 166 && p.y < 225) ||
		(p.x > 113 && p.x < 164 && p.y > 166 && p.y < 225) ||
		(p.x > 181 && p.x < 232 && p.y > 166 && p.y < 225) ||
		(p.x > 247 && p.x < 297 && p.y > 166 && p.y < 225) ||
		(p.x > 313 && p.x < 364 && p.y > 166 && p.y < 225) ||
		(p.x > 380 && p.x < 431 && p.y > 166 && p.y < 225) ||
		(p.x > 47 && p.x < 98 && p.y > 94 && p.y < 155) ||
		(p.x > 113 && p.x < 164 && p.y > 94 && p.y < 155) ||
		(p.x > 181 && p.x < 232 && p.y > 94 && p.y < 155) ||
		(p.x > 247 && p.x < 297 && p.y > 94 && p.y < 155) ||
		(p.x > 380 && p.x < 431 && p.y > 94 && p.y < 155))
	{
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
		this->unschedule(schedule_selector(SecondLevel::tenSecondsCallback));
		isDone = true;

	}
	if (isDone && p.x > 129 && p.x < 172 && p.y > 101 && p.y < 132)
	{
		CCDirector::sharedDirector()->replaceScene(SelectLevel::scene());
	}

}