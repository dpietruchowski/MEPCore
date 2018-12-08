#pragma once

#include <any>
#include <string>
#include <vector>

namespace mep {

class Operation {
public:
    template<typename Type>
    using RefArgs = std::vector<std::reference_wrapper<Type>>;

    template<typename Type>
    using Args = std::vector<Type>;

    Operation(const std::string& name, uint nArgs);
    virtual ~Operation() = default;

    std::any run(const Args<std::any>& args) const;
//    std::any run(const RefArgs<std::any>& args) const;
    std::string write() const;
    uint nArgs() const;

private:
    virtual std::any runOperation(const Args<std::any>& args) const = 0;
//    virtual std::any runOperation(const RefArgs<std::any>& args) const = 0;
    virtual void write(std::string& operationStr) const = 0;

private:
    std::string name_;
    uint nArgs_;
};

}
