#include"ShopInfoEntity.h"

using namespace rapidjson;
ShopInfoEntity::ShopInfoEntity(rapidjson::Document & doc, const std::string id)
{
	rapidjson::Value &value = doc[id.c_str()];
	auto obj = value.GetObject();
	this->icon = value["icon"].GetString();
	this->desc = value["desc"].GetString();
	this->cost = value["cost"].GetInt();
	this->costType = value["costType"].GetInt();
	this->reward = value["reward"].GetString();

	this->initShopinfoArr();
}

ShopInfoEntity::ShopInfoEntity()
{
}

void ShopInfoEntity::initShopinfoArr()
{
	std::vector<ShopInfoStruct> shoplist;
	rapidjson::Document tempdoc;
	tempdoc.Parse(this->reward.c_str());
	auto tempvlaue = tempdoc.GetArray();
	cocos2d::log("---------------shop list info-----------------");
	for (int i = 0;i < tempvlaue.Size();i++) {
		//cocos2d::log("id = %s num = %d",tempvlaue[i][0].GetString(),tempvlaue[i][1].GetInt());
		ShopInfoStruct shop;
		int tempstr = tempvlaue[i][0].GetInt();
		shop.id = cocos2d::StringUtils::format("%d", tempstr);
		shop.num = tempvlaue[i][1].GetInt();
		shoplist.push_back(shop);
		cocos2d::log("%s -----------------> %d", shop.id.c_str(), shop.num);
	}
	this->shopinfoArr = shoplist;
}
