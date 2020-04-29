#ifndef __COMMONDIALOGCOMPONENT_H_  
#define __COMMONDIALOGCOMPONENT_H_
#include"cocos2d.h"
#include"ui\CocosGUI.h"
using namespace cocos2d;
using namespace ui;
class CommonDialogComponent:public Node{
public:
	Text* m_text_tips;
	Text* m_text_content;
	Button* m_btn_no;
	Button* m_btn_yes;
	CREATE_FUNC(CommonDialogComponent);
	virtual bool init();
	void setYesCallBack(std::function<void()>);
	void setCancelCallBack(std::function<void()> func=nullptr);
	void setStyle(int style,std::string other = "");
	void setContentString(std::string other="");
public:
	void initData();
private:
	void initAnima();
	void removeSelf();
	Size m_winSize;
	std::function<void()> m_yes_callback;
	std::function<void()> m_no_callback;
	Node* rootnode;
};
#endif