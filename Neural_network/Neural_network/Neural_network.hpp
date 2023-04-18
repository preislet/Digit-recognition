#ifndef NEURAL_NET_HPP
#define NEURAL_NET_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include<fstream>
#include<sstream>

class Neuron;
class NeuralNet;
using Layer = std::vector<Neuron>;

constexpr static unsigned int PARAMETER_FOR_ParametricReLU = 0.8;
constexpr static unsigned int PARAMETER_FOR_ELU = 1;

enum class ActivationFunctions
{
    Sigmoid,
    Tanh,
    ReLU,
    LeakyReLU,
    ParametricReLU,
    ELU,
    Swish,
    GELU,
    SELU,
};

struct RMSError {
    double error = 0;
    double recentAverageError = 0;
    double recentAverageSmoothingFactor = 100;
};

struct Connection {
    double weight;
    double deltaWeight;
    Connection();
private:
    static double RandomNumber();
};

class Neuron {
private:
    int numberOfConnections;
    int index;
    ActivationFunctions activationFunctionName;
    double eta;
    double alpha;
    static constexpr int BIAS = 1;

    double inputValue;
    double outputValue;
    double gradient;

    std::vector<Connection> outputWeights;

	double ActivationFunction(double sumOfPreviousLayer);
    double ActivationFunctionDerivative(double Value);
    double SumDerivationsOfWeightsOfNextLayer(const Layer& nextLayer) const;
public:
    Neuron(int numberOfConnections, int index, double eta, double alpha, ActivationFunctions activationFunction);
    void SetOutputValue(const double outVal);
    double GetOutputValue() const;
    void FeedForward(const Layer& previousLayer);
    void CalculateOutputGradients(const double targetValue);
    void CalculateHiddenGradient(const Layer& nextLayer);
    void UpdatedInputWeights(Layer& prevLayer) const;
    void InsertWeights(const std::vector<double> &weight);
    std::vector<double> GetWeights() const;
};

class NeuralNet {
public:
    double alpha;
    double eta;
    ActivationFunctions activationFunction;
private:
    std::vector<int> topology;
    std::vector<Layer> layers;
    RMSError RMS_error;

    void CalculateRMS_error(const std::vector<double>& targetValues);
    void CalculateRecentAverageError();
    void CalculateOutputLayerGradients(const std::vector<double>& targetValues);
    void CalculateHiddenLayersGradients();
    void UpdateConnectionWeights();

public:
    NeuralNet();
    NeuralNet(const std::vector<int>& topology, double eta, double alpha, ActivationFunctions activationFunction);
    void NeuralNetUpdate(const std::vector<int>& topology, double eta, double alpha, ActivationFunctions activationFunction);
    void FeedForward(const std::vector<double>& inputValues);
    void BackPropagation(const std::vector<double>& targetValues);
    void InsertWeights(const std::vector<std::vector<std::vector<double>>>& weights);
    std::vector<int> GetTopology() const;
    std::vector<double> GetResults() const;
    double AverageGetError() const;
    std::vector<std::vector<std::vector<double>>> GetWeights() const;
};
std::vector<std::vector<double>> read_csv(const std::string& path);
void printValues(const int label, const ptrdiff_t index, const std::vector<double>& resultValues, const std::vector<double>& inputValues, const double averageError, const bool printNumber);
void TrainNetwork(NeuralNet& MyNetwork, const std::vector<std::vector<double>>& trainSamples);
double testNetwork(NeuralNet& MyNetwork, const std::vector<std::vector<double>>& testSamples, bool print = false);
void writeWeightsToFile(const NeuralNet& MyNetwork, const std::string &path);
void insertWeightsToNet(NeuralNet& MyNetwork,const std::string& path);

#endif // NEURAL_NET_HPP
