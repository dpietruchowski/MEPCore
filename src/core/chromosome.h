#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "utils/types.h"
#include "utils/log.h"
#include "gene.h"
#include "object.h"
#include "operation/operation.h"
#include "genetic/operationset.h"

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
    {
        ChromosomeLog(DEBUG) << writeShort() << " Copy constructor";
    }
    Chromosome& operator=(const Chromosome& rhs)
    {
        if (&rhs != this) {
            Object::operator =(rhs);
            genes_ = rhs.genes_;
        }
        ChromosomeLog(DEBUG) << writeShort() << " Copy assignment";
        return *this;
    }
    Chromosome(Chromosome&& other): Object(std::move(other)),
        genes_(std::move(other.genes_))
    {
        ChromosomeLog(DEBUG) << writeShort() << " Move constructor";
    }
    Chromosome& operator=(Chromosome&& rhs)
    {
        if (&rhs != this) {
            Object::operator =(std::move(rhs));
            genes_ = std::move(rhs.genes_);
            rhs.genes_.clear();
        }
        ChromosomeLog(DEBUG) << writeShort() << " Move assignment";
        return *this;
    }

public /* interface */:
    void init(OperationSet<Type>& set, uint startId) {
        ChromosomeLog(DEBUG) << writeShort() << " Initialization...";
        Gene<Type>& gene = emplaceGene(startId, set.terminal());
        gene.setColor(color_);
        for(uint i = 1; i < genes_.capacity(); ++i) {
            Gene<Type>& gene = emplaceGene(i + startId, set.rand());
            gene.setColor(color_);
            UintRandom childRandom(0, i - 1);
            for(uint ic = 0; ic < gene.nArgs(); ++ic) {
                gene.addChild(childRandom());
            }
        }
    }

    void run(const Fitness<Type>* fitness)
    {
        ChromosomeLog(DEBUG) << *this << " Running...";
        for(uint i = genes_.size(); i > 0; --i) {
            uint idx = i - 1;
            if(genes_[idx].isCleared()) {
                runGene(idx);
            }
            genes_[idx].assess(fitness);
        }
        assess();
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

    const Gene<Type>& at(uint idx) const {
        assert(idx < genes_.size());
        return genes_.at(idx);
    }

    bool isFull() const {
        return genes_.size() >= genes_.capacity();
    }

    template<typename ...Args>
    Gene<Type>& emplaceGene(Args&&... args)
    {
        if(!isFull())
            genes_.emplace_back(args...);
        return genes_.back();
    }

    void mutate(const Gene<Type>& gene, uint cutPoint)
    {
        ChromosomeLog(DEBUG) << *this << " Copy mutation";
        if(!isFull() || cutPoint >= genes_.size())
            return;
        genes_[cutPoint] = gene;
    }

    void mutate(Gene<Type>&& gene, uint cutPoint)
    {
        ChromosomeLog(DEBUG) << *this << " Move mutation";
        if(!isFull() || cutPoint >= genes_.size())
            return;
        genes_[cutPoint] = std::move(gene);
    }

    /* The biggest parent must be eqaul or bigger than this child! */
    void crossover(const Parents<Type>& parents,
                   const std::set<uint>& cutPoints)
    {
        ChromosomeLog(DEBUG) << writeShort() << " Crossover, parents:";
        for(const auto& parent: parents) {
            ChromosomeLog(DEBUG) << *parent;
        }
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
            const Chromosome* parent =
                    _parents.lower_bound(genes_.capacity())->second;
            for(; idx < parent->size(); ++idx) {
                assert(idx < parent->genes_.size());
                addGene(parent->genes_[idx]);
            }
        }
        ChromosomeLog(DEBUG) << "Child: " << *this;
    }

    std::string writeLine() const
    {
        std::string chromosomeStr = writeShort();
        for(const auto& gene: genes_) {
            chromosomeStr += gene.writeShort();
        }
        return chromosomeStr;
    }

    void assess()
    {
        uint minScore = Object::MAX_SCORE;
        for(auto& gene: genes_) {
            if(gene.score() < minScore) {
                minScore = gene.score();
                bestGene_ = &gene;
            }
        }
        setScore(minScore);
    }


protected:
    void writeObject(std::string &objectStr) const
    {
        objectStr += "\n";
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
            GeneArgs<Type> args;
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
        Args<Type> args;
        for(auto child: currentGene.children()) {
            runGeneRecursive(child);
            args.push_back(&genes_[child]);
        }
        currentGene.run(args);
    }

private:
    Genes<Type> genes_;
    Gene<Type> *bestGene_;
};

} // namespace mep

#endif // CHROMOSOME_H
