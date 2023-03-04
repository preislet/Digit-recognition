#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<memory>

#include "Neural_network.hpp" 
int main()
{
    std::vector<int> topology;

    Net MyNetwork(topology);

    std::vector<double> inputValues;
    MyNetwork.FeedForward(inputValues);
    std::vector<double> targetValues;
    MyNetwork.BackPropagation(targetValues);
    std::vector<double> resultValues;
    MyNetwork.GetResults(resultValues);

}

