#include "mepcoretest.h"

#include "modules.h"
#include "double.h"

#include <vector>
#include <iostream>
#include <limits>

std::vector<OperationPtr> createOperations() {
    std::vector<OperationPtr> operations;
    operations.emplace_back(new Terminal({10}, "ten"));
    operations.emplace_back(new Terminal({11}, "eleven"));
    operations.emplace_back(new Function(sub, "subtraction", 2));
    operations.emplace_back(new Function(add, "addition", 3));
    operations.emplace_back(new Function(mult, "multiplication", 3));
    operations.emplace_back(new Function(div, "division", 2));
    return operations;
}

void MEPCoreTest::smokeTest()
{
    auto operations = createOperations();

    std::vector<Gene> chromosome;
    chromosome.emplace_back(0, operations[0].get());
    for (int i = 1; i < 10; ++i) {
        uint idx = rand() % operations.size();
        chromosome.emplace_back(i, operations[idx].get());
    }

    int i = 0;
    for(auto& gene: chromosome) {
        for(uint k = 0; k < gene.nArgs(); ++k)
            gene.addChild(rand() % i);
        ++i;
    }

    for(const auto& gene: chromosome) {
        std::cout << gene.write() << std::endl;
    }
    for(auto& gene: chromosome) {
        std::vector<Gene*> args;
        for(auto childIdx: gene.children())
            args.push_back(&chromosome[childIdx]);
        gene.run(args);
    }
    i = 0;
    for(const auto& gene: chromosome) {
        std::cout << "[" << i << "] " <<
                     gene.result().value << std::endl;
        ++i;
    }

    QVERIFY2(true, "Failure");
}

MEPCoreTest::MEPCoreTest()
{

}

uint MAX_SCORE = std::numeric_limits<uint>::max();

void MEPCoreTest::compareCopies(const Gene& original, const Gene& copied) {
    QCOMPARE(copied.isCleared(), true);
    QCOMPARE(copied.children().size(), original.children().size());
    QCOMPARE(copied.nArgs(), original.nArgs());
    QCOMPARE(copied.result().value, Double().value);
    QCOMPARE(copied.id(), original.id());
    QCOMPARE(copied.score(), MAX_SCORE);
    uint i = 0;
    for(const auto &child: copied.children()) {
        QCOMPARE(child, original.children()[i]);
        ++i;
    }
}

void MEPCoreTest::compareMoved(const Gene& original,
                  const Gene& movedFrom, const Gene& movedTo) {
    QCOMPARE(movedTo.isCleared(), true);
    QCOMPARE(movedTo.children().size(), original.children().size());
    QCOMPARE(movedTo.nArgs(), original.nArgs());
    QCOMPARE(movedTo.result().value, Double().value);
    QCOMPARE(movedTo.id(), original.id());
    QCOMPARE(movedTo.score(), MAX_SCORE);
    uint i = 0;
    for(const auto &child: movedTo.children()) {
        QCOMPARE(child, original.children()[i]);
        ++i;
    }

    QCOMPARE(movedFrom.isCleared(), true);
    QCOMPARE(movedFrom.children().size(), (unsigned long)0);
    QCOMPARE(movedFrom.nArgs(), original.nArgs());
    QCOMPARE(movedFrom.result().value, Double().value);
    QCOMPARE(movedFrom.id(), original.id());
    QCOMPARE(movedFrom.score(), MAX_SCORE);
}

void MEPCoreTest::geneTerminalTest()
{
    auto operations = createOperations();
    // Copy
    Gene original(0, operations[0].get());
    Gene other(1, operations[1].get());
    Gene copied = other;
    Gene movedFrom(original);
    Gene moved = other;
    QCOMPARE(original.isCleared(), true);
    QCOMPARE(original.children().size(), (unsigned long)0);
    QCOMPARE(original.nArgs(), (uint)0);
    QCOMPARE(original.result().value, Double().value);
    QCOMPARE(original.id(), (uint)0);
    QCOMPARE(original.score(), MAX_SCORE);
    compareCopies(original, Gene(original));
    compareMoved(original, movedFrom, Gene(std::move(movedFrom)));
    // clear
    copied = other;
    movedFrom = original;
    //
    copied = original;
    compareCopies(original, copied);
    moved = std::move(movedFrom);
    compareMoved(original, movedFrom, moved);

    original.run();
    QCOMPARE(original.isCleared(), false);
    QCOMPARE(original.result().value, 10.0);
    compareCopies(original, Gene(original));
    compareMoved(original, movedFrom, Gene(std::move(movedFrom)));
    // clear
    copied = other;
    movedFrom = original;
    //
    copied = original;
    compareCopies(original, copied);
    moved = std::move(movedFrom);
    compareMoved(original, movedFrom, moved);

    original.clear();
    QCOMPARE(original.isCleared(), true);
    QCOMPARE(original.result().value, 0.0);
    compareCopies(original, Gene(original));
    compareMoved(original, movedFrom, Gene(std::move(movedFrom)));
    // clear
    copied = other;
    movedFrom = original;
    //
    copied = original;
    compareCopies(original, copied);
    moved = std::move(movedFrom);
    compareMoved(original, movedFrom, moved);
}

void MEPCoreTest::geneFunctionTest()
{
    auto operations = createOperations();
    // Copy
    std::vector<Gene> terminals;
    terminals.emplace_back(0, operations[0].get());
    terminals.emplace_back(1, operations[1].get());
    std::vector<Gene*> args;
    terminals[0].run();
    terminals[1].run();
    args.push_back(&terminals[0]);
    args.push_back(&terminals[1]);
    Gene original(2, operations[2].get());
    Gene other(3, operations[3].get());
    Gene copied = other;
    Gene movedFrom(original);
    Gene moved = other;
    QCOMPARE(original.isCleared(), true);
    QCOMPARE(original.children().size(), (unsigned long)0);
    QCOMPARE(original.nArgs(), (uint)2);
    QCOMPARE(original.result().value, Double().value);
    QCOMPARE(original.id(), (uint)2);
    QCOMPARE(original.score(), MAX_SCORE);
    compareCopies(original, Gene(original));
    compareMoved(original, movedFrom, Gene(std::move(movedFrom)));
    // clear
    copied = other;
    movedFrom = original;
    //
    copied = original;
    compareCopies(original, copied);
    moved = std::move(movedFrom);
    compareMoved(original, movedFrom, moved);

    original.run(args);
    QCOMPARE(original.isCleared(), false);
    QCOMPARE(original.result().value, -1.0);
    compareCopies(original, Gene(original));
    compareMoved(original, movedFrom, Gene(std::move(movedFrom)));
    // clear
    copied = other;
    movedFrom = original;
    //
    copied = original;
    compareCopies(original, copied);
    moved = std::move(movedFrom);
    compareMoved(original, movedFrom, moved);

    original.clear();
    QCOMPARE(original.isCleared(), true);
    QCOMPARE(original.result().value, 0.0);
    compareCopies(original, Gene(original));
    compareMoved(original, movedFrom, Gene(std::move(movedFrom)));
    // clear
    copied = other;
    movedFrom = original;
    //
    copied = original;
    compareCopies(original, copied);
    moved = std::move(movedFrom);
    compareMoved(original, movedFrom, moved);
}

Chromosome createChromosome(std::vector<OperationPtr>& operations,
                            uint startIdx, uint size,
                            Color::Code code = Color::DEFAULT)
{
    Chromosome chromosome(startIdx, size);
    std::cout << "Create Chromosome()" << std::endl;
    for(uint i = startIdx; i < startIdx + size; ++i) {
        Gene& g = chromosome.emplaceGene(i, operations[(i - startIdx)%6].get());
        g.setColor(code);
        for(uint ic = 0; ic < g.nArgs(); ++ic) {
            g.addChild(rand() % (i - startIdx));
        }
    }

    return chromosome;
}

void MEPCoreTest::compareChromosome(const Chromosome& chromosome,
                       const Chromosome& copy) {
    QCOMPARE(copy.id(), chromosome.id());
    QCOMPARE(copy.size(), chromosome.size());
    QCOMPARE(copy.score(), chromosome.score());
    QCOMPARE(copy.writeLine(), chromosome.writeLine());
}

void MEPCoreTest::compareChromosomeMoved(const Chromosome& chromosome,
                            const Chromosome& moved,
                            const Chromosome& movedFrom) {
    QCOMPARE(moved.id(), chromosome.id());
    QCOMPARE(moved.size(), chromosome.size());
    QCOMPARE(moved.score(), chromosome.score());
    QCOMPARE(moved.writeLine(), chromosome.writeLine());
    QCOMPARE(movedFrom.writeLine(), chromosome.writeShort());
    QCOMPARE(movedFrom.size(), (uint)0);
}

void MEPCoreTest::chromosomeConstructorTest()
{
    auto operations = createOperations();
    Chromosome chromosome = createChromosome(operations, 0, 0);
    QCOMPARE(chromosome.id(), (uint)0);
    QCOMPARE(chromosome.size(), (uint)0);
    QCOMPARE(chromosome.score(), MAX_SCORE);

    Chromosome copyWithoutGenes = chromosome;
    compareChromosome(chromosome, copyWithoutGenes);

    Chromosome copyWithoutGenes2(0, 0);
    copyWithoutGenes2 = chromosome;
    compareChromosome(chromosome, copyWithoutGenes2);

    chromosome = createChromosome(operations, 0, 5);

    Chromosome copy = chromosome;
    compareChromosome(chromosome, copy);

    Chromosome copy2(0, 0);
    copy2 = chromosome;
    compareChromosome(chromosome, copy2);

    Chromosome moved = std::move(copy);
    compareChromosomeMoved(chromosome, moved, copy);
    Chromosome moved2(0, 0);
    moved2 = std::move(copy2);
    compareChromosomeMoved(chromosome, moved2, copy2);
}
void MEPCoreTest::chromosomeCrossoverTest(const std::vector<Chromosome*>& parents,
                                          std::set<uint> cutPoints,
                                          std::string expected)
{
    Chromosome child(100, 10);
    child.crossover(parents, cutPoints);
    std::cout << child << std::endl;
    QCOMPARE(child.writeLine(), expected);

}

void MEPCoreTest::chromosomeCrossoverTest()
{
    auto operations = createOperations();
    Chromosome chromosome = createChromosome(operations, 0, 10);
    Chromosome parent1 = createChromosome(operations, 10, 5, Color::RED);
    Chromosome parent2 = createChromosome(operations, 15, 7, Color::GREEN);
    Chromosome parent3 = createChromosome(operations, 22, 10, Color::BLUE);
    std::cout << chromosome << std::endl;
    std::cout << parent1 << std::endl;
    std::cout << parent2 << std::endl;
    std::cout << parent3 << std::endl;

    std::vector<Chromosome*> parents;
    parents.push_back(&parent1);
    parents.push_back(&parent2);
    parents.push_back(&parent3);
        // out of bound 1
    chromosomeCrossoverTest(parents, { 2, 4, 6, 11 },
        "{100}[10 ][11 ][17 ][18 ][26 ][27 ][28 ][29 ][30 ][31 ]");
    chromosomeCrossoverTest(parents, { 2, 4, 6, 20 },
        "{100}[10 ][11 ][17 ][18 ][26 ][27 ][28 ][29 ][30 ][31 ]");
    chromosomeCrossoverTest(parents, { 2, 4, 6, 10 },
        "{100}[10 ][11 ][17 ][18 ][26 ][27 ][28 ][29 ][30 ][31 ]");
    chromosomeCrossoverTest(parents, { 2, 4, 6, 9 },
        "{100}[10 ][11 ][17 ][18 ][26 ][27 ][28 ][29 ][30 ][31 ]");
    chromosomeCrossoverTest(parents, { 0, 2, 4, 6, 9 },
        "{100}[15 ][16 ][24 ][25 ][19 ][20 ][28 ][29 ][30 ][31 ]");
    chromosomeCrossoverTest(parents, { 1, 2, 3, 4, 5 },
        "{100}[10 ][16 ][24 ][13 ][19 ][27 ][28 ][29 ][30 ][31 ]");
    chromosomeCrossoverTest(parents, { 5 },
        "{100}[10 ][11 ][12 ][13 ][14 ][27 ][28 ][29 ][30 ][31 ]");
    chromosomeCrossoverTest(parents, { 3, 7 },
        "{100}[10 ][11 ][12 ][18 ][19 ][20 ][21 ][29 ][30 ][31 ]");
    chromosomeCrossoverTest(parents, { 3, 8 },
                            "{100}[10 ][11 ][12 ][25 ][26 ][27 ][28 ][29 ][30 ][31 ]");
}

void MEPCoreTest::chromosomeMutationTest()
{
    auto operations = createOperations();
    Chromosome chromosome = createChromosome(operations, 0, 10);

    Gene gene(100, operations[0].get());
    chromosome.mutate(gene, 5);
    std::cout << chromosome << std::endl;
    QCOMPARE(chromosome.writeLine(),
        std::string("{0  }[0  ][1  ][2  ][3  ][4  ][100][6  ][7  ][8  ][9  ]"));
    Gene gene2(101, operations[2].get());
    chromosome.mutate(std::move(gene2), 5);
    std::cout << chromosome << std::endl;
    QCOMPARE(chromosome.writeLine(),
        std::string("{0  }[0  ][1  ][2  ][3  ][4  ][101][6  ][7  ][8  ][9  ]"));
}

void MEPCoreTest::chromosomeRunTest()
{
    auto operations = createOperations();
    Chromosome chromosome = createChromosome(operations, 0, 10);
    std::cout << chromosome << std::endl;
    chromosome.run();
}

