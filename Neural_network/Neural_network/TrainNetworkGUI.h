#pragma once

#include <string>
#include<iostream>
#include <vector>
#include<sstream>
#include "Image_conversion.hpp"
#include "Neural_network.hpp"
#using <System.dll>
#using <System.Drawing.dll>

namespace TrainGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	void MarshalString(String^ s, std::string& os);

	static NeuralNet CustomNet;
	public ref class TrainNetworkGUI : public System::Windows::Forms::Form
	{
	public:
		TrainNetworkGUI(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Uvoln?te všechny používané prost?edky.
		/// </summary>
		~TrainNetworkGUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button_Train;
	protected:
	private: System::Windows::Forms::Button^ button_SaveNetwork;
	private: System::Windows::Forms::Label^ label_accuracy;
	private: System::Windows::Forms::Label^ label_alpha;
	private: System::Windows::Forms::Label^ label_eta;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox_topology;
	private: System::Windows::Forms::TextBox^ textBox_alpha;
	private: System::Windows::Forms::TextBox^ textBox_eta;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel_activationFunction;
	private: System::Windows::Forms::Label^ label_act;
	private: System::Windows::Forms::CheckBox^ checkBox_Sigmoid;
	private: System::Windows::Forms::Label^ label_activationFunction;
	private: System::Windows::Forms::CheckBox^ checkBox_SELU;
	private: System::Windows::Forms::CheckBox^ checkBox_Tanh;
	private: System::Windows::Forms::CheckBox^ checkBox_ReLU;
	private: System::Windows::Forms::CheckBox^ checkBox_LeakyReLU;
	private: System::Windows::Forms::CheckBox^ checkBox_ParametricReLU;
	private: System::Windows::Forms::CheckBox^ checkBox_ELU;
	private: System::Windows::Forms::CheckBox^ checkBox_Swish;
	private: System::Windows::Forms::CheckBox^ checkBox_GELU;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label_Name;
	private: System::Windows::Forms::TextBox^ textBox_Name;
	private: System::Windows::Forms::Label^ label_progress;
	private: System::Windows::Forms::Label^ label7;

	private:
		/// <summary>
		/// Vyžaduje se prom?nná návrhá?e.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda vyžadovaná pro podporu Návrhá?e - neupravovat
		/// obsah této metody v editoru kódu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button_Train = (gcnew System::Windows::Forms::Button());
			this->button_SaveNetwork = (gcnew System::Windows::Forms::Button());
			this->label_accuracy = (gcnew System::Windows::Forms::Label());
			this->label_alpha = (gcnew System::Windows::Forms::Label());
			this->label_eta = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox_topology = (gcnew System::Windows::Forms::TextBox());
			this->textBox_alpha = (gcnew System::Windows::Forms::TextBox());
			this->textBox_eta = (gcnew System::Windows::Forms::TextBox());
			this->tableLayoutPanel_activationFunction = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->checkBox_SELU = (gcnew System::Windows::Forms::CheckBox());
			this->label_act = (gcnew System::Windows::Forms::Label());
			this->checkBox_Sigmoid = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_Tanh = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_ReLU = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_LeakyReLU = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_ParametricReLU = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_ELU = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_Swish = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_GELU = (gcnew System::Windows::Forms::CheckBox());
			this->label_activationFunction = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label_Name = (gcnew System::Windows::Forms::Label());
			this->textBox_Name = (gcnew System::Windows::Forms::TextBox());
			this->label_progress = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel_activationFunction->SuspendLayout();
			this->SuspendLayout();
			// 
			// button_Train
			// 
			this->button_Train->BackColor = System::Drawing::SystemColors::Control;
			this->button_Train->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button_Train->Location = System::Drawing::Point(165, 12);
			this->button_Train->Name = L"button_Train";
			this->button_Train->Size = System::Drawing::Size(336, 87);
			this->button_Train->TabIndex = 0;
			this->button_Train->Text = L"Train";
			this->button_Train->UseVisualStyleBackColor = false;
			this->button_Train->Click += gcnew System::EventHandler(this, &TrainNetworkGUI::button_Train_Click);
			// 
			// button_SaveNetwork
			// 
			this->button_SaveNetwork->Enabled = false;
			this->button_SaveNetwork->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button_SaveNetwork->Location = System::Drawing::Point(280, 541);
			this->button_SaveNetwork->Name = L"button_SaveNetwork";
			this->button_SaveNetwork->Size = System::Drawing::Size(336, 91);
			this->button_SaveNetwork->TabIndex = 1;
			this->button_SaveNetwork->Text = L"Save Network";
			this->button_SaveNetwork->UseVisualStyleBackColor = true;
			this->button_SaveNetwork->Visible = false;
			this->button_SaveNetwork->Click += gcnew System::EventHandler(this, &TrainNetworkGUI::button_SaveNetwork_Click);
			// 
			// label_accuracy
			// 
			this->label_accuracy->AutoSize = true;
			this->label_accuracy->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label_accuracy->Location = System::Drawing::Point(270, 483);
			this->label_accuracy->Name = L"label_accuracy";
			this->label_accuracy->Size = System::Drawing::Size(315, 55);
			this->label_accuracy->TabIndex = 2;
			this->label_accuracy->Text = L"Accuracy: x%";
			// 
			// label_alpha
			// 
			this->label_alpha->AutoSize = true;
			this->label_alpha->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label_alpha->Location = System::Drawing::Point(12, 223);
			this->label_alpha->Name = L"label_alpha";
			this->label_alpha->Size = System::Drawing::Size(58, 20);
			this->label_alpha->TabIndex = 3;
			this->label_alpha->Text = L"Alpha: ";
			// 
			// label_eta
			// 
			this->label_eta->AutoSize = true;
			this->label_eta->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label_eta->Location = System::Drawing::Point(12, 257);
			this->label_eta->Name = L"label_eta";
			this->label_eta->Size = System::Drawing::Size(42, 20);
			this->label_eta->TabIndex = 4;
			this->label_eta->Text = L"Eta: ";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label1->Location = System::Drawing::Point(12, 192);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(81, 20);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Topology: ";
			// 
			// textBox_topology
			// 
			this->textBox_topology->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->textBox_topology->Location = System::Drawing::Point(99, 189);
			this->textBox_topology->Name = L"textBox_topology";
			this->textBox_topology->Size = System::Drawing::Size(160, 26);
			this->textBox_topology->TabIndex = 6;
			this->textBox_topology->TextChanged += gcnew System::EventHandler(this, &TrainNetworkGUI::textBox_topology_TextChanged);
			// 
			// textBox_alpha
			// 
			this->textBox_alpha->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->textBox_alpha->Location = System::Drawing::Point(99, 220);
			this->textBox_alpha->Name = L"textBox_alpha";
			this->textBox_alpha->Size = System::Drawing::Size(160, 26);
			this->textBox_alpha->TabIndex = 7;
			this->textBox_alpha->TextChanged += gcnew System::EventHandler(this, &TrainNetworkGUI::textBox_alpha_TextChanged);
			// 
			// textBox_eta
			// 
			this->textBox_eta->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->textBox_eta->Location = System::Drawing::Point(99, 254);
			this->textBox_eta->Name = L"textBox_eta";
			this->textBox_eta->Size = System::Drawing::Size(160, 26);
			this->textBox_eta->TabIndex = 8;
			this->textBox_eta->TextChanged += gcnew System::EventHandler(this, &TrainNetworkGUI::textBox_eta_TextChanged);
			// 
			// tableLayoutPanel_activationFunction
			// 
			this->tableLayoutPanel_activationFunction->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel_activationFunction->ColumnCount = 1;
			this->tableLayoutPanel_activationFunction->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel_activationFunction->Controls->Add(this->checkBox_SELU, 0, 9);
			this->tableLayoutPanel_activationFunction->Controls->Add(this->label_act, 0, 0);
			this->tableLayoutPanel_activationFunction->Controls->Add(this->checkBox_Sigmoid, 0, 1);
			this->tableLayoutPanel_activationFunction->Controls->Add(this->checkBox_Tanh, 0, 2);
			this->tableLayoutPanel_activationFunction->Controls->Add(this->checkBox_ReLU, 0, 3);
			this->tableLayoutPanel_activationFunction->Controls->Add(this->checkBox_LeakyReLU, 0, 4);
			this->tableLayoutPanel_activationFunction->Controls->Add(this->checkBox_ParametricReLU, 0, 5);
			this->tableLayoutPanel_activationFunction->Controls->Add(this->checkBox_ELU, 0, 6);
			this->tableLayoutPanel_activationFunction->Controls->Add(this->checkBox_Swish, 0, 7);
			this->tableLayoutPanel_activationFunction->Controls->Add(this->checkBox_GELU, 0, 8);
			this->tableLayoutPanel_activationFunction->Location = System::Drawing::Point(324, 162);
			this->tableLayoutPanel_activationFunction->Name = L"tableLayoutPanel_activationFunction";
			this->tableLayoutPanel_activationFunction->RowCount = 10;
			this->tableLayoutPanel_activationFunction->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				10)));
			this->tableLayoutPanel_activationFunction->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				10)));
			this->tableLayoutPanel_activationFunction->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				10)));
			this->tableLayoutPanel_activationFunction->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				10)));
			this->tableLayoutPanel_activationFunction->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				10)));
			this->tableLayoutPanel_activationFunction->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				10)));
			this->tableLayoutPanel_activationFunction->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				10)));
			this->tableLayoutPanel_activationFunction->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				10)));
			this->tableLayoutPanel_activationFunction->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				10)));
			this->tableLayoutPanel_activationFunction->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
				10)));
			this->tableLayoutPanel_activationFunction->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel_activationFunction->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel_activationFunction->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel_activationFunction->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel_activationFunction->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel_activationFunction->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel_activationFunction->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel_activationFunction->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel_activationFunction->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel_activationFunction->Size = System::Drawing::Size(210, 318);
			this->tableLayoutPanel_activationFunction->TabIndex = 9;
			// 
			// checkBox_SELU
			// 
			this->checkBox_SELU->AutoSize = true;
			this->checkBox_SELU->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->checkBox_SELU->Location = System::Drawing::Point(4, 283);
			this->checkBox_SELU->Name = L"checkBox_SELU";
			this->checkBox_SELU->Size = System::Drawing::Size(71, 24);
			this->checkBox_SELU->TabIndex = 9;
			this->checkBox_SELU->Tag = L"8";
			this->checkBox_SELU->Text = L"SELU";
			this->checkBox_SELU->UseVisualStyleBackColor = true;
			this->checkBox_SELU->Click += gcnew System::EventHandler(this, &TrainNetworkGUI::check_ActivationFunction_Click);
			// 
			// label_act
			// 
			this->label_act->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label_act->AutoSize = true;
			this->label_act->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label_act->Location = System::Drawing::Point(29, 6);
			this->label_act->Name = L"label_act";
			this->label_act->Size = System::Drawing::Size(151, 20);
			this->label_act->TabIndex = 0;
			this->label_act->Text = L"Activation functions:";
			// 
			// checkBox_Sigmoid
			// 
			this->checkBox_Sigmoid->AutoSize = true;
			this->checkBox_Sigmoid->Checked = true;
			this->checkBox_Sigmoid->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox_Sigmoid->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->checkBox_Sigmoid->Location = System::Drawing::Point(4, 35);
			this->checkBox_Sigmoid->Name = L"checkBox_Sigmoid";
			this->checkBox_Sigmoid->Size = System::Drawing::Size(85, 24);
			this->checkBox_Sigmoid->TabIndex = 1;
			this->checkBox_Sigmoid->Tag = L"0";
			this->checkBox_Sigmoid->Text = L"Sigmoid";
			this->checkBox_Sigmoid->UseVisualStyleBackColor = true;
			this->checkBox_Sigmoid->Click += gcnew System::EventHandler(this, &TrainNetworkGUI::check_ActivationFunction_Click);
			// 
			// checkBox_Tanh
			// 
			this->checkBox_Tanh->AutoSize = true;
			this->checkBox_Tanh->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->checkBox_Tanh->Location = System::Drawing::Point(4, 66);
			this->checkBox_Tanh->Name = L"checkBox_Tanh";
			this->checkBox_Tanh->Size = System::Drawing::Size(64, 24);
			this->checkBox_Tanh->TabIndex = 2;
			this->checkBox_Tanh->Tag = L"1";
			this->checkBox_Tanh->Text = L"Tanh";
			this->checkBox_Tanh->UseVisualStyleBackColor = true;
			this->checkBox_Tanh->Click += gcnew System::EventHandler(this, &TrainNetworkGUI::check_ActivationFunction_Click);
			// 
			// checkBox_ReLU
			// 
			this->checkBox_ReLU->AutoSize = true;
			this->checkBox_ReLU->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->checkBox_ReLU->Location = System::Drawing::Point(4, 97);
			this->checkBox_ReLU->Name = L"checkBox_ReLU";
			this->checkBox_ReLU->Size = System::Drawing::Size(70, 24);
			this->checkBox_ReLU->TabIndex = 3;
			this->checkBox_ReLU->Tag = L"2";
			this->checkBox_ReLU->Text = L"ReLU";
			this->checkBox_ReLU->UseVisualStyleBackColor = true;
			this->checkBox_ReLU->Click += gcnew System::EventHandler(this, &TrainNetworkGUI::check_ActivationFunction_Click);
			// 
			// checkBox_LeakyReLU
			// 
			this->checkBox_LeakyReLU->AutoSize = true;
			this->checkBox_LeakyReLU->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->checkBox_LeakyReLU->Location = System::Drawing::Point(4, 128);
			this->checkBox_LeakyReLU->Name = L"checkBox_LeakyReLU";
			this->checkBox_LeakyReLU->Size = System::Drawing::Size(112, 24);
			this->checkBox_LeakyReLU->TabIndex = 4;
			this->checkBox_LeakyReLU->Tag = L"3";
			this->checkBox_LeakyReLU->Text = L"LeakyReLU";
			this->checkBox_LeakyReLU->UseVisualStyleBackColor = true;
			this->checkBox_LeakyReLU->Click += gcnew System::EventHandler(this, &TrainNetworkGUI::check_ActivationFunction_Click);
			// 
			// checkBox_ParametricReLU
			// 
			this->checkBox_ParametricReLU->AutoSize = true;
			this->checkBox_ParametricReLU->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->checkBox_ParametricReLU->Location = System::Drawing::Point(4, 159);
			this->checkBox_ParametricReLU->Name = L"checkBox_ParametricReLU";
			this->checkBox_ParametricReLU->Size = System::Drawing::Size(146, 24);
			this->checkBox_ParametricReLU->TabIndex = 5;
			this->checkBox_ParametricReLU->Tag = L"4";
			this->checkBox_ParametricReLU->Text = L"ParametricReLU";
			this->checkBox_ParametricReLU->UseVisualStyleBackColor = true;
			this->checkBox_ParametricReLU->Click += gcnew System::EventHandler(this, &TrainNetworkGUI::check_ActivationFunction_Click);
			// 
			// checkBox_ELU
			// 
			this->checkBox_ELU->AutoSize = true;
			this->checkBox_ELU->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->checkBox_ELU->Location = System::Drawing::Point(4, 190);
			this->checkBox_ELU->Name = L"checkBox_ELU";
			this->checkBox_ELU->Size = System::Drawing::Size(60, 24);
			this->checkBox_ELU->TabIndex = 6;
			this->checkBox_ELU->Tag = L"5";
			this->checkBox_ELU->Text = L"ELU";
			this->checkBox_ELU->UseVisualStyleBackColor = true;
			this->checkBox_ELU->Click += gcnew System::EventHandler(this, &TrainNetworkGUI::check_ActivationFunction_Click);
			// 
			// checkBox_Swish
			// 
			this->checkBox_Swish->AutoSize = true;
			this->checkBox_Swish->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->checkBox_Swish->Location = System::Drawing::Point(4, 221);
			this->checkBox_Swish->Name = L"checkBox_Swish";
			this->checkBox_Swish->Size = System::Drawing::Size(70, 24);
			this->checkBox_Swish->TabIndex = 7;
			this->checkBox_Swish->Tag = L"6";
			this->checkBox_Swish->Text = L"Swish";
			this->checkBox_Swish->UseVisualStyleBackColor = true;
			this->checkBox_Swish->Click += gcnew System::EventHandler(this, &TrainNetworkGUI::check_ActivationFunction_Click);
			// 
			// checkBox_GELU
			// 
			this->checkBox_GELU->AutoSize = true;
			this->checkBox_GELU->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->checkBox_GELU->Location = System::Drawing::Point(4, 252);
			this->checkBox_GELU->Name = L"checkBox_GELU";
			this->checkBox_GELU->Size = System::Drawing::Size(73, 24);
			this->checkBox_GELU->TabIndex = 8;
			this->checkBox_GELU->Tag = L"7";
			this->checkBox_GELU->Text = L"GELU";
			this->checkBox_GELU->UseVisualStyleBackColor = true;
			this->checkBox_GELU->Click += gcnew System::EventHandler(this, &TrainNetworkGUI::check_ActivationFunction_Click);
			// 
			// label_activationFunction
			// 
			this->label_activationFunction->AutoSize = true;
			this->label_activationFunction->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(238)));
			this->label_activationFunction->Location = System::Drawing::Point(12, 162);
			this->label_activationFunction->Name = L"label_activationFunction";
			this->label_activationFunction->Size = System::Drawing::Size(204, 20);
			this->label_activationFunction->TabIndex = 10;
			this->label_activationFunction->Text = L"Activation function: Sigmoid";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label2->Location = System::Drawing::Point(17, 508);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(247, 24);
			this->label2->TabIndex = 11;
			this->label2->Text = L"Default network parameters: ";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label3->Location = System::Drawing::Point(17, 551);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(183, 20);
			this->label3->TabIndex = 12;
			this->label3->Text = L"Topology: 784;128;64;10";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label4->Location = System::Drawing::Point(17, 532);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(189, 20);
			this->label4->TabIndex = 13;
			this->label4->Text = L"Activation function: ReLU";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label5->Location = System::Drawing::Point(17, 571);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(134, 20);
			this->label5->TabIndex = 14;
			this->label5->Text = L"Alpha: 0.0889798";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label6->Location = System::Drawing::Point(17, 591);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(109, 20);
			this->label6->TabIndex = 15;
			this->label6->Text = L"Eta: 0.033665";
			// 
			// label_Name
			// 
			this->label_Name->AutoSize = true;
			this->label_Name->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label_Name->Location = System::Drawing::Point(12, 290);
			this->label_Name->Name = L"label_Name";
			this->label_Name->Size = System::Drawing::Size(55, 20);
			this->label_Name->TabIndex = 16;
			this->label_Name->Text = L"Name:";
			// 
			// textBox_Name
			// 
			this->textBox_Name->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->textBox_Name->Location = System::Drawing::Point(99, 288);
			this->textBox_Name->Name = L"textBox_Name";
			this->textBox_Name->Size = System::Drawing::Size(160, 26);
			this->textBox_Name->TabIndex = 17;
			this->textBox_Name->TextChanged += gcnew System::EventHandler(this, &TrainNetworkGUI::textBox_Name_TextChanged);
			// 
			// label_progress
			// 
			this->label_progress->AutoSize = true;
			this->label_progress->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label_progress->Location = System::Drawing::Point(36, 343);
			this->label_progress->Name = L"label_progress";
			this->label_progress->Size = System::Drawing::Size(213, 31);
			this->label_progress->TabIndex = 18;
			this->label_progress->Text = L"Training finished";
			this->label_progress->Visible = false;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label7->Location = System::Drawing::Point(148, 102);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(374, 20);
			this->label7->TabIndex = 19;
			this->label7->Text = L"Training is possible only when all text boxes are filled";
			// 
			// TrainNetworkGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(681, 644);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label_progress);
			this->Controls->Add(this->textBox_Name);
			this->Controls->Add(this->label_Name);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label_activationFunction);
			this->Controls->Add(this->tableLayoutPanel_activationFunction);
			this->Controls->Add(this->textBox_eta);
			this->Controls->Add(this->textBox_alpha);
			this->Controls->Add(this->textBox_topology);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->label_eta);
			this->Controls->Add(this->label_alpha);
			this->Controls->Add(this->label_accuracy);
			this->Controls->Add(this->button_SaveNetwork);
			this->Controls->Add(this->button_Train);
			this->Name = L"TrainNetworkGUI";
			this->Text = L"Train";
			this->tableLayoutPanel_activationFunction->ResumeLayout(false);
			this->tableLayoutPanel_activationFunction->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		bool topologyInserted = false;
		bool alphaInserted = false;
		bool etaInserted = false;
		bool nameInserted = false;
		bool activationFunctionInserted = true;
		int activationFunctionNum = 0;


	private: System::Void button_Train_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_SaveNetwork_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void check_ActivationFunction_Click(System::Object^ sender, System::EventArgs^ e);
	private: void writeNeuralNetInfoToFile(const NeuralNet& CustomNet, const std::string& name);
	private: System::Void textBox_eta_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void textBox_topology_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void textBox_alpha_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void textBox_Name_TextChanged(System::Object^ sender, System::EventArgs^ e);
};
}