#include "gtest/gtest.h"
#include "base.h"
#include "other_base.h"
#include "derived.h"
#include <memory>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/types/polymorphic.hpp>

template<typename T>
using output_serializers = cereal::traits::detail::count_output_serializers<T,
    cereal::PortableBinaryOutputArchive>;

template<typename T>
using input_serializers = cereal::traits::detail::count_input_serializers<T,
    cereal::PortableBinaryInputArchive>;

TEST(Serialization, Base) {
    ASSERT_EQ(output_serializers<Base>::value, 1);
    ASSERT_EQ(output_serializers<Derived>::value, 1);

    std::stringstream ss;
    {
        cereal::PortableBinaryOutputArchive oarchive(ss);

        std::shared_ptr<Base> ptr = std::make_shared<Derived>(3, 4, 5);

        oarchive(ptr);
    }

    {
        cereal::PortableBinaryInputArchive iarchive(ss);

        std::shared_ptr<Base> obj;
        iarchive(obj);

        Derived *d = dynamic_cast<Derived*>(obj.get());
        ASSERT_NE(nullptr, d);
        ASSERT_EQ(3, d->derivedVal);
        ASSERT_EQ(4, d->baseVal);
        ASSERT_EQ(5, d->otherBaseVal);
    }
}

TEST(Serialization, OtherBase) {
    ASSERT_EQ(output_serializers<OtherBase>::value, 1);
    ASSERT_EQ(output_serializers<Derived>::value, 1);

    std::stringstream ss;
    {
        cereal::PortableBinaryOutputArchive oarchive(ss);

        std::shared_ptr<OtherBase> ptr = std::make_shared<Derived>(3, 4, 5);

        oarchive(ptr);
    }

    {
        cereal::PortableBinaryInputArchive iarchive(ss);

        std::shared_ptr<OtherBase> obj;
        iarchive(obj);

        Derived *d = dynamic_cast<Derived*>(obj.get());
        ASSERT_NE(nullptr, d);
        ASSERT_EQ(3, d->derivedVal);
        ASSERT_EQ(4, d->baseVal);
        ASSERT_EQ(5, d->otherBaseVal);
    }
}
