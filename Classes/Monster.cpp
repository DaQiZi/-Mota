#include"cocos2d.h"
#include"Monster.h"
#include "json/document.h"
#include "json/rapidjson.h"


using namespace rapidjson;
//using namespace cocos2d;
void Monster::initData(std::string){

}

Monster::Monster(rapidjson::Document &doc, const std::string id){
	CCASSERT(doc.HasMember(id.c_str()), "doc member not find");
	rapidjson::Value &value = doc[id.c_str()];
	auto obj = value.GetObject();
	CCASSERT(value.IsObject(),"doc not object");
	this->m_id = cocos2d::StringUtils::toString(obj["id"].GetInt()) ;
	this->m_blood = obj["blood"].GetInt();
	this->m_attack = obj["attack"].GetInt();
	this->m_stype = obj["stype"].GetInt();
	this->m_defence = obj["defence"].GetInt();
	this->m_gold = obj["gold"].GetInt();
	this->m_soul = obj["soul"].GetInt();
	this->m_name = obj["name"].GetString();
	this->m_iconName = obj["icon"].GetString();
	this->m_desc = obj["desc"].GetString();
	//cocos2d::log("monster info =   %d %d  %d", this->m_blood, this->m_blood, this->m_defence);
	/*auto obj = doc[id.c_str()].GetObjectW(id.c_str());*/
}