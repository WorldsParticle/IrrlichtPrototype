#ifndef CORNER_H
#define CORNER_H

#include <vector>
#include <memory>
#include "point.h"

namespace map
{

class Zone;
class CrossedEdge;

///
/// \brief The Corner class (vertex)
/// represent the vertices of zones
/// contains the shape of Voronoi polygons
///
class Corner
{

public:

    explicit Corner();

    inline friend std::ostream &operator<<(std::ostream &os, const Corner &c)
    { return os << "[" << c.index << "]" << c.point; }

    ///
    /// \brief Max corner index in for the associated Voronoi Diagram
    ///
    static int  indexMax;  // change this

    ///
    /// \brief Index of the corner in the associated Voronoi Diagram
    ///
    const int   index;

    ///
    /// \brief Location (x, y) of the corner
    ///
    Point   point;

    ///
    /// \brief True if the corner is an ocean corner
    ///
    bool    ocean;

    ///
    /// \brief True is the corner is a lake or ocean corner
    ///
    bool    water;

    ///
    /// \brief True if the corner touches ocean and land polygons
    ///
    bool    coast;

    ///
    /// \brief True if the corner is at the edge of the map
    ///
    bool    border;

    ///
    /// \brief Corner elevation (range : 0.0 to 1.0)
    ///
    float   elevation;

    ///
    /// \brief Corner moisture (range : 0.0 to 1.0)
    ///
    float   moisture;

    ///
    /// \brief Faces touching the corner
    ///
    std::vector<Zone *>         faces;

    ///
    /// \brief Edges touching the corner
    ///
    std::vector<CrossedEdge *>  edges;

    ///
    /// \brief All the corners linked to this corner by an edge
    ///
    std::vector<Corner *>       adjacent;

    ///
    /// \brief Number of rivers going through the corner
    ///
    int     river;     // 0 if no river, or volume of water in river

    ///
    /// \brief Adjacent corner with the lowest elevation
    ///
    Corner  *downslope; // pointer to adjacent corner most downhill

    ///
    /// \brief Pointer to a coastal corner, or null
    ///
    Corner  *watershed; // pointer to coastal corner, or null

    ///
    /// \brief Size of the watershed
    ///
    int     watershedSize;

    ///
    /// \brief Copy constructor.
    ///
    Corner(const Corner& other);

    ///
    /// \brief Move constructor.
    ///
    Corner(Corner&& other);

    ///
    /// \brief Copy assignment operator.
    ///
    Corner& operator=(const Corner& other);

    ///
    /// \brief Move assignment operator.
    ///
    Corner& operator=(Corner&& other);
};

}

#endif // CORNER_H
