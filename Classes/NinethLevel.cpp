#include "NinethLevel.h"



CCScene* NinethLevel::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	NinethLevel *layer = NinethLevel::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool NinethLevel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	return true;
}