#include"CommonDialogComponent.h"
#include"cocostudio/CocoStudio.h"
#include"Constant.h"
#include "Utils.h"
#include "DataManager.h"
bool CommonDialogComponent::init(){
	if (!Node::init())
	{
		return false;
	}
	Utils::getInstance()->addTouchSwallow(this);
	//DataManager::getInstance()->setIsCanTouch(false);
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(NOTIFICATION_TYPE::MOVE_TOUCH_LISTENER, (void*)true);
	this->m_winSize = Director::getInstance()->getWinSize();
	Utils::getInstance()->addBackground(this);
	this->initData();
	this->initAnima(); 
	return true;
}

void CommonDialogComponent::initData(){
	this->m_yes_callback = nullptr;
	this->rootnode = CSLoader::createNode(FILE_NAME::t_commonDialogComponent_csb);
	this->addChild(rootnode);
	this->m_btn_no = (Button*)rootnode->getChildByName("btn_no");
	this->m_btn_yes = (Button*)rootnode->getChildByName("btn_yes");
	this->m_text_tips = (Text*)rootnode->getChildByName("text_tips");
	this->m_text_content = (Text*)rootnode->getChildByName("text_content");

	this->m_btn_no->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (this->m_no_callback)
			{
				this->m_no_callback();
			}
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(NOTIFICATION_TYPE::MOVE_TOUCH_LISTENER, (void*)false);
			//DataManager::getInstance()->setIsCanTouch(true);
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(NOTIFICATION_TYPE::TARGET_NODE_CHANGE);
			this->removeSelf();
		}
	});

	this->m_btn_yes->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (this->m_yes_callback)
			{
				this->m_yes_callback();
				
			}
			//DataManager::getInstance()->setIsCanTouch(true);
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(NOTIFICATION_TYPE::MOVE_TOUCH_LISTENER, (void*)false);
			//this->removeFromParent();
			this->removeSelf();
		}
	});

	//auto listener = EventListenerTouchOneByOne::create();
	//listener->onTouchBegan = [](Ref* sender,Event* eve){
	//	return true;
	//};
	//listener->setSwallowTouches(true);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void CommonDialogComponent::initAnima()
{
	this->rootnode->setScale(0.0f);
	this->rootnode->runAction(ScaleTo::create(0.2f,1.0f));
}

void CommonDialogComponent::removeSelf()
{
	this->rootnode->runAction(Sequence::create(
		ScaleTo::create(0.1f, 0.0f), CallFunc::create([this]() {
		this->removeFromParent();
	}),nullptr));
}

void CommonDialogComponent::setYesCallBack(std::function<void()> callback=nullptr){
	this->m_yes_callback = callback;
}

void CommonDialogComponent::setCancelCallBack(std::function<void()> func)
{
	this->m_no_callback = func;
}

void CommonDialogComponent::setStyle(int style, std::string other)
{
	auto valuemap = FileUtils::getInstance()->getValueMapFromFile(FILE_NAME::t_chinese_xml);
	if (style==DIALOG_STYLE::TIPS)
	{
		this->m_btn_no->setVisible(false);
		this->m_btn_yes->setPositionX(0.0f);
		this->m_text_tips->setString(valuemap["tip"].asString());
		//std::string newstr = StringUtils::format(valuemap["tips"].asString().c_str(),other.c_str());*/
		this->m_text_content->setText(other);
	}
	/*else if (style==DIALOG_STYLE::LOST_TIPS)
	{
		this->m_btn_no->setVisible(false);
		this->m_btn_yes->setPositionX(0.0f);
		this->m_text_tips->setString(valuemap["tip"].asString());
		std::string newstr = valuemap["lost"].asString();
		this->m_text_content->setText(newstr);
	}*/
}

void CommonDialogComponent::setContentString(std::string other)
{
	this->m_text_content->setString(other);
}
