#include"HeroInfoView.h"
#include"cocostudio\CocoStudio.h"
#include"DataManager.h"
#include "Constant.h"
#include"cocos2d.h"
#include "JumpFloorComponent.h"
#include"MHurtComponent.h"
#include"Utils.h"
#include"MapUtil.h"
#include"TabComponent.h"

using namespace cocos2d;
void HeroInfoView::initData(){
	this->m_winSize = Director::getInstance()->getWinSize();
	auto rootNode = CSLoader::createNode(FILE_NAME::t_heroinfo_csb);
	this->addChild(rootNode);
	this->setContentSize(rootNode->getContentSize());
	m_btn_head =(Button*)rootNode->getChildByName("btn_head");
	m_lb_key0 = (TextAtlas*)rootNode->getChildByName("lb_key0");
	m_lb_key1 = (TextAtlas*)rootNode->getChildByName("lb_key1");
	m_lb_key2 = (TextAtlas*)rootNode->getChildByName("lb_key2");
	m_lb_attack = (TextAtlas*)rootNode->getChildByName("lb_attack");
	m_lb_defend = (TextAtlas*)rootNode->getChildByName("lb_defend");
	m_lb_money = (TextAtlas*)rootNode->getChildByName("lb_money1");
	m_lb_soul = (TextAtlas*)rootNode->getChildByName("lb_money2");
	m_lb_blood = (TextAtlas*)rootNode->getChildByName("lb_blood");
	m_load_blood = (LoadingBar*)rootNode->getChildByName("load_1");
	m_lb_blood->setString("18874489236");
	m_load_blood->setPercent(100);

	this->btn_selectFloor = (Button*)rootNode->getChildByName("btn_selectFloor");
	this->btn_selectFloor->addTouchEventListener([this](Ref* sedner, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED)
		{
			if (DataManager::getInstance()->getHeroIsFight())
			{
				return;
			}
			auto jumpComponent = JumpFloorComponent::create();
			jumpComponent->setPosition(LocationUtils::getInstance()->CENTER);
			Utils::getInstance()->getRootNode()->addChild(jumpComponent);
			_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::HERO_STOP_MOVE);
		}
	});
	this->btn_selectFloor->setPressedActionEnabled(true);


	this->btn_hurt = (Button*)rootNode->getChildByName("btn_hurt");
	Utils::getInstance()->addButtonListener(this->btn_hurt, [this]() {
		if (DataManager::getInstance()->getHeroIsFight())
		{
			return;
		}
		auto item = MHurtComponent::create();
		auto list = MapUtil::getInstance()->getMapMonsterList();
		item->updateComponent(list);
		item->setPosition(LocationUtils::getInstance()->CENTER);
		Utils::getInstance()->getRootNode()->addChild(item);
		_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::HERO_STOP_MOVE);
	});

	Utils::getInstance()->addButtonListener(this->m_btn_head, [this]() {
		if (DataManager::getInstance()->getHeroIsFight())
		{
			return false;
		}
		auto item = TabComponent::create();
		item->setPosition(Vec2::ZERO);
		Utils::getInstance()->getRootNode()->addChild(item);
		_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::HERO_STOP_MOVE);
	});
}
bool HeroInfoView::init(){
	if (!Node::init()){
		return false;
	}
	this->initData();
	this->initNotification();
	this->updateView();
	return true;
}

void HeroInfoView::updateView(Ref* sender){
	auto data = DataManager::getInstance();
	m_lb_key0->setString(StringUtils::format("%d", data->m_key0_num));
	m_lb_key1->setString(StringUtils::format("%d", data->m_key1_num));
	m_lb_key2->setString(StringUtils::format("%d", data->m_key2_num));
	m_lb_attack->setString(StringUtils::format("%d", data->m_attack));
	m_lb_defend->setString(StringUtils::format("%d", data->m_defend));
	m_lb_money->setString(StringUtils::format("%d", data->m_money1_num));
	m_lb_soul->setString(StringUtils::format("%d", data->m_money2_num));
	//todo计算血条的百分比。
	m_lb_blood->setString(StringUtils::format("%d", data->m_nowblood));
	this->changeProgress(0);
}
void HeroInfoView::changeProgress(int blood){
	auto data = DataManager::getInstance();
	data->m_nowblood -= blood;
	int &newblood = data->m_nowblood;
	if (newblood <= 0.0){
		newblood = 0;
		m_load_blood->setPercent(0);
	}
	else{
		m_load_blood->setPercent(newblood * 100 / data->m_sumblood);
	}
}


void HeroInfoView::initNotification(){

	auto customlistener = EventListenerCustom::create(NOTIFICATION_TYPE::HERO_INFO_VIEW_UPDATE, CC_CALLBACK_1(HeroInfoView::updateView, this));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(customlistener, this);
	//Director::getInstance()->
	//NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(HeroInfoView::updateView), NOTIFICATION_TYPE::HERO_BLOOD_UPDATE, nullptr);
}
