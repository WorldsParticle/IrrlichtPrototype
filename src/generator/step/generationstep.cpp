#include "generator/step/generationstep.h"

namespace gen
{

Param  *GenerationStep::param(const std::string &name)
{
    for (const auto &p: m_params)
        if (p->name() == name)
            return p;
    return (nullptr);
}

}
