#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <limits>
#include <cmath>

///
/// \brief This class stores the 2d (x, z) coordinates of a point.
///
class   Point
{
public:
    ///
    /// \brief Default constructors : expect x & z parameters.
    /// \param x coordinate
    /// \param z coordinate
    ///
    explicit Point(double nx, double nz) : x(nx), z(nz) {}

    inline friend std::ostream &operator<<(std::ostream &os, const Point &p)
    { return os << "(" << p.x << ", " << p.z << ")"; }

    inline bool operator==(const Point &other)
    { return (std::abs(x - other.x) < std::numeric_limits<double>::epsilon())
                && (std::abs(z - other.z) < std::numeric_limits<double>::epsilon()); }

    inline bool operator!=(const Point &other)
    { return !(*this == other); }

    ///
    /// \brief X coordinates of the point.
    ///
    double  x;

    ///
    /// \brief Z coordinates of the point.
    ///
    double  z;
};

#endif // POINT_H
