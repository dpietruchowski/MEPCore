#include <boost/test/included/unit_test.hpp>

#include <stdio.h>

#include "color.h"
#include "log.h"

using namespace mep;

BOOST_AUTO_TEST_CASE( color_test )
{
  Color red(Color::RED);
  Color green(Color::GREEN);

  std::cout << red << "Color" << green << " test" << std::endl;
}

BOOST_AUTO_TEST_CASE( log_test )
{
  GeneLog(ERROR) << "Gene Log test";
  ChromosomeLog(ERROR) << "Chromsome Log test";
  PopulationLog(ERROR) << "Population Log test";
}