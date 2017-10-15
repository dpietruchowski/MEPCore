#ifndef TYPES_H
#define TYPES_H

#include <memory>
#include <vector>

namespace mep {

using uint = unsigned int;

template<typename Type>
using Args = std::vector<Type*>;

template<typename Type>
class Operation;

template<typename Type>
using OperationPtr = std::unique_ptr<Operation<Type>>;

template<typename Type>
using FunctionPtr = Type (*)(const std::vector<Type*>&);
} // namespace mep

#endif // TYPES_H
