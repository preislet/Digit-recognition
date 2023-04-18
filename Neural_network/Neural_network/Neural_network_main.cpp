#include<iostream>
#include<stdlib.h>
#include<crtdbg.h>

using namespace System;

using namespace System::Windows::Forms;

#include "NeuralNetMainGUI.h"
[STAThread]
int main(){

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew NeuralNetGUI::MainForm());
	

	return 0;
	
}

