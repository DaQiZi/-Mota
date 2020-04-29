#include"ShopItemComponent.h"
#include"cocostudio/CocoStudio.h"
#include"Constant.h"
#include"ShopInfoEntity.h"
#include"DataManager.h"
#include"Utils.h"
using namespace cocos2d;
using namespace ui;
void ShopItemComponent::initData()
{

	auto rootnode = CSLoader::createNode(FILE_NAME::t_shopItemComponent_csb);
	//rootnode->setAnchorPoint(Vec2::ZERO);
	/*auto node = (Node*)rootnode->getChildByName("Node");;
	node->setAnchorPoint(Vec2::ZERO);*/
	this->lb_cost = (Text*)rootnode->getChildByName("lb_cost");
	this->lb_name = (Text*)rootnode->getChildByName("lb_name");
	this->img_cost = (Sprite*)rootnode->getChildByName("img_cost");
	this->img_icon = (Sprite*)rootnode->getChildByName("img_icon");
	this->btn_buy = (Button*)rootnode->getChildByName("btn_buy");
	this->img_bg = (Sprite*)rootnode->getChildByName("img_bg");

	//auto size = rootnode->getContentSize();
	rootnode->setContentSize(img_bg->getContentSize());
	//rootnode->setAnchorPoint(this->img_bg->getAnchorPoint());
	this->setContentSize(rootnode->getContentSize());
	//this->setContentSize(rootnode->getContentSize());
	//size = this->getContentSize();
	this->btn_buy->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(NOTIFICATION_TYPE::TARGET_NODE_CHANGE);
			//this->removeSelf();

			auto valuemap = FileUtils::getInstance()->getValueMapFromFile(FILE_NAME::t_chinese_xml);
			if (data.costType == SHOP_CONST_TYPE::GOLE)
			{
				int money = DataManager::getInstance()->m_money1_num;
				if ((money + data.cost) <= 0)
				{
					std::string str = StringUtils::format(valuemap["tips"].asString().c_str(),valuemap["gold"].asString().c_str());
					Utils::getInstance()->addTipsDialog(Utils::getInstance()->getRootNode(),str);
					return;
				}
			}
			else {
				int money = DataManager::getInstance()->m_money2_num;
				if ((money + data.cost) <= 0)
				{
					std::string str = StringUtils::format(valuemap["tips"].asString().c_str(), valuemap["soul"].asString().c_str());
					Utils::getInstance()->addTipsDialog(Utils::getInstance()->getRootNode(), str);
					return;
				}
			}
			std::string content = Config::getInstance()->getChineseContent("buy");
			Utils::getInstance()->addTipsLabel(content);
			DataManager::getInstance()->handleShopCost(this->data.costType,this->data.cost,this->data.shopinfoArr);
		}
	});
	this->btn_buy->setPressedActionEnabled(true);
	this->addChild(rootnode);
	//this->addChild(img);
}

void ShopItemComponent::udpateData(const ShopInfoEntity& data)
{
	this->data = data;
	auto str = StringUtils::format("x%d", -data.cost);
	this->lb_cost->setString(str);
	this->lb_name->setString(data.desc);
	this->img_icon->setTexture(TextureCache::getInstance()->addImage(data.icon));
	Texture2D* img = nullptr;
	if (data.costType==SHOP_CONST_TYPE::GOLE)
	{
		img = TextureCache::getInstance()->addImage("res/ui_jb.png");
	}
	else {
		img = TextureCache::getInstance()->addImage("res/ui_hun.png");
	}
	this->img_cost->setTexture(img);
	//todo

	//this->
}

bool ShopItemComponent::init()
{
	if (!Layout::init())
	{
		return false;
	}
	this->initData();

	return true;

}
