//
// Created by Andy Wang on 3/28/22.
//

#include <iostream>
#include "core/model.h"

namespace naivebayes {

Model::Model(const string& file_path) : Model(file_path, kDefaultImageSize) {}

Model::Model(const string& file_path, int image_size)
    : processor_(image_size), image_size_(image_size) {
  std::ifstream input_file(file_path);
  if (input_file.is_open()) {
    input_file >> processor_;
  }
  num_images_ = processor_.images_.size();
  // count number of classes
  classes_count_ = vector<int>(kNumDigits);
  for (ImageProcessor::Image& image : processor_.images_) {
    classes_count_.at(image.digit_)++;
  }
}

void Model::Train() {
  CalculatePriors();
  CalculateFeatureProbabilities();
}

void Model::CalculatePriors() {
  priors_.clear();
  priors_.reserve(kNumDigits);
  for (size_t freq : classes_count_) {
    priors_.push_back((kLaplace + freq) / (kNumDigits * kLaplace + num_images_));
  }
}

void Model::CalculateFeatureProbabilities() {
  feature_probabilities_ = vector<vector<vector<float>>>
      (kNumDigits,vector<vector<float>>
       (image_size_,vector<float>
        (image_size_,0)));
  // get shaded pixel counts for each (i,j)
  for (ImageProcessor::Image& image : processor_.images_) {
    for (int row = 0; row < image_size_; row++) {
      for (int col = 0; col < image_size_; col++) {
        if (image.image_arr2d_[row][col] == kBlackPixel ||
            image.image_arr2d_[row][col] == kGrayPixel)
          feature_probabilities_.at(image.digit_)[row][col]++;
      }
    }
  }
  // divide by total # images belonging to class/digit
  for (int digit = 0; digit < kNumDigits; digit++) {
    for (int row = 0; row < image_size_; row++) {
      for (int col = 0; col < image_size_; col++) {
        feature_probabilities_.at(digit)[row][col] =
            (kLaplace + feature_probabilities_.at(digit)[row][col]) /
            (2 * kLaplace + classes_count_.at(digit));
      }
    }
  }
}

std::ostream& operator<<(std::ostream& ostream, const Model& model) {
  // output priors
  for (int i = 0; i < model.kNumDigits; i++) {
    ostream << model.GetPriors().at(i);
    ostream << " ";
  }
  ostream << "\n";
  // output 28x28 grid of probabilities for each digit/class
  for (int digit = 0; digit < model.kNumDigits; digit++) {
    for (int row = 0; row < model.image_size_; row++) {
      for (int col = 0; col < model.image_size_; col++) {
        ostream << model.GetFeatureProbabilities().at(digit)[row][col]
                << " ";
      }
      ostream << "\n";
    }
  }
  return ostream;
}

std::istream& operator>>(std::istream& istream, Model& model) {
  // load priors, which is the first line of the input file
  model.priors_.clear();
  model.priors_.reserve(model.kNumDigits);
  for (int i = 0; i < model.kNumDigits; i++) {
    float val;
    istream >> val;
    model.priors_.push_back(val);
  }
  // load 3D vector of feature probabilities
  model.feature_probabilities_ = vector<vector<vector<float>>>
      (model.kNumDigits,vector<vector<float>>
       (model.image_size_,vector<float>
        (model.image_size_,0)));
  for (int digit = 0; digit < model.kNumDigits; digit++) {
    for (int row = 0; row < model.image_size_; row++) {
      for (int col = 0; col < model.image_size_; col++) {
        float val;
        istream >> val;
        model.feature_probabilities_.at(digit)[row][col] = val;
      }
    }
  }
  return istream;
}

const vector<float>& Model::GetPriors() const {
  return priors_;
}

const vector<vector<vector<float>>>& Model::GetFeatureProbabilities() const {
  return feature_probabilities_;
}

}  // namespace naivebayes
