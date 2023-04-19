#include<iostream>
#include<stdlib.h>
#include<crtdbg.h>

using namespace System;

using namespace System::Windows::Forms;

#include "NeuralNetMainGUI.h"
#include "Tests.hpp";
[STAThread]
int main(int argc, char** argv){
	std::vector<std::string> args(argv, argv + argc);

	if(args.size() == 2 && args[1] == "-test")
	{
		Testing::RunAllTests();
	}
	else
	{
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		Application::Run(gcnew NeuralNetGUI::MainForm());
	}
	
	

	return 0;
	
}

