#include "Generator/steps/generationstep.h"

namespace gen
{

Param  *GenerationStep::paramFromName(const std::string &namee)
{
    for (const auto &p: m_params)
        if (p->name() == namee)
            return p;
    return (nullptr);
}

}
