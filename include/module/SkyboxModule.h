#pragma once

#include "module/AModule.h"
#include "scene/weather/AWeather.h"
#include <map>


class SkyboxModule : public AModule, video::IShaderConstantSetCallBack
{
public:
    SkyboxModule(IrrlichtDevice* _device,
        scene::ICameraSceneNode* _camera)
        : AModule(_device, _camera),
        _active(nullptr),
        _weather(AWeather::E_WEATHER::NONE),
        _night(false),
        _timer(nullptr),
        _lastTime(0),
        _mixFactor(0)
	{
	}
	~SkyboxModule()
	{
	}

	virtual int init();
	virtual int update();

    void setSkybox(bool night, int weather);

    irr::s32 _shader;
    virtual void OnSetConstants(video::IMaterialRendererServices* services, s32 userData);

private:
    void createSkyboxesPair(AWeather::E_WEATHER w, const std::string & pathDay, const std::string & pathNight);
    scene::ISceneNode * createSkybox(const std::string & path);

private:
    // Current active skybox
    scene::ISceneNode * _active;
    AWeather::E_WEATHER _weather;
	bool                _night;

    irr::ITimer * _timer;
    irr::u32      _lastTime;
    float         _mixFactor;

    std::map<AWeather::E_WEATHER,
             std::pair<scene::ISceneNode *, scene::ISceneNode *>>   _skyboxes;

    #define     TIME_OF_DAY     1.0f                // Real time for one day (in min)
    #define     TWILIGHT_START  TIME_OF_DAY * 0.5
    #define     NIGHT_START     TIME_OF_DAY * 0.575
    #define     DAWN_START      TIME_OF_DAY * 0.925
};
