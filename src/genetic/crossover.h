#ifndef MEP_GENETIC_CROSSOVER_H
#define MEP_GENETIC_CROSSOVER_H

#include "core/chromosome.h"
#include "utils/random.h"

namespace mep {

template<typename Type>
class Crossover {
public:
    Chromosome<Type> operator()(Chromosome<Type>& parent1,
                                Chromosome<Type>& parent2) {
        uint size = parent1.size() > parent2.size() ? parent1.size() :
                                                      parent2.size();
        Chromosome<Type> child(0, size);
        Parents<Type> parents = { &parent1, &parent2 };
        std::set<uint> cutPoints;
        UintRandom pointRandom(1, size - 1);
        crossover(cutPoints, pointRandom);
        child.crossover(parents, cutPoints);
        return child;
    }

private:
    virtual void crossover(std::set<uint>& cutPoints,
                   UintRandom& random) const = 0;
};

template<typename Type>
class OnePointCrossover final: public Crossover<Type> {
private:
    void crossover(std::set<uint>& cutPoints,
                   UintRandom& random) const override {
        cutPoints.insert(random());
    }
};

template<typename Type>
class TwoPointCrossover final: public Crossover<Type> {
private:
    void crossover(std::set<uint>& cutPoints,
                   UintRandom& random) const override {
        /// Three random points
        /// start -p1-> point1
        /// point1 -p2-> point2
        /// point2 -p1-> point3
        /// point3 -p2-> end;
        cutPoints.insert({random(), random()});
    }
};

template<typename Type>
class UniformCrossover final: public Crossover<Type> {
private:
    void crossover(std::set<uint>& cutPoints,
                   UintRandom& random) const override {
        uint nCuts = random();
        for(uint i = 0; i < nCuts; ++i)
            cutPoints.insert(random());
    }
};

}


#endif // MEP_GENETIC_CROSSOVER_H
