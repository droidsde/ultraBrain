#include "TenthLevel.h"



CCScene* TenthLevel::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	TenthLevel *layer = TenthLevel::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool TenthLevel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	return true;
}