#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<memory>
#include<fstream>
#include<sstream>


#include "Neural_network.cpp"


std::vector<std::vector<double>> read_csv(const std::string& path)
{
    std::ifstream CSV_File(path);
    std::string line;

    std::vector<std::vector<double>> result;
    result.emplace_back();
    if(CSV_File.good()) std::getline(CSV_File, line); //extract names of column

    while(std::getline(CSV_File, line))
    {
        std::stringstream ss(line);
        std::string tmp;

        std::getline(ss, tmp, ',');
        double tmp_int = std::stod(tmp);
        result.back().emplace_back(tmp_int);

        while(std::getline(ss,tmp, ','))
        {
            double tmp_int = std::stod(tmp);
            tmp_int = (tmp_int > 0.0) ? 1.0 : 0.0;
            result.back().emplace_back(tmp_int);
        }
        result.emplace_back();
    }
    CSV_File.close();
    while (result.back().empty()) result.pop_back();
    return result;
}
void printValues(const int label, const ptrdiff_t index, const std::vector<double>& resultValues, const std::vector<double>& inputValues, const double averageError, const bool printNumber)
{
    std::cout << "Expected value: " << label << std::endl;
    std::cout << "Network output: " << index << std::endl;
    std::cout << "Exact probability: ";
    for (const double val : resultValues)
        std::cout << val << " ";
    std::cout << std::endl;
    std::cout << "Average Error: " << averageError << std::endl;
    std::cout << std::endl;

    if (!printNumber)
    {
        std::cout << "=========================================================" << std::endl;
        return;
    }

    for (int i = 0; i < 28; ++i)
    {
        for (int j = 0; j < 28; ++j)
        {
            if (inputValues[28 * i + j] == 0.0) std::cout << " ";
            else std::cout << "S";
        }
        std::cout << std::endl;
    }

    std::cout << "=========================================================" << std::endl;
}
void testNetwork(const std::vector<std::vector<double>>& trainSamples, const std::vector<std::vector<double>>& testSamples, float eta_divider, float alpha_divider)
{
    const std::vector<int> topology = { 784,128,64,10 };
    float eta = rand() / float(RAND_MAX);
	float alpha = rand() / float(RAND_MAX);
    eta = eta / eta_divider;
    alpha = alpha / alpha_divider;
    std::cout << "eta: " << eta << " alpha: " << alpha << " ";
	
    Net MyNetwork(topology, eta, alpha);

    //train
    for (auto trainSample : trainSamples)
    {
        const int label = trainSample[0];

        std::vector<double> targetValues(10, 0.0);
        targetValues[label] = 1.0;
        trainSample.erase(trainSample.begin());

        MyNetwork.FeedForward(trainSample);
        MyNetwork.BackPropagation(targetValues);

        //std::vector<double> resultValues = MyNetwork.GetResults();
        //resultValues.pop_back();

        //const auto max_element = std::max_element(resultValues.begin(), resultValues.end());
        //const auto max_element_index = std::distance(resultValues.begin(), max_element);
        //printValues(label, max_element_index, resultValues, trainSample, MyNetwork.AverageGetError(), false);
    }

    //test
   
    double correct_predictions = 0.0;
    for (auto testSample : testSamples)
    {
        const int label = testSample[0];

        std::vector<double> targetValues(10, 0.0);
        targetValues[label] = 1.0;
        testSample.erase(testSample.begin());
        MyNetwork.FeedForward(testSample);
        std::vector<double> resultValues = MyNetwork.GetResults();

        resultValues.pop_back();
        const auto max_element = std::max_element(resultValues.begin(), resultValues.end());
        const auto max_element_index = std::distance(resultValues.begin(), max_element);
        if (label == max_element_index) correct_predictions += 1.0;

        //printValues(label, max_element_index, resultValues, testSample, MyNetwork.AverageGetError(), true);
    }
    std::cout << correct_predictions / 10000 << std::endl;
}

int main()
{
    const auto trainSamples = read_csv("train.csv");
    const auto testSamples = read_csv("test.csv");
    for (int i = 0; i < 200; i++)
    {
        const float eta_divider = 4;
        const float alpha_divider = 2;
        testNetwork(trainSamples, testSamples, eta_divider, alpha_divider);
    }
}

