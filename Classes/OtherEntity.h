#ifndef __OTHERENTITY_H_  
#define __OTHERENTITY_H_

#include "json/document.h"
#include "json/rapidjson.h"
class OtherEntity{
public:
	int type;
	int id;
	int stype;
	int add;
	std::string name;
public:
	void initData(std::string id);
	OtherEntity(rapidjson::Document &doc, const std::string id);
};

#endif