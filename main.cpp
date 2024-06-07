#include "miragezip.h"
#include "gui.h"

//#define UNIT_TESTING

using namespace System;
using namespace System::Windows::Forms;


#ifdef UNIT_TESTING
#include "gmock/gmock.h"
using namespace testing;
class MirageTesting : public ::testing::Test
{
public:
	MirageZip mirage;
};

TEST_F(MirageTesting, WeakPasswordTest)
{
	ASSERT_THAT(mirage.TestPassword("121212121212"), Le(WEAK_SCORE));
	ASSERT_THAT(mirage.TestPassword("verylongpassword"), Le(WEAK_SCORE));
	
}
TEST_F(MirageTesting, MediumPasswordTest)
{
	ASSERT_THAT(mirage.TestPassword("Password1234"), Eq(MEDIUM_SCORE));
	ASSERT_THAT(mirage.TestPassword("$Password2$"), Eq(MEDIUM_SCORE));
	ASSERT_THAT(mirage.TestPassword("!!!!1234567890!!!!"), Eq(MEDIUM_SCORE));
}
TEST_F(MirageTesting, StrongPasswordTest)
{
	ASSERT_THAT(mirage.TestPassword("Password#12!"), Eq(STRONG_SCORE));
	ASSERT_THAT(mirage.TestPassword("good.Pass123"), Eq(STRONG_SCORE));
}
#endif

[STAThreadAttribute]
int main(array<String^>^ args)
{
#ifdef UNIT_TESTING
	testing::InitGoogleMock();

	if (RUN_ALL_TESTS())
		return EXIT_FAILURE;
#endif

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