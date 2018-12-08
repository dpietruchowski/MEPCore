#pragma once

#include "operation.h"

namespace mep {

class Terminal: public Operation
{
public:
    Terminal(const std::any& terminal, const std::string& name);

private:
    std::any runOperation(const Args<std::any>& args) const override;
//    std::any runOperation(const RefArgs<std::any>& args) const override;
    void write(std::string& objectStr) const override;

private:
    std::any terminal_;
};

}
