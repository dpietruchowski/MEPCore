#include "mepcoretest.h"

#include "modules.h"
#include "double.h"
#include "utils/log.h"

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

void MEPCoreTest::geneMutationTest()
{
    auto operations = createOperations();
    Gene gene(20, operations[3].get());
    mep::IdxArgs geneArgs = { 1, 2, 3 };
    gene.addChild(geneArgs[0]);
    gene.addChild(geneArgs[1]);
    gene.addChild(geneArgs[2]);
    mep::IdxArgs args = { 5, 6, 2 };
    Gene argsMutated(gene, args);
    Gene attrMutated(gene, operations[2].get());

    QCOMPARE(argsMutated.children().size(), (size_t)3);
    uint i = 0;
    for(const auto child: argsMutated.children()) {
        QCOMPARE(child, args[i]);
        ++i;
    }

    QCOMPARE(attrMutated.children().size(), (size_t)2);
    i = 0;
    for(const auto child: attrMutated.children()) {
        QCOMPARE(child, geneArgs[i]);
        ++i;
    }
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
    Double reference = { 5 };
    DoubleFitness fitness(reference);
    auto operations = createOperations();
    Chromosome chromosome = createChromosome(operations, 0, 10);
    std::cout << chromosome << std::endl;
    chromosome.run(&fitness);
    std::cout << chromosome.write() << std::endl;
    QCOMPARE(chromosome.score(), (uint)4);
}

void MEPCoreTest::randomTest()
{
    Random rand;
    std::map<uint, uint> hist;
    for(int i = 1; i < 20; ++i) {
        for(int k = 0; k < 2; ++k)
            ++hist[rand(i-1)];
    }
    for (auto p : hist) {
        std::cout << p.first << " : "  << std::to_string(p.second) << std::string(p.second, '*') << '\n';
    }
}

struct Int {
    Int(int val): value(val) { std::cout << "Int constructor" << std::endl; }
    Int(const Int& val) { std::cout << "Copy" << std::endl; }
    Int(Int&& val) { std::cout << "Copy" << std::endl; }
    Int& operator=(const Int& val) { std::cout << "Copy" << std::endl; }
    Int& operator=(Int&& val) { std::cout << "Copy" << std::endl; }
    ~Int() { std::cout << "Int destructor" << std::endl; }
    int value;
};

void MEPCoreTest::ptrSetTest()
{
    std::map<Int*, int> ptrs;
    for(int i = 0; i < 3; ++i) {
        ptrs[new Int(i)] = 0;
    }
    PtrSet<Int> set;
    auto iter = ptrs.begin();
    set.registerPtr(1.0/3, (iter++)->first);
    set.registerPtr(1.0/3, (iter++)->first);
    set.registerPtr(1.0/3, (iter++)->first);

    for(int i = 0; i < 2000; ++i) {
        ++ptrs[set.rand()];
    }

    for (auto p : ptrs) {
        std::cout << p.first << " : "  << std::to_string(p.second)
                  << std::string(p.second/20, '*') << '\n';
    }
}

void MEPCoreTest::operationSetTest()
{
    OperationSet set(Double{10}, "ten");
    Function* fun = new Function(div, "division", 2);
    set.registerPtr(0.1, Double{10}, "ten");
    set.registerPtr(0.01, Double{20}, "twenty");
    set.registerPtr(0.01, add, "addition", 3);
    set.registerPtr(0.58, sub, "subtraction", 2);
    set.registerPtr(0.3, fun);

    std::map<double, int> ptrs;
    for(int i = 0; i < 2000; ++i) {
        Operation* op = set.rand();
        std::vector<Double> _args;
        std::vector<Double*> args;
        for(uint i = 0; i < op->nArgs(); ++i) {
            _args.push_back({(i+1)*10.0});
            args.push_back(&_args.back());
        }
        Double result = op->run(args);
        ++ptrs[std::floor(result.value)];
    }

    for (auto p : ptrs) {
        std::cout << p.first << " : "  << std::to_string(p.second)
                  << std::string(p.second/20, '*') << '\n';
    }
}

void selectionHist(Selection *selection) {
    std::map<uint, uint> hist;
    int maxIter = 200;
    for(int i = 0; i < maxIter; ++i) {
        ++hist[selection->select()];
    }
    for (auto p : hist) {
        std::cout << p.first << " : "  << std::to_string(p.second)
                  << std::string((p.second*100)/maxIter, '*') << '\n';
    }
}

void MEPCoreTest::TournamentTest()
{
    TournamentSelection selection(4);
    selection.add(0, 100, 0); // 0.0111
    selection.add(1, 200, 1); // 0.0222
    selection.add(2, 1000, 2);// 0.1111
    selection.add(3, 2000, 3);// 0.2222
    selection.add(4, 3000, 4);// 0.3333
    selection.add(5, 5000, 5);// 0.5555
    selection.add(6, 9000, 6);// 1

    selectionHist(&selection);

    selection.add(7, 9000, 7);// 1
    selection.select();
}

void MEPCoreTest::RouletteTest()
{
    RankRouletteSelection rankSelection{};
    rankSelection.add(0, 100, 0); // 0.25
    rankSelection.add(1, 200, 1); // 0.21
    rankSelection.add(2, 1000, 2);// 0.18
    rankSelection.add(3, 2000, 3);// 0.14
    rankSelection.add(4, 3000, 4);// 0.11
    rankSelection.add(5, 5000, 5);// 0.07
    rankSelection.add(6, 9000, 6);// 0.04

    selectionHist(&rankSelection);

    FitnessRouletteSelection fitnessSelection{};
    fitnessSelection.add(0, 100, 0); // 0.21
    fitnessSelection.add(1, 200, 1); // 0.21
    fitnessSelection.add(2, 1000, 2);// 0.18
    fitnessSelection.add(3, 2000, 3);// 0.16
    fitnessSelection.add(4, 3000, 4);// 0.14
    fitnessSelection.add(5, 5000, 5);// 0.09
    fitnessSelection.add(6, 9000, 6);// ~0.0

    selectionHist(&fitnessSelection);

    fitnessSelection.add(7, 1, 7);

    selectionHist(&fitnessSelection);
}

OperationSet createOperationSet() {
    OperationSet set(Double{100}, "one hundred");
    Function* fun = new Function(div, "division", 2);
    set.registerPtr(0.15, Double{10}, "ten");
    set.registerPtr(0.1, Double{20}, "twenty");
    set.registerPtr(0.3, add, "addition", 3);
    set.registerPtr(0.1, sub, "subtraction", 2);
    set.registerPtr(0.3, mult, "multiplication", 3);
    set.registerPtr(0.05, fun);

    return set;
}

void MEPCoreTest::mutationTest()
{
    auto set = createOperationSet();
    DoubleFitness fitness(Double{0});

    Chromosome individual(0, 10);
    individual.init(set, 0);
    individual.run(&fitness);
    std::cout << individual << std::endl;
    std::cout << individual.write() << std::endl;

    Chromosome child(individual);

    child.setColor(Color::BLUE);
    ArgumentMutation argMutation;
    argMutation(set, child);
    std::cout << child << std::endl;
    std::cout << child.write() << std::endl;

    child.setColor(Color::RED);
    AttributeMutation attMutation;
    attMutation(set, child);
    std::cout << child << std::endl;
    std::cout << child.write() << std::endl;

    child.setColor(Color::GREEN);
    CombinedMutation comMutation;
    comMutation(set, child);
    std::cout << child << std::endl;
    std::cout << child.write() << std::endl;

    for(int i = 0; i < 10; ++i) {
        argMutation(set, child);
    }
    for(int i = 0; i < 10; ++i) {
        comMutation(set, child);
    }
    for(int i = 0; i < 10; ++i) {
        attMutation(set, child);
    }
}

void MEPCoreTest::crossoverTest()
{
    auto set = createOperationSet();
    DoubleFitness fitness(Double{0});

    Chromosome parent1(0, 10);
    parent1.init(set, 0);
    std::cout << parent1 << std::endl;
    std::cout << parent1.write() << std::endl;
    Chromosome parent2(10, 10);
    parent2.init(set, 10);
    std::cout << parent2 << std::endl;
    std::cout << parent2.write() << std::endl;

    OnePointCrossover opCrossover;
    Chromosome child1 = opCrossover(parent1, parent2);
    std::cout << child1 << std::endl;
    std::cout << child1.write() << std::endl;

    TwoPointCrossover tpCrossover;
    Chromosome child2 = tpCrossover(parent1, parent2);
    std::cout << child2 << std::endl;
    std::cout << child2.write() << std::endl;

    UniformCrossover uniCrossover;
    Chromosome child3 = uniCrossover(parent1, parent2);
    std::cout << child3 << std::endl;
    std::cout << child3.write() << std::endl;

    for(int i = 0; i < 10; ++i) {
        Chromosome child = opCrossover(parent1, parent2);
    }
    for(int i = 0; i < 10; ++i) {
        Chromosome child = tpCrossover(parent1, parent2);
    }
    for(int i = 0; i < 10; ++i) {
        Chromosome child = uniCrossover(parent1, parent2);
    }
}

void MEPCoreTest::populationTest()
{
    mep::Log::MAX_LEVEL = mep::LogLevel::DEBUG;
    Fitness* fitness = new DoubleFitness(Double{0});
    Selection* selection = new RankRouletteSelection();
    Terminal terminal(Double{10}, "ten");
    Population population(10, terminal, selection, fitness);
    population.operationSet.registerPtr(
                0.05, new Terminal(Double{20}, "twenty"));
    population.operationSet.registerPtr(
                0.1, new Function(sub, "subtraction", 2));
    population.operationSet.registerPtr(
                0.1, new Function(add, "addition", 3));
    population.operationSet.registerPtr(
                0.05, new Function(mult, "multiplication", 3));
    population.operationSet.registerPtr(
                0.7, new Function(div, "division", 2));
    population.init(10);
    population.crossoverSet.registerPtr(0.4, new OnePointCrossover());
    population.crossoverSet.registerPtr(0.4, new TwoPointCrossover());
    population.crossoverSet.registerPtr(0.2, new UniformCrossover());
    population.mutationSet.registerPtr(0.2, new ArgumentMutation());
    population.mutationSet.registerPtr(0.2, new AttributeMutation());
    population.mutationSet.registerPtr(0.6, new CombinedMutation());
    std::vector<uint> scores;
    for(int i = 0; i < 1000; ++i) {
        scores.push_back(population.bestScore());
        auto child = population.reproduce();
        population.add(std::move(child));
    }
    for(const auto score : scores)
        std::cout << score << " ";
    std::cout << endl;
}

using Log = mep::Log;
using GeneLog = mep::GeneLog;
using ChromosomeLog = mep::ChromosomeLog;
using PopulationLog = mep::PopulationLog;

void MEPCoreTest::logTest()
{
    using namespace mep;
    std::string name = "dfadsf";
    GeneLog(ERROR) << "Damian" << name;
    PopulationLog(ERROR) << name;
}

