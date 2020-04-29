#include"Utils.h"
#include"CommonDialogComponent.h"
#include"Constant.h"
#include"cocos2d.h"
using namespace cocos2d;
Utils * Utils::getInstance()
{
	static Utils instance;
	return &instance;
}

void Utils::addTouchSwallow(Node* node)
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Ref* sender, Event* eve) {
		return true;
	};
	listener->setSwallowTouches(true);
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}

void Utils::addTipsDialog(Node* node, std::string content, std::function<void()> callback)
{
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(NOTIFICATION_TYPE::MOVE_TOUCH_LISTENER, (void*)true);
	auto item = CommonDialogComponent::create();
	//this->addTouchSwallow(item);
	item->setStyle(DIALOG_STYLE::TIPS,content);
	item->setPosition(LocationUtils::getInstance()->CENTER);
	item->setYesCallBack(callback);
	node->addChild(item,2);
}

void Utils::addTwoButtonDialog(Node * node, std::string content, std::function<void()> callback, std::function<void()> no_cb)
{
	
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(NOTIFICATION_TYPE::MOVE_TOUCH_LISTENER, (void*)true);
	auto item = CommonDialogComponent::create();
	//this->addTouchSwallow(item);
	item->setYesCallBack(callback);
	item->setCancelCallBack(no_cb);
	item->setContentString(content);
	item->setPosition(LocationUtils::getInstance()->CENTER);
	node->addChild(item,2);
}

void Utils::addBackground(Node* node, Vec2 anchor)
{
	auto layer = LayerColor::create(Color4B::BLACK);
	layer->setOpacity(125.0f);
	layer->setAnchorPoint(anchor);
	layer->ignoreAnchorPointForPosition(false);
	node->addChild(layer);
}

void Utils::addButtonListener(ui::Button* btn, std::function<void()> callback)
{
	btn->addTouchEventListener([callback](Ref* sender,Widget::TouchEventType type) {
		if (type==Widget::TouchEventType::ENDED)
		{
			callback();
		}
	});
	btn->setPressedActionEnabled(true);
}

Node * Utils::getRootNode()
{
	return this->rootnode;
}

void Utils::setRootNode(Node * node)
{
	this->rootnode = node;
}

std::string Utils::getcurrTime()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

	struct timeval now;
	struct tm* time;

	gettimeofday(&now, NULL);


	time = localtime(&now.tv_sec);
	int year = time->tm_year + 1900;
	log("year = %d", year);

	char date[32] = { 0 };
	sprintf(date, "%d-%02d-%02d %d:%02d", (int)time->tm_year + 1900, (int)time->tm_mon + 1, (int)time->tm_mday, (int)time->tm_hour, (int)time->tm_min, (int)time->tm_sec);
	log("%s", date);
	return StringUtils::format("%s", date);

#endif

#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )

	struct tm* tm;
	time_t timep;
	time(&timep);
	//tm = localtime(&timep);
	tm = localtime(&timep);
	char date[32] = { 0 };
	sprintf(date, "%d-%02d-%02d %d:%02d", (int)tm->tm_year + 1900, (int)tm->tm_mon + 1, (int)tm->tm_mday,(int)tm->tm_hour,(int)tm->tm_min,(int)tm->tm_sec);
	//cocos2d::log("%s", date);
	return StringUtils::format("%s", date);

#endif
}

void Utils::setButtonDisable(cocos2d::ui::Button * btn)
{
	btn->setBright(false);
	btn->setTouchEnabled(false);
}

void Utils::addTipsLabel(std::string content)
{
	auto label = cocos2d::Label::createWithSystemFont(content,"",80);
	auto size = Director::getInstance()->getWinSize();
	label->setPosition(Vec2(size.width/2,800.0f));
	label->setScale(0.0f);
	auto act_1 = ScaleTo::create(0.2f,1.0f);
	auto act_2 = DelayTime::create(0.5f);
	auto act_3 = RemoveSelf::create();
	label->runAction(Sequence::create(act_1, act_2, act_3, nullptr));
	//label->runAction();
	auto obj = this->getRootNode();
	obj->addChild(label);
}



LocationUtils* LocationUtils::getInstance() {
	static LocationUtils instance;
	return &instance;
}

LocationUtils::LocationUtils() {
	this->WIN_SIZE = Director::getInstance()->getWinSize();
	this->CENTER = Vec2(WIN_SIZE.width / 2, WIN_SIZE.height / 2);
}