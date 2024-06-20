#pragma once

#include <string>
#include <vector>
#include <shlobj.h>
#include <stdlib.h>
#include <Windows.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "info.h"
#include "miragezip.h"
#include "resource.h"

void ConvertString(System::String^, std::string&);

// Object y-positions
const int posYButtons[3] = { 63, -230, -523 },
posYButtonText[3] = { 227,-66, -359 },
posYStrengthText[3] = { 488, 195, -98 },
posYMatchText[3] = { 781, 488, 195 },
posYHeader1[3] = { 22, -271, -564 },
posYHeader2[3] = { 353, 60, -233 },
posYHeader3[3] = { 646, 353, 60 },
posYInput1[3] = { 438, 145, -148 },
posYInput2[3] = { 731, 438, 145 },
posYButtonNext1[3] = { 443, 150, -143 },
posYButtonNext2[3] = { 736, 443, 150 },
posYButtonBack1[3] = { 308, 15, -258 },
posYButtonBack2[3] = { 601, 307, 13 };

// 293 between regions

const std::vector<std::string> headerFrames =
{
	"'`-.,                ,.-`'",
	"`-.,'                ',.-`",
	"-.,'`                `',.-",
	".,`'-                -'`,.",
	",`'-.                .-'`,"
};

namespace Mirage
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for gui
	/// </summary>
	public ref class gui : public System::Windows::Forms::Form
	{
	private:
		MirageZip* miragePtr;

		int currentRegion{ 1 },
			transIncrement,
			anchor,
			snapIndex;

		bool imageSelected{ false },
			fileSelected{ false },
			passMatch{ false };

		const char* imagePath,
			* imageExt,
			* filePath,
			* exportPath;

	private: System::Windows::Forms::LinkLabel^ link_open;
	private: System::Windows::Forms::LinkLabel^ link_reset;
	private: System::Windows::Forms::LinkLabel^ link_divider;
	private: System::Windows::Forms::Label^ divider_top;


	private: System::Windows::Forms::LinkLabel^ link_more;


	public:
		gui(MirageZip &mirageObj)
		{
			miragePtr = &mirageObj;

			InitializeComponent();

			header_1->BringToFront();
			ActiveControl = button_go;
			button_go->Enabled = false;
			button_next1->Enabled = false;
			button_next2->Enabled = false;
			timer_anim->Start();

			button_next1->FlatStyle = FlatStyle::Flat;
			button_next2->FlatStyle = FlatStyle::Flat;
			button_back1->FlatStyle = FlatStyle::Flat;
			button_back2->FlatStyle = FlatStyle::Flat;
			button_next1->FlatAppearance->BorderSize = 0;
			button_next2->FlatAppearance->BorderSize = 0;	
			button_back1->FlatAppearance->BorderSize = 0;
			button_back2->FlatAppearance->BorderSize = 0;
		}

		void Translate()
		{
			header_1->Location = System::Drawing::Point(header_1->Location.X, header_1->Location.Y + transIncrement);
			header_2->Location = System::Drawing::Point(header_2->Location.X, header_2->Location.Y + transIncrement);
			header_3->Location = System::Drawing::Point(header_3->Location.X, header_3->Location.Y + transIncrement);
			header_1_back->Location = System::Drawing::Point(header_1_back->Location.X, header_1_back->Location.Y + transIncrement);

			button_image->Location = System::Drawing::Point(button_image->Location.X, button_image->Location.Y + transIncrement);
			button_file->Location = System::Drawing::Point(button_file->Location.X, button_file->Location.Y + transIncrement);
			button_go->Location = System::Drawing::Point(button_go->Location.X, button_go->Location.Y + transIncrement);

			text_button_image->Location = System::Drawing::Point(text_button_image->Location.X, text_button_image->Location.Y + transIncrement);
			text_button_file->Location = System::Drawing::Point(text_button_file->Location.X, text_button_file->Location.Y + transIncrement);
			text_strength->Location = System::Drawing::Point(text_strength->Location.X, text_strength->Location.Y + transIncrement);
			text_match->Location = System::Drawing::Point(text_match->Location.X, text_match->Location.Y + transIncrement);

			input_1->Location = System::Drawing::Point(input_1->Location.X, input_1->Location.Y + transIncrement);
			input_2->Location = System::Drawing::Point(input_2->Location.X, input_2->Location.Y + transIncrement);

			button_next1->Location = System::Drawing::Point(button_next1->Location.X, button_next1->Location.Y + transIncrement);
			button_next2->Location = System::Drawing::Point(button_next2->Location.X, button_next2->Location.Y + transIncrement);

			button_back1->Location = System::Drawing::Point(button_back1->Location.X, button_back1->Location.Y + transIncrement);
			button_back2->Location = System::Drawing::Point(button_back2->Location.X, button_back2->Location.Y + transIncrement);
		}
		void snapItems(int index)
		{
			header_1->Location = System::Drawing::Point(header_1->Location.X, posYHeader1[index]);
			header_2->Location = System::Drawing::Point(header_2->Location.X, posYHeader2[index]);
			header_3->Location = System::Drawing::Point(header_3->Location.X, posYHeader3[index]);
			header_1_back->Location = System::Drawing::Point(header_1_back->Location.X, posYHeader1[index]);

			button_image->Location = System::Drawing::Point(button_image->Location.X, posYButtons[index]);
			button_file->Location = System::Drawing::Point(button_file->Location.X, posYButtons[index]);
			button_go->Location = System::Drawing::Point(button_go->Location.X, posYButtons[index]);

			text_button_image->Location = System::Drawing::Point(text_button_image->Location.X, posYButtonText[index]);
			text_button_file->Location = System::Drawing::Point(text_button_file->Location.X, posYButtonText[index]);
			text_strength->Location = System::Drawing::Point(text_strength->Location.X, posYStrengthText[index]);
			text_match->Location = System::Drawing::Point(text_match->Location.X, posYMatchText[index]);

			input_1->Location = System::Drawing::Point(input_1->Location.X, posYInput1[index]);
			input_2->Location = System::Drawing::Point(input_2->Location.X, posYInput2[index]);

			button_next1->Location = System::Drawing::Point(button_next1->Location.X, posYButtonNext1[index]);
			button_next2->Location = System::Drawing::Point(button_next2->Location.X, posYButtonNext2[index]);

			button_back1->Location = System::Drawing::Point(button_back1->Location.X, posYButtonBack1[index]);
			button_back2->Location = System::Drawing::Point(button_back2->Location.X, posYButtonBack2[index]);
		}
		void Reset()
		{
			imageSelected = fileSelected = passMatch = false;
			imagePath = filePath = exportPath = nullptr;

			button_go->Enabled = false;

			input_1->Text = "";
			input_2->Text = "";
			text_button_image->Text = "< select image >";
			text_button_file->Text = "< select file >";
			text_button_image->ForeColor = System::Drawing::Color::Black;
			text_button_file->ForeColor = System::Drawing::Color::Black;

			BackgroundImage = getImageFromRes(IDB_PNG1);
			link_more->Visible = true;
			link_reset->Visible = false;
			link_open->Visible = false;
			link_divider->Visible = false;

			currentRegion = 1;

			timer_anim->Start();

			header_1->Location = System::Drawing::Point(header_1->Location.X, posYHeader1[0]);
			header_2->Location = System::Drawing::Point(header_2->Location.X, posYHeader2[0]);
			header_3->Location = System::Drawing::Point(header_3->Location.X, posYHeader3[0]);
			header_1_back->Location = System::Drawing::Point(header_1_back->Location.X, posYHeader1[0]);

			button_image->Location = System::Drawing::Point(button_image->Location.X, posYButtons[0]);
			button_file->Location = System::Drawing::Point(button_file->Location.X, posYButtons[0]);
			button_go->Location = System::Drawing::Point(button_go->Location.X, posYButtons[0]);

			text_button_image->Location = System::Drawing::Point(text_button_image->Location.X, posYButtonText[0]);
			text_button_file->Location = System::Drawing::Point(text_button_file->Location.X, posYButtonText[0]);
			text_strength->Location = System::Drawing::Point(text_strength->Location.X, posYStrengthText[0]);
			text_match->Location = System::Drawing::Point(text_match->Location.X, posYMatchText[0]);

			input_1->Location = System::Drawing::Point(input_1->Location.X, posYInput1[0]);
			input_2->Location = System::Drawing::Point(input_2->Location.X, posYInput2[0]);

			button_next1->Location = System::Drawing::Point(button_next1->Location.X, posYButtonNext1[0]);
			button_next2->Location = System::Drawing::Point(button_next2->Location.X, posYButtonNext2[0]);

			button_back1->Location = System::Drawing::Point(button_back1->Location.X, posYButtonBack1[0]);
			button_back2->Location = System::Drawing::Point(button_back2->Location.X, posYButtonBack2[0]);
		}

	protected:
		~gui()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::Label^ header_1;
	private: System::Windows::Forms::Button^ button_image;
	private: System::Windows::Forms::Button^ button_file;
	private: System::Windows::Forms::Button^ button_go;
	private: System::Windows::Forms::Label^ text_button_image;
	private: System::Windows::Forms::Label^ text_button_file;
	private: System::Windows::Forms::Label^ header_2;
	private: System::Windows::Forms::TextBox^ input_1;
	private: System::Windows::Forms::Timer^ timer_scroll;
	private: System::Windows::Forms::Label^ header_3;
	private: System::Windows::Forms::TextBox^ input_2;
	private: System::Windows::Forms::Button^ button_next1;
	private: System::Windows::Forms::Button^ button_next2;
	private: System::Windows::Forms::Button^ button_back1;
	private: System::Windows::Forms::Button^ button_back2;
	private: System::Windows::Forms::Label^ text_strength;
	private: System::Windows::Forms::Label^ text_match;
	private: System::Windows::Forms::Timer^ timer_anim;
	private: System::Windows::Forms::Label^ header_1_back;

	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(gui::typeid));
			this->header_1 = (gcnew System::Windows::Forms::Label());
			this->button_image = (gcnew System::Windows::Forms::Button());
			this->button_file = (gcnew System::Windows::Forms::Button());
			this->button_go = (gcnew System::Windows::Forms::Button());
			this->text_button_image = (gcnew System::Windows::Forms::Label());
			this->text_button_file = (gcnew System::Windows::Forms::Label());
			this->header_2 = (gcnew System::Windows::Forms::Label());
			this->input_1 = (gcnew System::Windows::Forms::TextBox());
			this->timer_scroll = (gcnew System::Windows::Forms::Timer(this->components));
			this->header_3 = (gcnew System::Windows::Forms::Label());
			this->input_2 = (gcnew System::Windows::Forms::TextBox());
			this->button_next1 = (gcnew System::Windows::Forms::Button());
			this->button_next2 = (gcnew System::Windows::Forms::Button());
			this->button_back1 = (gcnew System::Windows::Forms::Button());
			this->button_back2 = (gcnew System::Windows::Forms::Button());
			this->text_strength = (gcnew System::Windows::Forms::Label());
			this->text_match = (gcnew System::Windows::Forms::Label());
			this->timer_anim = (gcnew System::Windows::Forms::Timer(this->components));
			this->header_1_back = (gcnew System::Windows::Forms::Label());
			this->link_more = (gcnew System::Windows::Forms::LinkLabel());
			this->link_open = (gcnew System::Windows::Forms::LinkLabel());
			this->link_reset = (gcnew System::Windows::Forms::LinkLabel());
			this->link_divider = (gcnew System::Windows::Forms::LinkLabel());
			this->divider_top = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// header_1
			// 
			this->header_1->AutoSize = true;
			this->header_1->Font = (gcnew System::Drawing::Font(L"Lucida Console", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->header_1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(20)),
				static_cast<System::Int32>(static_cast<System::Byte>(50)));
			this->header_1->Location = System::Drawing::Point(346, 22);
			this->header_1->Name = L"header_1";
			this->header_1->Size = System::Drawing::Size(163, 19);
			this->header_1->TabIndex = 1;
			this->header_1->Text = L"MirageZip BETA";
			this->header_1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// button_image
			// 
			this->button_image->BackColor = System::Drawing::Color::White;
			this->button_image->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_image.BackgroundImage")));
			this->button_image->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_image->Location = System::Drawing::Point(38, 63);
			this->button_image->Name = L"button_image";
			this->button_image->Size = System::Drawing::Size(217, 197);
			this->button_image->TabIndex = 2;
			this->button_image->UseVisualStyleBackColor = false;
			this->button_image->Click += gcnew System::EventHandler(this, &gui::button_image_Click);
			// 
			// button_file
			// 
			this->button_file->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_file.BackgroundImage")));
			this->button_file->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_file->Location = System::Drawing::Point(318, 63);
			this->button_file->Name = L"button_file";
			this->button_file->Size = System::Drawing::Size(217, 197);
			this->button_file->TabIndex = 3;
			this->button_file->UseVisualStyleBackColor = false;
			this->button_file->Click += gcnew System::EventHandler(this, &gui::button_file_Click);
			// 
			// button_go
			// 
			this->button_go->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_go.BackgroundImage")));
			this->button_go->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_go->Location = System::Drawing::Point(595, 63);
			this->button_go->Name = L"button_go";
			this->button_go->Size = System::Drawing::Size(217, 197);
			this->button_go->TabIndex = 4;
			this->button_go->UseVisualStyleBackColor = false;
			this->button_go->Click += gcnew System::EventHandler(this, &gui::button_go_Click);
			// 
			// text_button_image
			// 
			this->text_button_image->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->text_button_image->Location = System::Drawing::Point(46, 219);
			this->text_button_image->MaximumSize = System::Drawing::Size(200, 28);
			this->text_button_image->Name = L"text_button_image";
			this->text_button_image->Size = System::Drawing::Size(200, 28);
			this->text_button_image->TabIndex = 5;
			this->text_button_image->Text = L"< select image >";
			this->text_button_image->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// text_button_file
			// 
			this->text_button_file->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->text_button_file->Location = System::Drawing::Point(326, 219);
			this->text_button_file->Name = L"text_button_file";
			this->text_button_file->Size = System::Drawing::Size(200, 28);
			this->text_button_file->TabIndex = 6;
			this->text_button_file->Text = L"< select file >";
			this->text_button_file->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// header_2
			// 
			this->header_2->AutoSize = true;
			this->header_2->Font = (gcnew System::Drawing::Font(L"Candara Light", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->header_2->ForeColor = System::Drawing::Color::Black;
			this->header_2->Location = System::Drawing::Point(258, 353);
			this->header_2->Name = L"header_2";
			this->header_2->Size = System::Drawing::Size(339, 59);
			this->header_2->TabIndex = 7;
			this->header_2->Text = L"Enter password";
			this->header_2->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// input_1
			// 
			this->input_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 26.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->input_1->Location = System::Drawing::Point(268, 438);
			this->input_1->MaxLength = 256;
			this->input_1->Name = L"input_1";
			this->input_1->Size = System::Drawing::Size(280, 47);
			this->input_1->TabIndex = 8;
			this->input_1->UseSystemPasswordChar = true;
			this->input_1->TextChanged += gcnew System::EventHandler(this, &gui::input_1_TextChanged);
			this->input_1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &gui::PollReturnKey);
			// 
			// timer_scroll
			// 
			this->timer_scroll->Interval = 1;
			this->timer_scroll->Tick += gcnew System::EventHandler(this, &gui::timer_scroll_Tick);
			// 
			// header_3
			// 
			this->header_3->Font = (gcnew System::Drawing::Font(L"Candara Light", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->header_3->ForeColor = System::Drawing::Color::Black;
			this->header_3->Location = System::Drawing::Point(226, 646);
			this->header_3->Name = L"header_3";
			this->header_3->Size = System::Drawing::Size(390, 59);
			this->header_3->TabIndex = 9;
			this->header_3->Text = L"Confirm password";
			this->header_3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// input_2
			// 
			this->input_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 26.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->input_2->Location = System::Drawing::Point(268, 731);
			this->input_2->MaxLength = 256;
			this->input_2->Name = L"input_2";
			this->input_2->Size = System::Drawing::Size(280, 47);
			this->input_2->TabIndex = 10;
			this->input_2->UseSystemPasswordChar = true;
			this->input_2->TextChanged += gcnew System::EventHandler(this, &gui::input_2_TextChanged);
			this->input_2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &gui::PollReturnKey);
			// 
			// button_next1
			// 
			this->button_next1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_next1.BackgroundImage")));
			this->button_next1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_next1->FlatAppearance->BorderSize = 0;
			this->button_next1->Location = System::Drawing::Point(554, 443);
			this->button_next1->Name = L"button_next1";
			this->button_next1->Size = System::Drawing::Size(38, 38);
			this->button_next1->TabIndex = 11;
			this->button_next1->UseVisualStyleBackColor = true;
			this->button_next1->Click += gcnew System::EventHandler(this, &gui::button_next1_Click);
			// 
			// button_next2
			// 
			this->button_next2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_next2.BackgroundImage")));
			this->button_next2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_next2->Location = System::Drawing::Point(554, 736);
			this->button_next2->Name = L"button_next2";
			this->button_next2->Size = System::Drawing::Size(38, 38);
			this->button_next2->TabIndex = 12;
			this->button_next2->UseVisualStyleBackColor = true;
			this->button_next2->Click += gcnew System::EventHandler(this, &gui::button_next2_Click);
			// 
			// button_back1
			// 
			this->button_back1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_back1.BackgroundImage")));
			this->button_back1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_back1->Location = System::Drawing::Point(12, 322);
			this->button_back1->Name = L"button_back1";
			this->button_back1->Size = System::Drawing::Size(35, 35);
			this->button_back1->TabIndex = 13;
			this->button_back1->UseVisualStyleBackColor = true;
			this->button_back1->Click += gcnew System::EventHandler(this, &gui::button_back1_Click);
			// 
			// button_back2
			// 
			this->button_back2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_back2.BackgroundImage")));
			this->button_back2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_back2->Location = System::Drawing::Point(12, 582);
			this->button_back2->Name = L"button_back2";
			this->button_back2->Size = System::Drawing::Size(35, 35);
			this->button_back2->TabIndex = 14;
			this->button_back2->UseVisualStyleBackColor = true;
			this->button_back2->Click += gcnew System::EventHandler(this, &gui::button_back2_Click);
			// 
			// text_strength
			// 
			this->text_strength->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->text_strength->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->text_strength->Location = System::Drawing::Point(329, 488);
			this->text_strength->Name = L"text_strength";
			this->text_strength->Size = System::Drawing::Size(180, 28);
			this->text_strength->TabIndex = 16;
			this->text_strength->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// text_match
			// 
			this->text_match->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->text_match->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->text_match->Location = System::Drawing::Point(329, 781);
			this->text_match->Name = L"text_match";
			this->text_match->Size = System::Drawing::Size(180, 28);
			this->text_match->TabIndex = 17;
			this->text_match->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// timer_anim
			// 
			this->timer_anim->Interval = 1;
			this->timer_anim->Tick += gcnew System::EventHandler(this, &gui::timer_anim_Tick);
			// 
			// header_1_back
			// 
			this->header_1_back->AutoSize = true;
			this->header_1_back->Font = (gcnew System::Drawing::Font(L"Lucida Console", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->header_1_back->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->header_1_back->Location = System::Drawing::Point(280, 22);
			this->header_1_back->Name = L"header_1_back";
			this->header_1_back->Size = System::Drawing::Size(295, 19);
			this->header_1_back->TabIndex = 18;
			this->header_1_back->Text = L"\'`-.,                ,.-`\'";
			this->header_1_back->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// link_more
			// 
			this->link_more->AutoSize = true;
			this->link_more->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->link_more->LinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->link_more->Location = System::Drawing::Point(786, 22);
			this->link_more->Name = L"link_more";
			this->link_more->Size = System::Drawing::Size(31, 13);
			this->link_more->TabIndex = 19;
			this->link_more->TabStop = true;
			this->link_more->Text = L"More";
			this->link_more->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &gui::link_more_LinkClicked);
			// 
			// link_open
			// 
			this->link_open->AutoSize = true;
			this->link_open->DisabledLinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->link_open->Font = (gcnew System::Drawing::Font(L"Candara", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->link_open->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->link_open->LinkColor = System::Drawing::Color::White;
			this->link_open->Location = System::Drawing::Point(408, 160);
			this->link_open->Name = L"link_open";
			this->link_open->Size = System::Drawing::Size(83, 14);
			this->link_open->TabIndex = 20;
			this->link_open->TabStop = true;
			this->link_open->Text = L"Open Location";
			this->link_open->Visible = false;
			this->link_open->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &gui::link_open_LinkClicked);
			// 
			// link_reset
			// 
			this->link_reset->AutoSize = true;
			this->link_reset->Font = (gcnew System::Drawing::Font(L"Candara", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->link_reset->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->link_reset->LinkColor = System::Drawing::Color::White;
			this->link_reset->Location = System::Drawing::Point(353, 160);
			this->link_reset->Name = L"link_reset";
			this->link_reset->Size = System::Drawing::Size(35, 14);
			this->link_reset->TabIndex = 21;
			this->link_reset->TabStop = true;
			this->link_reset->Text = L"Reset";
			this->link_reset->Visible = false;
			this->link_reset->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &gui::link_reset_LinkClicked);
			// 
			// link_divider
			// 
			this->link_divider->ActiveLinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->link_divider->AutoSize = true;
			this->link_divider->DisabledLinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->link_divider->Font = (gcnew System::Drawing::Font(L"Candara", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->link_divider->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->link_divider->LinkBehavior = System::Windows::Forms::LinkBehavior::NeverUnderline;
			this->link_divider->LinkColor = System::Drawing::Color::White;
			this->link_divider->Location = System::Drawing::Point(394, 160);
			this->link_divider->Name = L"link_divider";
			this->link_divider->Size = System::Drawing::Size(10, 14);
			this->link_divider->TabIndex = 22;
			this->link_divider->TabStop = true;
			this->link_divider->Text = L"|";
			this->link_divider->Visible = false;
			// 
			// divider_top
			// 
			this->divider_top->Font = (gcnew System::Drawing::Font(L"MS Gothic", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->divider_top->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->divider_top->Location = System::Drawing::Point(0, -17);
			this->divider_top->Name = L"divider_top";
			this->divider_top->Size = System::Drawing::Size(849, 24);
			this->divider_top->TabIndex = 23;
			this->divider_top->Text = L"-----------------------------------------------";
			this->divider_top->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// gui
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(850, 280);
			this->Controls->Add(this->divider_top);
			this->Controls->Add(this->link_divider);
			this->Controls->Add(this->link_reset);
			this->Controls->Add(this->link_open);
			this->Controls->Add(this->link_more);
			this->Controls->Add(this->header_1_back);
			this->Controls->Add(this->text_match);
			this->Controls->Add(this->text_strength);
			this->Controls->Add(this->button_back2);
			this->Controls->Add(this->button_back1);
			this->Controls->Add(this->button_next2);
			this->Controls->Add(this->button_next1);
			this->Controls->Add(this->input_2);
			this->Controls->Add(this->header_3);
			this->Controls->Add(this->input_1);
			this->Controls->Add(this->header_2);
			this->Controls->Add(this->text_button_file);
			this->Controls->Add(this->text_button_image);
			this->Controls->Add(this->button_go);
			this->Controls->Add(this->button_file);
			this->Controls->Add(this->button_image);
			this->Controls->Add(this->header_1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"gui";
			this->Opacity = 0.99;
			this->Text = L"MirageZip BETA";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		public: System::Drawing::Image^ getImageFromRes(long resource_ID) {
			// Function getImageFromRes
			// A function for loading PNG images from resources in C++ CLR/CLI
			// Copyright (C) Giuseppe Pischedda 2007 / Bordon / Simple

			//Load the resource module:
			HMODULE hInst = NULL;

			// Find the resource using the resource ID from file "resource.h"
			HRSRC hResource = ::FindResource(hInst, MAKEINTRESOURCE(resource_ID), L"PNG");
			if (!hResource) return nullptr;

			// Load the resource and save the total size.
			DWORD Size = SizeofResource(hInst, hResource);
			HGLOBAL MemoryHandle = LoadResource(hInst, hResource);
			if (MemoryHandle == NULL) return nullptr;

			//Create a cli::array of byte with size = total size + 2
			cli::array<BYTE>^ MemPtr = gcnew array<BYTE>(Size + 2);

			//Cast from LPVOID to char *
			char* lkr = (char*)(LockResource(MemoryHandle));

			//Copy from unmanaged memory to managed array
			System::Runtime::InteropServices::Marshal::Copy((IntPtr)lkr, MemPtr, 0, Size);

			// Create a new MemoryStream with size = MemPtr
			System::IO::MemoryStream^ stream = gcnew System::IO::MemoryStream(MemPtr);

			//Write in the MemoryStream
			stream->Write(MemPtr, 0, Size);

			//Set the position for read the stream
			stream->Position = 0;

			//Free allocated resources
			FreeLibrary(hInst);

			//Create an Image abstract class pointer
			System::Drawing::Image^ ptrPNG;

			//Assign the stream to abstract class pointer
			ptrPNG = System::Drawing::Image::FromStream(stream);
			return ptrPNG;
		}
		private: void PollReturnKey(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
		{
			if (e->KeyChar == (char)Keys::Return)
			{
				e->Handled = true;

				if (sender == input_1)
				{
					input_2->Text = "";
					ActiveControl = input_2;
					transIncrement = -20;
					timer_scroll->Start();
				}

				else if (sender == input_2)
				{
					std::string passwordData;
					ConvertString(this->input_1->Text, passwordData);
					miragePtr->SetPassword(passwordData.c_str());
					header_3->Text = "Confirmed password";
					header_3->ForeColor = System::Drawing::Color::FromArgb(255, 0, 255, 0);
					input_2->Visible = false;
					button_next2->Visible = false;
					text_match->Visible = false;
					button_back2->Visible = false;
				}
			}
		}
		private: System::Void timer_anim_Tick(System::Object^ sender, System::EventArgs^ e)
		{
			static int currentFrame{ 0 },
				ticks{ 0 },
				saved{ -1 },
				error{ 0 };

			static bool revealLinks{ false };
			
			if (currentRegion == 1)
			{
				if (++ticks == 7)
				{
					header_1_back->Text = (currentFrame < 4 ? gcnew String(headerFrames[++currentFrame].data()) : gcnew String(headerFrames[currentFrame = 0].data()));
					ticks = 0;
				}
			}

			if (header_3->Text == "Confirmed password")
			{
				if (header_3->Location.Y >= 60 && header_3->Location.Y < 90)
					header_3->Location = System::Drawing::Point(header_3->Location.X, header_3->Location.Y + 3);

				else if (header_3->ForeColor.R < 255)
					header_3->ForeColor = System::Drawing::Color::FromArgb(255, header_3->ForeColor.R + 5,
						(header_3->ForeColor.B < 220 ? 220 : header_3->ForeColor.G + 5),
						header_3->ForeColor.B + 5);

				else
				{

					header_3->ForeColor = System::Drawing::Color::FromArgb(255, 255, 255, 255);
					header_3->Text = "Success";
					BackgroundImage = getImageFromRes(IDB_PNG2);
					saved = 0;

					if (error = HideFile(miragePtr))
					{
						MessageBox::Show(gcnew String(miragePtr->GetError().c_str()));

						if (error == 1)
							Reset();
					}
				}
			}

			if (saved == 0)
			{
				if (System::IO::File::Exists(gcnew String(exportPath)))
					saved = 1;
			}

			else if (saved == 1)
			{
				if (header_3->ForeColor.R > 0)
					header_3->ForeColor = System::Drawing::Color::FromArgb(255, header_3->ForeColor.R - 5,
						220,
						header_3->ForeColor.B - 5);

				else
				{
					saved = 2;
					revealLinks = true;
				}
			}

			if (revealLinks)
			{
				link_divider->Visible = true;

				if (link_reset->Visible == false)
				{
					link_reset->Visible = true;
					link_open->Visible = true;
				}

				if (link_reset->LinkColor.R > 0)
				{
					link_reset->LinkColor = System::Drawing::Color::FromArgb(255,
						link_reset->LinkColor.R - 5,
						(link_reset->LinkColor.B - 5 > 220 ? link_reset->LinkColor.B - 5 : 220),
						link_reset->LinkColor.B - 5);
					link_open->LinkColor = System::Drawing::Color::FromArgb(255,
						link_open->LinkColor.R - 5,
						(link_open->LinkColor.B - 5 > 220 ? link_open->LinkColor.B - 5 : 220),
						link_open->LinkColor.B - 5);

					if (link_divider->LinkColor.R > 230)
					{
						link_divider->LinkColor = System::Drawing::Color::FromArgb(255,
							link_divider->LinkColor.R - 5,
							link_divider->LinkColor.G - 5,
							link_divider->LinkColor.B - 5);
					}
				}

				else
				{
					timer_anim->Stop();
					revealLinks = false;
				}
			}
		}
		private: System::Void timer_scroll_Tick(System::Object^ sender, System::EventArgs^ e)
		{
			// Translate from region 1
			if (currentRegion == 1)
			{
				if (BackgroundImage != nullptr)
					BackgroundImage = nullptr;

				Translate();

				// Snap y-positions and update region
				if (header_2->Location.Y <= posYHeader2[1])
				{
					snapItems(1);

					currentRegion = 2;

					timer_scroll->Stop();
				}
			}

			// Translate from region 2
			else if (currentRegion == 2)
			{
				Translate();

				// Snap y-positions and update region
				anchor = (transIncrement < 0 ? header_3->Location.Y : header_1->Location.Y * -1);

				if (anchor <= (transIncrement < 0 ? posYHeader3[2] : posYHeader1[0] * -1))
				{
					snapIndex = (transIncrement < 0 ? 2 : 0);

					snapItems(snapIndex);

					currentRegion = (transIncrement < 0 ? 3 : 1);
					link_more->Visible = (currentRegion == 1 ? true : false);
					BackgroundImage = (currentRegion == 1 ? getImageFromRes(IDB_PNG1) : nullptr);

					timer_scroll->Stop();
				}
			}

			// Translate from region 3
			else if (currentRegion == 3)
			{
				Translate();

				// Snap y-positions and update region
				if (header_2->Location.Y >= posYHeader2[1])
				{
					snapItems(1);

					currentRegion = 2;

					timer_scroll->Stop();
				}
			}
		}
		private: System::Void button_image_Click(System::Object^ sender, System::EventArgs^ e)
		{
			OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
			static std::string str;
			size_t strPos;

			openFileDialog1->InitialDirectory = gcnew String(getenv("USERPROFILE"));
			openFileDialog1->Filter = "Image Files|*.jpg;*.jpeg;*.png;*.gif;";
			openFileDialog1->FilterIndex = 2;
			openFileDialog1->RestoreDirectory = true;

			if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				ConvertString(openFileDialog1->FileName, str);
				imagePath = str.c_str();
				miragePtr->SetPath(MirageZip::PATH_TYPE::IMAGE, str);
				strPos = str.find_last_of("\\");
				str.erase(0, strPos + 1);

				text_button_image->Text = gcnew String(str.data());
				text_button_image->ForeColor = System::Drawing::Color::Green;

				strPos = str.find_last_of('.');
				str.erase(0, strPos);
				imageExt = str.c_str();

				imageSelected = true;

				if (fileSelected)
					button_go->Enabled = true;
			}
		}
		private: System::Void button_file_Click(System::Object^ sender, System::EventArgs^ e)
		{
			OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
			std::string str;
			size_t strPos;

			openFileDialog1->InitialDirectory = gcnew String(getenv("USERPROFILE"));
			openFileDialog1->Filter = "All files (*.*)|*.*";
			openFileDialog1->FilterIndex = 2;
			openFileDialog1->RestoreDirectory = true;

			if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				ConvertString(openFileDialog1->FileName, str);
				filePath = str.c_str();
				miragePtr->SetPath(MirageZip::PATH_TYPE::FILE, str);
				strPos = str.find_last_of("\\");
				str.erase(0, strPos + 1);

				text_button_file->Text = gcnew String(str.data());
				text_button_file->ForeColor = System::Drawing::Color::Green;

				fileSelected = true;

				if (imageSelected)
					button_go->Enabled = true;
			}
		}
		private: System::Void input_1_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{
			// Determine password strength
			std::string pw{ "" };
			ConvertString(input_1->Text, pw);
			unsigned int points{miragePtr->TestPassword(pw)};

			if (points < MEDIUM_SCORE)
			{
				text_strength->Text = "Weak";
				text_strength->ForeColor = System::Drawing::Color::Red;
			}
			else if (points == MEDIUM_SCORE)
			{
				text_strength->Text = "Fair";
				text_strength->ForeColor = System::Drawing::Color::Orange;
			}
			else if (points == STRONG_SCORE)
			{
				text_strength->Text = "Strong";
				text_strength->ForeColor = System::Drawing::Color::Green;
			}
			if (input_1->Text->Length > 0)
				button_next1->Enabled = true;
			else
			{
				button_next1->Enabled = false;
				text_strength->Text = "";
			}
		}
		private: System::Void button_go_Click(System::Object^ sender, System::EventArgs^ e)
		{
			static std::string filePath;
			std::string filter;
			filter = "Image Files|*";
			filter += imageExt;
			filter += ";";
			System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
			saveFileDialog1 = gcnew System::Windows::Forms::SaveFileDialog();
			saveFileDialog1->Filter = gcnew String(filter.data());
			System::Windows::Forms::DialogResult result = saveFileDialog1->ShowDialog();
			if (result == System::Windows::Forms::DialogResult::OK)
			{
				ConvertString(saveFileDialog1->FileName, filePath);
				exportPath = filePath.c_str();
				miragePtr->SetPath(MirageZip::PATH_TYPE::EXPORT, filePath);
				input_1->Text = "";
				ActiveControl = input_1;
				transIncrement = -20;
				link_more->Visible = false;
				timer_scroll->Start();
			}
		}
		private: System::Void button_back1_Click(System::Object^ sender, System::EventArgs^ e)
		{
			transIncrement = 20;
			timer_scroll->Start();
		}
		private: System::Void button_next1_Click(System::Object^ sender, System::EventArgs^ e)
		{
			input_2->Text = "";
			ActiveControl = input_2;
			transIncrement = -20;
			timer_scroll->Start();
		}
		private: System::Void button_back2_Click(System::Object^ sender, System::EventArgs^ e)
		{
			input_2->Text = "";
			ActiveControl = input_1;
			transIncrement = 20;
			timer_scroll->Start();
		}
		private: System::Void button_next2_Click(System::Object^ sender, System::EventArgs^ e)
		{
			std::string passwordData;
			ConvertString(this->input_1->Text, passwordData);
			miragePtr->SetPassword(passwordData.c_str());
			header_3->Text = "Confirmed password";
			header_3->ForeColor = System::Drawing::Color::FromArgb(255, 0, 255, 0);
			input_2->Visible = false;
			button_next2->Visible = false;
			text_match->Visible = false;
			button_back2->Visible = false;
		}
		private: System::Void input_2_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (input_2->Text == input_1->Text)
			{
				passMatch = true;
				text_match->Text = "Match";
				text_match->ForeColor = System::Drawing::Color::Green;
				button_next2->Enabled = true;
			}

			else
			{
				passMatch = false;
				text_match->Text = "Different";
				text_match->ForeColor = System::Drawing::Color::Red;
				button_next2->Enabled = false;
			}

			if (input_2->Text->Length < 1)
				text_match->Text = "";
		}
		private: System::Void link_more_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e)
		{
			info^ infoForm = gcnew info();
			infoForm->Show();
		}
		private: System::Void link_reset_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e)
		{
			Reset();
		}
		private: System::Void link_open_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e)
		{
			std::string cmd{ "C:\\Windows\\explorer.exe"},
				openPath{ exportPath };
			size_t pos = openPath.find_last_of("\\");
			openPath.erase(pos, openPath.length()-1);

			try
			{
				System::Diagnostics::Process::Start(gcnew String(cmd.data()), gcnew String(openPath.data()));
			}

			catch (...)
			{
				link_open->Text = "(failed to open)";
				link_open->Enabled = false;
			}
		}
	};
}

void ConvertString(System::String^ s, std::string& os)
{
	using namespace System::Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(System::IntPtr((void*)chars));
}