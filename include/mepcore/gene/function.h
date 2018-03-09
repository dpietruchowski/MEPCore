#ifndef MEP_CORE_FUNCTION_H
#define MEP_CORE_FUNCTION_H

#include "operation.h"

namespace mep {

template<typename TerminalType>
class Function final: public Operation<TerminalType>
{
  using Args = typename Operation<TerminalType>::Args;
 public:
  using Ptr = TerminalType (*)(const Args&);

 public:
  Function(Ptr function, const std::string& name, uint nArgs):
      Operation<TerminalType>(name, nArgs), function_(function) { }

 private /* methods */:
  TerminalType runOperation(const Args& args) const override {
    return function_(args);
  }

  void writeOperation(std::string &objectStr) const override {
    objectStr += "Function";
  }

 private:
  Ptr function_;
};

}
#endif // MEP_CORE_FUNCTION_H
