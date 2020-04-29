#ifndef __SHOPCOMPONENT_H_  
#define __SHOPCOMPONENT_H_
#include"cocos2d.h"
#include"ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;

class ShopEntity;
class ShopComponent : public cocos2d::Node{
public:
	ui::Text* lb_name;
	ui::Text* lb_desc;
	ui::Button* btn_close;
	ui::ImageView* img_head;
	ui::ListView* lv_list;
	cocos2d::ui::Layout* content;
	
public:
	void updateData(const ShopEntity& entity);
	void initData();
	virtual bool init();
	CREATE_FUNC(ShopComponent);
	void initAnima();
	void removeSelf();

};
#endif