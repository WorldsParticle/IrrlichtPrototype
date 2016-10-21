#include "Generator/map/crossededge.h"

namespace map
{

int CrossedEdge::indexMax = 0;
CrossedEdge::CrossedEdge() :
    index(indexMax),
    z0(nullptr),
    z1(nullptr),
    c0(nullptr),
    c1(nullptr),
    midpoint(0, 0),
    river()
{
    ++indexMax;
}

}
