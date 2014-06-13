#ifndef __SEVENTHLEVEL__H__
#define __SEVENTHLEVEL__H__

#include "cocos2d.h"
using namespace cocos2d;

class SeventhLevel : public CCLayer
{
public:
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(SeventhLevel);

	virtual void registerWithTouchDispatcher();

	virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);


	void setRule();
	void display();

private:
	CCSize winSize;
	int size;
	CCSprite *forward_button;
	CCSprite *rule_img;
	bool isRemoved;
	float time;
	bool isDone;
	CCSprite *result;

	int key;

	int isContain(CCPoint p);
	void setResult();
	void timeCallback(float dt);
};

#endif