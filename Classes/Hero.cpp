#include"Hero.h"
#include"Config.h"
#include"cocos2d.h"
#include"DataManager.h"
using namespace cocos2d;
Hero* Hero::create(std::string filename){
	Hero* hero = new Hero();
	if (hero&&hero->init(filename))
	{
		hero->autorelease();
		return hero;
	}
	else{
		CC_SAFE_DELETE(hero);
		return nullptr;
	}
}
bool Hero::init(std::string filename){
	if (!Node::init()){
		return false;
	}
	
	this->initData(filename);
	this->initNotification();
	return true;
}
void Hero::initData(std::string filename){
	ArmatureDataManager::getInstance()->addArmatureFileInfo(filename);
	this->m_heroArmature = Armature::create("hero");
	this->playAnimation(HERO_ANIMATION_ENUM::L_RUN);
	this->addChild(this->m_heroArmature); 
	m_lastDirection = DIRECTION_ENUM::STAND;
	m_lastAnimaName = "";
	m_lastScale = false;
	m_heroisMoving = false;
	//this->setHeroIsFight(false);
} 
void Hero::playAnimation(HERO_ANIMATION_ENUM name){
	std::string animaName;
	bool scaleX = false;
	switch (name)
	{
	case R_STANE:
		animaName = HeroConfig::getInstance()->getAnimationName(HERO_ANIMATION_ENUM::L_STANE);
		scaleX = true;
		break;
	case R_RUN:
		animaName = HeroConfig::getInstance()->getAnimationName(HERO_ANIMATION_ENUM::L_RUN);
		scaleX = true;
		break;
	case R_FIGHT:
		animaName = HeroConfig::getInstance()->getAnimationName(HERO_ANIMATION_ENUM::L_FIGHT);
		scaleX = true;
		break;
	default:
		animaName = HeroConfig::getInstance()->getAnimationName(name);
		break;
	}
	//·ÀÖ¹ÖØ¸´²¥·Å
	if (animaName==this->m_lastAnimaName&&scaleX==this->m_lastScale)
	{
		return;
	}
	this->m_lastAnimaName = animaName;
	this->m_lastScale = scaleX;
	this->m_heroArmature->getAnimation()->play(animaName);
	if (scaleX)
	{
		this->setScaleX(-1);
	}
	else{
		this->setScaleX(1);
	}
	//this->changeStatus();
	/*auto pBone = m_heroArmature->getBone("head");
	pBone->setScale(0);*/
	
}
void Hero::setHeroMoveStauts(bool flag){
	this->m_heroisMoving = flag;
}
//void Hero::playStandAnima()
//{
//	HERO_ANIMATION_ENUM heroAnima;
//	if (this->m_lastDirection==DIRECTION_ENUM::LEFT)
//	{
//		heroAnima = HERO_ANIMATION_ENUM::L_STANE;
//	}else if (this->m_lastDirection==DIRECTION_ENUM::RIGHT)
//	{
//		heroAnima = HERO_ANIMATION_ENUM::R_STANE;
//	}
//	else if (this->m_lastDirection==DIRECTION_ENUM::UP) {
//		heroAnima = HERO_ANIMATION_ENUM::UP_STANE;
//	}
//	else {
//		heroAnima = HERO_ANIMATION_ENUM::DOWN_STANE;
//	}
//	this->playAnimation(heroAnima);
//}
void Hero::changeHeroDirection(DIRECTION_ENUM direction, bool saveDirection){
	//this->setHeroIsFight(false);
	DataManager::getInstance()->setHeroIsFight(false);
	//DataManager::getInstance()->setHeroIsFight(false);
	HERO_ANIMATION_ENUM heroAnima;
	switch (direction)
	{
	case STAND:
		if (this->m_lastDirection==LEFT)
		{
			heroAnima = HERO_ANIMATION_ENUM::L_STANE;
		}
		else if (this->m_lastDirection==RIGHT){
			heroAnima = HERO_ANIMATION_ENUM::R_STANE;
		}
		else if (this->m_lastDirection==UP)
		{
			heroAnima = HERO_ANIMATION_ENUM::UP_STANE;
		}
		else 
		{
			heroAnima = HERO_ANIMATION_ENUM::DOWN_STANE;
		}
		//this->setHeroMoveStauts(false);
		break;
	case UP:
		heroAnima = HERO_ANIMATION_ENUM::UP_RUN;
		break;
	case DOWN:
		heroAnima = HERO_ANIMATION_ENUM::DOWN_RUN;
		break;
	case LEFT:
		heroAnima = HERO_ANIMATION_ENUM::L_RUN;
		break;
	case RIGHT:
		heroAnima = HERO_ANIMATION_ENUM::R_RUN;
		break;
	default:
		break;
	}
	if (direction==DIRECTION_ENUM::STAND)
	{
		this->setHeroMoveStauts(false);
	}
	else{
		this->setHeroMoveStauts(true);
	}  
	if (saveDirection)
	{
		this->m_lastDirection = direction;
	}
	//log("-----------%d-----------",this->m_heroisMoving);
	//bool flag = false;
	/*if (heroAnima==HERO_ANIMATION_ENUM::R_FIGHT)
	{
		this->playAnimation(HERO_ANIMATION_ENUM::L_FIGHT, true);
	}
	else if (heroAnima==HERO_ANIMATION_ENUM::R_RUN)
	{
		this->playAnimation(HERO_ANIMATION_ENUM::L_RUN,true);
	}
	else if (heroAnima==HERO_ANIMATION_ENUM::R_STANE)
	{
		this->playAnimation(HERO_ANIMATION_ENUM::L_STANE, true);
	}
	else{*/
	this->playAnimation(heroAnima);
	//}
}
void Hero::initNotification()
{
	auto stoplistener = EventListenerCustom::create(NOTIFICATION_TYPE::HERO_STOP_MOVE, [this](EventCustom* ref) {
		if (this->m_heroisMoving)
		{
			this->setStopMove(true);
			this->m_heroisMoving = false;
			this->changeHeroDirection(DIRECTION_ENUM::STAND);
			_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::TARGET_NODE_CHANGE);
			_eventDispatcher->dispatchCustomEvent(NOTIFICATION_TYPE::ARROW_HIDE);
		}
	});
	//_eventDispatcher->addCustomEventListener()
	_eventDispatcher->addEventListenerWithSceneGraphPriority(stoplistener,this);

}
void Hero::playFightAnima(){
	DataManager::getInstance()->setHeroIsFight(true);

	//this->setHeroIsFight(true);
	HERO_ANIMATION_ENUM anima;
	switch (this->m_lastDirection)
	{
	case DIRECTION_ENUM::UP:
		anima = HERO_ANIMATION_ENUM::UP_FIGHT;
		break;
	case DIRECTION_ENUM::DOWN:
		anima = HERO_ANIMATION_ENUM::DOWN_FIGHT;
		break;
	case DIRECTION_ENUM::LEFT:
		anima = HERO_ANIMATION_ENUM::L_FIGHT;
		break;
	case DIRECTION_ENUM::RIGHT:
		anima = HERO_ANIMATION_ENUM::R_FIGHT;
		break;
	default:
		break;
	}
	this->playAnimation(anima);
}
//demo
void Hero::changeStatus(){
	static int i = 1;
	if (i==5)
	{
		i = 1;
	}
	for (size_t j = 1; j <5; j++)
	{
		if (i!=j)
		{
			auto pBone = m_heroArmature->getBone(StringUtils::format("sheild%d", j));
			pBone->setScale(1);
		}
		else
		{
			auto pBone = m_heroArmature->getBone(StringUtils::format("sheild%d", j));
			pBone->setScale(0);
		}
	}
	for (size_t j = 1; j <6; j++)
	{
		if (i != j)
		{
			auto pBone = m_heroArmature->getBone(StringUtils::format("sword%d", j));
			pBone->setScale(1);
		}
		else
		{
			auto pBone = m_heroArmature->getBone(StringUtils::format("sword%d", j));
			pBone->setScale(0);
		}
	}

	auto sequence = Sequence::create(DelayTime::create(0.5f), CallFunc::create([this](){
		this->changeStatus(); 
	}), nullptr);
	this->runAction(sequence);
	i++;
}


