#include <core/image_processor.h>

namespace naivebayes {

ImageProcessor::ImageProcessor() : ImageProcessor(kDefaultImageSize) {}

ImageProcessor::ImageProcessor(int image_size) {
  image_size_ = image_size;
  images_ = vector<Image>();
  images_.reserve(kNumImages);
}

std::istream& operator>>(std::istream& istream, ImageProcessor& processor) {
  string line;
  while (std::getline(istream, line)) {
    // initialize an Image
    ImageProcessor::Image image;
    // first get the actual digit
    image.digit_ = std::stoi(line);
    // then initialize the 2D array
    image.image_arr2d_.reserve(processor.image_size_);
    for (size_t row = 0; row < processor.image_size_; row++) {
      std::getline(istream, line);
      vector<char> row_of_chars;
      row_of_chars.reserve(processor.image_size_);
      for (size_t col = 0; col < processor.image_size_; col++) {
        row_of_chars.push_back(line[col]);
      }
      image.image_arr2d_.push_back(row_of_chars);
    }
    processor.images_.push_back(image);
  }
  return istream;
}

}  // namespace naivebayes