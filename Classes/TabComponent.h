#ifndef __TABCOMPONENT_H_  
#define __TABCOMPONENT_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"Monster.h"
class SaveItem;
class BookItem;
class SetItem;
class TabComponent :public cocos2d::Node{
public:
	cocos2d::ui::Layout* ly_bg;
	cocos2d::ui::Layout* ly_set;
	cocos2d::ui::Layout* ly_save;
	cocos2d::ui::Layout* ly_book;
	cocos2d::ui::Button* btn_set;
	cocos2d::ui::Button* btn_save;
	cocos2d::ui::Button* btn_book;
	cocos2d::ui::Button* btn_close;

	
	SaveItem* save_layout;
	BookItem* book_layout;
	SetItem* set_layout;
public:
	virtual bool init();
	void initData();
	void initButton();
	void moveAllLayout();
	void updateSave();
	void updateSet();
	void updateBook();
	//void initBackgournd();
	CREATE_FUNC(TabComponent);
};

class SaveItem : public cocos2d::Node{
public:
	cocos2d::ui::Text* lb_time;
	cocos2d::ui::Text* lb_blood;
	cocos2d::ui::Text* lb_soul;
	cocos2d::ui::Text* lb_attack;
	cocos2d::ui::Text* lb_floor;
	cocos2d::ui::Text* lb_defend;
	cocos2d::ui::Text* lb_tips;
	cocos2d::ui::Text* lb_gold;
	cocos2d::ui::Text* lb_key_red;
	cocos2d::ui::Text* lb_key_yellow;
	cocos2d::ui::Text* lb_key_blue;
	cocos2d::Node* node_hero;
	cocos2d::ui::Button* btn_save;
	cocos2d::ui::Button* btn_read;
	
	cocos2d::ui::Layout* ly_base;
public:
	void updateItem(cocos2d::ui::Layout* parent);
	CREATE_FUNC(SaveItem);
	virtual bool init();
	void setAllVisible(bool flag);
	void showAllInfo();
};

class BookItem : public cocos2d::Node {
private:
	cocos2d::ui::ListView* lv_list;
public:
	CREATE_FUNC(BookItem);
	virtual bool init();
	void initData();
	void updateItem(cocos2d::ui::Layout* parent);
};
class Monster;
class BookItemComponent :public cocos2d::ui::Widget {
public:
	CREATE_FUNC(BookItemComponent);
	virtual bool init();
	void initData();
	void updateData(const Monster& monster);
public:
	cocos2d::ui::Layout* ly_head;
	cocos2d::ui::Text* lb_name;
	cocos2d::ui::Text* lb_desc;
};

class SetItem :public cocos2d::Node {
public:
	cocos2d::ui::Button* btn_reset;
	cocos2d::ui::Button* btn_music;
	cocos2d::ui::Button* btn_effect;
	cocos2d::ui::Slider* sl_music;
	cocos2d::ui::Slider* sl_effect;
	cocos2d::ui::Button* btn_back;
public:
	CREATE_FUNC(SetItem);
	virtual bool init();
	void initData();
	void updateData(cocos2d::ui::Layout* parent);
};
#endif