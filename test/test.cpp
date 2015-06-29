#include "gtest/gtest.h"
#include "base.h"
#include "other_base.h"
#include "derived.h"
#include <memory>
#include <type_traits>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/types/polymorphic.hpp>

template<typename T>
using output_serializers = cereal::traits::detail::count_output_serializers<T,
    cereal::PortableBinaryOutputArchive>;

template<typename T>
using input_serializers = cereal::traits::detail::count_input_serializers<T,
    cereal::PortableBinaryInputArchive>;

TEST(Serialization, Preconditions) {
    ASSERT_EQ(1, output_serializers<Base>::value);
    ASSERT_EQ(1, output_serializers<Derived>::value);
    ASSERT_EQ(1, output_serializers<OtherBase>::value);

    ASSERT_TRUE(std::is_polymorphic<Base>::value);
    ASSERT_TRUE(std::is_polymorphic<OtherBase>::value);
    ASSERT_TRUE(std::is_polymorphic<Derived>::value);

    constexpr bool baseOfBase = std::is_base_of<Base,Derived>::value;
    constexpr bool baseOfOtherBase = std::is_base_of<OtherBase,Derived>::value;
    ASSERT_TRUE(baseOfBase);
    ASSERT_TRUE(baseOfOtherBase);
}

TEST(Serialization, Base) {
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
