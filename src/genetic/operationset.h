#ifndef MEP_GENETIC_OPERATIONSET_H
#define MEP_GENETIC_OPERATIONSET_H

#include "ptrset.h"
#include "utils/types.h"
#include "utils/log.h"
#include "operation.h"

namespace mep {

template<typename Type>
class OperationSet
{
public:
    OperationSet(const Type& terminal, const std::string& name):
        terminal_(terminal, name)
    { }
    OperationSet(const Terminal<Type>& terminal):
        terminal_(terminal)
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
        Operation<Type>* operation = set_.rand();
        ChromosomeLog(DEBUG) << "Random operation: " << operation->write();
        return operation;
    }
    Operation<Type>* terminal() {
        return &terminal_;
    }

    void reset() {
        set_.reset();
    }

private:
    PtrSet<Operation<Type>> set_;
    Terminal<Type> terminal_;
};

}

#endif // MEP_GENETIC_OPERATIONSET_H
