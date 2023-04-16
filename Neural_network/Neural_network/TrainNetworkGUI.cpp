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
void TrainGUI::MarshalString(String^ s, std::string& os)
{
	using namespace Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}
void TrainGUI::TrainNetworkGUI::writeNeuralNetInfoToFile(const NeuralNet& CustomNet, const std::string& name)
{
	std::string fullpath = "Networks/" + name + "_info.txt";
	const std::wstring info_path(fullpath.begin(), fullpath.end());

	std::ofstream infoFile(info_path.c_str());

	std::vector<int>topology = CustomNet.GetTopology();
	std::string sTopology;
	double eta = CustomNet.eta;
	double alpha = CustomNet.alpha;
	ActivationFunctions ActFun = CustomNet.activationFunction;

	for (auto NumofNeuron : topology)
		sTopology += std::to_string(NumofNeuron) + ";";

	sTopology.pop_back();
	infoFile << sTopology << "\n";
	infoFile << eta << "\n";
	infoFile << alpha << "\n";
	infoFile << static_cast<std::underlying_type_t<ActivationFunctions>>(ActFun) << "\n" ;
}


System::Void TrainGUI::TrainNetworkGUI::button_Train_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::vector<int> topology;
	std::string sTopology;

	MarshalString(textBox_topology->Text, sTopology);
	try
	{
		std::stringstream ss(sTopology);
		std::string tmp;
		while (getline(ss, tmp, ';'))
			topology.emplace_back(std::stoi(tmp));
	}
	catch(...)
	{
		topologyInserted = false;
		textBox_topology->Text = "";
	}
	if(topology[0] != 784 && topology.back() != 10)
	{
		topologyInserted = false;
		textBox_topology->Text = "";
	}

	if (!(topologyInserted && alphaInserted && etaInserted && nameInserted && activationFunctionInserted)) return;

	std::string sAlpha;
	std::string sEta;
	MarshalString(textBox_alpha->Text, sAlpha);
	MarshalString(textBox_eta->Text, sEta);

	ActivationFunctions activationFunction = static_cast<ActivationFunctions>(activationFunctionNum);
	double Alpha = std::stod(sAlpha);
	double Eta = std::stod(sEta);

	CustomNet.NeuralNetUpdate(topology, Eta, Alpha, activationFunction);

	std::vector<std::vector<double>> testSamples = read_csv("test.csv");
	std::vector<std::vector<double>> trainSamples = read_csv("train.csv");
	TrainNetwork(CustomNet, trainSamples);
	double accuracy = testNetwork(CustomNet, testSamples);

	label_accuracy->Text = "Accuracy: " + (accuracy * 100).ToString() + "%";
	button_Train->Enabled = false;
	button_SaveNetwork->Visible = true;
	button_SaveNetwork->Enabled = true;
}
System::Void TrainGUI::TrainNetworkGUI::button_SaveNetwork_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::string name;
	MarshalString(textBox_Name->Text, name);
	writeNeuralNetInfoToFile(CustomNet, name);
	writeWeightsToFile(CustomNet, name + ".txt");
	this->Close();
}
System::Void TrainGUI::TrainNetworkGUI::check_ActivationFunction_Click(System::Object^ sender, System::EventArgs^ e)
{
	for (int i = 1; i < 10; i++)
	{
		CheckBox^ checkBox = safe_cast<CheckBox^>(tableLayoutPanel_activationFunction->GetControlFromPosition(0, i));
		if (checkBox == sender && checkBox->Checked == true) activationFunctionNum = i - 1;
		if (checkBox == sender && checkBox->Checked == false) activationFunctionNum = 0;

		checkBox->Checked = false;
	}
	CheckBox^ checkBox = safe_cast<CheckBox^>(tableLayoutPanel_activationFunction->GetControlFromPosition(0, activationFunctionNum + 1));
	checkBox->Checked = true;
	label_activationFunction->Text = "Activation Function: " + checkBox->Text;
}
System::Void TrainGUI::TrainNetworkGUI::textBox_Name_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	std::string name;
	MarshalString(textBox_Name->Text, name);

	if (name.size() > 0) nameInserted = true;
	else nameInserted = false;
}
System::Void TrainGUI::TrainNetworkGUI::textBox_alpha_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	std::string sAlpha;
	MarshalString(textBox_alpha->Text, sAlpha);
	double alpha;
	try
	{
		alpha = std::stod(sAlpha);
		alphaInserted = true;
	}
	catch (...)
	{
		alphaInserted = false;
		textBox_alpha->Text = "";
	}
}
System::Void TrainGUI::TrainNetworkGUI::textBox_topology_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	topologyInserted = true;
}
System::Void TrainGUI::TrainNetworkGUI::textBox_eta_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	std::string sEta;
	MarshalString(textBox_eta->Text, sEta);
	double eta;
	try
	{
		eta = std::stod(sEta);
		etaInserted = true;
	}
	catch (...)
	{
		etaInserted = false;
		textBox_eta->Text = "";
	}
}

