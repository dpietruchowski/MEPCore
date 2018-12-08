#include <boost/test/included/unit_test.hpp>

#include <stdio.h>

#include "color.h"

using namespace mep;

BOOST_AUTO_TEST_CASE( color_test )
{
  Color red(Color::RED);
  Color green(Color::GREEN);

  std::cout << red << "Color" << green << " test" << std::endl;
}