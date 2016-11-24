#include "Configuration.h"

#include "generator/step/heightmapingstep.h"
#include "generator/step/lakerstep.h"
#include "map/heightmap.h"
#include "map/heightpoint.h"

namespace gen
{

HeightMapingStep::HeightMapingStep(const std::string &name) :
    GenerationStep(name),
    m_zoneLookUp()
{
}

HeightMapingStep::~HeightMapingStep()
{

}

// crée une bitmap coloriée en en greyscale selon l'humidité des points
void    HeightMapingStep::paintByMoisture()
{
    int _height = static_cast<int>(m_map->zMax());
    int _width = static_cast<int>(m_map->xMax());
    bitmap_image m_image(_width, _height);
    m_image.clear();

    for (int i = 0; i < _height; ++i)
        for (int j = 0; j < _width; ++j)
        {
            ::map::HeightPoint & p = m_map->heightMap().pointAt(j, i);
            if (p.zone->ocean)
                m_image.set_pixel(j, _height - i - 1, 0, 0, 125);
            else
                m_image.set_pixel(j, _height - i - 1, static_cast<unsigned char>(p.zone->moisture * 255.0f), static_cast<unsigned char>(p.zone->moisture * 255.0f), static_cast<unsigned char>(p.zone->moisture * 255.0f));
        }
    m_image.save_image((std::string)RESOURCES_PATH + "/mapmoisture.bmp");
}

// crée une bitmap coloriée en greyscale selon la hauteur des points
void    HeightMapingStep::paintByHeight()
{
    int _height = static_cast<int>(m_map->zMax());
    int _width = static_cast<int>(m_map->xMax());
    bitmap_image m_image(_width, _height);
    m_image.clear();

    for (int i = 0; i < _height; ++i)
        for (int j = 0; j < _width; ++j)
        {
            ::map::HeightPoint & p = m_map->heightMap().pointAt(j, i);
            /*if (p.zone->ocean)
                m_image.set_pixel(j, _height - i - 1, 0, 0, 125);
            else*/
                m_image.set_pixel(j, _height - i - 1, static_cast<unsigned char>(p.z * 255.0), static_cast<unsigned char>(p.z * 255.0), static_cast<unsigned char>(p.z * 255.0));
        }
    m_image.save_image((std::string)RESOURCES_PATH + "/mapheight.bmp");
}

// crée une bitmap qui assigne différentes couleures selon le land time (bordure, océan, beach/coast et water
void    HeightMapingStep::paintByLandType()
{
    int _height = static_cast<unsigned int>(m_map->zMax());
    int _width = static_cast <unsigned int>(m_map->xMax());
    bitmap_image m_image(_width, _height);
    m_image.clear();

    for (int i = 0; i < _height; ++i)
        for (int j = 0; j < _width; ++j)
        {
            ::map::HeightPoint & p = m_map->heightMap().pointAt(j, i);
            if (p.zone->border)
                m_image.set_pixel(j, _height - i - 1, 200, 50, 50);
            else if (p.zone->ocean)
                m_image.set_pixel(j, _height - i - 1, 50, 50, 200);
            else if (p.zone->coast)
                m_image.set_pixel(j, _height - i - 1, 255, 255, 204);
            else if (p.zone->water)
                m_image.set_pixel(j, _height - i - 1, 0, 255, 255);
            else
                m_image.set_pixel(j, _height - i - 1, 255, 200, 130);
        }
    m_image.save_image((std::string)RESOURCES_PATH + "/maptype.bmp");
}

// crée une bitmap qui colorie les zones selon leur biome
void    HeightMapingStep::paintByBiome()
{
    int _height = static_cast<int>(m_map->zMax());
    int _width = static_cast<int>(m_map->xMax());
    bitmap_image m_image(_width, _height);
    m_image.clear();

    for (int i = 0; i < _height; ++i)
        for (int j = 0; j < _width; ++j)
        {
            ::map::HeightPoint & p = m_map->heightMap().pointAt(j, i);
            if (p.zone->biome == ::map::BEACH)
                m_image.set_pixel(j, _height - i - 1, 255, 255, 204);
            else if (p.zone->biome == ::map::OCEAN)
                m_image.set_pixel(j, _height - i - 1, 26, 0, 153);
            else if (p.zone->biome == ::map::MARSH)
                m_image.set_pixel(j, _height - i - 1, 0, 204, 153);
            else if (p.zone->biome == ::map::ICE)
                m_image.set_pixel(j, _height - i - 1, 220, 250, 255);
            else if (p.zone->biome == ::map::LAKE)
                m_image.set_pixel(j, _height - i - 1, 61, 139, 255);
            else if (p.zone->biome == ::map::SNOW)
                m_image.set_pixel(j, _height - i - 1, 248, 248, 248);
            else if (p.zone->biome == ::map::TUNDRA)
                m_image.set_pixel(j, _height - i - 1, 208, 208, 176);
            else if (p.zone->biome == ::map::BARE)
                m_image.set_pixel(j, _height - i - 1, 176, 176, 176);
            else if (p.zone->biome == ::map::SCORCHED)
                m_image.set_pixel(j, _height - i - 1, 144, 144, 144);
            else if (p.zone->biome == ::map::TAIGA)
                m_image.set_pixel(j, _height - i - 1, 204, 212, 187);
            else if (p.zone->biome == ::map::SHRUBLAND)
                m_image.set_pixel(j, _height - i - 1, 196, 204, 187);
            else if (p.zone->biome == ::map::TEMPERATE_DESERT)
                m_image.set_pixel(j, _height - i - 1, 228, 232, 202);
            else if (p.zone->biome == ::map::TEMPERATE_RAIN_FOREST)
                m_image.set_pixel(j, _height - i - 1, 164, 196, 168);
            else if (p.zone->biome == ::map::TEMPERATE_DECIDUOUS_FOREST)
                m_image.set_pixel(j, _height - i - 1, 180, 196, 169);
            else if (p.zone->biome == ::map::GRASSLAND)
                m_image.set_pixel(j, _height - i - 1, 196, 212, 170);
            else if (p.zone->biome == ::map::TROPICAL_SEASONAL_FOREST)
                m_image.set_pixel(j, _height - i - 1, 169, 204, 164);
            else if (p.zone->biome == ::map::TROPICAL_RAIN_FOREST)
                m_image.set_pixel(j, _height - i - 1, 228, 232, 202);
            else if (p.zone->biome == ::map::SUBTROPICAL_DESERT)
                m_image.set_pixel(j, _height - i - 1, 233, 221, 199);

        }
    m_image.save_image((std::string)RESOURCES_PATH + "/mapbiome.bmp");
}

void    HeightMapingStep::run()
{
    // seed pour le bruit
    //int seed = rand() % 1000000;

    m_zoneLookUp.createCloud(m_map);
    for (unsigned int i = 0; i < m_map->xMax(); ++i)
    {
        for (unsigned int j = 0; j < m_map->zMax(); ++j)
        {
            ::map::HeightPoint &p = m_map->heightMap().pointAt(i, j);
            p.x = static_cast<double>(i);
            p.z = static_cast<double>(j);
            ::map::Zone *z;
            // trouve la zone à laquelle appartient le pixel en (i, j)
            z = m_zoneLookUp.getNearestZone(static_cast<double>(i), static_cast<double>(j));
            p.zone = z;

            float elevation = 0.0;
            for (auto & e : z->borders)
            {
                glm::vec3 a, b, c;
                a.x = static_cast<float>(z->point.x);
                a.y = z->elevation;
                a.z = static_cast<float>(z->point.z);

                b.x = static_cast<float>(e->c0->point.x);
                b.y = e->c0->elevation;
                b.z = static_cast<float>(e->c0->point.z);

                c.x = static_cast<float>(e->c1->point.x);
                c.y = e->c1->elevation;
                c.z = static_cast<float>(e->c1->point.z);

                if (::map::HeightMap::pointInsideTrigon(glm::vec3(static_cast<float>(i), 0.0, static_cast<float>(j)), a, b, c))
                {
                    glm::vec3 cross;
                    float d;
                    b = b - a;
                    c = c - a;
                    cross = glm::cross(b, c);
                    d = cross.x * a.x + cross.y * a.y + cross.z * a.z;
                    elevation = (d - cross.x * static_cast<float>(i) - static_cast<float>(j) * cross.z) / cross.y;
                    break;
                }
            }
            // génère du bruit aléatoire
            /*float  additionalNoise = octave_noise_2d(8.0f, 0.5f, 0.012f, static_cast<float>(j) + static_cast<float>(seed), static_cast<float>(i) + static_cast<float>(seed));
            additionalNoise = additionalNoise / 10.0f;*/

            // set le y du point sur la heightmap
            p.y = static_cast<double>(elevation); //+ additionalNoise;
            if (p.y > 1.0)
                p.y = 1.0;
        }
    }
    //m_map->heightMap().generateMesh();

    // LakerStep needs to be done after setting heights, but before generating the heightmaps.
    GenerationStep * g = new LakerStep("Laker");
    g->launch(m_map);
    delete(g);

    paintByBiome();
    paintByHeight();
    paintByLandType();

    paintByMoisture();
    paintHeightmapGrid();
}

void   HeightMapingStep::paintHeightmapGrid()
{
  bitmap_image heightmap(m_map->tileSize(), m_map->tileSize());
  m_map->heightmapGrid().resize(m_map->gridXMax() * m_map->gridZMax());

  for (unsigned int gridX = 0; gridX < m_map->gridXMax(); ++gridX)
    for (unsigned int gridZ = 0; gridZ < m_map->gridZMax(); ++gridZ)
    {
      for (unsigned int x = 0; x < m_map->tileSize(); ++x)
        for (unsigned int z = 0; z < m_map->tileSize(); ++z)
        {
          ::map::HeightPoint *p;
        /*  if (x > (m_map->gridSize() - 50) && gridX < (m_map->gridXMax() - 1))
          {
            p = &m_map->heightMap().pointAt(gridX * m_map->tileSize() + m_map->tileSize(),
          gridY * m_map->tileSize() + z);
                                                      }
          else if (x < 50 && gridX != 0)
          {
            p = &m_map->heightMap().pointAt(gridX * m_map->tileSize(),
          gridZ * m_map->tileSize() + e);
                                                            }
          else
          {*/
          p = &m_map->heightMap().pointAt(gridX * m_map->tileSize() + x,
                                                              gridZ * m_map->tileSize() + z);
                                                            //}
          heightmap.set_pixel(x, z,
                            static_cast<unsigned char>(p->y * 255.0),
                            static_cast<unsigned char>(p->y * 255.0),
                            static_cast<unsigned char>(p->y * 255.0));
        }
      std::string path = (std::string)RESOURCES_PATH + "/generated/" +
                          std::to_string(gridZ) + "z_" + std::to_string(gridX) +
                          "x_heightmap.bmp";
      std::cout << "Heightmap generated : " << path << std::endl;
      heightmap.save_image(path);
      m_map->heightmapGrid()[gridX + m_map->gridXMax() * gridZ] = path; // WARNING, preferable to size the grids and use []
    }
}

}
