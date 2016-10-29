#ifndef MAP_H
#define MAP_H

#include <map>
#include "point.h"
#include "zone.h"
#include "corner.h"
#include "crossededge.h"
#include "heightmap.h"
#include "lake.h"

namespace map
{


///
/// \brief This class stores every information about the map
///
class MapGraph
{
public:
    MapGraph(unsigned int xMax, unsigned int zMax, unsigned int tileSize);

    ///
    /// \brief Copy constructor.
    ///
    ~MapGraph();

    ///
    /// \brief Find the polygon to a 2D (x, y) point (only work if center of the polygon, see zonelookup for better result)
    /// \param point for which we need to find nearest neighbor
    ///
    Zone    *findZone(const Point *p); // ugly and slow

    inline std::map<int, Zone *>        &zones()
    { return m_zones; }

    inline std::map<int, Corner *>      &corners()
    { return m_corners; }

    inline std::map<int, CrossedEdge *> &edges()
    { return m_edges; }

    inline std::list<Lake *> &lakes()
    { return m_lakes; }

    inline double xMax()
    { return m_xMax; }

    inline double zMax()
    { return m_zMax; }

    inline HeightMap   &heightMap()
    { return m_heightMap; }

    inline unsigned int tileSize()
    { return m_tileSize; }

    inline unsigned int gridXMax()
    { return m_gridXMax; }

    inline unsigned int gridZMax()
    { return m_gridZMax; }

    inline std::vector<std::string> &textureGrid()
    { return m_textureGrid; }

    inline std::string &textureAt(unsigned int x, unsigned int z)
    { return m_textureGrid[x * m_zMax + z]; }

    inline std::vector<std::string> &heightmapGrid()
    { return m_heightmapGrid; }

    inline std::string &heightmapAt(unsigned int x, unsigned int z)
    { return m_heightmapGrid[x + m_gridXMax * z]; }

private:

    ///
    /// \brief Map's zones (= Voronoi polygons).
    ///
    std::map<int, Zone *>         m_zones;

    ///
    /// \brief Map's zone's corners (= vertices of the Voronoi polygons).
    ///
    std::map<int, Corner *>       m_corners;

    ///500
    /// \brief Edges of the map (= edges of the Voronoi polygons)
    ///
    std::map<int, CrossedEdge *>  m_edges;

    ///
    /// \brief Width of the map
    ///
    double    m_xMax;

    ///
    /// \brief Height of the map
    ///
    double    m_zMax;

    HeightMap m_heightMap;

    // liste des lacs
    std::list<Lake *> m_lakes;

    /// gestion de la grille de texture (multi terrain)
    unsigned int m_tileSize; // longueur et largeur d'une cellule
    unsigned int m_gridXMax; // nombre de cellules en x
    unsigned int m_gridZMax; // nombre de cellules en z
    std::vector<std::string>  m_textureGrid; // path to the image
    std::vector<std::string>  m_heightmapGrid; // same
};

}

#endif // MAP_H
