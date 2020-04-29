#include"cocos2d.h"
//#include"AudioEngine.h"
#include"SimpleAudioEngine.h"
#include"SoundUtil.h"
#include"DataManager.h"

using namespace CocosDenshion;
SoundUtil * SoundUtil::getInstance()
{
	static SoundUtil instance;
	return &instance;
}

SoundUtil::SoundUtil()
{
	this->isFirstRun = true;
}

void SoundUtil::preloadMusicAndEffect()
{
	//cocos2d::experimental::AudioEngine::get;
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/lv.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/get_hp.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/get_jewel.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/ge_key.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/get_other.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/getNewWeapon.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/lv.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/opendoor.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/run.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/transfer.mp3");

	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(DataManager::getInstance()->getMusicVolume() / 100.0f);
	SimpleAudioEngine::getInstance()->setEffectsVolume(DataManager::getInstance()->getEffectVolume() / 100.0f);

}

void SoundUtil::playMusic(std::string name)
{
	
}

void SoundUtil::playEffect(AUDIO_EFFECT_ENUM type)
{
	if (!DataManager::getInstance()->getEffectSwitch())
	{
		return;
	}
	auto instance = SimpleAudioEngine::getInstance();
	switch (type)
	{
	case AU_KEY:
		instance->playEffect("music/get_key.mp3");
		break;
	case AU_DOOR:
		instance->playEffect("music/opendoor.mp3");
		break;
	case AU_RUN:
		instance->playEffect("music/run.mp3");
		break;
	case AU_HP:
		instance->playEffect("music/get_hp.mp3");
		break;
	case AU_FIGHT:
		instance->playEffect("music/attack.mp3");
		break;
	case AU_DIA:
		instance->playEffect("music/get_other.mp3");
		break;
	case AU_FLOOR:
		instance->playEffect("music/transfer.mp3");
		break;
	case AU_EQUIP:
		instance->playEffect("music/getNewWeapon.mp3");
		break;
	default:
		break;
	}
}

void SoundUtil::playRun(bool status)
{
	if (!DataManager::getInstance()->getEffectSwitch())
	{
		return;
	}
	if (status) {
		if (isFirstRun)
		{
			this->runid = SimpleAudioEngine::getInstance()->playEffect("music/run.mp3", true, 1.0f, -2.0f, 1.0f);
			this->isFirstRun = false;
		}
		else {
			SimpleAudioEngine::getInstance()->resumeEffect(this->runid);
		}
	}
	else {
		SimpleAudioEngine::getInstance()->pauseEffect(this->runid);
	}
}

void SoundUtil::setMusicS(bool type)
{
	DataManager::getInstance()->setMusicSwitch(type);
	if (type)
	{
		this->playBG();
	}
	else {
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
}

void SoundUtil::setEffectS(bool type)
{
	DataManager::getInstance()->setEffectSwitch(type);
	if (!type) {
		SimpleAudioEngine::getInstance()->pauseAllEffects();
	}
}

void SoundUtil::playBG()
{
	if (!DataManager::getInstance()->getMusicSwitch())
	{
		return;
	}
	auto instance = SimpleAudioEngine::getInstance();
	instance->playBackgroundMusic("music/lv.mp3",true);
}



void SoundUtil::setMusicVolume(float value)
{
	float soundValue = value / 100.0f;
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(soundValue);
	DataManager::getInstance()->setMusicVolume(value);
}

void SoundUtil::setEffectVolume(float value)
{
	float soundValue = value / 100.0f;
	SimpleAudioEngine::getInstance()->setEffectsVolume(soundValue);
	DataManager::getInstance()->setEffectVolume(value);
}
