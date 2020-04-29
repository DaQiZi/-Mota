
#ifndef __LOADINGSCENE_H__
#define __LOADINGSCENE_H__
#include"cocos2d.h"
#include"ui/CocosGUI.h"
using namespace cocos2d;
class LoadingScene : public cocos2d::Layer{
public:
	static Scene* createScene();
	CREATE_FUNC(LoadingScene);
	virtual bool init();
	void initData();
	void preloadImg();
	void checkLoading(Texture2D* img);
	void initUI();
private:
	cocos2d::ValueVector filelist;
	cocos2d::ui::LoadingBar* load_1;
	cocos2d::ui::Text* lb_load;
	int loadingCount;
};
#endif
		