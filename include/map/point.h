#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <limits>
#include <cmath>

///
/// \brief This class stores the 2d (x, y) coordinates of a point.
///
class   Point
{
public:
    ///
    /// \brief Default constructors : expect x & y parameters.
    /// \param x coordinate
    /// \param y coordinate
    ///
    explicit Point(double nx, double ny) : x(nx), y(ny) {}

    inline friend std::ostream &operator<<(std::ostream &os, const Point &p)
    { return os << "(" << p.x << ", " << p.y << ")"; }

    inline bool operator==(const Point &other)
    { return (std::abs(x - other.x) < std::numeric_limits<double>::epsilon())
                && (std::abs(y - other.y) < std::numeric_limits<double>::epsilon()); }

    inline bool operator!=(const Point &other)
    { return !(*this == other); }

    ///
    /// \brief X coordinates of the point.
    ///
    double  x;

    ///
    /// \brief Y coordinates of the point.
    ///
    double  y;
};

#endif // POINT_H
