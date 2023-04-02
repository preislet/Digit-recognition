

using namespace System;

using namespace System::Windows::Forms;

#include "MainForm.h"
[STAThread]
int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew FormsProject::MainForm());
	return 0;
}

