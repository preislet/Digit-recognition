#ifndef IMAGE_COVERSION
#define IMAGE_COVERSION

#include<vector>
#include<string>

constexpr static unsigned int neuralNetworkImageWidth = 28;
constexpr static unsigned int neuralNetworkImageHeight = 28;
struct RGB
{
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
};
std::vector<std::vector<RGB>> ConvertToVector(const std::string& path);
std::vector<std::vector<int>> ConvertToBinVector(const std::vector<std::vector<RGB>>& imageRGBVector);

std::vector<int> ConvertToCompressedBinaryNet_readyVector(const std::string& path);
std::vector<int> ConvertToCompressedBinaryNet_readyVector(const std::vector<std::vector<RGB>>& imageRGBVector);
std::vector<int> ConvertToCompressedBinaryNet_readyVector(const std::vector<std::vector<int>> &INT_vector);

void PrintNumber(const std::vector<double>& Img_vector);
#endif //IMAGE_COVERSION