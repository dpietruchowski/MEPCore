#include "function.h"

namespace mep {

Function::Function(const Type& function, const std::string& name, uint nArgs):
    Operation(name, nArgs), function_(function)
{ }

std::any Function::runOperation(const Args<std::any>& args) const {
  return function_(args);
}
/*
std::any Function::runOperation(const RefArgs<std::any>& args) const {
  return function_(args);
}
*/
void Function::write(std::string& objectStr) const {
  objectStr += "Function";
}

}