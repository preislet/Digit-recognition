#include <string>
#include<iostream>
#include <vector>
#include<sstream>

#include "Image_conversion.hpp"
#include "Neural_network.hpp"

#include "MainForm.h"
#using <System.dll>
#using <System.Drawing.dll>

using namespace System::Runtime::InteropServices;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


NeuralNetGUI::MainForm::MainForm(void)
{
	InitializeComponent();
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
NeuralNetGUI::MainForm::~MainForm()
{
	if (components)
	{
		delete components;
	}
}


void NeuralNetGUI::MainForm::MarshalString(String^ s, std::string& os)
{
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}
std::vector<double>  NeuralNetGUI::MainForm::LoadFromDrawing()
{
	std::vector<double> Img_vector;
	int columnCount = tableLayoutPanel_draw->ColumnCount;
	int rowCount = tableLayoutPanel_draw->RowCount;
	for (int i = 0; i < rowCount; ++i)
		for (int j = 0; j < columnCount; ++j)
		{
			if (tableLayoutPanel_draw->GetControlFromPosition(j, i)->BackColor == System::Drawing::Color::Black) Img_vector.push_back(1.0);
			else Img_vector.push_back(0.0);
		}
	return Img_vector;
}

System::Void  NeuralNetGUI::MainForm::standard_nn_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (standard_nn->Checked == true) custom_nn->Checked = false;
	else custom_nn->Checked = true;
}
System::Void  NeuralNetGUI::MainForm::custom_nn_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (custom_nn->Checked == true) {
		standard_nn->Checked = false;
		label_NameOfCustomNeuralNet->Visible = true;
	}
	else {
		standard_nn->Checked = true;
		label_NameOfCustomNeuralNet->Visible = false;
	}
}
System::Void  NeuralNetGUI::MainForm::labelDrawClick(System::Object^ sender, System::EventArgs^ e)
{
	Label^ label = safe_cast<Label^>(sender);

	if (label->BackColor == System::Drawing::SystemColors::Control) label->BackColor == System::Drawing::SystemColors::Desktop;
	else label->BackColor = System::Drawing::SystemColors::Control;
}
System::Void  NeuralNetGUI::MainForm::Start_button_Click(System::Object^ sender, System::EventArgs^ e)
{
	const std::vector<int> topology = { 784,128,64,10 };
	NeuralNet DefaultNet(topology, 0.033665, 0.0889798);
	insertWeightsToNet(DefaultNet);
	std::vector<double>Img_vector = LoadFromDrawing();
	DefaultNet.FeedForward(Img_vector);
	std::vector<double> resultValues = DefaultNet.GetResults();
	resultValues.pop_back();
	const auto max_element = std::max_element(resultValues.begin(), resultValues.end());
	const auto max_element_index = std::distance(resultValues.begin(), max_element);

	label_result->Text = max_element_index.ToString();
}
System::Void  NeuralNetGUI::MainForm::clear_button_Click(System::Object^ sender, System::EventArgs^ e) {
	int columnCount = tableLayoutPanel_draw->ColumnCount;
	int rowCount = tableLayoutPanel_draw->RowCount;
	for (int i = 0; i < columnCount; ++i)
		for (int j = 0; j < rowCount; ++j)
			tableLayoutPanel_draw->GetControlFromPosition(i, j)->BackColor = System::Drawing::SystemColors::Control;
}
System::Void  NeuralNetGUI::MainForm::UploadButton_Click(System::Object^ sender, System::EventArgs^ e) {
	Stream^ MyStream;
	OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
	openFileDialog1->Filter = "All Files (*.*)|*.*";
	openFileDialog1->FilterIndex = 1;
	std::string fileName = "";
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		System::String^ sFileName = openFileDialog1->FileName;
		MarshalString(sFileName, fileName);
	}
	std::vector<int> Img_vector = ConvertToCompressedBinaryNet_readyVector(fileName);
	int columnCount = tableLayoutPanel_draw->ColumnCount;
	int rowCount = tableLayoutPanel_draw->RowCount;
	for (int i = 0; i < columnCount; ++i)
		for (int j = 0; j < rowCount; ++j)
			if (Img_vector[28 * i + j] == 1.00) tableLayoutPanel_draw->GetControlFromPosition(j, i)->BackColor = System::Drawing::Color::Black;
}
System::Void  NeuralNetGUI::MainForm::button_Up_Click(System::Object^ sender, System::EventArgs^ e)
{
	size_t rows = tableLayoutPanel_draw->RowCount;
	size_t columns = tableLayoutPanel_draw->ColumnCount;

	for(size_t rowNum = 0; rowNum < rows; ++rowNum)
		for(size_t columnNum = 0; columnNum < columns; ++columnNum)
		{
			if(rowNum == 0) tableLayoutPanel_draw->GetControlFromPosition()
		}
}
System::Void  NeuralNetGUI::MainForm::button_left_Click(System::Object^ sender, System::EventArgs^ e)
{
	return;
}
System::Void  NeuralNetGUI::MainForm::button_down_Click(System::Object^ sender, System::EventArgs^ e)
{
	return;
}
System::Void  NeuralNetGUI::MainForm::button_right_Click(System::Object^ sender, System::EventArgs^ e)
{
	return;
}
System::Void  NeuralNetGUI::MainForm::button_trainNeuralNet_Click(System::Object^ sender, System::EventArgs^ e)
{
	return;
}