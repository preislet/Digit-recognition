#pragma once

#include <string>
#include<iostream>
#include <vector>
#include<sstream>
#include "Image_conversion.hpp"
#include "Neural_network.hpp"
#using <System.dll>
#using <System.Drawing.dll>

namespace TrainNetworkGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Souhrn pro TrainNetworkGUI
	/// </summary>
	public ref class TrainNetworkGUI : public System::Windows::Forms::Form
	{
	public:
		TrainNetworkGUI(void)
		{
			InitializeComponent();
			//
			//TODO: Sem p�idejte k�d konstruktoru.
			//
		}

	protected:
		/// <summary>
		/// Uvoln�te v�echny pou��van� prost�edky.
		/// </summary>
		~TrainNetworkGUI()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Vy�aduje se prom�nn� n�vrh��e.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda vy�adovan� pro podporu N�vrh��e - neupravovat
		/// obsah t�to metody v editoru k�du.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// TrainNetworkGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1151, 644);
			this->Name = L"TrainNetworkGUI";
			this->Text = L"TrainNetworkGUI";
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
