#ifndef VORONOIGENERATOR_H
#define VORONOIGENERATOR_H

#include "generator/generator.h"
#include "map/point.h"
#include "event.h"
#include <list>
#include <map>
#include <queue>
#include <set>
#include <memory>

namespace map
{
    class Zone;
}

namespace vor
{

class Parabola;
class Edge;

///
/// \brief The VoronoiGenerator class
/// Based on the design found in https://github.com/amitp/mapgen2
///
class Voronoi
{
public:
    Voronoi();
    ~Voronoi();

    ///
    /// \brief fortuneAlgo
    /// \param sites is a copied list of points from where to start
    ///
    const std::vector<Edge *> *fortuneAlgo(const std::vector<Point *> &sites);

private:
    void    clearData();

    ///
    /// \brief finishEdge
    /// \param p
    ///
    void    finishEdge(Parabola *p);

    ///
    /// \brief addParabola
    /// \param site
    ///
    void    addParabola(Point *site);
    void    removeParabola(Event *e); // should pass Parabola as argument when implemented

    // to review
    double       getXofEdge(Parabola *p, double y); // return current x position of an intersection point of left and right parabolas
    Parabola    *getParabolaAtX(double nx); // return leaf parabola at nx position in the current beachline

    ///
    /// \brief getY will retrieve the intersecting y value between a site parabola and an x value
    /// \param s is the site
    /// \param x is the x value
    /// \return
    ///
    double      getY(const Point *s, double x);

    ///
    /// \brief checkCircle find if the current parabola will close soon
    /// \param p
    ///
    void        checkCircle(Parabola *b);

    ///
    /// \brief getEdgeIntersection compute the point where two parabola edge will collide.
    /// \param a
    /// \param b
    /// \todo  return bool a feed a reference
    ///
    Point *getEdgeIntersection(Edge *a, Edge *b); // à refaire en plus propre

    ///
    /// \brief _edges
    ///
    std::vector<Edge *>         m_edges;

    ///
    /// \brief temporary points (edges interesct, ...)
    ///
    std::vector<Point *>        m_points;

    ///
    /// \brief _events potential future events wich can modify the beach line
    /// (another point or parabola intersection)
    ///
    std::priority_queue<Event *, std::vector<Event *>, Event::compareEvent>   m_events;
    std::set<Event *>   m_deleted; // comme je repasse sur une queue

    double                      m_sweepLine;     // sweep line going down
    std::shared_ptr<Parabola>   m_root;         // root parabola containing the beach line
};

}

#endif // VORONOIGENERATOR_H
