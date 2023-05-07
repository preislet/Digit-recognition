#include "NeuralNetMainGUI.h"

#include <string>
#include<iostream>
#include <vector>
#include<sstream>

#include "Image_conversion.hpp"
#include "Neural_network.hpp"

#include "TrainNetworkGUI.h"
#using <System.dll>
#using <System.Drawing.dll>

using namespace System::Runtime::InteropServices;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

// This is the constructor for the MainForm class which is responsible for initializing the form's components and setting up the drawing canvas.
NeuralNetGUI::MainForm::MainForm(void)
{
	InitializeComponent();
	fileHandler.insertWeightsToNet(DefaultNet, "weights.txt");
	int numOfColumns = tableLayoutPanel_draw->ColumnCount;
	int numOfRows = tableLayoutPanel_draw->RowCount;
	for (int i = 0; i < numOfColumns; ++i)
		for (int j = 0; j < numOfRows; ++j)
		{
			Label^ b = gcnew System::Windows::Forms::Label();
			b->Text = "";
			b->Name = "button_" + i + "_" + j;
			b->BackColor = System::Drawing::SystemColors::Control;
			b->Click += gcnew System::EventHandler(this, &MainForm::labelDrawClick);
			tableLayoutPanel_draw->Controls->Add(b, i, j);
		}
}

// This is the destructor for the MainForm class, which is responsible for freeing up any allocated memory when the form is closed.
NeuralNetGUI::MainForm::~MainForm() { if (components) delete components; }

int NeuralNetGUI::MainForm::returnTopBorder(int rows, int columns)
{
	int corner = 0;
	for (int i = 0; i < rows; i++)
	{
		bool changed = false;
		for (int j = 0; j < columns; j++)
			if (tableLayoutPanel_draw->GetControlFromPosition(j, i)->BackColor == System::Drawing::SystemColors::Desktop) {
				corner = i;
				changed = true;
				break;
			}
		if (changed) break;
	}
	return corner;
}
int NeuralNetGUI::MainForm::returnBottomBorder(int rows, int columns)
{
	int corner = 0;
	for (int i = rows - 1; i >= 0; --i)
	{
		bool changed = false;
		for (int j = 0; j < columns; j++)
			if (tableLayoutPanel_draw->GetControlFromPosition(j, i)->BackColor == System::Drawing::SystemColors::Desktop) {
				corner = IMAGE_DIMENSION - 1 - i;
				changed = true;
				break;
			}
		if (changed) break;
	}
	return corner;
}
int NeuralNetGUI::MainForm::returnLeftBorder(int rows, int columns)
{
	int corner = 0;
	for (int j = 0; j < columns; j++)
	{
		bool changed = false;
		for (int i = 0; i < rows; i++)
			if (tableLayoutPanel_draw->GetControlFromPosition(j, i)->BackColor == System::Drawing::SystemColors::Desktop) {
				corner = j;
				changed = true;
				break;
			}
		if (changed) break;
	}
	return corner;
}
int NeuralNetGUI::MainForm::returnRightBorder(int rows, int columns)
{
	int corner = 0;
	for (int j = columns - 1; j >= 0; --j)
	{
		bool changed = false;
		for (int i = 0; i < rows; i++)
			if (tableLayoutPanel_draw->GetControlFromPosition(j, i)->BackColor == System::Drawing::SystemColors::Desktop) {
				corner = IMAGE_DIMENSION - 1 - j;
				changed = true;
				break;
			}
		if (changed) break;
	}
	return corner;
}
void NeuralNetGUI::MainForm::SumScoresPrediction(const std::vector<std::vector<double>>& AllResults)
{
	std::vector<double> resultValues(10, 0.0);
	for (const std::vector<double>& resultVector : AllResults)
	{
		for (int i = 0; i < resultVector.size(); ++i)
			resultValues[i] += resultVector[i];
	}

	const auto max_elem = std::max_element(resultValues.begin(), resultValues.end());
	const auto max_index = std::distance(resultValues.begin(), max_elem);

	label_result->Text = max_index.ToString();

	fillOutputTable(resultValues);
}
void NeuralNetGUI::MainForm::HighestScorePrediction(const std::vector<std::vector<double>>& AllResults)
{
	double max_element = 0;
	int max_index = 0;
	for (const std::vector<double>& resultVector : AllResults)
	{
		const auto curr_max_element = std::max_element(resultVector.begin(), resultVector.end());
		const auto curr_max_element_index = std::distance(resultVector.begin(), curr_max_element);

		if (max_element < resultVector[curr_max_element_index])
		{
			max_element = resultVector[curr_max_element_index];
			max_index = int(curr_max_element_index);
			label_result->Text = max_index.ToString();
			fillOutputTable(resultVector);
		}
	}
}
void NeuralNetGUI::MainForm::BasicPrediction(NeuralNet& Network)
{
	std::vector<double>Img_vector = LoadFromDrawing();
	Network.FeedForward(Img_vector);
	std::vector<double> resultValues = Network.GetResults();

	const auto max_element = std::max_element(resultValues.begin(), resultValues.end());
	const auto max_element_index = std::distance(resultValues.begin(), max_element);

	label_result->Text = max_element_index.ToString();

	fillOutputTable(resultValues);
}
void  NeuralNetGUI::MainForm::PredictNumber(NeuralNet& Network)
{

	if (checkBox_allPositions->Checked == true)
	{
		std::vector<std::vector<double>> AllResults = TryAllPosition(Network);

		if (checkBox_sumScores->Checked == true) SumScoresPrediction(AllResults);
		else HighestScorePrediction(AllResults);

	}
	else BasicPrediction(Network);
	
}

std::vector<std::vector<double>> NeuralNetGUI::MainForm::TryAllPosition(NeuralNet& Network)
{
	std::vector<std::vector<double>> allResults;

	int rows = tableLayoutPanel_draw->RowCount;
	int columns = tableLayoutPanel_draw->ColumnCount;
	std::vector<int> cornersOfImage(4, 0); //top, bottom, left, right

	cornersOfImage[0] = returnTopBorder(rows, columns);
	cornersOfImage[1] = returnBottomBorder(rows, columns);
	cornersOfImage[2] = returnLeftBorder(rows, columns);
	cornersOfImage[3] = returnRightBorder(rows, columns);

	for (int move_up = 0; move_up < cornersOfImage[0]; move_up++)
		button_Up_Click(nullptr, nullptr);
	for (int move_left = 0; move_left < cornersOfImage[2]; move_left++)
		button_left_Click(nullptr, nullptr);

	for (int move_down = 0; move_down <= cornersOfImage[0] + cornersOfImage[1]; ++move_down)
	{
		if (move_down != 0) button_down_Click(nullptr, nullptr);
		for (int move_right = 0; move_right <= cornersOfImage[2] + cornersOfImage[3]; ++move_right)
		{
			if (move_right != 0) button_right_Click(nullptr, nullptr);
			auto Img_vector = LoadFromDrawing();
			//PrintNumber(Img_vector);

			Network.FeedForward(Img_vector);
			std::vector<double> resultValues = Network.GetResults();
			allResults.emplace_back(resultValues);
		}
		for (int move_left = 0; move_left < cornersOfImage[2] + cornersOfImage[3]; ++move_left)
			button_left_Click(nullptr, nullptr);
	}

	return allResults;
}
// This function iterates over the labels in the drawing canvas and constructs a binary vector representing the image that was drawn by the user.
std::vector<double>  NeuralNetGUI::MainForm::LoadFromDrawing()
{
	std::vector<double> Img_vector;
	int columnCount = tableLayoutPanel_draw->ColumnCount;
	int rowCount = tableLayoutPanel_draw->RowCount;
	for (int i = 0; i < rowCount; ++i)
		for (int j = 0; j < columnCount; ++j)
		{
			if (tableLayoutPanel_draw->GetControlFromPosition(j, i)->BackColor == System::Drawing::SystemColors::Desktop) Img_vector.push_back(1.0);
			else Img_vector.push_back(0.0);
		}

	//PrintNumber(Img_vector);
	return Img_vector;
}

// This function takes a vector of result values and populates the probability table with the corresponding values.
void  NeuralNetGUI::MainForm::fillOutputTable(const std::vector<double>& resultValues)
{
	for (int i = 0; i < resultValues.size();++i)
		tableLayoutPanel_Propability->GetControlFromPosition(1, i)->Text = resultValues[i].ToString();

}

/*This function is called when the standard neural network check button is selected.
 It sets the custom check network check button to unchecked and hides the custom neural network name label.*/
System::Void  NeuralNetGUI::MainForm::standard_nn_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (standard_nn->Checked == true) custom_nn->Checked = false;
	else custom_nn->Checked = true;
}

/*This function is called when the custom neural network check button is selected.
 It sets the standard neural network check button to unchecked and shows the custom neural network name label.*/
System::Void  NeuralNetGUI::MainForm::custom_nn_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (custom_nn->Checked == true) {
		standard_nn->Checked = false;
		label_NameOfCustomNeuralNet->Visible = true;
	}
	else {
		standard_nn->Checked = true;
		label_NameOfCustomNeuralNet->Visible = false;
		return;
	}

	String^ s = "In the Networks folder, select the file with the name of your chosen network";
	MessageBox::Show(s);

	Stream^ MyStream = nullptr;
	OpenFileDialog^ openFileDialog_Net = gcnew OpenFileDialog;
	openFileDialog_Net->RestoreDirectory = true;
	openFileDialog_Net->InitialDirectory = "Networks";
	openFileDialog_Net->Filter = "Text Files | *_info.txt";
	openFileDialog_Net->FilterIndex = 2;
	std::string fileName = "";
	if (openFileDialog_Net->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		System::String^ sFileName = openFileDialog_Net->FileName;
		TrainGUI::MarshalString(sFileName, fileName);
	}
	if (fileName == "")
	{
		standard_nn->Checked = true;
		return;
	}
	const std::wstring weights_path(fileName.begin(), fileName.end());

	std::ifstream infoFile(weights_path.c_str());
	std::string sTopology;
	std::string sEta;
	std::string sAlpha;
	std::string sActFun;
	std::getline(infoFile, sTopology);
	std::getline(infoFile, sEta);
	std::getline(infoFile, sAlpha);
	std::getline(infoFile, sActFun);

	double eta = std::stod(sEta);
	double alpha = std::stof(sAlpha);
	ActivationFunctionsNum actFun = static_cast<ActivationFunctionsNum>(std::stoi(sActFun));
	std::vector<int> topology;

	std::stringstream ss(sTopology);
	std::string tmp;
	while (getline(ss, tmp, ';'))
		topology.emplace_back(std::stoi(tmp));

	CustomNet.NeuralNetUpdate(topology, eta, alpha, actFun);
	std::cout << CustomNet.eta << std::endl;
	std::cout << CustomNet.alpha << std::endl;

	const std::string suffiix = "_info.txt";
	const int suffixLength = suffiix.length();

	std::string weights_filename = fileName.erase(fileName.length() - suffixLength) + ".txt";

	std::string base_filename = fileName.substr(fileName.find_last_of("/\\") + 1);
	String^ sysstr = gcnew String(base_filename.data());
	fileHandler.insertWeightsToNet(CustomNet, base_filename + ".txt");
	label_NameOfCustomNeuralNet->Text = "Name of custom neural Net: " + sysstr;
}

// This function is called when a label in the drawing canvas is clicked. It toggles the background color of the label between black and white.
System::Void  NeuralNetGUI::MainForm::labelDrawClick(System::Object^ sender, System::EventArgs^ e)
{
	Label^ label = safe_cast<Label^>(sender);

	if (label->BackColor == System::Drawing::SystemColors::Control) label->BackColor = System::Drawing::SystemColors::Desktop;
	else label->BackColor = System::Drawing::SystemColors::Control;
}


System::Void  NeuralNetGUI::MainForm::Start_button_Click(System::Object^ sender, System::EventArgs^ e)
{
	custom_nn->Checked == true ? PredictNumber(CustomNet) : PredictNumber(DefaultNet);
}

// This function is called when the user clicks the "Clear" button. It resets the background color of all the labels in the drawing canvas to white.
System::Void  NeuralNetGUI::MainForm::clear_button_Click(System::Object^ sender, System::EventArgs^ e) {
	int columnCount = tableLayoutPanel_draw->ColumnCount;
	int rowCount = tableLayoutPanel_draw->RowCount;
	for (int i = 0; i < columnCount; ++i)
		for (int j = 0; j < rowCount; ++j)
			tableLayoutPanel_draw->GetControlFromPosition(i, j)->BackColor = System::Drawing::SystemColors::Control;
}

/*This function is called when the user clicks the "Upload" button. It opens a file dialog for the user to select an image file.
 It then loads the image into the drawing canvas and prepares the image vector for processing by the neural network.*/
System::Void  NeuralNetGUI::MainForm::UploadButton_Click(System::Object^ sender, System::EventArgs^ e) {
	Stream^ MyStream = nullptr;
	String^ s = "Select an image, which will be subsequently converted into a 28x28 field";
	MessageBox::Show(s);
	OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
	openFileDialog1->RestoreDirectory = true;
	openFileDialog1->InitialDirectory = "Numbers";
	openFileDialog1->Filter = "Image Files | *.jpg;*.jpeg;*.png";
	openFileDialog1->FilterIndex = 1;
	std::string fileName = "";
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		System::String^ sFileName = openFileDialog1->FileName;
		TrainGUI::MarshalString(sFileName, fileName);
	}

	if (fileName == "") return;
	clear_button_Click(sender, e);

	std::vector<int> Img_vector = imageConversion.ConvertToCompressedBinaryNet_readyVector(fileName);


	int columnCount = tableLayoutPanel_draw->ColumnCount;
	int rowCount = tableLayoutPanel_draw->RowCount;
	for (int i = 0; i < columnCount; ++i)
		for (int j = 0; j < rowCount; ++j)
			if (Img_vector[IMAGE_DIMENSION * i + j] == 1.00) tableLayoutPanel_draw->GetControlFromPosition(j, i)->BackColor = System::Drawing::SystemColors::Desktop;
}

// This function handles the click event of the up button. It moves the currently selected item in the list box up by one position.
System::Void  NeuralNetGUI::MainForm::button_Up_Click(System::Object^ sender, System::EventArgs^ e)
{
	const unsigned int rows = tableLayoutPanel_draw->RowCount;
	const unsigned int columns = tableLayoutPanel_draw->ColumnCount;

	for (unsigned int rowNum = 0; rowNum < rows; ++rowNum)
		for (unsigned int columnNum = 0; columnNum < columns; ++columnNum)
		{
			if (rowNum == rows - 1)
			{
				tableLayoutPanel_draw->GetControlFromPosition(columnNum, rowNum)->BackColor = System::Drawing::SystemColors::Control;
				continue;
			}
			if (rowNum == 0) tableLayoutPanel_draw->GetControlFromPosition(columnNum, rowNum)->BackColor = System::Drawing::SystemColors::Control;

			tableLayoutPanel_draw->GetControlFromPosition(columnNum, rowNum)->BackColor = tableLayoutPanel_draw->GetControlFromPosition(columnNum, rowNum + 1)->BackColor;
		}
}
// This function handles the click event of the left button. It updates the currently selected item in the list box left by one position.
System::Void  NeuralNetGUI::MainForm::button_left_Click(System::Object^ sender, System::EventArgs^ e)
{
	const unsigned int rows = tableLayoutPanel_draw->RowCount;
	const unsigned int columns = tableLayoutPanel_draw->ColumnCount;

	for (unsigned int columnNum = 0; columnNum < columns; ++columnNum)
		for (unsigned int rowNum = 0; rowNum < rows; ++rowNum)
		{
			if (columnNum == 0) tableLayoutPanel_draw->GetControlFromPosition(columnNum, rowNum)->BackColor = System::Drawing::SystemColors::Control;
			if (columnNum == columns - 1)
			{
				tableLayoutPanel_draw->GetControlFromPosition(columnNum, rowNum)->BackColor = System::Drawing::SystemColors::Control;
				continue;
			}
			tableLayoutPanel_draw->GetControlFromPosition(columnNum, rowNum)->BackColor = tableLayoutPanel_draw->GetControlFromPosition(columnNum + 1, rowNum)->BackColor;
		}
}
// This function handles the click event of the down button. It moves the currently selected item in the list box down by one position.
System::Void  NeuralNetGUI::MainForm::button_down_Click(System::Object^ sender, System::EventArgs^ e)
{
	const unsigned int rows = tableLayoutPanel_draw->RowCount;
	const unsigned int columns = tableLayoutPanel_draw->ColumnCount;

	for (int rowNum = rows - 1; rowNum >= 0; --rowNum)
		for (unsigned int columnNum = 0; columnNum < columns; ++columnNum)
		{
			if (rowNum == rows - 1) tableLayoutPanel_draw->GetControlFromPosition(columnNum, rowNum)->BackColor = System::Drawing::SystemColors::Control;
			if (rowNum == 0)
			{
				tableLayoutPanel_draw->GetControlFromPosition(columnNum, rowNum)->BackColor = System::Drawing::SystemColors::Control;
				continue;
			}
			tableLayoutPanel_draw->GetControlFromPosition(columnNum, rowNum)->BackColor = tableLayoutPanel_draw->GetControlFromPosition(columnNum, rowNum - 1)->BackColor;

		}
}
// This function handles the click event of the right button. It updates the currently selected item in the list box right by one position.
System::Void  NeuralNetGUI::MainForm::button_right_Click(System::Object^ sender, System::EventArgs^ e)
{
	const unsigned int rows = tableLayoutPanel_draw->RowCount;
	const unsigned int columns = tableLayoutPanel_draw->ColumnCount;

	for (int columnNum = columns - 1; columnNum >= 0; --columnNum)
		for (unsigned int rowNum = 0; rowNum < rows; ++rowNum)
		{
			if (columnNum == columns - 1) tableLayoutPanel_draw->GetControlFromPosition(columnNum, rowNum)->BackColor = System::Drawing::SystemColors::Control;
			if (columnNum == 0)
			{
				tableLayoutPanel_draw->GetControlFromPosition(columnNum, rowNum)->BackColor = System::Drawing::SystemColors::Control;
				continue;
			}
			tableLayoutPanel_draw->GetControlFromPosition(columnNum, rowNum)->BackColor = tableLayoutPanel_draw->GetControlFromPosition(columnNum - 1, rowNum)->BackColor;
		}
}
System::Void  NeuralNetGUI::MainForm::button_trainNeuralNet_Click(System::Object^ sender, System::EventArgs^ e)
{
	TrainGUI::TrainNetworkGUI^ trainForm = gcnew TrainGUI::TrainNetworkGUI;
	trainForm->Show();
}

System::Void  NeuralNetGUI::MainForm::checkBox_allPositions_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	CheckBox^ checkBox = safe_cast<CheckBox^>(sender);
	if(checkBox->Checked == true)
	{
		checkBox_highestScore->Visible = true;
		checkBox_sumScores->Visible = true;
	}
	else
	{
		checkBox_highestScore->Visible = false;
		checkBox_sumScores->Visible = false;
	}
}
System::Void NeuralNetGUI::MainForm::checkBox_sumScores_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (checkBox_sumScores->Checked == true) checkBox_highestScore->Checked = false;
	else checkBox_highestScore->Checked = true;
}
System::Void NeuralNetGUI::MainForm::checkBox_highestScore_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (checkBox_highestScore->Checked == true) checkBox_sumScores->Checked = false;
	else checkBox_sumScores->Checked = true;
}
