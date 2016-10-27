#ifndef PARABOLA_H
#define PARABOLA_H

#include "map/point.h"

namespace map
{
    class Zone;
}

namespace vor
{

class Event;
class Edge;

///
/// \brief The Parabola class
/// keep in mind that sweepline is going down (horizontal beachline)
/// todo : change right/left to prev/next ?
class Parabola
{
public:

    ///
    /// \brief Max parabola index on the associated Voronoi diagram.
    ///
    static int  indexMax;  // change this

    ///
    /// \brief Index of the parabola on the associated Voronoi diagram.
    ///
    const int   index;

    /*
        isLeaf		: flag whether the node is Leaf or internal node
        site		: pointer to the focus point of parabola (when it is parabola)
        corner		: pointer to the corner
        cEvent		: pointer to the event, when the arch disappears (circle event) // rework this
        parent		: pointer to the parent node in tree
    */

    ///
    /// \brief Flag whether the node is Leaf or internal node.
    ///
    bool		isLeaf;

    ///
    /// \brief Pointer to the focus point of parabola (when it is parabola).
    ///
    Point       *site;

    // when not leaf
    ///
    /// \brief Default constructor.
    ///
    Edge        *edge;

    ///
    /// \brief Pointer to the event, when the arch disappears (circle event).
    ///
    Event       *cEvent;

    ///
    /// \brief Pointer to the parent node in tree.
    ///
    Parabola    *parent;

    /*
        Constructors of the class (empty for edge, with focus parameter for an arch).
    */
    ///
    /// \brief Default constructor.
    ///
    Parabola	();

    ///
    /// \brief Constructor with focus parameter for an arch.
    /// \param Focus parameter
    ///
    Parabola	(Point *p);

    ///
    /// \brief Default desructor..
    ///
    ~Parabola   ();

    inline friend std::ostream &operator<<(std::ostream &os, const Parabola &p)
    { return os << "isLeaf[" << p.isLeaf << "] index[" << p.index << "]"; }

    /*
        Access to the children (in tree).
    */

    ///
    /// \brief Sets the left parabola.
    /// \param Pointer to new left parabola.
    ///
    inline void setLeft (Parabola * p) {_left  = p; p->parent = this;}

    ///
    /// \brief Sets the right parabola.
    /// \param Pointer to new right parabola.
    ///
    inline void setRight(Parabola * p) {_right = p; p->parent = this;}

    ///
    /// \brief Left parabola getter.
    ///
    Parabola    *left () const { return _left;  }

    ///
    /// \brief Right parabola getter.
    ///
    Parabola    *right() const { return _right; }

    /*
        Some useful tree operations  // why static ?

        GetLeft			: returns the closest left leave of the tree
        GetRight		: returns the closest right leafe of the tree
        GetLeftParent	: returns the closest parent which is on the left
        GetRightParent	: returns the closest parent which is on the right
        GetLeftChild	: returns the closest leave which is on the left of current node
        GetRightChild	: returns the closest leave which is on the right of current node
    */

    ///
    /// \brief Returns the closest left leave of the tree.
    /// \param Parabola.
    ///
    static Parabola * getLeft			(Parabola * p);

    ///
    /// \brief Returns the closest right leafe of the tree.
    /// \param Parabola.
    ///
    static Parabola * getRight			(Parabola * p);

    ///
    /// \brief Returns the closest parent which is on the left.
    /// \param Parabola.
    ///
    static Parabola * getLeftParent     (Parabola * p);

    ///
    /// \brief Returns the closest parent which is on the right.
    /// \param Parabola.
    ///
    static Parabola * getRightParent	(Parabola * p);

    ///
    /// \brief Returns the closest leave which is on the left of current node.
    /// \param Parabola.
    ///
    static Parabola * getLeftChild		(Parabola * p);

    ///
    /// \brief Default constructor.
    /// \param Parabola.
    ///
    static Parabola * getRightChild     (Parabola * p);

    ///
    /// \brief Returns the closest leave which is on the right of current node.
    ///
    Parabola(const Parabola& other);

    ///
    /// \brief Default constructor.
    ///
    Parabola(Parabola&& other);

    ///
    /// \brief Default constructor.
    ///
    Parabola& operator=(const Parabola& other);

    ///
    /// \brief Default constructor.
    ///
    Parabola& operator=(Parabola && other);

private:

    ///
    /// \brief Left parabola.
    ///
    Parabola * _left;

    ///
    /// \brief Right parabola.
    ///
    Parabola * _right;
};

}

#endif // PARABOLA_H
