#include <iostream>

#include "gene/function.h"
#include "gene/terminal.h"
#include "gene/gene.h"

using namespace std;

int add(const vector<int*>& args) {
  return *args[0] + *args[1];
}

struct MepModel {
  using Type = int;
  static uint assess(const int& result) {
    return result;
  }
  static uint clear(int& result) {
    result = 0;
  }
  static void show(int result) {
    cout << "result: " << result << endl;
  }
  mep::Operation<int>* operation;
};

int main() {
  mep::Terminal<int> term1{10, "ten"};
  cout << term1.run({}) << endl;
  cout << term1.write() << endl;

  mep::Terminal<int> term2{45, "ten"};
  cout << term2.run({}) << endl;
  cout << term2.write() << endl;

  mep::Function<int> func{&add, "add", 2};
  cout << func.write() << endl;

  mep::Gene gene1{MepModel{&term1}};
  mep::Gene gene2{MepModel{&term2}};

  mep::Gene gene3{MepModel{&func}};

  gene1.run({});
  gene2.run({});
  std::vector<mep::Gene*> args = {&gene1, &gene2};
  gene3.run(args);

  cout << gene1.assess() << endl;
  cout << gene2.assess() << endl;
  cout << gene3.assess() << endl;

  gene1.show();
  gene1.clear();
  gene1.show();

  cout << gene1.nArgs() << endl;
}