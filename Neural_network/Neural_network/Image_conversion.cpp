#include<vector>
#include<algorithm>
#include<string>


#include <Winsock2.h>
#include <windows.h> 
#include<gdiplus.h>
#include<basetsd.h>

#include <tchar.h>
#include <stdio.h>


#pragma comment(lib,"gdiplus.lib")
#include"Image_conversion.hpp"

#include <iostream>

/*This function takes a path to an image file and returns a vector of vectors of RGB values that represent the pixels in the image.
 It uses the GDI+ library to read the image file and extract the RGB values of each pixel.
 It then stores these values in a two-dimensional vector, where each row represents a horizontal line of pixels in the image, and each column represents
 a single pixel in that line.*/
std::vector<std::vector<RGB>> ImageConverison::ConvertToVector(const std::string& path) const
{
    
    Gdiplus::GdiplusStartupInput si;
    ULONG_PTR token;
    Gdiplus::GdiplusStartup(&token, &si, nullptr);
    const std::wstring Image_path(path.begin(), path.end());

    Gdiplus::Bitmap image(Image_path.c_str(), false);
    const int width = image.GetWidth();
    const int height = image.GetHeight();

    std::vector<std::vector<RGB>> Image_vector;
    for (int i = 0; i < width; i++)
    {
        std::vector<RGB> row_vector;
        row_vector.reserve(width);
        for (int j = 0; j < height; j++)
        {
            RGB rgb;
            Gdiplus::Color argb;
        	image.GetPixel(i, j, &argb);
            rgb.r = argb.GetR();
            rgb.g = argb.GetG();
            rgb.b = argb.GetB();
            row_vector.emplace_back(rgb);
        }
        Image_vector.emplace_back(row_vector);
    }

    return Image_vector;
}

/*This function takes a vector of vectors of RGB values and converts it into a binary vector of vectors, where each element is either 0 or 1,
 depending on whether the corresponding RGB value represents a white or black pixel. It does this by iterating over each element in the input vector,
 and checking whether its RGB values are equal to those of a white pixel (255, 255, 255).
 If so, it sets the corresponding element in the output vector to 0; otherwise, it sets it to 1.*/
std::vector<std::vector<int>> ImageConverison::ConvertToBinVector(const std::vector<std::vector<RGB>>& imageRGBVector) const
{
    std::vector<std::vector<int>> INT_vector;
    for (int i = 0; i < imageRGBVector.size(); ++i)
    {
        std::vector<int> INT_vector_line;
        for (int j = 0; j < imageRGBVector[0].size(); ++j)
        {
            if (imageRGBVector[i][j].r == whitePixel.r && imageRGBVector[i][j].g == whitePixel.g && imageRGBVector[i][j].b == whitePixel.b) INT_vector_line.push_back(0);
            else INT_vector_line.push_back(1);
        }
    	INT_vector.emplace_back(INT_vector_line);
    }

    std::vector<std::vector<int> >INT_vectorTranspose(INT_vector[0].size(), std::vector<int>(INT_vector.size()));
    for (size_t i = 0; i < INT_vector.size(); ++i)
        for (size_t j = 0; j < INT_vector[0].size(); ++j)
            INT_vectorTranspose[j][i] = INT_vector[i][j];

    return INT_vectorTranspose;
}

/*(overloaded): These functions take either a path to an image file or a vector of vectors of RGB values, and convert it into a vector of integers
 that is ready to be used as input to a compressed neural network. This is done by first calling ConvertToBinVector to convert the RGB values into binary values,
 and then compressing the resulting binary vector by dividing it into small windows, and representing each window with a single binary value that indicates whether
 more than half of the pixels in the window are black or white.*/
std::vector<int> ImageConverison::ConvertToCompressedBinaryNet_readyVector(const std::string& path) const
{
    const std::vector<std::vector<RGB>> imageRGBVector = ConvertToVector(path);
	std::vector<int> Img_vector = ConvertToCompressedBinaryNet_readyVector(imageRGBVector);
    return Img_vector;

}
std::vector<int> ImageConverison::ConvertToCompressedBinaryNet_readyVector(const std::vector<std::vector<RGB>>& imageRGBVector) const
{
    const std::vector<std::vector<int>> INT_vector = ConvertToBinVector(imageRGBVector);
	std::vector<int> Img_vector = ConvertToCompressedBinaryNet_readyVector(INT_vector);
    return Img_vector;
}
std::vector<int> ImageConverison::ConvertToCompressedBinaryNet_readyVector(const std::vector<std::vector<int>> &INT_vector) const
{
    
    std::vector<int> neuralNetReadyVector;
	const size_t width = INT_vector[0].size();
	const size_t height = INT_vector.size();

    const size_t window_width = width / neuralNetworkImageWidth;
    const size_t window_height = height / neuralNetworkImageHeight;


    for(size_t windowRow = 0; windowRow < neuralNetworkImageHeight; ++windowRow)
    {
	    for(size_t windowColumn = 0; windowColumn < neuralNetworkImageWidth; ++windowColumn)
	    {
            std::vector <std::vector<int>> windowVector;
            for(size_t i = windowRow * window_height; i < (windowRow + 1) * window_height; i++)
            {
                std::vector<int> windowVector_line;
	            for (size_t j = windowColumn * window_width; j < (windowColumn + 1) * window_width; j++)
	            {
                    windowVector_line.push_back(INT_vector[i][j]);
	            }
                windowVector.emplace_back(windowVector_line);
            }
            size_t counterOfOnes = 0;
            for (const auto& windowLine : windowVector)
                counterOfOnes += std::count(windowLine.begin(), windowLine.end(), 1);

            if (counterOfOnes >= (window_width * window_height) / 2) neuralNetReadyVector.push_back(1);
            else neuralNetReadyVector.push_back(0);
            
	    }
    }
    return neuralNetReadyVector;
}

/*This function takes a vector of integers that represent a compressed binary image of a handwritten digit, and prints it to the console in the form of a 28x28 grid of characters,
 where each character represents a single pixel in the image. The character 'S' is used to represent a black pixel,
 and a space character is used to represent a white pixel.*/
void ImageConverison::PrintNumber(const std::vector<double>& Img_vector) const
{
    for (size_t i = 0; i < 28; ++i)
    {
        for (size_t j = 0; j < 28; ++j)
        {
            if (Img_vector[28 * i + j] == 0.0) std::cout << " ";
            else std::cout << "S";
        }
        std::cout << std::endl;
    }
}
    
    
   
