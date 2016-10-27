#ifndef CROSSEDEDGE_H
#define CROSSEDEDGE_H

#include <memory>
#include "point.h"
#include "zone.h"

namespace map
{

class Zone;
class Corner;

///
/// \brief The CrossedEdge class
/// represent both edge of Voronoi and Delaunay graph
/// allowing to connect them together
/// it is the cross point you can see between black and white segment in http://www-cs-students.stanford.edu/~amitp/game-programming/polygon-map-generation/voronoi-and-delaunay.png
/// \todo mettre le coeff directeur des deux droites
///
class CrossedEdge
{

public:

    ///
    /// \brief Default constructor.
    ///
    explicit CrossedEdge();

    inline friend std::ostream &operator<<(std::ostream &os, const CrossedEdge &e)
    { return os << "[" << e.index << "](" << e.z0->index << ", " << e.z1->index << ") mid" << e.midpoint; }

    ///
    /// \brief Max crossededge index in the associated Voronoi diagram
    ///
    static int  indexMax;

    ///
    /// \brief Crossededge's index in the associated Voronoi diagram
    ///
    const int   index;

    ///
    /// \brief Both side zones, which draw Delaunay (z0 used as left & z1 as right during computing)
    ///
    Zone         *z0, *z1;

    ///
    /// \brief Both end corners, draws a Voronoi edge
    ///
    Corner       *c0, *c1;

    ///
    /// \brief Location of the mid point of the edge
    ///
    Point       midpoint;

    ///
    /// \brief Number of rivers going through the edge
    ///
    int         river;
};

}

#endif // CROSSEDEDGE_H
