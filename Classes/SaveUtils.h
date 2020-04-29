#ifndef __SAVEUTILS_H_  
#define __SAVEUTILS_H_
#include"cocos2d.h"
class SaveUtils {
public:
	SaveUtils();
	static SaveUtils* getInstance();
	//temp save
	/*
	
		if params value is false,then save hero info
	*/
	bool saveDataToLocal(bool saveother=false);
	//forever save
	void saveDataAsFile();
	cocos2d::ValueMap getDataFromMyFile();
	void LoadDataFromSaveFile();
	void addHeroInfoToMap();
	//about book data 
	void loadBookInfoFromFile();
	void saveBookInfo();
	//reset data
	void resetGame();
	cocos2d::ValueVector getBookInfoList();
	void setNewBookInfoList(cocos2d::ValueVector list);
	cocos2d::ValueVector getValueVectorByFloor(int);
	bool saveTargetFloorStatus(int,int,int);
	void initSettingInfo();
	void saveSettingInfo();
	bool haveTempData();
private:
	cocos2d::ValueMap m_map_data;
	cocos2d::ValueVector m_book_data;
	bool m_status;
};
#endif