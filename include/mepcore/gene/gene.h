#ifndef MEP_CORE_GENE_H
#define MEP_CORE_GENE_H

#include <memory>
#include <vector>

#include "operation.h"

namespace mep {

using uint = unsigned int;

class Gene
{
 public:
  template<typename TerminalModel>
  Gene(const TerminalModel& terminal): concept_(new Model<TerminalModel>(terminal)),
      children_(), isCleared_{true}
  { }

  Gene(const Gene& other): concept_(other.concept_->clone()), 
      children_(other.children_), isCleared_{true}
  { }
  Gene(Gene&& other): concept_(other.concept_->clone()), 
      children_(std::move(other.children_)), isCleared_{true} {
    other.children_.clear();
  }
  const Gene& operator=(const Gene& rhs) {
    if (&rhs != this) {
      *concept_ = *rhs.concept_;
      children_ = rhs.children_;
      isCleared_ = true;
    }
    return *this;
  }
  Gene& operator=(Gene&& rhs) {
    if (&rhs != this) {
      *concept_ = *rhs.concept_;
      rhs.concept_.reset();
      children_ = std::move(rhs.children_);
      rhs.children_.clear();
      isCleared_ = true;
    }
    return *this;
  }

  uint assess() const;
  void run(const std::vector<Gene*>& args);
  bool addChild(uint idx);
  const std::vector<uint>& children() const;
  bool isCleared() const;
  uint nArgs() const;
  void clear();
  void show() const;

 private:
  struct Concept {
    virtual uint assess() const = 0;
    virtual void run(const std::vector<Concept*>& args) = 0;
    virtual uint nArgs() const = 0;
    virtual void clear() = 0;
    virtual std::string write() const = 0;
    virtual void show() const = 0;
    virtual std::unique_ptr<Concept> clone() const = 0;
  };

  template<typename TerminalModel>
  struct Model : public Concept {
    using OperationPtr = Operation<typename TerminalModel::Type>*;
    using Result = typename TerminalModel::Type;
    Model(const TerminalModel& terminal): operation(terminal.operation), result{} {}
    Model(const Model& other): operation(other.operation), result{} {}
    Model& operator=(const Model& rhs) {
      if (&rhs != this) {
          operation = rhs.operation;
          clear();
      }
    }

    void run(const std::vector<Concept*>& args) {
      // assert static_cast
      std::vector<typename TerminalModel::Type*> operation_args;
      operation_args.reserve(args.size());
      for(const auto concept: args) {
        Model<TerminalModel> *arg = static_cast<Model<TerminalModel> *> (concept);
        operation_args.push_back(&arg->result);
      }
      result = operation->run(operation_args);
    }

    uint assess() const override {
      return TerminalModel::assess(result);
    }

    uint nArgs() const override {
      return operation->nArgs();
    }

    void clear() override {
      TerminalModel::clear(result);
    }

    std::string write() const override {
      return operation->write();
    }

    void show() const override {
      TerminalModel::show(result);
    }

    std::unique_ptr<Concept> clone() const {
      return std::unique_ptr<Concept>(new Model<TerminalModel>(*this));
    }

    OperationPtr operation;
    Result result;
  };

  std::unique_ptr<Concept> concept_;
  std::vector<uint> children_;
  bool isCleared_;
};

} // namespace mep

#endif // MEP_CORE_GENE_H
