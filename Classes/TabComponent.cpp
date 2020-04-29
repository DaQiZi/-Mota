#include"TabComponent.h"
#include"cocostudio/CocoStudio.h"
#include"Constant.h"
#include"Utils.h"
#include"SaveUtils.h"
#include"CommonDialogComponent.h"
#include"Hero.h"
#include"Config.h"
#include"MapUtil.h"
#include"MainScene.h"
#include"SoundUtil.h"
#include"DataManager.h"
using namespace cocos2d;
using namespace ui;
bool TabComponent::init()
{
	if (!Node::init())
	{
		return false;
	}
	Utils::getInstance()->addBackground(this,Vec2::ZERO);
	Utils::getInstance()->addTouchSwallow(this);
	
	this->initData();
	return true;
}

void TabComponent::initData()
{
	this->save_layout = nullptr;
	this->book_layout = nullptr;
	this->set_layout = nullptr;
	auto rootnode = CSLoader::createNode(FILE_NAME::t_TabComponent_csb);
	//rootnode->setPosition(LocationUtils::getInstance()->CENTER);
	this->addChild(rootnode);

	this->ly_bg = (Layout*)rootnode->getChildByName("ly_bg");
	this->ly_set = (Layout*)rootnode->getChildByName("ly_set");
	this->ly_save = (Layout*)rootnode->getChildByName("ly_save");
	this->ly_book = (Layout*)rootnode->getChildByName("ly_book");

	this->btn_book = (Button*)ly_bg->getChildByName("btn_book");
	this->btn_close = (Button*)ly_bg->getChildByName("btn_close");
	this->btn_set = (Button*)ly_bg->getChildByName("btn_set");
	this->btn_save = (Button*)ly_bg->getChildByName("btn_save");
	this->initButton();
}

void TabComponent::initButton()
{
	Vec2 location(30,185);

	this->ly_save->setPosition(location);
	this->btn_save->setBright(false);
	this->updateSave();
	Utils::getInstance()->addButtonListener(this->btn_close, [this,location]() {
		this->removeFromParent();
	});

	Utils::getInstance()->addButtonListener(this->btn_book, [this,location]() {
		//this->removeFromParent();
		this->moveAllLayout();
		this->ly_book->setPosition(location);
		this->ly_book->setVisible(true);
		//this->btn_book->setBright(false);
		Utils::getInstance()->setButtonDisable(this->btn_book);
		this->updateBook();
	});
	Utils::getInstance()->addButtonListener(this->btn_set, [this,location]() {
		//this->removeFromParent();
		this->moveAllLayout();
		this->ly_set->setPosition(location);
		this->ly_set->setVisible(true);
		//this->btn_set->setBright(false);
		Utils::getInstance()->setButtonDisable(this->btn_set);
		this->updateSet();
	});
	Utils::getInstance()->addButtonListener(this->btn_save, [this,location]() {
		//this->removeFromParent();
		this->moveAllLayout();
		this->ly_save->setPosition(location);
		this->ly_save->setVisible(true);
		Utils::getInstance()->setButtonDisable(this->btn_save);
		//this->btn_save->setBright(false);
		this->updateSave();
	});
}

void TabComponent::moveAllLayout()
{
	this->ly_book->setPosition(Vec2(-1000,-1000));
	this->ly_save->setPosition(Vec2(-1000, -1000));
	this->ly_set->setPosition(Vec2(-1000, -1000));
	this->ly_book->setVisible(false);
	this->ly_save->setVisible(false);
	this->ly_set->setVisible(false);
	this->btn_book->setBright(true);
	this->btn_set->setBright(true);
	this->btn_save->setBright(true);

	this->btn_book->setTouchEnabled(true);
	this->btn_set->setTouchEnabled(true);
	this->btn_save->setTouchEnabled(true);
}

void TabComponent::updateSave()
{

	if (this->save_layout==nullptr)
	{
		this->save_layout = SaveItem::create();
		this->save_layout->updateItem(this->ly_save);
		//this->addChild(this->s)
		this->ly_save->addChild(this->save_layout);
	}
	//std::string time = Utils::getInstance()->getcurrTime();
	/*auto lable = Text::create();
	lable->setString(time);
	this->ly_save->addChild(lable)
	;*/
	//log("%s ",time.c_str());
}

void TabComponent::updateSet()
{
	if (this->set_layout==nullptr)
	{
		auto item = SetItem::create();
		item->updateData(this->ly_set);
		this->ly_set->addChild(item);
	}
}

void TabComponent::updateBook()
{
	if (this->book_layout==nullptr)
	{
		this->book_layout = BookItem::create();
		this->book_layout->updateItem(this->ly_book);
		this->ly_book->addChild(this->book_layout);
	}
}



void SaveItem::updateItem(cocos2d::ui::Layout * parent)
{
	auto layout = (Layout*)parent->getChildByName("ly_base");
	this->ly_base = layout;
	this->lb_time = (Text*)layout->getChildByName("lb_time");
	this->lb_floor = (Text*)layout->getChildByName("lb_floor");
	this->lb_blood = (Text*)layout->getChildByName("lb_blood");
	this->lb_attack = (Text*)layout->getChildByName("lb_attack");
	this->lb_defend = (Text*)layout->getChildByName("lb_defend");
	this->lb_soul = (Text*)layout->getChildByName("lb_soul");
	this->lb_tips = (Text*)parent->getChildByName("lb_tips");

	this->lb_gold = (Text*)layout->getChildByName("lb_gold");
	this->lb_key_red = (Text*)layout->getChildByName("lb_key_red");
	this->lb_key_yellow = (Text*)layout->getChildByName("lb_key_yellow");
	this->lb_key_blue = (Text*)layout->getChildByName("lb_key_blue");

	this->node_hero = (Node*)layout->getChildByName("node_hero");
	this->btn_save = (Button*)parent->getChildByName("btn_save");
	this->btn_read = (Button*)parent->getChildByName("btn_read");
	

	
	this->lb_time->setString(Utils::getInstance()->getcurrTime());

	auto hero = Hero::create("hero.ExportJson");
	hero->setScale(1.2f);
	hero->playAnimation(HERO_ANIMATION_ENUM::DOWN_STANE);
	hero->setPosition(this->node_hero->getPosition());
	this->ly_base->addChild(hero);
	//hero->

	this->setAllVisible(true);
	auto datamap = SaveUtils::getInstance()->getDataFromMyFile();
	bool haveData = false;
	if (datamap.size()<=0)
	{
		this->setAllVisible(false);
		haveData = false;
	}
	else {
		this->showAllInfo();
		this->setAllVisible(true);
		haveData = true;

	}
	Utils::getInstance()->addButtonListener(this->btn_read, [this]() {
		auto datamap = SaveUtils::getInstance()->getDataFromMyFile();
		bool haveData = false;
		if (datamap.size()>0)
		{
			haveData = true;
		}
		if (!haveData)
		{
			Utils::getInstance()->addTipsDialog(Utils::getInstance()->getRootNode(),"no file");
		}
		else {
			auto valuemap = FileUtils::getInstance()->getValueMapFromFile(FILE_NAME::t_chinese_xml);
			auto obj = Utils::getInstance()->getRootNode();
			Utils::getInstance()->addTwoButtonDialog(obj, valuemap["readSave"].asString(), [this]() {
				SaveUtils::getInstance()->LoadDataFromSaveFile();
				int floor = Value(this->lb_floor->getString()).asInt();
				Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(NOTIFICATION_TYPE::SCENE_JUMP_TO_TARGET_FLOOR,(void*)floor);
			});
		}
	});
	Utils::getInstance()->addButtonListener(this->btn_save, [this]() {
		//auto item = CommonDialogComponent::create(
		auto valuemap = FileUtils::getInstance()->getValueMapFromFile(FILE_NAME::t_chinese_xml);
		auto obj = Utils::getInstance()->getRootNode();
		Utils::getInstance()->addTwoButtonDialog(obj, valuemap["save"].asString(), [this]() {
			log("save ");
			SaveUtils::getInstance()->saveDataAsFile();
			this->showAllInfo();
		});
	});
}

bool SaveItem::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

void SaveItem::setAllVisible(bool flag)
{
	this->ly_base->setVisible(flag);
	flag = !flag;
	this->lb_tips->setVisible(flag);
	
}

void SaveItem::showAllInfo()
{
	
	//read data and show
	auto filename = FileUtils::getInstance()->getWritablePath() + FILE_NAME::t_save_map_data;
	auto valuemap = FileUtils::getInstance()->getValueMapFromFile(filename);
	this->lb_time->setString(valuemap["time"].asString());
	this->lb_floor->setString(valuemap["curfloor"].asString());
	this->lb_blood->setString(valuemap["nowblood"].asString());
	this->lb_attack->setString(valuemap["attack"].asString());
	this->lb_soul->setString(valuemap["soul"].asString());
	this->lb_defend->setString(valuemap["defend"].asString());

	this->lb_gold->setString(valuemap["gold"].asString());
	this->lb_key_red->setString(valuemap["red_key"].asString());
	this->lb_key_blue->setString(valuemap["blue_key"].asString());
	this->lb_key_yellow->setString(valuemap["yellow_key"].asString());
	this->setAllVisible(true);
}

bool BookItemComponent::init()
{
	if (!Widget::init())
	{
		return false;
	}
	this->initData();
	return true;
}

void BookItemComponent::initData()
{
	auto node = CSLoader::createNode(FILE_NAME::t_BookItemComponent_csb);
	this->addChild(node);

	auto ly_base = (Layout*)node->getChildByName("ly_base");
	this->ly_head = (Layout*)ly_base->getChildByName("ly_head");
	this->lb_name = (Text*)ly_base->getChildByName("lb_name");
	this->lb_desc = (Text*)ly_base->getChildByName("lb_desc");
	this->setContentSize(ly_base->getContentSize());
}

void BookItemComponent::updateData(const Monster& monster)
{
	auto spr = Sprite::create(monster.m_iconName);
	spr->setAnchorPoint(Vec2(0.5f, 1.0f));
	spr->setPosition(Vec2(ly_head->getContentSize().width / 2, ly_head->getContentSize().height));
	this->ly_head->addChild(spr);

	this->lb_name->setString(monster.m_name);
	this->lb_desc->setString(monster.m_desc);
}

bool BookItem::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->initData();
	return true;
} 

void BookItem::initData()
{
	
}

void BookItem::updateItem(cocos2d::ui::Layout * parent)
{
	this->lv_list = (ListView*)parent->getChildByName("lv_list");

	auto booklist = SaveUtils::getInstance()->getBookInfoList();
	auto allMosterList = Config::getInstance()->getMonsterList();
	for (auto monster :allMosterList)
	{
		auto item = BookItemComponent::create();
		bool isfind = false;
		for (auto bookid:booklist)
		{
			if (monster.m_id==bookid.asString())
			{
				isfind = true;
				break;
			}
		}
		if (isfind)
		{
			Monster m = Config::getInstance()->getMonsterById(monster.m_id);
			item->updateData(m);
		}
		this->lv_list->pushBackCustomItem(item);
	}
}

bool SetItem::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->initData();
	return true;
}

void SetItem::initData()
{
	
}

void SetItem::updateData(cocos2d::ui::Layout * parent)
{
	this->btn_effect = (Button*)parent->getChildByName("btn_effect");
	if (!DataManager::getInstance()->getEffectSwitch())
	{
		this->btn_effect->setBright(false);
	}
	Utils::getInstance()->addButtonListener(this->btn_effect, [this]() {
		bool flag = false;
		if (this->btn_effect->isBright())
		{
			flag = false;
			log("guan bi effect");
		}
		else {
			flag = true;
			log("kai qi  effect");
		}
		SoundUtil::getInstance()->setEffectS(flag);
		this->btn_effect->setBright(flag);
	});
	
	this->btn_music = (Button*)parent->getChildByName("btn_music");
	if (!DataManager::getInstance()->getMusicSwitch())
	{
		this->btn_music->setBright(false);
	}
	Utils::getInstance()->addButtonListener(this->btn_music, [this]() {
		bool flag = false;
		if (this->btn_music->isBright())
		{
			flag = false;
		}
		else {
			flag = true;
		}
		this->btn_music->setBright(flag);
		SoundUtil::getInstance()->setMusicS(flag);
	});
	this->btn_reset = (Button*)parent->getChildByName("btn_reset");
	Utils::getInstance()->addButtonListener(this->btn_reset, [this]() {
		auto obj = Utils::getInstance()->getRootNode();
		auto valuemap = FileUtils::getInstance()->getValueMapFromFile(FILE_NAME::t_chinese_xml);
		Utils::getInstance()->addTwoButtonDialog(obj, valuemap["reset"].asString(), [this]() {
			
			log("chong zhi you xi ");
			SaveUtils::getInstance()->resetGame();
			_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::SCENE_JUMP_TO_TARGET_FLOOR, (void*)1);
		});
	});


	this->sl_effect = (Slider*)parent->getChildByName("sl_effect");
	this->sl_effect->setPercent(DataManager::getInstance()->getEffectVolume());
	this->sl_effect->addEventListener([this](Ref* sender,Slider::EventType type) {
		if (type==Slider::EventType::ON_SLIDEBALL_UP)
		{
			int per = this->sl_effect->getPercent();
			SoundUtil::getInstance()->setEffectVolume(per);
			log(" ------>  %d",per);
		}
	});
	this->sl_music = (Slider*)parent->getChildByName("sl_music");
	this->sl_music->setPercent(DataManager::getInstance()->getMusicVolume());
	this->sl_music->addEventListener([this](Ref* sender, Slider::EventType type) {
		if (type == Slider::EventType::ON_SLIDEBALL_UP)
		{
			int per = this->sl_music->getPercent();
			SoundUtil::getInstance()->setMusicVolume(per);
			//log(" ------>  %d", per);
		}
	});

	this->btn_back = (Button*)parent->getChildByName("btn_back");
	Utils::getInstance()->addButtonListener(this->btn_back, [this]() {
		auto valuemap = FileUtils::getInstance()->getValueMapFromFile(FILE_NAME::t_chinese_xml);
		Utils::getInstance()->addTwoButtonDialog(Utils::getInstance()->getRootNode(), valuemap["back"].asString(), [this]() {
			//SaveUtils::getInstance()->saveDataToLocal()
			SaveUtils::getInstance()->saveDataToLocal();
			Director::getInstance()->replaceScene(MainScene::createScene());
		});
	});
}


