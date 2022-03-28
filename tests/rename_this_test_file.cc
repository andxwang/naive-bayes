#include <catch2/catch.hpp>

#include <core/image_processor.h>
#include <iostream>
using std::cout;
using std::endl;

using namespace naivebayes;

TEST_CASE("Image processor initialization") {
  ImageProcessor processor;
  string file_path = "/Users/andywang/Downloads/Cinder/my-projects/naivebayes-andyw-git/data/images_small.txt";
  std::ifstream input_file(file_path);
  if (input_file.is_open()) {
    input_file >> processor;
  }
  REQUIRE(processor.images_.at(0).digit_ == 5);
}

/*
TODO: Rename this test file. You'll also need to modify CMakeLists.txt.

You can (and should) create more test files; this project is too big
for all tests to be in the same file. Remember that, for each file (foo.cc)
containing non-trivial code, you should have a corresponding test file
(foo_test.cc)

Make sure to add any files that you create to CMakeLists.txt.

TODO Delete this comment and the placeholder test before submitting your code.
*/
