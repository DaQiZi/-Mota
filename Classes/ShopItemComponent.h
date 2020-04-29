#ifndef __SHOPITEMCOMPONENT_H_  
#define __SHOPITEMCOMPONENT_H_
#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include"ShopInfoEntity.h"
//class ShopInfoEntity;
class ShopItemComponent :public cocos2d::ui::Layout{
public:
	cocos2d::Sprite* img_icon;
	cocos2d::Sprite* img_cost;
	cocos2d::ui::Text* lb_name;
	cocos2d::ui::Text* lb_cost;
	cocos2d::ui::Button* btn_buy;
	cocos2d::Sprite* img_bg;
	ShopInfoEntity data;
public:
	void initData();
	void udpateData(const ShopInfoEntity& data);
	virtual bool init();
	CREATE_FUNC(ShopItemComponent);
};
#endif