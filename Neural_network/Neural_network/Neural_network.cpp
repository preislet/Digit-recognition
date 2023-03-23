#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cassert>

class Neuron;
using Layer = std::vector<Neuron>;

// eta 0,5, alpha 0.1 - 0,55
// eta 0,3, alpha 0.5 - 0,57
// eta 0,5, alpha 0.5 - 0,583
// eta 0,6, alpha 0.5 - 0,686
// eta 0,65, alpha 0.6 - 0.672
// eta 0,6, alpha 0.65 - 0.59
// eta 0,62, alpha 0.5 - 0.58
// eta 0,7, alpha 0.7 - 0.58
// eta 0,2, alpha 0,1 - 0,64
// eta 0,1, alpha 0,1 - 0,65 

/* Overall net training rate [0.0 ... 1.0]
	 * 0.0 - slow learner
	 * 0,2 - medium learner
	 * 1.0 - reckless learner
	 */
//constexpr static double eta = 0.3;

/* Momentum [0.0 ... n]
 * 0.0 - no momentum
 * 0.5 - moderate momentum
 */
//constexpr static double alpha = 0.1;

struct RMSError
{
	double error = 0;
	double recentAverageError = 0;
	double recentAverageSmoothingFactor = 100;
};

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
	static double RandomNumber() { return rand() / double(RAND_MAX); }
};

class Neuron
{
private:
	int numberOfConnections;
	int index;
	double eta;
	double alpha;

	double outputValue;
	double gradient;

	std::vector<Connection> outputWeights;

	static double ActivationFunction(double sumOfPreviousLayer) { return 1 / (1 + exp(-sumOfPreviousLayer)); }

	static double ActivationFunctionDerivative(double Value) { return (1 / (1 + exp(-Value))) * (1 - 1 / (1 + exp(-Value))); }

	double SumDerivationsOfWeightsOfNextLayer(const Layer& nextLayer) const
	{
		double SumOfDerivationsOfWeightsOfNextLayer = 0;
		for (unsigned int NeuronNum = 0; NeuronNum < nextLayer.size() - 1; ++NeuronNum)
			SumOfDerivationsOfWeightsOfNextLayer += outputWeights[NeuronNum].weight * nextLayer[NeuronNum].gradient;
		return SumOfDerivationsOfWeightsOfNextLayer;
	}
public:
	Neuron(int numberOfConnections, int index, double eta, double alpha)
	{
		this->numberOfConnections = numberOfConnections;
		this->index = index;
		this->eta = eta;
		this->alpha = alpha;
		outputValue = 0;
		gradient = 0;
		for (int i = 0; i < numberOfConnections; ++i)
		{
			outputWeights.emplace_back(Connection());
		}
	}

	void SetOutputValue(const double outVal) { outputValue = outVal; }
	double GetOutputValue() const { return outputValue; }

	void FeedForward(const Layer& previousLayer)
	{
		double sumOfPreviousLayer = 0;

		for (const Neuron& neuron : previousLayer)
			sumOfPreviousLayer += neuron.GetOutputValue() * neuron.outputWeights[index].weight;

		outputValue = ActivationFunction(sumOfPreviousLayer);
	}
	void CalculateOutputGradients(const double targetValue)
	{
		gradient = (targetValue - outputValue) * ActivationFunctionDerivative(outputValue);
	}
	void CalculateHiddenGradient(const Layer& nextLayer)
	{
		const double DerivativeOfWeightsOfNextLayer = SumDerivationsOfWeightsOfNextLayer(nextLayer);
		gradient = DerivativeOfWeightsOfNextLayer * ActivationFunctionDerivative(outputValue);
	}
	void UpdatedInputWeights(Layer& prevLayer) const
	{
		for (Neuron& neuron : prevLayer)
		{
			const double CurrentDeltaWeight = neuron.outputWeights[index].deltaWeight;
			const double NewDeltaWeight = eta * neuron.outputValue * gradient + alpha * CurrentDeltaWeight;

			neuron.outputWeights[index].deltaWeight = NewDeltaWeight;
			neuron.outputWeights[index].weight += NewDeltaWeight;
		}
	}
};

class Net
{
private:

	std::vector<int> topology;
	std::vector<Layer> layers;
	RMSError RMS_error;


	void CalculateRMS_error(const std::vector<double>& targetValues)
	{
		const Layer& outputLayer = layers[layers.size() - 1];

		const unsigned int NumOfOutputNeuronsWithoutBiasNeuron = layers[layers.size() - 1].size() - 1;

		for (unsigned int NumOfNeuron = 0; NumOfNeuron < NumOfOutputNeuronsWithoutBiasNeuron; ++NumOfNeuron)
			RMS_error.error += pow(targetValues[NumOfNeuron] - outputLayer[NumOfNeuron].GetOutputValue(), 2);

		RMS_error.error = sqrt(RMS_error.error / NumOfOutputNeuronsWithoutBiasNeuron);
	}
	void CalculateRecentAverageError()
	{
		RMS_error.recentAverageError = (RMS_error.recentAverageError * RMS_error.recentAverageSmoothingFactor + RMS_error.error) / (RMS_error.recentAverageSmoothingFactor + 1);
	}
	void CalculateOutputLayerGradients(const std::vector<double>& targetValues)
	{
		Layer& outputLayer = layers[layers.size() - 1];

		const unsigned int NumOfOutputNeuronsWithoutBiasNeuron = layers[layers.size() - 1].size() - 1;

		for (unsigned int NumOfNeuron = 0; NumOfNeuron < NumOfOutputNeuronsWithoutBiasNeuron; ++NumOfNeuron)
		{
			outputLayer[NumOfNeuron].CalculateOutputGradients(targetValues[NumOfNeuron]);
		}
	}
	void CalculateHiddenLayersGradients()
	{
		const unsigned int NumOfLayersWithoutOutputLayer = layers.size() - 2;

		for (unsigned int NumOfLayer = NumOfLayersWithoutOutputLayer; NumOfLayer > 0; --NumOfLayer)
		{
			Layer& CurrentHiddenLayer = layers[NumOfLayer];
			Layer& NextLayer = layers[NumOfLayer + 1];

			for (Neuron& neuron : CurrentHiddenLayer)
				neuron.CalculateHiddenGradient(NextLayer);
		}
	}
	void UpdateConnectionWeights()
	{
		for (unsigned int LayerNum = layers.size() - 1; LayerNum > 0; --LayerNum)
		{
			Layer& currentLayer = layers[LayerNum];
			Layer& previousLayer = layers[LayerNum - 1];

			for (unsigned int neuronNum = 0; neuronNum < currentLayer.size() - 1; ++neuronNum)
			{
				Neuron& neuron = currentLayer[neuronNum];
				neuron.UpdatedInputWeights(previousLayer);
			}
		}
	}
public:
	double AverageGetError() const
	{
		return RMS_error.recentAverageError;
	}
	Net(const std::vector<int>& topology, double eta, double alpha)
	{
		this->topology = topology;

		for (unsigned int NumOfLayer = 0; NumOfLayer < topology.size(); ++NumOfLayer)
		{
			int numOfOutputs;
			if (NumOfLayer == topology.size() - 1) { numOfOutputs = 0; } //Last layer -> no output
			else numOfOutputs = topology[NumOfLayer + 1];

			Layer tmpLayer;
			for (int neuronNum = 0; neuronNum <= topology[NumOfLayer]; ++neuronNum)
				tmpLayer.emplace_back(Neuron(numOfOutputs, neuronNum, eta, alpha));

			tmpLayer[tmpLayer.size() - 1].SetOutputValue(1.0); //OutputValue of BiasNeuron
			layers.emplace_back(tmpLayer);
		}
	}

	void FeedForward(const std::vector<double>& inputValues)
	{
		assert(inputValues.size() == layers[0].size() - 1);
		for (int i = 0; i < inputValues.size(); ++i)
			layers[0][i].SetOutputValue(inputValues[i]);

		for (unsigned int layerNum = 1; layerNum < layers.size(); ++layerNum)
			for (unsigned int NeuronNum = 0; NeuronNum < layers[layerNum].size() - 1; ++NeuronNum)
				layers[layerNum][NeuronNum].FeedForward(layers[layerNum - 1]);
	}

	void BackPropagation(const std::vector<double>& targetValues)
	{
		CalculateRMS_error(targetValues);
		CalculateRecentAverageError();

		CalculateOutputLayerGradients(targetValues);

		CalculateHiddenLayersGradients();

		UpdateConnectionWeights();
	}
	std::vector<double> GetResults() const
	{
		std::vector<double> resultValues;
		const Layer& outputLayer = layers[layers.size() - 1];
		for (const Neuron& neuron : outputLayer)
			resultValues.emplace_back(neuron.GetOutputValue());
		return resultValues;
	}


};