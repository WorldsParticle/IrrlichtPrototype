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
// Copyright (C) 2016 Martin-Pierrat Louis (louismartinpierrat@gmail.com)
//

#include    <irrlicht.h>
#include    <memory>

///
/// This class is used to implement a custom shader.
/// This custom shader should be used to draw tree with transparency.
///
class   CustomTreeShader : public irr::video::IShaderConstantSetCallBack
{
public:
    ///
    /// Initialize the shader in the GPU.
    ///
    static bool     Initialize(irr::video::IGPUProgrammingServices *gpu);

    ///
    /// Return a valid E_MATERIAL_TYPE if the shader has been initialized. Otherwise throw a runtime_error.
    ///
    static irr::video::E_MATERIAL_TYPE  GetMaterialType(void);

    ///
    /// return true if the shader has been already correctly initialized. Otherwise return false.
    ///
    static bool     IsInitalized(void);

public:
    /// Should not be used, only by the irrlicht engine.
    virtual void    OnSetConstants(irr::video::IMaterialRendererServices* services, irr::s32 userData);
    /// Should not be used, only by the irrlicht engine.
    virtual void    OnSetMaterial(const irr::video::SMaterial &material);

private:
    ///
    /// The material applied to the shader.
    ///
    const irr::video::SMaterial     *m_used_material;

    ///
    /// Store if the shader has been already initialized.
    ///
    static bool     m_initialized;

    ///
    /// Store the new material type created during the initialization process.
    ///
    static irr::video::E_MATERIAL_TYPE  m_material_type;

    ///
    /// Internally used.
    ///
    static std::unique_ptr<CustomTreeShader>    m_instance;
};