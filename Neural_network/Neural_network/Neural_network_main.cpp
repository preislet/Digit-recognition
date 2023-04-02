#include<iostream>
#include<vector>
#include<string>
#include<fstream>

#include "Neural_network.hpp"
#include "Image_conversion.hpp"

int main()
{

    std::vector<std::vector<RGB>> RGB_vector = ConvertToVector("four2.jpg");
    std::vector<std::vector<int>> INT_vector = ConvertToBinVector(RGB_vector);
    std::vector<int> vec = ConvertToCompressedBinaryNet_readyVector(INT_vector);



    


    /*
     *
    const std::vector<int> topology = { 784,128,64,10 };
    
    //const auto trainSamples = read_csv("train.csv");
    const auto testSamples = read_csv("test.csv");

    for (int i = 0; i < 8; i++)
    {
        const float eta = 0.033665;
        const float alpha = 0.0889798;
        std::cout << "eta: " << eta << " alpha: " << alpha << " ";

        Net MyNetwork(topology, eta, alpha);
        insertWeightsToNet(MyNetwork);
        //TrainNetwork(MyNetwork, trainSamples);
        double prop = testNetwork(MyNetwork, testSamples);

        std::cout << std::endl;
    }
    */
	
}

