#include<iostream>

using namespace System;

using namespace System::Windows::Forms;

#include "MainForm.h"
[STAThread]
int main(){
/*
	const std::vector<int> topology = { 784,128,64,10 };
	NeuralNet DefaultNet(topology, 0.033665, 0.0889798);
	std::vector<std::vector<double>> testSamples = read_csv("test.csv");
	std::vector<std::vector<double>> trainSamples = read_csv("train.csv");
	TrainNetwork(DefaultNet, trainSamples);
	auto accuracy  = testNetwork(DefaultNet, testSamples, true);
	std::cout << accuracy;
	*/
	
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew NeuralNetGUI::MainForm());
	return 0;
	
}

