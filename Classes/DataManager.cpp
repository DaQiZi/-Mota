#include"DataManager.h"
#include"cocos2d.h"
#include "Constant.h"
#include"OtherEntity.h"
#include"Monster.h"
//#include""
DataManager* DataManager::getInstance(){
	static DataManager instance;
	return &instance;
}

DataManager::DataManager(){

	bool isFirst = cocos2d::UserDefault::getInstance()->getBoolForKey("isFirst", true);
	if (isFirst)
	{
		cocos2d::UserDefault::getInstance()->setBoolForKey("isFirst",false);
		this->initDataDueToFirst();
	}
	else {
		this->initDataFromFile();
	}
	//this->initSettingInfo();
	/*m_key0_num = 0;
	m_key1_num = 0;
	m_key2_num = 0;
	m_money1_num = 99;
	m_money2_num = 99;
	m_attack = 30;
	m_defend = 0;
	m_nowblood = 1000;
	m_sumblood = 1000;
	m_floot_sum = 4;
	heroFloorStatus = STAIRS_TYPE_ENUM::DOWN;
	this->setArrivalFloor(2);
	this->setHeroIsFight(false);
	m_cur_floor = cocos2d::UserDefault::getInstance()->getIntegerForKey(SAVE_TO_LOCAL::GET_CUR_FLOOR.c_str(), 1);
	*/
}

void DataManager::setHeroNowBlood(int nowblood){
	this->m_nowblood = nowblood;
	
	//cocos2d::EventCustom myevent(NOTIFICATION_TYPE::HERO_BLOOD_UPDATE);
	///cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(NOTIFICATION_TYPE::HERO_INFO_VIEW_UPDATE);
	this->sendUpdataHeroView();
}

void DataManager::setHeroFloorStatus(STAIRS_TYPE_ENUM type)
{
	if (type == STAIRS_TYPE_ENUM::UP)
	{
		this->m_cur_floor++;
		if (this->m_cur_floor>this->getArrivalFloor())
		{
			this->setArrivalFloor(this->m_cur_floor);
		}
	}
	else {
		this->m_cur_floor--;
	}
	this->heroFloorStatus = type;
}

void DataManager::setTargetFloor(int floor)
{
	this->m_cur_floor = floor;
	if (floor==1)
	{
		this->heroFloorStatus = STAIRS_TYPE_ENUM::DOWN;
	}
	else {
		this->heroFloorStatus = STAIRS_TYPE_ENUM::UP;
	}
}

int DataManager::getCurFloor()
{
	return this->m_cur_floor;
}

int DataManager::getFloorSumFromFile(){
	auto valueMap = cocos2d::FileUtils::getInstance()->getValueMapFromFile(FILE_NAME::t_first_hero_info);
	int sumfloor = valueMap["sumFloor"].asInt();
	return sumfloor;
}

void DataManager::addHeroBlood(int blood)
{
	if (this->m_nowblood+blood>this->m_sumblood)
	{
		this->m_nowblood += blood;
		this->m_sumblood = this->m_nowblood;
	}
	else {
		this->m_nowblood += blood;
	}
	this->sendUpdataHeroView();
}

void DataManager::addHeroAttack(int attack)
{
	this->m_attack += attack;
	this->sendUpdataHeroView();
}

void DataManager::addHeroDefend(int defend)
{
	this->m_defend += defend;
	this->sendUpdataHeroView();
}

void DataManager::addHeroKey(int type, int cost)
{
	switch (type)
	{
	case KEY_TYPE::YELLOW:
		this->m_key2_num+=cost;
		break;
	case KEY_TYPE::BLUE:
		this->m_key1_num+=cost;
		break;
	case KEY_TYPE::RED:
		this->m_key0_num+=cost;
		break;
	case KEY_TYPE::ALL_KEY:
		this->m_key0_num+=cost;
		this->m_key1_num+=cost;
		this->m_key2_num+=cost;
		break;
	default:
		break;
	}
	this->sendUpdataHeroView();
}

void DataManager::addHeroGoldAndSoul(int gold, int soul)
{
	this->m_money1_num += gold;
	this->m_money2_num += soul;
	this->sendUpdataHeroView();
}

void DataManager::handleShopCost(int costype, int price, vector<ShopInfoStruct> costlist)
{
	if (costype==SHOP_CONST_TYPE::GOLE)
	{
		this->addHeroGoldAndSoul(price);
	}
	else {
		this->addHeroGoldAndSoul(0,price);
	}
	for (auto const &item:costlist)
	{
		int count = item.num;
		for (int i=0;i<count;i++)
		{
			auto entity = Config::getInstance()->getOtherEntityById(item.id);
			this->handleAllAttr(entity);
		}
	}
}

void DataManager::sendUpdataHeroView()
{
	cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(NOTIFICATION_TYPE::HERO_INFO_VIEW_UPDATE);
}

void DataManager::handleAllAttr(const OtherEntity& entity)
{
	//todo all entity cost or reward will be handle in here
	MIAN_TYPE_ENUM type = (MIAN_TYPE_ENUM)entity.type;
	switch (entity.type)
	{
	case MIAN_TYPE_ENUM::BLOOD:
		this->addHeroBlood(entity.add);
		break;
	case MIAN_TYPE_ENUM::KEY:
		this->addHeroKey(entity.stype,entity.add);
		break;
	case MIAN_TYPE_ENUM::DIAMONDS:
		if (entity.stype==DIAMONDS_TYPE::ATTACK)
		{
			this->addHeroAttack(entity.add);
		}
		else {
			this->addHeroDefend(entity.add);
		}
		break;
	case MIAN_TYPE_ENUM::EQUIP:
		if (entity.stype==EQUIP_TYPE::ATTACK)
		{
			this->addHeroAttack(entity.add);
		}
		else {
			this->addHeroDefend(entity.add);
		}
	default:
		break;
	}
	this->sendUpdataHeroView();
}

int DataManager::getFloorSum()
{
	return this->m_floot_sum;
}

void DataManager::initDataFromFile()
{
	auto filename = cocos2d::FileUtils::getInstance()->getWritablePath() + FILE_NAME::t_map_data;
	auto valuemap = cocos2d::FileUtils::getInstance()->getValueMapFromFile(filename);
	this->initInfo(valuemap);
	//this->set
}


void DataManager::initDataDueToFirst()
{
	auto valuemap = cocos2d::FileUtils::getInstance()->getValueMapFromFile(FILE_NAME::t_first_hero_info);
	this->initInfo(valuemap);
}

//void DataManager::saveSettingInfo()
//{
//	
//}

void DataManager::initInfo(cocos2d::ValueMap & valuemap)
{
	this->m_attack = valuemap["attack"].asInt();
	this->m_defend = valuemap["defend"].asInt();
	this->m_money1_num = valuemap["gold"].asInt();
	this->m_money2_num = valuemap["soul"].asInt();
	this->m_key0_num = valuemap["red_key"].asInt();
	this->m_key1_num = valuemap["blue_key"].asInt();
	this->m_key2_num = valuemap["yellow_key"].asInt();
	this->m_nowblood = valuemap["nowblood"].asInt();
	this->m_sumblood = valuemap["sumblood"].asInt();
	//this->setArrivalFloor(25);
	this->setArrivalFloor(valuemap["arrival_floor"].asInt());
	//this->m_cur_floor = 1;
	this->m_cur_floor = valuemap["curfloor"].asInt();

	this->setHeroIsFight(false);
	//change floor info
	this->setTargetFloor(this->m_cur_floor);
	this->m_floot_sum = this->getFloorSumFromFile();
	//this->setHeroFloorStatus(STAIRS_TYPE_ENUM::UP);

	this->setExitShow(false);
	//this->setIsCanTouch(true);
}

int DataManager::caculateFightHurt(const Monster& monster) {
	int m_real_hurt = DataManager::getInstance()->m_attack - monster.m_defence;
	int hero_real_hurt = monster.m_attack - DataManager::getInstance()->m_defend;
	int tempHeroBlood = -1;
	//对怪物造成的伤害为0
	if (m_real_hurt <= 0)
	{
		//todo fail
		//log("failure");
		return tempHeroBlood;
	}
	if (hero_real_hurt < 0)
	{
		hero_real_hurt = 0;
	}
	int m_blood = monster.m_blood;
	int hero_blood = DataManager::getInstance()->m_nowblood;

	while (m_blood > 0 && hero_blood > 0)
	{
		//caculate hurt
		m_blood -= m_real_hurt;
		hero_blood -= hero_real_hurt;
	}
	//int flag = false;
	if (hero_blood <= 0)
	{
		//failure
		//log("failure");
		//flag = false;
	}
	else {
		//win
		//log("win");
		tempHeroBlood = hero_blood;
		//int new_blood = hero_blood;
		//DataManager::getInstance()->setHeroNowBlood(new_blood);
		//flag = true;
		//tempHeroBlood = new_blood;
	}
	return tempHeroBlood;
}
