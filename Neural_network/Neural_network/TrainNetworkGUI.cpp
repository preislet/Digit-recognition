#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cassert>
#include<fstream>
#include<sstream>

#include "TrainNetworkGUI.h"

/*This function takes a managed System::String and converts it to an unmanaged std::string.
 It is used to convert the file path of an image from the OpenFileDialog component into a format that can be used by the C++ code.*/
void TrainGUI::TrainNetworkGUI::MarshalString(String^ s, std::string& os)
{
	using namespace Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}


System::Void TrainGUI::TrainNetworkGUI::button_Train_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (!(topologyInserted && alphaInserted && etaInserted && nameInserted && activationFunctionInserted)) return;
	std::vector<int> topology;

	std::string sAlpha;
	std::string sEta;
	std::string sTopology;
	MarshalString(textBox_alpha->Text, sAlpha);
	MarshalString(textBox_eta->Text, sEta);
	MarshalString(textBox_topology->Text, sTopology);
	
	ActivationFunctions activationFunction = static_cast<ActivationFunctions>(activationFunctionNum);
	double Alpha = std::stod(sAlpha);
	double Eta = std::stod(sEta);

	std::stringstream ss(sTopology);
	std::string tmp;
	while (getline(ss, tmp, ';'))
		topology.emplace_back(std::stoi(tmp));


	CustomNet.NeuralNetUpdate(topology, Eta, Alpha, activationFunction);

	std::vector<std::vector<double>> testSamples = read_csv("test.csv");
	std::vector<std::vector<double>> trainSamples = read_csv("train.csv");
	TrainNetwork(CustomNet, trainSamples);
	double accuracy = testNetwork(CustomNet, testSamples);

	label_accuracy->Text = "Accuracy: " + (accuracy * 100).ToString() + "%";
	button_SaveNetwork->Visible = true;
	button_SaveNetwork->Enabled = true;
}
System::Void TrainGUI::TrainNetworkGUI::button_SaveNetwork_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::string name;
	MarshalString(textBox_Name->Text, name);
	writeWeightsToFile(CustomNet, name);
	//TODO Ukladani vsech parametru
}
System::Void TrainGUI::TrainNetworkGUI::check_ActivationFunction_Click(System::Object^ sender, System::EventArgs^ e)
{
	for(int i = 1; i < 9; i++)
	{
		CheckBox^ checkBox = safe_cast<CheckBox^>(tableLayoutPanel_activationFunction->GetControlFromPosition(0, i));
		if (checkBox == sender && checkBox->Checked == true) activationFunctionNum = i - 1;
		if (checkBox == sender && checkBox->Checked == false) activationFunctionNum = 0;

		checkBox->Checked = false;
	}
	CheckBox^ checkBox = safe_cast<CheckBox^>(tableLayoutPanel_activationFunction->GetControlFromPosition(0, activationFunctionNum + 1));
	checkBox->Checked = true;
}
