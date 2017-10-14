#ifndef TERMINALGENE_H
#define TERMINALGENE_H

#include "types.h"
#include "gene.h"

namespace mep {

template<typename Type>
class TerminalGene: public Gene<Type>
{
public:
    TerminalGene(uint id, const Type& terminal):
        Gene<Type>(id, 0), terminal_(terminal.clone()) {

    }

    GenePtr<Type> clone() const override {
        return GenePtr<Type> (new TerminalGene(*this));
    }
protected /* methods */:
    TerminalGene(const TerminalGene& other):
        Gene<Type>(other), terminal_(other.terminal_.clone()) {

    }
    TerminalGene& operator=(const TerminalGene& rhs) {
        Gene<Type>::operator =(rhs);
        terminal_ = rhs.terminal_.clone();
    }

private /* methods */:
    Type run(const std::vector<Type*>& /* args */) const override {
        return terminal_.clone();
    }
    void writeObject(std::string &objectStr) const override {
        objectStr += "TerminalGene";
    }
private:
    Type terminal_;
};

}

#endif // TERMINALGENE_H
