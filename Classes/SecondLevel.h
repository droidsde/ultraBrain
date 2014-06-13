#ifndef __SECONDELEVEL__H__
#define __SECONDELEVEL__H__

#include "cocos2d.h"
using namespace cocos2d;

class SecondLevel : public CCLayer
{
public:
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(SecondLevel);

	virtual void registerWithTouchDispatcher();

	virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);


	void fadeOutCallback();
	void fadeInCallback();
	void twoSecondsCallback(float dt);
	void tenSecondsCallback(float dt);

private:
	CCSprite *forward_button;
	CCSprite *rule_img;
	CCSprite *key_img;
	CCSprite *candidatite_img;
	CCSprite *result;
	bool isRemoved;
	bool isDone;
	float time;
};

#endif