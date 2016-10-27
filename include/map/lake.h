#ifndef LAKE_H
#define LAKE_H

#include <irrlicht.h>
#include <iostream>
#include <limits>
#include <cmath>
#include <list>
#include <map>

#include "map/zone.h"

namespace map
{

class   Lake
{
public:
    Lake();
    ~Lake();

    void                                                        addPoint(irr::u32 x, irr::u32 y, irr::u32 mapSize);
    void                                                        addPerimeterPoint(irr::u32 x, irr::u32 y, irr::u32 mapSize);
    void                                                        addZone(Zone * z);

    std::map<irr::u64, irr::core::vector2d< irr::u32 >> &       getPoints();
    std::map<irr::u64, irr::core::vector2d< irr::u32 >> &       getPerimeterPoints();
    std::map<Zone *, Zone *> &                                  getZones();

    bool                                                        containsPoint(irr::u32 x, irr::u32 y, irr::u32 mapSize);
    bool                                                        containsPerimeterPoint(irr::u32 x, irr::u32 y, irr::u32 mapSize);
    bool                                                        containsZone(Zone * z);

private:

    // u64 key accomodates for up to 2^32 * 2^32 map size,
    // if you'd ever need more, a time machine should have been built by then
    // please come back in 2016 and leave a git issue.
    std::map<irr::u64, irr::core::vector2d< irr::u32 >> _points;

    std::map<irr::u64, irr::core::vector2d< irr::u32 >> _perimeterPoints;

    std::map<Zone *, Zone *>                            _zones;
};

} // END OF NAMESPACE MAP

#endif // LAKE_H
