#ifndef MEPCORETEST_H
#define MEPCORETEST_H

#include <QString>
#include <QtTest>
#include "modules.h"

class MEPCoreTest: public QObject
{
    Q_OBJECT

public:
    MEPCoreTest();

private /* methods */:
    void chromosomeCrossoverTest(const std::vector<Chromosome*>& parents,
                               std::set<uint> cutPoints,
                               std::string expected);
    void compareCopies(const Gene& original, const Gene& copied);
    void compareMoved(const Gene& original,
                      const Gene& movedFrom, const Gene& movedTo);
    void compareChromosome(const Chromosome& chromosome,
                           const Chromosome& copy);
    void compareChromosomeMoved(const Chromosome& chromosome,
                                const Chromosome& moved,
                                const Chromosome& movedFrom);
private Q_SLOTS:
    void smokeTest();
    void geneTerminalTest();
    void geneFunctionTest();
    void chromosomeConstructorTest();
    void chromosomeCrossoverTest();
    void chromosomeMutationTest();
    void chromosomeRunTest();
};

#endif // MEPCORETEST_H
