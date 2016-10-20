#include "generator/generator.h"

#include "map/map.h"
#include "generator/step/zoningstep.h"
#include "generator/step/shaperstep.h"
#include "generator/step/elevatorstep.h"
#include "generator/step/riverorstep.h"
#include "generator/step/moistorstep.h"
#include "generator/step/biomizatorstep.h"
#include "generator/step/heightmapingstep.h"

namespace gen
{

Generator::Generator() :
    m_steps()
{
    m_steps.push_back(new ZoningStep());
    m_steps.push_back(new ShaperStep());
    m_steps.push_back(new ElevatorStep());
    m_steps.push_back(new RiverorStep());
    m_steps.push_back(new MoistorStep());
    m_steps.push_back(new BiomizatorStep());
    m_steps.push_back(new HeightMapingStep());
}

void    Generator::run(::map::MapGraph *map)
{
    for (const auto &step: m_steps)
    {
        std::cout << step->name() << std::endl;
        step->launch(map);
    }
}

GenerationStep  *Generator::stepFromName(const std::string &namee)
{
    for (const auto &s: m_steps)
        if (s->name() == namee)
            return s;
    return (nullptr);
}

}
