#include"ShopComponent.h"
#include"cocostudio/CocoStudio.h"
#include"Constant.h"
#include"ShopEntity.h"
#include"ShopItemComponent.h"
#include"ShopInfoEntity.h"
#include"Utils.h"
#include"DataManager.h"
//#include"JumpFloorComponent.h"
bool ShopComponent::init()
{
	if (!Node::init())
	{
		return false;
	}
	_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::MOVE_TOUCH_LISTENER, (void*)true);
	Utils::getInstance()->addBackground(this);
	Utils::getInstance()->addTouchSwallow(this);
	this->initData();
	this->initAnima();
	return true;
}

void ShopComponent::initAnima()
{
	this->setScale(0.0f);
	this->runAction(ScaleTo::create(0.2f, 1.0f));
}

void ShopComponent::removeSelf()
{
	this->runAction(Sequence::create(
		ScaleTo::create(0.1f, 0.0f), CallFunc::create([this]() {
		_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::MOVE_TOUCH_LISTENER, (void*)false);
		this->removeFromParent();
	}), nullptr));
}

void ShopComponent::updateData(const ShopEntity& entity)
{
	this->lb_desc->setString(entity.desc);
	this->lb_name->setString(entity.name);
	auto& arr = entity.shoplistArr;
	//auto filename = FileUtils::getInstance()->path
	this->img_head->loadTexture("head/"+entity.icon);
	for (const auto& item : arr)
	{
		auto shopitem = ShopItemComponent::create();

		auto shopinfo = Config::getInstance()->getShopInfoEntityById(item);

		shopitem->udpateData(shopinfo);
		this->lv_list->pushBackCustomItem(shopitem);
	}

	//for (int i = 1;i <= 3;i++)
	//{
	//	/*auto item = ImageView::create("res\\UI_buy_title.png");
	//	item->setAnchorPoint(Vec2::ZERO);
	//	auto layout = Layout::create();
	//	layout->setContentSize(item->getContentSize());
	//	layout->addChild(item);*/
	//	auto item = ShopItemComponent::create();


	//	this->lv_list->pushBackCustomItem(item);
	//	//log("item position  %f  %f", item->getPositionX(), item->getPositionY());
	//}
}

void ShopComponent::initData()
{
	auto rootNode = CSLoader::createNode(FILE_NAME::t_shopComponent_csb);
	this->addChild(rootNode);

	//init
	this->lb_desc = (Text*)rootNode->getChildByName("lb_desc");
	this->lb_name = (Text*)rootNode->getChildByName("lb_name");
	this->img_head = (ImageView*)rootNode->getChildByName("img_head");
	this->btn_close = (Button*)rootNode->getChildByName("btn_close");
	
	this->lv_list = (ListView*)rootNode->getChildByName("lv_list");
	this->lv_list->setScrollBarEnabled(false);
	//this->content = (Layout*)lv_list->getChildByName("content");
	//this->lb_name = (Text*)rootNode->getChildByName("lb_name");
	this->btn_close->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(NOTIFICATION_TYPE::TARGET_NODE_CHANGE);
			this->removeSelf();
		}
	});
	this->btn_close->setPressedActionEnabled(true);
	//ActionManager::getin
	this->img_head->loadTexture("head/head_0.png");


	//this->img_head->setContentSize(TextureCache::getInstance()->addImage(FILE_NAME::tou__name3_png)->getContentSize());

	//this->lv_list->setLayoutType(Layout::Type::VERTICAL);
	//this->lv_list->setPosition(Vec2(0.5f,0.5f));
	
}
