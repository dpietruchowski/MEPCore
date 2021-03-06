#ifndef MEP_CORE_GENE_H
#define MEP_CORE_GENE_H

#include "utils/types.h"
#include "utils/log.h"
#include "object.h"
#include "operation/operation.h"

#include <assert.h>
#include <string>
#include <unordered_set>
#include <vector>
#include <iostream>

namespace mep {

template<typename Type>
class Gene: public Object
{
public /* constructors and operators */:
    Gene(uint id, Operation<Type>* operation): Object(id),
        operation_(operation), children_{}, result_(), isCleared_(true)
    {
        children_.reserve(operation->nArgs());
    }
    Gene(const Gene& other): Object(other),
        operation_(other.operation_), children_(other.children_), result_(),
        isCleared_(true)
    {
        GeneLog(CONSTRUCTORS) << writeShort() << " Copy constructor";
    }
    Gene& operator=(const Gene& rhs) {
        if (&rhs != this) {
            Object::operator =(rhs);
            operation_ = rhs.operation_;
            children_ = rhs.children_;
            result_ = Type();
            isCleared_ = true;
        }
        GeneLog(CONSTRUCTORS) << writeShort() << " Copy assignment";
        return *this;

    }
    Gene(Gene&& other): Object(std::move(other)),
        operation_(other.operation_), children_(std::move(other.children_)),
        result_(), isCleared_(true) {
        GeneLog(CONSTRUCTORS) << writeShort() << " Move constructor";
        other.children_.clear();
    }
    Gene& operator=(Gene&& rhs) {
        if (&rhs != this) {
            Object::operator =(std::move(rhs));
            operation_ = rhs.operation_;
            children_ = std::move(rhs.children_);
            rhs.children_.clear();
            result_ = Type();
            isCleared_ = true;
        }
        GeneLog(CONSTRUCTORS) << writeShort() << " Move assignment";
        return *this;
    }
    /// Mutation Constructors
    Gene(const Gene& other, Operation<Type>* operation): Object(other),
        operation_(operation), children_(other.children_), result_(),
        isCleared_(true)
    {
        while(children_.size() > operation_->nArgs()) {
            children_.pop_back();
        }
        GeneLog(DEBUG) << writeShort() << "Attr Mutation constructor";
    }
    Gene(const Gene& other, const IdxArgs& children): Object(other),
        operation_(other.operation_), children_(children), result_(),
        isCleared_(true)
    {
        GeneLog(DEBUG) << writeShort() << "Args Mutation constructor";
    }
public /* methods */:
    void run(const GeneArgs<Type>& args = {}) {
        GeneLog(DEBUG) << writeShort() << " Running...";
        assert(args.size() == nArgs());
        Args<Type> typeArgs;
        for(const auto arg: args) {
            assert(!arg->isCleared());
            typeArgs.push_back(&arg->result_);
        }
        result_ = operation_->run(typeArgs);
        isCleared_ = false;
    }
    bool addChild(uint idx) {
        if (children_.size() >= nArgs())
            return false;
        children_.push_back(idx);
        return true;
    }

    const IdxArgs& children() const {
        return children_;
    }

    bool isCleared() const { return isCleared_; }
    uint nArgs() const { return operation_->nArgs(); }
    void clear() {
        result_.clear();
        isCleared_ = true;
    }
    const Type& result() const {
        return result_;
    }
    void assess(const Fitness<Type>* fitness) {
        GeneLog log(DEBUG);
        log << writeShort() << " Assessing... score: ";
        assert(!isCleared());
        uint score = fitness->measure(result_);
        log << score;
        setScore(score);
    }

protected:
    virtual void writeObject(std::string &objectStr) const override {
        objectStr += operation_->write() + ", children: ";
        for(const auto child: children_) {
            objectStr += std::to_string(child);
            objectStr += ", ";
        }
    }
    void writeShortObject(std::string &objectStr) const {
        objectStr = "[" + objectStr + "]";
    }

private:
    Operation<Type>* operation_;
    IdxArgs children_;
    Type result_;
    bool isCleared_;
};

} // namespace mep

#endif // MEP_CORE_GENE_H
