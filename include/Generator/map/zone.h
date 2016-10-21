#ifndef ZONE_H
#define ZONE_H

#include <vector>
#include <memory>
#include "point.h"

namespace map
{

class CrossedEdge;
class Corner;


///
/// \brief Enumeration of all the possible zone biomes.
///
enum Biome {
    OCEAN,
    MARSH,
    ICE,
    LAKE,
    BEACH,
    SNOW,
    TUNDRA,
    BARE,
    SCORCHED,
    TAIGA,
    SHRUBLAND,
    TEMPERATE_DESERT,
    TEMPERATE_RAIN_FOREST,
    TEMPERATE_DECIDUOUS_FOREST,
    GRASSLAND,
    TROPICAL_SEASONAL_FOREST,
    TROPICAL_RAIN_FOREST,
    SUBTROPICAL_DESERT
};

///
/// \brief The Site class
/// Represent the Delaunay triangulation
/// This is the zone as itself, the face of the polygon
///
class Zone
{

public:

    ///
    /// \brief Default constructor.
    /// \param Center's x coordinates
    /// \param Center's y coordinates
    ///
    explicit Zone(double x = 0, double y = 0);

    inline friend std::ostream &operator<<(std::ostream &os, const Zone &s)
    { return os << "[" << s.index << "](" << s.point.x << ", " << s.point.y << ")"; }

    ///
    /// \brief Checks if the zone zone has a neighbor.
    /// \param The zone for which we need to check whether is has neighbors or not.
    ///
    bool    haveNeighbor(Zone *zone);

    ///
    /// \brief Max zone index of the associated Voronoi diagram.
    ///
    static int  indexMax;  // change this

    ///
    /// \brief Zone's index on the associated Voronoi diagram.
    ///
    const int   index;

    ///
    /// \brief (x, y) location of the center of the zone.
    ///
    Point       point;

    ///
    /// \brief True if the zone is a lake or an ocean zone.
    ///
    bool        water;

    ///
    /// \brief True if the zone is an ocean zone.
    ///
    bool        ocean;

    ///
    /// \brief True if the zone touches at least one land and one ocean polygon.
    ///
    bool        coast;

    ///
    /// \brief True if the zone touches the border of the map
    ///
    bool        border;

    ///
    /// \brief Average elevation of the zone's corners (range : 0.0 to 1.0)
    ///
    float       elevation;

    ///
    /// \brief Average moisture of the zone's corners (range : 0.0 to 1.0)
    ///
    float       moisture;

    ///
    /// \brief Zone's biome type.
    ///
    Biome biome;

    ///
    /// \brief Neighboring zones.
    ///
    std::vector<Zone *>         neighbors;

    ///
    /// \brief Edges the zone's polygon.
    ///
    std::vector<CrossedEdge *>  borders;

    ///
    /// \brief Vertices of the zone's polygon.
    ///
    std::vector<Corner *>       corners;
};

}

#endif // ZONE_H
