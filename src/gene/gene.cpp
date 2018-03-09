#include "gene.h"

namespace mep {

uint Gene::assess() const {
  return concept_->assess();
}

void Gene::run(const std::vector<Gene*>& args) {
  std::vector<Concept*> concept_args;
  concept_args.reserve(args.size());
  for(const auto gene: args) {
    concept_args.push_back(gene->concept_.get());
  }
  concept_->run(concept_args);
  isCleared_ = false;
}

bool Gene::addChild(uint idx) {
  if (children_.size() >= nArgs())
    return false;
  children_.push_back(idx);
  return true;
}
    
const std::vector<uint>& Gene::children() const {
  return children_;
}
    
bool Gene::isCleared() const { 
  return isCleared_; 
}
    
uint Gene::nArgs() const { 
  return concept_->nArgs(); 
}
    
void Gene::clear() {
    concept_->clear();
    isCleared_ = true;
}

void Gene::show() const {
    concept_->show();
}

} // namespace mep