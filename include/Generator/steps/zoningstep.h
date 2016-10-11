#ifndef ZONINGSTEP_H
#define ZONINGSTEP_H

#include "Generator/generator.h"
#include "Generator/map/map.h"
#include "Generator/tools/voronoi/voronoi.h"
#include "generationstep.h"
#include "Generator/param/intvalue.h"

namespace gen
{

class ZoningStep : public GenerationStep
{
public:
    ///
    /// \brief ZoningStep constructor
    ///
    ZoningStep();

    ///
    /// \brief destructor
    ///
    virtual ~ZoningStep();

    ///
    /// \brief run
    /// carefull if run an already filled map
    ///
    virtual void    run();

private:

    ///
    /// \brief generate a random set of sites
    ///
    std::vector<Point *> generateRandomSites();

    ///
    /// \brief LloydRelaxation, used for smooth zones shape
    ///
    void    LloydRelaxation();

    ///
    /// \brief transfert the data from voronoi diagram to mapgraph
    /// \param edges is the result of fortune algorithme
    ///
    void    computeMap(const std::vector<vor::Edge *> *edges);

    ///
    /// \brief checkCorner
    /// \param z
    /// \param p
    /// \return corner
    ///
    map::Corner *checkCorner(map::Zone *z, Point &p);

    ///
    /// \brief object which construct voronoi edges
    ///
    vor::Voronoi    m_voronoi;

    ///
    /// \brief let the user select the zone number
    ///
    IntValue        m_zoneNumber;
};

}


#endif /* ZONINGSTEP_H */
