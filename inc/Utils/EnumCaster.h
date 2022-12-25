#pragma once

#include "../Enums/TSEnum.h"
#include "../Enums/CrossoverType.h"
#include "../Enums/MutationType.h"

#include <string>

class EnumCaster
{
public:
    static std::string castToString(NeighbourType type_);
    static std::string castToString(MutationType type_);
    static std::string castToString(CrossoverType type_);
};