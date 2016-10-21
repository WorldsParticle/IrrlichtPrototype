#ifndef HEIGHTMAPINGSTEP_HPP
#define HEIGHTMAPINGSTEP_HPP

#include "generationstep.h"
#include "Generator/map/zonelookup.h"
#include "bitmap/bitmap_image.h"

namespace gen
{

///
/// \brief The HeightMapingStep class
/// it will fill the heightmap points height
///
class HeightMapingStep : public GenerationStep
{
public:
    HeightMapingStep();
    virtual ~HeightMapingStep();

    void    run();

private:

    // temporary painters
    void    paintByMoisture();
    void    paintByHeight();
    void    paintByBiome();
    void    paintByLandType();

    ///
    /// \brief Class holding the zone's center kd-tree.
    /// should move it inside MapGraph, and createCould at the end of zoningStep
    ///
    map::ZoneLookUp m_zoneLookUp;
};

}

#endif  /* HEIGHTMAPINGSTEP_HPP */
