#ifndef MEP_CORE_TERMINAL_H
#define MEP_CORE_TERMINAL_H

#include "utils/types.h"
#include "operation.h"

namespace mep {

template<typename Type>
class Terminal: public Operation<Type>
{
public:
    Terminal(const Type& terminal,const std::string& name):
        Operation<Type>(name, 0), terminal_(terminal)
    { }

private /* methods */:
    Type runOperation(const Args<Type>& /* args */) const override {
        return terminal_;
    }
    void write(std::string &objectStr) const override {
        objectStr += "Terminal";
    }
private:
    Type terminal_;
};

}

#endif // MEP_CORE_TERMINAL_H
