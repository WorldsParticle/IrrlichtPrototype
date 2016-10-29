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

#include    "shaders/CustomTreeShader.h"
#include    "Configuration.h"

#include    <stdexcept>

//
// STATIC MEMBER
//

bool                                CustomTreeShader::m_initialized = false;
irr::video::E_MATERIAL_TYPE         CustomTreeShader::m_material_type = static_cast<irr::video::E_MATERIAL_TYPE>(0);
std::unique_ptr<CustomTreeShader>   CustomTreeShader::m_instance = nullptr;

bool
CustomTreeShader::Initialize(irr::video::IGPUProgrammingServices *gpu)
{
    if (gpu == nullptr)
    {
        throw std::runtime_error("You should pass a valid pointer (not nullptr) to the Initialize static method of the CustomTreeShader.");
    }
    else if (CustomTreeShader::m_initialized == true)
    {
        throw std::runtime_error("You can't initialize two time the CustomTreeShader.");
    }
    CustomTreeShader::m_instance = std::make_unique<CustomTreeShader>();
    irr::s32 result = gpu->addHighLevelShaderMaterialFromFiles(
        RESOURCES_PATH "/shaders/CustomTreeShader.vert", "main", irr::video::EVST_VS_5_0,
        RESOURCES_PATH "/shaders/CustomTreeShader.frag", "main", irr::video::EPST_PS_5_0,
        CustomTreeShader::m_instance.get(),
        irr::video::EMT_NORMAL_MAP_SOLID, 0, irr::video::EGSL_DEFAULT);
    if (result == -1) return false;
    CustomTreeShader::m_material_type = static_cast<irr::video::E_MATERIAL_TYPE>(result);
    CustomTreeShader::m_initialized = true;
    return true;
}

irr::video::E_MATERIAL_TYPE
CustomTreeShader::GetMaterialType(void)
{
    if (CustomTreeShader::m_initialized == false)
    {
        throw std::runtime_error("The CustomTreeShader hasnt been correctly initialized and your implementation try to get a valid E_MATERIAL_TYPE in order to use it.");
    }
    return CustomTreeShader::m_material_type;
}

bool
CustomTreeShader::IsInitalized(void)
{
    return CustomTreeShader::m_initialized;
}

//
// NON STATIC MEMBER
//

void
CustomTreeShader::OnSetConstants(irr::video::IMaterialRendererServices* services, irr::s32)
{
    auto    driver = services->getVideoDriver();
    irr::core::matrix4  model = driver->getTransform(irr::video::ETS_WORLD);
    irr::core::matrix4  view = driver->getTransform(irr::video::ETS_VIEW);
    irr::core::matrix4  projection = driver->getTransform(irr::video::ETS_PROJECTION);
    irr::core::matrix4  modelview = view * model;
    irr::core::matrix4  modelviewprojection = projection * view * model;

    services->setVertexShaderConstant("modelview", modelview.pointer(), 16);
    services->setVertexShaderConstant("modelviewprojection", modelviewprojection.pointer(), 16);

    // Pixel shader constants

    irr::core::vector3df    light_position(20000.0f, 20000.0f, -20000.0f);
    irr::core::vector3df    light_ambient(0.1f, 0.1f, 0.1f);
    irr::core::vector3df    light_diffuse(0.95f, 0.0f, 0.0f);
    irr::core::vector3df    light_specular(0.0f, 0.0f, 0.0f);

    irr::f32    specular_hardness = 100.0f;
    irr::s32    texture_layer_id = 0;

    services->setPixelShaderConstant("diffuse_texture", &texture_layer_id, 1);

    services->setPixelShaderConstant("lights.position", &light_position.X, 3);
    services->setPixelShaderConstant("lights.ambient", &light_ambient.X, 3);
    services->setPixelShaderConstant("lights.diffuse", &light_diffuse.X, 3);
    services->setPixelShaderConstant("lights.specular", &light_specular.X, 3);

    services->setPixelShaderConstant("specular_hardness", &specular_hardness, 1);
}

void
CustomTreeShader::OnSetMaterial(const irr::video::SMaterial &material)
{
    this->m_used_material = &material;
}