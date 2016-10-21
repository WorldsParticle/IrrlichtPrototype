#ifndef GENERATOR_MARIE_H
#define GENERATOR_MARIE_H

#include "steps/generationstep.h"
#include <map>
#include <list>


#include "map/map.h"
#include "steps/generationstep.h"

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

    ///
    /// \brief Executes the map generation steps.
    ///
    void run(::map::MapGraph *map);

    ///
    /// \brief steps getter
    /// \return
    ///
    inline const std::list<GenerationStep *>  &steps()
    { return m_steps; }

    ///
    /// \brief stepFromName
    /// \param name
    /// \return step
    ///
    GenerationStep  *stepFromName(const std::string &namee);

protected:
    ///
    /// \brief steps which are run (in order)
    ///
    std::list<GenerationStep *> m_steps;
};

}

#endif // GENERATOR_H
