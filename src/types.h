#ifndef TYPES_H
#define TYPES_H

#include <memory>
#include <vector>

namespace mep {

using uint = unsigned int;

template<typename Type>
class Gene;

template<typename Type>
using GenePtr = std::unique_ptr<Gene<Type>>;

template<typename Type>
using FunctionPtr = Type (*)(const std::vector<Type*>&);

template<typename Type>
struct Function {
    FunctionPtr<Type> ptr;
    std::string name;
    uint nArgs;
};

} // namespace mep

#endif // TYPES_H
