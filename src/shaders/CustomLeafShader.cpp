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

#include    "shaders/CustomLeafShader.h"
#include    "Configuration.h"

#include    <stdexcept>

//
// STATIC MEMBER
//

bool                                CustomLeafShader::m_initialized = false;
irr::video::E_MATERIAL_TYPE         CustomLeafShader::m_material_type = static_cast<irr::video::E_MATERIAL_TYPE>(0);
std::unique_ptr<CustomLeafShader>   CustomLeafShader::m_instance = nullptr;

bool
CustomLeafShader::Initialize(irr::video::IGPUProgrammingServices *gpu)
{
    if (gpu == nullptr)
    {
        throw std::runtime_error("You should pass a valid pointer (not nullptr) to the Initialize static method of the CustomTreeShader.");
    }
    else if (CustomLeafShader::m_initialized == true)
    {
        throw std::runtime_error("You can't initialize two time the CustomTreeShader.");
    }
    CustomLeafShader::m_instance = std::make_unique<CustomLeafShader>();
    irr::s32 result = gpu->addHighLevelShaderMaterialFromFiles(
        RESOURCES_PATH "/shaders/CustomLeafShader.vert", "main", irr::video::EVST_VS_5_0,
        RESOURCES_PATH "/shaders/CustomLeafShader.frag", "main", irr::video::EPST_PS_5_0,
        CustomLeafShader::m_instance.get(),
        irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL, 0, irr::video::EGSL_DEFAULT);
    if (result == -1) return false;
    CustomLeafShader::m_material_type = static_cast<irr::video::E_MATERIAL_TYPE>(result);
    CustomLeafShader::m_initialized = true;
    return true;
}

irr::video::E_MATERIAL_TYPE
CustomLeafShader::GetMaterialType(void)
{
    if (CustomLeafShader::m_initialized == false)
    {
        throw std::runtime_error("The CustomTreeShader hasnt been correctly initialized and your implementation try to get a valid E_MATERIAL_TYPE in order to use it.");
    }
    return CustomLeafShader::m_material_type;
}

bool
CustomLeafShader::IsInitalized(void)
{
    return CustomLeafShader::m_initialized;
}

//
// NON STATIC MEMBER
//

void
CustomLeafShader::OnSetConstants(irr::video::IMaterialRendererServices* services, irr::s32)
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
    texture_layer_id = 1;
    services->setPixelShaderConstant("normal_texture", &texture_layer_id, 1);
    texture_layer_id = 2;
    services->setPixelShaderConstant("alpha_texture", &texture_layer_id, 1);

    services->setPixelShaderConstant("lights.position", &light_position.X, 3);
    services->setPixelShaderConstant("lights.ambient", &light_ambient.X, 3);
    services->setPixelShaderConstant("lights.diffuse", &light_diffuse.X, 3);
    services->setPixelShaderConstant("lights.specular", &light_specular.X, 3);

    services->setPixelShaderConstant("specular_hardness", &specular_hardness, 1);
}

void
CustomLeafShader::OnSetMaterial(const irr::video::SMaterial &material)
{
    this->m_used_material = &material;
}