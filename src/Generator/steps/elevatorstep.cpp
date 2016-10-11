#include "Generator/steps/elevatorstep.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <queue>

#include "Generator/map/map.h"

namespace gen
{

ElevatorStep::ElevatorStep() :
    GenerationStep("Elevation"),
    m_slopeFactor("Facteur d'aplanissement")
{
    m_slopeFactor.setMinValue(0);
    m_slopeFactor.setMaxValue(100);
    m_slopeFactor.setValue(50);
    params().push_back(&m_slopeFactor);
}

ElevatorStep::~ElevatorStep()
{
}

void    ElevatorStep::run()
{
    assignCornerElevation();
    redistributeElevation();
    setPolygonElevation();
    calculateDownSlopes();
}


void        ElevatorStep::assignCornerElevation()
{
    std::queue<map::Corner *>   q;
int a = 0;
    for (auto & corner : m_map->corners())
    {

        if (corner.second->border)
        {
            ++a;
            corner.second->elevation = 0.0;
            q.push(corner.second);
        }
        else
            corner.second->elevation = std::numeric_limits<float>::max();
    }

    while (q.size())
    {
    map::Corner *corner = q.front();
        q.pop();

        for (map::Corner *adj : corner->adjacent)
        {
            float newElevation = 0.00001f + corner->elevation;
            if (!corner->water && !adj->water)
            {
                newElevation += 1.0f;
                // add randomness here if map looks too dull
            }
            if (newElevation < adj->elevation)
            {
                adj->elevation = newElevation;
                q.push(adj);
            }
        }
    }
}


struct sortByElevation
{
  bool operator() (map::Corner *L, map::Corner *R) { return L->elevation < R->elevation; }
};

void        ElevatorStep::redistributeElevation()
{
    float scaleFactor = 0.2f + (1.0f - static_cast<float>(m_slopeFactor.value()) / 100.0f) * 1.8f;
    std::vector<map::Corner *> corners;

    for (const auto & corner : m_map->corners())
    {
        if (!corner.second->ocean)
            corners.push_back(corner.second);
    }
    std::sort(corners.begin(), corners.end(), sortByElevation());

    for (unsigned int i = 0; i < corners.size(); ++i)
    {
       float y, x;

       y = static_cast<float>(i) / static_cast<float>(corners.size() - 1);
       x = static_cast<float>(sqrt(scaleFactor) - sqrt(scaleFactor * (1.0f - y)));
       if (x > 1.0f)
           x = 1.0f;
       corners[i]->elevation = x;
    }

}

void        ElevatorStep::setPolygonElevation()
{
    for (const auto & zone : m_map->zones())
    {
        float sumElevation = 0.0;
        for (auto corner : zone.second->corners)
        {
            sumElevation += corner->elevation;
        }
        zone.second->elevation = sumElevation / static_cast<float>(zone.second->corners.size());
    }
}

void        ElevatorStep::calculateDownSlopes()
{
    for (const auto & q : m_map->corners())
    {
    map::Corner *steepest = q.second;
        for (map::Corner *neighbor : q.second->adjacent)
        {
            if (neighbor->elevation < steepest->elevation)
                steepest = neighbor;
        }
        q.second->downslope = steepest;
    }
}


}
