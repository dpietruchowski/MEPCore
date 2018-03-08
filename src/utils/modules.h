#ifndef MEP_UTILS_MODULES_H
#define MEP_UTILS_MODULES_H

#include "core.h"
#include "operation.h"
#include "genetic.h"

namespace mep {

template<typename Type>
struct modules {
    using Operation = Operation<Type>;
    using Function = Function<Type>;
    using Terminal = Terminal<Type>;
    using Gene = Gene<Type>;
    using Chromosome = Chromosome<Type>;
    using Fitness = Fitness<Type>;
    using OperationSet = OperationSet<Type>;
    using Mutation = Mutation<Type>;
    using ArgumentMutation = ArgumentMutation<Type>;
    using AttributeMutation = AttributeMutation<Type>;
    using CombinedMutation = CombinedMutation<Type>;
    using Crossover = Crossover<Type>;
    using OnePointCrossover = OnePointCrossover<Type>;
    using TwoPointCrossover = TwoPointCrossover<Type>;
    using UniformCrossover = UniformCrossover<Type>;
    using Population = Population<Type>;
};

}

#endif // MEP_UTILS_MODULES_H
