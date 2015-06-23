#ifndef CEREAL_TEST_OTHER_BASE_H
#define CEREAL_TEST_OTHER_BASE_H

class OtherBase {
public:
    OtherBase(int otherBaseVal);
    virtual ~OtherBase();

    int otherBaseVal;

    template<class Archive>
    void serialize(Archive ar) {
        ar(otherBaseVal);
    }
};

#endif // CEREAL_TEST_OTHER_BASE_H
