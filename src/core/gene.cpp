#include "gene.h"

#include <assert.h>

namespace mep {

Gene::Gene(uint id, Operation* operation): Object(id),
    operation_{operation}, children_{}, result_(), isCleared_(true)
{
  children_.reserve(operation_->nArgs());
}

Gene::Gene(const Gene& other): Object(other),
    operation_(other.operation_), children_(other.children_), result_(),
    isCleared_(true)
{
}

Gene& Gene::operator=(const Gene& rhs) {
  if (&rhs != this) {
    Object::operator =(rhs);
    operation_ = rhs.operation_;
    children_ = rhs.children_;
    result_ = {};
    isCleared_ = true;
  }
  return *this;

}
Gene::Gene(Gene&& other): Object(std::move(other)),
  operation_(other.operation_), children_(std::move(other.children_)),
  result_(), isCleared_(true) {
  other.children_.clear();
}

Gene& Gene::operator=(Gene&& rhs) {
  if (&rhs != this) {
    Object::operator =(std::move(rhs));
    operation_ = rhs.operation_;
    children_ = std::move(rhs.children_);
    rhs.children_.clear();
    result_ = {};
    isCleared_ = true;
  }
  return *this;
}

void Gene::run(const Args& args) {
  GeneLog(DEBUG) << writeShort() << " Running...";
  assert(args.size() == nArgs());
  Operation::Args<std::any> typeArgs;
  for(const auto arg: args) {
    assert(!arg->isCleared());
    typeArgs.push_back(arg->result_);
  }
  result_ = operation_->run(typeArgs);
  isCleared_ = false;
}

bool Gene::addChild(uint idx) {
  if (children_.size() >= nArgs())
    return false;
  children_.push_back(idx);
  return true;
}

const Gene::ChildrenRefs& Gene::children() const {
  return children_;
}

bool Gene::isCleared() const {
  return isCleared_;
}

uint Gene::nArgs() const {
  return operation_->nArgs();
}

void Gene::clear() {
  result_ = {};
  isCleared_ = true;
}

const std::any& Gene::result() const {
  return result_;
}

void Gene::assess(const Fitness& fitness) {
  GeneLog log(DEBUG);
  log << writeShort() << " Assessing... score: ";
  assert(!isCleared());
  //uint score = fitness->measure(result_);
  uint score = 0;
  log << score;
  setScore(score);
}

void Gene::writeObject(std::string &objectStr) const {
  objectStr += operation_->write() + ", children:[";
  for(const auto child: children_) {
    objectStr += std::to_string(child);
    objectStr += ",";
  }
  objectStr += "]";
}
void Gene::writeShortObject(std::string &objectStr) const {
  objectStr = "[" + objectStr + "]";
}

}
