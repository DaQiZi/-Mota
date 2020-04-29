
#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__
#include"cocos2d.h"
#include"ui/CocosGUI.h"
using namespace cocos2d;
class MainScene : public cocos2d::Layer{
public:
	static Scene* createScene();
	CREATE_FUNC(MainScene);
	virtual bool init();
	void initData();
	void initNotification();
private:
	cocos2d::ui::Button* btn_begin;
	cocos2d::ui::Button* btn_continue;
	cocos2d::ui::Button* btn_exit;
	cocos2d::ui::Button* btn_help;
};
#endif
		