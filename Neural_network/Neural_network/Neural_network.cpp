#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<hash_map>
#include<memory>
#include<cassert>

class Neuron;
typedef std::vector<Neuron> Layer;

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
	int NumberOfConnections;
	double outputValue;
	std::vector<Connection> outputWeights;
public:
	Neuron(int NumberOfConnections)
	{
		this->NumberOfConnections = NumberOfConnections;
		outputValue = 0;
		for(int i = 0; i < NumberOfConnections; ++i)
		{
			outputWeights.emplace_back(Connection());
		}
	};

	void SetOutputValue(const double outVal) { outputValue = outVal; }
	double GetOutputValue() const { return outputValue; }

	void FeedForward(std::unique_ptr<Layer> layerPtr)
	{
		
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
			for (int i = 0; i <= topology[NumOfLayer]; ++i)
				tmpLayer.emplace_back(Neuron(numOfOutputs));

			layers.emplace_back(tmpLayer);
		}
			
				
			
	}

	void FeedForward(const std::vector<double>& inputValues)
	{
		assert(inputValues.size() == layers[0].size() - 1);
		for (int i = 0; i < inputValues.size(); ++i)
			layers[0][i].SetOutputValue(inputValues[i]);

		for (int layerNum = 1; layerNum < layers.size(); ++layerNum)
			for (Neuron neuron : layers[layerNum])
				neuron.FeedForward(std::make_unique<Layer>(layers[layerNum]));
		//37:34
	};
	void BackPropagation(const std::vector<double>& targetValues);
	void GetResults(std::vector<double> resultValues) const;


};
