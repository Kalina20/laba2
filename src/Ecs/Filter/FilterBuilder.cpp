#include "FilterBuilder.h"

Filter FilterBuilder::Build() const
{
    return Filter(_world, _componentStorages);
}
