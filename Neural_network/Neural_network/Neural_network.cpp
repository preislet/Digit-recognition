#define _USE_MATH_DEFINES
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cassert>
#include<fstream>
#include<sstream>
#include<cmath>
#include<memory>

#include "Neural_network.hpp"

class Neuron;
class NeuralNet;
using Layer = std::vector<Neuron>;

//Constructor for the Connection class, which initializes the weight of the connection to a random value and sets the delta weight to 0.
::Connection::Connection()
{
	this->weight = RandomNumber() / 1000;
	this->deltaWeight = 0;
}

//Helper function that generates a random number between 0 and 1 for use in initializing connection weights.
double ::Connection::RandomNumber() { return rand() / double(RAND_MAX); }

double::ActivationFunctionSigmoid::EvaluateActivationFunction(double& value, double& gradient) {
	return 1 / (1 + exp(-value));
}
double::ActivationFunctionSigmoid::EvaluateActivationFunctionDerivative(double& value, double& gradient) {
	return (1 / (1 + exp(-value))) * (1 - (1 / (1 + exp(-value))));
}
double::ActivationFunctionTanh::EvaluateActivationFunction(double& value, double& gradient) {
	return tanh(value);
}
double::ActivationFunctionTanh::EvaluateActivationFunctionDerivative(double& value, double& gradient) {
	return 1 - (tanh(value) * tanh(value));
}
double::ActivationFunctionReLU::EvaluateActivationFunction(double& value, double& gradient) {
	return std::max(value, 0.0);
}
double::ActivationFunctionReLU::EvaluateActivationFunctionDerivative(double& value, double& gradient) {
	return value >= 0 ? 1 : 0;
}
double::ActivationFunctionLeakyReLU::EvaluateActivationFunction(double& value, double& gradient) {
	return value > 0 ? value : 0.01 * value;
}
double::ActivationFunctionLeakyReLU::EvaluateActivationFunctionDerivative(double& value, double& gradient) {
	return value >= 0 ? 1 : 0.01;
}
double::ActivationFunctionParametricReLU::EvaluateActivationFunction(double& value, double& gradient) {
	return std::max(PARAMETER_FOR_ParametricReLU * value, 0.0);
}
double::ActivationFunctionParametricReLU::EvaluateActivationFunctionDerivative(double& value, double& gradient) {
	return value >= 0 ? 1 : PARAMETER_FOR_ParametricReLU;
}
double::ActivationFunctionELU::EvaluateActivationFunction(double& value, double& gradient) {
	return value > 0 ? value : PARAMETER_FOR_ELU * (exp(value) - 1);
}
double::ActivationFunctionELU::EvaluateActivationFunctionDerivative(double& value, double& gradient) {
	return value >= 0 ? 1 : EvaluateActivationFunction(value, gradient) - PARAMETER_FOR_ELU;
}
double::ActivationFunctionSwish::EvaluateActivationFunction(double& value, double& gradient) {
	return value / (1 + exp(-value));
}
double::ActivationFunctionSwish::EvaluateActivationFunctionDerivative(double& value, double& gradient) {
	return (EvaluateActivationFunction(value, gradient) + (1 / (1 + exp(-value))) * (1 - EvaluateActivationFunction(value, gradient)));
}
double::ActivationFunctionSELU::EvaluateActivationFunction(double& value, double& gradient) {
	return value > 0 ? value : gradient * (exp(value) - 1);
}
double::ActivationFunctionSELU::EvaluateActivationFunctionDerivative(double& value, double& gradient) {
	return value >= 0 ? 1 : EvaluateActivationFunction(value, gradient) - gradient;
}
double::ActivationFunctionGELU::EvaluateActivationFunction(double& value, double& gradient) {
	return 0.5 * value * (1 + erf(value / sqrt(2)));
}
double::ActivationFunctionGELU::EvaluateActivationFunctionDerivative(double& value, double& gradient) {
	return (0.5 * erf(value / sqrt(2)) + 0.398942 * value * exp(pow(-value, 2)) + 0.5);
}


/*Constructor for the Neuron class, which takes as arguments the number of connections to the next layer, the index of the neuron in the current layer,
 and the learning rate (eta) and momentum (alpha) values. It initializes the neuron's output value and gradient to 0, and creates a vector of output weights
 with random initial weights.*/
::Neuron::Neuron(int numberOfConnections, int index, double eta, double alpha, ActivationFunctionsNum activationFunctionName, const std::shared_ptr<std::vector<std::unique_ptr<ActivationFunctionBase>>>& ActivationFunctions)
{
	this->numberOfConnections = numberOfConnections;
	this->index = index;
	this->eta = eta;
	this->alpha = alpha;
	this->activationFunctionName = activationFunctionName;
	this->ActivationFunctions = ActivationFunctions;
	inputValue = 0;
	outputValue = 0;
	gradient = 0;
	for (int i = 0; i < numberOfConnections; ++i)
	{
		outputWeights.emplace_back(Connection());
	}
}

//Setter function for the output value of a neuron.
void Neuron::SetOutputValue(const double outVal) { outputValue = outVal; }

//Calculates the output value of a neuron based on the weighted sum of the previous layer's output values and the neuron's activation function.
void Neuron::FeedForward(const Layer& previousLayer)
{
	double sumOfPreviousLayer = 0;

	for (const Neuron& neuron : previousLayer)
		sumOfPreviousLayer += neuron.GetOutputValue() * neuron.outputWeights[index].weight;

	inputValue = sumOfPreviousLayer + BIAS;
	outputValue = ActivationFunction(sumOfPreviousLayer);
}

//Calculates the gradient of a neuron's output value based on the difference between the target output value and the actual output value, multiplied by the derivative of the neuron's activation function.
void Neuron::CalculateOutputGradients(const double targetValue) { gradient = (targetValue - outputValue) * ActivationFunctionDerivative(inputValue); }

/*Calculates the gradient of a hidden neuron's output value based on the sum of the derivatives of the weights of the next layer multiplied by the gradients of the neurons in the next layer,
 all multiplied by the derivative of the neuron's activation function.*/
void Neuron::CalculateHiddenGradient(const Layer& nextLayer)
{
	const double DerivativeOfWeightsOfNextLayer = SumDerivationsOfWeightsOfNextLayer(nextLayer);
	gradient = DerivativeOfWeightsOfNextLayer * ActivationFunctionDerivative(inputValue);
}

/*Updates the weights of the connections between the previous layer and the neuron, based on the neuron's gradient and the output value of the previous layer neurons,
 using the learning rate (eta) and momentum (alpha) values.*/
void Neuron::UpdatedInputWeights(Layer& prevLayer) const
{
	for (Neuron& neuron : prevLayer)
	{
		const double CurrentDeltaWeight = neuron.outputWeights[index].deltaWeight;
		const double NewDeltaWeight = eta * neuron.outputValue * gradient + alpha * CurrentDeltaWeight;

		neuron.outputWeights[index].deltaWeight = NewDeltaWeight;
		neuron.outputWeights[index].weight += NewDeltaWeight;
	}
}

//Inserts weights to outputWeights vector 
void Neuron::InsertWeights(const std::vector<double>& weight)
{
	for (size_t i = 0; i < weight.size(); ++i)
		outputWeights[i].weight = weight[i];
}

double Neuron::ActivationFunction(double sumOfPreviousLayer){
	return ActivationFunctions->at(static_cast<int>(activationFunctionName))->EvaluateActivationFunction(sumOfPreviousLayer, gradient);
}

double Neuron::ActivationFunctionDerivative(double Value) {
	return ActivationFunctions->at(static_cast<int>(activationFunctionName))->EvaluateActivationFunctionDerivative(Value, gradient);
}

//Calculates the sum of the derivatives of the weights of the next layer for a neuron.
double Neuron::SumDerivationsOfWeightsOfNextLayer(const Layer& nextLayer) const
{
	double SumOfDerivationsOfWeightsOfNextLayer = 0;
	for (unsigned int NeuronNum = 0; NeuronNum < nextLayer.size(); ++NeuronNum)
		SumOfDerivationsOfWeightsOfNextLayer += outputWeights[NeuronNum].weight * nextLayer[NeuronNum].gradient;
	return SumOfDerivationsOfWeightsOfNextLayer;
}

//Getter function for the output value of a neuron.
double Neuron::GetOutputValue() const { return outputValue; }
std::vector<double> Neuron::GetWeights() const
{
	std::vector<double> neuronWeights;
	neuronWeights.reserve(outputWeights.size());
	for (const auto& connection : outputWeights)
	{
		neuronWeights.push_back(connection.weight);
	}
	return neuronWeights;
}


NeuralNet::NeuralNet() {}
/*Constructor for the NeuralNet class, which takes as argument a vector of integers specifying the number of neurons in each layer, and the learning rate (eta) and momentum (alpha) values.
 It creates the layers of neurons, initializing the weights of the output connections randomly, and sets the output value of the bias neuron in each layer to 1.0.*/
NeuralNet::NeuralNet(const std::vector<int>& topology, double eta, double alpha, ActivationFunctionsNum activationFunction)
{
	this->alpha = alpha;
	this->eta = eta;
	this->activationFunction = activationFunction;
	this->topology = topology;

	if (!ActivationFunctionsLoadedCorrectly()) {
		ActivationFunctions->push_back(std::make_unique<ActivationFunctionSigmoid>());
		ActivationFunctions->push_back(std::make_unique<ActivationFunctionTanh>());
		ActivationFunctions->push_back(std::make_unique<ActivationFunctionReLU>());
		ActivationFunctions->push_back(std::make_unique<ActivationFunctionLeakyReLU>());
		ActivationFunctions->push_back(std::make_unique<ActivationFunctionParametricReLU>());
		ActivationFunctions->push_back(std::make_unique<ActivationFunctionELU>());
		ActivationFunctions->push_back(std::make_unique<ActivationFunctionSwish>());
		ActivationFunctions->push_back(std::make_unique<ActivationFunctionGELU>());
		ActivationFunctions->push_back(std::make_unique<ActivationFunctionSELU>());
		if (!ActivationFunctionsLoadedCorrectly()) {
			throw std::runtime_error("Activation functions not loaded correctly");
		}
	}

	for (unsigned int NumOfLayer = 0; NumOfLayer < topology.size(); ++NumOfLayer)
	{
		int numOfOutputs;
		if (NumOfLayer == topology.size() - 1) { numOfOutputs = 0; } //Last layer -> no output
		else numOfOutputs = topology[NumOfLayer + 1];

		Layer tmpLayer;
		for (int neuronNum = 0; neuronNum < topology[NumOfLayer]; ++neuronNum)
			tmpLayer.emplace_back(Neuron(numOfOutputs, neuronNum, eta, alpha, activationFunction, ActivationFunctions));

		layers.emplace_back(tmpLayer);
	}
}
void NeuralNet::NeuralNetUpdate(const std::vector<int>& topology, double eta, double alpha, ActivationFunctionsNum activationFunction)
{
	this->alpha = alpha;
	this->eta = eta;
	this->activationFunction = activationFunction;
	this->topology = topology;

	layers.clear();
	RMS_error.error = 0;
	RMS_error.recentAverageError = 0;
	RMS_error.recentAverageSmoothingFactor = 100;

	
	if (!ActivationFunctionsLoadedCorrectly()) {
		ActivationFunctions->push_back(std::make_unique<ActivationFunctionSigmoid>());
		ActivationFunctions->push_back(std::make_unique<ActivationFunctionTanh>());
		ActivationFunctions->push_back(std::make_unique<ActivationFunctionReLU>());
		ActivationFunctions->push_back(std::make_unique<ActivationFunctionLeakyReLU>());
		ActivationFunctions->push_back(std::make_unique<ActivationFunctionParametricReLU>());
		ActivationFunctions->push_back(std::make_unique<ActivationFunctionELU>());
		ActivationFunctions->push_back(std::make_unique<ActivationFunctionSwish>());
		ActivationFunctions->push_back(std::make_unique<ActivationFunctionGELU>());
		ActivationFunctions->push_back(std::make_unique<ActivationFunctionSELU>());
		if (!ActivationFunctionsLoadedCorrectly()) {
			throw std::runtime_error("Activation functions not loaded correctly");
		}
	}
	
	

	for (unsigned int NumOfLayer = 0; NumOfLayer < topology.size(); ++NumOfLayer)
	{
		int numOfOutputs;
		if (NumOfLayer == topology.size() - 1) { numOfOutputs = 0; } //Last layer -> no output
		else numOfOutputs = topology[NumOfLayer + 1];

		Layer tmpLayer;
		for (int neuronNum = 0; neuronNum < topology[NumOfLayer]; ++neuronNum)
			tmpLayer.emplace_back(Neuron(numOfOutputs, neuronNum, eta, alpha, activationFunction, ActivationFunctions));

		layers.emplace_back(tmpLayer);
	}
	
}

bool NeuralNet::ActivationFunctionsLoadedCorrectly() const
{
		return ActivationFunctions->size() == static_cast<int>(ActivationFunctionsNum::COUNT_);
}
//Calculates the root mean square (RMS) error between the output values of the network and the target output values.
void NeuralNet::CalculateRMS_error(const std::vector<double>& targetValues)
{
	const Layer& outputLayer = layers[layers.size() - 1];

	for (unsigned int NumOfNeuron = 0; NumOfNeuron < outputLayer.size(); ++NumOfNeuron)
		RMS_error.error += pow(targetValues[NumOfNeuron] - outputLayer[NumOfNeuron].GetOutputValue(), 2);

	RMS_error.error = sqrt(RMS_error.error / outputLayer.size());
}

//Calculates a rolling average of the RMS error over the most recent iterations, using a smoothing factor to weight the contributions of each iteration.
void NeuralNet::CalculateRecentAverageError()
{
	RMS_error.recentAverageError = (RMS_error.recentAverageError * RMS_error.recentAverageSmoothingFactor + RMS_error.error) / (RMS_error.recentAverageSmoothingFactor + 1);
}

/*Calculates the gradients of the output neurons in the network, based on the difference between the target output values and the actual output values,
 multiplied by the derivative of the activation function.*/
void NeuralNet::CalculateOutputLayerGradients(const std::vector<double>& targetValues)
{
	Layer& outputLayer = layers[layers.size() - 1];

	for (unsigned int NumOfNeuron = 0; NumOfNeuron < outputLayer.size(); ++NumOfNeuron)
		outputLayer[NumOfNeuron].CalculateOutputGradients(targetValues[NumOfNeuron]);

}

/*Calculates the gradients of the hidden neurons in the network, based on the derivatives of the weights of the next layer and the gradients of the neurons in the next layer, multiplied by the derivative of the activation function.
It calls the CalculateHiddenGradient() function for each hidden neuron in each hidden layer of the network.*/
void NeuralNet::CalculateHiddenLayersGradients()
{
	const unsigned int NumOfLayersWithoutOutputLayer = int(layers.size() - 2);

	for (unsigned int NumOfLayer = NumOfLayersWithoutOutputLayer; NumOfLayer > 0; --NumOfLayer)
	{
		Layer& CurrentHiddenLayer = layers[NumOfLayer];
		Layer& NextLayer = layers[NumOfLayer + 1];

		for (Neuron& neuron : CurrentHiddenLayer)
			neuron.CalculateHiddenGradient(NextLayer);
	}
}

/*This function updates the weights of the neural network based on the calculated gradients and the learning rate.
 *It uses the back propagation algorithm to adjust the weights in the direction that minimizes the error.*/
void NeuralNet::UpdateConnectionWeights()
{
	for (unsigned int LayerNum = int(layers.size() - 1); LayerNum > 0; --LayerNum)
	{
		Layer& currentLayer = layers[LayerNum];
		Layer& previousLayer = layers[LayerNum - 1];

		for (unsigned int neuronNum = 0; neuronNum < currentLayer.size(); ++neuronNum)
		{
			Neuron& neuron = currentLayer[neuronNum];
			neuron.UpdatedInputWeights(previousLayer);
		}
	}
}
void NeuralNet::InsertWeights(const std::vector<std::vector<std::vector<double>>>& weights)
{
	for (size_t layerIndex = 0; layerIndex < layers.size() - 1; ++layerIndex)
	{
		for (size_t NeuronIndex = 0; NeuronIndex < layers[layerIndex].size(); ++NeuronIndex)
		{
			layers[layerIndex][NeuronIndex].InsertWeights(weights[layerIndex][NeuronIndex]);
		}
	}
}

//Feeds forward the input values through the network, calculating the output values for each neuron using the FeedForward() function.
void NeuralNet::FeedForward(const std::vector<double>& inputValues)
{
	assert(inputValues.size() == layers[0].size());
	for (int i = 0; i < inputValues.size(); ++i)
		layers[0][i].SetOutputValue(inputValues[i]);

	for (unsigned int layerNum = 1; layerNum < layers.size(); ++layerNum)
		for (unsigned int NeuronNum = 0; NeuronNum < layers[layerNum].size(); ++NeuronNum)
			layers[layerNum][NeuronNum].FeedForward(layers[layerNum - 1]);
}
void NeuralNet::BackPropagation(const std::vector<double>& targetValues)
{
	CalculateRMS_error(targetValues);
	CalculateRecentAverageError();

	CalculateOutputLayerGradients(targetValues);

	CalculateHiddenLayersGradients();

	UpdateConnectionWeights();
}
std::vector<std::vector<std::vector<double>>> NeuralNet::GetWeights() const
{
	std::vector<std::vector<std::vector<double>>> allWeights;
	for (const auto& layer : layers)
	{
		std::vector<std::vector<double>> layerWeights;
		for (const auto& neuron : layer)
		{
			std::vector<double> neuronWeights = neuron.GetWeights();
			layerWeights.emplace_back(neuronWeights);
		}
		allWeights.emplace_back(layerWeights);
	}
	return allWeights;
}

/*This function returns the topology of the neural network as a vector. The first element of the vector is the number of input neurons,
 *the last element is the number of output neurons, and all other elements are the number of neurons in each hidden layer.*/
std::vector<int> NeuralNet::GetTopology() const
{
	return topology;
}

double NeuralNet::AverageGetError() const { return RMS_error.recentAverageError; }

//Return final values stored in output neurons
std::vector<double> NeuralNet::GetResults() const
{
	std::vector<double> resultValues;
	const Layer& outputLayer = layers[layers.size() - 1];
	for (const Neuron& neuron : outputLayer)
		resultValues.emplace_back(neuron.GetOutputValue());
	return resultValues;
}

std::vector<Layer> NeuralNet::GetLayers() const
{
	return layers;
}


/*This function takes in several parameters related to a neural network and prints them to the console.
 It first prints the expected label and the network output index, followed by the exact probability values obtained from the network.
 It then prints the average error and a blank line. Finally, if the boolean parameter printNumber is true, it prints the input values as a IMAGE_DIMENSIONxIMAGE_DIMENSION grid of characters
 ('S' for non-zero values and ' ' for zero values)*/
void NetworksTraining::printValues(const int label, const ptrdiff_t index, const std::vector<double>& resultValues, const std::vector<double>& inputValues, const double averageError, const bool printNumber) const
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

	for (int i = 0; i < IMAGE_DIMENSION; ++i)
	{
		for (int j = 0; j < IMAGE_DIMENSION; ++j)
		{
			if (inputValues[IMAGE_DIMENSION * i + j] == 0.0) std::cout << " ";
			else std::cout << "S";
		}
		std::cout << std::endl;
	}

	std::cout << "=========================================================" << std::endl;
}

/*This function takes in a reference to a NeuralNet object (a neural network) and a vector of input training samples, and updates the network's weights using back propagation.
 For each sample in the vector, it extracts the label and target values, feeds the input forward through the network, and performs back propagation to update the weights based on the
 error between the output and target values.*/
void NetworksTraining::TrainNetwork(::NeuralNet& MyNetwork, std::vector<std::vector<double>>& trainSamples) const
{
	for (auto& trainSample : trainSamples)
	{
		const int label = int(trainSample[0]);

		std::vector<double> targetValues(10, 0.0);
		targetValues[label] = 1.0;
		trainSample.erase(trainSample.begin());

		MyNetwork.FeedForward(trainSample);
		MyNetwork.BackPropagation(targetValues);
	}
}

/*This function takes in a reference to a NeuralNet object (a neural network), a vector of input test samples, and a boolean flag indicating whether to print the test results.
 It iterates through the test samples, extracts the label and target values, feeds the input forward through the network, and compares the network's output to the true label
 to count the number of correct predictions. If the print flag is true, it also calls the */
double NetworksTraining::testNetwork(::NeuralNet& MyNetwork, std::vector<std::vector<double>>& testSamples, bool print) const
{
	std::vector<std::vector<int>> corrects(10, std::vector<int>(2, 0));
	double correct_predictions = 0.0;
	for (auto& testSample : testSamples)
	{
		const int label = int(testSample[0]);

		std::vector<double> targetValues(10, 0.0);
		targetValues[label] = 1.0;
		corrects[label][0]++;
		testSample.erase(testSample.begin());
		MyNetwork.FeedForward(testSample);
		std::vector<double> resultValues = MyNetwork.GetResults();

		//resultValues.pop_back();
		const auto max_element = std::max_element(resultValues.begin(), resultValues.end());
		const auto max_element_index = std::distance(resultValues.begin(), max_element);
		if (label == max_element_index) {
			correct_predictions += 1.0;
			corrects[label][1]++;
		}

		if (print) printValues(label, max_element_index, resultValues, testSample, MyNetwork.AverageGetError(), true);
	}
	std::cout << correct_predictions / testSamples.size() << std::endl;
	return correct_predictions / testSamples.size();
}

/*his function takes in a file path and reads in a CSV file containing input data for a neural network.
 It returns a vector of vectors of doubles, where each inner vector corresponds to a row of data in the CSV file.*/
std::vector<std::vector<double>> FileHandler::read_csv(const std::string& path) const
{
	std::ifstream CSV_File(path);
	std::string line;

	std::vector<std::vector<double>> result;
	result.emplace_back();
	if (CSV_File.good()) std::getline(CSV_File, line); //extract names of column

	while (std::getline(CSV_File, line))
	{
		std::stringstream ss(line);
		std::string tmp;

		std::getline(ss, tmp, ',');
		double tmp_int = std::stod(tmp);
		result.back().emplace_back(tmp_int);

		while (std::getline(ss, tmp, ','))
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

/*his function takes in a NeuralNet object and writes its weights to a text file in a specific format.
 The weights are stored in a 3D vector, where each layer of the network is a matrix of weights between neurons.
 The function iterates through the layers and matrices of weights, writing each weight to a new line in the file.*/
void FileHandler::writeWeightsToFile(const NeuralNet& MyNetwork, const std::string& path = "weights.txt") const
{
	std::string fullpath = "Networks/" + path;
	const std::wstring weights_path(fullpath.begin(), fullpath.end());

	std::ofstream outputFile(weights_path.c_str());
	const auto outputWeightsVector = MyNetwork.GetWeights();
	if (outputFile.is_open())
	{
		for (size_t i = 0; i < outputWeightsVector.size(); i++)
		{
			for (size_t j = 0; j < outputWeightsVector[i].size(); j++)
			{
				for (size_t k = 0; k < outputWeightsVector[i][j].size(); k++)
				{
					outputFile << outputWeightsVector[i][j][k];
					if (k < outputWeightsVector[i][j].size() - 1)
					{
						outputFile << " ";
					}
				}
				outputFile << "\n";
			}
		}
		outputFile.close();
	}
	else
	{
		std::cout << "Unable to open file!" << std::endl;
	}
}
/*This function takes in a NeuralNet object and reads in a text file containing weights in the same format as written by writeWeightsToFile.
 It extracts the weights from the file and inserts them into the NeuralNet object, replacing the existing weights. It assumes that the topology of the NeuralNet object matches the topology used to
 write the weights to the file.*/
void FileHandler::insertWeightsToNet(NeuralNet& MyNetwork, const std::string& path = "weights.txt") const
{
	std::string fullpath = "Networks/" + path;
	const std::wstring weights_path(fullpath.begin(), fullpath.end());

	std::ifstream weightsFile(weights_path.c_str());
	std::string line;
	std::vector<std::vector<std::vector<double>>> weights;
	std::vector<int> Net_topology = MyNetwork.GetTopology();
	Net_topology.pop_back();
	for (auto topology : Net_topology)
	{
		std::vector<std::vector<double>> layer;
		for (size_t i = 0; i < topology; ++i)
		{
			std::vector<double> neuron;
			std::getline(weightsFile, line);
			std::stringstream ss(line);
			while (getline(ss, line, ' '))
			{
				neuron.emplace_back(std::stod(line));
			}
			layer.emplace_back(neuron);
		}
		weights.emplace_back(layer);
	}
	MyNetwork.InsertWeights(weights);
	weightsFile.close();
}