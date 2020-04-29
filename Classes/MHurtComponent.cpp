#include"MHurtComponent.h"
#include"cocostudio/CocoStudio.h"
#include"Constant.h"
#include"Config.h"
#include"MHurtItemComponent.h"
#include"Utils.h"
#include"Monster.h"
using namespace cocos2d;
using namespace ui;
void MHurtComponent::initData()
{
	auto rootnode = CSLoader::createNode(FILE_NAME::t_MHurtComponent_csb);
	this->addChild(rootnode);

	this->btn_close = (Button*)rootnode->getChildByName("btn_close");
	this->btn_close->addTouchEventListener([this](Ref* sender,Widget::TouchEventType type) {
		if (type==Widget::TouchEventType::ENDED)
		{
			this->removeFromParent();
		}
	});
	this->btn_close->setPressedActionEnabled(true);
	this->lv_list = (ListView*)rootnode->getChildByName("lv_list");
	/*for (int i = 0;i<8;i++)
	{
		auto item = MHurtItemComponent::create();
		this->lv_list->pushBackCustomItem(item);
	}*/
}

bool MHurtComponent::init()
{
	if (!Node::init())
	{
		return false;
	}
	Utils::getInstance()->addBackground(this);
	Utils::getInstance()->addTouchSwallow(this);
	this->initData();
	return true;
}

void MHurtComponent::updateComponent(const std::vector<std::string> &list)
{
	//this->monsterIdList = list; 
	for (const auto &id : list)
	{
		auto item = Config::getInstance()->getMonsterById(id);
		auto uiItem = MHurtItemComponent::create();
		uiItem->updateItem(item);
		this->lv_list->pushBackCustomItem(uiItem);
	}
}
