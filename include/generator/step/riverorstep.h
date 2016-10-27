#ifndef RIVEROR_H
#define RIVEROR_H

#include "generationstep.h"
#include "map/map.h"
#include "../param/intvalue.h"

namespace gen {

///
/// \brief This class generates rivers and determine watersheds on a Voronoi diagram.
/// Based on the design found in https://github.com/amitp/mapgen2
///
class RiverorStep : public GenerationStep
{
public:
    ///
    /// \brief Default constructor.
    ///
    RiverorStep(const std::string &name);

    ///
    /// \brief Default destructor.
    ///
    ~RiverorStep();


    ///
    /// \brief Runs the generation step.
    ///
    virtual void run();

private:
    ///
    /// \brief Generates rivers.
    ///
    void                createRivers();

    ///
    /// \brief Calculate the watersheds.
    ///
    void                calculateWatersheds();

    ///
    /// \brief Find edge associated to two corners.
    /// \param From corner.
    /// \param To corner.
    ///
    ::map::CrossedEdge    *lookupEdgeFromCorner(::map::Corner *from,:: map::Corner *to);

    ///
    /// \brief let the user select the number of rivers
    ///
    IntValue        m_riverFactor;

};

}

#endif // RIVEROR_H
