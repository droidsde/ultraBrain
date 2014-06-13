#ifndef __HELLOWORLDSCENE__H__
#define __HELLOWORLDSCENE__H__


#include "cocos2d.h"
using namespace cocos2d;

class HelloWorld : public CCLayer
{
public:
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(HelloWorld);

	void HelloWorld::update(float delta);

	void HelloWorld::callback(CCObject *object);

	void HelloWorld::menuCloseCallback(CCObject* pSender);

private:
	CCSize winSize;
	int current;
	int amount;
	
	
};



#endif
