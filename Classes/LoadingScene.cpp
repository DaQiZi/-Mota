
#include"LoadingScene.h"
#include"MainScene.h"
#include"Constant.h"
#include"cocostudio/CocoStudio.h"

Scene * LoadingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadingScene::init(){
	if (!Layer::init())
	{
		return false;
	}
	this->initData();
	//this->filelist.size();
	this->initUI();
	this->preloadImg();
	return true;
}


void LoadingScene::preloadImg()
{
	for (auto filename : this->filelist)
	{
		//log("filename = %s",filename.asString().c_str());
		TextureCache::getInstance()->addImageAsync(filename.asString(),CC_CALLBACK_1(LoadingScene::checkLoading,this));
	}
}

void LoadingScene::checkLoading(Texture2D * img)
{
	this->loadingCount++;
	
	float value = (this->loadingCount +0.0f)/ this->filelist.size();
	if (this->loadingCount>=this->filelist.size())
	{
		//MessageBox("123", "1232");
		Director::getInstance()->replaceScene(MainScene::createScene());
		//Director::getInstance()->
		return;
	}
	//Director::getInstance()->end();
	this->load_1->setPercent(value*100);
	std::string str = StringUtils::format("loading %0.1f%%", value*100);
	this->lb_load->setString(str);
}

void LoadingScene::initUI()
{
	auto root = CSLoader::createNode(FILE_NAME::t_LoadingScene_csb);
	this->addChild(root);
	this->load_1 = (cocos2d::ui::LoadingBar*)root->getChildByName("load_1");
	this->lb_load = (cocos2d::ui::Text*)root->getChildByName("lb_load");
}
		
void LoadingScene::initData() {
	this->loadingCount = 0;
	this->filelist = FileUtils::getInstance()->getValueVectorFromFile("getImgPath.xml");
}
