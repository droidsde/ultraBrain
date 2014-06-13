#ifndef __LEVELSELECT_SCENE__
#define __LEVELSELECT_SCENE__

#include "cocos2d.h"
USING_NS_CC;
class LevelSelectScene : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

	~LevelSelectScene();
	LevelSelectScene();
    
    virtual bool init();  
    
    
    
	void backCallBack( Ref* pSender );
	void menuCallBack( Ref* pSender );

    // implement the "static create()" method manually
    CREATE_FUNC(LevelSelectScene);

	
	
	Size visibleSize;
	Point origin;
	Point center;

	Point pos[5];
	void initMenuPosition();
	void initMenu();
	void addBackgroud();

	MenuItemSprite* createMenuItemSprite(const char* normal, const char* select, const ccMenuCallback &callBack);
};

#endif // __LEVELSELECT_SCENE__
