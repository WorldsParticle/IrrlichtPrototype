#ifndef HALFEDGE_H
#define HALFEDGE_H

namespace map
{

class Zone;
class CrossedEdge;
class Corner;

///
/// \brief The halfEdge class
/// see the wikipedia link for more details (doubly connected edge list)
/// \todo index as the other ?
///
class HalfEdge
{
    ///
    /// \brief Crossed-edge associated with the half-edge (represents a voronoi edge).
    ///
    CrossedEdge *edge; // here represent the Voronoi one

    ///
    /// \brief Zone from which the half-edge departs.
    ///
    Zone        *center;

    ///
    /// \brief Corner from which the half edge departs.
    ///
    Corner      *origin;       // maybe use _edge.v0/v1 instead, if able to keep track of direction

    ///
    /// \brief Destination corner of the half edge.
    ///
    Corner      *destination;  // maybe use _edge.v1/v0 instead, if able to keep track of direction

    ///
    /// \brief Previous half-edge.
    ///
    HalfEdge    *prev;

    ///
    /// \brief Next half-edge.
    ///
    HalfEdge    *next;

    ///
    /// \brief Twin half-edge.
    ///
    HalfEdge    *twin;
};

}

#endif // HALFEDGE_H
