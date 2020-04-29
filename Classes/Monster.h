#ifndef __MONSTER_H_  
#define __MONSTER_H_
#include"Entity.h"
#include "json/document.h"
#include "json/rapidjson.h"
class Monster : public Entity{
public:
	void initData(std::string);
	Monster(rapidjson::Document &doc,const std::string id);
	int m_gold;
	int m_soul;
	int m_stype;
	std::string m_id;
	std::string m_name;
	std::string m_iconName;
	std::string m_desc;
};
#endif