#ifndef MEP_GENETIC_PTRSET_H
#define MEP_GENETIC_PTRSET_H

#include "utils/random.h"

#include <cmath>
#include <map>
#include <memory>
#include <utility>

namespace mep {

template<typename Type>
class PtrSet
{
public:
    PtrSet(): set_(), random_(0.0, 1.0)
    { }
    PtrSet(const PtrSet& other) = delete;
    PtrSet& operator=(const PtrSet& rhs) = delete;
    PtrSet(PtrSet&& other): set_(std::move(other.set_)), random_(0.0, 1.0)
    { }
    PtrSet& operator=(PtrSet&& rhs) {
        set_ = std::move(rhs.set_);
    }
    ~PtrSet() = default;

    void registerPtr(double probability, Type* ptr) {
        if(set_.empty()) {
            set_.emplace(std::piecewise_construct,
                         std::forward_as_tuple(probability),
                         std::forward_as_tuple(ptr));
        } else {
            auto last = set_.end();
            --last;
            double threshold = last->first + probability;

            threshold = std::round(threshold * 1000) / 1000;
            if(threshold > 1)
                throw "Can not add. Probability is greater than 1.";

            set_.emplace(std::piecewise_construct,
                         std::forward_as_tuple(threshold),
                         std::forward_as_tuple(ptr));
        }
    }

    void reset() {
        set_.clear();
    }

    Type* rand() const {
        if(set_.empty())
            throw "The set is empty.";
        auto last = set_.end();
        --last;
        double threshold = last->first;

        threshold = std::round(threshold * 1000) / 1000;
        if(threshold != 1)
            throw "Probability is not equal 1.";

        double random = const_cast<DoubleRandom&>(random_)();
        auto randomIter = set_.lower_bound(random);

        return randomIter->second.get();
    }
private:
    std::map<double, std::unique_ptr<Type>> set_;
    DoubleRandom random_;
};

}

#endif // MEP_GENETIC_PTRSET_H
