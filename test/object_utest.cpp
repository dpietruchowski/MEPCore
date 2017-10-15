#include <QString>
#include <QtTest>

#include "types.h"
#include "object.h"
#include "gene.h"
#include "operation/operation.h"
#include "operation/terminal.h"
#include "operation/function.h"

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

using Object = mep::Object;
using Gene = mep::Gene<Double>;
using Terminal = mep::Terminal<Double>;
using Function = mep::Function<Double>;
using OperationPtr = mep::OperationPtr<Double>;

class MEPCoreTest : public QObject
{
    Q_OBJECT

public:
    MEPCoreTest();

private Q_SLOTS:
    void simpleTest();
  //  void operatorAndConstructorTests();
};

MEPCoreTest::MEPCoreTest()
{
}

void MEPCoreTest::simpleTest()
{
    std::vector<OperationPtr> operations;
    operations.emplace_back(new Terminal({10}, "ten"));
    operations.emplace_back(new Terminal({1}, "one"));
    operations.emplace_back(new Terminal({5}, "five"));
    operations.emplace_back(new Function(add, "addition", 3));
    operations.emplace_back(new Function(sub, "subtraction", 2));
    operations.emplace_back(new Function(mult, "multiplication", 3));
    operations.emplace_back(new Function(div, "division", 2));

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
    double product = 1;
    for(const auto arg: args)
        product *= **arg;
    return {product};
}
Double div(const std::vector<Double*>& args) {
    return {**args[0] / **args[1]};
}

QTEST_APPLESS_MAIN(MEPCoreTest)

#include "object_utest.moc"
