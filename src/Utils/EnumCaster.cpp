#include "../../inc/Utils/EnumCaster.h"

std::string EnumCaster::castToString(NeighbourType type_)
{
    switch(type_)
    {
        case NeighbourType::Swap:
            return "swap";
        
        case NeighbourType::Insert:
            return "insert";

        case NeighbourType::Invert:
            return "invert";
            
        default:
            return "";
    }
}

std::string EnumCaster::castToString(MutationType type_)
{
    switch(type_)
    {
        case MutationType::Swap:
            return "swap";
        
        case MutationType::Insert:
            return "insert";

        default:
            return "";
    }
}

std::string EnumCaster::castToString(CrossoverType type_)
{
    switch(type_)
    {
        case CrossoverType::PMX:
            return "PMX";
        
        case CrossoverType::OX:
            return "OX";

        default:
            return "";
    }
}