#ifndef MEP_UTILS_TYPES_H
#define MEP_UTILS_TYPES_H

#include <memory>
#include <vector>

namespace mep {

using uint = unsigned int;
using IdxArgs = std::vector<uint>;

template<typename Type>
using Args = std::vector<Type*>;

template<typename Type>
class Gene;
template<typename Type>
using GeneArgs = Args<Gene<Type>>;

template<typename Type>
using Genes = std::vector<Gene<Type>>;

template<typename Type>
class Chromosome;
template<typename Type>
using Parents = std::vector<Chromosome<Type>*>;

template<typename Type>
class Operation;

template<typename Type>
using OperationPtr = std::unique_ptr<Operation<Type>>;

template<typename Type>
using FunctionPtr = Type (*)(const Args<Type>&);

} // namespace mep

#endif // MEP_UTILS_TYPES_H
