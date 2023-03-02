#ifndef Neural_network
#define Neural_network

#include<iostream>
#include<vector>
class Neuron;
typedef std::vector<Neuron> Layer;

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
	double outputValue;
	std::vector<Connection> outputWeights;
public:
	Neuron(int NumberOfConnections);
	void SetOutputValue(const double outVal);
	double GetOutputValue() const;
};

class Net
{
private:
	std::vector<int> topology;
	std::vector<Layer> layers;
public:
	Net(const std::vector<int>&){}

	void FeedForward(const std::vector<double>& inputValues);
	void BackPropagation(const std::vector<double>& outputValues);
	void GetResults(std::vector<double> resultValues) const;


};

#endif