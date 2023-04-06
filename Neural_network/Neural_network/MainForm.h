#pragma once
#include <string>
#include<iostream>
#include <vector>
#include<sstream>
//#include <msclr/marshal_cppstd.h>
#include "Image_conversion.hpp"
#include "Neural_network.hpp"
#using <System.dll>
#using <System.Drawing.dll>

namespace FormsProject {

	using namespace System::Runtime::InteropServices;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

<<<<<<< HEAD

=======
>>>>>>> fbcde6fd8b467e5923980cdebfe01739a2e02188
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:

		//NeuralNet CustomNEtwork;
		MainForm(void)
		{
			InitializeComponent();
			int numOfColumns = tableLayoutPanel_draw->ColumnCount;
			int numOfRows = tableLayoutPanel_draw->RowCount;
			for (int i = 0; i < numOfColumns; ++i)
				for (int j = 0; j < numOfRows; ++j)
				{
					Button^ b = gcnew System::Windows::Forms::Button();
					b->Text = "";
					b->Name = "button_" + i + "_" + j;
					b->BackColor = System::Drawing::SystemColors::Control;
					b->Click += gcnew System::EventHandler(this, &MainForm::buttonDrawClick);
					b->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::Drawbutton_MouseMove);
					tableLayoutPanel_draw->Controls->Add(b, i, j);
				}

		}

	protected:

	protected:
	private: System::Windows::Forms::Button^ Start_button;
	private: System::Windows::Forms::CheckBox^ standard_nn;
	private: System::Windows::Forms::CheckBox^ custom_nn;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Button^ train;
	private: System::Windows::Forms::TextBox^ textBox_topology;
	private: System::Windows::Forms::TextBox^ textBox_Eta;
	private: System::Windows::Forms::TextBox^ textBox_Appha;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ Accuracy_label;

	private: System::Windows::Forms::Button^ clear_button;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel_draw;


	private:
		bool clicked = false;
	private: System::Windows::Forms::Button^ Draw_button;
	private: System::Windows::Forms::Label^ label_result;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;


#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->Start_button = (gcnew System::Windows::Forms::Button());
			   this->standard_nn = (gcnew System::Windows::Forms::CheckBox());
			   this->custom_nn = (gcnew System::Windows::Forms::CheckBox());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->train = (gcnew System::Windows::Forms::Button());
			   this->textBox_topology = (gcnew System::Windows::Forms::TextBox());
			   this->textBox_Eta = (gcnew System::Windows::Forms::TextBox());
			   this->textBox_Appha = (gcnew System::Windows::Forms::TextBox());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   this->label5 = (gcnew System::Windows::Forms::Label());
			   this->label6 = (gcnew System::Windows::Forms::Label());
			   this->Accuracy_label = (gcnew System::Windows::Forms::Label());
			   this->clear_button = (gcnew System::Windows::Forms::Button());
			   this->tableLayoutPanel_draw = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->Draw_button = (gcnew System::Windows::Forms::Button());
			   this->label_result = (gcnew System::Windows::Forms::Label());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			   this->SuspendLayout();
			   // 
			   // Start_button
			   // 
			   this->Start_button->BackColor = System::Drawing::SystemColors::Highlight;
			   this->Start_button->ForeColor = System::Drawing::SystemColors::WindowText;
			   this->Start_button->Location = System::Drawing::Point(872, 745);
			   this->Start_button->Name = L"Start_button";
			   this->Start_button->Size = System::Drawing::Size(433, 118);
			   this->Start_button->TabIndex = 2;
			   this->Start_button->Text = L"Start";
			   this->Start_button->UseVisualStyleBackColor = false;
			   this->Start_button->Click += gcnew System::EventHandler(this, &MainForm::Start_button_Click);
			   // 
			   // standard_nn
			   // 
			   this->standard_nn->AutoSize = true;
			   this->standard_nn->Checked = true;
			   this->standard_nn->CheckState = System::Windows::Forms::CheckState::Checked;
			   this->standard_nn->Location = System::Drawing::Point(872, 127);
			   this->standard_nn->Name = L"standard_nn";
			   this->standard_nn->Size = System::Drawing::Size(162, 17);
			   this->standard_nn->TabIndex = 3;
			   this->standard_nn->Text = L"Use standard neural network";
			   this->standard_nn->UseVisualStyleBackColor = true;
			   this->standard_nn->CheckedChanged += gcnew System::EventHandler(this, &MainForm::standard_nn_CheckedChanged);
			   // 
			   // custom_nn
			   // 
			   this->custom_nn->AutoSize = true;
			   this->custom_nn->Location = System::Drawing::Point(872, 158);
			   this->custom_nn->Name = L"custom_nn";
			   this->custom_nn->Size = System::Drawing::Size(157, 17);
			   this->custom_nn->TabIndex = 4;
			   this->custom_nn->Text = L"Use my own neural network";
			   this->custom_nn->UseVisualStyleBackColor = true;
			   this->custom_nn->CheckedChanged += gcnew System::EventHandler(this, &MainForm::custom_nn_CheckedChanged);
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Location = System::Drawing::Point(873, 199);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(54, 13);
			   this->label1->TabIndex = 5;
			   this->label1->Text = L"Topology:";
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Location = System::Drawing::Point(873, 226);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(29, 13);
			   this->label2->TabIndex = 6;
			   this->label2->Text = L"Eta: ";
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->Location = System::Drawing::Point(873, 251);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(37, 13);
			   this->label3->TabIndex = 7;
			   this->label3->Text = L"Alpha:";
			   // 
			   // train
			   // 
			   this->train->Enabled = false;
			   this->train->Location = System::Drawing::Point(933, 286);
			   this->train->Name = L"train";
			   this->train->Size = System::Drawing::Size(177, 47);
			   this->train->TabIndex = 8;
			   this->train->Text = L"Train";
			   this->train->UseVisualStyleBackColor = true;
			   this->train->Click += gcnew System::EventHandler(this, &MainForm::train_Click);
			   // 
			   // textBox_topology
			   // 
			   this->textBox_topology->Location = System::Drawing::Point(933, 196);
			   this->textBox_topology->Name = L"textBox_topology";
			   this->textBox_topology->Size = System::Drawing::Size(94, 20);
			   this->textBox_topology->TabIndex = 9;
			   // 
			   // textBox_Eta
			   // 
			   this->textBox_Eta->Location = System::Drawing::Point(933, 223);
			   this->textBox_Eta->Name = L"textBox_Eta";
			   this->textBox_Eta->Size = System::Drawing::Size(94, 20);
			   this->textBox_Eta->TabIndex = 10;
			   // 
			   // textBox_Appha
			   // 
			   this->textBox_Appha->Location = System::Drawing::Point(933, 249);
			   this->textBox_Appha->Name = L"textBox_Appha";
			   this->textBox_Appha->Size = System::Drawing::Size(94, 20);
			   this->textBox_Appha->TabIndex = 11;
			   // 
			   // label4
			   // 
			   this->label4->AutoSize = true;
			   this->label4->Location = System::Drawing::Point(1033, 199);
			   this->label4->Name = L"label4";
			   this->label4->Size = System::Drawing::Size(121, 13);
			   this->label4->TabIndex = 12;
			   this->label4->Text = L"example: 724;129;64;10";
			   // 
			   // label5
			   // 
			   this->label5->AutoSize = true;
			   this->label5->Location = System::Drawing::Point(1033, 226);
			   this->label5->Name = L"label5";
			   this->label5->Size = System::Drawing::Size(28, 13);
			   this->label5->TabIndex = 13;
			   this->label5->Text = L"[0-1]";
			   // 
			   // label6
			   // 
			   this->label6->AutoSize = true;
			   this->label6->Location = System::Drawing::Point(1033, 251);
			   this->label6->Name = L"label6";
			   this->label6->Size = System::Drawing::Size(28, 13);
			   this->label6->TabIndex = 14;
			   this->label6->Text = L"[0-1]";
			   // 
			   // Accuracy_label
			   // 
			   this->Accuracy_label->AutoSize = true;
			   this->Accuracy_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15));
			   this->Accuracy_label->Location = System::Drawing::Point(1130, 308);
			   this->Accuracy_label->Name = L"Accuracy_label";
			   this->Accuracy_label->Size = System::Drawing::Size(137, 25);
			   this->Accuracy_label->TabIndex = 15;
			   this->Accuracy_label->Text = L"Accuracy: --%";
			   // 
			   // clear_button
			   // 
			   this->clear_button->Location = System::Drawing::Point(39, 12);
			   this->clear_button->Name = L"clear_button";
			   this->clear_button->Size = System::Drawing::Size(193, 61);
			   this->clear_button->TabIndex = 16;
			   this->clear_button->Text = L"Clear";
			   this->clear_button->UseVisualStyleBackColor = true;
			   this->clear_button->Click += gcnew System::EventHandler(this, &MainForm::clear_button_Click);
			   // 
			   // tableLayoutPanel_draw
			   // 
			   this->tableLayoutPanel_draw->ColumnCount = 28;
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->Location = System::Drawing::Point(39, 94);
			   this->tableLayoutPanel_draw->Name = L"tableLayoutPanel_draw";
			   this->tableLayoutPanel_draw->RowCount = 28;
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				   28)));
			   this->tableLayoutPanel_draw->Size = System::Drawing::Size(784, 784);
			   this->tableLayoutPanel_draw->TabIndex = 17;
			   // 
			   // Draw_button
			   // 
			   this->Draw_button->BackColor = System::Drawing::Color::Crimson;
			   this->Draw_button->Location = System::Drawing::Point(238, 31);
			   this->Draw_button->Name = L"Draw_button";
			   this->Draw_button->Size = System::Drawing::Size(155, 42);
			   this->Draw_button->TabIndex = 18;
			   this->Draw_button->Text = L"DRAW";
			   this->Draw_button->UseVisualStyleBackColor = false;
			   this->Draw_button->Click += gcnew System::EventHandler(this, &MainForm::Draw_button_Click);
			   // 
			   // label_result
			   // 
			   this->label_result->AutoSize = true;
			   this->label_result->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 72, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->label_result->Location = System::Drawing::Point(897, 540);
			   this->label_result->Name = L"label_result";
			   this->label_result->Size = System::Drawing::Size(109, 108);
			   this->label_result->TabIndex = 19;
			   this->label_result->Text = L"X";
			   // 
			   // button1
			   // 
			   this->button1->Location = System::Drawing::Point(564, 29);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(267, 43);
			   this->button1->TabIndex = 20;
			   this->button1->Text = L"Upload Image";
			   this->button1->UseVisualStyleBackColor = true;
			   this->button1->Click += gcnew System::EventHandler(this, &MainForm::UploadButton_Click);
			   // 
			   // MainForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1391, 970);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->label_result);
			   this->Controls->Add(this->Draw_button);
			   this->Controls->Add(this->tableLayoutPanel_draw);
			   this->Controls->Add(this->clear_button);
			   this->Controls->Add(this->Accuracy_label);
			   this->Controls->Add(this->label6);
			   this->Controls->Add(this->label5);
			   this->Controls->Add(this->label4);
			   this->Controls->Add(this->textBox_Appha);
			   this->Controls->Add(this->textBox_Eta);
			   this->Controls->Add(this->textBox_topology);
			   this->Controls->Add(this->train);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->custom_nn);
			   this->Controls->Add(this->standard_nn);
			   this->Controls->Add(this->Start_button);
			   this->Name = L"MainForm";
			   this->Text = L"Neural Network";
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion

	private: void MarshalString(String^ s, std::string& os)
	{
		using namespace Runtime::InteropServices;
		const char* chars =
			(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}
		   std::vector<double> LoadFromDrawing()
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
	private: System::Void button_draw_Click(System::Object^ sender, System::EventArgs^ e)
	{
		return;
	};
	private: System::Void train_Click(System::Object^ sender, System::EventArgs^ e)
	{
		const auto trainSamples = read_csv("train.csv");
		const auto testSamples = read_csv("test.csv");

		double eta = System::Convert::ToDouble(textBox_Eta->Text);
		double alpha = System::Convert::ToDouble(textBox_Appha->Text);

		std::string Topo = "";
		MarshalString(textBox_topology->Text, Topo);

		std::string token;
		std::stringstream ss(Topo);
		std::vector<int> Topology;
		while (std::getline(ss, token, ';'))
			Topology.emplace_back(std::stoi(token));
		NeuralNet CustomNet(Topology, eta, alpha);
		TrainNetwork(CustomNet, trainSamples);

		double accuracy = testNetwork(CustomNet, testSamples);


		Accuracy_label->Text = "Accuracy: " + accuracy * 100 + " %";
	}
	private: System::Void custom_nn_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (custom_nn->Checked == true)
		{
			train->Enabled = true;
			standard_nn->Checked = false;
		}
		else
		{
			train->Enabled = false;
			standard_nn->Checked = true;
		}
	}

	private: System::Void standard_nn_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (standard_nn->Checked == true) custom_nn->Checked = false;
		else custom_nn->Checked = true;

	}
	private: System::Void buttonDrawClick(System::Object^ sender, System::EventArgs^ e) {
		Button^ button = safe_cast<Button^>(sender);
		button->BackColor = System::Drawing::SystemColors::Control;

	}
	private: System::Void Start_button_Click(System::Object^ sender, System::EventArgs^ e) {
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
	private: System::Void Drawbutton_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		Button^ button = safe_cast<Button^>(sender);
		if (clicked) button->BackColor = System::Drawing::SystemColors::Desktop;
	}
	private: System::Void Draw_button_Click(System::Object^ sender, System::EventArgs^ e) {
		Button^ button = safe_cast<Button^>(sender);
		if (!clicked)
		{
			clicked = true;
			button->BackColor = System::Drawing::Color::LimeGreen;
		}
		else if (clicked)
		{
			clicked = false;
			button->BackColor = System::Drawing::Color::Crimson;
		}
	}
	private: System::Void clear_button_Click(System::Object^ sender, System::EventArgs^ e) {
		int columnCount = tableLayoutPanel_draw->ColumnCount;
		int rowCount = tableLayoutPanel_draw->RowCount;
		for (int i = 0; i < columnCount; ++i)
			for (int j = 0; j < rowCount; ++j)
				tableLayoutPanel_draw->GetControlFromPosition(i, j)->BackColor = System::Drawing::SystemColors::Control;
	}

	private: System::Void UploadButton_Click(System::Object^ sender, System::EventArgs^ e) {
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
	};
}
