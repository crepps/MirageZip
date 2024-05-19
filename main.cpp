#include "gui.h"
#include "miragezip.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
	MirageZip mirageObj;

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Mirage::gui form(mirageObj);
	Application::Run(% form);

	return 0;
}