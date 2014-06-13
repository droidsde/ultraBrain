#ifndef __SELECTLEVELSCENE__H__
#define __SELECTLEVELSCENE__H__

#include "cocos2d.h"
using namespace cocos2d;

class SelectLevel : public CCLayer
{
public:
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(SelectLevel);

	virtual void registerWithTouchDispatcher();

	virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

	void readData();
	void displayLevels();
	void displayScore();
	void update(float delta);

private:
	int level;
	int score;
	CCSize winSize;
};

#endif