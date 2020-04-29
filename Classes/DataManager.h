#ifndef __DATA_MANAGER_H_
#define __DATA_MANAGER_H_
#include"cocos2d.h"
#include"Config.h"
#include"Constant.h"
#include<vector>
//struct ShopInfoStruct;
class OtherEntity;
class Monster;
class DataManager{
public:
	//red blue yellow
	int m_key0_num;
	int m_key1_num;
	int m_key2_num;
	//gold   soul
	int m_money1_num;
	int m_money2_num;
	int m_attack;
	int m_defend;
	int m_nowblood;
	int m_sumblood;
	int m_cur_floor;
	//floor sum
	
	STAIRS_TYPE_ENUM heroFloorStatus;
	CC_SYNTHESIZE(int, m_arrival_floor, ArrivalFloor);
	
	CC_SYNTHESIZE(bool,m_hero_isFight,HeroIsFight);
	//setHeroIsFight
	/*
		about setting
	*/
	CC_SYNTHESIZE(int,m_isFirst,IsFirst);
	CC_SYNTHESIZE(int,m_MusicVolume,MusicVolume);
	CC_SYNTHESIZE(int,m_EffectVolume,EffectVolume);
	CC_SYNTHESIZE(bool,musicSwitch,MusicSwitch);
	CC_SYNTHESIZE(bool,effectSwitch,EffectSwitch);
	CC_SYNTHESIZE(bool,exitShow,ExitShow);
	//CC_SYNTHESIZE(bool,isCanTouch,IsCanTouch);
public:
	static DataManager* getInstance();
	DataManager();
	void setHeroNowBlood(int nowblood);
	//about floor
	void setHeroFloorStatus(STAIRS_TYPE_ENUM type);
	void setTargetFloor(int floor);
	int getCurFloor();

	int getFloorSum();
	void addHeroBlood(int blood);
	void addHeroAttack(int attack);
	void addHeroDefend(int defend);
	void addHeroKey(int type,int cost);
	void addHeroGoldAndSoul(int gold = 0,int soul = 0);
	void handleShopCost(int costype,int price,std::vector<ShopInfoStruct> costlist);
	void sendUpdataHeroView();
	void handleAllAttr(const OtherEntity& entity);

	int caculateFightHurt(const Monster& monster);
	int getFloorSumFromFile();
	/*
		about local 
		
	*/
	void initDataFromFile();
	
	void initDataDueToFirst();
	
	private:
	int m_floot_sum;
	//int m_arrival_floor;
	void initInfo(cocos2d::ValueMap& valuemap);
	
};
#endif