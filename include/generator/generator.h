#ifndef GENERATOR_MARIE_H
#define GENERATOR_MARIE_H

#include "step/generationstep.h"
#include <map>
#include <list>


#include "map/map.h"
#include "step/generationstep.h"

namespace map
{
class MapGraph;
}

namespace gen
{

///
/// \brief This class run a bunch of step whose fill the mapgraph
/// for now it will juste launch one by one the generation steps which have been assigned (actually in a static way)
///
class Generator
{
public:

    ///
    /// \brief Default constructor.
    ///
    Generator();

    /// destructor
    virtual ~Generator();

    ///
    /// \brief Executes the map generation steps.
    ///
    ::map::MapGraph *run(unsigned int xMax, unsigned int yMax);

    ///
    /// \brief steps getter
    /// \return
    ///
    inline std::list<GenerationStep *>  &steps()
    { return m_steps; }

    ///
    /// \brief getStep
    /// \param name
    /// \return step
    ///
    GenerationStep  *step(const std::string &name);

protected:
    ///
    /// \brief steps which are run (in order)
    ///
    std::list<GenerationStep *> m_steps;
};

}

#endif // GENERATOR_H
