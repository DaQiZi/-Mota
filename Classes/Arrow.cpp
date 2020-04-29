
#include"Arrow.h"

using namespace cocos2d;
bool Arrow::init(){
	if (!Node::init())
	{
		return false;
	}
	
	this->initData();
	return true;
}

void Arrow::initData(){
	auto spr1 = Sprite::create("a5.png");
	spr1->setPosition(Vec2::ZERO);
	this->addChild(spr1);

	auto spr2 = Sprite::create("a11.png");
	spr2->setPosition(Vec2::ZERO);
	this->addChild(spr2);

	auto fade = Sequence::create(FadeIn::create(0.2f),FadeOut::create(0.2f),nullptr);
	auto scale = Sequence::create(ScaleTo::create(0.2f,0.2),ScaleTo::create(0.2f,2.0f),nullptr);
	spr2->runAction(RepeatForever::create(Spawn::create(fade,scale,nullptr)));

	auto spr3 = Sprite::create("goal_jian.png");
	spr3->setScale(0.5f);
	auto action = Sequence::create(MoveBy::create(0.2f, Vec2(0.0f,10.0f)), MoveBy::create(0.2f, Vec2(0.0f,-10.0f)),nullptr);
	spr3->runAction(RepeatForever::create(action));
	spr3->setAnchorPoint(Vec2(0.5f,0.0f));
	spr3->setPosition(Vec2::ZERO);
	this->addChild(spr3);
}
		