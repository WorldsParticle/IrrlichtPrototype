#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "generationstep.h"
#include "../param/intvalue.h"

namespace gen {

///
/// \brief This class assign heights to the corners and zones of a Voronoi diagram
/// Based on the design found in https://github.com/amitp/mapgen2
///
class ElevatorStep : public GenerationStep
{
public:
    ///
    /// \brief Default constructor.
    ///
    ElevatorStep();

    ///
    /// \brief Default destructor.
    ///
    ~ElevatorStep();

    ///
    /// \brief Runs the generation step.
    ///
    virtual void run();

private:

    ///
    /// \brief Assign's a Voronoi diagram's corners their height
    ///
    void        assignCornerElevation();

    ///
    /// \brief Redistribute the elevation to a x^2 type curve, yielding more lower heights.
    ///
    void        redistributeElevation();

    ///
    /// \brief Assign's a Voronoi diagram's polyongs their elevation (corner's average).
    ///
    void        setPolygonElevation();

    ///
    /// \brief Find for each Voronoi diagram's corners its neighboring corner with the lowest elevation.
    ///
    void        calculateDownSlopes();

    ///
    /// \brief let the user select how flat the terrain will be.
    ///
    IntValue        m_slopeFactor;

};

}

#endif // ELEVATOR_H
