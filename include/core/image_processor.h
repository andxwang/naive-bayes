#pragma once

#include <string>
#include <vector>
#include <istream>
#include <fstream>

using std::vector;
using std::string;

namespace naivebayes {

class ImageProcessor {
 public:
  ImageProcessor();
  ImageProcessor(int image_size);
  /**
   * Overloads >> operator to parse file into ImageProcessor object.
   * @param istream the istream
   * @param processor the ImageProcessor object
   * @return the istream
   */
  friend std::istream& operator>> (std::istream& istream, ImageProcessor& processor);

  struct Image {
    Image() {
      digit_ = 0;
      image_arr2d_ = vector<vector<char>>();
    }
    int digit_;
    vector<vector<char>> image_arr2d_;
  };

  static const int kDefaultImageSize = 28;
  const int kNumImages = 5000;
  int image_size_;
  vector<Image> images_;
};

}  // namespace naivebayes