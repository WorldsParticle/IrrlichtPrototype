//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; If not, see <http://www.gnu.org/licenses/>.
//
// Copyright (C) WorldsParticle
//

#pragma once

#include <irrlicht.h>
#include "driverChoice.h"

class MyEventReceiver;
class ElementsModule;
class SkyboxModule;
class TerrainModule;
class WaterModule;
class SoundModule;
class ParticleModule;
class GUIModule;

class Core
{
public:
    ///
    /// \brief Default constructor. Take the main parameter as argument
    /// \param argc the number of arguments in argv
    /// \param argv the arguments used to launch the project.
    ///
	Core(int argc, char *argv[]);

    ///
    /// \brief Destructor.
    ///
    /// The destructor drop the device if the device is not null.
    ///
	~Core(void);

public:
    ///
    /// \brief Run the core and launch the application.
    /// \return 0 if everything goes well, an error number otherwise.
    ///
    int     run(void);

public:
    ///
    /// \brief Getter for the irrlicht module.
    ///
    irr::IrrlichtDevice     *getIrrlichtDevice(void)
    {
        return _device;
    }

    ///
    /// \brief Getter for the active camera in the scene manager.
    /// \return A pointer to an active camera.
    ///
    irr::scene::ICameraSceneNode    *getActiveCamera(void)
    {
        return _device->getSceneManager()->getActiveCamera();
    }

    ///
    /// \brief Getter for the Element module.
    ///
    ElementsModule  *getElementsModule(void)
    {
        return _elementsModule;
    }

    ///
    /// \brief Getter for the skybox module.
    ///
    SkyboxModule    *getSkyboxModule(void)
    {
        return _skyboxModule;
    }

    ///
    /// \brief Getter for the terrain module.
    ///
    TerrainModule   *getTerrainModule(void)
    {
        return _terrainModule;
    }

    ///
    /// \brief Getter for the water module.
    ///
    WaterModule     *getWaterModule(void)
    {
        return _waterModule;
    }

    ///
    /// \brief Getter for the sound module.
    ///
    SoundModule     *getSoundModule(void)
    {
        return _soundModule;
    }

    ///
    /// \\brief Getter for the particle module.
    ///
    ParticleModule  *getParticleModule(void)
    {
        return _particleModule;
    }

    ///
    /// \brief Getter for the GUI module.
    ///
    GUIModule       *getGUIModule(void)
    {
        return _GUIModule;
    }

private:
    ///
    /// \brief Set some usefull parameter in irrlicht engine.
    ///
    void    initIrrlicht(void);

    ///
    /// \brief This method is used to create the irrlicht device and set some usefull pointer.
    ///
    void    createIrrlichtDevice(void);

    ///
    /// \brief Initialise differents irrlicht modules.
    ///
    /// Here is the list of module currently used : 
    ///
    ///     - ElementsModule
    ///     - SkyboxModule
    ///     - TerrainModule
    ///     - WaterModule
    ///     - SoundModule
    ///     - ParticleModule
    ///
    int     initModules(void);

    ///
    ///  \brief Launch the game loop when everything is well initialised.
    ///
    int     gameLoop(void);

    ///
    /// \brief Create an irrlicht FPS camera and store the pointer into _camera.
    ///
    void    createFPSCamera(void);

    ///
    /// \brief Update the active module used in the core.
    ///
    void    updateModules(void);

private:
    ///
    /// \brief Custom event receiver.
    ///
	MyEventReceiver			*_receiver;

    ///
    /// \brief Elements module
    ///
	ElementsModule			*_elementsModule;

    ///
    /// \brief Skybox module
    ///
	SkyboxModule			*_skyboxModule;

    ///
    /// \brief Terrain module
    ///
    TerrainModule			*_terrainModule;

    ///
    /// \brief Water module.
    ///
	WaterModule			    *_waterModule;

    ///
    /// \brief Sound module
    ///
	SoundModule			    *_soundModule;

    ///
    /// \brief Particle module
    ///
	ParticleModule			*_particleModule;

    ///
    /// \brief The GUI Module.
    ///
    GUIModule               *_GUIModule;

    ///
    /// \brief Irrlicht device, core module of the irrlicht library.
    ///
    irr::IrrlichtDevice		*_device;

    ///
    /// \brief Store the window size that should be used to create the irrlicht window.
    ///
    irr::core::dimension2d<irr::u32> _windowSize;

    ///
    /// \brief Store the value true if the irrlicht window should be in fullscreen or false otherwise.
    ///
    bool    _fullscreen;
};

