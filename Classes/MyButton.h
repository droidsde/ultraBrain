#ifndef __MYSPRITE__H__
#define __MYSPRITE__H__

#include "cocos2d.h"
using namespace cocos2d;


class MyButton :public CCSprite, public CCTouchDelegate
{
private:
	CCScene *navigateTo;
	CCLayer *layer;


public:
	static MyButton*  createWithTexture(CCTexture2D *pTexture);
	void setNavigation(CCScene *navigateTo);
	void setLayer(CCLayer *l);

    CCRect getRect();
	bool containsTouchLocation(CCTouch *touch);
	    
    //添加触屏委托，重新此方法
    virtual void onEnter();
    //移除监听事件，防止内存溢出
    virtual void   onExit();

    
    //触屏响应重写这三个方法
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);//按下
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);//拖动
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);//松开;

};

#endif
