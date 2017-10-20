#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "types.h"
#include "gene.h"
#include "object.h"
#include "operation/operation.h"

#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <utility>
#include <vector>

namespace mep {

template<typename Type>
class Chromosome: public Object
{
public /* constructors and operatos */:
    Chromosome(uint id, uint size): Object(id),
        genes_{}
    {
        genes_.reserve(size);
    }
    Chromosome(const Chromosome& other): Object(other),
        genes_(other.genes_)
    { std::cout << "Chromosome Copy Constructor: " << id() << std::endl; }
    Chromosome& operator=(const Chromosome& rhs)
    {
        if (&rhs != this) {
            Object::operator =(rhs);
            genes_ = rhs.genes_;
        }
        std::cout << "Chromosome Copy Assignment: " << writeShort() << std::endl;
        return *this;
    }
    Chromosome(Chromosome&& other): Object(std::move(other)),
        genes_(std::move(other.genes_))
    { std::cout << "Chromosome Move Constructor: " << writeShort() << std::endl; }
    Chromosome& operator=(Chromosome&& rhs)
    {
        if (&rhs != this) {
            Object::operator =(std::move(rhs));
            genes_ = std::move(rhs.genes_);
            rhs.genes_.clear();
        }
        std::cout << "Chromosome Move Assignment: " << writeShort() << std::endl;
        return *this;
    }

public /* interface */:
    void run(/* const Fitness* */)
    {
        for(uint i = genes_.size(); i > 0; --i) {
            uint idx = i - 1;
            if(genes_[idx].isCleared()) {
                runGene(idx);
            }
        }
    }

public /* methods */:
    friend std::ostream& operator<<(std::ostream &os,
                                    const Chromosome<Type>& chromosome)
    {
        operator <<(os, static_cast<const Object&>(chromosome));
        for(const auto& gene: chromosome.genes_) {
            os << gene;
        }
        return os;
    }

    uint size() const
    {
        return genes_.size();
    }

    bool isFull() const {
        return genes_.size() >= genes_.capacity();
    }

    bool addGene(const Gene<Type>& gene)
    {
        if(isFull())
            return false;
        genes_.emplace_back(gene);
        return true;
    }

    bool addGene(Gene<Type>&& gene)
    {
        if(isFull())
            return false;
        genes_.emplace_back(std::move(gene));
        return true;
    }

    Gene<Type>& emplaceGene(uint id, Operation<Type>* operation)
    {
        if(!isFull())
            genes_.emplace_back(id, operation);
        return genes_.back();
    }

    void mutate(const Gene<Type>& gene, uint cutPoint)
    {
        if(!isFull() || cutPoint >= genes_.size())
            return;
        genes_[cutPoint] = gene;
    }

    void mutate(Gene<Type>&& gene, uint cutPoint)
    {
        if(!isFull() || cutPoint >= genes_.size())
            return;
        genes_[cutPoint] = std::move(gene);
    }

    /* The biggest parent must be eqaul or bigger than this child! */
    void crossover(const std::vector<Chromosome*>& parents,
                   const std::set<uint>& cutPoints)
    {
        if(isFull())
            return;
        if(cutPoints.size() == 0 || parents.size() == 0)
            return;
        std::multimap<uint, Chromosome*> _parents;
        for(const auto parent: parents) {
            _parents.insert(std::make_pair(parent->size(), parent));
        }
        if(_parents.rbegin()->first < genes_.capacity())
            return;

        uint idx = 0;
        auto start = _parents.begin();
        auto stop = _parents.end();
        auto iter = start;
        for(auto cutPoint: cutPoints) {
            start = _parents.lower_bound(cutPoint);
            if (start == stop)
                break;
            if(iter == stop)
                iter = start;
            if(cutPoint > iter->first)
                iter = start;
            if(genes_.capacity() < cutPoint)
                cutPoint = genes_.capacity();
            const Chromosome* parent = iter->second;
            for(; idx < cutPoint; ++idx) {
                assert(idx < parent->genes_.size());
                addGene(parent->genes_[idx]);
            }
            ++iter;
        }
        if(!isFull()) {
            const Chromosome* parent = _parents.rbegin()->second;
            for(; idx < parent->size(); ++idx) {
                assert(idx < parent->genes_.size());
                addGene(parent->genes_[idx]);
            }
        }
    }

    std::string writeLine() const
    {
        std::string chromosomeStr = writeShort();
        for(const auto& gene: genes_) {
            chromosomeStr += gene.writeShort();
        }
        return chromosomeStr;
    }


protected:
    void writeObject(std::string &objectStr) const
    {
        for(const auto& gene: genes_) {
            objectStr += gene.write();
            objectStr += "\n";
        }
    }
    void writeShortObject(std::string &objectStr) const
    {
        objectStr = "{" + objectStr + "}";
    }
private /* methods */:
    void runGene(uint idx) {
        std::deque<uint> q = {idx};
        std::deque<uint> queue = {idx};
        while(!q.empty()) {
            uint current = q.front();
            q.pop_front();
            for(auto child: genes_[current].children()) {
                q.push_front(child);
                queue.push_front(child);
            }
        }
        while(!queue.empty()) {
            uint current = queue.front();
            queue.pop_front();
            Gene<Type> &currentGene = genes_[current];
            if (!currentGene.isCleared())
                continue;
            std::vector<Gene<Type>*> args;
            for(auto child: currentGene.children()) {
                args.push_back(&genes_[child]);
            }
            currentGene.run(args);
        }
    }

    void runGeneRecursive(uint current) {
        Gene<Type> &currentGene = genes_[current];
        if(!currentGene.isCleared())
            return;
        std::vector<Gene<Type>*> args;
        for(auto child: currentGene.children()) {
            runGeneRecursive(child);
            args.push_back(&genes_[child]);
        }
        currentGene.run(args);
    }

    uint assessObject(/* const Fitness& fitness */) const override
    {
        return 0;
    }

private:
    std::vector<Gene<Type>> genes_;
    Gene<Type> *bestGene_;
};

} // namespace mep

#endif // CHROMOSOME_H
