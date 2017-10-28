#ifndef OPERATION_H
#define OPERATION_H

#include "utils/types.h"

#include <string>
#include <assert.h>

namespace mep {

template<typename Type>
class Operation {
public:
    Operation(const std::string& name, uint nArgs):
        name_(name), nArgs_(nArgs)
    { }

    Type run(const Args<Type>& args) const {
        assert(args.size() == nArgs_);
        return runOperation(args);
    }

    std::string write() const {
        std::string operationStr = "O name: " + name_ +
                ", number of arguments: " + std::to_string(nArgs_) + ", ";
        write(operationStr);
        return operationStr;
    }
    uint nArgs() const { return nArgs_; }

private /* methods */:
    virtual Type runOperation(const Args<Type>& args) const = 0;
    virtual void write(std::string& operationStr) const = 0;

private:
    std::string name_;
    uint nArgs_;
};

}

#endif // OPERATION_H
