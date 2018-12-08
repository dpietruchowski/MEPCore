#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <vector>

#include "function.h"
#include "terminal.h"
#include "gene.h"

int Int(const std::any& a) {
  return std::any_cast<int>(a);
}

std::any Add(const std::vector<std::any>& args) {
  return Int(args[0]) + Int(args[1]);
}

mep::Function add = {Add, "add", 2};
mep::Terminal ten = {10, "ten"};
mep::Terminal one = {1, "one"};

BOOST_AUTO_TEST_CASE( run_test )
{
  mep::Gene one_gene = {0, &one};
  mep::Gene ten_gene = {1, &ten};
  mep::Gene add_gene = {2, &add};

  BOOST_CHECK_NO_THROW(one_gene.run());
  BOOST_TEST( Int(one_gene.result()) == 1 );
  BOOST_CHECK_NO_THROW(ten_gene.run());
  BOOST_TEST( Int(ten_gene.result()) == 10 );
  BOOST_CHECK_NO_THROW(add_gene.run({&one_gene, &ten_gene}));
  BOOST_TEST( Int(add_gene.result()) == 11 );
}