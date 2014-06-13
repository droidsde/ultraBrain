#ifndef __FOURTHLEVEL__H__
#define __FOURTHLEVEL__H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>
using namespace cocos2d;
using namespace std;
USING_NS_CC_EXT;

class FourthLevel : public CCLayer
{
public:
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(FourthLevel);

	virtual void registerWithTouchDispatcher();

	virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

	void initAnsAndQues();
	void setRandom();
	void setRule();
	void setResult();
	void setEditBox();

	void display();
	void timeCallback(float dt);
	void removePicture(CCNode *node);

	int contains(CCPoint p);

private:
	int ans[8];
	int pic[10];
	string ques[8];
	int key;
	int pos;

	CCSize winSize;
	float time;
	CCSprite *result;
	CCSprite *forward_button;
	CCSprite *rule_img;
	bool isRemoved;
	bool isDone;
	bool isOver;
	CCEditBox *editBox;
};

#endif