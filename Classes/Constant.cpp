#include "Constant.h"
#include "FirstLevel.h"
#include "SecondLevel.h"
#include "ThirdLevel.h"
#include "FourthLevel.h"
#include "FifthLevel.h"
#include "SixthLevel.h"
#include "SeventhLevel.h"
#include <iostream>
#define xPosition firstLevelPos[0]
#define yPosition firstLevelPos[1]

using namespace std;


Constant* Constant::instance = NULL;
bool Constant::isSetLevel = false;

Constant::Constant()
{
	setPicPath();
	setFirstLevelPosition();
	setLevelFiveToSevenPosition();
}


Constant::~Constant()
{
}

Constant* Constant::getInstance()
{
	if (instance == NULL)
		instance = new Constant();
	return instance;
}




void Constant::setPicPath()
{
	picPath.push_back("/pic/back.png");
	picPath.push_back("/pic/forward.png");
	picPath.push_back("/pic/restart.png");
	picPath.push_back("/pic/level.png");
	picPath.push_back("/pic/numbers.png");
	picPath.push_back("/pic/result.png");
	picPath.push_back("/pic/background.png");
	picPath.push_back("/pic/level_background.png");

	picPath.push_back("/pic/level1.png");
	picPath.push_back("/pic/level2.png");
	picPath.push_back("/pic/level3.png");
	picPath.push_back("/pic/level4.png");
	picPath.push_back("/pic/level5.png");
	picPath.push_back("/pic/level6.png");
	picPath.push_back("/pic/level7.png");
	picPath.push_back("/pic/level8.png");
	picPath.push_back("/pic/level9.png");
	picPath.push_back("/pic/level10.png");

	picPath.push_back("/pic/level1_key_face.png");
	picPath.push_back("/pic/level1_condaditate_faces.png");

	picPath.push_back("/pic/level2_key_face.png");
	picPath.push_back("/pic/level2_condaditate_faces.png");

	picPath.push_back("/pic/apple.png");
	picPath.push_back("/pic/banana.png");
	picPath.push_back("/pic/cherry.png");
	picPath.push_back("/pic/peach.png");
	picPath.push_back("/pic/pear.png");
	picPath.push_back("/pic/pineapple.png");

	picPath.push_back("/pic/tian_level5.png");

	picPath.push_back("/pic/tian_level6.png");

	picPath.push_back("/pic/tian_level7.png");
}

void Constant::setAllLevels()
{
	if (!allLevels.empty())
		allLevels.clear();
	CCScene *scene = FirstLevel::scene();
	scene->retain();
	allLevels.push_back(scene);

	scene = SecondLevel::scene();
	scene->retain();
	allLevels.push_back(scene);

	scene = ThirdLevel::scene();
	scene->retain();
	allLevels.push_back(scene);

	scene = FourthLevel::scene();
	scene->retain();
	allLevels.push_back(scene);

	scene = FifthLevel::scene();
	scene->retain();
	allLevels.push_back(scene);

	scene = SixthLevel::scene();
	scene->retain();
	allLevels.push_back(scene);

	scene = SeventhLevel::scene();
	scene->retain();
	allLevels.push_back(scene);
}

void Constant::setFirstLevelPosition()
{
	xPosition = 120.0;
	yPosition = 215.0;
}

void Constant::setLevelFiveToSevenPosition()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int i, j;
	for (i = -2; i <= 2; i++)
	{
		for (j = 0; j <= 1; j++)
		{
			level_five.push_back(ccp(winSize.width / 2 + i * 70, winSize.height / 2 + 35 - 70 * j));
		}

		for (j = 0; j <= 3; j++)
		{
			level_six.push_back(ccp(winSize.width / 2 + i * 50, winSize.height / 2 + 75 - 50 * j));
		}

		for (j = 0; j <= 5; j++)
		{
			level_seven.push_back(ccp(winSize.width / 2 + i * 25, winSize.height / 2 + 62.5 - j * 25));
		}
	}
}



vector<string> Constant::getAllPicPath()
{
	return picPath;
}

float* Constant::getFirstLevelPosition()
{
	return firstLevelPos;
}

vector<CCScene*> Constant::getAllLevels()
{
	if (!isSetLevel)
	{
		setAllLevels();
		isSetLevel = true;
	}
	return allLevels;
}

vector<CCPoint> Constant::getLevelFivePosition()
{
	return level_five;
}

vector<CCPoint> Constant::getLevelSixPosition()
{
	return level_six;
}

vector<CCPoint> Constant::getLevelSevenPosition()
{
	return level_seven;
}


char* Constant::G2U(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}