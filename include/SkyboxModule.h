#pragma once

#include "AModule.h"
#include "AWeather.h"
#include <map>


class SkyboxModule : public AModule
{
public:
    SkyboxModule(IrrlichtDevice* _device,
        scene::ICameraSceneNode* _camera)
        : AModule(_device, _camera),
        _active(nullptr),
        _weather(AWeather::E_WEATHER::NONE),
        _night(false)
	{
	}
	~SkyboxModule()
	{
	}

	virtual int init();
	virtual int update();

    void activate(bool night);
    // Temporary setter for testing purpose (Cf MyEventReceiver.cpp)
    void setWeather(AWeather::E_WEATHER weather) { _weather = weather; }

    inline bool  night() const
    { return _night; }

private:
    scene::ISceneNode *createSkybox(const std::string & path);

private:
    // Current active skybox
    scene::ISceneNode * _active;
    AWeather::E_WEATHER _weather;
	bool		        _night;

    std::map<AWeather::E_WEATHER,
             std::pair<scene::ISceneNode *, scene::ISceneNode *>>   _skyboxes;
};
