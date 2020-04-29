#include"JumpFloorComponent.h"
#include"cocostudio/CocoStudio.h"
#include"DataManager.h"
#include"MapUtil.h"
#include"Utils.h"
using namespace cocos2d;
using namespace ui;
bool JumpFloorComponent::init()
{
	if (!Node::init())
	{
		return false;
	}
	Utils::getInstance()->addBackground(this);
	
	this->initData();
	this->initArrow();
	this->initPage();
	this->showMap(DataManager::getInstance()->getCurFloor());
	return true;
}

void JumpFloorComponent::initData()
{
	this->ly_map = Layout::create();
	this->ly_map->setClippingEnabled(true);
	this->ly_map->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(ly_map,1);
	auto rootnode = CSLoader::createNode("JumpFloorComponent.csb");
	this->btn_close = (Button*)rootnode->getChildByName("btn_close");
	
	this->btn_close->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
		if (type==Widget::TouchEventType::ENDED)
		{
			this->removeFromParent();
		}
	});
	this->btn_close->setPressedActionEnabled(true);
	this->pv_list = (PageView*)rootnode->getChildByName("pv_list");
	this->addChild(rootnode);
	this->map = nullptr;
	this->lastClick = nullptr;

	Utils::getInstance()->addTouchSwallow(this);
}

void JumpFloorComponent::initPage()
{
	auto size = this->pv_list->getSize();
	this->pv_list->setClippingEnabled(true);
	int floorSum = DataManager::getInstance()->getFloorSum();
	int page = 1+floorSum / Constant::PAGE_NUM;
	int pageNum = Constant::PAGE_NUM;
	//this->pv_list->setClippingType()
	//layout->setSize();
	int curpage = 0;
	for (int i =0;i<page;i++)
	{
		
		auto layout = Layout::create();
		layout->setContentSize(size);
		
		layout->setBackGroundColor(Color3B::GREEN);
		//layout->setLayoutType(Layout::Type::);
		for (int j = 0;j<pageNum;j++)
		{
			
			int floor = j + 1 + 8 * i;
			if (floor>floorSum)
			{
				break;
			}
			auto btn = Button::create("res/ui_btn.png", "res/ui_btn.png");
			btn->setPressedActionEnabled(true);
			auto str = StringUtils::format("%d", floor);
			btn->setPosition(Vec2((j % 4) * 100 + 35, 120- (j / 4) * 100));
			if (floor==DataManager::getInstance()->getCurFloor())
			{
				curpage = i;
				auto target_Point = this->getBtnPosition(btn);
				//node_arrow->setParent(layout);
				target_Point.x += layout->getContentSize().width*i;
				node_arrow->setPosition(target_Point);
			}
			btn->setTitleText(str);
			btn->setTitleFontSize(50);
			btn->setAnchorPoint(Vec2::ZERO);
			if (DataManager::getInstance()->getArrivalFloor()<floor)
			{
				btn->setColor(Color3B::GRAY);
			}
			btn->addTouchEventListener([this,floor,btn,layout,i](Ref* sender,Widget::TouchEventType type) {
				if (type==Widget::TouchEventType::ENDED)
				{
					if (DataManager::getInstance()->getArrivalFloor()<floor)
					{
						return;
					}
					if (this->lastClick==nullptr)
					{
						if (DataManager::getInstance()->getCurFloor()==floor)
						{
							return;
						}
						//log("show the %d floor",floor);
						this->lastClick = btn;
						auto target_point = this->getBtnPosition(btn);
						target_point.x += layout->getContentSize().width*i;
						node_arrow->setPosition(target_point);
						this->showMap(floor);
					}
					else if (this->lastClick==btn)
					{
						//log("jump to target floor");
						this->lastClick = nullptr;
						Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(NOTIFICATION_TYPE::SCENE_JUMP_TO_TARGET_FLOOR, (void*)floor);

					}else if (this->lastClick!=btn)
					{
						//log("new record");
						this->lastClick = btn;
						auto target_point = this->getBtnPosition(btn);
						target_point.x += layout->getContentSize().width*i;
						node_arrow->setPosition(target_point);
						this->showMap(floor);
					}
					//log("cur floor %d",floor);
				}
			});
			layout->addChild(btn);
		}
		//layout->addChild(img);
		this->pv_list->addPage(layout);
	}

	this->pv_list->setCurPageIndex(curpage);
}

void JumpFloorComponent::initArrow()
{
	this->node_arrow = Node::create();
	//this->node_arrow->retain();
	this->pv_list->addChild(this->node_arrow);
	int len = 4;
	float rotation = 360 / 4;
	Vec2 list[4] = {Vec2(20.0,0.0f),Vec2(0.0,-20.0f),Vec2(-20.0f,0.0f),Vec2(0.0,20.0f) };
	for (int i =0;i<len;i++)
	{
		auto arrow = Sprite::create("fzlp_jian.png");
		arrow->setRotation(rotation*i);
		arrow->setAnchorPoint(Vec2(0.0f,0.5f));
		arrow->setPosition(list[i]);
		this->node_arrow->addChild(arrow);
	}
}

void JumpFloorComponent::showMap(int floor)
{
	if (map!=nullptr)
	{
		map->removeFromParent();
		map = nullptr;
	}
	std::string mapstr = StringUtils::format("floor/floor_%d.tmx", floor);
	map = experimental::TMXTiledMap::create(mapstr);
	map->setAnchorPoint(Vec2(0.5f,0.5f));
	float scale = 0.55f;
	map->setScale(scale);
	//int x = -map->getContentSize().width / 2;
	

	ly_map->setPosition(Vec2(0,125));
	//map->
	//MapUtil::getInstance()->setMap(map);
	MapUtil::getInstance()->initMapSize(map->getTileSize(),map->getMapSize());
	MapUtil::getInstance()->updateMapVisible(map, floor);
	MapUtil::getInstance()->initImageReplaceAndAnimation(map,false);
	ly_map->setContentSize(Size(map->getContentSize().width*scale -50,map->getContentSize().height*scale -50));
	//ly_map->setScale(map->getScale());
	ly_map->addChild(map,2);
	map->setPosition(Vec2(ly_map->getContentSize().width / 2, ly_map->getContentSize().height/2-30.0f));
	//map->addChild()
}

cocos2d::Vec2 JumpFloorComponent::getBtnPosition(cocos2d::ui::Button * btn)
{
	Vec2 pos = btn->getPosition();
	pos.x += btn->getContentSize().width / 2;
	pos.y += btn->getContentSize().height / 2;
	return pos;
}

//JumpFloorComponent::~JumpFloorComponent()
//{
//	super
//	this->node_arrow->release();
//}
