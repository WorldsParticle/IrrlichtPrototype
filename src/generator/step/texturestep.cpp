#include "generator/step/texturestep.h"
#include "tool/bitmap_image.h"

#include "Configuration.h"

namespace gen {

TextureStep::TextureStep(const std::string &name) :
  GenerationStep(name)
{

}

TextureStep::~TextureStep()
{

}

void TextureStep::run()
{
  //paintTextureGrid();
}

void TextureStep::paintTextureGrid()
{
  bitmap_image texture(m_map->tileSize(), m_map->tileSize());
  m_map->textureGrid().resize(m_map->gridXMax() * m_map->gridZMax());

  for (unsigned int gridX = 0; gridX < m_map->gridXMax(); ++gridX)
    for (unsigned int gridZ = 0; gridZ < m_map->gridZMax(); ++gridZ)
    {
      for (unsigned int x = 0; x < m_map->tileSize(); ++x)
        for (unsigned int z = 0; z < m_map->tileSize(); ++z)
        {
          ::map::HeightPoint & p = m_map->heightMap().pointAt(gridX * m_map->tileSize() + x,
                                                              gridZ * m_map->tileSize() + z);
          texture.set_pixel(x, z,
                            static_cast<unsigned char>(p.z * 255.0),
                            static_cast<unsigned char>(p.z * 255.0),
                            static_cast<unsigned char>(p.z * 255.0));
        }
      std::string path = (std::string)RESOURCES_PATH + "/generated/" +
                            std::to_string(gridX) + "_" + std::to_string(gridZ) +
                            "texture.bmp";
      std::cout << "Texture generated : " << path << std::endl;
      texture.save_image(path);
      m_map->textureGrid()[gridX + m_map->gridXMax() * gridZ] = path; // WARNING, preferable to size the grids and use []

    }
}


}
