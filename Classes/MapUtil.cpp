//#pragma once
//#pragma execution_character_set("utf-8")
#include"MapUtil.h"
#include"Constant.h"
#include"DataManager.h"
#include"SaveUtils.h"
#include"cocostudio/CocoStudio.h"
MyNode MapUtil::convertCocosPointToTileNode(Point p){
	MyNode node;
	node.m_x = p.x / this->m_tileSize.width;
	node.m_y = p.y / this->m_tileSize.height;
	return node;
}
Point MapUtil::convertTileNodeToCocosPoint(MyNode node){
	Point p;
	p.x = node.m_x*this->m_tileSize.width;
	p.y = node.m_y*this->m_tileSize.height;
	return p;
}
MapUtil* MapUtil::getInstance(){
	static MapUtil instance;
	return &instance;
}
void MapUtil::initMapSize(cocos2d::Size tileSize,cocos2d::Size mapSize){
	this->m_tileSize.width = (int)tileSize.width;
	this->m_tileSize.height = (int)tileSize.height;
	this->m_mapSize.width = mapSize.width;
	this->m_mapSize.height = mapSize.height;

	//TextureCache::getInstance()->
}

bool MapUtil::judgeNodeLegal(MyNode curNode){
	if (curNode.m_x<0||curNode.m_x>=this->m_mapSize.width){
		return false;
	}
	if (curNode.m_y<0||curNode.m_y>=this->m_mapSize.height){
		return false;
	}
	if (this->judgeNodeIsBlock(curNode)){
		return false;
	}
	return true;
}

void MapUtil::setMap(experimental::TMXTiledMap* map){
	this->m_map = map;
	this->m_map_layer = this->m_map->getLayer(Constant::BLOCK_LAYER_NAME);
	this->m_main_layer = this->m_map->getLayer(Constant::MAIN_LAYER_NAME);
	this->initMainLayerVisible();
	//MessageBox("1","");
	this->initImageReplaceAndAnimation();
	//this->initMainLayerAnima();
	this->checkMapBookInfo();
}
//void MapUtil::initMainLayerAnima(){
//	Size size = this->m_map->getMapSize();
//	for (size_t i = 0; i < size.width; i++)
//	{
//		for (size_t j = 0; j < size.height; j++)
//		{
//			auto gid = this->m_main_layer->getTileGIDAt(Vec2(i, j));
//			auto tile = this->m_main_layer->getTileAt(Vec2(i,j));
//			auto value = this->m_map->getPropertiesForGID(gid);
//			if (!value.isNull())
//			{
//				auto valueMap = value.asValueMap();
//				if (valueMap.find(Constant::MAIN_TYPE) != valueMap.end()&&tile->isVisible())
//				{
//					int type = valueMap[Constant::MAIN_TYPE].asInt();
//
//					switch (type)
//					{
//					case MIAN_TYPE_ENUM::MONSTERS:
//					{
//						//auto texture = TextureCache::getInstance()->addImage("rw34.png");
//						////auto frame = SpriteFrame::createWithTexture(texture,);
//						////texture->getContentSize();
//						///*tile->setTexture(texture);*/
//						////tile->setSpriteFrame();
//						//tile->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3.png"));
//						//tile->setScale(1.0f);
//						auto action1 = ScaleTo::create(0.5f, 0.8f, 1.2f);
//						auto action2 = ScaleTo::create(0.5f, 1.0f);
//						auto seq = Sequence::create(action1, action2, nullptr);
//						tile->runAction(RepeatForever::create(seq));
//						tile->setAnchorPoint(Vec2(0.5f,0));
//						//tile->setPositionX(tile->getPositionX() + this->m_tileSize.width/2);
//						
//						break;
//					}
//					default:
//						break;
//					}
//				}
//			}
//		}
//	}
//}

void MapUtil::setMainLayerAnimation(Sprite* spr, bool isChange)
{
	auto action1 = ScaleTo::create(0.5f, 0.8f, 1.2f);
	auto action2 = ScaleTo::create(0.5f, 1.0f);
	auto seq = Sequence::create(action1, action2, nullptr);
	spr->runAction(RepeatForever::create(seq));
	spr->setAnchorPoint(Vec2(0.5f, 0));
	if (!isChange)
	{
		spr->setPositionX(spr->getPositionX() + this->m_tileSize.width/2);
	}
}

void MapUtil::initImageReplaceAndAnimation(experimental::TMXTiledMap* map, bool playAction)
{
	auto imgValuemap = FileUtils::getInstance()->getValueMapFromFile(FILE_NAME::t_img_judge_xml);
	Size size = this->m_map->getMapSize();
	//MessageBox("2", "");
	experimental::TMXLayer* templayer = nullptr;
	if (map==nullptr)
	{
		templayer = this->m_main_layer;
		map = this->m_map;
	}
	else {
		templayer = map->getLayer(Constant::MAIN_LAYER_NAME);
	}
	//
	for (size_t i = 0; i < size.width; i++)
	{
		for (size_t j = 0; j < size.height; j++)
		{
			auto gid = templayer->getTileGIDAt(Vec2(i, j));
			auto tile = templayer->getTileAt(Vec2(i, j));
			auto value = map->getPropertiesForGID(gid);
			if (tile&&!tile->isVisible())
			{
				continue;
			}
			if (!value.isNull())
			{
				auto valueMap = value.asValueMap();
				bool isChange = false;
				if (valueMap.find(Constant::MAIN_ID) != valueMap.end()&&tile->isVisible())
				{
					std::string id = valueMap[Constant::MAIN_ID].asString();
					if (imgValuemap.find(id)!=imgValuemap.end())
					{
						//MessageBox("", "123");
						std::string img_name = imgValuemap[id].asString();
						auto img = SpriteFrameCache::getInstance()->getSpriteFrameByName(img_name);
						tile->setAnchorPoint(Vec2(0.5f,0));
						tile->setSpriteFrame(img);
						tile->setPositionX(tile->getPositionX() + this->m_tileSize.width / 2);
						isChange = true;
					}
				}
				if (valueMap.find(Constant::MAIN_TYPE)!=valueMap.end()&&tile->isVisible())
				{
					int type = valueMap[Constant::MAIN_TYPE].asInt();
					
					if (type==MIAN_TYPE_ENUM::MONSTERS)
					{
						std::string id = valueMap[Constant::MAIN_ID].asString();
						auto monsterInfo = Config::getInstance()->getMonsterById(id);
						if (monsterInfo.m_stype == MONSTER_TYPE::BOOS)
						{
							cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("spine/minotaus.ExportJson");
							auto boss = cocostudio::Armature::create("minotaus");
							if (playAction)
							{
								boss->getAnimation()->play("Action0");
							}
							boss->setPosition(Vec2(boss->getContentSize().width/7,0));
							tile->addChild(boss);
							//tile->setvis
							//tile->texture
						}
						else if(playAction){
							this->setMainLayerAnimation(tile, isChange);
						}
					}

				}
			}
		}
	}
}

void MapUtil::initMainLayerVisible()
{
	int floor = DataManager::getInstance()->m_cur_floor;
	ValueVector newvector= SaveUtils::getInstance()->getValueVectorByFloor(floor);
	for (auto item:newvector)
	{
		int x = item.asInt() / Constant::SAVE_LOCAL_WEIGHT;
		int y = item.asInt()%Constant::SAVE_LOCAL_WEIGHT;
		MyNode node(x,y);
		this->setTargetTileVisible(node,false,false);
	}
}

bool MapUtil::judgeNodeIsBlock(MyNode curNode){
	//todo find gid
	MyNode newnode = curNode;

	newnode.m_y = this->m_mapSize.height - curNode.m_y-1;
	
	Point p(newnode.m_x,newnode.m_y);
	auto tilegid = this->m_map_layer->getTileGIDAt(p);
	//auto valueMap = this->m_map->getPropertiesForGID(tilegid);
	// 可能这里根本就没有图片
	if (tilegid==0)
	{
		return false;
	}
	else{
		//没有必要自己再判断一次，因为block层只有障碍物啊
		return true;
		/*auto tempValueMap = valueMap.asValueMap();
		if (tempValueMap.find(Constant::BLOCK_NAME) != tempValueMap.end()){
			bool flag = tempValueMap[Constant::BLOCK_NAME].asBool();
			if (flag){
				return true;
			}
			else{
				return false;
			}
		}*/
	}
	
	return false;
}
STAIRS_TYPE_ENUM MapUtil::judgeStairsType(MyNode curNode) {
	Point p = this->convertMyNodeToCoord(curNode);
	STAIRS_TYPE_ENUM newType = STAIRS_TYPE_ENUM::UP;
	auto gid = this->m_main_layer->getTileGIDAt(p);
	auto tile = this->m_main_layer->getTileAt(p);
	auto value = this->m_map->getPropertiesForGID(gid);
	if (value.isNull() || !tile->isVisible())
	{
		return newType;
	}
	else {
		auto valueMap = value.asValueMap();
		if (valueMap.find(Constant::STAIRS_TYPE) != valueMap.end()) {
			 newType = (STAIRS_TYPE_ENUM)valueMap[Constant::STAIRS_TYPE].asInt();
		}
	}
	return newType;
}
MIAN_TYPE_ENUM MapUtil::judgeMainLayerNodeType(MyNode curNode){
	Point p = this->convertMyNodeToCoord(curNode);
	MIAN_TYPE_ENUM newType = MIAN_TYPE_ENUM::NONE;
	auto gid = this->m_main_layer->getTileGIDAt(p);
	auto tile = this->m_main_layer->getTileAt(p);
	auto value = this->m_map->getPropertiesForGID(gid);
	if (value.isNull()||!tile->isVisible())
	{
		return newType;
	}
	else
	{
		auto valueMap = value.asValueMap();
		if (valueMap.find(Constant::MAIN_TYPE)!=valueMap.end())
		{
			int type = valueMap[Constant::MAIN_TYPE].asInt();
			
			newType = (MIAN_TYPE_ENUM)type;
			/*switch (type)
			{
			case MIAN_TYPE_ENUM::MONSTERS:
				newType = MIAN_TYPE_ENUM::MONSTERS;
				break;
			case MIAN_TYPE_ENUM::DOOR:
				newType = MIAN_TYPE_ENUM::DOOR;
				break;
			case MIAN_TYPE_ENUM::KEY:
				newType = MIAN_TYPE_ENUM::KEY;
				break;
			case MIAN_TYPE_ENUM::BLOOD:
				newType = MIAN_TYPE_ENUM::BLOOD;
				break;
			case MIAN_TYPE_ENUM::DIAMONDS:
				newType = MIAN_TYPE_ENUM::DIAMONDS;
				break;
			default:
				break;
			}*/
		}
	}
	return newType;
}
std::string MapUtil::getTargetNodeId(MyNode curNode){
	auto gid = this->m_main_layer->getTileGIDAt(this->convertMyNodeToCoord(curNode));
	if (gid==0)
	{
		return "";
	}
	auto valueMap = this->m_map->getPropertiesForGID(gid).asValueMap();
	std::string id = "";
	if (valueMap.find(Constant::MAIN_ID)!=valueMap.end())
	{
		id = valueMap[Constant::MAIN_ID].asString();
	}
	return id;
}

Point MapUtil::convertMyNodeToCoord(MyNode curNode){
	MyNode newnode = curNode;
	newnode.m_y = this->m_mapSize.height - curNode.m_y - 1;
	Point p(newnode.m_x, newnode.m_y);
	return p;
}
MyNode MapUtil::convertCoordToMyNode(MyNode curNode)
{
	MyNode newNode = curNode;
	newNode.m_y = this->m_mapSize.height - curNode.m_y - 1;
	return newNode;
}
void MapUtil::updateMapVisible(experimental::TMXTiledMap * map, int floor)
{
	auto layer = map->getLayer(Constant::MAIN_LAYER_NAME);
	//int floor = DataManager::getInstance()->m_cur_floor;
	ValueVector newvector = SaveUtils::getInstance()->getValueVectorByFloor(floor);
	for (auto item : newvector)
	{
		int x = item.asInt() / Constant::SAVE_LOCAL_WEIGHT;
		int y = item.asInt() % Constant::SAVE_LOCAL_WEIGHT;
		MyNode node(x, y);
		Point p = this->convertMyNodeToCoord(node);
		auto tile = layer->getTileAt(p);
		tile->stopAllActions();
		tile->setVisible(false);
		/*this->setTargetTileVisible(node, false, false);*/
	}
}
std::vector<std::string> MapUtil::getMapMonsterList(bool isall)
{
	std::vector<std::string> list;
	list.reserve(5);
	for (int i = 0;i<this->m_mapSize.width;i++)
	{
		for (int j = 0;j<this->m_mapSize.height;j++)
		{
			MyNode node(i,j);
			auto type = this->judgeMainLayerNodeType(node);
			if (type==MIAN_TYPE_ENUM::MONSTERS)
			{
				Point p = this->convertMyNodeToCoord(node);
				auto tile = this->m_main_layer->getTileAt(p);
				auto id = this->getTargetNodeId(node);
				bool isFind = false;
				/*for (auto &item:list)
				{
					if (item==id)
					{
						isFind = true;
						break;
					}
				}*/
				if (isall)
				{
					if (std::find(list.begin(),list.end(),id)==list.end())
					{
						list.push_back(id);
					}
				}
				else {
					if (tile->isVisible() && std::find(list.begin(), list.end(), id) == list.end())
					{
						list.push_back(id);
					}
				}
				
				
			}
		}
	}
	return list;
}
void MapUtil::checkMapBookInfo()
{
	auto bookinfo = SaveUtils::getInstance()->getBookInfoList();
	auto mapMonsterList = this->getMapMonsterList(true);
	std::vector<std::string> templist;
	templist.reserve(5);
	for (auto id : mapMonsterList)
	{
		bool isfind = false;
		for (auto value : bookinfo)
		{
			if (value.asString() == id)
			{
				isfind = true;
				break;
			}
		}
		if (!isfind)
		{
			templist.push_back(id);
		}
	}
	for (auto id : templist)
	{
		bookinfo.push_back(Value(id));
	}
	SaveUtils::getInstance()->setNewBookInfoList(bookinfo);
}
bool MapUtil::judgeNodeIsAddCost(MyNode curNode)
{
	int type = this->judgeMainLayerNodeType(curNode);
	bool flag = false;
	switch (type)
	{
		case MIAN_TYPE_ENUM::MONSTERS:
			flag = true;
			break;
		case MIAN_TYPE_ENUM::SHOP:
			flag = true;
			break;
		case MIAN_TYPE_ENUM::DOOR:
			flag = true;
			break;
		case MIAN_TYPE_ENUM::STAIRS:
			flag = true;
			break;
	default:
		break;
	}
	return flag;
}
void MapUtil::setTargetTileVisible(MyNode node,bool flag, bool needSave){
	/*MyNode newnode = node;
	newnode.m_y = this->m_mapSize.height - node.m_y - 1;
	Point p(newnode.m_x, newnode.m_y);*/
	Point p = this->convertMyNodeToCoord(node);
	auto tile = this->m_main_layer->getTileAt(p);
	tile->stopAllActions();
	tile->setVisible(flag);
	
	if (needSave)
	{
		int cur_floor = DataManager::getInstance()->m_cur_floor;
		SaveUtils::getInstance()->saveTargetFloorStatus(cur_floor,node.m_x,node.m_y);
		//log("%d %d is save to local",node.m_x,node.m_y);
	}
	/*if (flag==true){
		tile->setVisible(true);
	}
	else{
		tile->set
	}*/
}
