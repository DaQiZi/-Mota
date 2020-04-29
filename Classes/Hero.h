#ifndef __HERO_H_
#define __HERO_H_

#include"Entity.h"
#include"cocostudio\CocoStudio.h"
#include"Constant.h"
#include"cocos2d.h"
using namespace cocostudio;
class Hero : public Entity,public cocos2d::Node{
public:
	//CREATE_FUNC(Hero);
	bool init(std::string);
	static Hero* create(std::string);
	virtual void initData(std::string);
	void playAnimation(HERO_ANIMATION_ENUM);
	void playFightAnima();
	void changeStatus();
	void changeHeroDirection(DIRECTION_ENUM direction,bool saveDirection=true);
	void initNotification();
	void setHeroMoveStauts(bool);
	//void playStandAnima();
	bool m_heroisMoving;

	//inline
	DIRECTION_ENUM getDirection(){
		return this->m_lastDirection;
	}
	CC_SYNTHESIZE(bool,stopMove,StopMove);
	//CC_SYNTHESIZE(bool,heroIsFight,HeroIsFight);
private:
	Armature* m_heroArmature;
	DIRECTION_ENUM m_lastDirection;
	std::string m_lastAnimaName;
	bool m_lastScale;
	
};

#endif