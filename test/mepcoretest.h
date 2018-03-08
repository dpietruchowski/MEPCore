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
    void geneMutationTest();
    void chromosomeConstructorTest();
    void chromosomeCrossoverTest();
    void chromosomeMutationTest();
    void chromosomeRunTest();
    void randomTest();
    void ptrSetTest();
    void operationSetTest();
    void TournamentTest();
    void RouletteTest();
    void mutationTest();
    void crossoverTest();
    void populationTest();
    void logTest();
};

#endif // MEPCORETEST_H
