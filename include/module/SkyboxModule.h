#pragma once

#include "module/AModule.h"
#include "module/TimerModule.h"
#include "scene/weather/AWeather.h"
#include <map>

// Real time length for one day (in min)
#define     DAY_LENGTH      1.0f

class SkyboxModule : public AModule, video::IShaderConstantSetCallBack
{
public:
    SkyboxModule(Core *c, IrrlichtDevice* _device,
        scene::ICameraSceneNode* _camera,
        TimerModule * timerModule)
        : AModule(c, _device, _camera),
        _active(nullptr),
        _weather(AWeather::E_WEATHER::NONE),
        _night(false),
        _timer(timerModule),
        _mixFactor(0)
	{
	}
	~SkyboxModule()
	{
	}

public:
	virtual int init();
	virtual int update();

    virtual void OnSetConstants(video::IMaterialRendererServices* services, s32 userData);

    void setSkybox(bool night, int weather);

public:
    irr::s32 _shader;

  inline scene::ISceneNode *skybox() const
  { return _active; }


private:
    void createSkyboxesPair(AWeather::E_WEATHER w, const std::string & pathDay, const std::string & pathNight);
    scene::ISceneNode * createSkybox(const std::string & path);

private:
    // Current active skybox
    scene::ISceneNode * _active;
    AWeather::E_WEATHER _weather;
	bool                _night;

    TimerModule * _timer;
    float         _mixFactor;

    std::map<AWeather::E_WEATHER,
             std::pair<scene::ISceneNode *, scene::ISceneNode *>>   _skyboxes;
};
