#ifndef __JUMPFLOORCOMPONENT_H_  
#define __JUMPFLOORCOMPONENT_H_
#include"cocos2d.h"
#include"ui/CocosGUI.h"
class JumpFloorComponent :public cocos2d::Node{
public:
	cocos2d::ui::PageView* pv_list;
	cocos2d::ui::Button* btn_close;
public:
	virtual bool init();
	void initData();
	void initPage();
	void initArrow();
	CREATE_FUNC(JumpFloorComponent);
	void showMap(int floor);
	cocos2d::Vec2 getBtnPosition(cocos2d::ui::Button* btn);
	//virtual ~JumpFloorComponent();
private:
	Node* lastClick;
	cocos2d::experimental::TMXTiledMap* map;
	cocos2d::ui::Layout* ly_map;
	cocos2d::Node* node_arrow;
};
#endif