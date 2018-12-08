#ifndef MEP_CORE_GENE_H
#define MEP_CORE_GENE_H

#include "utils/log.h"
#include "object.h"
#include "operation.h"

#include <string>
#include <unordered_set>
#include <vector>
#include <functional>

namespace mep {

class Fitness;

class Gene: public Object
{
public:
    using Args = std::vector<Gene*>;
    using ChildrenRefs = std::vector<uint>;

    Gene(uint id, Operation* operation);
    Gene(const Gene& other);
    Gene& operator=(const Gene& rhs);
    Gene(Gene&& other);
    Gene& operator=(Gene&& rhs);

public:
    void mutate(Operation* operation);
    void mutate(const ChildrenRefs& children);

    void run(const Args& args = {});
    bool addChild(uint idx);
    const ChildrenRefs& children() const;

    bool isCleared() const;
    uint nArgs() const;
    void clear();
    const std::any& result() const;
    void assess(const Fitness& fitness);

protected:
    void writeObject(std::string &objectStr) const override;
    void writeShortObject(std::string &objectStr) const;

private:
    Operation* operation_;
    ChildrenRefs children_;
    std::any result_;
    bool isCleared_;
};

} // namespace mep

#endif // MEP_CORE_GENE_H
