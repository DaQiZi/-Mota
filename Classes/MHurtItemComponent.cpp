#include"MHurtItemComponent.h"
#include"cocostudio/CocoStudio.h"
#include"Constant.h"
#include"Monster.h"
#include"DataManager.h"
using namespace cocos2d;
using namespace ui;
bool MHurtItemComponent::init()
{
	if (!Widget::init())
	{
		return false;
	}
	this->initData();
	return true;
}

void MHurtItemComponent::initData()
{
	auto rootnode = CSLoader::createNode(FILE_NAME::t_MHurtItemComponent_csb);
	this->addChild(rootnode);
	

	this->ly_bg = (Layout*)rootnode->getChildByName("ly_bg");
	this->setContentSize(this->ly_bg->getContentSize());
	auto img_bg = (Sprite*)ly_bg->getChildByName("img_bg");
	

	this->ly_head= (Layout*)ly_bg->getChildByName("ly_head");
	//this->img_head = (Sprite*)lv->getChildByName("img_head");
	this->img_dead = (Sprite*)ly_bg->getChildByName("img_dead");

	this->lb_attack = (Text*)ly_bg->getChildByName("lb_attack");
	this->lb_name= (Text*)ly_bg->getChildByName("lb_name");
	this->lb_defend = (Text*)ly_bg->getChildByName("lb_defend");
	this->lb_gold = (Text*)ly_bg->getChildByName("lb_gold");
	this->lb_soul = (Text*)ly_bg->getChildByName("lb_soul");
	this->lb_blood = (Text*)ly_bg->getChildByName("lb_blood");

	this->lb_hurt = (TextAtlas*)ly_bg->getChildByName("lb_hurt");
}

void MHurtItemComponent::updateItem(const Monster& entity)
{
	this->lb_name->setString(entity.m_name);

	this->lb_attack->setString(StringUtils::toString(entity.m_attack));
	this->lb_defend->setString(StringUtils::toString(entity.m_defence));
	this->lb_gold->setString(StringUtils::toString(entity.m_gold));
	this->lb_soul->setString(StringUtils::toString(entity.m_soul));
	this->lb_blood->setString(StringUtils::toString(entity.m_blood));
	//texture
	auto spr = Sprite::create(entity.m_iconName);
	spr->setAnchorPoint(Vec2(0.5f,1.0f));
	spr->setPosition(Vec2(ly_head->getContentSize().width/2, ly_head->getContentSize().height));
	this->ly_head->addChild(spr);

	int blood = DataManager::getInstance()->caculateFightHurt(entity);
	if (blood<=0)
	{
		this->lb_hurt->setVisible(false);
		this->img_dead->setVisible(true);
	}
	else {
		int heroHurt = DataManager::getInstance()->m_nowblood-blood;
		this->lb_hurt->setString(StringUtils::toString(heroHurt));
	}
	//this->img_head->cl
}


