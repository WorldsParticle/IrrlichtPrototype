#ifndef SHAPER_H
#define SHAPER_H

#include "generationstep.h"
#include "../param/intvalue.h"

namespace gen {

///
/// \brief This class determines the land types of the corners and zones of a Voronoi diagram.
/// Based on the design found in https://github.com/amitp/mapgen2
///
class ShaperStep : public GenerationStep
{
public:
    ///
    /// \brief Default constructor.
    ///
    ShaperStep(const std::string &name);

    ///
    /// \brief Default destructor.
    ///
    ~ShaperStep();

    ///
    /// \brief Runs the generation step.
    ///
    virtual void run();

private:

    ///
    /// \brief Assign land corners and ocean corners.
    /// \param Seed for randomization of noise on the z coordinate.
    ///
    void        assignCornerLandPerlin(int seed);

    ///
    /// \brief Assign land and ocean zones according to corners' value.
    ///
    void        assignOceanCostAndLand();

    ///
    /// \brief let the user select the percentage of land
    ///
    IntValue        m_landRatio;
};

}

#endif // SHAPER_H
