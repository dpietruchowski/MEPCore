#pragma once

#include <functional>
#include "operation.h"

namespace mep {

class Function final: public Operation
{
public:
    using Type = std::function<std::any(const Args<std::any>&)>;
    Function(const Type& type, const std::string& name, uint nArgs);

private:
    std::any runOperation(const Args<std::any>& args) const override;
//    std::any runOperation(const RefArgs<std::any>& args) const override;
    void write(std::string &objectStr) const override;

private:
    Type function_;
};

}
