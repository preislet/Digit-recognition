#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<memory>
#include<fstream>
#include<sstream>


#include "Neural_network.hpp"


//https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
//TO-DO předělat funkci, aby vyhovovala přesně tomu, co potřebuji
std::vector<std::pair<std::string, std::vector<double>>> read_csv()
{
    std::vector<std::pair<std::string, std::vector<double>>> result;

    // Create an input filestream
    std::ifstream myFile("train.csv");

    // Make sure the file is open
    if (!myFile.is_open()) throw std::runtime_error("Could not open file");

    // Helper vars
    std::string line, colname;
    int val;

    // Read the column names
    if (myFile.good())
    {
        // Extract the first line in the file
        std::getline(myFile, line);

        // Create a stringstream from line
        std::stringstream ss(line);

        // Extract each column name
        while (std::getline(ss, colname, ',')) {

            // Initialize and add <colname, int vector> pairs to result
            result.push_back({ colname, std::vector<double> {} });
        }
    }

    // Read data, line by line
    while (std::getline(myFile, line))
    {
        // Create a stringstream of the current line
        std::stringstream ss(line);

        // Keep track of the current column index
        int colIdx = 0;

        // Extract each integer
        while (ss >> val) {

            // Add the current integer to the 'colIdx' column's values vector
            result.at(colIdx).second.push_back(val);

            // If the next token is a comma, ignore it and move on
            if (ss.peek() == ',') ss.ignore();

            // Increment the column index
            colIdx++;
        }
    }

    // Close file
    myFile.close();
    return result;
}

int main()
{
    std::vector<int> topology = { 784,128,64,10 };

    std::vector<std::pair<std::string, std::vector<double>>> result = read_csv();
    

    std::vector<double> label = result[0].second;

    Net MyNetwork(topology);

    for(size_t i = 1; i < result[0].second.size(); i++)
    {
        std::vector<double> targetValues;
        for(int j = 0; j < 10; j++)
        {
            if (j == label[i]) targetValues.push_back(1);
            else targetValues.push_back(0);
        }
        std::vector<double> inputValues;
        for(int h = 1; h < result.size(); h++)
        {
            inputValues.emplace_back(result[h].second.at(i));
        }
        MyNetwork.FeedForward(inputValues);
        MyNetwork.BackPropagation(targetValues);
        std::vector<double> resultValues = MyNetwork.GetResults();

        std::cout <<"Expected value: " << label[i] << std::endl;

        resultValues.pop_back();
        int position = 0;
        double max = -5;
        for (int o = 0; o < resultValues.size(); o++)
        {
	        if (resultValues[o] > max)
	        {
                position = o;
                max = resultValues[o];
	        }
        }
        std::cout << "Network output: " << position << std::endl;
        std::cout << "Exact probability: ";
        for (double val : resultValues)
            std::cout << val << " ";

        std::cout<<std::endl;
        std::cout << "Average Error: " << MyNetwork.AvarageGetError() << std::endl;
        std::cout << "=========================================================" << std::endl;
    }
}

