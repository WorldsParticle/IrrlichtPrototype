#include "generator/step/lakerstep.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <algorithm>

#include "tool/bitmap_image.h"

namespace gen
{

LakerStep::LakerStep(const std::string &name) :
    GenerationStep(name)
{
}

LakerStep::~LakerStep()
{
}

void    LakerStep::run()
{
    // steps
    createLakes();
}

// uses duplicate vertices because of UV mapping
// rectangular decomposition is NP complete, although we could use a fast heuristic to drastically reduce the tri count
void        LakerStep::createMesh(::map::Lake * lake, float lakeHeight)
{
    irr::scene::SMesh* Mesh = new irr::scene::SMesh();

    irr::scene::SMeshBuffer *buf = new irr::scene::SMeshBuffer();
    Mesh->addMeshBuffer(buf);
    buf->drop();

    buf->Vertices.reallocate(lake->getPoints().size() * 4);
    buf->Vertices.set_used(lake->getPoints().size() * 4);


    buf->Indices.reallocate(lake->getPoints().size() * 6);
    buf->Indices.set_used(lake->getPoints().size() * 6);

    unsigned int    vertIndex = 0;
    unsigned int    indIndex = 0;

    for (auto point : lake->getPoints())
    {
        auto vec = point.second;

        float x = static_cast<float>(vec.X);
        float y = static_cast<float>(vec.Y);

        buf->Vertices[vertIndex++] = irr::video::S3DVertex(x - 0.5f,lakeHeight,y - 0.5f,   0,1,0,    irr::video::SColor(255,0,255,255),    0, 1);
        buf->Vertices[vertIndex++] = irr::video::S3DVertex(x + 0.5f,lakeHeight,y - 0.5f,   0,1,0,  irr::video::SColor(255,255,0,255),  0, 0);
        buf->Vertices[vertIndex++] = irr::video::S3DVertex(x - 0.5f,lakeHeight,y + 0.5f,   0,1,0,    irr::video::SColor(255,255,255,0),    1, 1);
        buf->Vertices[vertIndex++] = irr::video::S3DVertex(x + 0.5f,lakeHeight,y + 0.5f,   0,1,0,    irr::video::SColor(255,255,255,0),    1, 0);

        buf->Indices[indIndex++]= vertIndex - 4;
        buf->Indices[indIndex++]= vertIndex - 3;
        buf->Indices[indIndex++]= vertIndex - 1;

        buf->Indices[indIndex++]= vertIndex - 4;
        buf->Indices[indIndex++]= vertIndex - 1;
        buf->Indices[indIndex++]= vertIndex - 2;
    }

    buf->recalculateBoundingBox();

    lake->setMesh(Mesh);

}

void        LakerStep::fillDepthMap(std::vector<int> & depthMap, unsigned int xMax, ::map::Lake * lake)
{
    std::stack<unsigned int> s;

    for (unsigned int j = 0; j < xMax; ++j)
    {
        int combo = 0;
        for (unsigned int i = 0; i < xMax; ++i)
        {
            if (m_map->heightMap().pointAt(i, j).zone->water == true &&
                    m_map->heightMap().pointAt(i, j).zone->ocean == false)
            {
                ++combo;
                depthMap[j * xMax + i] = depthMap[j * xMax + i] != -1 ? std::min(depthMap[j * xMax + i], combo) : combo;
                s.push(i);
            }
            else
            {
                int max = combo + 1;
                while (! s.empty())
                {
                    depthMap[j * xMax + s.top()] = std::min(depthMap[j * xMax + s.top()], max - combo);
                    combo--;
                    s.pop();
                }
                combo = 0;
            }
        }
    } // end of horizontal depth

    for (unsigned int i = 0; i < xMax; ++i)
    {
        int combo = 0;
        for (unsigned int j = 0; j < xMax; ++j)
        {
            if (m_map->heightMap().pointAt(i, j).zone->water == true &&
                    m_map->heightMap().pointAt(i, j).zone->ocean == false)
            {
                ++combo;
                depthMap[j * xMax + i] = depthMap[j * xMax + i] != -1 ? std::min(depthMap[j * xMax + i], combo) : combo;
                s.push(j);
            }
            else
            {
                int max = combo + 1;
                while (! s.empty())
                {
                    depthMap[s.top() * xMax + i] = std::min(depthMap[s.top() * xMax + i], max - combo);
                    combo--;
                    s.pop();
                }
                combo = 0;
            }
        }
    } // end of vertical depth

    int square[4][2] = {{1, 0},
                        {0, -1},
                        {1, 1},
                        {-1, 0}};
    std::queue<irr::core::vector2d<irr::u32> > q;

    for (auto point : lake->getPoints())
    {
        auto vec = point.second;
        for (int i = 0; i < 4; ++i)
        {
            if (depthMap[(vec.Y + square[i][1]) * xMax + (vec.X + square[i][0])] != -1)
            {
                if ((depthMap[(vec.Y + square[i][1]) * xMax + (vec.X + square[i][0])] - depthMap[vec.Y * xMax + vec.X]) > 1)
                {
                    depthMap[(vec.Y + square[i][1]) * xMax + (vec.X + square[i][0])] = depthMap[vec.Y * xMax + vec.X] + 1;
                    q.push(irr::core::vector2d<irr::u32>(vec.X + square[i][1], vec.Y + square[i][0]));
                }
            }
        }
        while (! q.empty())
        {
            vec = q.front();

            for (int i = 0; i < 4; ++i)
            {
                if (depthMap[(vec.Y + square[i][1]) * xMax + (vec.X + square[i][0])] != -1)
                {
                    if ((depthMap[(vec.Y + square[i][1]) * xMax + (vec.X + square[i][0])] - depthMap[vec.Y * xMax + vec.X]) > 1)
                    {
                        depthMap[(vec.Y + square[i][1]) * xMax + (vec.X + square[i][0])] = depthMap[vec.Y * xMax + vec.X] + 1;
                        q.push(irr::core::vector2d<irr::u32>(vec.X + square[i][1], vec.Y + square[i][0]));
                    }
                }
            }

            q.pop();
        }
    }
}

void        LakerStep::createLakes()
{
    unsigned int    yMax = static_cast<unsigned int>(m_map->yMax());
    unsigned int    xMax = static_cast<unsigned int>(m_map->xMax());

    // Temporary, create one random lake somewhere.
    while (42)
    {
        unsigned int x = rand() % xMax;
        unsigned int y = rand() % xMax;

        ::map::Zone * z = m_map->heightMap().pointAt(x, y).zone;
        if (z->ocean == false && z->water == false && z->coast == false)
        {
            z->water = true;
            z->biome = ::map::LAKE;
            break;
        }
    }

    // Creating lake objects with their respective adjacent zones
    for (auto elem : m_map->zones())
    {
        ::map::Zone * z = elem.second;

        if (z->water == true && z->ocean == false)
        {
            bool    toCreate = true;

            // on vérifie que la zone d'eau non-océane en fait partie d'aucun lac
            for (::map::Lake * l : m_map->lakes())
            {
                if (l->containsZone(z))
                {
                    toCreate = false;
                    break;
                }
            }

            // Si aucun lac ne contient la zone d'eau non-océane,
            // on crée un map::lac, dans lequel on va mettre toutes
            // les zones adjacentes d'eau non-océanes
            if (toCreate)
            {
               ::map::Lake * lake = new ::map::Lake();
               std::queue< ::map::Zone *> q;

               lake->addZone(z);
               for (::map::Zone * neighbor : z->neighbors)
               {
                   if (neighbor->water && !neighbor->ocean)
                    q.push(neighbor);
               }
               while (! q.empty())
               {
                   ::map::Zone * lakeZone = q.front();

                   lake->addZone(lakeZone);
                   for (::map::Zone * neighbor : lakeZone->neighbors)
                   {
                       if (neighbor->water && !neighbor->ocean && ! lake->containsZone(neighbor))
                        q.push(neighbor);
                   }

                   q.pop();
               }
               m_map->lakes().push_back(lake);
            } // end of putting all adjacent lake zones into a lake object.
        }
    } // end of linking lake objects <-> Zones

    std::list< ::map::Lake *>                               lakesDone;
    unsigned int lakes = 0;

    for (unsigned int j = 0; j < yMax; ++j)
    {
        for (unsigned int i = 0; i < xMax; ++i)
        {
            ::map::Zone * z = m_map->heightMap().pointAt(i, j).zone;

            if (!z->water || z->ocean)
                continue;
            else if (z->biome == ::map::LAKE)
                lakes ++;

            if (z->water && ! z->ocean)
            {
                bool            toDo = true;
                ::map::Lake *   target = nullptr;

                for (::map::Lake * lake : lakesDone)
                {
                    if (lake->containsZone(z))
                    {
                        if (lake->getPoints().empty())
                        {
                            target = lake;
                            lakesDone.push_back(lake);
                            break;
                        }
                        else
                            toDo = false;
                    }
                }
                if (toDo && target == nullptr)
                {
                    for (::map::Lake * lake : m_map->lakes())
                    {
                        if (lake->containsZone(z))
                        {
                            if (lake->getPoints().empty())
                            {
                                target = lake;
                                lakesDone.push_back(lake);
                                break;
                            }
                        }
                    }
                }
                if (toDo && target != nullptr)
                {
                    std::cout << target << std::endl;
                    std::queue<std::pair< unsigned int, unsigned int > >    q;
                    int square[8][2] = {{1, 0},
                                        {1, -1},
                                        {0, -1},
                                        {-1, -1},
                                        {-1, 0},
                                        {-1, 1},
                                        {0, 1},
                                        {1, 1}};

                    q.push({i, j});
                    target->addPoint(i, j, xMax);
                    while (! q.empty())
                    {
                        std::pair<unsigned int, unsigned int>   p = q.front();

                        for (int i = 0; i < 8; ++i)
                        {
                            unsigned int x = p.first + square[i][0];
                            unsigned int y = p.second + square[i][1];
                            if (target->containsZone(m_map->heightMap().pointAt(x, y).zone))
                            {
                                if (!(target->containsPoint(x, y, xMax)))
                                {
                                    target->addPoint(x, y, xMax);
                                    q.push({x, y});
                                }
                            }
                            else
                                target->addPerimeterPoint(x, y, xMax);
                        }


                        q.pop();
                    }

                }
            }
        }
    } // end of harvesting points.

    std::vector<int> depthMap;
    depthMap.resize(xMax * xMax);
    std::fill_n(depthMap.begin(), xMax * xMax, -1);

    // auto fury crime scene, keep your distance
    for (auto lake : m_map->lakes())
    {
        float   minHeight = 1.0f;
        int     maxDepth = 0;
        auto pts = lake->getPerimeterPoints();

        // fill map of depth according to distance from shore
        fillDepthMap(depthMap, xMax, lake);

        // get maximum depth
        for (auto point : depthMap)
            if (point > maxDepth)
                maxDepth = point;

        // get minimum height around the lake
        for (auto elem : pts)
        {
            auto vec = elem.second;
            if (m_map->heightMap().pointAt(vec.X, vec.Y).z < minHeight)
                minHeight = m_map->heightMap().pointAt(vec.X, vec.Y).z;
        }

        // set height of lake points following a linear curve
        pts = m_map->lakes().front()->getPoints();

        float maxDifferenceHeight = 0.10f;
        float fMaxDepth = static_cast<float>(maxDepth);

        for (auto elem : pts)
        {
            auto vec = elem.second;

            float depthRatio = static_cast<float>(depthMap[vec.Y * xMax + vec.X]) / fMaxDepth;

            m_map->heightMap().pointAt(vec.X, vec.Y).z = minHeight - std::pow(depthRatio, 0.75f) * maxDifferenceHeight;
        }
        createMesh(lake, minHeight - std::pow((1.0f / fMaxDepth), 0.75f) * maxDifferenceHeight);
    }



} // end of createLakes()

}
