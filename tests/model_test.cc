//
// Created by Andy Wang on 3/28/22.
//

#include <catch2/catch.hpp>
#include <core/model.h>
#include <iostream>
using std::cout;
using std::endl;

using namespace naivebayes;

const float kLaplace = 1.0;

Model full_model("/Users/andywang/Downloads/Cinder/my-projects/naivebayes-andyw-git/data/trainingimagesandlabels.txt");
Model small_model("/Users/andywang/Downloads/Cinder/my-projects/naivebayes-andyw-git/data/images_small.txt");

TEST_CASE("Prior calculation") {
  small_model.CalculatePriors();
  REQUIRE(Approx((kLaplace + 2.0)/(10*kLaplace + 16)) ==
          small_model.GetPriors().at(5));
  REQUIRE(Approx((kLaplace + 3.0)/(10*kLaplace + 16)) ==
          small_model.GetPriors().at(3));
  REQUIRE(Approx((kLaplace + 4.0)/(10*kLaplace + 16)) ==
          small_model.GetPriors().at(1));
  REQUIRE(Approx((kLaplace + 0.0)/(10*kLaplace + 16)) ==
          small_model.GetPriors().at(8));
}

TEST_CASE("Feature probability calculation") {
  SECTION("small model") {
    small_model.CalculateFeatureProbabilities();
    REQUIRE(Approx(kLaplace / (2 * kLaplace + 4)) ==
            small_model.GetFeatureProbabilities().at(1)[0][0]);
  }
  SECTION("5x5 model") {
    // 10 digits, each a 5x5 image
    Model model_5x5("/Users/andywang/Downloads/Cinder/my-projects/naivebayes-andyw-git/data/images_5x5.txt", 5);
    model_5x5.Train();
    // top left pixel appears in every 0
    REQUIRE(Approx((kLaplace + 5) / (2 * kLaplace + 5)) ==
            model_5x5.GetFeatureProbabilities().at(0)[0][0]);
    // middle pixel appears in every 2
    REQUIRE(Approx((kLaplace + 5) / (2 * kLaplace + 5)) ==
            model_5x5.GetFeatureProbabilities().at(2)[2][2]);
    // bottom left pixel never appears in any 9
    REQUIRE(Approx((kLaplace + 0) / (2 * kLaplace + 5)) ==
            model_5x5.GetFeatureProbabilities().at(9)[4][0]);
  }
}

TEST_CASE("Write to output file") {
  full_model.Train();
  string output_path = "/Users/andywang/Downloads/Cinder/my-projects/naivebayes-andyw-git/data/output.txt";
  std::ofstream output_file(output_path);
  if (output_file.is_open()) {
    output_file << full_model;
    output_file.close();
  }
}

TEST_CASE("Read from outputted file") {
  // first train model and write to output
  // this can be commented out if data is already present in output.txt
//  full_model.Train();
//  string output_path = "/Users/andywang/Downloads/Cinder/my-projects/naivebayes-andyw-git/data/output.txt";
//  std::ofstream output_file(output_path);
//  if (output_file.is_open()) {
//    output_file << full_model;
//    output_file.close();
//  }
  string file_path = "/Users/andywang/Downloads/Cinder/my-projects/naivebayes-andyw-git/data/output.txt";
  std::ifstream input_file(file_path);
  if (input_file.is_open()) {
    input_file >> full_model;
  }
  SECTION("Priors load test") {
    REQUIRE(Approx(0.0958084) == full_model.GetPriors().at(0));
    REQUIRE(Approx(0.112575) == full_model.GetPriors().at(1));
    REQUIRE(Approx(0.099002) == full_model.GetPriors().at(9));
  }
  SECTION("Feature probabilities load test") {
    REQUIRE(Approx(0.002079) ==
            full_model.GetFeatureProbabilities().at(0)[0][0]);
    REQUIRE(Approx(0.00623701) ==
            full_model.GetFeatureProbabilities().at(0)[6][4]);
  }
}