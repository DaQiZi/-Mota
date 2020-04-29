
#include "cocos2d.h"
#include "GameScene.h"
#include "AStar.h"
#include "MapUtil.h"
#include "Constant.h"
#include "HeroInfoView.h"
#include "Monster.h"
#include "Config.h"
#include "Hero.h"
#include "Monster.h"
#include "DataManager.h"
#include "CommonDialogComponent.h"
#include "OtherEntity.h"
#include "ShopComponent.h"
#include "ShopEntity.h"
#include"Utils.h"
#include"Arrow.h"
#include"MainScene.h"
#include"SoundUtil.h"
#include"SaveUtils.h"
using namespace cocos2d;

Scene* GameScene::createScene(){
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}


bool GameScene::init(){
	if (!Layer::init()){
		return false;
	}
	SoundUtil::getInstance()->playBG();
	m_winSize = Director::getInstance()->getVisibleSize();
	//this->initMap();
	this->initImg();
	this->showFloor();
	this->initData();
	Utils::getInstance()->setRootNode(this);
	return true;
}

void GameScene::initData(){
	this->m_map_origin = Vec2(-50.0f,-50.0f);
	this->m_hero = nullptr;
	this->m_arrow = nullptr;
	this->m_heroMoveSpeed = 200;
	
	this->m_moveChange = false;
	this->m_last_node.m_x = -1;
	this->m_last_node.m_y = -1;
	this->isMoveListenerSwallow = false;
	//this->m_heroIsMoveing = false;

	//this->drawnnode->draw
	this->initBG();
	this->initMap();
	this->initListener();
	this->initNotification();
	this->m_heroinfo = HeroInfoView::create();
	this->m_heroinfo->setPosition(Vec2(this->m_winSize.width / 2, this->m_map->getContentSize().height+20.0f));
	this->addChild(this->m_heroinfo);
}

void GameScene::initImg()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img/daiti.plist");
	//SpriteFrameCache::getInstance()->re
}

void GameScene::initMapFromFile(){

}
void GameScene::initMap(){
	int curFloor = DataManager::getInstance()->m_cur_floor;
	std::string filename = StringUtils::format("floor/floor_%d.tmx", curFloor);
	this->m_map = experimental::TMXTiledMap::create(filename);
	this->m_map->setPosition(this->m_map_origin);
	this->addChild(this->m_map);
	MapUtil::getInstance()->initMapSize(this->m_map->getTileSize(), this->m_map->getMapSize());
	MapUtil::getInstance()->setMap(this->m_map);
	//初始化角色的位置。
	//this->m_map->getMapSize();
	this->drawnnode = DrawNode::create();
	this->m_map->addChild(this->drawnnode, 2);

	this->m_arrow = Arrow::create();
	this->m_arrow->setVisible(false);
	this->m_map->addChild(this->m_arrow,3);
	this->initHero();
}

void GameScene::initBG()
{
	auto size = Director::getInstance()->getWinSize();
	auto img = Sprite::create("img/bg_top_1.png");
	img->setPosition(Vec2(size.width / 2, 1100.0f));
	img->setScale(2.0f);
	this->addChild(img);
	auto img1 = Sprite::create("img/bg_top.png");
	img1->setPosition(Vec2(size.width/2,1080.0f));
	this->addChild(img1);
}

void GameScene::initHero()
{
	//todo 根据状态，确定英雄需要站在那个口。
	auto hero_type = DataManager::getInstance()->heroFloorStatus;
	//if is up then location is down stairs
	auto mapsize = this->m_map->getMapSize();
	auto main_layer = this->m_map->getLayer(Constant::MAIN_LAYER_NAME);

	MyNode targetNode;
	MyNode heroStandNode;
	bool isFind = false;
	bool havaFloorShow = false;
	for (int w = 0;w<mapsize.width;w++)
	{
		for (int h=0;h<mapsize.height;h++)
		{
			//find stairs down 
			int gid = main_layer->getTileGIDAt(Vec2(w, h));
			Value value = this->m_map->getPropertiesForGID(gid);
			if (!value.isNull())
			{
				ValueMap valueMap = value.asValueMap();
				if (valueMap.find(Constant::MAIN_TYPE)!=valueMap.end())
				{
					int type = valueMap[Constant::MAIN_TYPE].asInt();
					if (type==MIAN_TYPE_ENUM::STAIRS)
					{
						int stairsType = valueMap[Constant::STAIRS_TYPE].asInt();
						STAIRS_TYPE_ENUM newType = (STAIRS_TYPE_ENUM)stairsType;
						//只能找到一个，就是符合英雄的状态的上或者下楼梯。
						if ((newType==STAIRS_TYPE_ENUM::UP&&hero_type==STAIRS_TYPE_ENUM::DOWN)||(newType == STAIRS_TYPE_ENUM::DOWN&&hero_type == STAIRS_TYPE_ENUM::UP))
						{
							targetNode.m_x = w;
							targetNode.m_y = h;
							isFind = true;
							//break;
						}
					}else if (type==MIAN_TYPE_ENUM::HERO_STAND)
					{
						heroStandNode.m_x = w;
						heroStandNode.m_y = h;
						havaFloorShow = true;
					}
				}
			}
		}
		/*if (isFind)
		{
			break;
		}*/
	}
	//auto around = 
	vector<MyNode> vec;
	vec.push_back(MyNode(targetNode.m_x - 1, targetNode.m_y));
	vec.push_back(MyNode(targetNode.m_x + 1, targetNode.m_y));
	vec.push_back(MyNode(targetNode.m_x, targetNode.m_y-1));
	vec.push_back(MyNode(targetNode.m_x, targetNode.m_y+1));

	MyNode hero_targetNode;
	for (MyNode node:vec)
	{
		if (node.m_x < 1 || node.m_x >= mapsize.width) {
			continue;;
		}
		if (node.m_y < 1 || node.m_y >= mapsize.height) {
			continue;
		}
		
		auto tempnode = MapUtil::getInstance()->convertCoordToMyNode(node);
		if (MapUtil::getInstance()->judgeNodeIsBlock(tempnode)) {
			continue;
		};
		auto type = MapUtil::getInstance()->judgeMainLayerNodeType(tempnode);
		if (hero_type==STAIRS_TYPE_ENUM::UP)
		{
			
			if (type==MIAN_TYPE_ENUM::HERO_STAND)
			{
				hero_targetNode = tempnode;
				break;
			}
		}
		else if (type == MIAN_TYPE_ENUM::NONE&&hero_type==STAIRS_TYPE_ENUM::DOWN) {
			hero_targetNode = tempnode;
			break;
		}
	}
	//todo 找到目标点。初始化位置
	//TMXObjectGroup* layer = this->m_map->getObjectGroup("object");
	//auto heroInfo = layer->getObject("hero");
	this->m_hero = Hero::create("hero.ExportJson");
	this->m_hero->playAnimation(HERO_ANIMATION_ENUM::DOWN_STANE);
	this->m_hero->setContentSize(this->m_map->getTileSize());
	//float x = heroInfo["x"].asFloat();
	//float y = heroInfo["y"].asFloat();
	float x = hero_targetNode.m_x*MapUtil::getInstance()->getTileSize().x;
	float y = hero_targetNode.m_y*MapUtil::getInstance()->getTileSize().y;

	this->m_hero->setPosition(Vec2(x + this->m_hero->getContentSize().width / 2, y + this->m_hero->getContentSize().height / 2));
	//this->m_hero->setPosition(Vec2(x, y));
	if (havaFloorShow)
	{
		auto node = MapUtil::getInstance()->convertCoordToMyNode(heroStandNode);
		float floor_x = node.m_x*MapUtil::getInstance()->getTileSize().x;
		float floor_y = node.m_y*MapUtil::getInstance()->getTileSize().y;
		this->showMapFloor(Vec2(floor_x,floor_y));
	}
	this->m_map->addChild(this->m_hero,3);
}

void GameScene::showMapFloor(Vec2 node)
{
	std::string floor = StringUtils::toString(DataManager::getInstance()->getCurFloor());
	auto lb_floor = TextAtlas::create(floor,"lv_num.png",24,38,"0");
	node.x += MapUtil::getInstance()->getTileSize().x / 2;
	node.y += MapUtil::getInstance()->getTileSize().y / 2;
	lb_floor->setPosition(node);
	this->m_map->addChild(lb_floor,3);
}
Vec2 GameScene::getHeroNewPos(Vec2 pos){
	auto hero_direction = this->m_hero->getDirection();
	
	Vec2 tempPos = pos;
	switch (hero_direction)
	{
	case STAND:
		break;
	case UP:
		tempPos.y = tempPos.y+MapUtil::getInstance()->getTileSize().y/2 +1;
		break;
	case DOWN:
		tempPos.y = tempPos.y-MapUtil::getInstance()->getTileSize().y / 2 + 1;
		break;
	case LEFT:
		tempPos.x = tempPos.x-MapUtil::getInstance()->getTileSize().x / 2 + 1;
		break;
	case RIGHT:
		tempPos.x = tempPos.x+MapUtil::getInstance()->getTileSize().x / 2 + 1;
		break;
	default:
		break;
	}
	return tempPos;
	//Vec2 newHeroPos = touch->getLocation();
}

void GameScene::initListener(){

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* e){
		
		return true;
	};
	listener->onTouchEnded = [this](Touch* touch, Event* e){
		if (this->isMoveListenerSwallow)
		{
			return;
		}
		bool isTouchMap = this->isTouchMap(touch->getLocation());
		if (isTouchMap){
			Vec2 newNode = this->m_map->convertTouchToNodeSpace(touch);
			MyNode target_node = MapUtil::getInstance()->convertCocosPointToTileNode(newNode);
			MyNode cur_node;
			if (this->m_hero->m_heroisMoving)
			{
				auto newPos = this->getHeroNewPos(this->m_hero->getPosition());
				cur_node = MapUtil::getInstance()->convertCocosPointToTileNode(newPos);
			}
			else {
				cur_node = MapUtil::getInstance()->convertCocosPointToTileNode(this->m_hero->getPosition());
			}
			
			
			if (MapUtil::getInstance()->judgeNodeIsBlock(target_node)){
				return;
			}
			else if (target_node.isEquls(this->m_last_node))
			{
				return;
			}else if (target_node.isEquls(cur_node))
			{
				return;
			}
			m_last_node = target_node;
			//Utils::getInstance()->addTipsLabel();
			auto  path = AStar::getInstance()->getPath(this->m_map->getLayer(Constant::BLOCK_NAME), cur_node, target_node);
			//由于可能出现点击一个点，又点击一个点，路线相同，但是人物要回头的现象。
			if (path.size() <= 0){
				log("no path or is curnode");
			}
			else{
				this->m_moveChange = false;
				if (this->m_hero->m_heroisMoving||DataManager::getInstance()->getHeroIsFight())
				{
					this->m_moveChange = true;
				}
				//this->m_moveChange = true;
				this->moveToTargetNode(path);
			}
			log("%d %d",cur_node.m_x,cur_node.m_y);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool GameScene::isTouchMap(Point p){
	int map_width = this->m_map->getTileSize().width*this->m_map->getMapSize().width+this->m_map_origin.x;
	int map_height = this->m_map->getTileSize().height*this->m_map->getMapSize().height+ this->m_map_origin.y;
	bool isTouch = false;
	if (p.x >= 0 && p.x <= map_width){
		if (p.y >= 0 && p.y <= map_height){
			isTouch = true;
		}
	}
	return isTouch;
	//aaa
}

void GameScene::drawHeroPath(vector<MyNode> path)
{
	/*this->drawnnode->clear();
	for (int i = 1; i < path.size(); i++) {
		auto node1 = MapUtil::getInstance()->convertTileNodeToCocosPoint(path[i - 1]);
		node1.x = node1.x + this->m_hero->getContentSize().width / 2;
		node1.y = node1.y + this->m_hero->getContentSize().height / 2;
		auto node2 = MapUtil::getInstance()->convertTileNodeToCocosPoint(path[i]);
		node2.x = node2.x + this->m_hero->getContentSize().width / 2;
		node2.y = node2.y + this->m_hero->getContentSize().height / 2;
		this->drawnnode->drawLine(node1, node2, Color4F::RED);
	}*/
	this->removePath(false);
	for (int i = 0; i < path.size(); i++) {
		
		auto node = MapUtil::getInstance()->convertTileNodeToCocosPoint(path[i]);
		node.x = node.x + this->m_hero->getContentSize().width / 2;
		node.y = node.y + this->m_hero->getContentSize().height / 2;
		int index = cocos2d::random() % 22;
		std::string filename = StringUtils::format("path/diban%d.png", index);
		auto spr = Sprite::create(filename);
		spr->setPosition(node);
		this->m_map->addChild(spr);
		this->m_draw_path.pushBack(spr);
		if (i==(path.size()-1))
		{
			if (m_arrow==nullptr)
			{
				m_arrow = Arrow::create();
				m_arrow->setPosition(node);
				this->m_map->addChild(m_arrow);
			}
			else {
				m_arrow->setPosition(node);
			}
			m_arrow->setVisible(true);
		}
	}
}
void GameScene::removePath(bool single)
{
	if (single)
	{
		if (this->m_draw_path.size() == 1)
		{
			if (this->m_arrow)
			{
				this->m_arrow->setPosition(Vec2(-100.0f, -100.0f));
				this->m_arrow->setVisible(false);
			}
		}
		if (this->m_draw_path.size()>0)
		{
			this->m_draw_path.at(0)->removeFromParent();
			this->m_draw_path.erase(this->m_draw_path.begin());
			
		}
	}
	else {
		for (auto img : this->m_draw_path)
		{
			img->removeFromParent();
		}
		this->m_draw_path.clear();
		if (this->m_arrow)
		{
			this->m_arrow->setPosition(Vec2(-100.0f, -100.0f));
			this->m_arrow->setVisible(false);
			
		}
		
	}
	
}
void GameScene::showFloor()
{
	auto size = Director::getInstance()->getWinSize();
	auto layer = LayerColor::create(Color4B::BLACK,size.width,size.height);
	auto valuemap = FileUtils::getInstance()->getValueMapFromFile(FILE_NAME::t_chinese_xml);
	auto str = StringUtils::format(valuemap["floor"].asString().c_str(),DataManager::getInstance()->getCurFloor());
	auto lb_text = Text::create();
	lb_text->setString(str);
	//layer->setPosition();
	lb_text->setPosition(LocationUtils::getInstance()->CENTER);
	lb_text->setFontSize(50);
	layer->addChild(lb_text);
	this->addChild(layer,5);
	auto act_1 = FadeOut::create(0.8f);
	auto act_2 = CallFunc::create([layer]() {
		layer->removeFromParent();
	});
	layer->runAction(Sequence::create(act_1, act_2, nullptr));
}

void GameScene::moveToTargetNode(std::vector<MyNode> path){
	
	this->drawHeroPath(path);
	//path.erase(path.begin());
	auto nextNode = MapUtil::getInstance()->convertTileNodeToCocosPoint(path[0]);
	nextNode.x = nextNode.x + this->m_hero->getContentSize().width / 2;
	nextNode.y = nextNode.y + this->m_hero->getContentSize().width / 2;
	//todo begin move
	if (!this->m_moveChange){

		this->heroMoveToNext(path, nextNode);
	}
	else{
		//this->m_moveCallback = std::bind(&GameScene::heroMoveToNext, this, path, nextNode);
		this->m_moveCallback = [=](){
			this->heroMoveToNext(path, nextNode);
		};
	}
}
void GameScene::changeHeroDirection(MyNode curnode, MyNode nextnode){

	DIRECTION_ENUM heroDirection;
	if (curnode.isEquls(nextnode))
	{
		heroDirection = DIRECTION_ENUM::STAND;
	}
	else if (curnode.m_y<nextnode.m_y){
		heroDirection = DIRECTION_ENUM::UP;
	}
	else if (curnode.m_y>nextnode.m_y){
		heroDirection = DIRECTION_ENUM::DOWN;
	}
	else if (curnode.m_x > nextnode.m_x){
		heroDirection = DIRECTION_ENUM::LEFT;
	}
	else if (curnode.m_x < nextnode.m_x)
	{
		heroDirection = DIRECTION_ENUM::RIGHT;
	}

	this->m_hero->changeHeroDirection(heroDirection);
}

void GameScene::heroOpenDoor(MyNode node){
	//this->m_heroIsMoveing = false;
	
	this->m_hero->changeHeroDirection(DIRECTION_ENUM::STAND);
	
	auto id = MapUtil::getInstance()->getTargetNodeId(node);
	auto obj = Config::getInstance()->getOtherEntityById(id);
	int key_num = 0;
	std::string key_id = "";
	switch (obj.stype)
	{
	case KEY_TYPE::YELLOW:
		key_num = DataManager::getInstance()->m_key2_num;
		key_id = "30001";
		break;
	case KEY_TYPE::BLUE:
		key_num = DataManager::getInstance()->m_key1_num;
		key_id = "30002";
		break;
	case KEY_TYPE::RED:
		key_num = DataManager::getInstance()->m_key0_num;
		key_id = "30003";
		break;
	default:
		break;
	}
	auto dialog = CommonDialogComponent::create();
	if (key_num>0)
	{
		dialog->setYesCallBack([this,obj,node]() {
			SoundUtil::getInstance()->playEffect(AUDIO_EFFECT_ENUM::AU_DOOR);
			DataManager::getInstance()->addHeroKey(obj.stype,obj.add);
			MyNode newnode;
			newnode.m_x = node.m_x;
			newnode.m_y = node.m_y + 1;

			std::string up_id = MapUtil::getInstance()->getTargetNodeId(newnode);
			if (up_id==StringUtils::toString(obj.id))
			{
				MapUtil::getInstance()->setTargetTileVisible(newnode,false,true);
			}
			this->m_doorCallbakc();
		});
		
	}
	else {
		dialog->setYesCallBack([this,key_id]() {
			_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::TARGET_NODE_CHANGE);
			auto keyobj = Config::getInstance()->getOtherEntityById(key_id);
			auto valuemap = FileUtils::getInstance()->getValueMapFromFile(FILE_NAME::t_chinese_xml);
			std::string newstr = StringUtils::format(valuemap["tips"].asString().c_str(), keyobj.name.c_str());
			Utils::getInstance()->addTipsDialog(this,newstr);
			
			/*auto tipsdialog = CommonDialogComponent::create();
			tipsdialog->setStyle(DIALOG_STYLE::TIPS,keyobj.name);
			tipsdialog->setPosition(LocationUtils::getInstance()->CENTER);
			this->addChild(tipsdialog);*/
		});
	}
	dialog->setCancelCallBack([this]() {
		_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::ARROW_HIDE);
	});
	//dialog->setYesCallBack(this->m_doorCallbakc);
	dialog->setPosition(LocationUtils::getInstance()->CENTER);
	this->addChild(dialog);
}
void GameScene::heroAddBlood(MyNode node)
{
	auto id = MapUtil::getInstance()->getTargetNodeId(node);
	auto obj = Config::getInstance()->getOtherEntityById(id);
	DataManager::getInstance()->handleAllAttr(obj);
	//DataManager::getInstance()->addHeroBlood(obj.add);
	std::string str = Config::getInstance()->getChineseContent("tipAdd");
	std::string name = Config::getInstance()->getChineseContent("blood");
	std::string content = StringUtils::format(str.c_str(),name.c_str(),obj.add);
	Utils::getInstance()->addTipsLabel(content);
	SoundUtil::getInstance()->playEffect(AUDIO_EFFECT_ENUM::AU_HP);
}
void GameScene::heroAddDiamond(MyNode node)
{
	auto id = MapUtil::getInstance()->getTargetNodeId(node);
	auto obj = Config::getInstance()->getOtherEntityById(id);
	std::string str = Config::getInstance()->getChineseContent("tipAdd");
	std::string name = "";
	if (obj.stype==DIAMONDS_TYPE::ATTACK)
	{
		name = Config::getInstance()->getChineseContent("attack");
	}
	else {
		name = Config::getInstance()->getChineseContent("defend");
	}
	std::string content = StringUtils::format(str.c_str(), name.c_str(), obj.add);
	Utils::getInstance()->addTipsLabel(content);
	SoundUtil::getInstance()->playEffect(AUDIO_EFFECT_ENUM::AU_DIA);
	DataManager::getInstance()->handleAllAttr(obj);
	/*if (obj.stype==DIAMONDS_TYPE::ATTACK)
	{
		DataManager::getInstance()->addHeroAttack(obj.add);
	}
	else {
		DataManager::getInstance()->addHeroDefend(obj.add);
	}*/
}
void GameScene::heroAssist(MyNode node) {
	auto id = MapUtil::getInstance()->getTargetNodeId(node);
	auto obj = Config::getInstance()->getOtherEntityById(id);
	std::string addname = "";
	auto valuemap = FileUtils::getInstance()->getValueMapFromFile(FILE_NAME::t_chinese_xml);
	if (obj.stype == EQUIP_TYPE::ATTACK)
	{
		DataManager::getInstance()->addHeroAttack(obj.add);
		addname = valuemap["attack"].asString();
	}
	else {
		DataManager::getInstance()->addHeroDefend(obj.add);
		addname = valuemap["defend"].asString();
	}
	std::string tips = valuemap["assist"].asString();
	std::string content = StringUtils::format(tips.c_str(), obj.name.c_str(), addname.c_str(), obj.add);
	Utils::getInstance()->addTipsDialog(this, content, [this,node]() {
		_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::ARROW_HIDE);
		MapUtil::getInstance()->setTargetTileVisible(node, false, true);
	});
}
void GameScene::heroAddEquip(MyNode node)
{
	SoundUtil::getInstance()->playEffect(AUDIO_EFFECT_ENUM::AU_EQUIP);
	auto id = MapUtil::getInstance()->getTargetNodeId(node);
	auto obj = Config::getInstance()->getOtherEntityById(id);
	std::string addname = "";
	auto valuemap = FileUtils::getInstance()->getValueMapFromFile(FILE_NAME::t_chinese_xml);
	if (obj.stype==EQUIP_TYPE::ATTACK)
	{
		//DataManager::getInstance()->addHeroAttack(obj.add);
		addname = valuemap["attack"].asString();
	}
	else {
		//DataManager::getInstance()->addHeroDefend(obj.add);
		addname = valuemap["defend"].asString();
	}
	DataManager::getInstance()->handleAllAttr(obj);
	std::string tips = valuemap["equip"].asString();
	std::string content = StringUtils::format(tips.c_str(), obj.name.c_str(), addname.c_str(), obj.add);
	Utils::getInstance()->addTipsDialog(this,content);
}
void GameScene::heroAddKey(MyNode node)
{
	auto id = MapUtil::getInstance()->getTargetNodeId(node);
	auto obj = Config::getInstance()->getOtherEntityById(id);
	DataManager::getInstance()->handleAllAttr(obj);

	std::string str = Config::getInstance()->getChineseContent("tipAdd");
	std::string name = "";
	if (obj.stype==KEY_TYPE::RED)
	{
		name = Config::getInstance()->getChineseContent("redKey");
	}
	else if (obj.stype==KEY_TYPE::YELLOW) {
		name = Config::getInstance()->getChineseContent("yellowKey");
	}
	else if (obj.stype==KEY_TYPE::BLUE)
	{
		name = Config::getInstance()->getChineseContent("blueKey");
	}else{
		name = Config::getInstance()->getChineseContent("allKey");
	}
	
	std::string content = StringUtils::format(str.c_str(), name.c_str(), obj.add);
	Utils::getInstance()->addTipsLabel(content);

	/*DataManager::getInstance()->addHeroKey(obj.stype, obj.add);*/
	SoundUtil::getInstance()->playEffect(AUDIO_EFFECT_ENUM::AU_KEY);
}

void GameScene::heroGoShop(MyNode node)
{
	auto id = MapUtil::getInstance()->getTargetNodeId(node);
	auto shopinfo = Config::getInstance()->getShopEntityById(id);
	auto shop = ShopComponent::create();
	shop->updateData(shopinfo);
	shop->setPosition(LocationUtils::getInstance()->CENTER);
	this->addChild(shop);
	//isContinue = false;
	this->m_hero->changeHeroDirection(DIRECTION_ENUM::STAND);
	_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::TARGET_NODE_CHANGE);
	_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::ARROW_HIDE);
}

void GameScene::heroDoFight(MyNode node){
	//调用英雄的战斗，并计算值。然后调用回调函数。
	//1.todo caculate hero and monsters hurt
	auto id = MapUtil::getInstance()->getTargetNodeId(node);
	Monster monster = Config::getInstance()->getMonsterById(id);
	int heroCurBlood = DataManager::getInstance()->m_nowblood;
	int blood = DataManager::getInstance()->caculateFightHurt(monster);
	//NotificationCenter::getInstance()->postNotification(NOTIFICATION_TYPE::HERO_BLOOD_UPDATE);
	//2.todo decade hero next action
	if (blood>0)
	{
		auto fightCB = [this,monster,blood,heroCurBlood]() {
			this->m_hero->playFightAnima();
			int heroHurt = heroCurBlood - blood;
			
			SoundUtil::getInstance()->playEffect(AUDIO_EFFECT_ENUM::AU_FIGHT);
			auto delay_time = DelayTime::create(Constant::HERO_FIGHT_TINE);
			auto callfunc = CallFunc::create([this, monster, blood,heroHurt]() {
				DataManager::getInstance()->addHeroGoldAndSoul(monster.m_gold, monster.m_soul);
				DataManager::getInstance()->setHeroNowBlood(blood);
				if (monster.m_stype == MONSTER_TYPE::BOOS)
				{
					
					auto valuemap = FileUtils::getInstance()->getValueMapFromFile(FILE_NAME::t_chinese_xml);
					auto str = valuemap["win"].asString();
					Utils::getInstance()->addTipsDialog(this, str, [this]() {
						//send notice win
						_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::GAME_WIN);
					});
				}
				else {
					if (heroHurt > 0)
					{
						auto label = LabelAtlas::create(StringUtils::format(":%d", heroHurt).c_str(), "res/num_cutHP.png", 24, 33, '0');
						label->setPosition(this->m_hero->getPosition() + Vec2(0.0f, 50.0f));
						this->m_map->addChild(label, 4);

						auto action = JumpBy::create(0.6f, Vec2(50.0f, 0), 100, 1);
						auto action_2 = RemoveSelf::create();
						label->runAction(Sequence::create(action, action_2, nullptr));
					}
					Utils::getInstance()->addTipsLabel(Config::getInstance()->getChineseContent("winFight"));
					this->m_fightCallback();
				}
			});
			auto seq = Sequence::create(delay_time, callfunc, nullptr);
			this->m_hero->runAction(seq);
		};
		if (!node.isEquls(m_last_node))
		{
			auto valuemap = FileUtils::getInstance()->getValueMapFromFile(FILE_NAME::t_chinese_xml);
			auto rootnode = Utils::getInstance()->getRootNode();
			auto content = StringUtils::format(valuemap["fight"].asString().c_str(),monster.m_name.c_str());
			this->m_hero->changeHeroDirection(DIRECTION_ENUM::STAND,false);
			//this->m_hero->getDirection();
			Utils::getInstance()->addTwoButtonDialog(rootnode, content, fightCB, [this]() {
				_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::ARROW_HIDE);
				_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::TARGET_NODE_CHANGE);
			});
		}
		else {
			fightCB();
		}
	}
	else {
		//DataManager::getInstance()->setIsCanTouch(false);
		//log("------------set touch false--------------");
		_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::TARGET_NODE_CHANGE);
		_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::ARROW_HIDE);
		auto valuemap = FileUtils::getInstance()->getValueMapFromFile(FILE_NAME::t_chinese_xml);
		Utils::getInstance()->addTipsDialog(this,valuemap["lost"].asString());
		this->m_hero->changeHeroDirection(DIRECTION_ENUM::STAND);
	}
}


bool GameScene::judgeNodeType(bool iscur,std::vector<MyNode> path, Point nextnode, MyNode targetnode)
{
	bool isContinue = true;
	auto type = MapUtil::getInstance()->judgeMainLayerNodeType(targetnode);
	if (iscur)
	{
		switch (type)
		{
		case  MIAN_TYPE_ENUM::NONE:
			break;
		case MIAN_TYPE_ENUM::KEY:
			log("is key ");
			//tod add key and remove the key;
			this->heroAddKey(targetnode);
			MapUtil::getInstance()->setTargetTileVisible(targetnode,false,true);
			break;
		case MIAN_TYPE_ENUM::BLOOD:
			log("is blood");
			this->heroAddBlood(targetnode);
			MapUtil::getInstance()->setTargetTileVisible(targetnode,false,true);
			break;
		case MIAN_TYPE_ENUM::DIAMONDS:
			log("is diamonds");
			this->heroAddDiamond(targetnode);
			MapUtil::getInstance()->setTargetTileVisible(targetnode,false,true);
			break;
		case MIAN_TYPE_ENUM::EQUIP:
			log("is equip");
			//aaa
			this->heroAddEquip(targetnode);
			MapUtil::getInstance()->setTargetTileVisible(targetnode, false, true);
			break;
		default:
			break;
		}
	}
	else{
		switch (type)
		{
		case MIAN_TYPE_ENUM::NONE:
			break;
		case  MIAN_TYPE_ENUM::MONSTERS:
			log("monster");
			this->m_fightCallback = [this, path, nextnode, targetnode](){
				MapUtil::getInstance()->setTargetTileVisible(targetnode,false,true);
				//如果在战斗的过程中，点击地图的其他路线的话，人还是在战斗的状态
				//但是战斗完了之后，会调转方向。原因是这里调用heromovetonext
				//会判断之后有没有移动，如果移动了，就调用另一个路径了。
				this->heroMoveToNext(path, nextnode);
			};
			SoundUtil::getInstance()->playRun(false);
			this->heroDoFight(targetnode);

			isContinue = false;
			break;
		case  MIAN_TYPE_ENUM::DOOR:
			log("is door");
			this->m_doorCallbakc = [this, path, nextnode, targetnode](){
				//todo save status ,and open a windom;
				MapUtil::getInstance()->setTargetTileVisible(targetnode, false,true);
				//nextNode = MyNode();
				this->heroMoveToNext(path, nextnode);
			};
			this->heroOpenDoor(targetnode);
			isContinue = false;
			break;
		case MIAN_TYPE_ENUM::STAIRS: {
			log("is stairs");
			auto type = MapUtil::getInstance()->judgeStairsType(targetnode);
			if (!targetnode.isEquls(m_last_node))
			{
				std::string name = "";
				auto valuemap = FileUtils::getInstance()->getValueMapFromFile(FILE_NAME::t_chinese_xml);
				if (type==STAIRS_TYPE_ENUM::DOWN)
				{
					name = valuemap["down"].asString();
				}
				else {
					name = valuemap["up"].asString();
				}
				Utils::getInstance()->addTwoButtonDialog(Utils::getInstance()->getRootNode(),
					name,
					[this,type]() {	
					_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::SCENE_CHANGE, (void*)type);
				}, [this]() {
					this->m_hero->changeHeroDirection(DIRECTION_ENUM::STAND);
					_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::ARROW_HIDE);
				});
			}
			else {
				_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::SCENE_CHANGE, (void*)type);
			}
			isContinue = false;
			break;
		}
		case MIAN_TYPE_ENUM::SHOP: {
			log("is shop");
			this->heroGoShop(targetnode);
			isContinue = false;
			break;
		}
		case MIAN_TYPE_ENUM::ASSIST:
		{
			log("is assist");
			this->heroAssist(targetnode);
			isContinue = false;
			
			this->m_hero->changeHeroDirection(DIRECTION_ENUM::STAND);
			_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::TARGET_NODE_CHANGE);
			break;
		}
		default:
			break;
		}
		
	}
	return isContinue;
}
void GameScene::heroMoveToNext(std::vector<MyNode> path, Point nextP){
	if (!m_moveChange){

		//todo change hero direction
		MyNode curnode = MapUtil::getInstance()->convertCocosPointToTileNode(this->m_hero->getPosition());
		//judge cur node status 
		bool isContinue = this->judgeNodeType(true,path, nextP, curnode);
		if (!isContinue||this->m_hero->getStopMove())
		{
			this->m_hero->setStopMove(false);
			SoundUtil::getInstance()->playRun(false);
			return;
		}
		MyNode nextNode = MapUtil::getInstance()->convertCocosPointToTileNode(nextP);
		this->changeHeroDirection(curnode, nextNode);

		isContinue = this->judgeNodeType(false,path, nextP, nextNode);
		if (!isContinue)
		{
			SoundUtil::getInstance()->playRun(false);
			return;
		}
		////todo check nextnode status
		//auto type = MapUtil::getInstance()->judgeMainLayerNodeType(nextNode);
		//switch (type)
		//{
		//case MIAN_TYPE_ENUM::NONE:
		//	break;
		//case MIAN_TYPE_ENUM::MONSTERS:
		//	//todo fight
		//	this->m_fightCallback = [this, path, nextP, nextNode](){
		//		MapUtil::getInstance()->setTargetTileVisible(nextNode);
		//		//如果在战斗的过程中，点击地图的其他路线的话，人还是在战斗的状态
		//		//但是战斗完了之后，会调转方向。原因是这里调用heromovetonext
		//		//会判断之后有没有移动，如果移动了，就调用另一个路径了。
		//		this->heroMoveToNext(path, nextP);
		//	};

		//	this->heroDoFight(nextNode);
		//	
		//	return;
		//	break;
		//case MIAN_TYPE_ENUM::DOOR:
		//	log("is door");
		//	this->m_doorCallbakc = [this,path,nextP,nextNode](){
		//		//todo save status ,and open a windom;
		//		MapUtil::getInstance()->setTargetTileVisible(nextNode,false);
		//		//nextNode = MyNode();
		//		this->heroMoveToNext(path,nextP);
		//	};
		//	this->heroOpenDoor(nextNode);
		//	return;
		//	break;
		//default:
		//	break;
		//}
		if (path.size() == 0){
			return;
		}
		/*this->m_heroIsMoveing = true;*/
		this->m_moveChange = false;
		float time = this->m_hero->getPosition().distance(nextP) / this->m_heroMoveSpeed;
		auto act_mt1 = MoveTo::create(time, nextP);
		//防止边界问题。
		path.erase(path.begin());

		if (path.size() <= 0){
			//return;
			auto act_call2 = CallFunc::create([this, path, nextP](){
				this->m_hero->m_heroisMoving = false;
				//这里还要调用一次，边界测试的结果。因为可能到了边界才按下按钮
				
				this->removePath(true);
				this->heroMoveToNext(path, nextP);
				SoundUtil::getInstance()->playRun(false);
				
			});
			this->m_hero->runAction(Sequence::create(act_mt1, act_call2, nullptr));

		}
		else{
			//todo compete next node
			auto nextNode = MapUtil::getInstance()->convertTileNodeToCocosPoint(path[0]);
			nextNode.x = nextNode.x + this->m_hero->getContentSize().width / 2;
			nextNode.y = nextNode.y + this->m_hero->getContentSize().width / 2;
			//todo run action
			auto act_call2 = CallFunc::create([this,path,nextNode]() {
				SoundUtil::getInstance()->playRun(true);
				this->heroMoveToNext(path,nextNode);
				this->removePath(true);
				
			});
			//auto act_call2 = CallFunc::create(CC_CALLBACK_0(GameScene::heroMoveToNext, this, path, nextNode));
			this->m_hero->runAction(Sequence::create(act_mt1, act_call2, nullptr));
		}
	}
	else{
		//todo 
		//this->m_moveCallback();
		this->m_moveChange = false;
		this->m_moveCallback();
	}
}

void GameScene::initNotification(){
	//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent();

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerCustom::create(NOTIFICATION_TYPE::TARGET_NODE_CHANGE, [this](Ref* ref){
		this->m_last_node.m_x = -1;
		this->m_last_node.m_y = -1;
	});
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto sceneChangeListener = EventListenerCustom::create(NOTIFICATION_TYPE::SCENE_CHANGE, [this](EventCustom* event) {
		auto flag = (int)event->getUserData();
		STAIRS_TYPE_ENUM curtype = (STAIRS_TYPE_ENUM)flag;
		DataManager::getInstance()->setHeroFloorStatus(curtype);
		/*if (curtype== STAIRS_TYPE_ENUM::UP)
		{
			DataManager::getInstance()->m_cur_floor++;
		}
		else {
			DataManager::getInstance()->m_cur_floor--;
		}*/
		SoundUtil::getInstance()->playRun(false);
		SoundUtil::getInstance()->playEffect(AUDIO_EFFECT_ENUM::AU_FLOOR);
		Director::getInstance()->replaceScene(GameScene::createScene());
	});
	dispatcher->addEventListenerWithSceneGraphPriority(sceneChangeListener, this);


	auto jumpSceneListener = EventListenerCustom::create(NOTIFICATION_TYPE::SCENE_JUMP_TO_TARGET_FLOOR, [this](EventCustom* event) {
		int targetFloor = (int)event->getUserData();
		DataManager::getInstance()->setTargetFloor(targetFloor);
		SoundUtil::getInstance()->playEffect(AUDIO_EFFECT_ENUM::AU_FLOOR);
		Director::getInstance()->replaceScene(GameScene::createScene());
	});

	dispatcher->addEventListenerWithSceneGraphPriority(jumpSceneListener,this);

	auto gamewin = EventListenerCustom::create(NOTIFICATION_TYPE::GAME_WIN, [this](EventCustom* event) {
		log("to menu scene");
		auto scene = MainScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	dispatcher->addEventListenerWithSceneGraphPriority(gamewin,this);

	auto arrowHide = EventListenerCustom::create(NOTIFICATION_TYPE::ARROW_HIDE, [this](EventCustom* event) {
		this->removePath(false);
	});
	dispatcher->addEventListenerWithSceneGraphPriority(arrowHide,this);

	auto keylistener = EventListenerKeyboard::create();

	keylistener->onKeyReleased = [](EventKeyboard::KeyCode keycode, cocos2d::Event *event) {
		if (DataManager::getInstance()->getExitShow())
		{
			return;
		}
		DataManager::getInstance()->setExitShow(true);
		switch (keycode) {
		case cocos2d::EventKeyboard::KeyCode::KEY_BACKSPACE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
		{
			auto str = Config::getInstance()->getChineseContent("exit");
			
			Utils::getInstance()->addTwoButtonDialog(Utils::getInstance()->getRootNode(), str, []() {
				//SaveUtils::getInstance()->save
				//Director::getInstance()->resume();
				SaveUtils::getInstance()->saveDataToLocal();
				Director::getInstance()->end();
			}, []() {
				//Director::getInstance()->resume/();/
				DataManager::getInstance()->setExitShow(false);
			});
			break;
		}
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keylistener, this);
	
	auto touchSallowListener = EventListenerCustom::create(NOTIFICATION_TYPE::MOVE_TOUCH_LISTENER, [this](EventCustom* event) {
		bool flag = (bool)event->getUserData();
		this->isMoveListenerSwallow = flag;
		//this->removePath(false);
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchSallowListener, this);
}