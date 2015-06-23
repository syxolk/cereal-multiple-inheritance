#include "derived.h"
#include "cereal/types/polymorphic.hpp"
#include "cereal/archives/portable_binary.hpp"

Derived::Derived(int derivedVal, int baseVal, int otherBaseVal) : Base(baseVal),
    OtherBase(otherBaseVal), derivedVal(derivedVal) {}

CEREAL_REGISTER_TYPE(Derived)
CEREAL_REGISTER_DYNAMIC_INIT(milk)
