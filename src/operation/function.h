#ifndef MEP_CORE_FUNCTION_H
#define MEP_CORE_FUNCTION_H

#include "utils/types.h"
#include "operation.h"

namespace mep {

template<typename Type>
class Function final: public Operation<Type>
{
public:
    Function(FunctionPtr<Type> function, const std::string& name, uint nArgs):
        Operation<Type>(name, nArgs), function_(function)
    { }

private /* methods */:
    Type runOperation(const Args<Type>& args) const override {
        return function_(args);
    }
    void write(std::string &objectStr) const override {
        objectStr += "Function";
    }
private:
    FunctionPtr<Type> function_;
};

}
#endif // MEP_CORE_FUNCTION_H
