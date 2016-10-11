#ifndef MOISTOR_H
#define MOISTOR_H

#include "generationstep.h"
#include "Generator/param/intvalue.h"

namespace gen {

///
/// \brief This class assigns moisture to the corners and zones of a Voronoi diagram.
/// Based on the design found in https://github.com/amitp/mapgen2
///
class MoistorStep : public GenerationStep
{
public:
    ///
    /// \brief Default constructor.
    ///
    MoistorStep();

    ///
    /// \brief Default destructor.
    ///
    ~MoistorStep();

    ///
    /// \brief Runs the generation step.
    ///
    virtual void run();

    ///
    /// \brief Assign moisture to Voronoi polygon's corners.
    ///
    void    assignCornerMoisture();

    ///
    /// \brief Redistributes moisture following a linear curve.
    ///
    void    redistributeMoisture();

    ///
    /// \brief Assign Voronoi polygon's moisture (= avg. of its corners).
    ///
    void    assignPolygonMoisture();

    ///
    /// \brief let the user influence the moisture
    ///
    IntValue        m_moistureFactor;

private:

};

}

#endif // MOISTOR_H
