#include "EighthLevel.h"



CCScene* EighthLevel::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	EighthLevel *layer = EighthLevel::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool EighthLevel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	return true;
}