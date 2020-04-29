#ifndef __SHOPENTITY_H_  
#define __SHOPENTITY_H_
#include"Config.h"
#include "json/document.h"
#include "json/rapidjson.h"
class ShopEntity {
public:
	std::string id;
	int type;
	std::string name;
	std::string icon;
	std::string desc;
	std::string shoplist;
	std::vector<std::string> shoplistArr;
public:
	ShopEntity(rapidjson::Document& doc,std::string id);
private:
	void initShopListArr();
};
#endif