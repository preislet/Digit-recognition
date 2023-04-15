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

// This is the constructor for the MainForm class which is responsible for initializing the form's components and setting up the drawing canvas.
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

// This is the destructor for the MainForm class, which is responsible for freeing up any allocated memory when the form is closed.
NeuralNetGUI::MainForm::~MainForm() { if (components) delete components; }

/*This function takes a managed System::String and converts it to an unmanaged std::string.
 It is used to convert the file path of an image from the OpenFileDialog component into a format that can be used by the C++ code.*/
void NeuralNetGUI::MainForm::MarshalString(String^ s, std::string& os)
{
	using namespace Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
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
			if (tableLayoutPanel_draw->GetControlFromPosition(j, i)->BackColor == System::Drawing::Color::Black) Img_vector.push_back(1.0);
			else Img_vector.push_back(0.0);
		}

	PrintNumber(Img_vector);
	return Img_vector;
}

// This function takes a vector of result values and populates the probability table with the corresponding values.
void  NeuralNetGUI::MainForm::fillOutputTable(const std::vector<double>& resultValues)
{
	for(int i = 0; i < resultValues.size();++i)
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
	}
}

// This function is called when a label in the drawing canvas is clicked. It toggles the background color of the label between black and white.
System::Void  NeuralNetGUI::MainForm::labelDrawClick(System::Object^ sender, System::EventArgs^ e)
{
	Label^ label = safe_cast<Label^>(sender);

	if (label->BackColor == System::Drawing::SystemColors::Control) label->BackColor = System::Drawing::SystemColors::Desktop;
	else label->BackColor = System::Drawing::SystemColors::Control;
}

/*This function is called when the user clicks the "Start" button. It initializes a default neural network with a specific topology
 and trains it with the uploaded weight file. It then feeds forward the image vector and displays the predicted class and the probability values
 in the probability table.*/
System::Void  NeuralNetGUI::MainForm::Start_button_Click(System::Object^ sender, System::EventArgs^ e)
{
	const std::vector<int> topology = { 784,128,64,10 };
	NeuralNet DefaultNet(topology, 0.033665, 0.0889798);
	insertWeightsToNet(DefaultNet);

	std::vector<double>Img_vector = LoadFromDrawing();

	DefaultNet.FeedForward(Img_vector);
	std::vector<double> resultValues = DefaultNet.GetResults();

	const auto max_element = std::max_element(resultValues.begin(), resultValues.end());
	const auto max_element_index = std::distance(resultValues.begin(), max_element);

	label_result->Text = max_element_index.ToString();

	fillOutputTable(resultValues);
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
	OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
	openFileDialog1->Filter = "Image Files | *.jpg;*.jpeg;*.png";
	openFileDialog1->FilterIndex = 1;
	std::string fileName = "";
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		System::String^ sFileName = openFileDialog1->FileName;
		MarshalString(sFileName, fileName);
	}

	if (fileName == "") return;
	clear_button_Click(sender, e);

	std::vector<int> Img_vector = ConvertToCompressedBinaryNet_readyVector(fileName);


	int columnCount = tableLayoutPanel_draw->ColumnCount;
	int rowCount = tableLayoutPanel_draw->RowCount;
	for (int i = 0; i < columnCount; ++i)
		for (int j = 0; j < rowCount; ++j)
			if (Img_vector[28 * i + j] == 1.00) tableLayoutPanel_draw->GetControlFromPosition(j, i)->BackColor = System::Drawing::Color::Black;
}

// This function handles the click event of the up button. It moves the currently selected item in the list box up by one position.
System::Void  NeuralNetGUI::MainForm::button_Up_Click(System::Object^ sender, System::EventArgs^ e)
{
	const unsigned int rows = tableLayoutPanel_draw->RowCount;
	const unsigned int columns = tableLayoutPanel_draw->ColumnCount;

	for(unsigned int rowNum = 0; rowNum < rows; ++rowNum)
		for(unsigned int columnNum = 0; columnNum < columns; ++columnNum)
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

	for(unsigned int columnNum = 0; columnNum < columns; ++columnNum)
		for(unsigned int rowNum = 0; rowNum < rows; ++rowNum)
		{
			if(columnNum == 0) tableLayoutPanel_draw->GetControlFromPosition(columnNum, rowNum)->BackColor = System::Drawing::SystemColors::Control;
			if(columnNum == columns - 1)
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

	for(int rowNum = rows - 1; rowNum >= 0; --rowNum)
		for(unsigned int columnNum = 0; columnNum < columns; ++columnNum)
		{
			if(rowNum == rows-1) tableLayoutPanel_draw->GetControlFromPosition(columnNum, rowNum)->BackColor = System::Drawing::SystemColors::Control;
			if(rowNum == 0)
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
	return;
}
