
#ifndef __HELPCOMPONENT_H__
#define __HELPCOMPONENT_H__
#include"cocos2d.h"
#include"ui/CocosGUI.h"
using namespace cocos2d;
class HelpComponent : public cocos2d::Node{
public:
	CREATE_FUNC(HelpComponent);
	virtual bool init();
	void initData();
public:
	ui::Button* btn_close;
	ui::Text* lb_help;
	ui::ScrollView* sl_view;
};
#endif
		