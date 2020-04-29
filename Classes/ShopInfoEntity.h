#ifndef __SHOPINFOENTITY_H_  
#define __SHOPINFOENTITY_H_
#include"Config.h"
#include "json/document.h"
#include "json/rapidjson.h"

class ShopInfoEntity {
public:
	std::string icon;
	std::string desc;
	int costType;
	int cost;
	std::string reward;
	std::vector<ShopInfoStruct> shopinfoArr;
public:
	ShopInfoEntity(rapidjson::Document &doc,const std::string id);
	ShopInfoEntity();
private:
	void initShopinfoArr();
};
#endif