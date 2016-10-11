#include "Generator/map/corner.h"

namespace map
{

int Corner::indexMax = 0;
Corner::Corner() :
    index(indexMax),
    point(0, 0),
    ocean(false),
    water(false),
    coast(false),
    border(false),
    elevation(0.0),
    moisture(0.0),
    faces(),
    edges(),
    adjacent(),
    river(0),
    downslope(),
    watershed(),
    watershedSize(0)
{
    ++indexMax;
}

Corner::Corner(const Corner& other) :
index(other.index),
point(other.point.x, other.point.y),
ocean(other.ocean),
water(other.water),
coast(other.coast),
border(other.border),
elevation(other.elevation),
moisture(other.moisture),
faces(other.faces),
edges(other.edges),
adjacent(other.adjacent),
river(other.river),
downslope(other.downslope),
watershed(other.watershed),
watershedSize(other.watershedSize)
{
}

Corner::Corner(Corner&& other) :
    index(other.index),
    point(other.point.x, other.point.y),
    ocean(other.ocean),
    water(other.water),
    coast(other.coast),
    border(other.border),
    elevation(other.elevation),
    moisture(other.moisture),
    faces(other.faces),
    edges(other.edges),
    adjacent(other.adjacent),
    river(other.river),
    downslope(other.downslope),
    watershed(other.watershed),
    watershedSize(other.watershedSize)
{
}

Corner& Corner::operator=(const Corner& other)
{
if (&other != this)
{
    *(const_cast<int *>(&(this->index))) = other.index;
    point = Point(other.point.x, other.point.y);
    ocean = other.ocean;
    water = other.water;
    coast = other.coast;
    border = other.border;
    elevation = other.elevation;
    moisture = other.moisture;
    faces = other.faces;
    edges = other.edges;
    adjacent = other.adjacent;
    river = other.river;
    downslope = other.downslope;
    watershed = other.watershed;
    watershedSize = other.watershedSize;
}
return *this;
}

Corner& Corner::operator=(Corner&& other)
{
if (&other != this)
{
    *(const_cast<int *>(&(this->index))) = other.index;
    point = Point(other.point.x, other.point.y);
    ocean = other.ocean;
    water = other.water;
    coast = other.coast;
    border = other.border;
    elevation = other.elevation;
    moisture = other.moisture;
    faces = other.faces;
    edges = other.edges;
    adjacent = other.adjacent;
    river = other.river;
    downslope = other.downslope;
    watershed = other.watershed;
    watershedSize = other.watershedSize;
}
return *this;
}

}
