#ifndef EDGE_H
#define EDGE_H

#include "map/point.h"
#include "map/zone.h"

namespace vor
{

/*
    A class that stores an edge in Voronoi diagram

    start		: pointer to start point
    end			: pointer to end point
    left		: pointer to Voronoi place on the left side of edge
    right		: pointer to Voronoi place on the right side of edge

    neighbour	: some edges consist of two parts, so we add the pointer to another part to connect them at the end of an algorithm

    direction	: directional vector, from "start", points to "end", normal of |left, right|
    f, g		: directional coeffitients satisfying equation y = f*x + g (edge lies on this line)
*/
///
/// \brief This class stores an edge in a Voronoi diagram.
///
class Edge  // should find a way to not use it
{
public:

    ///
    /// \brief Pointer to start point.
    ///
    Point       *start;

    ///
    /// \brief Pointer to end point.
    ///
    Point       *end;

    ///
    /// \brief Directional vector, from "start", points to "end", normal of |left, right|.
    ///
    Point       *direction;

    ///
    /// \brief Pointer to Voronoi place on the left side of edge.
    ///
    Point       *left;

    ///
    /// \brief Pointer to Voronoi place on the right side of edge.
    ///
    Point       *right;

    ///
    /// \brief Directional coeffitients satisfying equation y = f*x + g (edge lies on this line).
    ///
    double		f;

    ///
    /// \brief Directional coeffitients satisfying equation y = f*x + g (edge lies on this line).
    ///
    double		g;

    ///
    /// \brief Some edges consist of two parts, so we add the pointer to another part to connect them at the end of an algorithm.
    ///
    Edge * neighbour;

    /*
        Constructor of the class

        s		: pointer to start
        l		: pointer to left place
        r		: pointer to right place
    */

    ///
    /// \brief Default constructor.
    /// \param Pointer to start
    /// \param Pointer to left place.
    /// \param Pointer to right place.
    ///
    Edge(Point *s, Point *l, Point *r) :
        start(s),
        end(nullptr),
        direction(nullptr),
        left(l),
        right(r),
        f(0.0),
        g(0.0),
        neighbour(nullptr)
    {


        f = (r->x - l->x) / (l->y - r->y) ;
        g = s->y - f * s->x ;

        // Revoir
        direction = new Point((r->y - l->y),
                              -(r->x - l->x));
    }

    inline friend std::ostream &operator<<(std::ostream &os, const Edge &e)
    { return os << "[" << *e.left << "|" << *e.right << "]s" << *e.start << "d" << *e.direction; }
};

}

#endif // EDGE_H
