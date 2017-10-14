#ifndef GENE_H
#define GENE_H

#include "types.h"
#include "object.h"

#include <string>
#include <vector>
#include <assert.h>

namespace mep {

template<typename Type>
class Gene: public Object
{
public:
    Gene(uint id, uint nArgs): Object(id), nArgs_(nArgs), isCleared_(true) {}
    void run(const std::vector<Gene*>& args = {}) {
        assert(args.size() == nArgs_);
        std::vector<Type*> typeArgs;
        for(const auto arg: args) {
            assert(!arg->isCleared());
            typeArgs.push_back(&arg->result_);
        }
        result_ = run(typeArgs);
        isCleared_ = false;
    }
    bool isCleared() { return isCleared_; }
    uint nArgs() { return nArgs_; }
    void clear() {
        result_.clear();
        isCleared_ = true;
    }
    const Type& result() {
        return result_;
    }

    virtual GenePtr<Type> clone() const = 0;
protected:
    Gene(const Gene& other): Object(other),
        nArgs_(other.nArgs_), isCleared_(true){
    }
    Gene& operator=(const Gene& rhs) {
        Object::operator =(rhs);
        nArgs_ = rhs.nArgs_;
        isCleared_ = true;
    }
protected:
    virtual void writeObject(std::string &objectStr) const override {
        objectStr += "Number of arguments: " + std::to_string(nArgs_) + ", ";
    }

private /* methods */:
    uint assessObject(/* const Fitness& fitness */) const override {
        return 0;
    }
    virtual Type run(const std::vector<Type*>& args) const = 0;

private:
    uint nArgs_;
    bool isCleared_;
    Type result_;
};

} // namespace mep

#endif // GENE_H
