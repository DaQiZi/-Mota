#ifndef __HERO_INFO_H_
#define __HERO_INFO_H_
#include"cocos2d.h"
#include"ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
class HeroInfoView:public Node{
public:
	//static HeroInfo create();
	CREATE_FUNC(HeroInfoView);
	virtual bool init();
	Button* m_btn_head;
	TextAtlas* m_lb_key0;
	TextAtlas* m_lb_key1;
	TextAtlas* m_lb_key2;
	TextAtlas* m_lb_blood;
	TextAtlas* m_lb_attack;
	TextAtlas* m_lb_defend;
	TextAtlas* m_lb_money;
	TextAtlas* m_lb_soul;
	LoadingBar* m_load_blood;
	ui::Button* btn_selectFloor;
	cocos2d::ui::Button* btn_hurt;
	void initData();
	void updateView(Ref* sender=nullptr);
	void changeProgress(int blood);
	void initNotification();
private:
	Size m_winSize;
};
#endif