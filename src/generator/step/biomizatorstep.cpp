#include "generator/step/biomizatorstep.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <algorithm>

namespace gen
{

BiomizatorStep::BiomizatorStep() :
    GenerationStep("Attribution des biomes")
{
}

BiomizatorStep::~BiomizatorStep()
{
}

void    BiomizatorStep::run()
{
    assignBiomes();
}


::map::Biome        BiomizatorStep::getBiome(::map::Zone *z)
{
    if (z->ocean)
        return ::map::OCEAN;
    else if (z->water)
    {
        if (z->elevation < 0.1f)
            return ::map::MARSH;
        if (z->elevation > 0.8f)
            return ::map::ICE;
        return ::map::LAKE;
    }
    else if (z->coast)
        return ::map::BEACH;
    else if (z->elevation > 0.8f)
    {
        if (z->moisture > 0.5f)
            return ::map::SNOW;
        else if (z->moisture > 0.33f)
            return ::map::TUNDRA;
        else if (z->moisture > 0.16f)
            return ::map::BARE;
        else
            return ::map::SCORCHED;
    }
    else if (z->elevation > 0.6f)
    {
        if (z->moisture > 0.66f)
                return ::map::TAIGA;
        else if (z->moisture > 0.33f)
                return ::map::SHRUBLAND;
        else
            return ::map::TEMPERATE_DESERT;
    }
    else if (z->elevation > 0.3f)
    {
        if (z->moisture > 0.83f)
            return ::map::TEMPERATE_RAIN_FOREST;
        else if (z->moisture > 0.50f)
            return ::map::TEMPERATE_DECIDUOUS_FOREST;
        else if (z->moisture > 0.16f)
            return ::map::GRASSLAND;
        else
            return ::map::TEMPERATE_DESERT;
    }
    else
    {
        if (z->moisture > 0.66f)
            return ::map::TROPICAL_RAIN_FOREST;
        else if (z->moisture > 0.33f)
            return ::map::TROPICAL_SEASONAL_FOREST;
        else if (z->moisture > 0.16f)
            return ::map::GRASSLAND;
        else
            return (::map::SUBTROPICAL_DESERT);
    }
}

void        BiomizatorStep::assignBiomes()
{
    for (auto & z : m_map->zones())
    {
        z.second->biome = getBiome(z.second);
    }
}

}
