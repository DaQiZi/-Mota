#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include"Hero.h"
#include"ShopComponent.h"
#include"ShopItemComponent.h"
#include"Config.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "ShopInfoEntity.h"
#include"ShopEntity.h"
#include"Utils.h"
#include"JumpFloorComponent.h"
#include"MHurtItemComponent.h"
#include"MHurtComponent.h"
#include"Monster.h"
#include"TabComponent.h"
#include"Arrow.h"
//#include"HeroInfoView.h"
//#include"CommonDialogComponent.h"
//#include "Config.h"
//#include"OtherEntity.h"
USING_NS_CC;
using namespace cocostudio;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	auto winsize = Director::getInstance()->getWinSize();
	Utils::getInstance()->setRootNode(this);


	auto arrow = Arrow::create();
	arrow->setPosition(LocationUtils::getInstance()->CENTER);
	this->addChild(arrow);
	/*auto list = Config::getInstance()->getMonsterList();*/


	/*auto component = TabComponent::create();
	component->setPosition(Vec2(0,100));
	this->addChild(component);*/

	//cocos2d::
	/*auto component = MHurtComponent::create();
	component->setPosition(LocationUtils::getInstance()->CENTER);
	this->addChild(component);*/

	/*auto eneity = Config::getInstance()->getMonsterById("10001");
	auto item = MHurtItemComponent::create();
	item->updateItem(eneity);
	item->setPosition(Vec2(0,winsize.height/2));
	this->addChild(item);*/
	/*auto item = JumpFloorComponent::create();
	item->setPosition(LocationUtils::getInstance()->CENTER);
	this->addChild(item);*/
	//auto item = Config::getInstance()->getShopInfoEntityById("8003");
	/*auto item = Config::getInstance()->getShopEntityById("80001");
	auto shop = ShopComponent::create();
	shop->updateData(item);
	shop->setPosition(LocationUtils::getInstance()->CENTER);
	this->addChild(shop);*/

	/*std::string content = FileUtils::getInstance()->getStringFromFile("json//t_shop_list.json");
	rapidjson::Document doc;
	doc.Parse(content.c_str());

	auto &value = doc["8001"];
	auto obj = value.GetObjectW();
	std::string str = obj["cost"].GetString();
	log("%s", str.c_str());*/
	/*auto list = Config::getInstance()->getShopArray("8003");
	log("---------------shoplist------------------");
	for (auto item:list)
	{
		log("%s  %d",item.id.c_str(),item.num);
	}*/
	
	//auto node = ShopComponent::create();
	/*auto node = ShopComponent::create();
	node->setPosition(LocationUtils::getInstance()->CENTER);
	this->addChild(node);*/
	/*auto data = FileUtils::getInstance()->getValueMapFromFile(FILE_NAME::t_chinese_xml);
	std::string tips = data["tips"].asString();*/
	/*auto config = Config::getInstance()->getOtherEntityById("30001");
	auto lb = Label::create();
	lb->setSystemFontSize(100);
	lb->setString(config.name);
	lb->setPosition(LocationUtils::getInstance()->CENTER);
	this->addChild(lb);*/
	//

	//ValueMap map;
	//ValueVector vec_1;
	//int weight = 100;
	//for (int x = 1; x < 10;x++)
	//{
	//	for (int y = 0; y < 11;y++)
	//	{
	//		int value = x*weight + y;
	//		Value newvalue(value);
	//		vec_1.push_back(newvalue);
	//	}
	//}
	//map["1"] = vec_1;
	//std::string filename = FileUtils::getInstance()->getWritablePath() + "demo.xml";
	//auto flag = FileUtils::getInstance()->writeValueMapToFile(map, filename);
	//if (flag)
	//{
	//	log("file save success");
	//}
	//else{
	//	log("file save fail");
	//}
	//

	//ValueMap newmap = FileUtils::getInstance()->getValueMapFromFile(filename);
	//if (newmap.find("1")!=newmap.end())
	//{
	//	ValueVector newvec = newmap["1"].asValueVector();
	//	for (auto item:newvec)
	//	{
	//		//log("newvec");
	//		log(item.asString().c_str());
	//	}
	//}
	//vec_1.push_back(1);
	/*auto node = CommonDialogComponent::create();
	node->setPosition(LocationUtils::getInstance()->CENTER);
	this->addChild(node);*/
	/*auto heroinfo = HeroInfo::create();
	heroinfo->setPosition(Vec2(winsize.width / 2, winsize.height / 2));
	this->addChild(heroinfo);*/
	/*auto rootNode = CSLoader::createNode("heroInfo.csb");
	rootNode->setPosition(Vec2(winsize.width / 2, winsize.height / 2));*/
	/*auto btn_head = (ui::Button*)(rootNode->getChildByName("btn_head"));
	btn_head->addTouchEventListener([this](Ref* sender,ui::Widget::TouchEventType type){
		if (type==ui::Widget::TouchEventType::ENDED)
		{
			log("aaaaaaaaaaaaaaaaaaaaa");
		}
	});

	auto load = (ui::LoadingBar*)(rootNode->getChildByName("load_1"));
	load->setPercent(50.0f);
	this->addChild(rootNode);*/
	/*auto hero = Hero::create("hero.ExportJson");
	hero->setScale(4.0f);
	hero->setPosition(Vec2(winsize.width/2,winsize.height/2));*/





	//json Demo

	/*std::string content = FileUtils::getInstance()->getStringFromFile("hello.json");
	rapidjson::Document d;
	d.Parse(content.c_str());
	rapidjson::Value& s = d["10002"];
	if (s.IsObject())
	{
	auto obj = s.GetObjectW();
	rapidjson::Value& item = obj["name"];
	log("%s",item.GetString());
	}
	log("%s",content.c_str());*/
	//this->addChild(hero);
	/*ArmatureDataManager::getInstance()->addArmatureFileInfo("");*/
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
