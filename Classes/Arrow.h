#ifndef __ARROW_H__
#define __ARROW_H__
#include"cocos2d.h"
using namespace cocos2d;
class Arrow :public cocos2d::Node{
public:
	CREATE_FUNC(Arrow);
	virtual bool init();
	void initData();
};
#endif
		