#include "MyButton.h"
#include "SelectLevelScene.h"
using namespace cocos2d;

MyButton*  MyButton::createWithTexture(CCTexture2D *pTexture)
{
	MyButton *pobSprite = new MyButton();
    if (pobSprite && pobSprite->initWithTexture(pTexture))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void MyButton::setNavigation(CCScene *navigateTo)
{
	this->navigateTo = navigateTo;
	this->navigateTo->retain();
}

void MyButton::setLayer(CCLayer *l)
{
	layer = l;
}

void MyButton::onEnter()
{
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
	CCSprite::onEnter();
}

void MyButton::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}

CCRect MyButton::getRect()
{
	CCSize size = getTexture()->getContentSize();
	return CCRectMake(-size.width / 2, -size.height / 2, size.width, size.height);
}


bool MyButton::containsTouchLocation(CCTouch *touch)
{
	CCRect rc = getRect();
	CCPoint p = convertTouchToNodeSpaceAR(touch);
	return rc.containsPoint(p);
}

bool MyButton::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	bool bRet = false;
	if (containsTouchLocation(touch))
	{
		bRet = true;
	}
	return bRet;

}



void MyButton::ccTouchMoved(CCTouch* touch, CCEvent* event)
{

}

void MyButton::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if (getTag() == 0)
	{
		if (containsTouchLocation(touch))
		{
			//CCAssert(navigateTo != SelectLevel::scene(), "not equal");
			CCDirector::sharedDirector()->replaceScene(navigateTo);
		}
	}
	else
	{
		//layer = (CCLayer*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
		//CCAssert(layer != NULL, "layer in MyButton is NULL");
		//CCSprite *rule = (CCSprite*)layer->getChildByTag(10);
		//MyButton *forward = (MyButton*)this;
		//CCFadeOut *fadeOut = CCFadeOut::create(1.0f);
		//rule->runAction(CCSequence::create(fadeOut, NULL));
		//forward->runAction(CCSequence::create((CCFadeOut*)fadeOut->copy()->autorelease(), CCCallFunc::create((CCObject*)layer, callfunc_selector(MyButton::fadeOutCallback)), NULL));
	}
}