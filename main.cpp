#include "gui.h"
#include "miragezip.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
	MirageZip obj;

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Mirage::gui form;
	Application::Run(% form);

	return 0;
}