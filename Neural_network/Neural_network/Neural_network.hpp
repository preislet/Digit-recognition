#ifndef NEURAL_NET_HPP
#define NEURAL_NET_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include<fstream>
#include<sstream>
#include<memory>

class Neuron;
class NeuralNet;
using Layer = std::vector<Neuron>;

constexpr static double PARAMETER_FOR_ParametricReLU = 0.3;
constexpr static double PARAMETER_FOR_ELU = 0.01;
constexpr static double BIAS = 1.0;

constexpr static unsigned int OUTPUT_LAYER = 10;
constexpr static unsigned int NUM_OF_ACTIVATION_FUNCTIONS = 10;
constexpr static unsigned int IMAGE_DIMENSION = 28; // 28x28 pixels
constexpr static unsigned int IMAGE_SIZE = IMAGE_DIMENSION * IMAGE_DIMENSION;

// 
class ActivationFunctionBase {
public:
    virtual double EvaluateActivationFunction(double& value, double& gradient) = 0;
    virtual double EvaluateActivationFunctionDerivative(double& value, double& gradient) = 0;

    ~ActivationFunctionBase() = default;
};
class ActivationFunctionSigmoid :public ActivationFunctionBase
{
public:
    double virtual EvaluateActivationFunction(double& value, double& gradient) override;
    double virtual EvaluateActivationFunctionDerivative(double& value, double& gradient) override;
};
class ActivationFunctionTanh :public ActivationFunctionBase
{
public:
    double virtual EvaluateActivationFunction(double& value, double& gradient) override;
    double virtual EvaluateActivationFunctionDerivative(double& value, double& gradient) override;
};
class ActivationFunctionReLU :public ActivationFunctionBase
{
public:
    double virtual EvaluateActivationFunction(double& value, double& gradient) override;
    double virtual EvaluateActivationFunctionDerivative(double& value, double& gradient) override;
};
class ActivationFunctionLeakyReLU :public ActivationFunctionBase
{
public:
    double virtual EvaluateActivationFunction(double& value, double& gradient) override;
    double virtual EvaluateActivationFunctionDerivative(double& value, double& gradient) override;
};
class ActivationFunctionParametricReLU :public ActivationFunctionBase
{
public:
    double virtual EvaluateActivationFunction(double& value, double& gradient) override;
    double virtual EvaluateActivationFunctionDerivative(double& value, double& gradient) override;
};
class ActivationFunctionELU :public ActivationFunctionBase
{
public:
    double virtual EvaluateActivationFunction(double& value, double& gradient) override;
    double virtual EvaluateActivationFunctionDerivative(double& value, double& gradient) override;
};
class ActivationFunctionSwish :public ActivationFunctionBase
{
public:
    double virtual EvaluateActivationFunction(double& value, double& gradient) override;
    double virtual EvaluateActivationFunctionDerivative(double& value, double& gradient) override;
};
class ActivationFunctionGELU :public ActivationFunctionBase
{
public:
    double virtual EvaluateActivationFunction(double& value, double& gradient) override;
    double virtual EvaluateActivationFunctionDerivative(double& value, double& gradient) override;
};
class ActivationFunctionSELU :public ActivationFunctionBase
{
public:
    double virtual EvaluateActivationFunction(double& value, double& gradient) override;
    double virtual EvaluateActivationFunctionDerivative(double& value, double& gradient) override;
};

enum class ActivationFunctionsNum
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
    COUNT_
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
    ActivationFunctionsNum activationFunctionName;
    double eta;
    double alpha;
    double inputValue;
    double outputValue;
    double gradient;
    std::vector<Connection> outputWeights;
    std::vector<std::shared_ptr<ActivationFunctionBase>> ActivationFunctions;

    double ActivationFunction(double sumOfPreviousLayer);
    double ActivationFunctionDerivative(double Value);
    double SumDerivationsOfWeightsOfNextLayer(const Layer& nextLayer) const;
public:
    Neuron(int numberOfConnections, int index, double eta, double alpha, ActivationFunctionsNum activationFunction, const std::vector<std::shared_ptr<ActivationFunctionBase>>& ActivationFunctions);
    void SetOutputValue(const double outVal);
    double GetOutputValue() const;
    void FeedForward(const Layer& previousLayer);
    void CalculateOutputGradients(const double targetValue);
    void CalculateHiddenGradient(const Layer& nextLayer);
    void UpdatedInputWeights(Layer& prevLayer) const;
    void InsertWeights(const std::vector<double>& weight);
    std::vector<double> GetWeights() const;
};

class NeuralNet {
public:
    double alpha;
    double eta;
    ActivationFunctionsNum activationFunction;
private:
    std::vector<int> topology;
    std::vector<Layer> layers;
    RMSError RMS_error;
    std::vector<std::shared_ptr<ActivationFunctionBase>> ActivationFunctions;

    void CalculateRMS_error(const std::vector<double>& targetValues);
    void CalculateRecentAverageError();
    void CalculateOutputLayerGradients(const std::vector<double>& targetValues);
    void CalculateHiddenLayersGradients();
    void UpdateConnectionWeights();

public:
    NeuralNet();
    NeuralNet(const std::vector<int>& topology, double eta, double alpha, ActivationFunctionsNum activationFunction);
    void NeuralNetUpdate(const std::vector<int>& topology, double eta, double alpha, ActivationFunctionsNum activationFunction);
    void FeedForward(const std::vector<double>& inputValues);
    void BackPropagation(const std::vector<double>& targetValues);
    void InsertWeights(const std::vector<std::vector<std::vector<double>>>& weights);
    std::vector<int> GetTopology() const;
    std::vector<double> GetResults() const;
    std::vector<Layer> GetLayers() const;
    double AverageGetError() const;
    std::vector<std::vector<std::vector<double>>> GetWeights() const;
};

class FileHandler
{
public:
    std::vector<std::vector<double>> read_csv(const std::string& path) const;
    void writeWeightsToFile(const NeuralNet& MyNetwork, const std::string& path) const;
    void insertWeightsToNet(NeuralNet& MyNetwork, const std::string& path) const;
};

class NetworksTraining
{
public:
    void printValues(const int label, const ptrdiff_t index, const std::vector<double>& resultValues, const std::vector<double>& inputValues, const double averageError, const bool printNumber) const;
    void TrainNetwork(NeuralNet& MyNetwork, std::vector<std::vector<double>>& trainSamples) const;
    double testNetwork(NeuralNet& MyNetwork, std::vector<std::vector<double>>& testSamples, bool print = false) const;
};



#endif // NEURAL_NET_HPP