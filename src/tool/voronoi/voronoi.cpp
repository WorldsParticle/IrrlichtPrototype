#include "tool/voronoi/voronoi.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <algorithm>

#include "map/map.h"

#include "tool/voronoi/parabola.h"
#include "tool/voronoi/edge.h"

namespace vor
{

Voronoi::Voronoi() :
    m_edges(),
    m_points(),
    m_events(),
    m_deleted(),
    m_sweepLine(0),
    m_root(nullptr)
{
}

Voronoi::~Voronoi()
{
    clearData();
}

void    Voronoi::clearData()
{
    for(std::vector<Point *>::iterator it = m_points.begin(); it != m_points.end(); ++it)
        delete (*it);
    for(std::vector<Edge *>::iterator it = m_edges.begin(); it != m_edges.end(); ++it)
        delete (*it);
    m_points.clear();
    m_edges.clear();
    m_root = nullptr; // todo
    Parabola::indexMax = 0;
}

const std::vector<Edge *> *Voronoi::fortuneAlgo(const std::vector<Point *> &sites)
{
    clearData();

    for (std::vector<Point *>::const_iterator it = sites.begin(); it != sites.end(); ++it)
        m_events.push(new Event(new Point((*it)->x, (*it)->z), true));

    while (!m_events.empty())
    {
        Event *event = m_events.top();
        m_events.pop();

        m_sweepLine = event->point->z;

        if(m_deleted.find(event) != m_deleted.end())
        {
            delete(event);
            m_deleted.erase(event);
            continue;
        }

        if (event->is_par_event)
            addParabola(event->point);
        else
            removeParabola(event);
    }

    finishEdge(m_root);
    for(std::vector<Edge *>::iterator it = m_edges.begin(); it != m_edges.end(); ++it)
    {
        if( (*it)->neighbour)
        {
            (*it)->start = (*it)->neighbour->end;
            delete (*it)->neighbour;
        }
    }
    return &m_edges;
}

void	Voronoi::finishEdge(Parabola * p)
{
    if(p->isLeaf) {delete p; return;}

    double mx;
    if(p->edge->direction->x > 0.0)
        mx = p->edge->start->x + 10; //std::max(_map->xMax(), p->edge->start->x + 10 ); a vérifier
    else
        mx = std::min(0.0, p->edge->start->x - 10);

    p->edge->end = new Point(mx, mx * p->edge->f + p->edge->g);
    m_points.push_back(p->edge->end);

    finishEdge(p->left());
    finishEdge(p->right());
    delete p;
}

void    Voronoi::addParabola(Point *site)
{
    if (!m_root) { m_root = new Parabola(site); return; }

    // Nop
    /*if (_root->isLeaf && _root->site->point.z - site->point.z < 1)
    {
        _root->isLeaf = false;
        _root->setLeft(new Parabola(_root->site));
        _root->setRight(new Parabola(site));
        Point   s((site->point.x + _root->site->point.x) / 2, _zMax);

        if (site->point.x  > _root->site->point.x)
            _root->edge = new Edge(s, _root->site, site);
        else
            _root->edge = new Edge(s, site, _root->site);

        _tempEdges.push_back(_root->edge);

        return;
    }*/

    Parabola    *topParabola = getParabolaAtX(site->x); // get first parabola above the new site
    if (topParabola->cEvent) // Event annulé car bouffé par une nouvelle parabole
    {
        m_deleted.insert(topParabola->cEvent);
        topParabola->cEvent = nullptr;
    }

    Point   *start = new Point(site->x, getZ(topParabola->site, site->x));
    m_points.push_back(start);

    Edge    *el = new Edge(start, topParabola->site, site);
    Edge    *er = new Edge(start, site, topParabola->site);
    el->neighbour = er;
    m_edges.push_back(el);
    topParabola->edge = er;
    topParabola->isLeaf = false;

    Parabola    *p0 = new Parabola(topParabola->site); // Gauche
    Parabola    *p1 = new Parabola(site);              // Nouvelle, celle qui coupe
    Parabola    *p2 = new Parabola(topParabola->site); // Droite

    topParabola->setRight(p2);
    topParabola->setLeft(new Parabola());
    topParabola->left()->edge = el;
    topParabola->left()->setLeft(p0);
    topParabola->left()->setRight(p1);

    checkCircle(p0);
    checkCircle(p2);

}

void    Voronoi::removeParabola(Event *e)
{
    Parabola    *p1 = e->arch;

    Parabola    *pLeft = Parabola::getLeftParent(p1);
    Parabola    *pRight = Parabola::getRightParent(p1);
    Parabola    *p0 = Parabola::getLeftChild(pLeft);
    Parabola    *p2 = Parabola::getRightChild(pRight);

    if (p0 == p2)
        std::cout << "error : same focal point\n";

    if (p0->cEvent)
    {
        m_deleted.insert(p0->cEvent);
        p0->cEvent = nullptr;
    }
    if (p2->cEvent)
    {
        m_deleted.insert(p2->cEvent);
        p2->cEvent = nullptr;
    }

    Point   *p = new Point(e->point->x, getZ(p1->site, e->point->x));
    m_points.push_back(p);

    pLeft->edge->end = p;
    pRight->edge->end = p;

    Parabola * higher = nullptr;
    Parabola * par = p1;
    while(par != m_root)
    {
        par = par->parent;
        if(par == pLeft) higher = pLeft;
        if(par == pRight) higher = pRight;
    }

    higher->edge = new Edge(p, p0->site, p2->site);
    m_edges.push_back(higher->edge);

    Parabola * gparent = p1->parent->parent;
    if(p1->parent->left() == p1)
    {
        if(gparent->left()  == p1->parent) gparent->setLeft ( p1->parent->right() );
        if(gparent->right() == p1->parent) gparent->setRight( p1->parent->right() );
    }
    else
    {
        if(gparent->left()  == p1->parent) gparent->setLeft ( p1->parent->left()  );
        if(gparent->right() == p1->parent) gparent->setRight( p1->parent->left()  );
    }

    delete p1->parent;
    delete p1;

    checkCircle(p0);
    checkCircle(p2);
}

double      Voronoi::getXofEdge(Parabola *p, double z)
{
    const Point *sLeft = Parabola::getLeftChild(p)->site;
    const Point *sRight = Parabola::getRightChild(p)->site;

    // justifier
    double dp;

    // 1 = parabole gauche ; 2 = parabole droite ; vide = intersection
    // ax² + bx + c
    double a, a1, a2, b, b1, b2, c, c1, c2;

    // b² - 4ac, resolution d'equation du second defrée
    double   delta, x1, x2;

    double result;

    // REVERIFIER
    dp = 2.0 * (sLeft->z - z);
    a1 = 1.0 / dp;
    b1 = -2.0 * sLeft->x / dp;
    c1 = z + dp / 4 + sLeft->x * sLeft->x / dp;

    dp = 2.0 * (sRight->z - z);
    a2 = 1.0 / dp;
    b2 = -2.0 * sRight->x / dp;
    c2 = m_sweepLine + dp / 4 + sRight->x * sRight->x / dp; // why _sweepline ?

    a = a1 - a2;
    b = b1 - b2;
    c = c1 - c2;

    delta = b*b - 4 * a * c;
    x1 = (-b + sqrt(delta)) / (2*a);
    x2 = (-b - sqrt(delta)) / (2*a);

    if(sLeft->z < sRight->z)
        result = std::max(x1, x2);
    else
        result = std::min(x1, x2);

    return result;
}

Parabola    *Voronoi::getParabolaAtX(double nx)
{
    Parabola *p = m_root;
    double x = 0.0;

    while(!p->isLeaf)
    {
        x = getXofEdge(p, m_sweepLine);
        if (x > nx)
            p = p->left();
        else
            p = p->right();
    }
    return p;
}

double      Voronoi::getZ(const Point *s, double x)
{
    // Formule d'intersection, à reviser
    double dp = 2 * (s->z - m_sweepLine);
    double a1 = 1 / dp;
    double b1 = -2 * s->x / dp;
    double c1 = m_sweepLine + dp / 4 + s->x * s->x / dp;

    double result = a1*x*x + b1*x + c1;

    return(result);
}

void        Voronoi::checkCircle(Parabola *b)
{
    Parabola    *leftParent = Parabola::getLeftParent(b);
    Parabola    *rightParent = Parabola::getRightParent(b);

    Parabola    *a = Parabola::getLeftChild(leftParent);
    Parabola    *c = Parabola::getRightChild(rightParent);

    if (!a || !c || a->site == c->site)
        return;

    Point *s = NULL;
    if (!(s = getEdgeIntersection(leftParent->edge, rightParent->edge)))
        return;

    // Trouver la future distance de la sweepline quand intersection
    double dx = a->site->x - s->x;
    double dz = a->site->z - s->z;
    double d = sqrt( (dx * dx) + (dz * dz) );
    if(s->z - d >= m_sweepLine)
        return;

    Event *e = new Event(new Point(s->x, s->z - d), false);
    m_points.push_back(e->point);
    b->cEvent = e;
    e->arch = b;

    m_events.push(e);
}

Point   *Voronoi::getEdgeIntersection(Edge *a, Edge *b)
{
    double x = (b->g - a->g) / (a->f - b->f);
    double z = a->f * x + a->g;

    if((x - a->start->x)/a->direction->x < 0) return NULL;
    if((z - a->start->z)/a->direction->z < 0) return NULL;
    if((x - b->start->x)/b->direction->x < 0) return NULL;
    if((z - b->start->z)/b->direction->z < 0) return NULL;

    Point   *result = new Point(x, z);
    m_points.push_back(result);
    return result;
}

}
