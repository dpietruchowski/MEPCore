#ifndef MEP_CORE_OPERATION_H
#define MEP_CORE_OPERATION_H

#include <string>
#include <vector>

namespace mep {

template<typename TerminalType>
class Operation {
 public:
 using Args = std::vector<TerminalType*>;

 public:
  Operation(const std::string& name, uint nArgs):
      name_(name), nArgs_(nArgs) { }

  virtual ~Operation() = default;

  TerminalType run(const Args& args) const {
    /// assert(args.size() == nArgs_);
    return runOperation(args);
  }

  std::string write() const {
    std::string operationStr = "O name: " + name_ +
        ", number of arguments: " + std::to_string(nArgs_) +
        ", type: ";
    writeOperation(operationStr);
    return operationStr;
  }
  
  uint nArgs() const { return nArgs_; }

private /* methods */:
  virtual TerminalType runOperation(const Args& args) const = 0;
  virtual void writeOperation(std::string& operationStr) const = 0;

 private:
  std::string name_;
  uint nArgs_;
};

}

#endif // MEP_CORE_OPERATION_H