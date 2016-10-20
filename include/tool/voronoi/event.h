#ifndef EVENT_H
#define EVENT_H

#include "map/point.h"
#include "map/zone.h"

namespace vor

{

class Parabola;

///
/// \brief The QueuedEvent class
/// represent an event (next point in x coordinate or intersection of three circles)
/// \todo Replace with Site when sure of implementation
///
class Event
{

public:

    ///
    /// \brief Default constructor.
    /// \param Point at which the event is located. NO NOT DELETE
    /// \param True if event is special.
    ///
    explicit Event(Point *p, bool ispe) :
        arch(nullptr),
        point(p),
        is_par_event(ispe),
        y(p->y)
        {}

    ///
    /// \brief If the parabola intersect another parabola.
    ///
    Parabola    *arch;

    ///
    /// \brief If point.
    ///
    Point       *point;

    ///
    /// \brief True if the parabola is part of an event.
    ///
    bool        is_par_event;

    ///
    /// \brief y coordinate of the parabola.
    ///
    double      y;

    // Doit y'avoir moyen rester sur une map ou un set simple, voir une liste
    ///
    /// \brief Structure for comparing events
    ///
    struct compareEvent : public std::binary_function<Event *, Event *, bool>
    {
        bool    operator()(const Event *l, const Event *r) const
        { return (l->y < r->y); }
    };

};

}

#endif // EVENT_H
