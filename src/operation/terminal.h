#ifndef TERMINAL_H
#define TERMINAL_H

#include "types.h"
#include "operation.h"

namespace mep {

template<typename Type>
class Terminal: public Operation<Type>
{
public:
    Terminal(const Type& terminal,const std::string& name):
        Operation<Type>(name, 0), terminal_(terminal.clone())
    { }

private /* methods */:
    Type runOperation(const Args<Type>& /* args */) const override {
        return terminal_.clone();
    }
    void write(std::string &objectStr) const override {
        objectStr += "Terminal";
    }
private:
    Type terminal_;
};

}

#endif // TERMINAL_H
