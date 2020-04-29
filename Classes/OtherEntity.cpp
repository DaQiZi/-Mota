#include "cocos2d.h"
#include"OtherEntity.h"
//using namespace cocos2d;
using namespace rapidjson;
void OtherEntity::initData(std::string id)
{
}

OtherEntity::OtherEntity(rapidjson::Document & doc, const std::string id)
{
	CCASSERT(doc.HasMember(id.c_str()), "doc member not find");
	rapidjson::Value &value = doc[id.c_str()];
	auto obj = value.GetObject();
	CCASSERT(value.IsObject(), "doc not object");
	this->type = obj["type"].GetInt();
	this->id = obj["id"].GetInt();
	this->add = obj["add"].GetInt();
	this->stype = obj["stype"].GetInt();
	this->name = obj["name"].GetString();
	//cocos2d::log("monster info =   %d %d  %d", this->m_blood, this->m_blood, this->m_defence);
}
