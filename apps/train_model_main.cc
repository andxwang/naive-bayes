#include <iostream>

#include <core/model.h>

using std::cout;
using std::endl;

using namespace naivebayes;

// TODO: You may want to change main's signature to take in argc and argv
int main() {

  cout << "Training..." << endl;

  // train model from scratch
//  string full_data_file = "/Users/andywang/Downloads/Cinder/my-projects/naivebayes-andyw-git/data/trainingimagesandlabels.txt";
//  Model full_model(full_data_file);
//  full_model.Train();
//  string output_path = "/Users/andywang/Downloads/Cinder/my-projects/naivebayes-andyw-git/data/output_alt.txt";
//  std::ofstream output_file(output_path);
//  if (output_file.is_open()) {
//    output_file << full_model;
//    output_file.close();
//  }

  // load from output file to model
  // NOTE: by setting kGrayFactor to 0.78, the accuracy actually increases by 1.1!
  string train_data_path = "/Users/andywang/Downloads/Cinder/my-projects/naivebayes-andyw-git/data/";
  train_data_path += "output_alt.txt";
  Model full_model;
  std::ifstream train_is(train_data_path);
  if (train_is.is_open()) {
    train_is >> full_model;
  }

  // load test data into processor
  string test_data_path = "/Users/andywang/Downloads/Cinder/my-projects/naivebayes-andyw-git/data/testimagesandlabels.txt";
  ImageProcessor test_processor;
  std::ifstream istream(test_data_path);
  if (istream.is_open()) {
    istream >> test_processor;
  }
  int correct_total = 0;
  for (auto & image : test_processor.images_) {
    vector<vector<char>> image2d = image.image_arr2d_;
    int result = full_model.CalculateMaxLikelihoodDigit(image2d);
    cout << "Actual: " << image.digit_ << "; ";
    cout << "Guess: " << result << endl;
    if (image.digit_ == result)
      correct_total++;
  }
  cout << "Accuracy: " << static_cast<float>(correct_total) / test_processor.images_.size() << endl;

  return 0;
}
