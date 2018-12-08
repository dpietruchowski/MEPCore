#include "operation.h"

namespace mep {

Operation::Operation(const std::string& name, uint nArgs):
    name_(name), nArgs_(nArgs)
{ }

std::any Operation::run(const Args<std::any>& args) const {
    return runOperation(args);
}
/*
std::any Operation::run(const RefArgs<std::any>& args) const {
    return runOperation(args);
}
*/
std::string Operation::write() const {
    std::string operationStr = "O name: " + name_ +
        ", number of arguments: " + std::to_string(nArgs_) + ", ";
    write(operationStr);
    return operationStr;
}

uint Operation::nArgs() const {
  return nArgs_;
}

}