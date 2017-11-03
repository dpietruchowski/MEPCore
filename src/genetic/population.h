#ifndef MEP_GENETIC_POPULATION_H
#define MEP_GENETIC_POPULATION_H

#include "utils/log.h"
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
        operationSet(baseTerminal), selection_(selection), fitness_(fitness),
        actualSelection_(false)
    {
        population_.reserve(size);
    }

    void init(uint individualSize) {
        PopulationLog(DEBUG) << "Initialization...";
        for(uint i = 0; i < population_.capacity(); ++i) {
            bool added = false;
            do {
                Chromosome<Type> individual(i + i*individualSize, individualSize);
                individual.init(operationSet, i + i*individualSize);
                added = add(std::move(individual));
            } while(!added);
        }
    }

    Chromosome<Type> reproduce() {
        PopulationLog(DEBUG) << "Reproduction...";
        PopulationLog(DEBUG) << "Selection...";
        if(!actualSelection_) {
            selection_->reset();
            uint i = 0;
            for(const auto& idx: sorted_) {
                selection_->add(idx.second, idx.first, i);
                ++i;
            }
            actualSelection_ = true;
        }
        uint parent1 = selection_->select();
        uint parent2 = selection_->select();

        PopulationLog(DEBUG) << "Crossover...";
        Crossover<Type> *crossover = crossoverSet.rand();
        Chromosome<Type> child = (*crossover)(population_[parent1],
                                              population_[parent2]);
        PopulationLog(DEBUG) << "Mutation...";
        Mutation<Type> *mutation = mutationSet.rand();
        (*mutation)(operationSet, child);
        return child;
    }

    bool add(Chromosome<Type>&& individual) {
        PopulationLog(DEBUG) << "Adding individual... " << individual.writeShort();
        individual.run(fitness_.get());
        // For increasing diversity
        if(sorted_.count(individual.score()) > 0) {
            PopulationLog(DEBUG) << "Not added. Individual with " <<
                                    individual.score() << " score exists";
            return false;
        }
        uint inserted = 0;
        if(population_.size() < population_.capacity()) {
            population_.emplace_back(std::move(individual));
            inserted = population_.size() - 1;
        } else {
            auto worst = sorted_.rbegin();
            inserted = worst->second;
            population_[inserted] = std::move(individual);
            sorted_.erase(worst->first);
        }
        sorted_.insert(std::make_pair(population_[inserted].score(), inserted));
        actualSelection_ = false;
        PopulationLog(DEBUG) << "Individual added";
        return true;
    }

    uint avScore() const {
        double sum = 0;
        for(const auto& ind: population_) {
            sum += ind.score();
        }
        return sum / population_.size();
    }
    uint bestScore() const {
        auto iter = sorted_.begin();
        return population_[iter->second].score();
    }

    Chromosome<Type>& best() {
        auto iter = sorted_.begin();
        return population_[iter->second];
    }

    void movePopulation(Population&& population) {
        uint size = population.population_.size();
        population_ = std::move(population.population_);
        population.population_.clear();
        population.population_.reserve(size);
        sorted_ = std::move(population.sorted_);
        population.sorted_.clear();
        actualSelection_ = false;
    }


public /* members */:
    OperationSet<Type> operationSet;
    PtrSet<Mutation<Type>> mutationSet;
    PtrSet<Crossover<Type>> crossoverSet;

private /* members */:
    mutable std::unique_ptr<Selection> selection_;
    std::unique_ptr<Fitness<Type>> fitness_;
    // vector or list?
    std::vector<Chromosome<Type>> population_;
    std::map<uint, uint> sorted_;
    mutable bool actualSelection_;
};

}

#endif // MEP_GENETIC_POPULATION_H
