#ifndef __FIRSTLEVEL__H__
#define __FIRSTLEVEL__H__

#include "cocos2d.h"
#include "MyButton.h"
using namespace cocos2d;

class FirstLevel : public CCLayer
{
public:
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(FirstLevel);

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