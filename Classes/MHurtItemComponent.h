#ifndef __MHURTITEMCOMPONENT_H_  
#define __MHURTITEMCOMPONENT_H_
#include"cocos2d.h"
#include"ui/CocosGUI.h"

using namespace cocos2d;

class Monster;
class MHurtItemComponent :public cocos2d::ui::Widget{

public:
	//cocos2d::Sprite* img_head;
	cocos2d::Sprite* img_dead;
	cocos2d::ui::Text* lb_name;
	cocos2d::ui::Text* lb_soul;
	cocos2d::ui::Text* lb_gold;
	cocos2d::ui::Text* lb_attack;
	cocos2d::ui::Text* lb_defend;
	cocos2d::ui::Text* lb_blood;

	cocos2d::ui::TextAtlas* lb_hurt;
	cocos2d::ui::Layout* ly_head;
	cocos2d::ui::Layout* ly_bg;
public:
	virtual bool init();
	void initData();
	void updateItem(const Monster& entity);
	CREATE_FUNC(MHurtItemComponent);
};
#endif