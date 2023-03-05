#ifndef Neural_network
#define Neural_network

#include<iostream>
#include<vector>
class Neuron;
using Layer = std::vector<Neuron>;

struct RMSError
{
	double error;
	double recentAverageError;
	double recentAverageSmoothingFactor;
};
struct Connection
{
	double weight;
	double deltaWeight;
	Connection();
private:
	static double RandomNumber();
};

class Neuron
{
private:
	int NumberOfConnections;
	int index;

	double outputValue;
	double gradient;

	std::vector<Connection> outputWeights;

	static double ActivationFunction(double sumOfPreviousLayer);
	static double ActivationFunctionDerivative(double tanhValue);
	double SumDerivationsOfWeightsOfNextLayer(const Layer& nextLayer) const;
public:
	Neuron(int numberOfConnections, int index);
	void SetOutputValue(const double outVal);
	double GetOutputValue() const;
	void FeedForward(const Layer& previousLayer);
	void CalculateOutputGradients(const double targetValue);
	void CalculateHiddenGradient(const Layer& nextLayer);
	void UpdatedInputWeights(Layer& prevLayer) const;


};

class Net
{
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
	Net(const std::vector<int>&){}
	void FeedForward(const std::vector<double>& inputValues);
	void BackPropagation(const std::vector<double>& outputValues);
	std::vector<double> GetResults() const;


};

#endif