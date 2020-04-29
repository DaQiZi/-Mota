#include"HelpComponent.h"
#include"cocostudio/CocoStudio.h"
#include"Utils.h"
#include "Constant.h"
#include "Config.h"
using namespace cocos2d;
using namespace ui;
bool HelpComponent::init(){
	if (!Node::init())
	{
		return false;
	}
	Utils::getInstance()->addBackground(this,Vec2(0.0f,0.0f));
	Utils::getInstance()->addTouchSwallow(this);
	this->initData();
	return true;
}

void HelpComponent::initData(){
	auto rootnode = CSLoader::createNode(FILE_NAME::t_HelpCompoent_csb);
	rootnode->setPosition(LocationUtils::getInstance()->CENTER);
	this->addChild(rootnode);

	this->btn_close = (Button*)rootnode->getChildByName("btn_close");
	this->sl_view = (ScrollView*)rootnode->getChildByName("sl_view");
	this->lb_help = (Text*)sl_view->getChildByName("lb_help");

	Utils::getInstance()->addButtonListener(this->btn_close, [this]() {
		this->removeFromParent();
	});
	std::string content = Config::getInstance()->getChineseContent("allTip");
	this->lb_help->setString(content);

	this->sl_view->setInnerContainerSize(Size(550,1500));
	this->lb_help->setPosition(Vec2(0,1500));
	this->lb_help->setContentSize(Size(550, 1500));
}
