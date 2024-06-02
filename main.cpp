#include "miragezip.h"
#include "gui.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
	try
	{
		MirageZip mirageObj;
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		Mirage::gui mainForm(mirageObj);
		Application::Run(% mainForm);
	}
	catch (std::exception& e)
	{
		MessageBox::Show(gcnew String(e.what()));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}