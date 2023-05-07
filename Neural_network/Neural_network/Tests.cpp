#include "Tests.hpp"
#include "Neural_network.hpp"
#include "Image_conversion.hpp"

#include <string>
#include<iostream>
#include <vector>
#include<sstream>

//function is used to call all the test functions
void Testing::RunAllTests()
{
	TestNeuralNetCtor();
	TestNeuralNetUpdate();
	TestGetWeights();
	TestInsertingWeights();
	TestWritingWeightsToFileANIinsertWeightsToNet();
}

/*his function tests the constructor of the NeuralNet class. It generates a random topology, alpha, eta, and activation function,
 creates a new NeuralNet object, and compares the results of calling the GetTopology(), eta, alpha, activationFunction, and GetLayers() methods with
 the expected values.*/
void Testing::TestNeuralNetCtor()
{
	bool topologyCheck = false;
	bool etaCheck = false;
	bool alphaCheck = false;
	bool actFunCheck = false;
	bool layerSizeCheck = false;


	std::vector<int> topology;
	for (int i = 0; i < 10; i++)
		topology.emplace_back(rand()/100);
	int alpha = rand();
	int eta = rand();
	ActivationFunctionsNum actFun = static_cast<ActivationFunctionsNum>(rand() % 10);

	NeuralNet TestNet(topology, eta, alpha, actFun);
	std::vector<int> layersSize;
	std::vector<Layer> layers = TestNet.GetLayers();
	for(const Layer &layer: layers)
	{
		layersSize.push_back(int(layer.size()));
	}

	if (topology == TestNet.GetTopology()) topologyCheck = true;
	if (eta == TestNet.eta) etaCheck = true;
	if (alpha == TestNet.alpha) alphaCheck = true;
	if (actFun == TestNet.activationFunction) actFunCheck = true;
	if (layersSize == topology) layerSizeCheck = true;


	if (topologyCheck&&etaCheck&&alphaCheck&&actFunCheck&&layerSizeCheck) std::cout << "Test NeuralNet ctor: Passed +" << std::endl;
	else std::cout << "Test NeuralNet ctor: Failed -" << std::endl;
	
}

/*This function tests the NeuralNetUpdate method of the NeuralNet class. It creates a random topology, alpha, eta, and activation function,
 creates a NeuralNet object using these values, then generates new random values for the same parameters. It then calls the NeuralNetUpdate method on the
 first NeuralNet object with the new values and compares the results of calling the GetTopology(), eta, alpha, activationFunction, and GetLayers() methods
 with the expected values.*/
void Testing::TestNeuralNetUpdate()
{
	std::vector<int> topology;
	for (int i = 0; i < 10; i++)
		topology.emplace_back(rand() / 100);
	int alpha = rand();
	int eta = rand();
	ActivationFunctionsNum actFun = static_cast<ActivationFunctionsNum>(rand() % 10);

	NeuralNet TestNet(topology, eta, alpha, actFun);


	std::vector<int> newTopology;
	for (int i = 0; i < 10; i++)
		newTopology.emplace_back(rand() / 100);
	int newAlpha = rand();
	int newEta = rand();
	ActivationFunctionsNum newActFun = static_cast<ActivationFunctionsNum>(rand() % 10);

	TestNet.NeuralNetUpdate(newTopology, newEta, newAlpha, newActFun);
	NeuralNet TestNet2(newTopology, newEta, newAlpha, newActFun);
	if (TestNet.eta == TestNet2.eta && TestNet.alpha == TestNet2.alpha && TestNet.GetTopology() == TestNet2.GetTopology() && TestNet.activationFunction == TestNet2.activationFunction)
	{
		std::cout << "Test NeuralNet update: Passed +" << std::endl;
	}
	else std::cout << "Test NeuralNet update: Failed +" << std::endl;


	
}

/*This function tests the GetWeights method of the NeuralNet class. It generates a random topology, creates a NeuralNet object with the topology and
 *default alpha, eta, and activation function values, and retrieves the weights using the GetWeights method. It then compares the retrieved weights with
 *the weights stored in the Layer objects retrieved using the GetLayers method.*/
void Testing::TestGetWeights()
{
	std::vector<int> topology;
	for (int i = 0; i < 10; i++)
		topology.emplace_back(rand() / 100);
	NeuralNet TestNet(topology, 0, 0, static_cast<ActivationFunctionsNum>(0));
	auto weights = TestNet.GetWeights();
	auto layers = TestNet.GetLayers();

	bool areSame = true;
	for(int i = 0; i < weights.size(); i++)
		for(int j = 0; j < weights[i].size();j++)
			for(int k =0; k < weights[i][j].size();k++)
			{
				const auto &NeuronWeights = layers[i][j].GetWeights();
				if (weights[i][j][k] != NeuronWeights[k])
				{
					areSame = false;
				}
			}
	if (areSame) std::cout << "Test NeuralNet Get weights: Passed +" << std::endl;
	else std::cout << "Test NeuralNet Get weights: Failed -" << std::endl;

}

/*This function tests the InsertWeights method of the NeuralNet class. It generates a random topology and creates a NeuralNet object with the topology
and default alpha, eta, and activation function values. It then generates a set of random weights and inserts them into the NeuralNet object using the
InsertWeights method. Finally, it retrieves the inserted weights using the GetWeights method and compares them with the expected weights.*/
void Testing::TestInsertingWeights()
{
	
	std::vector<int> topology;
	for (int i = 0; i < 10; i++)
		topology.emplace_back(rand() / 100);
	std::vector<std::vector<std::vector<double>>> weights;
	for(int layer = 0; layer < topology.size() - 1; layer++)
	{
		std::vector<std::vector<double>> LayerConnections;
		for(int neuron = 0; neuron < topology[layer]; neuron++)
		{
			std::vector<double> NeuronConnections;
			for(int connection = 0; connection < topology[layer + 1]; connection++)
			{
				double weight = rand() % 10;
				NeuronConnections.emplace_back(weight);
			}
			LayerConnections.emplace_back(NeuronConnections);
		}
		weights.emplace_back(LayerConnections);
	}
	
	NeuralNet TestNet(topology, 0, 0, static_cast<ActivationFunctionsNum>(0));
	TestNet.InsertWeights(weights);

	std::vector<std::vector<std::vector<double>>> outputWeights = TestNet.GetWeights();

	
	bool areSame = true;
	for (int i = 0; i < outputWeights.size() - 1; i++)
		for (int j = 0; j < outputWeights[i].size();j++)
			for (int k = 0; k < outputWeights[i][j].size(); k++)
				if (outputWeights[i][j][k] != weights[i][j][k]) areSame = false;
				
		
	if (areSame) std::cout << "Test NeuralNet Inserting Weights: Passed +" << std::endl;
	else std::cout << "Test NeuralNet Inserting Weights: Failed -" << std::endl;
	
}

/*
 This function tests the WriteWeightsToFile and InsertWeights methods of the NeuralNet class. It creates a NeuralNet object with a small topology, generates
 some random weights, writes them to a file using the WriteWeightsToFile method, reads them back using the InsertWeights method, and finally, retrieves the
 inserted weights using the GetWeights method and compares them with the expected values.
 */
void Testing::TestWritingWeightsToFileANIinsertWeightsToNet()
{

	std::vector<int> topology;
	for (int i = 0; i < 3; i++)
		topology.emplace_back(rand() / 1000);
	NeuralNet TestNet(topology, 0, 0, static_cast<ActivationFunctionsNum>(0));
	auto preWeights = TestNet.GetWeights();
	writeWeightsToFile(TestNet, "TestingWritingWeightsToFile");
	insertWeightsToNet(TestNet, "TestingWritingWeightsToFile");
	auto postWeights = TestNet.GetWeights();

	bool areSame = true;
	for (int i = 0; i < postWeights.size(); i++)
		for (int j = 0; j < postWeights[i].size();j++)
			for (int k = 0; k < postWeights[i][j].size(); k++)
			{
				double diff = preWeights[i][j][k] - postWeights[i][j][k];
				if(diff > 0.00000001) areSame = false;
			}
				


	if(areSame) std::cout << "Test Write weights to file and inserting them back: Passed +" << std::endl;
	else std::cout << "Test Write weights to file and inserting them back: Failed -" << std::endl;

	remove("TestingWritingWeightsToFile");
}


