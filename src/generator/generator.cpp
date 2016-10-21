#include "generator/generator.h"

#include "map/map.h"
#include "generator/step/zoningstep.h"
#include "generator/step/shaperstep.h"
#include "generator/step/elevatorstep.h"
#include "generator/step/riverorstep.h"
#include "generator/step/moistorstep.h"
#include "generator/step/biomizatorstep.h"
#include "generator/step/heightmapingstep.h"
#include "generator/step/texturestep.h"

namespace gen
{

Generator::Generator() :
    m_steps()
{
}

Generator::~Generator()
{
  for (GenerationStep *step : m_steps)
    delete step;
}

::map::MapGraph    *Generator::run(unsigned int xMax, unsigned int yMax)
{
  map::MapGraph *map = new map::MapGraph(xMax, yMax, 500); // gridSize have to move inside a step
    for (const auto &step: m_steps)
    {
        std::cout << step->name() << std::endl;
        step->launch(map);
    }
  return map;
}

GenerationStep  *Generator::step(const std::string &name)
{
    for (const auto &s: m_steps)
        if (s->name() == name)
            return s;
    return (nullptr);
}

}
