#ifndef __UTILS_H_  
#define __UTILS_H_
#include "cocos2d.h"
#include"ui/CocosGUI.h"
USING_NS_CC;
class Utils {
public:
	static Utils* getInstance();
	void addTouchSwallow(Node* node);
	void addTipsDialog(Node* node,std::string content,std::function<void()> callback=nullptr);
	void addTwoButtonDialog(Node* node,std::string content,std::function<void()> callback,std::function<void()> no_cb=nullptr);
	void addBackground(Node* node,Vec2 anchor = Vec2(0.5f,0.5f));
	void addButtonListener(ui::Button* btn,std::function<void()> callback);
	Node* getRootNode();
	void setRootNode(Node* node);
	std::string getcurrTime();
	void setButtonDisable(cocos2d::ui::Button* btn);
	//void quickSendNotification(std::string noticeName);
	void addTipsLabel(std::string content);
public:
	Node* rootnode;
};

class LocationUtils {
public:
	LocationUtils();
	static LocationUtils* getInstance();
public:
	cocos2d::Size WIN_SIZE;
	cocos2d::Vec2 CENTER;
};

#endif