#ifndef POPULATION_H
#define POPULATION_H

#include "operationset.h"
#include "selection.h"
#include "mutation.h"
#include "crossover.h"
#include "fitness.h"
#include "core/chromosome.h"

#include <vector>
#include <map>
#include <memory>

namespace mep {

template<typename Type>
class Population {
public:
    Population(uint size, const Terminal<Type>& baseTerminal,
               Selection* selection, Fitness<Type>* fitness):
        operationSet(baseTerminal), selection_(selection), fitness_(fitness) {
        population_.reserve(size);
    }

    void init(uint individualSize) {
        for(uint i = 0; i < population_.capacity(); ++i) {
            Chromosome<Type> individual(i, individualSize);
            individual.init(operationSet, i);
            add(std::move(individual));
        }
    }

    Chromosome<Type> reproduce() const {

    }

    void add(Chromosome<Type>&& individual) {
        individual.run(fitness_.get());
        Chromosome<Type>* inserted = nullptr;
        if(population_.size() < population_.capacity()) {
            population_.emplace_back(std::move(individual));
            inserted = &population_.back();
        } else {
            auto worst = sorted_.rbegin();
            inserted = worst->second;
            *inserted = std::move(individual);
            sorted_.erase(worst->first);
        }
        sorted_.insert(std::make_pair(inserted->score(), inserted));
    }


public /* members */:
    OperationSet<Type> operationSet;
    PtrSet<Mutation<Type>> mutationSet;
    PtrSet<Crossover<Type>> crossoverSet;

private /* members */:
    std::unique_ptr<Selection> selection_;
    std::unique_ptr<Fitness<Type>> fitness_;
    // vector or list?
    std::vector<Chromosome<Type>> population_;
    std::map<uint, Chromosome<Type>*> sorted_;
};

}

#endif // POPULATION_H
