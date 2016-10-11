#include "Generator/steps/zoningstep.h"
#include "Generator/map/point.h"
#include "Generator/param/intvalue.h"

#include "Generator/tools/voronoi/edge.h"

#include <vector>
#include <ctime>

#define DRAND(min, max) (min) + (static_cast<double>(std::rand()) / RAND_MAX) * ((max) - (min))

namespace gen
{

ZoningStep::ZoningStep() :
    GenerationStep("Attribution des zones"),
    m_voronoi(),
    m_zoneNumber("Nombre de zones")
{
    m_zoneNumber.setMinValue(1);
    m_zoneNumber.setMaxValue(5000);
    m_zoneNumber.setValue(50);
    params().push_back(&m_zoneNumber);
}

ZoningStep::~ZoningStep()
{

}

void    ZoningStep::run()
{
    std::vector<Point *>                    sites = generateRandomSites();
    std::cout << "Generating Voronoi edges .." << std::endl;
    const std::vector<vor::Edge *>    *edges = m_voronoi.fortuneAlgo(sites);

    // do lloyd, relaunch fortune, and again (nb depending of a user param)
    // todo

    std::cout << "Translating into dual graph .." << std::endl;
    computeMap(edges);
}

std::vector<Point *>    ZoningStep::generateRandomSites()
{

    std::vector<Point *> sites;
    for (int i = 0; i < m_zoneNumber.value(); ++i)
        sites.push_back(new Point(DRAND(0, m_map->xMax()),
                                  DRAND(0, m_map->yMax())));
    return sites;
}

void    ZoningStep::LloydRelaxation() // NOT WORKING FOR NOW
{
    // filling neighbors temporarly.. ugly for now. will have to remove totally Zone from this algorythme
    /*for (const auto &e: _edges)
    {
        if (!e->left->haveNeighbor(e->right))
            e->left->neighbors.push_back(e->right);
        if (!e->right->haveNeighbor(e->left))
            e->right->neighbors.push_back(e->left);
    }

    for (const auto &z: _points)
    {
        z->point.x = 0;
        z->point.y = 0;
        for (const auto &n: z->neighbors)
        {
            z->point.x += n->point.x;
            z->point.y += n->point.y;
        }
        z->point.x /= z->neighbors.size();
        z->point.y /= z->neighbors.size();
        z->neighbors.clear();
        _events.push(new Event(z));
    }*/
}

void        ZoningStep::computeMap(const std::vector<vor::Edge *> *edges) // à clean au plus vite
{
    for (const auto &e: *edges)
    {
        map::CrossedEdge    *edge = new map::CrossedEdge();
        map::Zone           *left = m_map->findZone(e->left);
        map::Zone           *right = m_map->findZone(e->right);
        map::Corner         *c0;
        map::Corner         *c1;

        // Ugly workaround
        if (!left)
        {
            left = new map::Zone(e->left->x, e->left->y);
            m_map->zones().insert(std::pair<int, map::Zone *>(left->index, left));
        }
        if (!right)
        {
            right = new map::Zone(e->right->x, e->right->y);
            m_map->zones().insert(std::pair<int, map::Zone *>(right->index, right));
        }

        if (!left->haveNeighbor(right))
            left->neighbors.push_back(right);
        if (!right->haveNeighbor(left))
            right->neighbors.push_back(left);

        edge->z0 = left;
        edge->z1 = right;
        left->borders.push_back(edge);
        right->borders.push_back(edge);

        if (!(c0 = checkCorner(left, *e->start)))
        {
            if (!(c0 = checkCorner(right, *e->start)))
            {
                c0 = new map::Corner();
                m_map->corners().insert(std::pair<int, map::Corner *>(c0->index, c0));

                c0->point.x = e->start->x;
                c0->point.y = e->start->y;
                right->corners.push_back(c0);
                c0->faces.push_back(right);
            }
            left->corners.push_back(c0);
            c0->faces.push_back(left);
        }

        if (!(c1 = checkCorner(left, *e->end)))
        {
            if (!(c1 = checkCorner(right, *e->end)))
            {
                c1 = new map::Corner();
                m_map->corners().insert(std::pair<int, map::Corner *>(c1->index, c1));

                c1->point.x = e->end->x;
                c1->point.y = e->end->y;
                right->corners.push_back(c1);
                c1->faces.push_back(right);
            }
            left->corners.push_back(c1);
            c1->faces.push_back(left);
        }


        edge->c0 = c0;
        edge->c1 = c1;
        c0->edges.push_back(edge);
        c1->edges.push_back(edge);
        c0->adjacent.push_back(c1);
        c1->adjacent.push_back(c0);

        m_map->edges().insert(std::pair<int, map::CrossedEdge *>(edge->index, edge));
    }
}

map::Corner *ZoningStep::checkCorner(map::Zone *z, Point &p)
{
    for (std::vector<map::Corner *>::iterator it = z->corners.begin(); it != z->corners.end(); ++it)
        if (std::abs((*it)->point.x - p.x) < std::numeric_limits<double>::epsilon()
                    && (std::abs((*it)->point.y - p.y) < std::numeric_limits<double>::epsilon()))
            return (*it);
    return nullptr;
}




}
