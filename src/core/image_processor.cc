#include <core/image_processor.h>

namespace naivebayes {

ImageProcessor::ImageProcessor() {
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
    image.image_arr_.reserve(processor.kImageSize);
    for (size_t row = 0; row < processor.kImageSize; row++) {
      std::getline(istream, line);
      vector<char> row_of_chars;
      row_of_chars.reserve(processor.kImageSize);
      for (size_t col = 0; col < processor.kImageSize; col++) {
        row_of_chars.push_back(line[col]);
      }
      image.image_arr_.push_back(row_of_chars);
    }
    processor.images_.push_back(image);
  }
  return istream;
}

}  // namespace naivebayes