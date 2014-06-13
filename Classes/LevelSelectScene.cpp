#include "LevelSelectScene.h"
#include "HelloWorldScene.h"
#include "GameManager.h"
#include "LoadingScene.h"
Scene* LevelSelectScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LevelSelectScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LevelSelectScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
	center = Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2);

	FileUtils::getInstance()->addSearchPath("level");
	
	addBackgroud();
	
	initMenu();
    return true;
}

LevelSelectScene::~LevelSelectScene()
{

}
LevelSelectScene::LevelSelectScene()
{
}





void LevelSelectScene::addBackgroud()
{
	Sprite* bg = Sprite::create("background.png");
	bg->setPosition(center);
	this->addChild(bg);

}

void LevelSelectScene::backCallBack( Ref* pSender )
{
	CCScene* hello = HelloWorld::createScene();
	Director::getInstance()->replaceScene(hello);
}


void LevelSelectScene::initMenu()
{
	initMenuPosition();
	MenuItemSprite* item[5];
	for(int i = 0; i < 5; i++)
	{
		char normal[50];
		char select[50];
		sprintf_s(normal,"level_%d.png",i+1);
		sprintf_s(select,"level_selected_%d.png",i+1);
		item[i] = createMenuItemSprite(normal,select,CC_CALLBACK_1(LevelSelectScene::menuCallBack,this));
		item[i]->setTag(i+1);
		item[i]->setPosition(pos[i]);
	}
	Menu* menu = Menu::create(item[0],item[1],item[2],item[3],item[4],nullptr);
	menu->setPosition(Point(0,0));
	this->addChild(menu);
}

void LevelSelectScene::menuCallBack( Ref* pSender )
{
	int level = ((MenuItemSprite*)pSender)->getTag();
	GameManager::getInstance()->setCurrentLevel(level);
	if(GameManager::getInstance()->curLevel == 3 || GameManager::getInstance()->curLevel == 4)
	{
		Sprite* max = Sprite::create("underconstruct.png");
		this->addChild(max);
		max->setPosition(Point(center.x,center.y-300));
		max->runAction(Sequence::create(
			DelayTime::create(0.5f),
			FadeOut::create(2.0f),
			CallFunc::create(max,callfunc_selector(Sprite::removeFromParent)),
			NULL));
	}
	else
	{
		Scene* gs = LoadingScene::createScene();
		Director::getInstance()->replaceScene(gs);
	}
}

MenuItemSprite* LevelSelectScene::createMenuItemSprite( const char* normal, const char* select, const ccMenuCallback &callBack )
{
	Sprite* nor = Sprite::create(normal);
	Sprite* sel = Sprite::create(select);	
	MenuItemSprite* ret = MenuItemSprite::create(nor,sel,NULL,callBack);
	nor->setAnchorPoint(Point(0.5f,0.5f));
	sel->setAnchorPoint(Point(0.5f,0.5f));
	nor->setPosition(nor ->getContentSize().width/2,nor ->getContentSize().height/2);
	sel->setPosition(nor ->getContentSize().width/2,nor ->getContentSize().height/2);
	return ret;
}

void LevelSelectScene::initMenuPosition()
{
	float padding = 20;
	center.y -= 20;
	Sprite* little = Sprite::create("level_1.png");
	Sprite* large = Sprite::create("level_5.png");
	Size littleSize = little->getContentSize();
	Size largeSize = large->getContentSize();
	pos[1] = Point(center.x, center.y + littleSize.height/2+padding/2);
	pos[3] = Point(center.x, center.y - littleSize.height/2-padding/2);
	pos[0] = Point(center.x - littleSize.width - padding, center.y + littleSize.height/2+padding/2);
	pos[2] = Point(center.x - littleSize.width - padding, center.y - littleSize.height/2-padding/2);
	pos[4] = Point(center.x + littleSize.width/2+largeSize.width/2+padding,center.y);
	center.y += 20;
}
