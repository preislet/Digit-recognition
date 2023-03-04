#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cassert>

class Neuron;
using Layer = std::vector<Neuron>;

struct Connection
{
	double weight;
	double deltaWeight;
	Connection()
	{
		this->weight = RandomNumber();
		this->deltaWeight = 0;
	}
private:
	static double RandomNumber() { return (double)rand() / RAND_MAX; }
};

class Neuron
{
private:
	int numberOfConnections;
	int index;
	double outputValue;
	std::vector<Connection> outputWeights;

	static double ActivationFunction(double SumOfPreviousLayer) { return tanh(SumOfPreviousLayer); }

	// Derivative of tanh(x) = 1 - tanh(x)^2
	static double ActivationFunctionDerivative(double tanhValue) { return 1 - pow(tanhValue, 2); }
public:
	Neuron(int numberOfConnections, int index)
	{
		this->numberOfConnections = numberOfConnections;
		this->index = index;
		outputValue = 0;
		for(int i = 0; i < numberOfConnections; ++i)
		{
			outputWeights.emplace_back(Connection());
		}
	};

	void SetOutputValue(const double outVal) { outputValue = outVal; }
	double GetOutputValue() const { return outputValue; }

	void FeedForward(const Layer& previousLayer)
	{
		double SumOfPreviousLayer = 0;

		for (const Neuron &neuron : previousLayer)
			SumOfPreviousLayer += neuron.GetOutputValue() * neuron.outputWeights[index].weight;

		outputValue = ActivationFunction(SumOfPreviousLayer);
	}

	
};

class Net
{
private:
	std::vector<int> topology;
	std::vector<Layer> layers;
public:
	Net(const std::vector<int> &topology)
	{
		this->topology = topology;

		for (int NumOfLayer = 0; NumOfLayer < topology.size(); ++NumOfLayer)
		{
			int numOfOutputs;
			if (NumOfLayer == topology.size() - 1) { numOfOutputs = 0;} //Last layer -> no output
			else numOfOutputs = topology[NumOfLayer + 1];

			Layer tmpLayer;
			for (int neuronNum = 0; neuronNum <= topology[NumOfLayer]; ++neuronNum)
				tmpLayer.emplace_back(Neuron(numOfOutputs, neuronNum));

			layers.emplace_back(tmpLayer);
		}
			
				
			
	}

	void FeedForward(const std::vector<double>& inputValues)
	{
		assert(inputValues.size() == layers[0].size() - 1);
		for (int i = 0; i < inputValues.size(); ++i)
			layers[0][i].SetOutputValue(inputValues[i]);

		for (int layerNum = 1; layerNum < layers.size(); ++layerNum)
			for (Neuron &neuron : layers[layerNum])
				neuron.FeedForward(layers[layerNum - 1]);
		//37:34
	};
	void BackPropagation(const std::vector<double>& targetValues);
	void GetResults(std::vector<double> resultValues) const;


};
