#include "map/lake.h"

namespace map
{

Lake::Lake() :
        _points(),
        _perimeterPoints(),
        _zones(),
        _mesh(nullptr)
{
}


Lake::~Lake()
{
}

void    Lake::addPoint(irr::u32 x, irr::u32 y, irr::u32 mapSize)
{
    irr::core::vector2d< irr::u32 > p(x, y);

    _points[y * mapSize + x] = p;
}

void    Lake::addPerimeterPoint(irr::u32 x, irr::u32 y, irr::u32 mapSize)
{
    irr::core::vector2d< irr::u32 > p(x, y);

    _perimeterPoints[y * mapSize + x] = p;
}

void    Lake::addZone(Zone * z)
{
    _zones[z] = z;
}

void    Lake::setMesh(irr::scene::SMesh * mesh)
{
    _mesh = mesh;
}

std::map<irr::u64, irr::core::vector2d< irr::u32 >> &   Lake::getPoints()
{
    return(_points);
}

std::map<irr::u64, irr::core::vector2d< irr::u32 >> &   Lake::getPerimeterPoints()
{
    return(_perimeterPoints);
}

std::map<map::Zone *, map::Zone *> &     Lake::getZones()
{
    return(_zones);
}

bool    Lake::containsPoint(irr::u32 x, irr::u32 y, irr::u32 mapSize)
{
    irr::u64 key = y * mapSize + x;
    if (_points.find(key) != _points.end())
        return (true);
    return (false);
}

bool    Lake::containsPerimeterPoint(irr::u32 x, irr::u32 y, irr::u32 mapSize)
{
    irr::u64 key = y * mapSize + x;
    if (_perimeterPoints.find(key) != _perimeterPoints.end())
        return (true);
    return (false);
}

bool    Lake::containsZone(map::Zone * z)
{
    if (_zones.find(z) != _zones.end())
        return (true);
    return (false);
}

} // END OF NAMESPACE MAP
