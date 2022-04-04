//
// Created by Andy Wang on 3/28/22.
//

#ifndef MODEL_H_
#define MODEL_H_

#include "image_processor.h"
#include <string>

namespace naivebayes {

class Model {
 public:
  /**
   * One-parameter onstructor for a Model object.
   * @param file_path the file path of the training data and labels
   */
  Model(const string& file_path);

  /**
   * Two-parameter constructor for a Model object.
   * @param file_path the file path of the training data and labels
   * @param image_size the image dimension
   */
  Model(const string& file_path, int image_size);

  /**
   * Trains the model.
   * Runs CalculatePriors and CalculateFeatureProbabilities.
   */
  void Train();

  /**
    * Calculates the probability that an image
    * belongs to a certain class/digit,
    * i.e. P(class = c).
    * Factors in Laplace constant.
   */
  void CalculatePriors();

  /**
    * Calculates the ratio of
    * # images belonging to a class/digit where pixel (i,j) is shaded/unshaded
    * to the total # of images belonging to that class/digit in the training data,
    * i.e. P(F_(i,j) = f | class = c).
    * Factors in Laplace constant.
   */
  void CalculateFeatureProbabilities();

  /**
   * Operator overload for output stream.
   * @param ostream the output stream
   * @param model the model from which info is taken
   * @return the ostream
   */
  friend std::ostream& operator<<(std::ostream& ostream, const Model& model);

  /**
   * Operator overload for input stream.
   * @param istream the input stream
   * @param model the model to which info is written
   * @return the istream
   */
  friend std::istream& operator>> (std::istream& istream, Model& model);

  const vector<float>& GetPriors() const;
  const vector<vector<vector<float>>>& GetFeatureProbabilities() const;

 private:
  //=========== const variables ===========//
  const char kBlackPixel = '#';
  const char kGrayPixel = '+';
  const float kLaplace = 1.0;
  const int kNumDigits = 10; // should always be 10, i.e. [0,9]
  static const int kDefaultImageSize = 28;

  //=========== member objects ===========//
  ImageProcessor processor_;
  int image_size_;
  int num_images_; // 5000 images in training data file
  //=========== vectors for probability calculations ===========//
  // frequency of classes/digits by index
  vector<int> classes_count_;
  // priors for each class/digit
  vector<float> priors_;
  // 3d vector of image-wise feature probs for each digit/class, e.g. 10x28x28
  vector<vector<vector<float>>> feature_probabilities_;
};

}  // namespace naivebayes

#endif  // MODEL_H_
