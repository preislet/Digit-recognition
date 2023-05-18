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

class ImageConverison
{
private:
	RGB whitePixel = { 255,255,255 };
	bool IsPixelWhite(const  std::vector<std::vector<RGB>>& imageRGBVector, size_t i, size_t j) const;
public:
	std::vector<std::vector<RGB>> ConvertToVector(const std::string& path) const;
	std::vector<std::vector<int>> ConvertToBinVector(const std::vector<std::vector<RGB>>& imageRGBVector) const;

	std::vector<int> ConvertToCompressedBinaryNet_readyVector(const std::string& path) const;
	std::vector<int> ConvertToCompressedBinaryNet_readyVector(const std::vector<std::vector<RGB>>& imageRGBVector) const;
	std::vector<int> ConvertToCompressedBinaryNet_readyVector(const std::vector<std::vector<int>>& INT_vector) const;

	void PrintNumber(const std::vector<double>& Img_vector) const;
};
#endif //IMAGE_COVERSION