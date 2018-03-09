#ifndef MEP_CORE_TERMINAL_H
#define MEP_CORE_TERMINAL_H

#include "operation.h"

namespace mep {

template<typename TerminalType>
class Terminal: public Operation<TerminalType>
{
  using Args = typename Operation<TerminalType>::Args;

 public:
  Terminal(const TerminalType& terminal,const std::string& name):
      Operation<TerminalType>(name, 0), terminal_(terminal) { }

 private /* methods */:
  TerminalType runOperation(const Args& /* args */) const override {
    return terminal_;
  }

  void writeOperation(std::string &objectStr) const override {
    objectStr += "Terminal";
  }

 private:
  TerminalType terminal_;
};

}

#endif // MEP_CORE_TERMINAL_H
