#ifndef OPERATIONSET_H
#define OPERATIONSET_H

#include "ptrset.h"
#include "utils/types.h"
#include "operation.h"

namespace mep {

template<typename Type>
class OperationSet
{
public:
    OperationSet(const Type& terminal, const std::string& name):
        terminal_(new Terminal<Type>(terminal, name))
    { }

    void registerPtr(double probability, Operation<Type>* ptr) {
        set_.registerPtr(probability, ptr);
    }
    void registerPtr(double probability, const Type& terminal,
                     const std::string& name) {
        set_.registerPtr(probability,
                         new Terminal<Type>(terminal, name));
    }
    void registerPtr(double probability, FunctionPtr<Type> function,
                     const std::string& name, uint nArgs) {
        set_.registerPtr(probability,
                         new Function<Type>(function, name, nArgs));
    }

    Operation<Type>* rand() {
        return set_.rand();
    }
    Operation<Type>* terminal() {
        return terminal_.get();
    }

    void reset() {
        set_.reset();
    }

private:
    PtrSet<Operation<Type>> set_;
    std::unique_ptr<Operation<Type>> terminal_;
};

}

#endif // OPERATIONSET_H
