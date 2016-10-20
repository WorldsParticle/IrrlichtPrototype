#include "tool/voronoi/parabola.h"

namespace vor
{

int Parabola::indexMax = 0;

Parabola::Parabola() :
    index(indexMax),
    isLeaf(false),
    site(nullptr),
    edge(nullptr),
    cEvent(nullptr),
    parent(nullptr),
    _left(nullptr),
    _right(nullptr)
{
    ++indexMax;
}

Parabola::Parabola(Point *p) :
    index(indexMax),
    isLeaf(true),
    site(p),
    edge(nullptr),
    cEvent(nullptr),
    parent(nullptr),
    _left(nullptr),
    _right(nullptr)
{
    ++indexMax;
}

Parabola::~Parabola()
{
    site = nullptr;
    cEvent = nullptr;
    edge = nullptr;
    parent = nullptr;
    _left = nullptr;
    _right = nullptr;
}

/*
    Tree operations (described in the header file)
*/

Parabola * Parabola::getLeft			(Parabola * p)
{
    return getLeftChild(getLeftParent(p));
}


Parabola * Parabola::getRight(Parabola * p)
{
    return getRightChild(getRightParent(p));
}

Parabola * Parabola::getLeftParent(Parabola * p)
{
    Parabola * par		= p->parent;
    Parabola * pLast	= p;
    while(par->left() == pLast)
    {
        if(!par->parent) return nullptr;
        pLast = par;
        par = par->parent;
    }
    return par;
}

Parabola * Parabola::getRightParent(Parabola * p)
{
    Parabola * par		= p->parent;
    Parabola * pLast	= p;
    while(par->right() == pLast)
    {
        if(!par->parent) return nullptr;
        pLast = par; par = par->parent;
    }
    return par;
}

Parabola * Parabola::getLeftChild(Parabola * p)
{
    if(!p) return nullptr;
    Parabola * par = p->left();
    while(par && !par->isLeaf)
        par = par->right();
    return par;
}

Parabola * Parabola::getRightChild(Parabola * p)
{
    if(!p) return nullptr;
    Parabola * par = p->right();
    while(par && !par->isLeaf)
        par = par->left();
    return par;
}

Parabola::Parabola(const Parabola& other) :
index(other.index),
isLeaf(other.isLeaf),
site(other.site),
edge(other.edge),
cEvent(other.cEvent),
parent(other.parent),
_left(other.left()),
_right(other.right())
{
}

Parabola::Parabola(Parabola&& other) :
    index(other.index),
    isLeaf(other.isLeaf),
    site(other.site),
    edge(other.edge),
    cEvent(other.cEvent),
    parent(other.parent),
    _left(other.left()),
    _right(other.right())
{
}

Parabola& Parabola::operator=(const Parabola& other)
{
    if (&other != this)
    {
        *(const_cast<int *>(&(this->index))) = other.index;
        isLeaf = other.isLeaf;
        site = other.site;
        edge = other.edge;
        cEvent = other.cEvent;
        parent = other.parent;
        _left = other.left();
        _right = other.right();
    }
    return *this;
}

Parabola& Parabola::operator=(Parabola && other)
{
    if (&other != this)
    {
        *(const_cast<int *>(&(this->index))) = other.index;
        isLeaf = other.isLeaf;
        site = other.site;
        edge = other.edge;
        cEvent = other.cEvent;
        parent = other.parent;
        _left = other.left();
        _right = other.right();
    }
    return *this;
}

}
