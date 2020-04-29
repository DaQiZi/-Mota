#include "SaveUtils.h"
#include "cocos2d.h"
#include "Constant.h"
#include "Utils.h"
#include "DataManager.h"
//#include "MapUtil.h"
USING_NS_CC;
SaveUtils::SaveUtils()
{
	auto instance = FileUtils::getInstance();
	std::string filename = instance->getWritablePath() + FILE_NAME::t_map_data;
	std::string bookinfo = instance->getWritablePath() + FILE_NAME::t_book_info_data;
	if (instance->isFileExist(filename)){
		this->m_map_data = instance->getValueMapFromFile(filename);
		this->m_status = false;
	}
	else{
		this->m_status = false;
	}
	this->initSettingInfo();
	this->loadBookInfoFromFile();
	//this->m_map_data = 
}

SaveUtils* SaveUtils::getInstance()
{
	static SaveUtils instance;
	return &instance;
}

bool SaveUtils::saveDataToLocal(bool saveother)
{
	std::string filename = FileUtils::getInstance()->getWritablePath() + FILE_NAME::t_map_data;
	if (!saveother)
	{
		//sometime didn't save cur hero info ,as reset game, and read file from savefile
		//在读档和重置游戏的时候，不需要把当前的英雄信息。存到文件里面。英语真尼玛差。= =。
		this->addHeroInfoToMap();
	}
	this->saveBookInfo();
	this->saveSettingInfo();
	return FileUtils::getInstance()->writeValueMapToFile(this->m_map_data,filename);
}

void SaveUtils::saveDataAsFile()
{
	//save floor and all info
	std::string filename = FileUtils::getInstance()->getWritablePath() + FILE_NAME::t_save_map_data;
	this->addHeroInfoToMap();
	FileUtils::getInstance()->writeValueMapToFile(this->m_map_data, filename);
}

cocos2d::ValueMap SaveUtils::getDataFromMyFile()
{
	auto instance = FileUtils::getInstance();
	std::string filename = instance->getWritablePath() + FILE_NAME::t_save_map_data;
	return instance->getValueMapFromFile(filename);
}

void SaveUtils::LoadDataFromSaveFile()
{
	this->m_map_data = this->getDataFromMyFile();
	//load data form file  and then 
	this->saveDataToLocal(true);
	DataManager::getInstance()->initDataFromFile();
}

void SaveUtils::addHeroInfoToMap()
{
	this->m_map_data["time"] = Value(Utils::getInstance()->getcurrTime());
	this->m_map_data["nowblood"] = Value(DataManager::getInstance()->m_nowblood);
	this->m_map_data["sumblood"] = Value(DataManager::getInstance()->m_sumblood);
	this->m_map_data["attack"] = Value(DataManager::getInstance()->m_attack);
	this->m_map_data["defend"] = Value(DataManager::getInstance()->m_defend);
	this->m_map_data["gold"] = Value(DataManager::getInstance()->m_money1_num);
	this->m_map_data["soul"] = Value(DataManager::getInstance()->m_money2_num);
	this->m_map_data["red_key"] = Value(DataManager::getInstance()->m_key0_num);
	this->m_map_data["blue_key"] = Value(DataManager::getInstance()->m_key1_num);
	this->m_map_data["yellow_key"] = Value(DataManager::getInstance()->m_key2_num);
	this->m_map_data["curfloor"] = Value(DataManager::getInstance()->m_cur_floor);
	this->m_map_data["arrival_floor"] = Value(DataManager::getInstance()->getArrivalFloor());
}

void SaveUtils::loadBookInfoFromFile()
{
	auto instance = FileUtils::getInstance();
	std::string bookinfo = instance->getWritablePath() + FILE_NAME::t_book_info_data;
	if (instance->isFileExist(bookinfo)) {
		this->m_book_data = instance->getValueVectorFromFile(bookinfo);
	}
}

void SaveUtils::saveBookInfo()
{
	std::string bookinfo = FileUtils::getInstance()->getWritablePath() + FILE_NAME::t_book_info_data;
	FileUtils::getInstance()->writeValueVectorToFile(this->m_book_data,bookinfo);
}



void SaveUtils::resetGame()
{
	//todo 
	ValueMap newvalue;
	this->m_map_data = newvalue;
	//this->saveDataToLocal();
	DataManager::getInstance()->initDataDueToFirst();
	this->saveDataToLocal(true);
	UserDefault::getInstance()->setBoolForKey("isFirst",true);
	//DataManager::getInstance()->
}

ValueVector SaveUtils::getBookInfoList()
{
	return this->m_book_data;
}

void SaveUtils::setNewBookInfoList(ValueVector list)
{
	this->m_book_data = list;
}

cocos2d::ValueVector SaveUtils::getValueVectorByFloor(int floor)
{
	//todo 判断是否到最后一层了。
	Value newfloor(floor);
	if (this->m_map_data.find(newfloor.asString())!=this->m_map_data.end())
	{
		return this->m_map_data[newfloor.asString()].asValueVector();
	}
	ValueVector vec;
	return vec;
}

bool SaveUtils::saveTargetFloorStatus(int floor, int x, int y)
{
	int value = x*Constant::SAVE_LOCAL_WEIGHT + y;
	Value newValue(value);
	std::string newFloor = StringUtils::format("%d",floor);
	if (this->m_map_data.find(newFloor)!=this->m_map_data.end())
	{
		auto &vec = this->m_map_data[newFloor].asValueVector();
		vec.push_back(newValue);
	}
	else{
		ValueVector newVector;
		newVector.push_back(newValue);
		this->m_map_data[newFloor] = newVector;
	}
	return true;
}

void SaveUtils::initSettingInfo()
{
	auto instance = DataManager::getInstance();
	instance->setMusicVolume(cocos2d::UserDefault::getInstance()->getIntegerForKey("musicV", 100));
	instance->setEffectVolume(cocos2d::UserDefault::getInstance()->getIntegerForKey("effectV", 100));
	instance->setMusicSwitch(cocos2d::UserDefault::getInstance()->getBoolForKey("musicS", true));
	instance->setEffectSwitch(cocos2d::UserDefault::getInstance()->getBoolForKey("effectS", true));
}

void SaveUtils::saveSettingInfo()
{
	auto instance = DataManager::getInstance();
	cocos2d::UserDefault::getInstance()->setIntegerForKey("musicV", instance->getMusicVolume());
	cocos2d::UserDefault::getInstance()->setIntegerForKey("effectV", instance->getEffectVolume());
	cocos2d::UserDefault::getInstance()->setBoolForKey("musicS", instance->getMusicSwitch());
	cocos2d::UserDefault::getInstance()->setBoolForKey("effectS", instance->getEffectSwitch());
}

bool SaveUtils::haveTempData()
{
	if (m_map_data.size()>0) {
		return true;
	}
	else {
		return false;
	}
}
