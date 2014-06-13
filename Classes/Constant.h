#ifndef __CONSTANT__H__
#define __CONSTANT__H__

#include "cocos2d.h"
#include <string>
#include <vector>
using namespace std;
using namespace cocos2d;

class Constant
{
private:
	Constant();
	~Constant();
	void setPicPath();
	void setFirstLevelPosition();
	void setAllLevels();
	void setLevelFiveToSevenPosition();


	
	static Constant* instance;
	vector<string> picPath;
	float firstLevelPos[2];
	vector<CCScene*> allLevels;



public:

	vector<CCPoint> level_five;
	vector<CCPoint> level_six;
	vector<CCPoint> level_seven;

	static Constant* getInstance();
	vector<string> getAllPicPath();
	float* getFirstLevelPosition();
	vector<CCScene*> getAllLevels();
	vector<CCPoint> getLevelFivePosition();
	vector<CCPoint> getLevelSixPosition();
	vector<CCPoint> getLevelSevenPosition();

	static bool isSetLevel;

	char* G2U(const char* gb2312);
};

#endif