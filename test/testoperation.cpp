#include <boost/test/included/unit_test.hpp>

#include <vector>

#include "function.h"
#include "terminal.h"

int Int(const std::any& a) {
  return std::any_cast<int>(a);
}

std::any Add(const std::vector<std::any>& args) {
  return Int(args[0]) + Int(args[1]);
}

BOOST_AUTO_TEST_CASE( run_test )
{
  mep::Terminal ten = {10, "ten"};
  mep::Terminal nine = {9, "nine"};
  mep::Function add = {Add, "add", 2};

  BOOST_TEST( Int(ten.run({})) == 10 );
  BOOST_TEST( Int(nine.run({})) == 9 );
  BOOST_TEST( Int(add.run({ ten.run({}), nine.run({}) })) == 19 );
  BOOST_TEST( Int(add.run({ 1, 3 })) == 4 );
}
