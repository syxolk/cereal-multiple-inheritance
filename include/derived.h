#ifndef CEREAL_TEST_DERIVED_H
#define CEREAL_TEST_DERIVED_H

#include "base.h"
#include "other_base.h"

#include "cereal/types/base_class.hpp"
#include "cereal/types/polymorphic.hpp"

CEREAL_FORCE_DYNAMIC_INIT(milk)

class Derived : public Base, public OtherBase {
public:
    Derived(int derivedVal = 0, int baseVal = 0, int otherBaseVal = 0);

    int derivedVal;

    template<class Archive>
    void serialize(Archive &ar) {
        ar(cereal::base_class<Base>(this), cereal::base_class<OtherBase>(this),
           derivedVal);
    }
};

#endif // CEREAL_TEST_DERIVED_H
