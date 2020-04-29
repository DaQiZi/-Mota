#ifndef __MHURTCOMPONENT_H_  
#define __MHURTCOMPONENT_H_
#include "cocos2d.h"
#include"ui/CocosGUI.h"
class MHurtComponent :public cocos2d::Node{
private:
	cocos2d::ui::Button* btn_close;
	cocos2d::ui::ListView* lv_list;
	void initData();
	//std::vector<std::string> monsterIdList;
public:
	virtual bool init();
	CREATE_FUNC(MHurtComponent);
	void updateComponent(const std::vector<std::string> &list);
	
};
#endif