 //#pragma once
//#pragma execution_character_set("utf-8")
#include"Config.h"
#include"cocos2d.h"
#include"Constant.h"
#include"Monster.h"
#include"OtherEntity.h"
#include"ShopInfoEntity.h"
#include"ShopEntity.h"
using namespace cocos2d;
HeroConfig* HeroConfig::getInstance(){
	static HeroConfig config;
	return &config;
}
HeroConfig::HeroConfig(){
	hero_anima_arr[HERO_ANIMATION_ENUM::DOWN_STANE] = "Fstand";
	hero_anima_arr[HERO_ANIMATION_ENUM::DOWN_RUN] = "Frun";
	hero_anima_arr[HERO_ANIMATION_ENUM::DOWN_FIGHT] = "Ffight";
	hero_anima_arr[HERO_ANIMATION_ENUM::UP_STANE] = "Bstand";
	hero_anima_arr[HERO_ANIMATION_ENUM::UP_RUN] = "Brun";
	hero_anima_arr[HERO_ANIMATION_ENUM::UP_FIGHT] = "Bfight";
	hero_anima_arr[HERO_ANIMATION_ENUM::L_STANE] = "Sstand";
	hero_anima_arr[HERO_ANIMATION_ENUM::L_RUN] = "Srun";
	hero_anima_arr[HERO_ANIMATION_ENUM::L_FIGHT] = "Sfight";
}

std::string HeroConfig::getAnimationName(HERO_ANIMATION_ENUM name){
	return hero_anima_arr[name];
}

Config* Config::getInstance(){
	static Config config;
	return &config;
}

Config::Config(){
	//this->m_monsters_json = cocos2d::FileUtils::getInstance()->getStringFromFile(FILE_NAME::t_monsters_json);
	
	this->initAllDoc(m_monsters_doc, FILE_NAME::t_monsters_json);
	this->initAllDoc(m_otherEntity_doc, FILE_NAME::t_otherEntity_json);
	this->initAllDoc(m_shop_list_doc, FILE_NAME::t_shop_list_json);
	this->initAllDoc(m_shop_doc, FILE_NAME::t_shop_json);
	this->m_chineseMap = FileUtils::getInstance()->getValueMapFromFile(FILE_NAME::t_chinese_xml);
	log("config done");
}

void Config::initAllDoc(rapidjson::Document& doc,std::string filename){
	std::string content = FileUtils::getInstance()->getStringFromFile(filename);
	doc.Parse(content.c_str());
}

Monster Config::getMonsterById(std::string id){
	Monster m(this->m_monsters_doc,id);
	return m;
}

std::vector<Monster> Config::getMonsterList()
{
	std::vector<Monster> list;
	list.reserve(10);
	for (rapidjson::Value::ConstMemberIterator iter = this->m_monsters_doc.MemberBegin();iter != this->m_monsters_doc.MemberEnd();++iter)
	{
		auto id = iter->name.GetString();
		Monster m(this->m_monsters_doc,id);
		list.push_back(m);
		//cocos2d::log("------------>   %s", id);
	}
	return list;
}

OtherEntity Config::getOtherEntityById(std::string id)
{
	OtherEntity b(this->m_otherEntity_doc,id);
	return b;
}

ShopInfoEntity Config::getShopInfoEntityById(std::string id)
{
	ShopInfoEntity info(this->m_shop_list_doc,id);
	return info;
}

ShopEntity Config::getShopEntityById(std::string id)
{

	return ShopEntity(this->m_shop_doc,id);
}

std::string Config::getChineseContent(std::string key)
{
	return this->m_chineseMap[key].asString();
}

