#include<iostream>

using namespace System;

using namespace System::Windows::Forms;

#include "NeuralNetMainGUI.h"
[STAThread]
int main(){

	int i = 1;
	if (i == 0)
	{
		const std::vector<int> topology = { 784,128,64,10 };
		NeuralNet DefaultNet(topology, 0.033665, 0.0889798, ActivationFunctions::ReLU);
		insertWeightsToNet(DefaultNet, "weights.txt");

		std::vector<std::vector<double>> testSamples = read_csv("test.csv");
		//std::vector<std::vector<double>> trainSamples = read_csv("train.csv");
		//TrainNetwork(DefaultNet, trainSamples);
		auto accuracy = testNetwork(DefaultNet, testSamples);
		std::cout << accuracy;
		//writeWeightsToFile(DefaultNet);

	}
	

	if(i == 1){
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		Application::Run(gcnew NeuralNetGUI::MainForm());
	}
	
	return 0;
	
}

