#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

[System::STAThread]
int main(array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	DiplomaUI::MainForm myForm;
	Application::Run(%myForm);

	return 0;
}