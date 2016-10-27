#include <ctime>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <queue>

#include "map/map.h"
#include "generator/step/shaperstep.h"
#include "tool/simplexnoise.h"

namespace gen
{

ShaperStep::ShaperStep(const std::string &name) :
    GenerationStep(name),
    m_landRatio("Pourcentage de terre")
{
    m_landRatio.setMinValue(0);
    m_landRatio.setMaxValue(100);
    m_landRatio.setValue(80);
    params().push_back(&m_landRatio);
}

ShaperStep::~ShaperStep()
{
}

void    ShaperStep::run()
{
    assignCornerLandPerlin(rand() % 100000);
    assignOceanCostAndLand();
}

// TODO : assignCornerLandRadial()

void        ShaperStep::assignCornerLandPerlin(int seed)
{
    std::cout << m_landRatio.value() << std::endl;
    for (const auto & corner : m_map->corners())
    {
        Point p = corner.second->point;
        double xMax = m_map->xMax();
        double yMax = m_map->yMax();

        // assign corner.border if a corner is out of the map's bounding box
        if (p.x <= 0 || p.y <= 0 || p.x >= xMax || p.y >= yMax)
            corner.second->border = true;
        else
            corner.second->border = false;

        // put all corners inside for normalization, simplistic but doesn't affect outcome
        if (p.x > xMax)
            p.x = xMax;
        if (p.x < 0)
            p.x = 0;
        if (p.y > yMax)
            p.y = yMax;
        if (p.y < 0)
            p.y = 0;

        // perlin random number (z) € [0, 1], points are normalized to [-1, 1],
        // thus the farther a point from the center [0, 0],
        // the higher the threshold to earn the right to be a land corner as magnitude goes up.

        p.x = (p.x / xMax - 0.5) * 2;
        p.y = (p.y / yMax - 0.5) * 2;

        double magnitude = sqrt(pow(p.x, 2) + pow(p.y, 2));
        double z = static_cast<double>((octave_noise_2d(8.0f, 0.5f, 0.8f, static_cast<float>(p.x + seed), static_cast<float>(p.y + seed)) + 1) / 2.0f);
        double threshold = ((1.0 - static_cast<double>(m_landRatio.value()) / 100.0) * 0.58 + 0.28 * magnitude * magnitude);
        if (z > threshold && !corner.second->border)
            corner.second->water = false;
        else
            corner.second->water = true;
    }
}


void        ShaperStep::assignOceanCostAndLand()
{
    std::queue<::map::Zone *> q;


    // assigning ocean to border zones,
    // and water based on corners
    for (auto & zone : m_map->zones())
    {
        zone.second->ocean = false;
        int numWater = 0;
        for (auto corner : zone.second->corners)
        {
            if (corner->border)
            {
               zone.second->border = true;
               zone.second->ocean = true;
               corner->water = true;
               q.push(zone.second);
            }
            if (corner->water)
            {
                numWater += 1;
            }
        }
        zone.second->water = (zone.second->ocean || (numWater >= static_cast<double>(zone.second->corners.size()) * 0.01)); // 0.3 == LAKE_TRESHOLD
    }

    // propagating ocean zones
    while (q.size())
    {
        auto zone = q.front();
        q.pop();
        for (auto neighbor : zone->neighbors)
        {
            if (neighbor->water && !neighbor->ocean) {
                neighbor->ocean = true;
                q.push(neighbor);
            }
        }
    }

    // assigning coast zones
    for (auto & zone : m_map->zones())
    {
        int numOcean = 0;
        int numLand = 0;
        for (auto neighbor : zone.second->neighbors)
        {
            numOcean += static_cast<int>(neighbor->ocean);
            numLand += static_cast<int>(!neighbor->water);
        }
        zone.second->coast = (numOcean > 0) && (numLand > 0);
    }

    // assigning corner's ocean, coast & water
    for (auto & corner : m_map->corners())
    {
        unsigned int numOcean = 0;
        unsigned int numLand = 0;
        for (auto zone : corner.second->faces)
        {
            numOcean += static_cast<int>(zone->ocean);
            numLand += static_cast<int>(!zone->water);
        }
        corner.second->ocean = (numOcean == corner.second->faces.size());
        corner.second->coast = (numOcean > 0) && (numLand > 0);
        corner.second->water = corner.second->border || ((numLand != corner.second->faces.size()) && !corner.second->coast);
    }
}


}
