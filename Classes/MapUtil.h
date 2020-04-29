//#pragma once
//#pragma execution_character_set("utf-8")
#ifndef _MAP_UTILS_H_
#define _MAP_UTILS_H_
#include"AStar.h"
#include"cocos2d.h"
//#include"Constant.h"
class MapUtil{
private:
	struct TileSize{
		int width;
		int height;
	};
public:
	MyNode convertCocosPointToTileNode(Point p);
	Point convertTileNodeToCocosPoint(MyNode node);
	static MapUtil* getInstance();
	void initMapSize(cocos2d::Size size, cocos2d::Size mapSize);
	bool judgeNodeLegal(MyNode curNode);
	bool judgeNodeIsBlock(MyNode curNode);
	MIAN_TYPE_ENUM judgeMainLayerNodeType(MyNode curNode);
	STAIRS_TYPE_ENUM judgeStairsType(MyNode curNode);
	std::string getTargetNodeId(MyNode curNode);
	void setMap(experimental::TMXTiledMap* map);
	void setTargetTileVisible(MyNode node, bool flag=false, bool needSave=false);
	void setMainLayerAnimation(Sprite* spr,bool isChange);
	void initImageReplaceAndAnimation(experimental::TMXTiledMap* map=nullptr,bool playAction=true);
	void initMainLayerVisible();
	Point convertMyNodeToCoord(MyNode);
	MyNode convertCoordToMyNode(MyNode);

	void updateMapVisible(experimental::TMXTiledMap* map,int floor);

	//get all can see monster id;
	std::vector<std::string> getMapMonsterList(bool isall=false);
	//about book info
	void checkMapBookInfo();
	bool judgeNodeIsAddCost(MyNode curNode);
private:
	TileSize m_tileSize;
	Size m_mapSize;
	experimental::TMXTiledMap* m_map;
	experimental::TMXLayer* m_map_layer;
	experimental::TMXLayer* m_main_layer;
public:
	Vec2 getTileSize(){
		return Vec2(m_tileSize.width,m_tileSize.height);
	}
};


#endif 