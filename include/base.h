#ifndef CEREAL_TEST_BASE_H
#define CEREAL_TEST_BASE_H

class Base {
public:
    Base(int baseVal = 0);
    virtual ~Base();

    int baseVal;

    template<class Archive>
    void serialize(Archive ar) {
        ar(baseVal);
    }
};

#endif // CEREAL_TEST_BASE_H
