#include "map/zone.h"

namespace map
{

int Zone::indexMax = 0;
Zone::Zone(double x, double y) :
    index(indexMax),
    point(x, y),
    water(false),
    ocean(false),
    coast(false),
    border(false),
    elevation(0.0),
    moisture(0.0),
    biome(),
    neighbors(),
    borders(),
    corners()
{
    ++indexMax;
}

bool    Zone::haveNeighbor(Zone *zone)
{
    for (const auto &z: neighbors)
        if (z == zone)
            return true;
    return false;
}

}
