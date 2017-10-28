#ifndef FITNESS_H
#define FITNESS_H

#include "utils/types.h"

namespace mep {

template<typename Type>
class Fitness {
public:
    Fitness(const Type &reference): reference_(reference)
    { }
    virtual ~Fitness()
    { }

    void setReference(const Type &reference) {
        reference_ = reference;
    }

    uint measure(const Type& input) const {
        return measure(input, reference_);
    }

private:
    virtual uint measure(const Type& input, const Type& reference) const = 0;

private:
    Type reference_;
};

}

#endif // FITNESS_H
