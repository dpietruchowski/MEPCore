#include <QString>
#include <QtTest>

#include "types.h"
#include "object.h"
#include "gene.h"
#include "terminalgene.h"
#include "functiongene.h"

#include <iostream>

struct Double {
    double value;
    const double& operator*() const {
        return value;
    }
    double& operator*() {
        return value;
    }

    Double clone() const {
        return {value};
    }
    void clear() {
        value = 0;
    }
};

Double add(const std::vector<Double*>& args);
Double sub(const std::vector<Double*>& args);
Double mult(const std::vector<Double*>& args);
Double div(const std::vector<Double*>& args);

using DoubleFunction = mep::Function<Double>;
DoubleFunction addf = {add, "addition", 5};
DoubleFunction subf = {sub, "subtraction", 2};
DoubleFunction multf = {mult, "multiplication", 5};
DoubleFunction divf = {div, "division", 2};

using Object = mep::Object;
using Gene = mep::Gene<Double>;
using TerminalGene = mep::TerminalGene<Double>;
using FunctionGene = mep::FunctionGene<Double>;
using GenePtr = mep::GenePtr<Double>;

class MEPCoreTest : public QObject
{
    Q_OBJECT

public:
    MEPCoreTest();

private Q_SLOTS:
    void testCase1();
};

MEPCoreTest::MEPCoreTest()
{
}

void MEPCoreTest::testCase1()
{
    std::vector<GenePtr> originals;
    originals.emplace_back(new TerminalGene(0, {1}));
    originals.emplace_back(new TerminalGene(1, {7.5}));
    originals.emplace_back(new TerminalGene(2, {10}));
    originals.emplace_back(new TerminalGene(3, {2.5}));
    originals.emplace_back(new TerminalGene(4, {20}));
    originals.emplace_back(new FunctionGene(5, addf));
    originals.emplace_back(new FunctionGene(6, subf));
    originals.emplace_back(new FunctionGene(7, multf));
    originals.emplace_back(new FunctionGene(8, divf));

    for(const auto& g : originals) {
        std::cout << g->write() << std::endl;
        g->assess();
    }
    std::vector<Gene*> args1;
    args1.push_back(originals[0].get());
    args1.push_back(originals[1].get());
    args1.push_back(originals[2].get());
    args1.push_back(originals[3].get());
    args1.push_back(originals[4].get());
    std::vector<Gene*> args2;
    args2.push_back(originals[1].get());
    args2.push_back(originals[3].get());
    std::vector<Gene*> args3;
    args3.push_back(originals[5].get());
    args3.push_back(originals[8].get());

    Gene* root = originals[6].get();
    for(auto t1: args1) {
        t1->run();
    }
    for(auto t2: args2) {
        t2->run();
    }
    args3[0]->run(args1);
    args3[1]->run(args2);
    root->run(args3);

    std::cout << "The result is " << *args3[0]->result() << std::endl;
    std::cout << "The result is " << *args3[1]->result() << std::endl;
    std::cout << "The result is " << *root->result() << std::endl;


    QVERIFY2(true, "Failure");
}


Double add(const std::vector<Double*>& args) {
    double sum = 0;
    for(const auto& arg: args)
        sum += **arg;
    return {sum};
}
Double sub(const std::vector<Double*>& args) {
    return {**args[0] - **args[1]};
}
Double mult(const std::vector<Double*>& args) {
    double product = 0;
    for(const auto arg: args)
        product *= **arg;
    return {product};
}
Double div(const std::vector<Double*>& args) {
    return {**args[0] / **args[1]};
}

QTEST_APPLESS_MAIN(MEPCoreTest)

#include "unit_test.moc"
