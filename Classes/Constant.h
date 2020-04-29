//#pragma once
//#pragma execution_character_set("utf-8")
#ifndef _CONSTANT_H_
#define _CONSTANT_H_
#include<string>
using namespace std;

namespace Constant{
	const float HERO_FIGHT_TINE = 1.5f;
	const int SAVE_LOCAL_WEIGHT = 100;
	const std::string BLOCK_NAME = "isBlock";
	const std::string MAIN_TYPE = "type";
	const std::string MAIN_ID = "id";
	const std::string BLOCK_LAYER_NAME = "block";
	const std::string MAIN_LAYER_NAME = "main";
	const std::string STAIRS_TYPE = "stype";
	const int PAGE_NUM = 8;
	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
}

namespace SAVE_TO_LOCAL{
	const std::string GET_CUR_FLOOR = "GET_CUR_FLOOR";
}

namespace NOTIFICATION_TYPE{
	const std::string HERO_BLOOD_UPDATE = "HERO_BLOOD_UPDATE";
	const std::string HERO_INFO_VIEW_UPDATE = "HERO_INFO_VIEW_UPDATE";
	const std::string TARGET_NODE_CHANGE = "TARGET_NODE_CHANGE";
	const std::string SCENE_CHANGE = "SCENE_CHANGE";
	const std::string SCENE_JUMP_TO_TARGET_FLOOR = "SCENE_JUMP_TO_TARGET_FLOOR";
	const std::string HERO_STOP_MOVE = "HERO_STOP_MOVE";
	const std::string GAME_WIN = "GAME_WIN";
	const std::string ARROW_HIDE = "ARROW_HIDE";
	const std::string MOVE_TOUCH_LISTENER = "MOVE_TOUCH_LISTENER";
	//const std::string MOVE_CHANGE_
}

namespace FILE_NAME{
	const std::string t_monsters_json = "t_monsters.json";
	const std::string t_otherEntity_json = "t_otherEntity.json";
	const std::string t_shop_list_json = "json/t_shop_list.json";
	const std::string t_shop_json = "json/t_shop.json";

	const std::string t_heroinfo_csb = "heroInfo.csb";
	const std::string t_commonDialogComponent_csb = "CommonDialogComponent.csb";
	const std::string t_shopComponent_csb = "ShopComponent.csb";
	const std::string t_shopItemComponent_csb = "ShopItemComponent.csb";
	const std::string t_MHurtItemComponent_csb = "MHurtItemComponent.csb";
	const std::string t_MHurtComponent_csb = "MHurtComponent.csb";
	const std::string t_TabComponent_csb = "TabComponent.csb";
	const std::string t_BookItemComponent_csb = "BookItemComponent.csb";
	const std::string t_MainSceneComponent_csb = "MainSceneComponent.csb";
	const std::string t_LoadingScene_csb = "LoadingScene.csb";
	const std::string t_HelpCompoent_csb = "HelpComponent.csb";

	const std::string t_map_data = "mapdata.xml";
	const std::string t_save_map_data = "saveMapData.xml";
	const std::string t_book_info_data = "bookInfoData.xml";
	const std::string t_first_hero_info = "first_hero_info.xml";
	const std::string t_img_judge_xml = "img_judge.xml";

	const std::string t_chinese_xml = "chinese.xml";

	//other png
	const std::string tou__name1_png = "head/tou__name1.png";
	const std::string tou__name2_png = "head/tou__name2.png";
	const std::string tou__name3_png = "head/tou__name3.png";
}
enum HERO_ANIMATION_ENUM
{
	DOWN_STANE = 0,
	DOWN_RUN,
	DOWN_FIGHT,
	UP_STANE,
	UP_RUN,
	UP_FIGHT,
	L_STANE,
	L_RUN,
	L_FIGHT,
	R_STANE,
	R_RUN,
	R_FIGHT
};
enum  DIRECTION_ENUM
{
	STAND = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT
};
enum MIAN_TYPE_ENUM{
	NONE,
	MONSTERS,
	DOOR,
	KEY,
	BLOOD,
	DIAMONDS,
	STAIRS,
	HERO_STAND,
	SHOP,
	EQUIP,
	ASSIST
};
enum AUDIO_EFFECT_ENUM {
	AU_KEY,
	AU_DOOR,
	AU_RUN,
	AU_HP,
	AU_FIGHT,
	AU_DIA,
	AU_FLOOR,
	AU_EQUIP
};
enum class STAIRS_TYPE_ENUM {
	UP=1,
	DOWN
};
namespace DIAMONDS_TYPE {
	const int ATTACK = 1;
	const int DEFEND = 2;
}
namespace EQUIP_TYPE {
	const int ATTACK = 1;
	const int DEFEND = 2;
}
namespace KEY_TYPE {
	const int YELLOW = 1;
	const int BLUE = 2;
	const int RED = 3;
	const int ALL_KEY = 4;
}
namespace DIALOG_STYLE {
	const int COMMON = 1;
	const int TIPS = 2;
}

namespace SHOP_CONST_TYPE {
	const int GOLE = 1;
	const int SOUL = 2;
}

namespace MONSTER_TYPE {
	const int NEWBIE = 1;
	const int BOOS = 2;
}
#endif