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
	    
    //��Ӵ���ί�У����´˷���
    virtual void onEnter();
    //�Ƴ������¼�����ֹ�ڴ����
    virtual void   onExit();

    
    //������Ӧ��д����������
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);//����
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);//�϶�
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);//�ɿ�;

};

#endif
