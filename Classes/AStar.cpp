//#pragma once
//#pragma execution_character_set("utf-8")

#include"AStar.h"
#include"cocos2d.h"
#include "Constant.h"
#include"MapUtil.h"
bool MyNode::isEquls(MyNode node){
	if (this->m_x==node.m_x&&this->m_y==node.m_y){
		return true;
	}else
	{
		return false;
	}

}
bool MyFPathNode::isEquls(MyNode node){
	if (node.m_x==m_node.m_x&&node.m_y==m_node.m_y){
		return true;
	}
	else {
		return false;
	}
}

MyFPathNode::~MyFPathNode(){
	this->m_parent = nullptr;
}
MyFPathNode::MyFPathNode(MyNode node,MyFPathNode* parent=nullptr){
	m_f = 0;
	m_h = 0;
	m_g = 0;
	m_parent = parent;
	m_node.m_x = node.m_x;
	m_node.m_y = node.m_y;
}
int MyFPathNode::getFValue(){
	return this->m_f;
}
MyNode  MyFPathNode::getMyNode(){
	return this->m_node;
}
void MyFPathNode::initValue(int g, int h){
	this->m_h = h;
	this->m_g = g;
	this->m_f = this->m_g + this->m_h;
}
MyFPathNode* MyFPathNode::getParent(){
	return this->m_parent;
}
int MyFPathNode::getGValue(){
	return this->m_g;
}
void AStar::clearAllList(){
	for (auto item:openList){
		delete item;
	}
	for (auto item:closeList){
		delete item;
	}
	openList.clear();
	pathList.clear();
	closeList.clear();
}
std::vector<MyNode> AStar::getPath(experimental::TMXLayer* layer, MyNode curNode, MyNode targetNode){
	std::vector<MyNode> t_node;
	if (curNode.isEquls(targetNode)){//点击的就是目的地
		return t_node;
	}
	/*else if (this->m_lastNode.isEquls(targetNode))
	{
		return t_node;
	}*/
	//this->m_lastNode = targetNode;
	this->clearAllList();
	auto node = new MyFPathNode(curNode);
	this->insertToOpenList(node);
	//start A*
	while (openList.size()>0)
	{
		auto node = this->openList.at(0);
		this->closeList.push_back(node);
		this->openList.erase(this->openList.begin());
		// 如果当前点就是目标点。
		if (node->getMyNode().isEquls(targetNode)){
			//todo 翻转close表。
			/*for (auto iter = this->closeList.rbegin(); iter != this->closeList.rend();iter++){
				this->pathList.push_back(*iter);
			}*/
			auto pathnode = *this->closeList.rbegin();
			while (pathnode)
			{
				this->pathList.push_back(pathnode);
				pathnode = pathnode->getParent();
			}
			std::reverse(this->pathList.begin(),this->pathList.end());
			break;
		}
		
		//得到当前点周围的四个点。
		vector<MyNode> roundArr = this->getRoundNode(node->getMyNode());
		//todo check around node
		for (const auto & item_node: roundArr){
			//todo check in close list
			if (!this->checkInCloseList(item_node)){
				//todo check in open list
				int index = this->checkInOpenList(item_node);
				if (index<0){
					//todo update open list
					MyFPathNode* updatenode = new MyFPathNode(item_node,node);
					updatenode->initValue(updatenode->getParent()->getGValue()+this->moveCost(updatenode->getMyNode()),this->computeHValueFromNode(item_node,targetNode));
					this->insertToOpenList(updatenode);
				}else{
					//todo insert to open list
					auto existnode = this->openList.at(index);
					MyFPathNode* updatenode = new MyFPathNode(item_node, node);
					updatenode->initValue(updatenode->getParent()->getGValue() + this->moveCost(updatenode->getMyNode()), this->computeHValueFromNode(item_node, targetNode));
					if (updatenode->getFValue()<existnode->getFValue()){
						this->openList.erase(this->openList.begin()+index);
						delete existnode;
						this->insertToOpenList(updatenode);
					}
					else{
						delete updatenode;
					}
				}
			}
		}
	}
	//cocos2d::log("cur %d %d  to  target %d  %d",curNode.m_x,curNode.m_y,targetNode.m_x,targetNode.m_y);
	
	std::vector<MyNode> newPathList;
	//todo simple path
	for (auto node:this->pathList){
		newPathList.push_back(node->getMyNode());
	}
	this->clearAllList();
	log("find path");
	return newPathList;
	
}
bool AStar::checkInCloseList(MyNode node){
	for (const auto& tempnode :this->closeList){
		if (tempnode->getMyNode().isEquls(node)){
			return true;
		}
	}
	return false;
}
int AStar::checkInOpenList(MyNode node){
	int index = 0;
	for (const auto& tempnode : this->openList){
		if (tempnode->getMyNode().isEquls(node)){
			return index;
		}
		index++;
	}
	return -1;
}
AStar* AStar::getInstance(){
	static AStar instance;
	return &instance;
}
//根据算法，F值小的在前面，大的在后面，相等的，新的在前面
void AStar::insertToOpenList(MyFPathNode* node){
	int fValue = node->getFValue();
	int i = 0;
	for (; i < openList.size(); i++)
	{
		int tempFValue = openList[i]->getFValue();
		if (fValue<=tempFValue){
			break;
		}
	}
	openList.insert(openList.begin()+i,node);
}
int AStar::computeHValueFromNode(MyNode curnode, MyNode targetNode){
	int value = abs(curnode.m_x-targetNode.m_x)+abs(curnode.m_y-targetNode.m_y);
	return value;
}

int AStar::moveCost(MyNode node){
	if (MapUtil::getInstance()->judgeNodeIsAddCost(node))
	{
		return 1*5;
	}
	return 1;
}
MyNode AStar::getDirectionNode(MyNode curNode, Constant::Direction direction){
	MyNode tempNode = curNode;
	switch (direction){
		case Constant::Direction::UP:
			tempNode.m_y += 1;
			break;
		case Constant::Direction::DOWN:
			tempNode.m_y -= 1;
			break;
		case Constant::Direction::LEFT:
			tempNode.m_x -= 1;
			break;
		case Constant::Direction::RIGHT:
			tempNode.m_x += 1;
			break;
	}
	return tempNode;
}
std::vector<MyNode> AStar::getRoundNode(MyNode curNode){
	std::vector<MyNode> fourDirectionVector;
	MyNode tempNode;
	tempNode = this->getDirectionNode(curNode, Constant::Direction::RIGHT);
	if (MapUtil::getInstance()->judgeNodeLegal(tempNode)){
		MyNode node = tempNode;
		fourDirectionVector.push_back(node);
	}
	tempNode = this->getDirectionNode(curNode, Constant::Direction::DOWN);
	if (MapUtil::getInstance()->judgeNodeLegal(tempNode)){
		MyNode node = tempNode;
		fourDirectionVector.push_back(node);
	}
	tempNode = this->getDirectionNode(curNode, Constant::Direction::LEFT);
	if (MapUtil::getInstance()->judgeNodeLegal(tempNode)){
		MyNode node = tempNode;
		fourDirectionVector.push_back(node);
	}
	tempNode = this->getDirectionNode(curNode, Constant::Direction::UP);
	if (MapUtil::getInstance()->judgeNodeLegal(tempNode)){
		MyNode node = tempNode;
		fourDirectionVector.push_back(node);
	}
	return fourDirectionVector;
}
