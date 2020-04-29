//#pragma once
//#pragma execution_character_set("utf-8")

#ifndef __A_STAR_H_
#define __A_STAR_H_
#include<vector>
#include"cocos2d.h"
#include "Constant.h"
using namespace cocos2d;
struct MyNode{
	int m_x;
	int m_y;
	bool isEquls(MyNode node);
	MyNode(int x, int y){
		m_x = x;
		m_y = y;
	}
	MyNode(){
		m_x = -1;
		m_y = -1;
	}
};
class MyFPathNode{
public:
	bool isEquls(MyNode node);
	MyFPathNode(MyNode node,MyFPathNode* parent);
	~MyFPathNode();
	int getFValue();
	int getGValue();
	MyNode getMyNode();
	void initValue(int g,int h);
	MyFPathNode* getParent();
private:
	int m_f;
	int m_h;
	int m_g;
	MyNode m_node;
	MyFPathNode* m_parent;
};

class AStar{

public:
	using PathVector = std::vector<MyFPathNode*>;
	static AStar* getInstance();
	std::vector<MyNode> getPath(experimental::TMXLayer* layer, MyNode curNode, MyNode targetNode);
	void insertToOpenList(MyFPathNode* node);
	int computeHValueFromNode(MyNode curnode, MyNode targetNode);
	int moveCost(MyNode node);
	std::vector<MyNode> getRoundNode(MyNode curNode);
	MyNode getDirectionNode(MyNode curNode,Constant::Direction direction);
	void clearAllList();
	bool checkInCloseList(MyNode node);
	int checkInOpenList(MyNode node);
private:

	//typedef std::vector<MyFPathNode*> PathVector;
	PathVector openList;
	PathVector closeList;
	PathVector pathList;
	//MyNode m_lastNode;
};
#endif