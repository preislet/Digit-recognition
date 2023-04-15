#pragma once
#include <string>
#include<iostream>
#include <vector>
#include<sstream>
#include "Image_conversion.hpp"
#include "Neural_network.hpp"
#using <System.dll>
#using <System.Drawing.dll>

namespace NeuralNetGUI {

	using namespace System::Runtime::InteropServices;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	const std::vector<int> topology = { 784,128,64,10 };
	static NeuralNet DefaultNet(topology, 0.033665, 0.0889798, ActivationFunctions::ReLU);

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public: MainForm(void);
	public: ~MainForm();
	private: System::Windows::Forms::Button^ Start_button;
	private: System::Windows::Forms::CheckBox^ standard_nn;
	private: System::Windows::Forms::CheckBox^ custom_nn;
	private: System::Windows::Forms::Button^ clear_button;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel_draw;
	private: System::Windows::Forms::Label^ label_result;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;
	private: System::Windows::Forms::Label^ NumberGuess;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel_Propability;
	private: System::Windows::Forms::Label^ labelOutput_9;
	private: System::Windows::Forms::Label^ labelOutput_8;
	private: System::Windows::Forms::Label^ labelOutput_7;
	private: System::Windows::Forms::Label^ labelOutput_6;
	private: System::Windows::Forms::Label^ labelOutput_5;
	private: System::Windows::Forms::Label^ labelOutput_4;
	private: System::Windows::Forms::Label^ labelOutput_3;
	private: System::Windows::Forms::Label^ labelOutput_2;
	private: System::Windows::Forms::Label^ labelOutput_1;
	private: System::Windows::Forms::Label^ labelOutput_0;
	private: System::Windows::Forms::Label^ label_0;
	private: System::Windows::Forms::Label^ label_1;
	private: System::Windows::Forms::Label^ label_2;
	private: System::Windows::Forms::Label^ label_3;
	private: System::Windows::Forms::Label^ label_4;
	private: System::Windows::Forms::Label^ label_5;
	private: System::Windows::Forms::Label^ label_6;
	private: System::Windows::Forms::Label^ label_7;
	private: System::Windows::Forms::Label^ label_8;
	private: System::Windows::Forms::Label^ label_9;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Button^ button_Up;
	private: System::Windows::Forms::Button^ button_down;
	private: System::Windows::Forms::Button^ button_right;
	private: System::Windows::Forms::Button^ button_left;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label_NameOfCustomNeuralNet;
		   System::ComponentModel::Container^ components;


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
			   this->clear_button = (gcnew System::Windows::Forms::Button());
			   this->tableLayoutPanel_draw = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->label_result = (gcnew System::Windows::Forms::Label());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			   this->NumberGuess = (gcnew System::Windows::Forms::Label());
			   this->tableLayoutPanel_Propability = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->labelOutput_9 = (gcnew System::Windows::Forms::Label());
			   this->labelOutput_8 = (gcnew System::Windows::Forms::Label());
			   this->labelOutput_7 = (gcnew System::Windows::Forms::Label());
			   this->labelOutput_6 = (gcnew System::Windows::Forms::Label());
			   this->labelOutput_5 = (gcnew System::Windows::Forms::Label());
			   this->labelOutput_2 = (gcnew System::Windows::Forms::Label());
			   this->labelOutput_1 = (gcnew System::Windows::Forms::Label());
			   this->labelOutput_0 = (gcnew System::Windows::Forms::Label());
			   this->label_0 = (gcnew System::Windows::Forms::Label());
			   this->label_1 = (gcnew System::Windows::Forms::Label());
			   this->label_2 = (gcnew System::Windows::Forms::Label());
			   this->label_3 = (gcnew System::Windows::Forms::Label());
			   this->label_4 = (gcnew System::Windows::Forms::Label());
			   this->label_5 = (gcnew System::Windows::Forms::Label());
			   this->label_6 = (gcnew System::Windows::Forms::Label());
			   this->label_7 = (gcnew System::Windows::Forms::Label());
			   this->label_8 = (gcnew System::Windows::Forms::Label());
			   this->label_9 = (gcnew System::Windows::Forms::Label());
			   this->labelOutput_3 = (gcnew System::Windows::Forms::Label());
			   this->labelOutput_4 = (gcnew System::Windows::Forms::Label());
			   this->label7 = (gcnew System::Windows::Forms::Label());
			   this->button_Up = (gcnew System::Windows::Forms::Button());
			   this->button_down = (gcnew System::Windows::Forms::Button());
			   this->button_right = (gcnew System::Windows::Forms::Button());
			   this->button_left = (gcnew System::Windows::Forms::Button());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->label_NameOfCustomNeuralNet = (gcnew System::Windows::Forms::Label());
			   this->tableLayoutPanel_Propability->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // Start_button
			   // 
			   this->Start_button->BackColor = System::Drawing::SystemColors::Control;
			   this->Start_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->Start_button->ForeColor = System::Drawing::SystemColors::WindowText;
			   this->Start_button->Location = System::Drawing::Point(852, 760);
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
			   this->standard_nn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->standard_nn->Location = System::Drawing::Point(858, 655);
			   this->standard_nn->Name = L"standard_nn";
			   this->standard_nn->Size = System::Drawing::Size(268, 28);
			   this->standard_nn->TabIndex = 3;
			   this->standard_nn->Text = L"Use standard neural network";
			   this->standard_nn->UseVisualStyleBackColor = true;
			   this->standard_nn->CheckedChanged += gcnew System::EventHandler(this, &MainForm::standard_nn_CheckedChanged);
			   // 
			   // custom_nn
			   // 
			   this->custom_nn->AutoSize = true;
			   this->custom_nn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->custom_nn->Location = System::Drawing::Point(858, 689);
			   this->custom_nn->Name = L"custom_nn";
			   this->custom_nn->Size = System::Drawing::Size(262, 28);
			   this->custom_nn->TabIndex = 4;
			   this->custom_nn->Text = L"Use my own neural network";
			   this->custom_nn->UseVisualStyleBackColor = true;
			   this->custom_nn->CheckedChanged += gcnew System::EventHandler(this, &MainForm::custom_nn_CheckedChanged);
			   // 
			   // clear_button
			   // 
			   this->clear_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->clear_button->Location = System::Drawing::Point(630, 23);
			   this->clear_button->Name = L"clear_button";
			   this->clear_button->Size = System::Drawing::Size(193, 61);
			   this->clear_button->TabIndex = 16;
			   this->clear_button->Text = L"Clear";
			   this->clear_button->UseVisualStyleBackColor = true;
			   this->clear_button->Click += gcnew System::EventHandler(this, &MainForm::clear_button_Click);
			   // 
			   // tableLayoutPanel_draw
			   // 
			   this->tableLayoutPanel_draw->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
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
				   35)));
			   this->tableLayoutPanel_draw->Cursor = System::Windows::Forms::Cursors::Default;
			   this->tableLayoutPanel_draw->Location = System::Drawing::Point(39, 94);
			   this->tableLayoutPanel_draw->Margin = System::Windows::Forms::Padding(0);
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
			   // label_result
			   // 
			   this->label_result->AutoSize = true;
			   this->label_result->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			   this->label_result->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 72, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->label_result->Location = System::Drawing::Point(1063, 321);
			   this->label_result->Name = L"label_result";
			   this->label_result->Size = System::Drawing::Size(111, 110);
			   this->label_result->TabIndex = 19;
			   this->label_result->Text = L"X";
			   this->label_result->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // button1
			   // 
			   this->button1->BackColor = System::Drawing::Color::Transparent;
			   this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->button1->Location = System::Drawing::Point(39, 12);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(386, 72);
			   this->button1->TabIndex = 20;
			   this->button1->Text = L"Upload Image";
			   this->button1->UseVisualStyleBackColor = false;
			   this->button1->Click += gcnew System::EventHandler(this, &MainForm::UploadButton_Click);
			   // 
			   // NumberGuess
			   // 
			   this->NumberGuess->AutoSize = true;
			   this->NumberGuess->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->NumberGuess->Location = System::Drawing::Point(842, 350);
			   this->NumberGuess->Name = L"NumberGuess";
			   this->NumberGuess->Size = System::Drawing::Size(209, 55);
			   this->NumberGuess->TabIndex = 21;
			   this->NumberGuess->Text = L"Number:";
			   // 
			   // tableLayoutPanel_Propability
			   // 
			   this->tableLayoutPanel_Propability->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			   this->tableLayoutPanel_Propability->ColumnCount = 2;
			   this->tableLayoutPanel_Propability->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   28.34646F)));
			   this->tableLayoutPanel_Propability->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   71.65354F)));
			   this->tableLayoutPanel_Propability->Controls->Add(this->labelOutput_9, 1, 9);
			   this->tableLayoutPanel_Propability->Controls->Add(this->labelOutput_8, 1, 8);
			   this->tableLayoutPanel_Propability->Controls->Add(this->labelOutput_7, 1, 7);
			   this->tableLayoutPanel_Propability->Controls->Add(this->labelOutput_6, 1, 6);
			   this->tableLayoutPanel_Propability->Controls->Add(this->labelOutput_5, 1, 5);
			   this->tableLayoutPanel_Propability->Controls->Add(this->labelOutput_2, 1, 2);
			   this->tableLayoutPanel_Propability->Controls->Add(this->labelOutput_1, 1, 1);
			   this->tableLayoutPanel_Propability->Controls->Add(this->labelOutput_0, 1, 0);
			   this->tableLayoutPanel_Propability->Controls->Add(this->label_0, 0, 0);
			   this->tableLayoutPanel_Propability->Controls->Add(this->label_1, 0, 1);
			   this->tableLayoutPanel_Propability->Controls->Add(this->label_2, 0, 2);
			   this->tableLayoutPanel_Propability->Controls->Add(this->label_3, 0, 3);
			   this->tableLayoutPanel_Propability->Controls->Add(this->label_4, 0, 4);
			   this->tableLayoutPanel_Propability->Controls->Add(this->label_5, 0, 5);
			   this->tableLayoutPanel_Propability->Controls->Add(this->label_6, 0, 6);
			   this->tableLayoutPanel_Propability->Controls->Add(this->label_7, 0, 7);
			   this->tableLayoutPanel_Propability->Controls->Add(this->label_8, 0, 8);
			   this->tableLayoutPanel_Propability->Controls->Add(this->label_9, 0, 9);
			   this->tableLayoutPanel_Propability->Controls->Add(this->labelOutput_3, 1, 4);
			   this->tableLayoutPanel_Propability->Controls->Add(this->labelOutput_4, 1, 3);
			   this->tableLayoutPanel_Propability->Location = System::Drawing::Point(1029, 94);
			   this->tableLayoutPanel_Propability->Name = L"tableLayoutPanel_Propability";
			   this->tableLayoutPanel_Propability->RowCount = 10;
			   this->tableLayoutPanel_Propability->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				   10)));
			   this->tableLayoutPanel_Propability->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				   10)));
			   this->tableLayoutPanel_Propability->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				   10)));
			   this->tableLayoutPanel_Propability->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				   10)));
			   this->tableLayoutPanel_Propability->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				   10)));
			   this->tableLayoutPanel_Propability->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				   10)));
			   this->tableLayoutPanel_Propability->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				   10)));
			   this->tableLayoutPanel_Propability->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				   10)));
			   this->tableLayoutPanel_Propability->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				   10)));
			   this->tableLayoutPanel_Propability->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				   10)));
			   this->tableLayoutPanel_Propability->Size = System::Drawing::Size(145, 212);
			   this->tableLayoutPanel_Propability->TabIndex = 22;
			   // 
			   // labelOutput_9
			   // 
			   this->labelOutput_9->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->labelOutput_9->AutoSize = true;
			   this->labelOutput_9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->labelOutput_9->Location = System::Drawing::Point(45, 190);
			   this->labelOutput_9->Name = L"labelOutput_9";
			   this->labelOutput_9->Size = System::Drawing::Size(96, 21);
			   this->labelOutput_9->TabIndex = 19;
			   this->labelOutput_9->Text = L"---------------";
			   this->labelOutput_9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // labelOutput_8
			   // 
			   this->labelOutput_8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->labelOutput_8->AutoSize = true;
			   this->labelOutput_8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->labelOutput_8->Location = System::Drawing::Point(45, 169);
			   this->labelOutput_8->Name = L"labelOutput_8";
			   this->labelOutput_8->Size = System::Drawing::Size(96, 20);
			   this->labelOutput_8->TabIndex = 18;
			   this->labelOutput_8->Text = L"---------------";
			   this->labelOutput_8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // labelOutput_7
			   // 
			   this->labelOutput_7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->labelOutput_7->AutoSize = true;
			   this->labelOutput_7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->labelOutput_7->Location = System::Drawing::Point(45, 148);
			   this->labelOutput_7->Name = L"labelOutput_7";
			   this->labelOutput_7->Size = System::Drawing::Size(96, 20);
			   this->labelOutput_7->TabIndex = 17;
			   this->labelOutput_7->Text = L"---------------";
			   this->labelOutput_7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // labelOutput_6
			   // 
			   this->labelOutput_6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->labelOutput_6->AutoSize = true;
			   this->labelOutput_6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->labelOutput_6->Location = System::Drawing::Point(45, 127);
			   this->labelOutput_6->Name = L"labelOutput_6";
			   this->labelOutput_6->Size = System::Drawing::Size(96, 20);
			   this->labelOutput_6->TabIndex = 16;
			   this->labelOutput_6->Text = L"---------------";
			   this->labelOutput_6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // labelOutput_5
			   // 
			   this->labelOutput_5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->labelOutput_5->AutoSize = true;
			   this->labelOutput_5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->labelOutput_5->Location = System::Drawing::Point(45, 106);
			   this->labelOutput_5->Name = L"labelOutput_5";
			   this->labelOutput_5->Size = System::Drawing::Size(96, 20);
			   this->labelOutput_5->TabIndex = 15;
			   this->labelOutput_5->Text = L"---------------";
			   this->labelOutput_5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // labelOutput_2
			   // 
			   this->labelOutput_2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->labelOutput_2->AutoSize = true;
			   this->labelOutput_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->labelOutput_2->Location = System::Drawing::Point(45, 43);
			   this->labelOutput_2->Name = L"labelOutput_2";
			   this->labelOutput_2->Size = System::Drawing::Size(96, 20);
			   this->labelOutput_2->TabIndex = 12;
			   this->labelOutput_2->Text = L"---------------";
			   this->labelOutput_2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // labelOutput_1
			   // 
			   this->labelOutput_1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->labelOutput_1->AutoSize = true;
			   this->labelOutput_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->labelOutput_1->Location = System::Drawing::Point(45, 22);
			   this->labelOutput_1->Name = L"labelOutput_1";
			   this->labelOutput_1->Size = System::Drawing::Size(96, 20);
			   this->labelOutput_1->TabIndex = 11;
			   this->labelOutput_1->Text = L"---------------";
			   this->labelOutput_1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // labelOutput_0
			   // 
			   this->labelOutput_0->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->labelOutput_0->AutoSize = true;
			   this->labelOutput_0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->labelOutput_0->Location = System::Drawing::Point(45, 1);
			   this->labelOutput_0->Name = L"labelOutput_0";
			   this->labelOutput_0->Size = System::Drawing::Size(96, 20);
			   this->labelOutput_0->TabIndex = 10;
			   this->labelOutput_0->Text = L"---------------";
			   this->labelOutput_0->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label_0
			   // 
			   this->label_0->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->label_0->AutoSize = true;
			   this->label_0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->label_0->Location = System::Drawing::Point(4, 1);
			   this->label_0->Name = L"label_0";
			   this->label_0->Size = System::Drawing::Size(34, 20);
			   this->label_0->TabIndex = 0;
			   this->label_0->Text = L"0";
			   this->label_0->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label_1
			   // 
			   this->label_1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->label_1->AutoSize = true;
			   this->label_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->label_1->Location = System::Drawing::Point(4, 22);
			   this->label_1->Name = L"label_1";
			   this->label_1->Size = System::Drawing::Size(34, 20);
			   this->label_1->TabIndex = 1;
			   this->label_1->Text = L"1";
			   this->label_1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label_2
			   // 
			   this->label_2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->label_2->AutoSize = true;
			   this->label_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->label_2->Location = System::Drawing::Point(4, 43);
			   this->label_2->Name = L"label_2";
			   this->label_2->Size = System::Drawing::Size(34, 20);
			   this->label_2->TabIndex = 2;
			   this->label_2->Text = L"2";
			   this->label_2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label_3
			   // 
			   this->label_3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->label_3->AutoSize = true;
			   this->label_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->label_3->Location = System::Drawing::Point(4, 64);
			   this->label_3->Name = L"label_3";
			   this->label_3->Size = System::Drawing::Size(34, 20);
			   this->label_3->TabIndex = 3;
			   this->label_3->Text = L"3";
			   this->label_3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label_4
			   // 
			   this->label_4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->label_4->AutoSize = true;
			   this->label_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->label_4->Location = System::Drawing::Point(4, 85);
			   this->label_4->Name = L"label_4";
			   this->label_4->Size = System::Drawing::Size(34, 20);
			   this->label_4->TabIndex = 4;
			   this->label_4->Text = L"4";
			   this->label_4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label_5
			   // 
			   this->label_5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->label_5->AutoSize = true;
			   this->label_5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->label_5->Location = System::Drawing::Point(4, 106);
			   this->label_5->Name = L"label_5";
			   this->label_5->Size = System::Drawing::Size(34, 20);
			   this->label_5->TabIndex = 5;
			   this->label_5->Text = L"5";
			   this->label_5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label_6
			   // 
			   this->label_6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->label_6->AutoSize = true;
			   this->label_6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->label_6->Location = System::Drawing::Point(4, 127);
			   this->label_6->Name = L"label_6";
			   this->label_6->Size = System::Drawing::Size(34, 20);
			   this->label_6->TabIndex = 6;
			   this->label_6->Text = L"6";
			   this->label_6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label_7
			   // 
			   this->label_7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->label_7->AutoSize = true;
			   this->label_7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->label_7->Location = System::Drawing::Point(4, 148);
			   this->label_7->Name = L"label_7";
			   this->label_7->Size = System::Drawing::Size(34, 20);
			   this->label_7->TabIndex = 7;
			   this->label_7->Text = L"7";
			   this->label_7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label_8
			   // 
			   this->label_8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->label_8->AutoSize = true;
			   this->label_8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->label_8->Location = System::Drawing::Point(4, 169);
			   this->label_8->Name = L"label_8";
			   this->label_8->Size = System::Drawing::Size(34, 20);
			   this->label_8->TabIndex = 8;
			   this->label_8->Text = L"8";
			   this->label_8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label_9
			   // 
			   this->label_9->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->label_9->AutoSize = true;
			   this->label_9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->label_9->Location = System::Drawing::Point(4, 190);
			   this->label_9->Name = L"label_9";
			   this->label_9->Size = System::Drawing::Size(34, 21);
			   this->label_9->TabIndex = 9;
			   this->label_9->Text = L"9";
			   this->label_9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // labelOutput_3
			   // 
			   this->labelOutput_3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->labelOutput_3->AutoSize = true;
			   this->labelOutput_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->labelOutput_3->Location = System::Drawing::Point(45, 85);
			   this->labelOutput_3->Name = L"labelOutput_3";
			   this->labelOutput_3->Size = System::Drawing::Size(96, 20);
			   this->labelOutput_3->TabIndex = 13;
			   this->labelOutput_3->Text = L"---------------";
			   this->labelOutput_3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // labelOutput_4
			   // 
			   this->labelOutput_4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->labelOutput_4->AutoSize = true;
			   this->labelOutput_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->labelOutput_4->Location = System::Drawing::Point(45, 64);
			   this->labelOutput_4->Name = L"labelOutput_4";
			   this->labelOutput_4->Size = System::Drawing::Size(96, 20);
			   this->labelOutput_4->TabIndex = 14;
			   this->labelOutput_4->Text = L"---------------";
			   this->labelOutput_4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label7
			   // 
			   this->label7->AutoSize = true;
			   this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->label7->Location = System::Drawing::Point(842, 94);
			   this->label7->Name = L"label7";
			   this->label7->Size = System::Drawing::Size(181, 55);
			   this->label7->TabIndex = 23;
			   this->label7->Text = L"Output:";
			   // 
			   // button_Up
			   // 
			   this->button_Up->Location = System::Drawing::Point(464, 12);
			   this->button_Up->Name = L"button_Up";
			   this->button_Up->Size = System::Drawing::Size(84, 23);
			   this->button_Up->TabIndex = 24;
			   this->button_Up->Text = L"Up";
			   this->button_Up->UseVisualStyleBackColor = true;
			   this->button_Up->Click += gcnew System::EventHandler(this, &MainForm::button_Up_Click);
			   // 
			   // button_down
			   // 
			   this->button_down->Location = System::Drawing::Point(464, 70);
			   this->button_down->Name = L"button_down";
			   this->button_down->Size = System::Drawing::Size(84, 23);
			   this->button_down->TabIndex = 25;
			   this->button_down->Text = L"Down";
			   this->button_down->UseVisualStyleBackColor = true;
			   this->button_down->Click += gcnew System::EventHandler(this, &MainForm::button_down_Click);
			   // 
			   // button_right
			   // 
			   this->button_right->Location = System::Drawing::Point(512, 41);
			   this->button_right->Name = L"button_right";
			   this->button_right->Size = System::Drawing::Size(75, 23);
			   this->button_right->TabIndex = 26;
			   this->button_right->Text = L"Right";
			   this->button_right->UseVisualStyleBackColor = true;
			   this->button_right->Click += gcnew System::EventHandler(this, &MainForm::button_right_Click);
			   // 
			   // button_left
			   // 
			   this->button_left->Location = System::Drawing::Point(431, 41);
			   this->button_left->Name = L"button_left";
			   this->button_left->Size = System::Drawing::Size(75, 23);
			   this->button_left->TabIndex = 27;
			   this->button_left->Text = L"Left";
			   this->button_left->UseVisualStyleBackColor = true;
			   this->button_left->Click += gcnew System::EventHandler(this, &MainForm::button_left_Click);
			   // 
			   // button2
			   // 
			   this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(238)));
			   this->button2->Location = System::Drawing::Point(862, 516);
			   this->button2->Name = L"trainNewNeuralNet_button";
			   this->button2->Size = System::Drawing::Size(257, 116);
			   this->button2->TabIndex = 28;
			   this->button2->Text = L"Train new Neural Net";
			   this->button2->UseVisualStyleBackColor = true;
			   this->button2->Click += gcnew System::EventHandler(this, &MainForm::button_trainNeuralNet_Click);
			   // 
			   // label_NameOfCustomNeuralNet
			   // 
			   this->label_NameOfCustomNeuralNet->AutoSize = true;
			   this->label_NameOfCustomNeuralNet->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			   this->label_NameOfCustomNeuralNet->Location = System::Drawing::Point(881, 720);
			   this->label_NameOfCustomNeuralNet->Name = L"label_NameOfCustomNeuralNet";
			   this->label_NameOfCustomNeuralNet->Size = System::Drawing::Size(210, 20);
			   this->label_NameOfCustomNeuralNet->TabIndex = 29;
			   this->label_NameOfCustomNeuralNet->Text = L"Name of custom neural Net: ";
			   this->label_NameOfCustomNeuralNet->Visible = false;
			   // 
			   // MainForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1361, 970);
			   this->Controls->Add(this->label_NameOfCustomNeuralNet);
			   this->Controls->Add(this->button2);
			   this->Controls->Add(this->button_left);
			   this->Controls->Add(this->button_right);
			   this->Controls->Add(this->button_down);
			   this->Controls->Add(this->button_Up);
			   this->Controls->Add(this->label7);
			   this->Controls->Add(this->tableLayoutPanel_Propability);
			   this->Controls->Add(this->NumberGuess);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->label_result);
			   this->Controls->Add(this->tableLayoutPanel_draw);
			   this->Controls->Add(this->clear_button);
			   this->Controls->Add(this->custom_nn);
			   this->Controls->Add(this->standard_nn);
			   this->Controls->Add(this->Start_button);
			   this->Name = L"MainForm";
			   this->Text = L"Neural Network";
			   this->tableLayoutPanel_Propability->ResumeLayout(false);
			   this->tableLayoutPanel_Propability->PerformLayout();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion

	private:
		std::vector<std::vector<double>>TryAllPosition();
		void fillOutputTable(const std::vector<double>& resultValues);
		void MarshalString(String^ s, std::string& os);
		int returnTopBorder(int rows, int columns);
		int returnBottomBorder(int rows, int columns);
		int returnLeftBorder(int rows, int columns);
		int returnRightBorder(int rows, int columns);
		std::vector<double> LoadFromDrawing();
		System::Void custom_nn_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void standard_nn_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void labelDrawClick(System::Object^ sender, System::EventArgs^ e);
		System::Void Start_button_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void clear_button_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void UploadButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void button_Up_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void button_left_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void button_down_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void button_right_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void button_trainNeuralNet_Click(System::Object^ sender, System::EventArgs^ e);

	};
}
