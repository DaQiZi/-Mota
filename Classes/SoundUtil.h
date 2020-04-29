#ifndef __SOUNDUTIL_H_  
#define __SOUNDUTIL_H_
#include"cocos2d.h"
#include"Constant.h"
class SoundUtil {
public:
	static SoundUtil* getInstance();
	SoundUtil();
	void preloadMusicAndEffect();
	void playMusic(std::string name);
	void playEffect(AUDIO_EFFECT_ENUM type);
	void playRun(bool status);
	void setMusicS(bool type);
	void setEffectS(bool type);
	void playBG();
	void setMusicVolume(float value);
	void setEffectVolume(float value);
private:
	int runid;
	bool isFirstRun;
};
#endif