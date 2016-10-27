#ifndef HEIGHTMAPINGSTEP_HPP
#define HEIGHTMAPINGSTEP_HPP

#include "generationstep.h"
#include "map/zonelookup.h"
#include "tool/bitmap_image.h"

namespace gen
{

///
/// \brief The HeightMapingStep class
/// it will fill the heightmap points height
///
class HeightMapingStep : public GenerationStep
{
public:
    HeightMapingStep(const std::string &name);
    virtual ~HeightMapingStep();

    void    run();

private:

    // temporary painters
    void    paintByMoisture();
    void    paintByHeight();
    void    paintByBiome();
    void    paintByLandType();

    void    paintHeightmapGrid();

    ///
    /// \brief Class holding the zone's center kd-tree.
    /// should move it inside MapGraph, and createCould at the end of zoningStep
    ///
    ::map::ZoneLookUp m_zoneLookUp;
};

}

#endif  /* HEIGHTMAPINGSTEP_HPP */
