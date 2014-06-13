#include "FourthLevel.h"
#include "SelectLevelScene.h"

#include <sstream>
#include <stdlib.h>

#define IMAGEPOOL CCTextureCache::sharedTextureCache()
#define userDefault CCUserDefault::sharedUserDefault()

CCScene* FourthLevel::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	FourthLevel *layer = FourthLevel::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool FourthLevel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	winSize = CCDirector::sharedDirector()->getVisibleSize();
	this->setTouchEnabled(true);

	isDone = false;
	isRemoved = false;
	isOver = false;

	CCSprite *bg = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/background.png"));
	bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(bg, 0);

	initAnsAndQues();
	setRandom();
	setRule();
	setResult();


	return true;
}

void FourthLevel::initAnsAndQues()
{
	for (int i = 0; i < 8; i++)
	{
		ans[i] = 0;
		stringstream ss;
		ss << (i + 1);
		string str = "question" + ss.str();
		CCDictionary *dict = CCDictionary::createWithContentsOfFile("/word/words.xml");
		ques[i] = ((CCString*)dict->objectForKey(str))->m_sString;
	}
}


void FourthLevel::setRandom()
{
	for (int i = 0; i < 10; i++)
	{
		int r = rand() % 6;
		pic[i] = r;
		switch (r)
		{
		case 0:
			ans[0] += 1;
			ans[6] += 1;
			break;
		case 1:
			ans[1] += 1;
			ans[7] += 1;
			break;
		case 2:
			ans[2] += 1;
			break;
		case 3:
			ans[3] += 1;
			break;
		case 4:
			ans[4] += 1;
			ans[6] += 1;
			break;
		case 5:
			ans[5] += 1;
			ans[7] += 1;
			break;
		default:
			break;
		}
	}
	key = rand() % 8;
}

void FourthLevel::setRule()
{
	rule_img = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/level4.png"));
	rule_img->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	rule_img->setScale(0.4f);
	rule_img->setTag(10);
	this->addChild(rule_img, 1);

	forward_button = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/forward.png"));
	forward_button->setPosition(ccp(350,
		forward_button->getContentSize().height / 2 + CCDirector::sharedDirector()->getVisibleOrigin().y));
	rule_img->addChild(forward_button);
}

void FourthLevel::setResult()
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

void FourthLevel::setEditBox()
{
	if (isOver)
	{
		return;
	}
	pos = rand() % 4;
	stringstream ss;
	CCSprite *ans_background = NULL;
	CCLabelTTF *label = NULL;
	for (int i = 0; i < 4; i++)
	{
		ss.str("");
		ans_background = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/level.png"));
		ans_background->setScale(0.5f);
		if (i == pos)
		{
			ss << (ans[key]);
		}
		else
		{
			ss << (ans[key] + i * 5 + 1);
		}
		label = CCLabelTTF::create(ss.str().c_str(), "Arial", 24);
		label->setColor(ccc3(255, 0, 0));
		label->setPosition(ccp(40, 40));
		ans_background->addChild(label);
		ans_background->setPosition(ccp(winSize.width / 2 - 100 + i * 50, winSize.height / 2));
		this->addChild(ans_background, 1);
	}

	const char *ch = ques[key].c_str();
	CCLabelTTF *ques = CCLabelTTF::create(ch , "Arial", 24);
	ques->setColor(ccc3(255, 0, 0));
	ques->setPosition(ccp(winSize.width / 2 - 20, winSize.height / 2 + 40));
	this->addChild(ques, 1);

	isOver = true;

}

//void FourthLevel::editBoxReturn(cocos2d::extension::CCEditBox *editBox)
//{
//	isDone = true;
//	CCLOG("the text = %s", editBox->getText());
//	this->removeChildByTag(15);
//
//	CCDictionary *dict = CCDictionary::createWithContentsOfFile("/word/words.xml");
//	const char *win_word = ((CCString*)dict->objectForKey("win"))->m_sString.c_str();
//	const char *lose_word = ((CCString*)dict->objectForKey("lose"))->m_sString.c_str();
//	int answer = atoi(editBox->getText());
//	if (answer == ans[key])
//	{
//		int level = userDefault->getIntegerForKey("level");
//		if (level == 4)
//			level++;
//		userDefault->setIntegerForKey("level", level);
//
//		int score = userDefault->getIntegerForKey("score");
//		score += 5;
//		userDefault->setIntegerForKey("score", score);
//
//		CCLabelTTF *win = CCLabelTTF::create(win_word, "Arial", 24);
//		win->setColor(ccc3(255, 0, 0));
//		win->setPosition(ccp(150, 150));
//		result->addChild(win);
//
//		stringstream ss;
//		ss << (score);
//		CCLabelAtlas *lable = CCLabelAtlas::create(ss.str().c_str(), "/pic/numbers.png", 23, 26, '0');
//		lable->setPosition(ccp(150, 100));
//		result->addChild(lable);
//
//		result->setVisible(true);
//	}
//	else
//	{
//		CCLabelTTF *lose = CCLabelTTF::create(lose_word, "Arial", 24);
//		lose->setColor(ccc3(255, 0, 0));
//		lose->setPosition(ccp(150, 150));
//		result->addChild(lose);
//
//		int score = userDefault->getIntegerForKey("score");
//
//		stringstream ss;
//		ss << (score);
//		CCLabelAtlas *lable = CCLabelAtlas::create(ss.str().c_str(), "/pic/numbers.png", 23, 26, '0');
//		lable->setPosition(ccp(150, 100));
//		result->addChild(lable);
//
//		result->setVisible(true);
//	}
//	this->removeChild((CCNode*)editBox);
//}

int FourthLevel::contains(CCPoint p)
{
	int ppos = 0;
	if (p.x > 124 && p.x < 152 && p.y > 146 && p.y < 177)
	{
		ppos = 0;
		if (ppos == pos)
			return 1;
		else
			return 0;
	}
	else if (p.x > 173 && p.x < 202 && p.y > 146 && p.y < 177)
	{
		ppos = 1;
		if (ppos == pos)
			return 1;
		else
			return 0;
	}
	else if (p.x > 222 && p.x < 251 && p.y > 146 && p.y < 177)
	{
		ppos = 2;
		if (ppos == pos)
			return 1;
		else
			return 0;
	}
	else if (p.x > 276 && p.x < 301 && p.y > 146 && p.y < 177)
	{
		ppos = 3;
		if (ppos == pos)
			return 1;
		else
			return 0;
	}
	return -1;
}


void FourthLevel::display()
{
	isRemoved = true;	
	time = 10;
	this->schedule(schedule_selector(FourthLevel::timeCallback), 1.0f);
}

void FourthLevel::timeCallback(float dt)
{
	time -= dt;

	CCSequence *s = CCSequence::create(CCFadeIn::create(0.5f), CCMoveBy::create(3.0f, ccp(0, 250)), CCFadeOut::create(0.5f), CCCallFuncN::create((CCObject*)this, callfuncN_selector(FourthLevel::removePicture)), NULL);

	CCSprite *sprite = NULL;
	switch (pic[(int)time])
	{
	case 0:
		sprite = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/apple.png"));
		break;
	case 1:
		sprite = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/banana.png"));
		break;
	case 2:
		sprite = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/cherry.png"));
		break;
	case 3:
		sprite = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/peach.png"));
		break;
	case 4:
		sprite = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/pear.png"));
		break;
	case 5:
		sprite = CCSprite::createWithTexture(IMAGEPOOL->textureForKey("/pic/pineapple.png"));
		break;
	default:
		break;
	}

	sprite->setPosition(ccp(winSize.width / 2 + pic[(int)time] * 20, 30));
	this->addChild(sprite, 1);
	sprite->runAction(s);
}

void FourthLevel::removePicture(CCNode *node)
{
	this->removeChild(node);
	if (time < 1)
	{
		this->unschedule(schedule_selector(FourthLevel::timeCallback));
		setEditBox();
	}
}


void FourthLevel::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}


bool FourthLevel::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	CCPoint p = touch->getLocation();
	if (!isRemoved && (p.x > 218 && p.x < 250) && (p.y > 30 && p.y < 59))
	{
		return true;
	}
	int re = contains(p);
	if (isOver && re != -1)
	{
		return true;
	}
	if (isDone && p.x > 129 && p.x < 172 && p.y > 101 && p.y < 132)
	{
		return true;
	}
	return false;
}


void FourthLevel::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCPoint p = touch->getLocation();
	if (!isRemoved && (p.x > 218 && p.x < 250) && (p.y > 30 && p.y < 59))
	{
		CCFadeOut *fadeOut = CCFadeOut::create(1.0f);
		rule_img->runAction(CCSequence::create(fadeOut, NULL));
		forward_button->runAction(CCSequence::create((CCFadeOut*)fadeOut->copy()->autorelease(), CCCallFunc::create(this, callfunc_selector(FourthLevel::display)), NULL));
	}

	int re = contains(p);
	if (isOver && re != -1)
	{

		isOver = false;
		isDone = true;
		CCDictionary *dict = CCDictionary::createWithContentsOfFile("/word/words.xml");
		const char *win_word = ((CCString*)dict->objectForKey("win"))->m_sString.c_str();
		const char *lose_word = ((CCString*)dict->objectForKey("lose"))->m_sString.c_str();
		if (re == 1)
		{
			int level = userDefault->getIntegerForKey("level");
			if (level == 3)
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
		}
		else
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
		}
	}


	if (isDone && p.x > 129 && p.x < 172 && p.y > 101 && p.y < 132)
	{
		CCDirector::sharedDirector()->replaceScene(SelectLevel::scene());
	}
}