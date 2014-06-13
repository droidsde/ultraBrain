#ifndef __TENTHLEVEL__H__
#define __TENTHLEVEL__H__

#include "cocos2d.h"
using namespace cocos2d;

class TenthLevel : public CCLayer
{
public:
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(TenthLevel);
};

#endif