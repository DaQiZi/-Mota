#ifndef __CONFIG_H_
#define __CONFIG_H_
#include<string>
//#include<iostream>
#include"cocos2d.h"
#include"Constant.h"
//#include"cocos2d/external/json/document.h"
//#include"cocos2d/external/json/rapidjson.h"
#include "json/document.h"
#include "json/rapidjson.h"
//#include"rapidjson.h"
//#include "cocos2d/external/json/document.h"
#include"Monster.h"
//using namespace std;

class HeroConfig{
private:
	std::string hero_anima_arr[9];
public:
	static HeroConfig* getInstance();
	HeroConfig();
	std::string getAnimationName(HERO_ANIMATION_ENUM);

};
//class Monster;
class OtherEntity;
class ShopInfoEntity;
class ShopEntity;
struct ShopInfoStruct;
class Config{
public:
	static Config* getInstance();
	Config();
	void initAllDoc(rapidjson::Document& doc, std::string filename);
	Monster getMonsterById(std::string id);
	std::vector<Monster> getMonsterList();
	OtherEntity getOtherEntityById(std::string id);
	ShopInfoEntity getShopInfoEntityById(std::string id);
	ShopEntity  getShopEntityById(std::string id);
	std::string getChineseContent(std::string key);
private:
	//std::string m_monsters_json;
	rapidjson::Document m_monsters_doc;
	rapidjson::Document m_otherEntity_doc;
	rapidjson::Document m_shop_list_doc;
	rapidjson::Document m_shop_doc;
	cocos2d::ValueMap m_chineseMap;
};

struct ShopInfoStruct 
{
	std::string id;
	int num;
};
#endif