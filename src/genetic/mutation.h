#ifndef MEP_GENETIC_MUTATION_H
#define MEP_GENETIC_MUTATION_H

#include "core/chromosome.h"
#include "core/gene.h"
#include "utils/random.h"
#include "utils/log.h"
#include "genetic/operationset.h"

namespace mep {

template<typename Type>
class Mutation {
public:
    void operator()(OperationSet<Type>& operationSet,
                    Chromosome<Type>& child) {
        uint nGenes = UintRandom(1, (child.size() + 1) / 2)();
        for(uint i = 0; i < nGenes; ++i) {
            auto size = child.size();
            UintRandom random(1, size - 1);
            auto cutPoint = random();
            const Gene<Type>& mutated = child.at(cutPoint);
            auto newGene = createGene(operationSet, mutated, cutPoint);
            newGene.setColor(Color::YELLOW);
            child.mutate(std::move(newGene), cutPoint);
        }
    }
private:
    virtual Gene<Type> createGene(OperationSet<Type>& operationSet,
                                  const Gene<Type>& mutated,
                                  uint cutPoint) const = 0;
};

template<typename Type>
class ArgumentMutation final: public Mutation<Type> {
private:
    Gene<Type> createGene(OperationSet<Type>& /* operationSet */,
                          const Gene<Type>& mutated,
                          uint cutPoint) const override {
        PopulationLog(DEBUG) << "Argument Mutation...";
        IdxArgs newArgs;
        UintRandom childRandom(0, cutPoint - 1);
        for(uint i = 0; i < mutated.nArgs(); ++i) {
            newArgs.push_back(childRandom());
        }
        Gene<Type> newGene(mutated, newArgs);
        return newGene;
    }
};

template<typename Type>
class AttributeMutation final: public Mutation<Type> {
private:
    Gene<Type> createGene(OperationSet<Type>& operationSet,
                          const Gene<Type>& mutated,
                          uint cutPoint) const override {
        PopulationLog(DEBUG) << "Attribute Mutation...";
        Gene<Type> newGene(mutated, operationSet.rand());
        UintRandom childRandom(0, cutPoint - 1);
        while(newGene.children().size() < newGene.nArgs()) {
            newGene.addChild(childRandom());
        }
        assert(newGene.children().size() == newGene.nArgs());
        return newGene;
    }
};

template<typename Type>
class CombinedMutation final: public Mutation<Type> {
private:
    Gene<Type> createGene(OperationSet<Type>& operationSet,
                          const Gene<Type>& /* mutated */,
                          uint cutPoint) const override {
        PopulationLog(DEBUG) << "Combined Mutation...";
        //TODO newGene id should not be always 0
        Gene<Type> newGene(0, operationSet.rand());
        UintRandom childRandom(0, cutPoint - 1);
        for(uint i = 0; i < newGene.nArgs(); ++i) {
            newGene.addChild(childRandom());
        }
        return newGene;
    }
};

}

#endif // MEP_GENETIC_MUTATION_H
