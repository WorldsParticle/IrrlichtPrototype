#include "map/map.h"

namespace map
{

MapGraph::MapGraph(unsigned int xMaxx, unsigned int yMaxx, unsigned int zoneNumber) :
    m_zones(),
    m_corners(),
    m_edges(),
    m_xMax(xMaxx),
    m_yMax(yMaxx),
    m_zoneNumber(zoneNumber),
    m_heightMap(xMaxx, yMaxx)
{
    ::map::Zone::indexMax = 0;
    ::map::Corner::indexMax = 0;
    ::map::CrossedEdge::indexMax = 0;
}

MapGraph::~MapGraph()
{
    for(std::map<int, Zone *>::iterator it = m_zones.begin(); it != m_zones.end(); ++it)
        delete (*it).second;
    for(std::map<int, Corner *>::iterator it = m_corners.begin(); it != m_corners.end(); ++it)
        delete (*it).second;
    for(std::map<int, CrossedEdge *>::iterator it = m_edges.begin(); it != m_edges.end(); ++it)
        delete (*it).second;

    m_zones.clear();
    m_corners.clear();
    m_edges.clear();
}

Zone   *MapGraph::findZone(const Point *p)
{
    if (!p)
        return NULL;

    for(std::map<int, Zone *>::iterator it = m_zones.begin(); it != m_zones.end(); ++it)
        if ((*it).second->point == *p)
            return (*it).second;

    return NULL;
}

}
