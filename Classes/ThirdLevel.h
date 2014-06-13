#ifndef __THIRDLEVEL__H__
#define __THIRDLEVEL__H__

#include "cocos2d.h"
#include "cocos-ext.h"

#define MAX_SIZE 10

USING_NS_CC_EXT;
using namespace cocos2d;

class ThirdLevel : public CCLayer
{
public:
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(ThirdLevel);
	
	virtual void registerWithTouchDispatcher();

	virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

	void setEditBox();
	void setRandom();
	void display();
	void timeCallback(float dt);
	void removeNumber(CCNode* node);

	int contains(CCPoint p);

private:
	CCSize winSize;
	int number[MAX_SIZE];
	int sum;
	int pos;
	float time;
	CCSprite *result;
	CCSprite *forward_button;
	CCSprite *rule_img;
	bool isRemoved;
	bool isDone;
	bool isOver;
};

#endif