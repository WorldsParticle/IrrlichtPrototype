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

#include    "AModule.h"

class   GUIModule : public AModule
{
public:
    ///
    /// \brief Default constructor
    /// \param device The irrlicht device used in the application context.
    /// \param camera The main camera used by the application.
    ///
    GUIModule(IrrlichtDevice *device, scene::ICameraSceneNode *camera);

    ///
    /// \brief Destructor.
    ///
    ~GUIModule(void);

public:
    ///
    /// \brief Getter to know if the GUI Module should be visible or not.
    /// \return True if the GUI Module is visible, false otherwise.
    ///
    bool    isVisible(void) const
    {
        return _isVisible;
    }

public:
    ///
    /// \brief Set the visibility of the GUI module, if the visibility is set to false no GUI element should be drawn.
    /// \param visibility Replace the old visibility mode.
    ///
    void    setVisible(bool visibility)
    {
        _isVisible = visibility;
    }

public:
    ///
    ///
    ///
    virtual int     init(void);
    virtual int     update(void);

private:
    bool    _isVisible;

    ///
    /// 
    ///
    irr::gui::IGUIStaticText    *_console;
};