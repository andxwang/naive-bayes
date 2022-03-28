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
  friend std::istream& operator>> (std::istream& is, ImageProcessor& processor);

  struct Image {
   public:
    Image() {
      digit_ = 0;
      image_arr_ = vector<vector<char>>();
    }
    int digit_;
    vector<vector<char>> image_arr_;
  };

// private:
  const int kImageSize = 28;
  const int kNumImages = 5000;
  vector<Image> images_;
};

}  // namespace naivebayes

/*
TODO: rename this file. You'll also need to modify CMakeLists.txt.

You can (and should) create more classes and files in include/core (header
 files) and src/core (source files); this project is too big to only have a
 single class.

Make sure to add any files that you create to CMakeLists.txt.

TODO Delete this comment before submitting your code.
*/
