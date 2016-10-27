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
  bitmap_image texture(m_map->gridSize(), m_map->gridSize());
  m_map->textureGrid().resize(m_map->gridXMax() * m_map->gridYMax());

  for (unsigned int gridX = 0; gridX < m_map->gridXMax(); ++gridX)
    for (unsigned int gridY = 0; gridY < m_map->gridYMax(); ++gridY)
    {
      for (unsigned int x = 0; x < m_map->gridSize(); ++x)
        for (unsigned int y = 0; y < m_map->gridSize(); ++y)
        {
          ::map::HeightPoint & p = m_map->heightMap().pointAt(gridX * m_map->gridSize() + x,
                                                              gridY * m_map->gridSize() + y);
          texture.set_pixel(x, y,
                            static_cast<unsigned char>(p.z * 255.0),
                            static_cast<unsigned char>(p.z * 255.0),
                            static_cast<unsigned char>(p.z * 255.0));
        }
      std::string path = (std::string)RESOURCES_PATH + "/generated/" +
                            std::to_string(gridX) + "_" + std::to_string(gridY) +
                            "texture.bmp";
      std::cout << "Texture generated : " << path << std::endl;
      texture.save_image(path);
      m_map->textureGrid()[gridX + m_map->gridXMax() * gridY] = path; // WARNING, preferable to size the grids and use []

    }
}


}
