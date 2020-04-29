#include"ShopEntity.h"
using namespace rapidjson;
ShopEntity::ShopEntity(rapidjson::Document & doc, std::string id)
{
	auto &value = doc[id.c_str()];
	auto obj = value.GetObject();
	//this->id = value["id"].GetString();
	this->type = value["type"].GetInt();
	this->name = value["name"].GetString();
	this->icon = value["icon"].GetString();
	this->desc = value["desc"].GetString();
	this->shoplist = value["shoplist"].GetString();
	this->initShopListArr();
}

void ShopEntity::initShopListArr()
{
	rapidjson::Document tempdoc;
	tempdoc.Parse(this->shoplist.c_str());
	std::vector<std::string> shoplist;

	auto tempvlaue = tempdoc.GetArray();
	cocos2d::log("------------------shop id------------------");
	for (int i = 0;i < tempvlaue.Size();i++) {
		//cocos2d::log("id = %s num = %d",tempvlaue[i][0].GetString(),tempvlaue[i][1].GetInt());
		int id = tempvlaue[i].GetInt();
		std::string idStr = cocos2d::StringUtils::format("%d", id);
		shoplist.push_back(idStr);
		cocos2d::log("%d", id);
	}
	this->shoplistArr = shoplist;
}
