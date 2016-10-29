#ifndef LAKER_H
#define LAKER_H

#include <irrlicht.h>
#include "generationstep.h"
#include "map/map.h"
#include "../param/intvalue.h"

#include "map/lake.h"
#include <queue>
#include <vector>
#include <stack>

namespace gen {

class LakerStep : public GenerationStep
{
public:
    LakerStep(const std::string &name);

    ~LakerStep();

    virtual void run();

private:

    void                createMesh(::map::Lake * lake, float lakeHeight);
    void                fillDepthMap(std::vector<int> & depthMap, unsigned int xMax, ::map::Lake * lake);
    void                createLakes();
};

}

#endif // LAKER_H
