#ifndef  __GAMESCENE__H__
#define  __GAMESCENE__H__
#include<functional>
#include "cocos2d.h"
#include "AStar.h"
//#include "Hero.h"
class HeroInfoView;
class Hero;
class Monster;
class Arrow;
using namespace cocos2d;
class GameScene: public Layer{
public:
    static Scene* createScene();
    virtual bool init();  
    CREATE_FUNC(GameScene);
	void initData();
	void initImg();
	void initMap();
	void initBG();
	void initHero();
	void initListener();
	bool isTouchMap(Point p);
	void moveToTargetNode(std::vector<MyNode> path);
	void heroMoveToNext(std::vector<MyNode> path, Point nextP);
	void changeHeroDirection(MyNode,MyNode);
	
	void initMapFromFile();

	//do 
	void heroDoFight(MyNode);
	void heroOpenDoor(MyNode);
	void heroAddBlood(MyNode);
	void heroAddDiamond(MyNode);
	void heroAddKey(MyNode);
	void heroGoShop(MyNode);
	void heroAddEquip(MyNode node);
	void heroAssist(MyNode node);
	//notice
	void initNotification();
	bool judgeNodeType(bool,std::vector<MyNode>,Point,MyNode);

	Vec2 getHeroNewPos(Vec2);
	//draw path
	void drawHeroPath(vector<MyNode> path);
	void removePath(bool single);
	//show floor
	void showFloor();
	void showMapFloor(Vec2 node);
private:
	Size m_winSize;
	experimental::TMXTiledMap* m_map;
	Vec2 m_map_origin;
	//Sprite* m_hero;
	Hero* m_hero;
	HeroInfoView* m_heroinfo;
	float m_heroMoveSpeed;
	DrawNode* drawnnode;
	bool m_moveChange;
	MyNode m_last_node;

	//callback
	using quickCallback = std::function<void()>;
	quickCallback m_moveCallback;
	quickCallback m_fightCallback;
	quickCallback m_doorCallbakc;

	Vector<Sprite*> m_draw_path;
	//youhua
	vector<MyNode> m_last_path;
	Arrow* m_arrow;
	bool isMoveListenerSwallow;
};
#endif

