#ifndef FUNCTIONGENE_H
#define FUNCTIONGENE_H

#include "types.h"
#include "gene.h"

namespace mep {

template<typename Type>
class FunctionGene final: public Gene<Type>
{
public:
    FunctionGene(uint id, const Function<Type>& function):
        Gene<Type>(id, function.nArgs), function_(function.ptr),
        name_(function.name) {
    }
    GenePtr<Type> clone() const override {
        return GenePtr<Type> (new FunctionGene(*this));
    }
private /* methods */:
    FunctionGene(const FunctionGene& other):
        Gene<Type>(other), function_(other.function_) {

    }
    FunctionGene& operator=(const FunctionGene& rhs) {
        Gene<Type>::operator =(rhs);
        function_ = rhs.function_;
    }

    Type run(const std::vector<Type*>& args) const override {
        return function_(args);
    }
    void writeObject(std::string &objectStr) const override {
        Gene<Type>::writeObject(objectStr);
        objectStr += "FunctionGene, name: " + name_;
    }
private:
    FunctionPtr<Type> function_;
    std::string name_;
};

}

#endif // FUNCTIONGENE_H
