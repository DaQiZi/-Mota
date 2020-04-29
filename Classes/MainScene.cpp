
#include"MainScene.h"
#include "ui/CocosGUI.h"
#include"cocostudio/CocoStudio.h"
#include"Constant.h"
#include"Utils.h"
#include"DataManager.h"
#include"GameScene.h"
#include"SaveUtils.h"
#include"HelpComponent.h"
#include"SoundUtil.h"
using namespace cocos2d;
using namespace ui;
Scene * MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainScene::init(){
	if (!Layer::init())
	{ 
		return false;
	}
	Utils::getInstance()->setRootNode(this);
	SoundUtil::getInstance()->playBG();
	this->initData();
	this->initNotification();

	return true;
}

void MainScene::initData(){
	auto layer = CSLoader::createNode(FILE_NAME::t_MainSceneComponent_csb);
	this->addChild(layer);
	this->btn_begin = (Button*)layer->getChildByName("btn_begin");
	this->btn_continue = (Button*)layer->getChildByName("btn_continue");
	this->btn_exit = (Button*)layer->getChildByName("btn_exit");
	this->btn_help = (Button*)layer->getChildByName("btn_help");
	Utils::getInstance()->addButtonListener(this->btn_begin, [this]() {
		
		auto filename = FileUtils::getInstance()->getWritablePath() + FILE_NAME::t_map_data;
		if (FileUtils::getInstance()->isFileExist(filename))
		{
			auto valuemap = FileUtils::getInstance()->getValueMapFromFile(FILE_NAME::t_chinese_xml);
			Utils::getInstance()->addTwoButtonDialog(this, valuemap["start"].asString(), [this]() {
				SaveUtils::getInstance()->resetGame();
				auto scene = GameScene::createScene();
				Director::getInstance()->replaceScene(scene);
			});
		}
		else {
			auto scene = GameScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	});;

	Utils::getInstance()->addButtonListener(this->btn_continue, [this]() {
		//int floor = DataManager::getInstance()->getCurFloor();
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});

	Utils::getInstance()->addButtonListener(this->btn_exit, [this]() {
		Director::getInstance()->end();
	});
	Utils::getInstance()->addButtonListener(this->btn_help, [this]() {
		auto item = HelpComponent::create();
		//item->setPosition(LocationUtils::getInstance()->CENTER);
		this->addChild(item);
	});
}

void MainScene::initNotification()
{
	auto listener = EventListenerKeyboard::create();

	listener->onKeyReleased = [](EventKeyboard::KeyCode keycode, cocos2d::Event *event) {
		if (DataManager::getInstance()->getExitShow())
		{
			return;
		}
		DataManager::getInstance()->setExitShow(true);
		switch (keycode) {
		case cocos2d::EventKeyboard::KeyCode::KEY_BACKSPACE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
		{
			auto str = Config::getInstance()->getChineseContent("exit");
			Utils::getInstance()->addTwoButtonDialog(Utils::getInstance()->getRootNode(), str, []() {
				//SaveUtils::getInstance()->save
				//Director::getInstance()->resume();
				Director::getInstance()->end();
			}, []() {
				//Director::getInstance()->resume();
				DataManager::getInstance()->setExitShow(false);
			});
			break;
		}
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
