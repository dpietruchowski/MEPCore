find_package(Boost REQUIRED COMPONENTS unit_test_framework)

macro(create_test name)
  message(${name}.cpp)
  add_executable(${name} ${name}.cpp)
  target_include_directories(${name} PRIVATE ${Boost_INCLUDE_DIRS})
  target_compile_definitions(${name} PRIVATE BOOST_TEST_DYN_LINK=1 BOOST_TEST_MAIN=1)
  target_link_libraries(${name} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
  target_link_libraries(${name} libmepcore.so)
endmacro()

create_test("testoperation")
create_test("testutils")
create_test("testgene")