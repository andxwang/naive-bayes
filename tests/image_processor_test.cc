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

  SECTION("Digit tests") {
    REQUIRE(processor.images_.at(0).digit_ == 5);
    REQUIRE(processor.images_.at(1).digit_ == 0);
    REQUIRE(processor.images_.at(2).digit_ == 4);
    REQUIRE(processor.images_.at(15).digit_ == 7);
  }

  SECTION("2D char array tests") {
    string str;
    // pick an "interesting" row, i.e. one with shaded symbols
    vector<char> char_arr = processor.images_.at(0).image_arr2d_.at(7);
    for (char c : char_arr) {
      str += c;
    }
    REQUIRE(str == "       +##########+++++     ");

    char_arr = processor.images_.at(15).image_arr2d_.at(11);
    str = "";
    for (char c : char_arr) {
      str += c;
    }

    REQUIRE(str == "       +####++   +###+      ");
  }
}