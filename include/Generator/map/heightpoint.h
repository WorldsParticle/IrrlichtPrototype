#ifndef HEIGHTPOINT_H
#define HEIGHTPOINT_H

#include <iostream>
#include <memory>
#include <cmath>
#include <limits>
#include "zone.h"

namespace map
{

///
/// \brief Point with an added pointer to the zone the point belongs to.
///
class   HeightPoint
{
public:

    ///
    /// \brief Default constructor.
    ///
    HeightPoint() : x(0.0), y(0.0), z(0.0), zone(nullptr) {}

    ///
    /// \brief Parametrized arguments using (x, y) 2D coordinates.
    /// \param x coordinate
    /// \param y coordinate
    ///
    HeightPoint(double nx, double ny) : x(nx), y(ny), z(0.0), zone(nullptr) {}

    inline friend std::ostream &operator<<(std::ostream &os, const HeightPoint &p)
    { return os << "(" << p.x << ", " << p.y << ", " << p.z << ")"; }

    inline bool operator==(const HeightPoint &other)
    { return (std::abs(x - other.x) < std::numeric_limits<double>::epsilon())
                && (std::abs(y - other.y) < std::numeric_limits<double>::epsilon()); }

    inline bool operator!=(const HeightPoint &other)
    { return !(*this == other); }

    ///
    /// \brief X coordinate of the heightpoint.
    ///
    double  x;

    ///
    /// \brief Y coordinate of the heightpoint.
    ///
    double  y;

    ///
    /// \brief Z coordinate of the heightpoint.
    ///
    double  z;

    ///
    /// \brief Zone to which the heightpoint belongs.
    ///
    Zone     *zone;
};

}

#endif // HEIGHTPOINT_H
